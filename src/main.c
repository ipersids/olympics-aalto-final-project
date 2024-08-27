#include "project.h"

int main(void)
{
    char *str = NULL;
    char **str_splitted = NULL;
    char *command = NULL;
    olympic_db_t *db = NULL;
    olympic_db_t *load_db = NULL;
    int len = 0;
    int token_cnt = 0;

    // Continuously reads input from the user 
    // until a quit command (Q) is received
    while (true)
    {
        token_cnt = 0;
        len = read_std_input(&str);
        // Reading input or memory allocation failed
        if (len == -1)
        {
            // Free the database if allocated
            free_db_memory(&db);
            return -1;
        }

        // Quit program command
        if (len == 1 && str[0] == 'Q')
        {
            break;
        }

        // Split str into command and arguments
        str_splitted = input_str_split(str, &token_cnt);
        if (!str_splitted)
        {
            // Free the input string and db if allocated
            free(str);
            free_db_memory(&db);
            return -1;
        }

        command = str_splitted[0];
        if (token_cnt == 2 && strcmp(command, "A") == 0)
        {
            // Add nation command, which adds a nation to the db
            if (!add_new_nation(&db, str_splitted[1]))
                printf("Invalid command %s\n", command);
            else
                printf("SUCCESS\n");
        }
        else if (token_cnt == 2 && strcmp(command, "W") == 0)
        {
            // Save to file command, which saves the db to a text file
            if (write_db_file(&db, str_splitted))
                printf("Invalid command %s\n", command);
            else
                printf("SUCCESS\n");
        }
        else if (token_cnt == 5 && strcmp(command, "M") == 0)
        {
            // Add medals command, which adds the specified medals to a nation
            if (add_medals(&db, str_splitted))
                printf("Invalid command %s\n", command);
            else
                printf("SUCCESS\n");
        }
        else if (token_cnt == 1 && strcmp(command, "L") == 0)
        {
            // Print sorted db command, which displays the db content
            if (sort_db(&db))
                printf("Invalid command %s\n", command);
            else
                print_sorted_db(&db);
        }
        else if (token_cnt == 2 && strcmp(command, "O") == 0)
        {
            // Load from file command, which loads nations from a text file
            load_db = load_db_file(str_splitted[1]);
            if (!load_db)
                printf("Invalid command %s\n", command);
            else
            {
                free_db_memory(&db);
                db = load_db;
                printf("SUCCESS\n");
            }
        }
        else
        {
            printf("Invalid command %s\n", command);
        }

        free(str);
        free_splitted_str_memory(str_splitted);
        str = NULL;
        str_splitted = NULL;
        command = NULL;
    }

    // Release all allocated memory
    free_db_memory(&db);
    free(str);

    return 0;
}
