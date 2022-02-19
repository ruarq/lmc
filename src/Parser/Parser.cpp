/**
 * @author ruarq
 * @date 14.02.2022 
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

#include "Parser.hpp"

namespace Lm
{

Parser::Parser(Lexer &lexer, const Diagnostics &diagnostics)
	: lexer(lexer)
	, diagnostics(diagnostics)
{
}

auto Parser::Run() -> Ast::TranslationUnit *
{
	auto unit = new Ast::TranslationUnit();
	while ((curr = lexer.NextToken()).type != Token::Type::Eof)
	{
		unit->statements.push_back(GlobalStmt());
	}
	return unit;
}

auto Parser::GlobalStmt() -> Ast::Statement *
{
	switch (curr.type)
	{
		case Token::Type::Fn: return FunctionDecl();
		default:
			diagnostics.Error(curr.pos, Locale::Get("PARSER_ERROR_UNEXPECTED_TOKEN"));
			return nullptr;
	}
}

auto Parser::FunctionDecl() -> Ast::FunctionDecl *
{
	Consume(Token::Type::Fn, "fn");
	auto fn = new Ast::FunctionDecl();

	fn->ident = curr.symbol;
	Consume(Token::Type::Ident, "identifier");

	Consume(Token::Type::LParen, "(");
	Consume(Token::Type::RParen, ")");

	if (curr.type == Token::Type::Arrow)
	{
		Consume();
		fn->type = curr.symbol;
		Consume(Token::Type::Int32, "i32");
	}
	else
	{
		// TODO(ruarq): Global constant for this
		fn->type = Symbol("__void");
	}

	Consume(Token::Type::LCurly, "{");
	Consume(Token::Type::RCurly, "}");

	return fn;
}

auto Parser::Consume(const Token::Type type, const std::string &expected) -> void
{
	if (curr.type != type)
	{
		diagnostics.Error(curr.pos,
			fmt::format(Locale::Get("PARSER_ERROR_EXPECTED_TOKEN"), expected));
	}

	Consume();
}

auto Parser::Consume() -> void
{
	curr = lexer.NextToken();
}

}
