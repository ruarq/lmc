/**
 * @author ruarq
 * @date 09.02.2022 
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

#pragma once

#include <string>

namespace Lm
{

/**
 * @brief stores all information about a lexical token
 */
class Token final
{
public:
	/**
	 * @brief defines the type of a token
	 */
	enum class Type
	{
		LParen,			 ///< (
		RParen,			 ///< )
		LCurly,			 ///< {
		RCurly,			 ///< }
		LBracket,		 ///< [
		RBracket,		 ///< ]
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
		Dollar,			 ///< $

		Fn,			 ///< fn
		Mut,		 ///< mut
		Imut,		 ///< imut
		Ret,		 ///< ret
		Module,		 ///< module
		Import,		 ///< import
		Struct,		 ///< struct
		Local,		 ///< local
		Match,		 ///< match
		If,			 ///< if
		Elif,		 ///< elif
		Else,		 ///< else
		Break,		 ///< break
		Continue,	 ///< continue
		Int8,		 ///< i8
		UInt8,		 ///< u8
		Int16,		 ///< i16
		UInt16,		 ///< u16
		Int32,		 ///< i32
		UInt32,		 ///< u32
		Int64,		 ///< i64
		UInt64,		 ///< u64
		Float32,	 ///< f32
		Float64,	 ///< f64
		Long,		 ///< long
		ULong,		 ///< ulong
		Char,		 ///< char
		Bool,		 ///< bool
		True,		 ///< true
		False,		 ///< false

		Int32Literal,	   ///< 1234567890
		Float64Literal,	   ///< 123.456
		StringLiteral,	   ///< ""
		CharLiteral		   ///< ''
	};

public:
	Token(const Type type, const std::string &literal);

public:
	const Type type;			  ///< the type of the token
	const std::string literal;	  ///< the literal of the token
};

}
