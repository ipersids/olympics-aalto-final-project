#include "project.h"

/**
 * Checks if the given strings representing medal values are numeric.
 *
 * This function verifies if each of the provided strings (representing gold, silver,
 * and bronze medal counts) consists only of digit characters. It returns 0 if all
 * strings are numeric, and -1 if any of them contain non-digit characters.
 *
 * @param gold   String representing the gold medal count.
 * @param silver String representing the silver medal count.
 * @param bronze String representing the bronze medal count.
 * @return 0 if all values are numeric, -1 if any value is non-numeric.
 */
int medal_val_is_numeric(char *gold, char *silver, char *bronze)
{
    for (int i = 0, l = strlen(gold); i < l; i++)
    {
        if (!isdigit(gold[i]))
            return -1;
    }
    for (int i = 0, l = strlen(silver); i < l; i++)
    {
        if (!isdigit(silver[i]))
            return -1;
    }
    for (int i = 0, l = strlen(bronze); i < l; i++)
    {
        if (!isdigit(bronze[i]))
            return -1;
    }
    return 0;
}

/**
 * Adds medals to an existing nation in the database.
 *
 * This function searches for a nation in the database by its name. If the nation is
 * found, it updates the medal counts (gold, silver, and bronze) by adding the values
 * provided in the `arg` array. It performs validation to ensure the medal values are
 * numeric and that the updated counts do not become negative.
 *
 * @param db  Pointer to a pointer to the head of the linked list representing the database.
 * @param arg Array of strings containing the command arguments:
 *            - arg[1]: Nation name
 *            - arg[2]: Gold medal count to add
 *            - arg[3]: Silver medal count to add
 *            - arg[4]: Bronze medal count to add
 * @return 0 if the medals were successfully added, -1 if the nation was not found
 *         or if there was an error (e.g., invalid numeric values).
 */
int add_medals(olympic_db_t **db, char **arg)
{
    olympic_db_t *current = *db;
    int gold = 0;
    int silver = 0;
    int bronze = 0;

    if (!db || !*db)
        return -1;

    while (current)
    {
        if (strcmp(arg[1], current->name) == 0)
        {
            if (medal_val_is_numeric(arg[2], arg[3], arg[4]) == -1)
                return -1;
            gold = current->gold + atoi(arg[2]);
            silver = current->silver + atoi(arg[3]);
            bronze = current->bronze + atoi(arg[4]);
            if (gold < 0 || silver < 0 || bronze < 0)
                return -1;
            current->gold = gold;
            current->silver = silver;
            current->bronze = bronze;
            return 0;
        }
        current = current->next;
    }
    return -1;
}
