#include "project.h"

/**
 * Writes the contents of the database to a file.
 *
 * This function traverses the linked list representing the database and writes the
 * information of each node to a file specified by `arg[1]`. Each line in the file
 * represents a nation's record, including its name and medal counts. The file is
 * opened in write mode, which overwrites the file if it already exists or creates a
 * new file if it does not.
 *
 * @param db  Pointer to a pointer to the head of the linked list representing the database.
 * @param arg Array of strings containing the command arguments:
 *            - arg[1]: Path to the file where the database should be written.
 * @return 0 if the file was successfully written, -1 if there was an error (e.g., file could
 *         not be opened).
 */
int write_db_file(olympic_db_t **db, char **arg)
{
    olympic_db_t *current = *db;
    FILE *fd = NULL;

    if (!db || !*db)
        return -1;

    // Open (or create) the file in append mode
    fd = fopen(arg[1], "w");
    if (!fd)
        return -1;

    // Append information from db to the file
    while (current)
    {
        fprintf(fd, "%s %d %d %d\n",
                    current->name,
                    current->gold,
                    current->silver,
                    current->bronze);
        current = current->next;
    }

    // Close the file
    fclose(fd);

    return 0;
}

/**
 * Loads a database from a file.
 *
 * This function reads a file specified by the `path` parameter and parses its contents to
 * build a linked list of `olympic_db_t` structures. Each line in the file should represent
 * a nation with its medal counts, and the function assumes that each line contains the
 * following format: "nation_name gold silver bronze".
 *
 * The function allocates memory for the database and parses each line into a new node in
 * the linked list. If any error occurs (e.g., file not found, memory allocation failure,
 * invalid data format), the function cleans up any partially allocated memory and returns
 * `NULL` to indicate failure. If successful, it returns a pointer to the head of the linked
 * list representing the database.
 *
 * @param path The path to the file to be read.
 * @return A pointer to the head of the linked list representing the database, or `NULL`
 *         if an error occurs.
 */
olympic_db_t *load_db_file(char *path)
{
    olympic_db_t *db = NULL;
    olympic_db_t *current = NULL;
    FILE *fd = NULL;
    int ch = 0;
    int i = 0;
    int token_cnt = 0;
    char *buffer = NULL;
    char **arg = NULL;
    int buff_size = 1000;

    fd = fopen(path, "r");
    if (!fd)
        return NULL;
    buffer = (char *)malloc(buff_size * sizeof(char));
    if (!buffer)
    {
        fclose(fd);
        return NULL;
    }

    // Read the file character by character
    while ((ch = fgetc(fd)) != EOF)
    {
        if (ch == '\n')
        {
            buffer[i] = '\0';
            i = 0;
            // Split the line into tokens
            arg = input_str_split(buffer, &token_cnt);
            if (!arg)
            {
                fclose(fd);
                free(buffer);
                return NULL;
            }
            // Validate the token count and medal values
            if (token_cnt != 4 || medal_val_is_numeric(arg[1], arg[2], arg[3]) == -1)
            {
                fclose(fd);
                free(buffer);
                free_splitted_str_memory(arg);
                return NULL;
            }
            // Add a new nation node to the database
            current = add_new_nation(&db, arg[0]);
            if (!current)
            {
                fclose(fd);
                free(buffer);
                free_splitted_str_memory(arg);
                free_db_memory(&db);
                return NULL;
            }
            // Set the medal values for the current node
            current->gold = atoi(arg[1]);
            current->silver = atoi(arg[2]);
            current->bronze = atoi(arg[3]);
            free_splitted_str_memory(arg);
        }
        else
        {
            buffer[i] = ch;
            i++;
        }
    }

    // Check for errors during file reading
    if (ferror(fd))
    {
        free(buffer);
        fclose(fd);
        return NULL;
    }

    // Clean up and close the file
    fclose(fd);
    free(buffer);

    return db;
}
