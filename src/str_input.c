#include "project.h"

/**
 * Reads a line of input from standard input (stdin).
 *
 * This function reads characters from stdin until a newline character (`\n`) 
 * or end-of-file (EOF) is encountered. It dynamically allocates and resizes 
 * the buffer as needed to accommodate the input. The buffer is null-terminated 
 * and its length is returned.
 *
 * @param buffer: A pointer to a char pointer that will be allocated and filled with the input.
 * 
 * @return: The length of the input string, excluding the null terminator.
 *          Returns `-1` if memory allocation fails or if there is an error reading from stdin.
 */
int read_std_input(char **buffer)
{
    int capacity = 100;
    int len = 0;
    char ch = 0;
    char *new_buffer = NULL;
    int bytes_read = 0;

    *buffer = (char *)malloc(capacity * sizeof(char));
    // Memory allocation failed
    if (!(*buffer))
        return -1;

    while ((bytes_read = read(STDIN_FILENO, &ch, sizeof(char)) > 0))
    {
        // Not enough memory in buffer
        if (len == capacity)
        {
            capacity *= 2;
            new_buffer = (char *)realloc(*buffer, capacity * sizeof(char));
            // Memory re-allocation failed
            if (!new_buffer)
            {
                free(*buffer);
                return -1;
            }
            *buffer = new_buffer;
        }
        if (ch == '\n')
            break;
        (*buffer)[len] = ch;
        len++;
    }

    // error of reading input
    if (bytes_read == -1)
    {
        free(*buffer);
        return -1;
    }

    (*buffer)[len] = '\0';

    return len;
}

/**
 * Splits a string into tokens based on spaces and returns an array of these tokens.
 *
 * This function takes a string, duplicates it, and then splits it into tokens
 * using space as a delimiter. It dynamically allocates memory for an array of
 * strings to hold the tokens. The number of tokens is returned via the `token_cnt` 
 * pointer.
 *
 * @param str        The input string to be split into tokens.
 * @param token_cnt  Pointer to an integer where the number of tokens will be stored.
 * 
 * @return           A dynamically allocated array of strings (tokens), with the last
 *                   element set to NULL. If there is an error (e.g., memory allocation
 *                   failure), the function returns NULL.
 */
char** input_str_split(const char *str, int *token_cnt)
{
    char *str_copy = strdup(str);
    if (!str_copy)
        return NULL;

    char **temp = NULL;
    char *token = strtok(str_copy, " ");
    char **res = (char **)malloc(sizeof(char *));
    if (!res)
    {
        free(str_copy);
        return NULL;
    }
    int counter = 0;

    while (token != NULL)
    {
        temp = (char **)realloc(res, (counter + 1) * sizeof(char *));
        if (!temp)
        {
            for (int i = 0; i < counter; i++)
            {
                free(res[i]);
            }
            free(res);
            free(str_copy);
            return NULL;
        }
        res = temp;
        res[counter] = strdup(token);
        if (!res[counter])
        {
            for (int i = 0; i < counter; i++)
            {
                free(res[i]);
            }
            free(res);
            free(str_copy);
            return NULL;
        }
        counter++;
        token = strtok(NULL, " ");
    }

    temp = (char **)realloc(res, (counter + 1) * sizeof(char *));
    if (!temp)
    {
        free(str_copy);
        return NULL;
    }
    res = temp;
    res[counter] = NULL;
    *token_cnt = counter;

    free(str_copy);

    return res;
}
