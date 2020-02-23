//
//  vm.c
//  clox
//
//  Created by Maarten on 25/01/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//
#include <stdio.h>
#include "common.h"
#include "debug.h"
#include "vm.h"
#include "compiler.h"

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {
    
}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

static void binaryOpAddition() {
    double b = pop();
    double a = pop();
    push(a + b);
}
static void binaryOpSubtraction() {
    double b = pop();
    double a = pop();
    push(a - b);
}
static void binaryOpMultiplication() {
    double b = pop();
    double a = pop();
    push(a * b);
}
static void binaryOpDivision() {
    double b = pop();
    double a = pop();
    push(a / b);
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        printf("        ");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        
        // NOTE: Because vm.ip and vm.chunk->code both point to a byte address (because the array is byte sized) in (the same area of) memory,
        // subtracting one from the other will give the difference in bytes and thus the relative offset from
        // the beginning of the bytecode.
        disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
#endif
        
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD:        binaryOpAddition(); break;
            case OP_SUBTRACT:   binaryOpSubtraction(); break;
            case OP_MULTIPLY:   binaryOpMultiplication(); break;
            case OP_DIVIDE:     binaryOpDivision(); break;
            case OP_NEGATE:     push(-pop()); break;
            case OP_RETURN:
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
        }
    }
    
#undef READ_BYTE
#undef READ_CONSTANT
}

InterpretResult interpret(const char* source) {
    Chunk chunk;
    initChunk(&chunk);
    
    if (!compile(source, &chunk)) {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }
    
    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;
    
    InterpretResult result = run();
    
    freeChunk(&chunk);
    return result;
}

