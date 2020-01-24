//
//  memory.h
//  clox
//
//  Created by Maarten on 24/01/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//

#ifndef CLOX_MEMORY_H
#define CLOX_MEMORY_H

#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(previous, type, oldCount, count) \
    (type*)reallocate(previous, sizeof(type) * (oldCount), \
        sizeof(type) * (count))

#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

void* reallocate(void* previous, size_t oldSize, size_t newSize);

#endif //CLOX_MEMORY_H
