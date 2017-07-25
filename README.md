This is a tiny proof of concept about function hooking under x86 and Unix.

See `main.c` for a basic code example.

A word on how it works.
 Let's consider two functions `from` and `to`, for which we wanna redirect all the calls to the first to the second one.

What we are going to do is to replace the first bytes of `from` with an instruction jumping to `to`.
This instruction is basically the raw bytes for a `jmp` (whose parameter is a relative offset to add to the current instruction pointer).
The parameter is the distance between `to` and `from`, minus the size of the jump instruction (because the current address at the time of the jump is `from + size_of_the_instruction`)

Before actually writing that instruction, we backup the bytecode that it will overwrite.
Then we write the instruction and disable writing to the memory area.

To remove a hook, we only need to copy the backed-up bytes back to their original location in `from`.