#include <stdio.h>
#include <stdlib.h>

#include "tables.h"

void * insert_entry(unsigned int table_id)
:q
:q
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
	struct node_s * entry = td->head_entry;

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
	struct node_s * entry = td->head_entry;
	struct node_s * previous_entry = NULL;
	int deleted_entry = 0;

	while (entry != NULL) {
		if (is_func_tst(entry) == 1) {
			if (previous_entry == NULL) {
				td->head_entry = td->head_entry->next;
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
	if (table_id > ((sizeof (tables_info)) / sizeof(struct tables_s)))
		fprintf(stderr, "Table_id is greater than size of tables_info\n");

	struct table_s * td = &tables_info[table_id];
	struct node_s * ptr = td->head_entry;

	printf("[ ");

	while (ptr != NULL) {
		printf("%d, ", (int) ptr->value);
		ptr = ptr->next;
	}

	printf(" ]\n");
}

