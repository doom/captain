/*
** Created by doom on 23/07/17.
*/

#include <unistd.h>
#include <stdio.h>
#include "captain.h"

static void test_func(const char *str, size_t len)
{
    write(STDOUT_FILENO, "test_func says:\n", 16);
    write(STDOUT_FILENO, str, len);
}

static captain_handle_t h;

static void hook_func(const char *str, size_t len)
{
    cap_remove_hook(&h);
    write(STDOUT_FILENO, "not_", 4);
    test_func(str + 4, len - 4);
    cap_install_hook(&h, &test_func, &hook_func);
}

int main(void)
{
    test_func("Before\n", 7);

    cap_install_hook(&h, &test_func, &hook_func);
    test_func("Not Inside the hook\n", 20);
    cap_remove_hook(&h);

    test_func("After\n", 6);
    return 0;
}
