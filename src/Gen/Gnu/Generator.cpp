/**
 * @author ruarq
 * @date 19.02.2022 
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

#include "Generator.hpp"

namespace Lm::Gen::Gnu
{

auto Compile(const std::vector<Ir::Instruction> &instructions) -> void
{
	// preamble
	fmt::print(
		"\t.globl _start\n_start:\n\tcall main\n\tmov %rax, %rdi\n\tmov $60, %rax\n\tsyscall\n");

	for (auto &instr : instructions)
	{
		switch (instr.tag)
		{
			case Ir::Instruction::Tag::Label: fmt::print("{}:\n", instr.as.label.String()); break;
			case Ir::Instruction::Tag::Return: fmt::print("\tret\n"); break;

			case Ir::Instruction::Tag::Op:
			{
				switch (instr.as.op.type)
				{
					case Ir::Operation::Type::Move: fmt::print("\tmov $0, %rax\n"); break;
				}
			}
		}
	}
}

}
