#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

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

static int search_denis_ritchie(void * entry_ptr)
{
	struct human_s * entry = (struct human_s *) entry_ptr;
	return ((strcmp(entry->first_name, "Denis") && (strcmp(entry->last_name, "Ritchie"))));
}

static int search_bob_dylan(void * entry_ptr)
{
	struct human_s * entry = (struct human_s *) entry_ptr;
	return ((strcmp(entry->first_name, "Bob") && (strcmp(entry->last_name, "Dylan"))));
}

static int search_brian_kernighan(void * entry_ptr)
{
	struct human_s * entry = (struct human_s *) entry_ptr;
	return ((strcmp(entry->first_name, "Biran") && (strcmp(entry->last_name, "Kernighan"))));
}

struct string_s {
	char * value;
	unsigned int length;
};

static int string_purge_candidate(void * entry)
{
	return 0;
}

static int string_delete_candidate(void * entry)
{
	return 0;
}

int main(void)
{
	/*
	 * TEST INSERT AND SEARCH
	 */

	create_table(0, sizeof(struct human_s), human_purge_candidate, human_delete_candidate);

	struct table_s * td = &tables_info[0];
	struct human_s * bob_dylan = insert_entry(0);

	bob_dylan->first_name = "Bob";
	bob_dylan->last_name = "Dylan";
	bob_dylan->phone = 800976456;
	bob_dylan->size = 1.78;

	struct human_s * head = td->head_node->value;

	assert(strcmp(head->first_name, bob_dylan->first_name) == 0);
	assert(head->phone == bob_dylan->phone);
	printf("[OK] Insert in head\n");

	struct human_s * denis_ritchie = insert_entry(0);

	denis_ritchie->first_name = "Denis";
	denis_ritchie->last_name = "Ritchie";
	denis_ritchie->phone = 623454321;
	denis_ritchie->size = 1.88;

	struct human_s * found_ritchie = search(0, search_denis_ritchie)->value;

	assert(found_ritchie->size == denis_ritchie->size);
	assert(found_ritchie->phone == denis_ritchie->phone);
	printf("[OK] Insert in head\n");

	assert(td->entry_count == 2);
	printf("[OK] 2 entry\n");

	/* totally stupid test */
	struct human_s * brian_kernighan = insert_entry(0);
	memcpy(brian_kernighan, denis_ritchie, td->size_of_entry);

	/* Change some value */
	brian_kernighan->first_name = "Biran";
	brian_kernighan->last_name = "Kernighan";
	brian_kernighan->phone = 0;

	/* But that works */
	struct human_s * found_kernighan = search(0, search_brian_kernighan)->value;
	assert(found_kernighan->size == denis_ritchie->size);
	assert(found_kernighan->phone == brian_kernighan->phone);
	printf("[OK] Copy struct into new node\n");

	/*
	 * END TEST INSERT AND SEARCH
	 */


	/*
	 * TEST DELETE AND PURGE
	 */

	create_table(1, sizeof(struct string_s), string_purge_candidate, string_delete_candidate);


	/*
	 * END TEST DELETE AND PURGE
	 */

	return EXIT_SUCCESS;
}
