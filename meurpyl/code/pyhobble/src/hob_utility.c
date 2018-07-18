#include <stdio.h>
#include <stdlib.h>

void * 
hob_xmalloc (size_t size) 
{
    void *memory;
    memory = malloc(size);
    if (memory) {
        memset(memory, 0, size);
        return memory;
    } else {
        perror("Memory allocation error.");
        exit(EXIT_FAILURE);
    }
}

void hob_xfree(void *memory) 
{
    if (memory) {
        memset(memory, 0, sizeof(memory));
        free(memory);
        memory = NULL;
    } else {
        ;
    }
    return;
}