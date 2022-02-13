/**
 * @author ruarq
 * @date 09.02.2022 
 *
 * Copyright (C) 2022 ruarq
 * This product is licensed under the MIT license.
 */

#pragma once

#include <string>

#include "../File.hpp"

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

		Fn,			 ///< fn
		Mut,		 ///< mut
		Imut,		 ///< imut
		Ret,		 ///< ret
		Module,		 ///< module
		Import,		 ///< import
		Struct,		 ///< struct
		Local,		 ///< local
		Match,		 ///< match
		For,		 ///< for
		Loop,		 ///< loop
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
		Ident,		 ///< Identifier

		Int32Literal,	   ///< 1234567890
		Float64Literal,	   ///< 123.456
		StringLiteral,	   ///< ""
		CharLiteral,	   ///< ''

		Unknown,	///< Generated for tokens that are unknown
		Eof			///< End of file token
	};

public:
	Token(const Type type, const std::string &literal, const FileLoc &start, const FileLoc &end);

public:
	const Type type;			  ///< The type of the token
	const std::string literal;	  ///< The literal of the token
	const FileLoc start, end;	  ///< Start and end locations of the literal
};

}
