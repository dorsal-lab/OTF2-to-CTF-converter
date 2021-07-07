/*
 *Copyright (c) 2021 Ecole Polytechnique de Montreal
 * All rights reserved.
 *
 *This source code is licensed under the BSD-style license found in the
 *LICENSE file in the root directory of this source tree. 
 */

#ifndef _ATTRIBUTE_CALLBACKS_H
#define _ATTRIBUTE_CALLBACKS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <otf2/otf2.h>
#include "barectf-platform-linux-fs.h"
#include "barectf.h" 
#include "utilities_functions.h"

void trace_global_def_attribute(user_data_t *userData, OTF2_Type type, OTF2_AttributeValue value);

#endif
