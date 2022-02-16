/**
 * @author ruarq
 * @date 11.02.2022 
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

#include "Token.hpp"

namespace Lm
{

Token::Token(const Type type)
	: type(type)
{
}

Token::Token(const Type type, const Symbol symbol)
	: type(type)
	, symbol(symbol)
{
}

const std::unordered_map<std::string, Token::Type> stringToTokenType = {
	// clang-format off
	{ "fn",			Token::Type::Fn			},
	{ "mut",		Token::Type::Mut		},
	{ "let",		Token::Type::Let		},
	{ "ret",		Token::Type::Ret		},
	{ "module",		Token::Type::Module		},
	{ "import",		Token::Type::Import		},
	{ "struct",		Token::Type::Struct		},
	{ "local",		Token::Type::Local		},
	{ "match",		Token::Type::Match		},
	{ "for",		Token::Type::For		},
	{ "loop",		Token::Type::Loop		},
	{ "if",			Token::Type::If			},
	{ "elif",		Token::Type::Elif		},
	{ "else",		Token::Type::Else		},
	{ "break",		Token::Type::Break		},
	{ "continue",	Token::Type::Continue	},
	{ "i8",			Token::Type::Int8		},
	{ "u8",			Token::Type::UInt8		},
	{ "i16",		Token::Type::Int16		},
	{ "u16",		Token::Type::UInt16		},
	{ "i32",		Token::Type::Int32		},
	{ "u32",		Token::Type::UInt32		},
	{ "i64",		Token::Type::Int64		},
	{ "u64",		Token::Type::UInt64		},
	{ "f32",		Token::Type::Float32	},
	{ "f64",		Token::Type::Float64	},
	{ "long",		Token::Type::Long		},
	{ "ulong",		Token::Type::ULong		},
	{ "char",		Token::Type::Char		},
	{ "bool",		Token::Type::Bool		},
	{ "true",		Token::Type::True		},
	{ "false",		Token::Type::False		}
	// clang-format on
};
}
