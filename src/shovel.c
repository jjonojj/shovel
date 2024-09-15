#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DELIMITERS " \t\n(){}\";"

typedef enum
{
    TYPE_VOID,
    TYPE_INT
} Type;
const char *types[] = {"void", "int"};

typedef enum
{
    KEYW_RET
} Keyword;
const char *keywords[] = {"return"};

typedef struct
{
    Type ret_type;
    char *body;
} Function;

typedef struct
{

} Integer;

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

int main(int argc, char **argv)
{

    // hardcode program because im too lazy to do actual work. SHOULD print hey
    char *program = 'void main() { print("hey"); }';

    return 0;
}