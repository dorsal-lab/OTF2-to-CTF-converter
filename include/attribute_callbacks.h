/******************************************************
 * Copyright (c) 2021 Ecole Polytechnique de Montreal
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 ******************************************************/

#ifndef _ATTRIBUTE_CALLBACKS_H
#define _ATTRIBUTE_CALLBACKS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "barectf-platform-linux-fs.h"
#include "barectf.h"
#include "utilities_functions.h"
#include <otf2/otf2.h>

void trace_global_def_attribute(user_data_t* userData, OTF2_Type type, OTF2_AttributeValue value);

void trace_attribute_list(user_data_t* userData, OTF2_AttributeList* attributeList);

void trace_metrics(user_data_t* userData, OTF2_LocationRef self, OTF2_MetricRef metric, uint8_t numberOfMetrics, const OTF2_Type* typeIDs, const OTF2_MetricValue* metricValues);

void trace_program_arguments(user_data_t* userData, uint32_t numberOfArguments, const OTF2_StringRef* programArguments);

#endif
