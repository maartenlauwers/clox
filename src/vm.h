//
//  vm.h
//  clox
//
//  Created by Maarten on 25/01/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//

#ifndef vm_h
#define vm_h

#include "chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* ip;
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);

#endif /* vm_h */
