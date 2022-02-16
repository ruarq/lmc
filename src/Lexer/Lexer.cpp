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

auto Lexer::Run(const std::string &filename, std::string &&source) -> std::vector<Token>
{
	this->name = filename;
	this->source = std::move(source);
	pos = { 1, 0 };
	current = 0;

	std::vector<Token> tokens;

	while (!Eof())
	{
		tokens.push_back(NextToken());
	}

	return tokens;
}

auto Lexer::HadError() const -> bool
{
	return hadError;
}

auto Lexer::NextToken() -> Token
{
	auto SingleToken = [&](const Token::Type type) {
		File::Loc loc {
			.start = pos,
			.end = {pos.line, pos.column + 1},
			.offset = current
		};
		return Token(type, std::string { Consume() }, std::move(loc));
	};

	auto MultiToken = [&](const Token::Type type, const size_t size) {
		std::string literal;

		File::Loc loc;
		loc.start = pos;
		loc.offset = current;

		for (size_t i = 0; i < size; ++i)
		{
			literal += Consume();
		}

		loc.end = pos;

		return Token(type, std::move(literal), std::move(loc));
	};

	while (SkipWhitespace() || SkipComments())
		;

	if (Eof())
	{
		return SingleToken(Token::Type::Eof);
	}

	switch (Current())
	{
		case '0' ... '9': return Number();

		case 'a' ... 'z':
		case 'A' ... 'Z':
		case '_': return Identifier();

		case '"': return String();
		case '\'':
		{
			File::Loc loc;
			loc.start = pos;
			loc.offset = current;

			++current;
			std::string literal { Consume() };
			if (Consume() != '\'')
			{
				Error(loc.start, loc.offset, Locale::Get("LEXER_ERROR_UNTERMINATED_CHAR"));
			}

			loc.end = pos;

			return Token(Token::Type::CharLiteral, std::move(literal), std::move(loc));
		}

		case '(': return SingleToken(Token::Type::LParen);
		case ')': return SingleToken(Token::Type::RParen);
		case '[': return SingleToken(Token::Type::LBracket);
		case ']': return SingleToken(Token::Type::RBracket);
		case '{': return SingleToken(Token::Type::LCurly);
		case '}': return SingleToken(Token::Type::RCurly);
		case '.': return SingleToken(Token::Type::Dot);
		case ',': return SingleToken(Token::Type::Comma);
		case ';': return SingleToken(Token::Type::Semicolon);
		case '$': return SingleToken(Token::Type::Cast);
		case '@': return SingleToken(Token::Type::Attribute);

		case '-':
			if (Match("->"))
			{
				return MultiToken(Token::Type::Arrow, 2);
			}
			else if (Match("-="))
			{
				return MultiToken(Token::Type::MinusEqual, 2);
			}
			return SingleToken(Token::Type::Minus);

		case '=':
			if (Match("=="))
			{
				return MultiToken(Token::Type::Equal, 2);
			}
			else if (Match("=>"))
			{
				return MultiToken(Token::Type::WideArrow, 2);
			}
			return SingleToken(Token::Type::Assign);

		case ':':
			if (Match("::"))
			{
				return MultiToken(Token::Type::ColonColon, 2);
			}
			return SingleToken(Token::Type::Colon);

		case '+':
			if (Match("+="))
			{
				return MultiToken(Token::Type::PlusEqual, 2);
			}
			return SingleToken(Token::Type::Plus);

		case '*':
			if (Match("*="))
			{
				return MultiToken(Token::Type::StarEqual, 2);
			}
			return SingleToken(Token::Type::Star);

		case '/':
			if (Match("/="))
			{
				return MultiToken(Token::Type::SlashEqual, 2);
			}
			return SingleToken(Token::Type::Slash);

		case '%':
			if (Match("%="))
			{
				return MultiToken(Token::Type::ModEqual, 2);
			}
			return SingleToken(Token::Type::Mod);

		case '!':
			if (Match("!="))
			{
				return MultiToken(Token::Type::NotEqual, 2);
			}
			return SingleToken(Token::Type::Not);

		case '<':
			if (Match("<<="))
			{
				return MultiToken(Token::Type::LShiftEqual, 3);
			}
			else if (Match("<<"))
			{
				return MultiToken(Token::Type::LShift, 2);
			}
			else if (Match("<="))
			{
				return MultiToken(Token::Type::LessEqual, 2);
			}
			return SingleToken(Token::Type::Less);

		case '>':
			if (Match(">>="))
			{
				return MultiToken(Token::Type::RShiftEqual, 3);
			}
			else if (Match(">>"))
			{
				return MultiToken(Token::Type::RShift, 2);
			}
			else if (Match(">="))
			{
				return MultiToken(Token::Type::GreaterEqual, 2);
			}
			return SingleToken(Token::Type::Greater);

		case '&':
			if (Match("&&"))
			{
				return MultiToken(Token::Type::AndAnd, 2);
			}
			else if (Match("&="))
			{
				return MultiToken(Token::Type::AndEqual, 2);
			}
			return SingleToken(Token::Type::And);

		case '|':
			if (Match("||"))
			{
				return MultiToken(Token::Type::OrOr, 2);
			}
			else if (Match("|="))
			{
				return MultiToken(Token::Type::OrEqual, 2);
			}
			return SingleToken(Token::Type::Or);

		case '^':
			if (Match("^="))
			{
				return MultiToken(Token::Type::XorEqual, 2);
			}
			return SingleToken(Token::Type::Xor);

		case '~':
			if (Match("=="))
			{
				return MultiToken(Token::Type::FlipEqual, 2);
			}
			return SingleToken(Token::Type::Flip);

		default:
			Error(pos, current, Locale::Get("LEXER_ERROR_UNKNOWN_TOKEN"), Current());
			return SingleToken(Token::Type::Unknown);
	}
}

