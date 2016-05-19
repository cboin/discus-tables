#include <stdio.h>
#include <stdlib.h>

#include "tables.h"

struct entry_s * create_entry(unsigned int table_id)
{
	struct entry_s * entry = (struct entry_s *) malloc(sizeof(struct entry_s));

	if (entry != NULL) {
		entry->value = NULL;
		entry->next = NULL;
	} else {
		fprintf(stderr, "Creatin entry failed\n");
	}

	return entry;
}

void add_first(unsigned int table_id, struct entry_s * entry, const unsigned char * addr_value)
{
	if (table_id > ((sizeof (tables_info)) / sizeof(struct table_s)))
		fprintf(stderr, "Tables_id is greater than current tables_info size\n");

	if (entry == NULL)
		fprintf(stderr, "Trying to store null entry\n");

	struct table_s * td = &tables_info[table_id];

	entry->value = &addr_value;
	entry->next = td->head_entry;

	td->head_entry = entry;
}

struct entry_s * search(unsigned int table_id, int statement)
{
	return NULL;
}

int delete(unsigned int table_id)
{
	return -1;
}

void display_list(unsigned int table_id)
{
	if (table_id > ((sizeof (tables_info)) / sizeof(struct tables_s)))
		fprintf(stderr, "Table_id is greater than size of tables_info\n");

	struct table_s * td = &tables_info[table_id];
	struct entry_s * ptr = td->head_entry;

	printf("[ ");

	while (ptr != NULL) {
		printf("%d, ", (int) ptr->value);
		ptr = ptr->next;
	}

	printf(" ]\n");
}

