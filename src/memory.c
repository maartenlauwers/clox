//
//  memory.c
//  clox
//
//  Created by Maarten on 24/01/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//
#include <stdlib.h>

#include "common.h"
#include "memory.h"

void* reallocate(void* previous, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(previous);
        return NULL;
    }

    return realloc(previous, newSize);
}
