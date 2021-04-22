#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <otf2/otf2.h>
#include "barectf-platform-linux-fs.h"
#include "barectf.h" 
#include "event_callbacks.h"
#include "utilities_functions.h"

//Enter region event callback
OTF2_CallbackCode Enter_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    OTF2_RegionRef region){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    barectf_trace_Event_Enter(user_data->ctx, location, region);
    return OTF2_CALLBACK_SUCCESS;
}


//Leave region event callback
OTF2_CallbackCode Leave_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    OTF2_RegionRef region){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    barectf_trace_Event_Leave(user_data->ctx, location, region);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi send event callback
OTF2_CallbackCode MpiSend_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time, uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList *attributes,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    barectf_trace_Event_MpiSend(user_data->ctx, location, receiver, communicator, msgTag, msgLength);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi Isend event callback
OTF2_CallbackCode MpiIsend_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time, uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength,
                    uint64_t requestID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
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
    barectf_trace_Event_MpiIrecvRequest(user_data->ctx, location, requestID);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi recv event callback
OTF2_CallbackCode MpiRecv_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time, uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList *attributes,
                    uint32_t sender,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    barectf_trace_Event_MpiRecv(user_data->ctx, location, sender, communicator, msgTag, msgLength);
    return OTF2_CALLBACK_SUCCESS;
}

//Mpi Irecv event callback
OTF2_CallbackCode MpiIrecv_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time, uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength,
                    uint64_t requestID){
    user_data_t *user_data = (user_data_t*)userData;
    *(user_data->clock_address) = time;
    barectf_trace_Event_MpiIrecv(user_data->ctx, location, receiver, communicator, msgTag, msgLength, requestID);
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
    barectf_trace_Event_MpiCollectiveEnd(user_data->ctx, location, collectiveOp, communicator, root, sizeSent, sizeReceived);
    return OTF2_CALLBACK_SUCCESS;
}

//Function that set all event callbacks to an OTF2 event reader callbacks object
void set_events_callbacks(OTF2_EvtReaderCallbacks *event_callbacks){
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
}
