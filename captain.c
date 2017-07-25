/*
** Created by doom on 23/07/17.
*/

#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "captain.h"

#define JMP 0xE9

static int apply_mem_flags(void *var, size_t size, int flags)
{
    size_t page_size = getpagesize();
    void *page_base = (void *)((uintptr_t)var & ~(page_size - 1));

    return mprotect(page_base, size, flags);
}

int cap_install_hook(captain_handle_t *out, void *from, void *to)
{
    struct s_asm_jmp *jump;

    out->from = from;
    out->to = to;
    (void)memcpy(&out->backup, out->from, sizeof(out->backup));
    if (apply_mem_flags(out->from, sizeof(out->backup), PROT_READ | PROT_WRITE | PROT_EXEC))
        return -1;
    jump = out->from;
    jump->op = JMP;
    jump->rel = (intptr_t)out->to - (intptr_t)out->from - sizeof(struct s_asm_jmp);
    return apply_mem_flags(out->from, sizeof(out->backup), PROT_READ | PROT_EXEC);
}

int cap_remove_hook(captain_handle_t *h)
{
    if (apply_mem_flags(h->from, sizeof(h->backup), PROT_READ | PROT_WRITE | PROT_EXEC))
        return -1;
    (void)memcpy(h->from, &h->backup, sizeof(h->backup));
    return apply_mem_flags(h->from, sizeof(h->backup), PROT_READ | PROT_EXEC);
}
