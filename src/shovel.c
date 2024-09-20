#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int next(const char* code, char* to) {

    int index = 0;
    static const char* proc = NULL;
    if (proc == NULL) proc = code;

    char* buf = (char*)malloc(1);
    *buf = '\0';  

    while (*proc != '\0' && *proc != ' ') {
        buf = realloc(buf, index + 2);
        buf[index] = *proc;
        buf[index + 1] = '\0';

        index++;
        proc++;
    }

    int strln = strlen(buf) + 1;

    memcpy(to, buf, strln);

    free(buf);

    while (*proc == ' ') {
        proc++;
    }

    if (*proc == '\0' && strln == 1) {
        return 1;
    }
    return 0;
}


int eval(const char* code) {
    char cur[512];

    while (!next(code, cur)) {
        printf("%s\n", cur);
    } 
}

int main(int argc, char** argv) {
    const char* code = "one";
    eval(code);
}
