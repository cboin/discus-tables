#ifndef TABLES_H
#define TABLES_H

/**
 * @file tables.h
 *
 * @brief Tables managements
 *
 * This file discribed how each element of
 * the linked list will insert, deleted
 * and how to search its.
 *
 * To insert new element into a table you
 * have to give this id to create_entry
 * function, this function will returns
 * you a node_s pointer. To store data
 * into it you have to type:
 * entry->value = your_value;
 * After this your able to add this entry
 * to the linked list, this should be done
 * with the given function called add_first.
 * This function will add the element at
 * the head of the linked list.
 *
 * To delete an element in this list you
 * should use delete function this
 * function will delete each occurences of
 * entry describe by delete_candidante
 * function.
 *
 * To seatch after an element you have to
 * use search function, it will search after
 * your element within the table pointed by
 * table_id and returns if it found the
 * corresponding entry.
 */

typedef int (* func_tst) (void * entry);
typedef func_tst (purge_candidate_fun);
typedef func_tst (delete_candidate_fun);
typedef func_tst (search_candidate_fun);
typedef func_tst (free_entry_fun);

struct node_s {
	void * value;
	struct node_s * next;
};

struct table_s {
	purge_candidate_fun is_purge_candidate;
	delete_candidate_fun is_delete_candidate;
	free_entry_fun free_entry;
	struct node_s * head_node;
	unsigned int size_of_entry;
	unsigned int entry_count;
};

extern struct table_s tables_info[];

/**
 * Return the index of the first occurence of
 * the specified element in this linked list
 * or NULL if this list does not contain
 * the element.
 *
 * @param table_id the table id.
 * @param statement machter condition.
 *
 * @return The first element or NULL if
 * list does not contain this element.
 */
struct node_s * search(unsigned int table_id, func_tst is_func_tst);


/**
 * Removes each occurences of the specified
 * element from this list, If they are present
 * call delete_candidate function and strat to
 * remove each occurences.
 *
 * @see delete_candidate_fun
 * @param table_id the table id.
 *
 * @return If they are present it should returns
 * the numbers of occurences deleted, Otherwise
 * -1 is returned.
 */
int delete(unsigned int table_id, func_tst is_func_tst);

/**
 * Create of an entry ahead in the given table.
 *
 * @param table_id the table id.
 *
 * @return An entry to the speace allocated to store
 * data.
 */
void * insert_entry(unsigned int table_id);

/**
 * Display each elements stored into
 * this list.
 *
 * @param table_id the tbla id
 *
 */
void display_list(unsigned int table_id);

/**
 * Create a table
 * TODO
 */
void create_table(unsigned int table_id, unsigned int row_size, purge_candidate_fun purge_fun, delete_candidate_fun delete_fun);

void free_table(unsigned int table_id);

#endif
