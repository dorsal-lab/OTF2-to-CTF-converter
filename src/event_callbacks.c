/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 Yoann Heitz
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <otf2/otf2.h>
#include "barectf-platform-linux-fs.h"
#include "barectf.h" 
#include "event_callbacks.h"
#include "utilities_functions.h"
#include "attribute_callbacks.h"

//BufferFlush event callback
OTF2_CallbackCode BufferFlush_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_TimeStamp stopTime){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_BufferFlush(user_data->ctx, location, stopTime);
    return OTF2_CALLBACK_SUCCESS;
}

//MeasurementOnOff event callback
OTF2_CallbackCode MeasurementOnOff_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_MeasurementMode measurementMode){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MeasurementOnOff(user_data->ctx, location, measurementMode);
    return OTF2_CALLBACK_SUCCESS;
}

//Enter region event callback
OTF2_CallbackCode Enter_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RegionRef region){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_Enter(user_data->ctx, location, region);
    return OTF2_CALLBACK_SUCCESS;
}

//Leave region event callback
OTF2_CallbackCode Leave_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RegionRef region){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_Leave(user_data->ctx, location, region);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi send event callback
OTF2_CallbackCode MpiSend_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList *attributeList,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiSend(user_data->ctx, location, receiver, communicator, msgTag, msgLength);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi Isend event callback
OTF2_CallbackCode MpiIsend_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength,
                    uint64_t requestID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiIsend(user_data->ctx, location, receiver, communicator, msgTag, msgLength, requestID);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi IsendComplete event callback
OTF2_CallbackCode MpiIsendComplete_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t requestID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiIsendComplete(user_data->ctx, location, requestID);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi IrecvRequest event callback
OTF2_CallbackCode MpiIrecvRequest_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t requestID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiIrecvRequest(user_data->ctx, location, requestID);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi recv event callback
OTF2_CallbackCode MpiRecv_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList *attributeList,
                    uint32_t sender,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiRecv(user_data->ctx, location, sender, communicator, msgTag, msgLength);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi Irecv event callback
OTF2_CallbackCode MpiIrecv_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint32_t sender,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength,
                    uint64_t requestID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiIrecv(user_data->ctx, location, sender, communicator, msgTag, msgLength, requestID);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi RequestTest event callback
OTF2_CallbackCode MpiRequestTest_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t requestID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiRequestTest(user_data->ctx, location, requestID);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi RequestCancelled event callback
OTF2_CallbackCode MpiRequestCancelled_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t requestID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiRequestCancelled(user_data->ctx, location, requestID);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi CollectiveBegin event callback
OTF2_CallbackCode MpiCollectiveBegin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiCollectiveBegin(user_data->ctx, location);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi CollectiveEnd event callback
OTF2_CallbackCode MpiCollectiveEnd_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CollectiveOp collectiveOp,
                    OTF2_CommRef communicator,
                    uint32_t root,
                    uint64_t sizeSent,
                    uint64_t sizeReceived){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_MpiCollectiveEnd(user_data->ctx, location, collectiveOp, communicator, root, sizeSent, sizeReceived);
    return OTF2_CALLBACK_SUCCESS;
}

//OmpFork event callback
OTF2_CallbackCode OmpFork_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint32_t numberOfRequestedThreads){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_OmpFork(user_data->ctx, location, numberOfRequestedThreads);
    return OTF2_CALLBACK_SUCCESS;
}

//OmpJoin event callback
OTF2_CallbackCode OmpJoin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_OmpJoin(user_data->ctx, location);
    return OTF2_CALLBACK_SUCCESS;
}

//OmpAcquireLock event callback
OTF2_CallbackCode OmpAcquireLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint32_t lockID,
                    uint32_t acquisitionOrder){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_OmpAcquireLock(user_data->ctx, location, lockID, acquisitionOrder);
    return OTF2_CALLBACK_SUCCESS;
}

//OmpReleaseLock event callback
OTF2_CallbackCode OmpReleaseLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint32_t lockID,
                    uint32_t acquisitionOrder){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_OmpReleaseLock(user_data->ctx, location, lockID, acquisitionOrder);
    return OTF2_CALLBACK_SUCCESS;
}

