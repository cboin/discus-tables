#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tables.h"

#define NO 0
#define YES 1

struct table_s tables_info[2];

struct human_s {
	char * first_name;
	char * last_name;
	int phone;
	double size;
};

static int human_purge_candidate(void * entry_ptr)
{
        struct human_s * entry  = (struct human_s *) entry_ptr;
	return (strcmp(entry->first_name, "Bob") == 0);
}

static int human_delete_candidate(void * entry_ptr)
{
	struct human_s * entry = (struct human_s *) entry_ptr;
	return entry->phone == 0;
}

int main(void)
{
	create_table(0, sizeof(struct human_s), human_purge_candidate, human_delete_candidate);
	return EXIT_SUCCESS;
}
