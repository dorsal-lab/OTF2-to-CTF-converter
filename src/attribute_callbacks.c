/******************************************************
 * Copyright (c) 2021 Ecole Polytechnique de Montreal
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. 
 ******************************************************/

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

void trace_event_attribute(user_data_t *userData, OTF2_AttributeRef attribute, OTF2_Type type, OTF2_AttributeValue value){
    switch(type){
        case OTF2_TYPE_UINT8 :
            barectf_trace_EventAttribute_UInt8(userData->ctx, attribute, value.uint8);      
            break;
        case OTF2_TYPE_UINT16 :
            barectf_trace_EventAttribute_UInt16(userData->ctx, attribute, value.uint16);
            break;
        case OTF2_TYPE_UINT32 :
            barectf_trace_EventAttribute_UInt32(userData->ctx, attribute, value.uint32);
            break;
        case OTF2_TYPE_UINT64 :
            barectf_trace_EventAttribute_UInt64(userData->ctx, attribute, value.uint64);
            break;
        case OTF2_TYPE_INT8 :
            barectf_trace_EventAttribute_Int8(userData->ctx, attribute, value.int8);
            break;
        case OTF2_TYPE_INT16 :
            barectf_trace_EventAttribute_Int16(userData->ctx, attribute, value.int16);
            break;
        case OTF2_TYPE_INT32 :
            barectf_trace_EventAttribute_Int32(userData->ctx, attribute, value.int32);
            break;
        case OTF2_TYPE_INT64 :
            barectf_trace_EventAttribute_Int64(userData->ctx, attribute, value.int64);
            break;
        case OTF2_TYPE_FLOAT :
            barectf_trace_EventAttribute_Float(userData->ctx, attribute, value.float32);
            break;
        case OTF2_TYPE_DOUBLE :
            barectf_trace_EventAttribute_Double(userData->ctx, attribute, value.float64);
            break;
        case OTF2_TYPE_STRING :
            barectf_trace_EventAttribute_String(userData->ctx, attribute, value.stringRef);
            break;
        case OTF2_TYPE_ATTRIBUTE :
            barectf_trace_EventAttribute_Attribute(userData->ctx, attribute, value.attributeRef);
            break;
        case OTF2_TYPE_LOCATION :
            barectf_trace_EventAttribute_Location(userData->ctx, attribute, value.locationRef);
            break;
        case OTF2_TYPE_REGION :
            barectf_trace_EventAttribute_Region(userData->ctx, attribute, value.regionRef);
            break;
        case OTF2_TYPE_GROUP :
            barectf_trace_EventAttribute_Group(userData->ctx, attribute, value.groupRef);
            break;
        case OTF2_TYPE_METRIC :
            barectf_trace_EventAttribute_Metric(userData->ctx, attribute, value.metricRef);
            break;
        case OTF2_TYPE_COMM :
            barectf_trace_EventAttribute_Comm(userData->ctx, attribute, value.commRef);
            break;
        case OTF2_TYPE_PARAMETER :
            barectf_trace_EventAttribute_Parameter(userData->ctx, attribute, value.parameterRef);
            break;
        case OTF2_TYPE_RMA_WIN :
            barectf_trace_EventAttribute_RmaWin(userData->ctx, attribute, value.rmaWinRef);
            break;
        case OTF2_TYPE_SOURCE_CODE_LOCATION :
            barectf_trace_EventAttribute_SourceCodeLocation(userData->ctx, attribute, value.sourceCodeLocationRef);
            break;
        case OTF2_TYPE_CALLING_CONTEXT :
            barectf_trace_EventAttribute_CallingContext(userData->ctx, attribute, value.callingContextRef);
            break;
        case OTF2_TYPE_INTERRUPT_GENERATOR :
            barectf_trace_EventAttribute_InterruptGenerator(userData->ctx, attribute, value.interruptGeneratorRef);
            break;
        case OTF2_TYPE_IO_FILE :
            barectf_trace_EventAttribute_IoFile(userData->ctx, attribute, value.ioFileRef);
            break;
        case OTF2_TYPE_IO_HANDLE :
            barectf_trace_EventAttribute_IoHandle(userData->ctx, attribute, value.ioHandleRef);
            break;
        case OTF2_TYPE_LOCATION_GROUP :
            barectf_trace_EventAttribute_LocationGroup(userData->ctx, attribute, value.locationGroupRef);
            break;
    }
}

void trace_attribute_list(user_data_t *userData, OTF2_AttributeList *attributeList){
    OTF2_AttributeRef attribute;
    OTF2_Type type; 
    OTF2_AttributeValue value;
    uint32_t numberOfAttributes = OTF2_AttributeList_GetNumberOfElements(attributeList);
    for(uint32_t i = 0; i < numberOfAttributes; i++){
        OTF2_AttributeList_PopAttribute(attributeList, &attribute, &type, &value);
        trace_event_attribute(userData, attribute, type, value);
    }
}

void trace_one_metric(user_data_t *userData, OTF2_LocationRef self, OTF2_MetricRef metric, uint8_t index, const OTF2_Type typeID, const OTF2_MetricValue metricValue){
    switch(typeID){
        case OTF2_TYPE_INT64:
            barectf_trace_MetricValue_Int64(userData->ctx, self, metric, index, metricValue.signed_int);
            break;
        case OTF2_TYPE_UINT64:
            barectf_trace_MetricValue_UInt64(userData->ctx, self, metric, index, metricValue.unsigned_int);
            break;
        case OTF2_TYPE_DOUBLE:
            barectf_trace_MetricValue_Double(userData->ctx, self, metric, index, metricValue.floating_point);
            break;
    }
}

void trace_metrics(user_data_t *userData, OTF2_LocationRef self, OTF2_MetricRef metric, uint8_t numberOfMetrics, const OTF2_Type *typeIDs, const OTF2_MetricValue *metricValues){
    for(uint8_t i = 0; i < numberOfMetrics; i++){
        trace_one_metric(userData, self, metric, i, typeIDs[i], metricValues[i]);
    }
}

void trace_program_arguments(user_data_t *userData, uint32_t numberOfArguments, const OTF2_StringRef *programArguments){
    for(uint32_t i = 0; i < numberOfArguments; i++){
        barectf_trace_Event_ProgramArgument(userData->ctx, programArguments[i]);
    }
}
