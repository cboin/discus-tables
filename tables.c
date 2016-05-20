#include <stdio.h>
#include <stdlib.h>

#include "tables.h"

void * insert_entry(unsigned int table_id)
{
	struct table_s * td = &tables_info[table_id];
	struct node_s * entry = (struct node_s *) malloc(sizeof(struct node_s));

	if (entry != NULL) {
		if ((entry->value = malloc(td->size_of_entry)) == NULL)
			perror("malloc");
		entry->next = td->head_node;
		td->head_node = entry;
	}

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

	return NULL;
}

int delete(unsigned int table_id, func_tst is_func_tst)
{
	struct table_s * td = &tables_info[table_id];
	struct node_s * entry = td->head_node;
	struct node_s * previous_entry = NULL;
	int deleted_entry = 0;

	while (entry != NULL) {
		if (is_func_tst(entry) == 1) {
			if (previous_entry == NULL) {
				td->head_node = td->head_node->next;
			} else if (entry->next == NULL) {
				previous_entry->next = NULL;
			} else {
				previous_entry-> next = entry->next;
			}

			deleted_entry += 1;
		}

		previous_entry = entry;
		entry = entry->next;
	}

	return deleted_entry;
}

void display_list(unsigned int table_id)
{
}

void create_table(unsigned int table_id, unsigned int row_size, purge_candidate_fun purge_fun, delete_candidate_fun delete_fun)
{
	struct table_s * td = &tables_info[table_id];

	td->size_of_entry = row_size;
	td->entry_count = 0;
	td->is_purge_candidate = purge_fun;
	td->is_delete_candidate = delete_fun;
	td->head_node = NULL;
}
