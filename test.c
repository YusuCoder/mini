#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *skip_dollar(char *token)
{
    int i, j;
    int len;
    char *new_token;

    if (!token)
        return NULL;

    len = strlen(token);
    new_token = (char *)malloc(len + 1);
    if (!new_token)
        return NULL;
    i = 0;
    j = 0;
    while (token[i])
    {
        if (token[i] != '$')
        {
            new_token[j] = token[i];
            j++;
        }
        i++;
    }
    new_token[j] = '\0';

    return new_token;
}

int main(void)
{
	char str[] = "$'USER'";
	char *res;
	res = skip_dollar(str);
	printf("%s\n", res);
	return (0);
}
