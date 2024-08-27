#include "project.h"

/**
 * Swaps the contents of two nodes in a linked list.
 *
 * This function exchanges the data between two `olympic_db_t` nodes in a linked list.
 * It allocates a temporary node to hold the data of the first node while performing
 * the swap. After the swap, the temporary node is freed.
 *
 * The nodes are pointed to by `node1` and `node2`, which are pointers to pointers to
 * `olympic_db_t` structures. The function does not alter the actual node pointers
 * but only swaps the contents of the nodes they point to.
 *
 * @param node1 Pointer to the first node to swap.
 * @param node2 Pointer to the second node to swap.
 * @return A pointer to the first node after swapping (same as `*node1`).
 *         Returns `NULL` if memory allocation for the temporary node fails.
 */
olympic_db_t *swap_node_content(olympic_db_t **node1, olympic_db_t **node2)
{
    olympic_db_t *current = *node1;
    olympic_db_t *next = *node2;
    olympic_db_t *tmp = (olympic_db_t *)malloc(sizeof(olympic_db_t));

    if (!tmp)
        return NULL;

    // Copy the content of the first node into the temporary node
    tmp->name = current->name;
    tmp->gold = current->gold;
    tmp->silver = current->silver;
    tmp->bronze = current->bronze;

    // Swap the content of the first node with the second node
    current->name = next->name;
    current->gold = next->gold;
    current->silver = next->silver;
    current->bronze = next->bronze;

    // Copy the content of the temporary node to the second node
    next->name = tmp->name;
    next->gold = tmp->gold;
    next->silver = tmp->silver;
    next->bronze = tmp->bronze;

    free(tmp);

    return *node1;
}

/**
 * Sorts a linked list of `olympic_db_t` nodes in descending order based on medals.
 *
 * This function sorts a linked list of `olympic_db_t` nodes primarily by the number
 * of gold medals, then by silver medals if gold counts are equal, and finally by
 * bronze medals if both gold and silver counts are equal. The sorting is done in
 * descending order, so nodes with more medals appear earlier in the list.
 *
 * @param db Pointer to the head of the linked list to be sorted.
 * @return 0 on success, or -1 if the provided pointer is invalid (i.e., `db` is NULL
 *         or `*db` is NULL).
 */
int sort_db(olympic_db_t **db)
{
    olympic_db_t *current = *db;
    olympic_db_t *next = NULL;

    if (!db || !*db)
        return -1;

    while (current)
    {
        next = current->next;
        while (next)
        {
            if (current->gold < next->gold)
                swap_node_content(&current, &next);
            else if (current->gold == next->gold)
            {
                if (current->silver < next->silver)
                    swap_node_content(&current, &next);
                else if (current->silver == next->silver)
                {
                    if (current->bronze < next->bronze)
                        swap_node_content(&current, &next);
                }
            }
            next = next->next;
        }
        current = current->next;
    }
    return 0;
}

/**
 * Prints the contents of a sorted linked list of `olympic_db_t` nodes.
 *
 * This function iterates through a linked list of `olympic_db_t` nodes and prints
 * the details of each node in the format: `name gold silver bronze`. After printing
 * all nodes, it prints "SUCCESS" to indicate that the operation was completed.
 *
 * @param db Pointer to the head of the linked list to be printed.
 */
void print_sorted_db(olympic_db_t **db)
{
    olympic_db_t *current = *db;

    while (current)
    {
        printf("%s %d %d %d\n", current->name,
                                current->gold,
                                current->silver,
                                current->bronze);
        current = current->next;
    }
    printf("SUCCESS\n");
}
