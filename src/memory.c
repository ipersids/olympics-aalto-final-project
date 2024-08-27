#include "project.h"

/**
 * Frees the memory allocated for a linked list of `olympic_db_t` nodes.
 *
 * This function iterates through the linked list, freeing each node and its associated 
 * dynamically allocated memory. Specifically, it deallocates the memory for each nation's 
 * name string as well as the memory for each node in the list.
 *
 * @param db  Pointer to the pointer to the head of the linked list. The memory of 
 *            all nodes in the list and their associated name strings will be freed. 
 *            After freeing, the pointer to the head of the list will be set to NULL.
 */
void free_db_memory(olympic_db_t **db)
{
    olympic_db_t *current = *db;
    olympic_db_t *next = NULL;

    if (!*db)
        return;

    while (current)
    {
        next = current->next;
        free(current->name); // Free the name string
        free(current); // Free the current node
        current = next;
    }
    *db = NULL;
}

/**
 * Frees the memory allocated for a dynamically allocated array of strings.
 *
 * This function iterates over the array of strings, freeing each string individually,
 * and then frees the array itself. It is used to clean up memory after processing
 * a split string array, where each element was dynamically allocated.
 *
 * @param str  Pointer to the array of strings to be freed. The array itself and
 *             all the individual strings it contains will be deallocated.
 */
void free_splitted_str_memory(char **str)
{
    if (!str)
        return;
    for (int i = 0; str[i] != NULL; i++)
    {
        free(str[i]);
    }
    free(str);
}
