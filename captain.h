/*
** Created by doom on 23/07/17.
*/

#ifndef CAPTAIN_H_
# define CAPTAIN_H_

/**
 * Tiny PoC for x86 function hooking
 *
 * A word on how it works, for two functions "from" and "to":
 * - Enable writing to the memory area of the hooked function "from"
 * - Backup its first instruction
 * - Replace it with an instruction jumping to the new function "to"
 *   - This instruction is basically a jmp, whose parameter is a relative offset
 *   - The parameter is the distance between "to" and "from", minus the size of
 *     the jump instruction (because the current address at the time of the jump
 *     is "from" + size_of_the_instruction)
 *
 * To remove a hook, we just need to copy the backed-up bytes to their original
 * location in "from".
 */


# include <stdint.h>

struct __attribute__((packed)) s_asm_jmp
{
    uint8_t op;
    int32_t rel;
};

typedef struct captain_handle_s
{
    void *from;
    void *to;
    struct s_asm_jmp backup;
} captain_handle_t;

int cap_install_hook(captain_handle_t *out, void *from, void *to);
int cap_remove_hook(captain_handle_t *h);

#endif /* CAPTAIN_H_ */
