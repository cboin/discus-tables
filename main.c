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

void display_entry(struct human_s * entry)
{
	printf("First name: %s\n", entry->first_name);
	printf("Last name: %s\n", entry->last_name);
	printf("Phone: %d\n", entry->phone);
	printf("Size: %f\n", entry->size);
}

static int search_denis_ritchie(void * entry_ptr)
{
	struct human_s * entry = (struct human_s *) entry_ptr;
	return ((strcmp(entry->first_name, "Denis") && (strcmp(entry->last_name, "Ritchie"))));
}

static int search_bob_dyaln(void * entry_ptr)
{
	struct human_s * entry = (struct human_s *) entry_ptr;
	return ((strcmp(entry->first_name, "Bob") && (strcmp(entry->last_name, "Dylan"))));
}
int main(void)
{
	create_table(0, sizeof(struct human_s), human_purge_candidate, human_delete_candidate);

	struct human_s * bob_dyaln = insert_entry(0);

	bob_dyaln->first_name = "Bob";
	bob_dyaln->last_name = "Dyaln";
	bob_dyaln->phone = 800976456;
	bob_dyaln->size = 1.78;

	display_entry(bob_dyaln);

	struct human_s * denis_ritchie = insert_entry(0);

	denis_ritchie->first_name = "Denis";
	denis_ritchie->last_name = "Ritchie";
	denis_ritchie->phone = 623454321;
	denis_ritchie->size = 1.88;

	struct node_s * found_ritchie = search(0, search_denis_ritchie);	

	display_entry(found_ritchie->value);


	/* totally stupid test */
	struct table_s * td = &tables_info[0];
	struct human_s * brian_kernighan = insert_entry(0);
	memcpy(brian_kernighan, denis_ritchie, td->size_of_entry);

	brian_kernighan->first_name = "Biran";
	brian_kernighan->last_name = "Kernighan";
	
	/* But that works */
	display_entry(brian_kernighan);

	printf("Entry count; %d\n", td->entry_count);

	/* TODO: test delete */
	
	return EXIT_SUCCESS;
}
