//
//  compiler.c
//  clox
//
//  Created by Maarten on 01/02/2020.
//  Copyright © 2020 Maarten Lauwers. All rights reserved.
//

#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char* source) {
    initScanner(source);
}
