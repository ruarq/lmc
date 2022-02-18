/**
 * @author ruarq
 * @date 12.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "Lexer.hpp"

#define COLUMN_START 1
#define LINE_START 1

namespace Lm
{

Lexer::Lexer(const File &file, const Diagnostics &diagnostics)
	: start(file.Buf())
	, curr(start)
	, end(file.Buf() + file.Size())
	, pos({ .line = LINE_START, .column = COLUMN_START, .offset = 0 })
	, line(LINE_START)
	, column(COLUMN_START)
	, diagnostics(diagnostics)
{
}

auto Lexer::NextToken() -> Lm::Token
{
#if LM_LEXER_BUFFER_ENABLE
	if (bufToken >= buffer.size())
	{
		bufToken = 0;
		for (auto token = buffer.begin(); token != buffer.end() && !Eof(); ++token)
		{
			*token = LexToken();
			token->pos = pos;
		}
	}

	return buffer[bufToken++];
#else
	auto token = LexToken();
	token.pos = pos;
	return token;
#endif
}

auto Lexer::Eof() const -> bool
{
	return curr >= end;
}

auto Lexer::LexToken() -> Lm::Token
{
L_LEX_TOKEN:

	if (Eof())
	{
		return Token::Type::Eof;
	}

	pos.line = line;
	pos.column = column;
	pos.offset = curr - start;

	++column;
	switch (*curr++)
	{
		// Skip whitespace
		case '\n':
			++line;
			column = COLUMN_START;
			[[fallthrough]];
		case ' ':
		case '\t':
		case '\r':
		case '\f':
		{
			const auto prev = curr;
			while (curr < end && (*curr == ' ' || *curr == '\n' || *curr == '\t'))
			{
				if (*curr == '\n')
				{
					column = COLUMN_START;
					++line;
				}

				++curr;
			}
			column += curr - prev;
			goto L_LEX_TOKEN;
		}

		// Skip comments
		case '#':
			while (*curr != '\n')
			{
				++curr;
			}
			++curr;	   // Whitespace
			column = COLUMN_START;
			++line;
			goto L_LEX_TOKEN;

		case '0' ... '9':
		{
			const auto tokStart = curr - 1;
			auto type = Token::Type::Int32Literal;

			while (curr < end && *curr >= '0' && *curr <= '9')
			{
				++curr;
			}

			if (*curr == '.')
			{
				type = Token::Type::Float64Literal;
				++curr;
				while (*curr >= '0' && *curr <= '9')
				{
					++curr;
				}
			}

			column += curr - tokStart - 1;
			return Token(type, std::string(tokStart, curr));
		}

		case 'A' ... 'Z':
		case 'a' ... 'z':
		case '_':
		{
			const auto tokStart = curr - 1;

			while (
				curr < end && ((*curr >= 'A' && *curr <= 'Z') || (*curr >= 'a' && *curr <= 'z') ||
								  (*curr >= '0' && *curr <= '9') || (*curr == '_')))
			{
				++curr;
			}

			column += curr - tokStart - 1;

			std::string symbol(tokStart, curr);

			const auto type = GetKeywordType(symbol);
			if (type == Token::Type::Ident)
			{
				return Token(type, std::move(symbol));
			}

			return type;
		}

		case '"':
		{
			const auto tokStart = curr - 1;
			while (curr < end && *curr != '"' && *curr != '\n')
			{
				++curr;
			}

			if (*curr++ != '"')
			{
				diagnostics.Error(pos, Locale::Get("LEXER_ERROR_UNTERMINATED_STRING"));
			}

			column += curr - tokStart - 1;

			return Token(Token::Type::StringLiteral, std::string(tokStart, curr - 1));
		}

		case '\'':
		{
			std::string symbol = { *curr++ };
			if (*curr != '\'')
			{
				diagnostics.Error(pos, Locale::Get("LEXER_ERROR_UNTERMINATED_CHAR"));
			}
			return Token(Token::Type::CharLiteral, std::move(symbol));
		}

		case '(': return Token::Type::LParen;
		case ')': return Token::Type::RParen;
		case '[': return Token::Type::LBracket;
		case ']': return Token::Type::RBracket;
		case '{': return Token::Type::LCurly;
		case '}': return Token::Type::RCurly;
		case ';': return Token::Type::Semicolon;
		case '.': return Token::Type::Dot;
		case ',': return Token::Type::Comma;
		case '$': return Token::Type::Cast;
		case '@': return Token::Type::Attribute;

		case '-':
			if (*curr == '>')
			{
				Next();
				return Token::Type::Arrow;
			}
			else if (*curr == '=')
			{
				Next();
				return Token::Type::MinusEqual;
			}
			return Token::Type::Minus;

		case '=':
			if (*curr == '=')
			{
				Next();
				return Token::Type::Equal;
			}
			else if (*curr == '>')
			{
				Next();
				return Token::Type::WideArrow;
			}
			return Token::Type::Assign;

		case ':':
			if (*curr == ':')
			{
				Next();
				return Token::Type::ColonColon;
			}
			return Token::Type::Colon;

		case '+':
			if (*curr == '+')
			{
				Next();
				return Token::Type::PlusEqual;
			}
			else if (*curr == '=')
			{
				Next();
				return Token::Type::Plus;
			}
			return Token::Type::Plus;

		case '*':
			if (*curr == '=')
			{
				Next();
				return Token::Type::StarEqual;
			}
			return Token::Type::Star;

		case '/':
			if (*curr == '=')
			{
				Next();
				return Token::Type::SlashEqual;
			}
			return Token::Type::Slash;

		case '%':
			if (*curr == '=')
			{
				Next();
				return Token::Type::ModEqual;
			}
			return Token::Type::Mod;

		case '!':
			if (*curr == '=')
			{
				Next();
				return Token::Type::NotEqual;
			}
			return Token::Type::Not;

		case '<':
			if (*curr == '<')
			{
				Next();
				if (*curr == '=')
				{
					Next();
					return Token::Type::LShiftEqual;
				}
				return Token::Type::LShift;
			}
			else if (*curr == '=')
			{
				Next();
				return Token::Type::LessEqual;
			}
			return Token::Type::Less;

		case '>':
			if (*curr == '>')
			{
				Next();
				if (*curr == '=')
				{
					Next();
					return Token::Type::RShiftEqual;
				}
				return Token::Type::RShift;
			}
			else if (*curr == '=')
			{
				++curr;
				return Token::Type::GreaterEqual;
			}
			return Token::Type::Greater;

		case '&':
			if (*curr == '&')
			{
				Next();
				return Token::Type::AndAnd;
			}
			else if (*curr == '=')
			{
				Next();
				return Token::Type::AndEqual;
			}
			return Token::Type::And;

		case '|':
			if (*curr == '|')
			{
				Next();
				return Token::Type::OrOr;
			}
			else if (*curr == '=')
			{
				Next();
				return Token::Type::OrEqual;
			}
			return Token::Type::Or;

		case '^':
			if (*curr == '=')
			{
				Next();
				return Token::Type::XorEqual;
			}
			return Token::Type::Xor;

		case '~':
			if (*curr == '=')
			{
				Next();
				return Token::Type::FlipEqual;
			}
			return Token::Type::Flip;

		default: break;
	}

	diagnostics.Error(pos, fmt::format(Locale::Get("LEXER_ERROR_UNKNOWN_TOKEN"), *curr));
	goto L_LEX_TOKEN;
}

auto Lexer::Next() -> void
{
	++curr;
	++column;
}

}
