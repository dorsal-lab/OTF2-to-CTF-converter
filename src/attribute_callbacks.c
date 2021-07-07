/*
 *Copyright (c) 2021 Ecole Polytechnique de Montreal
 * All rights reserved.
 *
 *This source code is licensed under the BSD-style license found in the
 *LICENSE file in the root directory of this source tree. 
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <otf2/otf2.h>
#include "barectf-platform-linux-fs.h"
#include "barectf.h" 
#include "attribute_callbacks.h"
#include "utilities_functions.h"

void trace_global_def_attribute(user_data_t *userData, OTF2_Type type, OTF2_AttributeValue value){
    switch(type){
        case OTF2_TYPE_UINT8 :
            barectf_trace_GlobalDefAttribute_UInt8(userData->ctx, value.uint8);      
            break;
        case OTF2_TYPE_UINT16 :
            barectf_trace_GlobalDefAttribute_UInt16(userData->ctx, value.uint16);
            break;
        case OTF2_TYPE_UINT32 :
            barectf_trace_GlobalDefAttribute_UInt32(userData->ctx, value.uint32);
            break;
        case OTF2_TYPE_UINT64 :
            barectf_trace_GlobalDefAttribute_UInt64(userData->ctx, value.uint64);
            break;
        case OTF2_TYPE_INT8 :
            barectf_trace_GlobalDefAttribute_Int8(userData->ctx, value.int8);
            break;
        case OTF2_TYPE_INT16 :
            barectf_trace_GlobalDefAttribute_Int16(userData->ctx, value.int16);
            break;
        case OTF2_TYPE_INT32 :
            barectf_trace_GlobalDefAttribute_Int32(userData->ctx, value.int32);
            break;
        case OTF2_TYPE_INT64 :
            barectf_trace_GlobalDefAttribute_Int64(userData->ctx, value.int64);
            break;
        case OTF2_TYPE_FLOAT :
            barectf_trace_GlobalDefAttribute_Float(userData->ctx, value.float32);
            break;
        case OTF2_TYPE_DOUBLE :
            barectf_trace_GlobalDefAttribute_Double(userData->ctx, value.float64);
            break;
        case OTF2_TYPE_STRING :
            barectf_trace_GlobalDefAttribute_String(userData->ctx, value.stringRef);
            break;
        case OTF2_TYPE_ATTRIBUTE :
            barectf_trace_GlobalDefAttribute_Attribute(userData->ctx, value.attributeRef);
            break;
        case OTF2_TYPE_LOCATION :
            barectf_trace_GlobalDefAttribute_Location(userData->ctx, value.locationRef);
            break;
        case OTF2_TYPE_REGION :
            barectf_trace_GlobalDefAttribute_Region(userData->ctx, value.regionRef);
            break;
        case OTF2_TYPE_GROUP :
            barectf_trace_GlobalDefAttribute_Group(userData->ctx, value.groupRef);
            break;
        case OTF2_TYPE_METRIC :
            barectf_trace_GlobalDefAttribute_Metric(userData->ctx, value.metricRef);
            break;
        case OTF2_TYPE_COMM :
            barectf_trace_GlobalDefAttribute_Comm(userData->ctx, value.commRef);
            break;
        case OTF2_TYPE_PARAMETER :
            barectf_trace_GlobalDefAttribute_Parameter(userData->ctx, value.parameterRef);
            break;
        case OTF2_TYPE_RMA_WIN :
            barectf_trace_GlobalDefAttribute_RmaWin(userData->ctx, value.rmaWinRef);
            break;
        case OTF2_TYPE_SOURCE_CODE_LOCATION :
            barectf_trace_GlobalDefAttribute_SourceCodeLocation(userData->ctx, value.sourceCodeLocationRef);
            break;
        case OTF2_TYPE_CALLING_CONTEXT :
            barectf_trace_GlobalDefAttribute_CallingContext(userData->ctx, value.callingContextRef);
            break;
        case OTF2_TYPE_INTERRUPT_GENERATOR :
            barectf_trace_GlobalDefAttribute_InterruptGenerator(userData->ctx, value.interruptGeneratorRef);
            break;
        case OTF2_TYPE_IO_FILE :
            barectf_trace_GlobalDefAttribute_IoFile(userData->ctx, value.ioFileRef);
            break;
        case OTF2_TYPE_IO_HANDLE :
            barectf_trace_GlobalDefAttribute_IoHandle(userData->ctx, value.ioHandleRef);
            break;
    }
}