//OmpTaskCreate event callback
OTF2_CallbackCode OmpTaskCreate_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t taskID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_OmpTaskCreate(user_data->ctx, location, taskID);
    return OTF2_CALLBACK_SUCCESS;
}

//OmpTaskSwitch event callback
OTF2_CallbackCode OmpTaskSwitch_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t taskID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_OmpTaskSwitch(user_data->ctx, location, taskID);
    return OTF2_CALLBACK_SUCCESS;
}

//OmpTaskComplete event callback
OTF2_CallbackCode OmpTaskComplete_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t taskID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_OmpTaskComplete(user_data->ctx, location, taskID);
    return OTF2_CALLBACK_SUCCESS;
}

//Metric event callback
OTF2_CallbackCode Metric_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_MetricRef metric,
                    uint8_t numberOfMetrics,
                    const OTF2_Type *typeIDs,
                    const OTF2_MetricValue *metricValues){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    barectf_trace_Event_Metric(user_data->ctx, location, metric, numberOfMetrics);
    trace_attribute_list(user_data, attributeList);
    trace_metrics(user_data, location, metric, numberOfMetrics, typeIDs, metricValues);
    return OTF2_CALLBACK_SUCCESS;
}

//ParameterString event callback
OTF2_CallbackCode ParameterString_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_ParameterRef parameter,
                    OTF2_StringRef string){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ParameterString(user_data->ctx, location, parameter, string);
    return OTF2_CALLBACK_SUCCESS;
}

//ParameterInt event callback
OTF2_CallbackCode ParameterInt_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_ParameterRef parameter,
                    int64_t value){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ParameterInt(user_data->ctx, location, parameter, value);
    return OTF2_CALLBACK_SUCCESS;
}

