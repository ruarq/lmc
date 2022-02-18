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

Token::Token()
	: type(Token::Type::Eof)
{
}

Token::Token(const Type type)
	: type(type)
{
}

Token::Token(const Type type, const Symbol symbol)
	: type(type)
	, symbol(symbol)
{
}

auto GetKeywordType(const std::string &str) -> Token::Type
{
	switch (str.size())
	{
		case 2:
			switch (str[0])
			{
				case 'f': return str[1] == 'n' ? Token::Type::Fn : Token::Type::Ident;
				case 'i':
					switch (str[1])
					{
						case '8': return Token::Type::Int8;
						case 'f': return Token::Type::If;
						default: return Token::Type::Ident;
					}

				case 'u': return str[1] == '8' ? Token::Type::UInt8 : Token::Type::Ident;

				default: return Token::Type::Ident;
			}

		case 3:
			switch (str[0])
			{
				case 'f':
					switch (str[1])
					{
						case '3':
							if (str[2] == '2')
							{
								return Token::Type::Float32;
							}
							return Token::Type::Ident;

						case '6':
							if (str[2] == '4')
							{
								return Token::Type::Float64;
							}
							return Token::Type::Ident;

						case 'o':
							if (str[2] == 'r')
							{
								return Token::Type::For;
							}
							return Token::Type::Ident;

						default: return Token::Type::Ident;
					}

				case 'i':
					switch (str[1])
					{
						case '1':
							if (str[2] == '6')
							{
								return Token::Type::Int16;
							}
							return Token::Type::Ident;

						case '3':
							if (str[2] == '2')
							{
								return Token::Type::Int32;
							}
							return Token::Type::Ident;

						case '6':
							if (str[2] == '4')
							{
								return Token::Type::Int64;
							}
							return Token::Type::Ident;

						default: return Token::Type::Ident;
					}

				case 'l':
					if (str[1] == 'e' && str[2] == 't')
					{
						return Token::Type::Let;
					}
					return Token::Type::Ident;

				case 'm':
					if (str[1] == 'u' && str[2] == 't')
					{
						return Token::Type::Mut;
					}
					return Token::Type::Ident;

				case 'r':
					if (str[1] == 'e' && str[2] == 't')
					{
						return Token::Type::Ret;
					}
					return Token::Type::Ident;

				case 'u':
					switch (str[1])
					{
						case '1':
							if (str[2] == '6')
							{
								return Token::Type::UInt16;
							}
							return Token::Type::Ident;

						case '3':
							if (str[2] == '2')
							{
								return Token::Type::UInt32;
							}
							return Token::Type::Ident;

						case '6':
							if (str[2] == '4')
							{
								return Token::Type::UInt64;
							}
							return Token::Type::Ident;

						default: return Token::Type::Ident;
					}

				default: return Token::Type::Ident;
			}

		case 4:
			switch (str[0])
			{
				case 'b':
					if (str[1] == 'o' && str[2] == 'o' && str[3] == 'l')
					{
						return Token::Type::Bool;
					}
					return Token::Type::Ident;

				case 'c':
					if (str[1] == 'h' && str[2] == 'a' && str[3] == 'r')
					{
						return Token::Type::Char;
					}
					return Token::Type::Ident;

				case 'e':
					if (str[1] == 'l')
					{
						switch (str[2])
						{
							case 'i':
								if (str[3] == 'f')
								{
									return Token::Type::Elif;
								}
								return Token::Type::Ident;

							case 's':
								if (str[3] == 'e')
								{
									return Token::Type::Else;
								}
								return Token::Type::Ident;

							default: return Token::Type::Ident;
						}
					}
					return Token::Type::Ident;

				case 'l':
					switch (str[1])
					{
						case 'o':
							switch (str[2])
							{
								case 'o':
									if (str[3] == 'p')
									{
										return Token::Type::Loop;
									}
									return Token::Type::Ident;

								case 'n':
									if (str[3] == 'g')
									{
										return Token::Type::Long;
									}
									return Token::Type::Ident;

								default: return Token::Type::Ident;
							}

						default: return Token::Type::Ident;
					}

				case 't':
					if (str[1] == 'r' && str[2] == 'u' && str[3] == 'e')
					{
						return Token::Type::True;
					}
					return Token::Type::Ident;

				default: return Token::Type::Ident;
			}

		case 5:
			switch (str[0])
			{
				case 'b':
					if (str[1] == 'r' && str[2] == 'e' && str[3] == 'a' && str[4] == 'k')
					{
						return Token::Type::Break;
					}
					return Token::Type::Ident;

				case 'f':
					if (str[1] == 'a' && str[2] == 'l' && str[3] == 's' && str[4] == 'e')
					{
						return Token::Type::False;
					}
					return Token::Type::Ident;

				case 'l':
					if (str[1] == 'o' && str[2] == 'c' && str[3] == 'a' && str[4] == 'l')
					{
						return Token::Type::Local;
					}
					return Token::Type::Ident;

				case 'm':
					if (str[1] == 'a' && str[2] == 't' && str[3] == 'c' && str[4] == 'h')
					{
						return Token::Type::Match;
					}
					return Token::Type::Ident;

				case 'u':
					if (str[1] == 'l' && str[2] == 'o' && str[3] == 'n' && str[4] == 'g')
					{
						return Token::Type::ULong;
					}
					return Token::Type::Ident;

				default: return Token::Type::Ident;
			}

		case 6:
			switch (str[1])
			{
				case 'i':
					if (str[1] == 'm' && str[2] == 'p' && str[3] == 'o' && str[4] == 'r' &&
						str[5] == 't')
					{
						return Token::Type::Import;
					}
					return Token::Type::Ident;

				case 'm':
					if (str[1] == 'o' && str[2] == 'd' && str[3] == 'u' && str[4] == 'l' &&
						str[5] == 'e')
					{
						return Token::Type::Module;
					}
					return Token::Type::Ident;

				case 's':
					if (str[1] == 't' && str[2] == 'r' && str[3] == 'u' && str[4] == 'c' &&
						str[5] == 't')
					{
						return Token::Type::Struct;
					}
					return Token::Type::Ident;

				default: return Token::Type::Ident;
			}

		case 8:
			if (str == "continue")
			{
				return Token::Type::Continue;
			}
			return Token::Type::Ident;

		default: return Token::Type::Ident;
	}
}

}
