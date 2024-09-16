#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DELIMITERS " \t\n(){}\";"
#define VARIABLE_BUFFER_SIZE 256
#define FUNCTION_BUFFER_SIZE 256

typedef enum
{
    TYPE_UNDEF = -1,

    TYPE_VOID,
    TYPE_INT,

    TYPE_SIZE
} Type;
const char *types[] = {"void", "int"};

typedef enum
{
    KEYW_UNDEF = -1,

    KEYW_RET,

    KEYW_SIZE
} Keyword;
const char *keywords[] = {"return"};

typedef struct
{
    int ptr;
    char* name;
    Type ret_type;
    char *body;
} Function;

typedef struct
{
    const char *name;
    int value;
} Integer;

Type map_type(const char* query) {
    for (int i = 0; i < TYPE_SIZE; i++) {
        if (strcmp(query, types[i]) == 0) return i;
    }

    return -1;
}

Keyword map_keyw(const char* query) {
    for (int i = 0; i < KEYW_SIZE; i++) {
        if (strcmp(query, keywords[i]) == 0) return i;
    }

    return -1;
}

int fn_search(const char* query, const Function* functions, int len) {
    for (int i = 0; i < len; i++) {
        if (strcmp(query, functions[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

void tokenize(const char *input, char ***tokens, int *num_tokens)
{
    size_t buffer_size = 10;
    size_t token_count = 0;

    *tokens = (char **)malloc(buffer_size * sizeof(char *));
    if (*tokens == NULL)
    {
        perror("Failed to allocate memory");
        exit(1);
    }

    const char *start = input;
    const char *end = NULL;
    while (*start)
    {
        while (isspace((unsigned char)*start))
        {
            start++;
        }

        if (*start == '\0')
            break;

        if (strchr(DELIMITERS, *start))
        {

            end = start + 1;
            size_t length = 1;
            char *token = (char *)malloc(length + 1);
            if (token == NULL)
            {
                perror("Failed to allocate memory");
                exit(1);
            }
            strncpy(token, start, length);
            token[length] = '\0';

            if (token_count >= buffer_size)
            {
                buffer_size *= 2;
                *tokens = (char **)realloc(*tokens, buffer_size * sizeof(char *));
                if (*tokens == NULL)
                {
                    perror("Failed to reallocate memory");
                    exit(1);
                }
            }
            (*tokens)[token_count++] = token;

            start = end;
        }
        else
        {

            end = strpbrk(start, DELIMITERS);
            if (end == NULL)
                end = start + strlen(start);

            size_t length = end - start;
            char *token = (char *)malloc(length + 1);
            if (token == NULL)
            {
                perror("Failed to allocate memory");
                exit(1);
            }
            strncpy(token, start, length);
            token[length] = '\0';

            if (token_count >= buffer_size)
            {
                buffer_size *= 2;
                *tokens = (char **)realloc(*tokens, buffer_size * sizeof(char *));
                if (*tokens == NULL)
                {
                    perror("Failed to reallocate memory");
                    exit(1);
                }
            }
            (*tokens)[token_count++] = token;

            start = end;
        }
    }

    *tokens = (char **)realloc(*tokens, (token_count + 1) * sizeof(char *));
    (*tokens)[token_count] = NULL;
    *num_tokens = token_count;
}

void interpret(const char **program, int prog_length)
{
    int initial_ptr = 0;

    Integer ints[VARIABLE_BUFFER_SIZE];
    int var_int_ptr = 0;

    Function funcs[FUNCTION_BUFFER_SIZE];
    int func_int_ptr = 0;

    for (int i = 0; i < prog_length; i++) {
        const char* cur = program[i];
        // assuming first word is type
        Type cur_type = map_type(cur);
        if (cur_type == TYPE_UNDEF) {
            // assuming first word is function call

            if (fn_search(cur, funcs, func_int_ptr) == 0) {
                // function found, exec it
            }

            // yea i have no idea
            perror("unexpected token");
            exit(1);
        }

        // assuming following structure:
        // type - name - parentheses if function, semicolon or [equal and value] if variable; 
        // so we check if program[i+3] is a opening parenthesis, if yes its a function if its semicolon or equal its a variable, and else we perror and exit w 1

        if (strcmp(program[i+2], "(") == 0)
        {
            // function I GUESS

        } else if (strcmp(program[i+2], "=") == 0)
        {
            // variable, but defined at declaration
            switch (cur_type) {
                case TYPE_INT:
                    {
                        Integer var = {program[i+1], atoi(program[i+4])};
                        // push variable into ints[]

                        if (!(var_int_ptr < VARIABLE_BUFFER_SIZE)) {
                            perror("variable buffer overflow");
                            exit(1);
                        }

                        ints[var_int_ptr] = var;
                        var_int_ptr++;
                    }
                default:
                    perror("unexpected variable type.");
                    exit(1);
            }


        } else if (strcmp(program[i+2], ";") == 0)
        {
            // variable, but NOT defined at declaration
            switch (cur_type) {
                case TYPE_INT:
                    {
                        Integer var = {program[i+1], 0};
                        // push variable into ints[]

                        if (!(var_int_ptr < VARIABLE_BUFFER_SIZE)) {
                            perror("variable buffer overflow");
                            exit(1);
                        }

                        ints[var_int_ptr] = var;
                        var_int_ptr++;
                    }
                default:
                    perror("unexpected variable type.");
                    exit(1);
            }
        }
    }
}

int main(int argc, char **argv)
{
    // hardcode program because im too lazy to do actual work. SHOULD print hey
    char *code = "void main() { print(\"hey\"); }";

    char **tokens = NULL;
    int num_tokens = 0;

    tokenize(code, &tokens, &num_tokens);

    for (int i = 0; i < num_tokens; i++)
    {
        printf("[%s]\n", tokens[i]);
    }

    printf("---\n");

    //interpret(tokens, num_tokens);

    return 0;
}
