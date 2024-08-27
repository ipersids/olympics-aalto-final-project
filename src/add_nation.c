#include "project.h"

/**
 * Adds a new nation to the end of the linked list of `olympic_db_t` nodes.
 *
 * This function creates a new node for the given nation, initializes its fields, 
 * and appends it to the end of the linked list. If a nation with the same name 
 * already exists in the list, the function does not add a new node and returns `NULL`.
 *
 * @param db      Pointer to the pointer to the head of the linked list. 
 *                The new nation will be added to the end of this list.
 * @param nation  The name of the nation to be added. This string is duplicated and 
 *                stored in the new node.
 * 
 * @return        A pointer to the newly added `olympic_db_t` node if the operation 
 *                is successful, or `NULL` if there was an error (e.g., memory allocation failure 
 *                or a nation with the same name already exists).
 */
olympic_db_t *add_new_nation(olympic_db_t **db, char *nation)
{
    olympic_db_t *current = *db;
    olympic_db_t *prev = NULL;
    olympic_db_t *res = (olympic_db_t *)malloc(sizeof(olympic_db_t));

    if (!res)
        return NULL;
    
    res->name = strdup(nation);
    if (!res->name)
    {
        free(res);
        return NULL;
    }
    res->gold = 0;
    res->silver = 0;
    res->bronze = 0;
    res->next = NULL;

    if (*db == NULL)
    {
        *db = res;
        return res;
    }

    while (current)
    {
        if (strcmp(nation, current->name) == 0)
        {
            free(res->name);
            free(res);
            return NULL;
        }
        prev = current;
        current = current->next;
    }
    prev->next = res;

    return res;
}
