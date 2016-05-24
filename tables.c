#include <stdio.h>
#include <stdlib.h>

#include "tables.h"

void * insert_entry(unsigned int table_id)
{
	struct table_s * td = &tables_info[table_id];
	struct node_s * entry = (struct node_s *) malloc(sizeof(struct node_s));

	if (entry != NULL) {
		entry->value = malloc(td->size_of_entry);
		entry->next = td->head_node;
		td->head_node = entry;
	}

	td->entry_count += 1;

	/* pointer to the allocated memory */
	return entry->value;
}

struct node_s * search(unsigned int table_id, func_tst is_func_tst)
{
	struct table_s * td = &tables_info[table_id];
	struct node_s * entry = td->head_node;

	while (entry != NULL) {
		if (is_func_tst(entry) == 1)
			return entry;

		entry = entry->next;
	}

	/* element not found */
	return NULL;
}

int delete(unsigned int table_id, func_tst is_func_tst)
{
	struct table_s * td = &tables_info[table_id];
	struct node_s * current = td->head_node;
	struct node_s * next = (current) ? current->next : NULL;
	int deleted_entry = 0;
	struct node_s * prev = td->head_node;

	/* Remove from head of list */
	while (current != NULL && is_func_tst(current->value) == 0)
	{
		next = current->next;
		free(current->value);
		free(current);
		/*
		 * prevent the current pointer can be used
		 * to free the same memory more than once.
		 */
		current = NULL;
		current = next;
		td->head_node = current;

		/* Update counters */
		deleted_entry += 1;
		td->entry_count -= 1;
	}

	/* Remove item into the list */
	while (current != NULL) {
		if (next != NULL && is_func_tst(next->value) == 0) {
			current->next = next->next;
			free(next->value);
			free(next);
			next = NULL;

			/* Update counters */
			deleted_entry += 1;
			td->entry_count -= 1;
		} else {
			current = next;
		}

		if (current != NULL)
			next = current->next;
	}

	return deleted_entry;
}

void create_table(unsigned int table_id, unsigned int entry_size, purge_candidate_fun purge_fun, delete_candidate_fun delete_fun, free_entry_candidate_fun free_entry_fun)
{
	struct table_s * td = &tables_info[table_id];

	td->size_of_entry = entry_size;
	td->entry_count = 0;
	td->is_purge_candidate = purge_fun;
	td->is_delete_candidate = delete_fun;
	td->free_entry_candidate = free_entry_fun;
	td->head_node = NULL;
}

void free_table(unsigned int table_id) {
	struct table_s * td = &tables_info[table_id];
	struct node_s * current = td->head_node;
	struct node_s * next = NULL;

	while (current != NULL) {
		next = current->next;
		td->free_entry_candidate(current->value);
		/*
		 * The next instrcution gonna override
		 * the current value.
		 */
		free(current);
		current = next;
	}

	/*
	 * Setting head_node to NULL after it is freed
	 * eliminate the possibility that the head_node
	 * pointer can be used
	 */
	td->head_node = NULL;
}
