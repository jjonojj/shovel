#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define delimiters
#define DELIMITERS " \t\n(){};"

enum Type {
    T_INT,    
};

void tokenize(const char *input, char ***tokens, int *num_tokens) {
    // Initial buffer size
    size_t buffer_size = 10;
    size_t token_count = 0;

    // Allocate initial memory for tokens
    *tokens = (char **)malloc(buffer_size * sizeof(char *));
    if (*tokens == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    const char *start = input;
    const char *end = NULL;

    while (*start) {
        // Skip whitespace
        while (isspace((unsigned char)*start)) {
            start++;
        }

        if (*start == '\0') break;

        // Check if character is a delimiter
        if (strchr(DELIMITERS, *start)) {
            // Handle single-character delimiters
            end = start + 1;
            size_t length = 1;
            char *token = (char *)malloc(length + 1);
            if (token == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            strncpy(token, start, length);
            token[length] = '\0';

            // Add token to array
            if (token_count >= buffer_size) {
                buffer_size *= 2;
                *tokens = (char **)realloc(*tokens, buffer_size * sizeof(char *));
                if (*tokens == NULL) {
                    perror("Failed to reallocate memory");
                    exit(EXIT_FAILURE);
                }
            }
            (*tokens)[token_count++] = token;

            start = end;
        } else {
            // Handle non-delimiter tokens
            end = strpbrk(start, DELIMITERS);
            if (end == NULL) end = start + strlen(start);

            size_t length = end - start;
            char *token = (char *)malloc(length + 1);
            if (token == NULL) {
                perror("Failed to allocate memory");
                exit(EXIT_FAILURE);
            }
            strncpy(token, start, length);
            token[length] = '\0';

            // Add token to array
            if (token_count >= buffer_size) {
                buffer_size *= 2;
                *tokens = (char **)realloc(*tokens, buffer_size * sizeof(char *));
                if (*tokens == NULL) {
                    perror("Failed to reallocate memory");
                    exit(EXIT_FAILURE);
                }
            }
            (*tokens)[token_count++] = token;

            start = end;
        }
    }


    // Null-terminate the tokens array
    *tokens = (char **)realloc(*tokens, (token_count + 1) * sizeof(char *));
    (*tokens)[token_count] = NULL;
    *num_tokens = token_count;
}

void interpret() {

}

int main() {
    const char *code = "void main () { return 0; }";
    char **tokens = NULL;
    int num_tokens = 0;

    tokenize(code, &tokens, &num_tokens);

    for (int i = 0; i < num_tokens; i++) {
        printf("[%s]\n", tokens[i]);
        free(tokens[i]); // Free each token
    }

    free(tokens); // Free the array of tokens

    return 0;
}
