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

	return entry->value;
}

struct node_s * search(unsigned int table_id)
{
	struct table_s * td = &tables_info[table_id];

	struct node_s * entry;

	/* if list is empty */
	if ((entry = td->head_node) == NULL)
		return NULL;

	while (entry != NULL) {
		if (td->is_search_candidate(entry) == 1)
			return entry;

		entry = entry->next;
	}

	/* element not found */
	return NULL;
}

int delete(unsigned int table_id)
{
	struct table_s * td = &tables_info[table_id];
	struct node_s * current = td->head_node;
	struct node_s * next = NULL;
	int deleted_entry = 0;
	struct node_s * prev = td->head_node;

	if (td->head_node == NULL)
		return 0;

	while (current != NULL) {
		if (td->is_delete_candidate(current->value) == 0) {
			if (current == prev) {
				prev = current->next;
				free(current);
				current = prev;
				td->head_node = current;
			} else {
				prev->next = current->next;
				free(current);
				current=prev->next;
			}
			deleted_entry += 1;
			td->entry_count -= 1;
		} else {
			prev = current;
			current = prev->next;
		}
	}

	return deleted_entry;
}

void create_table(unsigned int table_id, unsigned int row_size, purge_candidate_fun purge_fun, delete_candidate_fun delete_fun, search_candidate_fun search_fun)
{
	struct table_s * td = &tables_info[table_id];

	td->size_of_entry = row_size;
	td->entry_count = 0;
	td->is_purge_candidate = purge_fun;
	td->is_delete_candidate = delete_fun;
	td->is_search_candidate = search_fun;
	td->head_node = NULL;
}
