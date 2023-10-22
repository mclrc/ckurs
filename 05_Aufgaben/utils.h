#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Utility functions used throughout the codebase.
*/

/*
Try to malloc, abort when out of memory.
*/
void* mallocx(size_t size) {
    void * allocation = malloc(size);

    if (allocation) {
        return allocation;
    } else {
        printf("Out of memory");
        abort();
    }
}

/*
Return whether the given string contains characters which might make trouble in a file name.
*/
bool is_invalid_filename(char* name) {
    int len = strlen(name);

    for(int i = 0; i<len;i++){
        if(name[i] == '/' || name[i] == '\\' || name[i] == '<' || name[i] == '>' || name[i] == '|'
            || name[i] == ':' || name[i] == '*' || name[i] == '?' || name[i] == '"'){
            return true;
        }
    }

    return false;
}

#endif