//ParameterUnsignedInt event callback
OTF2_CallbackCode ParameterUnsignedInt_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_ParameterRef parameter,
                    uint64_t value){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ParameterUnsignedInt(user_data->ctx, location, parameter, value);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaWinCreate event callback
OTF2_CallbackCode RmaWinCreate_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaWinCreate(user_data->ctx, location, win);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaWinDestroy event callback
OTF2_CallbackCode RmaWinDestroy_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaWinDestroy(user_data->ctx, location, win);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaCollectiveBegin event callback
OTF2_CallbackCode RmaCollectiveBegin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaCollectiveBegin(user_data->ctx, location);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaCollectiveEnd event callback
OTF2_CallbackCode RmaCollectiveEnd_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CollectiveOp collectiveOp,
                    OTF2_RmaSyncLevel syncLevel,
                    OTF2_RmaWinRef win,
                    uint32_t root,
                    uint64_t bytesSent,
                    uint64_t bytesReceived){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaCollectiveEnd(user_data->ctx, location, collectiveOp, syncLevel, win, root, bytesSent, bytesReceived);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaGroupSync event callback
OTF2_CallbackCode RmaGroupSync_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaSyncLevel syncLevel,
                    OTF2_RmaWinRef win,
                    OTF2_GroupRef group){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaGroupSync(user_data->ctx, location, syncLevel, win, group);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaRequestLock event callback
OTF2_CallbackCode RmaRequestLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint32_t remote,
                    uint64_t lockId,
                    OTF2_LockType lockType){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaRequestLock(user_data->ctx, location, win, remote, lockId, lockType);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaAcquireLock event callback
OTF2_CallbackCode RmaAcquireLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint32_t remote,
                    uint64_t lockId,
                    OTF2_LockType lockType){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaAcquireLock(user_data->ctx, location, win, remote, lockId, lockType);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaTryLock event callback
OTF2_CallbackCode RmaTryLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint32_t remote,
                    uint64_t lockId,
                    OTF2_LockType lockType){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaTryLock(user_data->ctx, location, win, remote, lockId, lockType);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaReleaseLock event callback
OTF2_CallbackCode RmaReleaseLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint32_t remote,
                    uint64_t lockId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaReleaseLock(user_data->ctx, location, win, remote, lockId);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaSync event callback
OTF2_CallbackCode RmaSync_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint32_t remote,
                    OTF2_RmaSyncType syncType){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaSync(user_data->ctx, location, win, remote, syncType);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaWaitChange event callback
OTF2_CallbackCode RmaWaitChange_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaWaitChange(user_data->ctx, location, win);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaPut event callback
OTF2_CallbackCode RmaPut_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint32_t remote,
                    uint64_t bytes,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaPut(user_data->ctx, location, win, remote, bytes, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaGet event callback
OTF2_CallbackCode RmaGet_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint32_t remote,
                    uint64_t bytes,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaGet(user_data->ctx, location, win, remote, bytes, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaAtomic event callback
OTF2_CallbackCode RmaAtomic_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint32_t remote,
                    OTF2_RmaAtomicType type,
                    uint64_t bytesSent,
                    uint64_t bytesReceived,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaAtomic(user_data->ctx, location, win, remote, type, bytesSent, bytesReceived, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaOpCompleteBlocking event callback
OTF2_CallbackCode RmaOpCompleteBlocking_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaOpCompleteBlocking(user_data->ctx, location, win, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaOpCompleteNonBlocking event callback
OTF2_CallbackCode RmaOpCompleteNonBlocking_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaOpCompleteNonBlocking(user_data->ctx, location, win, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaOpTest event callback
OTF2_CallbackCode RmaOpTest_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaOpTest(user_data->ctx, location, win, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaOpCompleteRemote event callback
OTF2_CallbackCode RmaOpCompleteRemote_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_RmaWinRef win,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_RmaOpCompleteRemote(user_data->ctx, location, win, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadFork event callback
OTF2_CallbackCode ThreadFork_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_Paradigm model,
                    uint32_t numberOfRequestedThreads){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadFork(user_data->ctx, location, model, numberOfRequestedThreads);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadJoin event callback
OTF2_CallbackCode ThreadJoin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_Paradigm model){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadJoin(user_data->ctx, location, model);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadTeamBegin event callback
OTF2_CallbackCode ThreadTeamBegin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadTeam){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadTeamBegin(user_data->ctx, location, threadTeam);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadTeamEnd event callback
OTF2_CallbackCode ThreadTeamEnd_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadTeam){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadTeamEnd(user_data->ctx, location, threadTeam);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadAcquireLock event callback
OTF2_CallbackCode ThreadAcquireLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_Paradigm model,
                    uint32_t lockID, 
                    uint32_t acquisitionOrder){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadAcquireLock(user_data->ctx, location, model, lockID, acquisitionOrder);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadReleaseLock event callback
OTF2_CallbackCode ThreadReleaseLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_Paradigm model,
                    uint32_t lockID, 
                    uint32_t acquisitionOrder){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadAcquireLock(user_data->ctx, location, model, lockID, acquisitionOrder);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadTaskCreate event callback
OTF2_CallbackCode ThreadTaskCreate_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadTeam,
                    uint32_t creatingThread,
                    uint32_t generationNumber){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadTaskCreate(user_data->ctx, location, threadTeam, creatingThread, generationNumber);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadTaskSwitch event callback
OTF2_CallbackCode ThreadTaskSwitch_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadTeam,
                    uint32_t creatingThread,
                    uint32_t generationNumber){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadTaskSwitch(user_data->ctx, location, threadTeam, creatingThread, generationNumber);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadTaskComplete event callback
OTF2_CallbackCode ThreadTaskComplete_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadTeam,
                    uint32_t creatingThread,
                    uint32_t generationNumber){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadTaskComplete(user_data->ctx, location, threadTeam, creatingThread, generationNumber);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadCreate event callback
OTF2_CallbackCode ThreadCreate_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadContingent,
                    uint64_t sequenceCount){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadCreate(user_data->ctx, location, threadContingent, sequenceCount);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadBegin event callback
OTF2_CallbackCode ThreadBegin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadContingent,
                    uint64_t sequenceCount){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadBegin(user_data->ctx, location, threadContingent, sequenceCount);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadWait event callback
OTF2_CallbackCode ThreadWait_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadContingent,
                    uint64_t sequenceCount){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadWait(user_data->ctx, location, threadContingent, sequenceCount);
    return OTF2_CALLBACK_SUCCESS;
}

//ThreadEnd event callback
OTF2_CallbackCode ThreadEnd_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CommRef threadContingent,
                    uint64_t sequenceCount){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ThreadEnd(user_data->ctx, location, threadContingent, sequenceCount);
    return OTF2_CALLBACK_SUCCESS;
}

//CallingContextEnter event callback
OTF2_CallbackCode CallingContextEnter_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CallingContextRef callingContext,
                    uint32_t unwindDistance){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_CallingContextEnter(user_data->ctx, location, callingContext, unwindDistance);
    return OTF2_CALLBACK_SUCCESS;
}

//CallingContextLeave event callback
OTF2_CallbackCode CallingContextLeave_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CallingContextRef callingContext){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_CallingContextLeave(user_data->ctx, location, callingContext);
    return OTF2_CALLBACK_SUCCESS;
}

//CallingContextSample event callback
OTF2_CallbackCode CallingContextSample_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CallingContextRef callingContext,
                    uint32_t unwindDistance,
                    OTF2_InterruptGeneratorRef interruptGenerator){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_CallingContextSample(user_data->ctx, location, callingContext, unwindDistance, interruptGenerator);
    return OTF2_CALLBACK_SUCCESS;
}

//IoCreateHandle event callback
OTF2_CallbackCode IoCreateHandle_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    OTF2_IoAccessMode mode,
                    OTF2_IoCreationFlag creationFlags,
                    OTF2_IoStatusFlag statusFlags){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoCreateHandle(user_data->ctx, location, handle, mode, creationFlags, statusFlags);
    return OTF2_CALLBACK_SUCCESS;
}

//IoDestroyHandle event callback
OTF2_CallbackCode IoDestroyHandle_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoDestroyHandle(user_data->ctx, location, handle);
    return OTF2_CALLBACK_SUCCESS;
}

//IoDuplicateHandle event callback
OTF2_CallbackCode IoDuplicateHandle_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef oldHandle,
                    OTF2_IoHandleRef newHandle,
                    OTF2_IoStatusFlag statusFlags){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoDuplicateHandle(user_data->ctx, location, oldHandle, newHandle, statusFlags);
    return OTF2_CALLBACK_SUCCESS;
}

