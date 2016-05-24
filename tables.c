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

struct node_s * search(unsigned int table_id, func_tst is_func_tst)
{
	struct table_s * td = &tables_info[table_id];

	struct node_s * entry = td->head_node;

	while (entry != NULL) {
		if (is_func_tst(entry) == 1)
			return entry;

		entry = entry->next;
	}

	printf("return NULL\n");

	/* element not found */
	return NULL;
}

struct string_s {
	char * value;
	int length;
};

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
		printf("Remove: %s\n", ((struct string_s *) current->value)->value);
		next = current->next;
		free(current->value);
		free(current);
		current = next;
		td->head_node = current;
		deleted_entry += 1;
		td->entry_count -= 1;
	}

	/* Remove item into the list */
	while (current != NULL) {
		if (next != NULL && is_func_tst(next->value) == 0) {
			printf("Remove: %s\n", ((struct string_s *) next->value)->value);
			current->next = next->next;
			free(next->value);
			free(next);
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

void create_table(unsigned int table_id, unsigned int row_size, purge_candidate_fun purge_fun, delete_candidate_fun delete_fun)
{
	struct table_s * td = &tables_info[table_id];

	td->size_of_entry = row_size;
	td->entry_count = 0;
	td->is_purge_candidate = purge_fun;
	td->is_delete_candidate = delete_fun;
	td->head_node = NULL;
}

void free_table(unsigned int table_id) {
	struct table_s * td = &tables_info[table_id];
	struct node_s * current = td->head_node;
	struct node_s * next = NULL;

	while (current != NULL) {
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}
