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

#pragma once

#include <vector>

#include "../Diagnostics.hpp"
#include "../Lexer/Lexer.hpp"
#include "../Lexer/Token.hpp"
#include "Ast/Expression.hpp"
#include "Ast/FunctionDecl.hpp"
#include "Ast/Identifier.hpp"
#include "Ast/Int32Expr.hpp"
#include "Ast/Node.hpp"
#include "Ast/ReturnStmt.hpp"
#include "Ast/StmtBlock.hpp"
#include "Ast/TranslationUnit.hpp"

namespace Lm
{

class Parser final
{
public:
	Parser(Lexer &lexer, const Diagnostics &diagnostics);

public:
	auto Run() -> Ast::TranslationUnit *;

private:
	auto GlobalStmt() -> Ast::Statement *;
	auto FunctionDecl() -> Ast::FunctionDecl *;
	auto StmtBlock() -> Ast::StmtBlock *;
	auto Statement() -> Ast::Statement *;
	auto ReturnStmt() -> Ast::ReturnStmt *;

	auto Expression() -> Ast::Expression *;

	inline auto Ident() -> Ast::Identifier;

	/**
	 * @brief Consume a specific token type
	 */
	auto Consume(const Token::Type type, const std::string &expected) -> Token;

	/**
	 * @brief Consume any token
	 */
	inline auto Consume() -> Token;

	inline auto Eof() const -> bool;

	template<typename T>
	inline auto Alloc() -> T *
	{
		auto node = new T();
		node->pos = curr.pos;
		return node;
	}

private:
	Lexer &lexer;
	const Diagnostics &diagnostics;
	Token curr;
};

}
