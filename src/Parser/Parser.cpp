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
	auto fn = Alloc<Ast::FunctionDecl>();

	Consume(Token::Type::Fn, "fn");

	fn->ident = Ident();

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

	fn->statements = StmtBlock();

	return fn;
}

auto Parser::StmtBlock() -> Ast::StmtBlock *
{
	auto stmtBlock = Alloc<Ast::StmtBlock>();
	stmtBlock->pos = curr.pos;

	Consume(Token::Type::LCurly, "{");

	while (!Eof() && curr.type != Token::Type::RCurly)
	{
		stmtBlock->statements.push_back(Statement());
	}

	Consume(Token::Type::RCurly, "}");

	return stmtBlock;
}

auto Parser::Statement() -> Ast::Statement *
{
	switch (curr.type)
	{
		case Token::Type::Ret: return ReturnStmt();
		default:
			diagnostics.Error(curr.pos, Locale::Get("PARSER_ERROR_UNEXPECTED_TOKEN"));
			return nullptr;
	}
}

auto Parser::ReturnStmt() -> Ast::ReturnStmt *
{
	auto returnStmt = Alloc<Ast::ReturnStmt>();
	Consume(Token::Type::Ret, "ret");
	returnStmt->expr = Expression();
	Consume(Token::Type::Semicolon, ";");
	return returnStmt;
}

auto Parser::Expression() -> Ast::Expression *
{
	switch (curr.type)
	{
		case Token::Type::Int32Literal:
		{
			auto int32Expr = Alloc<Ast::Int32Expr>();
			const auto tok = Consume(Token::Type::Int32Literal, "i32 literal");
			if (tok.symbol)
			{
				int32Expr->value = std::stoi(tok.symbol.String());
			}
			return int32Expr;
		}

		default:
			diagnostics.Error(curr.pos, Locale::Get("PARSER_ERROR_UNEXPECTED_TOKEN"));
			return nullptr;
	}
}

auto Parser::Ident() -> Ast::Identifier
{
	Ast::Identifier ident;
	ident.pos = curr.pos;
	const auto tok = Consume(Token::Type::Ident, "identifier");
	ident.symbol = tok.symbol;
	return ident;
}

auto Parser::Consume(const Token::Type type, const std::string &expected) -> Token
{
	if (curr.type != type)
	{
		diagnostics.Error(curr.pos,
			fmt::format(Locale::Get("PARSER_ERROR_EXPECTED_TOKEN"), expected));
	}

	return Consume();
}

auto Parser::Consume() -> Token
{
	const auto ret = curr;
	curr = lexer.NextToken();
	return ret;
}

auto Parser::Eof() const -> bool
{
	return curr.type == Token::Type::Eof;
}

}
