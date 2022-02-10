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
		Quote,			 ///< '
		DoubleQuote,	 ///< "

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
	};

public:
	Token(const Type type, const std::string &literal);

public:
	Type type;				///< the type of the token
	std::string literal;	///< the literal of the token
};

}
