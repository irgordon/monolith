#include <os/compiler.h>

OS_EXTERN_C_BEGIN
OS_EXTERN_C_END

OS_NORETURN static void test_noreturn(void) {
    for (;;) {
    }
}

int main(void) {
    OS_UNUSED int ref = 0;
    test_noreturn();
}
