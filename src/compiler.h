//
//  compiler.h
//  clox
//
//  Created by Maarten on 01/02/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//

#ifndef compiler_h
#define compiler_h

#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#endif /* compiler_h */
