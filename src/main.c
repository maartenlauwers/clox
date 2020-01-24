//
//  main.c
//  clox
//
//  Created by Maarten on 24/01/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//

#include "common.h"
#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {
    Chunk chunk;
    initChunk(&chunk);
    writeChunk(&chunk, OP_RETURN);

    disassembleChunk(&chunk, "test chunk");

    freeChunk(&chunk);
    return 0;
}
