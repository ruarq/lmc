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

namespace Lm
{

auto Lexer::Run(const char *source_, const char *end_) -> std::vector<Token>
{
	start = source_;
	curr = source_;
	end = end_;

	std::vector<Token> tokens;
	while (curr < end)
	{
		auto token = NextToken();
		if (token.type != Token::Type::Unknown)
		{
			token.offset = curr - start;
			tokens.push_back(token);
		}
		else if (curr >= end)
		{
			tokens.push_back(Token::Type::Eof);
		}
	}

	return tokens;
}

auto Lexer::NextToken() -> Lm::Token
{
NEXT_TOKEN:

	switch (*curr++)
	{
		// Skip whitespace
		case ' ':
		case '\n':
		case '\t':
		case '\r':
		case '\f':
			while (curr < end && (*curr == ' ' || *curr == '\n' || *curr == '\t' || *curr == '\r' ||
									 *curr == '\f'))
			{
				++curr;
			}
			goto NEXT_TOKEN;

		// Skip comments
		case '#':
			while (*curr != '\n')
			{
				++curr;
			}
			goto NEXT_TOKEN;

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

			std::string symbol(tokStart, curr);
			auto type = Token::Type::Ident;

			if (stringToTokenType.find(symbol) != stringToTokenType.end())
			{
				type = stringToTokenType.at(symbol);
			}

			if (type == Token::Type::Ident)
			{
				return Token(type, std::move(symbol));
			}

			return type;
		}

		case '"':
		{
			const auto tokStart = curr;
			while (curr < end && *curr != '"' && '\n')
			{
				++curr;
			}
			if (*++curr != '"')
			{
				// TODO(ruarq): error
			}
			return Token(Token::Type::StringLiteral, std::string(tokStart, curr - 1));
		}

		case '\'':
		{
			std::string symbol = { *curr };
			if (*++curr)
			{
				// TODO(ruarq): error
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
				++curr;
				return Token::Type::Arrow;
			}
			else if (*curr == '=')
			{
				++curr;
				return Token::Type::MinusEqual;
			}
			return Token::Type::Minus;

		case '=':
			if (*curr == '=')
			{
				++curr;
				return Token::Type::Equal;
			}
			else if (*curr == '>')
			{
				++curr;
				return Token::Type::WideArrow;
			}
			return Token::Type::Assign;

		case ':':
			if (*curr == ':')
			{
				++curr;
				return Token::Type::ColonColon;
			}
			return Token::Type::Colon;

		case '+':
			if (*curr == '+')
			{
				++curr;
				return Token::Type::PlusEqual;
			}
			else if (*curr == '=')
			{
				++curr;
				return Token::Type::Plus;
			}
			return Token::Type::Plus;

		case '*':
			if (*curr == '=')
			{
				++curr;
				return Token::Type::StarEqual;
			}
			return Token::Type::Star;

		case '/':
			if (*curr == '=')
			{
				++curr;
				return Token::Type::SlashEqual;
			}
			return Token::Type::Slash;

		case '%':
			if (*curr == '=')
			{
				++curr;
				return Token::Type::ModEqual;
			}
			return Token::Type::Mod;

		case '!':
			if (*curr == '=')
			{
				++curr;
				return Token::Type::NotEqual;
			}
			return Token::Type::Not;

		case '<':
			if (*curr == '<')
			{
				++curr;
				if (*curr == '=')
				{
					++curr;
					return Token::Type::LShiftEqual;
				}
				return Token::Type::LShift;
			}
			else if (*curr == '=')
			{
				++curr;
				return Token::Type::LessEqual;
			}
			return Token::Type::Less;

		case '>':
			if (*curr == '>')
			{
				++curr;
				if (*curr == '=')
				{
					++curr;
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
				++curr;
				return Token::Type::AndAnd;
			}
			else if (*curr == '=')
			{
				++curr;
				return Token::Type::AndEqual;
			}
			return Token::Type::And;

		case '|':
			if (*curr == '|')
			{
				++curr;
				return Token::Type::OrOr;
			}
			else if (*curr == '=')
			{
				++curr;
				return Token::Type::OrEqual;
			}
			return Token::Type::Or;

		case '^':
			if (*curr == '=')
			{
				++curr;
				return Token::Type::XorEqual;
			}
			return Token::Type::Xor;

		case '~':
			if (*curr == '=')
			{
				++curr;
				return Token::Type::FlipEqual;
			}
			return Token::Type::Flip;

		default: break;
	}

	return Token::Type::Unknown;
}
}
