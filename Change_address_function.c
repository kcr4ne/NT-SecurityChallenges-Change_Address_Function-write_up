#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void hidden_shell() {
    system("/bin/sh");
}

void dummy_func() {
    printf("Dummy function. Nothing to see here!\n");
}

void vulnerable() {
    char buf[64];
    void (*func_ptr) () = dummy_func;

    printf("Input: ");
    fflush(stdout);

    fgets(buf, 128, stdin);

    if (strcmp(buf, "nope\n") == 0) {
    printf("Nice try!\n");
    }

    printf("Calling function pointer ... \n");
    func_ptr();
}

int main() {
    setbuf(stdout, NULL);
    vulnerable();
    return 0;
}