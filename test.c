#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_first_quote(char *token) {
    int i = 0, j = 0;
    int found_quote = 0;
    char quote_char = '\0';
    int len = strlen(token);
    char *new_token = (char *)malloc((len + 1) * sizeof(char));

    if (!new_token)
        return NULL;

    while (token[i]) {
        if (!found_quote && (token[i] == '\"' || token[i] == '\'')) {
            found_quote = 1;
            quote_char = token[i];
            i++;
            continue;
        }
        if (found_quote && token[i] == quote_char) {
            i++;
			found_quote = 0;
            continue;
        }
        new_token[j++] = token[i++];
    }

    new_token[j] = '\0';
    return new_token;
}

void quote_handing(char **tokens) {
    int i = 0;
    char *temp;

    while (tokens[i]) {
        if (strchr(tokens[i], '\"') || strchr(tokens[i], '\'')) {
            temp = tokens[i];
            tokens[i] = remove_first_quote(tokens[i]);
        }
        i++;
    }
}

// int main() {
//     char *tokens[] = {"echo", NULL};
//     quote_handing(tokens);

//     for (int i = 0; tokens[i]; i++) {
//         printf("Processed token: %s\n", tokens[i]);
//         // free(tokens[i]); // Remember to free the processed tokens
//     }

//     return 0;
// }