//IoSeek event callback
OTF2_CallbackCode IoSeek_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    int64_t offsetRequest,
                    OTF2_IoSeekOption whence,
                    uint64_t offsetResult){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoSeek(user_data->ctx, location, handle, offsetRequest, whence, offsetResult);
    return OTF2_CALLBACK_SUCCESS;
}

//IoChangeStatusFlags event callback
OTF2_CallbackCode IoChangeStatusFlags_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    OTF2_IoStatusFlag statusFlags){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoChangeStatusFlags(user_data->ctx, location, handle, statusFlags);
    return OTF2_CALLBACK_SUCCESS;
}

//IoDeleteFile event callback
OTF2_CallbackCode IoDeleteFile_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoParadigmRef ioParadigm,
                    OTF2_IoFileRef file){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoDeleteFile(user_data->ctx, location, ioParadigm, file);
    return OTF2_CALLBACK_SUCCESS;
}

//IoOperationBegin event callback
OTF2_CallbackCode IoOperationBegin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    OTF2_IoOperationMode mode,
                    OTF2_IoOperationFlag operationFlags,
                    uint64_t bytesRequest,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoOperationBegin(user_data->ctx, location, handle, mode, operationFlags, bytesRequest, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//IoOperationTest event callback
OTF2_CallbackCode IoOperationTest_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoOperationTest(user_data->ctx, location, handle, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//IoOperationIssued event callback
OTF2_CallbackCode IoOperationIssued_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoOperationIssued(user_data->ctx, location, handle, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//IoOperationComplete event callback
OTF2_CallbackCode IoOperationComplete_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    uint64_t bytesResult,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoOperationComplete(user_data->ctx, location, handle, bytesResult, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//IoOperationCancelled event callback
OTF2_CallbackCode IoOperationCancelled_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    uint64_t matchingId){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoOperationCancelled(user_data->ctx, location, handle, matchingId);
    return OTF2_CALLBACK_SUCCESS;
}

//IoAcquireLock event callback
OTF2_CallbackCode IoAcquireLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    OTF2_LockType lockType){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoAcquireLock(user_data->ctx, location, handle, lockType);
    return OTF2_CALLBACK_SUCCESS;
}

//IoReleaseLock event callback
OTF2_CallbackCode IoReleaseLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    OTF2_LockType lockType){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoReleaseLock(user_data->ctx, location, handle, lockType);
    return OTF2_CALLBACK_SUCCESS;
}

//IoTryLock event callback
OTF2_CallbackCode IoTryLock_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_IoHandleRef handle,
                    OTF2_LockType lockType){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_IoTryLock(user_data->ctx, location, handle, lockType);
    return OTF2_CALLBACK_SUCCESS;
}