auto Lexer::Identifier() -> Token
{
	auto IsIdent = [](const char c) {
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_');
	};

	auto GetKeywordType = [&](const std::string &ident) {
		auto Match = [&](const std::string &match, const size_t offset) {
			size_t i = offset;
			for (const auto &c : match)
			{
				if (c != ident.at(i))
				{
					return false;
				}

				++i;
			}
			return true;
		};

		switch (ident.at(0))
		{
			case 'f':
				if (ident.size() <= 1)
				{
					return Token::Type::Ident;
				}

				switch (ident.at(1))
				{
					case 'a':
						if (Match("lse", 2))
						{
							return Token::Type::False;
						}
						return Token::Type::Ident;

					case 'o':
						if (Match("r", 2))
						{
							return Token::Type::For;
						}
						return Token::Type::Ident;

					case '6':
						if (Match("4", 2))
						{
							return Token::Type::Float64;
						}
						return Token::Type::Ident;

					case '3':
						if (Match("2", 2))
						{
							return Token::Type::Float32;
						}
						return Token::Type::Ident;

					case 'n': return Token::Type::Fn;

					default: return Token::Type::Ident;
				}

			case 'm':
				if (ident.size() <= 1)
				{
					return Token::Type::Ident;
				}

				switch (ident.at(1))
				{
					case 'o':
						if (Match("dule", 2))
						{
							return Token::Type::Module;
						}
						return Token::Type::Ident;

					case 'a':
						if (Match("tch", 2))
						{
							return Token::Type::Match;
						}
						return Token::Type::Ident;

					case 'u':
						if (Match("t", 2))
						{
							return Token::Type::Mut;
						}
						return Token::Type::Ident;

					default: return Token::Type::Ident;
				}

			case 'i':
				if (ident.size() <= 1)
				{
					return Token::Type::Ident;
				}

				switch (ident.at(1))
				{
					case 'm':
						if (ident.size() <= 2)
						{
							return Token::Type::Ident;
						}

						switch (ident.at(2))
						{
							case 'p':
								if (Match("ort", 2))
								{
									return Token::Type::Import;
								}
								return Token::Type::Ident;

							default: return Token::Type::Ident;
						}

					case 'f': return Token::Type::If;

					case '6':
						if (Match("4", 2))
						{
							return Token::Type::Int64;
						}
						return Token::Type::Ident;

					case '3':
						if (Match("2", 2))
						{
							return Token::Type::Int32;
						}
						return Token::Type::Ident;

					case '1':
						if (Match("6", 2))
						{
							return Token::Type::Int16;
						}
						return Token::Type::Ident;

					case '8': return Token::Type::Int8;

					default: return Token::Type::Ident;
				}

			case 'u':
				if (ident.size() <= 1)
				{
					return Token::Type::Ident;
				}

				switch (ident.at(1))
				{
					case 'l':
						if (Match("ong", 2))
						{
							return Token::Type::ULong;
						}
						return Token::Type::Ident;

					case '6':
						if (Match("4", 2))
						{
							return Token::Type::UInt64;
						}
						return Token::Type::Ident;

					case '3':
						if (Match("2", 2))
						{
							return Token::Type::UInt32;
						}
						return Token::Type::Ident;

					case '1':
						if (Match("6", 2))
						{
							return Token::Type::UInt16;
						}
						return Token::Type::Ident;

					case '8': return Token::Type::UInt8;

					default: return Token::Type::Ident;
				}

			case 'r':
				if (Match("et", 1))
				{
					return Token::Type::Ret;
				}
				return Token::Type::Ident;

			case 'l':
				if (ident.size() <= 1)
				{
					return Token::Type::Ident;
				}

				switch (ident.at(1))
				{
					case 'e':
						if (Match("t", 2))
						{
							return Token::Type::Let;
						}
						return Token::Type::Ident;

					case 'o':
						if (ident.size() <= 2)
						{
							return Token::Type::Ident;
						}

						switch (ident.at(2))
						{
							case 'n':
								if (Match("g", 3))
								{
									return Token::Type::Long;
								}
								return Token::Type::Ident;

							case 'c':
								if (Match("al", 3))
								{
									return Token::Type::Local;
								}
								return Token::Type::Ident;

							case 'o':
								if (Match("p", 3))
								{
									return Token::Type::Loop;
								}
								return Token::Type::Ident;

							default: return Token::Type::Ident;
						}

					default: return Token::Type::Ident;
				}

			case 's':
				if (Match("truct", 1))
				{
					return Token::Type::Struct;
				}
				return Token::Type::Ident;

			case 'e':
				if (ident.size() <= 1)
				{
					return Token::Type::Ident;
				}

				switch (ident.at(1))
				{
					case 'l':
						if (ident.size() <= 2)
						{
							return Token::Type::Ident;
						}

						switch (ident.at(2))
						{
							case 's':
								if (Match("e", 3))
								{
									return Token::Type::Else;
								}
								return Token::Type::Ident;

							case 'i':
								if (Match("f", 3))
								{
									return Token::Type::Elif;
								}
								return Token::Type::Ident;

							default: return Token::Type::Ident;
						}

					default: return Token::Type::Ident;
				}

			case 'b':
				if (ident.size() <= 1)
				{
					return Token::Type::Ident;
				}

				switch (ident.at(1))
				{
					case 'r':
						if (Match("eak", 1))
						{
							return Token::Type::Break;
						}
						return Token::Type::Ident;

					case 'o':
						if (Match("ol", 1))
						{
							return Token::Type::Bool;
						}
						return Token::Type::Ident;

					default: return Token::Type::Ident;
				}

			case 'c':
				if (Match("har", 1))
				{
					return Token::Type::Char;
				}
				return Token::Type::Ident;

			case 't':
				if (Match("rue", 1))
				{
					return Token::Type::True;
				}
				return Token::Type::Ident;

			default: return Token::Type::Ident;
		}
	};

	File::Loc loc;
	loc.start = pos;
	loc.offset = current;

	std::string literal;
	while (IsIdent(Current()))
	{
		literal += Consume();
	}

	loc.end = pos;

	return Token(GetKeywordType(literal), std::move(literal), std::move(loc));
}

