/**
 * @author ruarq
 * @date 09.02.2022 
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

#include <cstdint>

#include "../Symbol.hpp"

namespace Lm
{

struct SourcePos final
{
	size_t line;
	size_t column;
	size_t offset;
};

/**
 * @brief stores all information about a lexical token
 */
class Token final
{
public:
	/**
	 * @brief defines the type of a token
	 */
	enum class Type : std::uint8_t
	{
		LParen,			 ///< (
		RParen,			 ///< )
		LBracket,		 ///< [
		RBracket,		 ///< ]
		LCurly,			 ///< {
		RCurly,			 ///< }
		Dot,			 ///< .
		Comma,			 ///< ,
		Arrow,			 ///< ->
		WideArrow,		 ///< =>
		Colon,			 ///< :
		ColonColon,		 ///< ::
		Semicolon,		 ///< ;
		Plus,			 ///< +
		PlusEqual,		 ///< +=
		Minus,			 ///< -
		MinusEqual,		 ///< -=
		Star,			 ///< *
		StarEqual,		 ///< *=
		Slash,			 ///< /
		SlashEqual,		 ///< /=
		Mod,			 ///< %
		ModEqual,		 ///< %=
		Assign,			 ///< =
		Equal,			 ///< ==
		Not,			 ///< !
		NotEqual,		 ///< !=
		Less,			 ///< <
		Greater,		 ///< >
		LessEqual,		 ///< <=
		GreaterEqual,	 ///< >=
		AndAnd,			 ///< &&
		OrOr,			 ///< ||
		And,			 ///< &
		AndEqual,		 ///< &=
		Or,				 ///< |
		OrEqual,		 ///< |=
		Xor,			 ///< ^
		XorEqual,		 ///< ^=
		Flip,			 ///< ~
		FlipEqual,		 ///< ~=
		LShift,			 ///< <<
		LShiftEqual,	 ///< <<=
		RShift,			 ///< >>
		RShiftEqual,	 ///< >>=
		Cast,			 ///< $
		Attribute,		 ///< @

		Fn,			 ///< fn
		Int8,		 ///< i8
		If,			 ///< if
		UInt8,		 ///< u8
		Float32,	 ///< f32
		Float64,	 ///< f64
		For,		 ///< for
		Int16,		 ///< i16
		Int32,		 ///< i32
		Int64,		 ///< i64
		Let,		 ///< let
		Mut,		 ///< mut
		Ret,		 ///< ret
		UInt16,		 ///< u16
		UInt32,		 ///< u32
		UInt64,		 ///< u64
		Bool,		 ///< bool
		Char,		 ///< char
		Elif,		 ///< elif
		Else,		 ///< else
		Long,		 ///< long
		Loop,		 ///< loop
		True,		 ///< true
		Break,		 ///< break
		False,		 ///< false
		Local,		 ///< local
		Match,		 ///< match
		ULong,		 ///< ulong
		Import,		 ///< import
		Module,		 ///< module
		Struct,		 ///< struct
		Continue,	 ///< continue
		Ident,		 ///< Identifier

		Int32Literal,	   ///< 1234567890
		Float64Literal,	   ///< 123.456
		StringLiteral,	   ///< ""
		CharLiteral,	   ///< ''

		Unknown,	///< Default token type value
		Eof			///< End of file token
	};

public:
	Token();
	Token(const Type type);
	Token(const Type type, const Symbol symbol);

public:
	Type type;		  ///< The type of the token
	Symbol symbol;	  ///< The tokens symbol
	SourcePos pos;	  ///< The source of the token (just positional data)
};

auto GetKeywordType(const std::string &str) -> Token::Type;

}
