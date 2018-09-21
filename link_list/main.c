#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct list_t
{
    int dirty;
    char acFile[64];
    struct list_t *next;
} list_t;

typedef struct
{
    list_t *list;
} shell_t;

static int regist(void **obj)
{   
    static int i = 0;
    list_t *s = (list_t *)*obj;

    while(s->dirty)
    {
        if (s->next)
            s = s->next;
        else
        {
            s->next = (list_t *)malloc(sizeof(list_t));
            if (!s->next)
            {
                printf("out of memory \n");
                return -1;
            }
            printf("reg %p \n", s->next);
            s = s->next;
        }
    }

    s->dirty = 1;
    sprintf(s->acFile, "%d%d", i, i);
    i++;


    return 0;
}

int destroy(void **obj)
{
    list_t *s = (list_t *)*obj;
    list_t *t;

    if (s->dirty)
    {
        t = s;
        if (s->next)
        {
            *obj = s->next;
            printf("append %p \n", *obj);
        }
        printf("free %p \n", t);
        free(t);
    }

    return 0;
}

int main(void)
{
    shell_t shell;
    shell.list = (list_t *)malloc(sizeof(list_t));
    if (!shell.list)
    {
        printf("out of memory \n");
        return -1;
    }
    memset(shell.list, 0, sizeof(shell.list));

    if (shell.list)
        printf("reg %p \n", shell.list);

    regist((void *)&shell.list);
    if (shell.list)
        printf("222  %p \n", shell.list);
    
    regist((void *)&shell.list);
    if (shell.list->next)
        printf("333  %p \n", shell.list->next);


    regist((void *)&shell.list);
    if (shell.list)
        printf("444  %p \n", shell.list);

    destroy((void *)&shell.list->next);
    if (shell.list->next)
        printf("555  %p \n", shell.list->next);

    destroy((void *)&shell.list);
    if (shell.list)
        printf("666  %p \n", shell.list);


    destroy((void *)&shell.list);
    if (shell.list)
        printf("777  %p \n", shell.list);


    return 0;
}