auto Lexer::Number() -> Token
{
	auto IsNumber = [](const char c) {
		return c >= '0' && c <= '9';
	};

	File::Loc loc;
	loc.start = pos;
	loc.offset = current;

	std::string literal;
	auto type = Token::Type::Int32Literal;

	while (IsNumber(Current()))
	{
		literal += Consume();
	}

	if (Current() == '.')
	{
		literal += Consume();
		type = Token::Type::Float64Literal;
		while (IsNumber(Consume()))
		{
			literal += Consume();
		}
	}

	loc.end = pos;

	return Token(type, std::move(literal), std::move(loc));
}

auto Lexer::String() -> Token
{
	File::Loc loc;
	loc.start = pos;
	loc.offset = current;

	++current;

	std::string literal;
	while (!Eof() && Current() != '"' && Current() != '\n')
	{
		literal += Consume();
	}

	if (Current() != '"')
	{
		Error(loc.start, loc.offset, Locale::Get("LEXER_ERROR_UNTERMINATED_STRING"));
	}

	++current;

	loc.end = pos;

	return Token(Token::Type::StringLiteral, std::move(literal), std::move(loc));
}

auto Lexer::SkipWhitespace() -> bool
{
	auto IsWhitespace = [](const char &c) {
		return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
	};

	const auto prev = current;
	while (IsWhitespace(Current()))
	{
		if (Current() == '\n')
		{
			++pos.line;
			pos.column = 0;
		}
		++current;
	}

	return prev != current;
}

auto Lexer::SkipComments() -> bool
{
	if (Current() == '#')
	{
		while (Current() != '\n')
		{
			Consume();
		}

		return true;
	}

	return false;
}

auto Lexer::Current() const -> char
{
	return source[current];
}

auto Lexer::Consume() -> char
{
	++pos.column;
	return source[current++];
}

auto Lexer::Match(const std::string &match, const size_t offset) -> bool
{
	size_t i = offset;
	for (const auto &c : match)
	{
		if (c != source[current + i])
		{
			return false;
		}
		++i;
	}

	return true;
}

auto Lexer::Eof() const -> bool
{
	return current >= source.size();
}
}
