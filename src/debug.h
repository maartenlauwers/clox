//
//  debug.h
//  clox
//
//  Created by Maarten on 24/01/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//

#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);

#endif //CLOX_DEBUG_H
