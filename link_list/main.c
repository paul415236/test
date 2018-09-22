#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    char acFile[64];
    struct node_t *prev;
    struct node_t *next;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;
    long nr;
} list_t;

node_t * append(list_t *list, char *file)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    strncpy(node->acFile, file, sizeof(node->acFile));

    if (list->nr)
    {
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
    }
    else
    {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    }

    list->nr ++;

    return node;
}

int delete(list_t *list, node_t *node)
{
    if (list->nr <= 0)
        return 0;

    if (node->prev)
        node->prev->next = node->next;
    else
        list->head = node->next;

    if (node->next)
        node->next->prev = node->prev;
    else
        list->tail = node->prev;

    free(node);
    list->nr --;
    
    return 0;
}

int show(list_t *list)
{
    int i;
    node_t *tmp;

	if (list->nr == 0)
		printf ("empty \n");

    tmp = list->head;
    for (i = 0; i < list->nr; i++)
    {
        printf("[%d] node: %p \n", i, tmp);
        tmp = tmp->next;
    }

    return 0;
}

int main(int argc, char **argv)
{
#define TEST_PERIOD (500)
    int i;
    list_t *list;
    list = (list_t *)malloc(sizeof(list_t));
    list->head = list->tail = NULL;
    list->nr = 0;

    for (i = 0; i < TEST_PERIOD; i++)
    {
        append(list, "1212121"); // we don't care data
    }

    show(list);

    int r;
    node_t *tmp;
    for (;i > 0; i--)
    {
        printf("========================= \n");
		if (i)
        	r = rand() % i;
		else
			r = 0;

        printf("rand=%d, ", r);
        for (tmp = list->head; r > 0; r--)
            tmp = tmp->next;

        printf("node=%p \n", tmp);

        delete(list, tmp);
        show(list);
    }

    free(list);

    return 0;
}
