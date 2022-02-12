/**
 * @author ruarq
 * @date 12.02.2022 
 *
 * lmc is the official compiler for the Lumin programming language.
 * Copyright (C) 2022 ruarq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "Lexer.hpp"

namespace Lm
{

auto Lexer::Run(const File &file) -> std::vector<Token>
{
	this->file = &file;
	pos = { 0, 0 };
	current = 0;

	std::vector<Token> tokens;

	while (!Eof())
	{
		tokens.push_back(NextToken());
	}

	return tokens;
}

auto Lexer::NextToken() -> Token
{
	auto SingleToken = [&](const Token::Type type) {
		return Token(type, { Consume() }, pos, { pos.line, pos.column + 1 });
	};

	auto MultiToken = [&](const Token::Type type, const size_t size) {
		const auto start = current;
		current += size;
		return Token(type, std::string(file->content, start, size), pos, { pos.line, pos.column + 1 });
	};

	SkipWhitespace();

	const auto currentChar = Current();
	switch (currentChar)
	{
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
			if (Match("~="))
			{
				return MultiToken(Token::Type::FlipEqual, 2);
			}
			return SingleToken(Token::Type::Flip);

		default: return SingleToken(Token::Type::Unknown);
	}
}

auto Lexer::SkipWhitespace() -> void
{
	auto IsWhitespace = [](const char &c) {
		return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
	};

	while (IsWhitespace(Current()))
	{
		Consume();
	}
}

auto Lexer::Current() const -> char
{
	if (!Eof())
	{
		return file->content.at(current);
	}
	else
	{
		return '\0';
	}
}

auto Lexer::Consume() -> char
{
	if (!Eof())
	{
		const auto currentChar = file->content.at(current++);
		++pos.column;

		if (currentChar == '\n')
		{
			++pos.line;
			pos.column = 0;
		}

		return currentChar;
	}
	else
	{
		return '\0';
	}
}

auto Lexer::Match(const std::string &match) -> bool
{
	size_t i = 0;
	for (const auto &c : match)
	{
		if (c != file->content.at(i + current))
		{
			return false;
		}
		++i;
	}

	return true;
}

auto Lexer::Eof() const -> bool
{
	return current >= file->content.size();
}

}
