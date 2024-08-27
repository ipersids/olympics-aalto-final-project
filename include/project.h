#ifndef _PROJECT__H_
#define _PROJECT__H_

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct olympic_db
{
    char *name;                 // name of the nation, which is a string that can have arbitrary length.
    int gold;                   // number of gold medals, which is a non-negative integer.
    int silver;                 // number of silver medal, which is a non-negative integer.
    int bronze;                 // number of bronze medals, which is a non-negative integer.
    struct olympic_db *next;    // pointer to the next node
} olympic_db_t;

olympic_db_t *add_new_nation(olympic_db_t **db, char *nation);
olympic_db_t *swap_node_content(olympic_db_t **node1, olympic_db_t **node2);
olympic_db_t *load_db_file(char *path);
int medal_val_is_numeric(char *gold, char *silver, char *bronze);
int write_db_file(olympic_db_t **db, char **arg);
int add_medals(olympic_db_t **db, char **arg);
int sort_db(olympic_db_t **db);
int read_std_input(char **buffer);
char** input_str_split(const char *str, int *token_cnt);
void print_sorted_db(olympic_db_t **db);
void free_db_memory(olympic_db_t **db);
void free_splitted_str_memory(char **str);

#endif
