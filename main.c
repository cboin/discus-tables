#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "tables.h"

struct table_s tables_info[2];

struct human_s {
    char *first_name;
    char *last_name;
    int phone;
    double size;
};

static int human_purge_candidate(void *entry_ptr)
{
    struct human_s *entry = (struct human_s *) entry_ptr;
    return strcmp((char *) entry->first_name, "Bob") == 0;
}

static int human_delete_candidate(void *entry_ptr)
{
    struct human_s *entry = (struct human_s *) entry_ptr;
    return entry->phone == 0;
}

static int search_denis_ritchie(void *entry_ptr)
{
    struct human_s *entry = (struct human_s *) entry_ptr;
    return (strcmp((char *) entry->first_name, "Denis") == 0) &&
	(strcmp((char *) entry->last_name, "Ritchie") == 0);
}

static int search_bob_dylan(void *entry_ptr)
{
    struct human_s *entry = (struct human_s *) entry_ptr;
    return (strcmp(entry->first_name, "Bob") == 0) &&
	(strcmp(entry->last_name, "Dylan") == 0);
}

static int search_brian_kernighan(void *entry_ptr)
{
    struct human_s *entry = (struct human_s *) entry_ptr;
    return (strcmp((char *) entry->first_name, "Brian") == 0) &&
	(strcmp((char *) entry->last_name, "Kernighan") == 0);
}

static int human_free_entry(void *entry_ptr)
{
    struct human_s *entry = (struct human_s *) entry_ptr;
    free(entry);

    return 0;
}

struct string_s {
    char *value;
    unsigned int length;
};

static int string_purge_candidate(void *entry_ptr)
{
    return 0;
}

static int hello_world_delete_candidate(void *entry_ptr)
{
    struct string_s *entry = (struct string_s *) entry_ptr;
    return strcmp((char *) entry->value, "Hello, world") == 0;
}

static int search_hello_world(void *entry_ptr)
{
    struct string_s *entry = (struct string_s *) entry_ptr;
    return (strcmp((char *) entry->value, "Hello, world") == 0) &&
	(entry->length == strlen("Hello, world"));
}

static int bar_delete_candidate(void *entry_ptr)
{
    struct string_s *entry = (struct string_s *) entry_ptr;
    return strcmp((char *) entry->value, "bar") == 0;
}

static int foo_delete_candidate(void *entry_ptr)
{
    struct string_s *entry = (struct string_s *) entry_ptr;
    return strcmp((char *) entry->value, "foo") == 0;
}

static int search_foo(void *entry_ptr)
{
    struct string_s *entry = (struct string_s *) entry_ptr;
    return strcmp((char *) entry->value, "foo") == 0;
}

static int string_free_entry(void *entry_ptr)
{
    struct string_s *entry = (struct string_s *) entry_ptr;
    free(entry);
    entry = NULL;

    return 0;
}

int main(void)
{
    /*
     * TEST INSERT AND SEARCH
     */

    create_table(0, sizeof(struct human_s), human_purge_candidate,
		 human_delete_candidate, human_free_entry);

    struct table_s *td = &tables_info[0];
    struct human_s *bob_dylan = insert_entry(0);

    bob_dylan->first_name = "Bob";
    bob_dylan->last_name = "Dylan";
    bob_dylan->phone = 800976456;
    bob_dylan->size = 1.78;

    struct human_s *head = td->head_node->value;

    /* We check if the head of our list is equals to the normal entry */
    assert(strcmp((char *) head->first_name, bob_dylan->first_name) == 0);
    assert(head->phone == bob_dylan->phone);

    struct human_s *denis_ritchie = insert_entry(0);

    denis_ritchie->first_name = "Denis";
    denis_ritchie->last_name = "Ritchie";
    denis_ritchie->phone = 623454321;
    denis_ritchie->size = 1.88;

    /* We search after Ritchie */
    struct human_s *found_ritchie = search(0, search_denis_ritchie)->value;

    assert(found_ritchie->size == denis_ritchie->size);
    assert(found_ritchie->phone == denis_ritchie->phone);

    /* At this state entry count should equals to two */
    assert(td->entry_count == 2);

    /* totally stupid test */
    struct human_s *brian_kernighan = insert_entry(0);
    memcpy(brian_kernighan, denis_ritchie, td->size_of_entry);

    /* Change some value */
    brian_kernighan->first_name = "Brian";
    brian_kernighan->last_name = "Kernighan";
    brian_kernighan->phone = 0;

    /* But that works */
    struct human_s *found_kernighan = search(0, search_brian_kernighan)->value;
    assert(found_kernighan->size == denis_ritchie->size);
    assert(found_kernighan->phone == brian_kernighan->phone);

    /*
     * END TEST INSERT AND SEARCH
     */

    /*
     * TEST DELETE AND PURGE
     */

    create_table(1, sizeof(struct string_s), string_purge_candidate,
		 hello_world_delete_candidate, string_free_entry);
    td = &tables_info[1];

    /* Our fresh list should not contain any item */
    assert(td->head_node == NULL);

    /* Here, we will insert in head */
    struct string_s *hello_world = insert_entry(1);

    char *s = "Hello, world";
    hello_world->value = s;
    hello_world->length = strlen(s);

    /* That, works ! */
    assert(td->head_node != NULL);

    /* One regular check */
    struct string_s *tmp = td->head_node->value;
    assert(hello_world->length == tmp->length);

    /* We will remove the head of list */
    int deleted_entry = delete(1, hello_world_delete_candidate);
    assert(deleted_entry == 1);

    /* Search after NULL node */
    struct node_s *deleted = search(1, search_hello_world);
    assert(deleted == NULL);
    assert(td->head_node == NULL);

    /* Here, entry count should be equals to zero */
    assert(td->entry_count == 0);

    /* Now, we will try to insert three item into the list */
    struct string_s *foo = insert_entry(1);
    foo->value = "foo";
    foo->length = strlen("foo");

    struct string_s *bar = insert_entry(1);
    bar->value = "bar";
    bar->length = strlen("bar");

    struct string_s *fum = insert_entry(1);
    fum->value = "fum";
    fum->length = strlen("fum");

    /* So, entry count is equals to three */
    assert(td->entry_count == 3);

    /* Small display test */
    struct node_s *current = td->head_node;

    int i;
    for (i = 0; current != NULL; i++, current = current->next)
	printf("[%d] value->%s\n", i,
	       ((struct string_s *) current->value)->value);

    /* If we try to delete into the middle of our list */
    deleted_entry = delete(1, bar_delete_candidate);
    assert(deleted_entry == 1);

    /* Fine */
    assert(td->entry_count == 2);

    struct string_s *pwet = insert_entry(1);
    pwet->value = "pwet";
    pwet->length = strlen("pwet");

    deleted_entry = delete(1, foo_delete_candidate);

    /* The tail was deleted */
    assert(td->entry_count == 2);

    /* If we search after the old tail, search should return NULL */
    struct node_s *old_tail = search(1, search_foo);
    assert(old_tail == NULL);

    /*
     * END TEST DELETE AND PURGE
     */

    free_table(0);
    free_table(1);

    return EXIT_SUCCESS;
}
