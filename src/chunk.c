//
//  chunk.c
//  clox
//
//  Created by Maarten on 24/01/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//

#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    
    chunk->lineCount = 0;
    chunk->lineCapacity = 0;
    chunk->lines = NULL;
    
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->lineCapacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(chunk->code, uint8_t, oldCapacity, chunk->capacity);
    }
    
    chunk->code[chunk->count] = byte;
    
    
    if (getLine(chunk, chunk->count - 1) != line) {
        // Add a new line
        if (chunk->lineCapacity < chunk->lineCount + 2) {
            int oldCapacity = chunk->lineCapacity;
            chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
            chunk->lines = GROW_ARRAY(chunk->lines, int, oldCapacity, chunk->lineCapacity);
        }
        
        chunk->lines[chunk->lineCount] = line;
        chunk->lines[chunk->lineCount + 1] = chunk->count;
        chunk->lineCount += 2;
    }
    else {
        chunk->lines[chunk->lineCount - 1] = chunk->count;
    }
    
    chunk->count++;
}

int addConstant(Chunk *chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

int getLine(Chunk *chunk, int offset) {
    if (offset < 0) {
        return -1;
    }
    
    for (int i = 0; i < chunk->lineCapacity; i += 2) {
        int line = chunk->lines[i];
        int lineOffset = chunk->lines[i+1];
        
        if (offset <= lineOffset) {
            return line;
        }
    }
    return -1;
}