//ProgramBegin event callback
OTF2_CallbackCode ProgramBegin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_StringRef programName,
                    uint32_t numberOfArguments,
                    const OTF2_StringRef *programArguments){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    trace_program_arguments(user_data, numberOfArguments, programArguments);
    barectf_trace_Event_ProgramBegin(user_data->ctx, location, programName);
    return OTF2_CALLBACK_SUCCESS;
}

//ProgramEnd event callback
OTF2_CallbackCode ProgramEnd_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    int64_t exitStatus){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    trace_attribute_list(user_data, attributeList);
    barectf_trace_Event_ProgramEnd(user_data->ctx, location, exitStatus);
    return OTF2_CALLBACK_SUCCESS;
}


//Function that set all event callbacks to an OTF2 event reader callbacks object
void set_events_callbacks(OTF2_EvtReaderCallbacks *event_callbacks){
    OTF2_Call(OTF2_EvtReaderCallbacks_SetBufferFlushCallback(event_callbacks,
                                                    &BufferFlush_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMeasurementOnOffCallback(event_callbacks,
                                                    &MeasurementOnOff_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetEnterCallback(event_callbacks,
                                                    &Enter_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetLeaveCallback(event_callbacks,
                                                    &Leave_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiSendCallback(event_callbacks,
                                                    &MpiSend_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiIsendCallback(event_callbacks,
                                                    &MpiIsend_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiIsendCompleteCallback(event_callbacks,
                                                    &MpiIsendComplete_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiIrecvRequestCallback(event_callbacks,
                                                    &MpiIrecvRequest_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiRecvCallback(event_callbacks,
                                                    &MpiRecv_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiIrecvCallback(event_callbacks,
                                                    &MpiIrecv_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiRequestTestCallback(event_callbacks,
                                                    &MpiRequestTest_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiRequestCancelledCallback(event_callbacks,
                                                    &MpiRequestCancelled_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiCollectiveBeginCallback(event_callbacks,
                                                    &MpiCollectiveBegin_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMpiCollectiveEndCallback(event_callbacks,
                                                    &MpiCollectiveEnd_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetOmpForkCallback(event_callbacks,
                                                    &OmpFork_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetOmpJoinCallback(event_callbacks,
                                                    &OmpJoin_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetOmpAcquireLockCallback(event_callbacks,
                                                    &OmpAcquireLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetOmpReleaseLockCallback(event_callbacks,
                                                    &OmpReleaseLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetOmpTaskCreateCallback(event_callbacks,
                                                    &OmpTaskCreate_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetOmpTaskSwitchCallback(event_callbacks,
                                                    &OmpTaskSwitch_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetOmpTaskCompleteCallback(event_callbacks,
                                                    &OmpTaskComplete_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetMetricCallback(event_callbacks,
                                                    &Metric_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetParameterStringCallback(event_callbacks,
                                                    &ParameterString_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetParameterIntCallback(event_callbacks,
                                                    &ParameterInt_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetParameterUnsignedIntCallback(event_callbacks,
                                                    &ParameterUnsignedInt_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaWinCreateCallback(event_callbacks,
                                                    &RmaWinCreate_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaWinDestroyCallback(event_callbacks,
                                                    &RmaWinDestroy_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaCollectiveBeginCallback(event_callbacks,
                                                    &RmaCollectiveBegin_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaCollectiveEndCallback(event_callbacks,
                                                    &RmaCollectiveEnd_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaGroupSyncCallback(event_callbacks,
                                                    &RmaGroupSync_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaRequestLockCallback(event_callbacks,
                                                    &RmaRequestLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaAcquireLockCallback(event_callbacks,
                                                    &RmaAcquireLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaTryLockCallback(event_callbacks,
                                                    &RmaTryLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaReleaseLockCallback(event_callbacks,
                                                    &RmaReleaseLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaSyncCallback(event_callbacks,
                                                    &RmaSync_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaWaitChangeCallback(event_callbacks,
                                                    &RmaWaitChange_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaPutCallback(event_callbacks,
                                                    &RmaPut_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaGetCallback(event_callbacks,
                                                    &RmaGet_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaAtomicCallback(event_callbacks,
                                                    &RmaAtomic_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaOpCompleteBlockingCallback(event_callbacks,
                                                    &RmaOpCompleteBlocking_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaOpCompleteNonBlockingCallback(event_callbacks,
                                                    &RmaOpCompleteNonBlocking_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaOpTestCallback(event_callbacks,
                                                    &RmaOpTest_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetRmaOpCompleteRemoteCallback(event_callbacks,
                                                    &RmaOpCompleteRemote_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadForkCallback(event_callbacks,
                                                    &ThreadFork_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadJoinCallback(event_callbacks,
                                                    &ThreadJoin_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadTeamBeginCallback(event_callbacks,
                                                    &ThreadTeamBegin_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadTeamEndCallback(event_callbacks,
                                                    &ThreadTeamEnd_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadAcquireLockCallback(event_callbacks,
                                                    &ThreadAcquireLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadReleaseLockCallback(event_callbacks,
                                                    &ThreadReleaseLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadTaskCreateCallback(event_callbacks,
                                                    &ThreadTaskCreate_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadTaskSwitchCallback(event_callbacks,
                                                    &ThreadTaskSwitch_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadTaskCompleteCallback(event_callbacks,
                                                    &ThreadTaskComplete_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadCreateCallback(event_callbacks,
                                                    &ThreadCreate_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadBeginCallback(event_callbacks,
                                                    &ThreadBegin_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadWaitCallback(event_callbacks,
                                                    &ThreadWait_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetThreadEndCallback(event_callbacks,
                                                    &ThreadEnd_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetCallingContextEnterCallback(event_callbacks,
                                                    &CallingContextEnter_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetCallingContextLeaveCallback(event_callbacks,
                                                    &CallingContextLeave_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetCallingContextSampleCallback(event_callbacks,
                                                    &CallingContextSample_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoCreateHandleCallback(event_callbacks,
                                                    &IoCreateHandle_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoDestroyHandleCallback(event_callbacks,
                                                    &IoDestroyHandle_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoDuplicateHandleCallback(event_callbacks,
                                                    &IoDuplicateHandle_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoSeekCallback(event_callbacks,
                                                    &IoSeek_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoChangeStatusFlagsCallback(event_callbacks,
                                                    &IoChangeStatusFlags_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoDeleteFileCallback(event_callbacks,
                                                    &IoDeleteFile_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoOperationBeginCallback(event_callbacks,
                                                    &IoOperationBegin_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoOperationTestCallback(event_callbacks,
                                                    &IoOperationTest_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoOperationIssuedCallback(event_callbacks,
                                                    &IoOperationIssued_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoOperationCompleteCallback(event_callbacks,
                                                    &IoOperationComplete_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoOperationCancelledCallback(event_callbacks,
                                                    &IoOperationCancelled_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoAcquireLockCallback(event_callbacks,
                                                    &IoAcquireLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoReleaseLockCallback(event_callbacks,
                                                    &IoReleaseLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetIoTryLockCallback(event_callbacks,
                                                    &IoTryLock_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetProgramBeginCallback(event_callbacks,
                                                    &ProgramBegin_callback));

    OTF2_Call(OTF2_EvtReaderCallbacks_SetProgramEndCallback(event_callbacks,
                                                    &ProgramEnd_callback));
}
