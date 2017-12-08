This is a tiny proof of concept about function hooking under x86 and Unix.

See `main.c` for a basic code example.

### A word on how it works
Let's say we have two functions `original_func` and `new_func`, and we want to redirect all the calls to the former to the latter.

In order to do that, we modify the beginning of the code of `original_func` to insert an instruction jumping to `new_func`.
This instruction will be a `jmp`, whose parameter is the distance between `original_func` and `new_func`, minus the size of the jump instruction (because the current address at the time of the jump is `original_func + size_of_the_jmp_instruction`)

Before actually writing that instruction, we also backup the bytes it will overwrite, so we can restore them if needed.
That way, we can easily remove a hook by copying the backed-up bytes back to their original location in `original_func`.
