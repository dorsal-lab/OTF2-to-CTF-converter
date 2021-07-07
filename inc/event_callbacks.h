/*
 *Copyright (c) 2021 Ecole Polytechnique de Montreal
 * All rights reserved.
 *
 *This source code is licensed under the BSD-style license found in the
 *LICENSE file in the root directory of this source tree. 
 */

#ifndef _EVENT_CALLBACKS_H
#define _EVENT_CALLBACKS_H

#include <stdint.h>
#include <otf2/otf2.h>

// OTF2_CallbackCode Enter_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t event_position,
//                     void *userData,
//                     OTF2_AttributeList *attributes,
//                     OTF2_RegionRef region);

// OTF2_CallbackCode Leave_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t event_position,
//                     void *userData,
//                     OTF2_AttributeList *attributes,
//                     OTF2_RegionRef region);

// OTF2_CallbackCode MpiSend_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time, uint64_t event_position,
//                     void *userData,
//                     OTF2_AttributeList *attributes,
//                     uint32_t receiver,
//                     OTF2_CommRef communicator,
//                     uint32_t msgTag,
//                     uint64_t msgLength);

// OTF2_CallbackCode MpiIsend_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time, uint64_t event_position,
//                     void* userData,
//                     OTF2_AttributeList *attributes,
//                     uint32_t receiver,
//                     OTF2_CommRef communicator,
//                     uint32_t msgTag,
//                     uint64_t msgLength,
//                     uint64_t requestID);

// OTF2_CallbackCode MpiIsendComplete_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t eventPosition,
//                     void *userData,
//                     OTF2_AttributeList *attributeList,
//                     uint64_t requestID);

// OTF2_CallbackCode MpiIrecvRequest_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t eventPosition,
//                     void *userData,
//                     OTF2_AttributeList *attributeList,
//                     uint64_t requestID);                   

// OTF2_CallbackCode MpiRecv_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t event_position,
//                     void *userData,
//                     OTF2_AttributeList *attributes,
//                     uint32_t sender,
//                     OTF2_CommRef communicator,
//                     uint32_t msgTag,
//                     uint64_t msgLength);

// OTF2_CallbackCode MpiIrecv_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t event_position,
//                     void *userData,
//                     OTF2_AttributeList *attributes,
//                     uint32_t sender,
//                     OTF2_CommRef communicator,
//                     uint32_t msgTag,
//                     uint64_t msgLength,
//                     uint64_t requestID);

// OTF2_CallbackCode MpiRequestTest(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t eventPosition,
//                     void *userData,
//                     OTF2_AttributeList *attributeList,
//                     uint64_t requestID);

// OTF2_CallbackCode MpiRequestCancelled_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t eventPosition,
//                     void *userData,
//                     OTF2_AttributeList *attributeList,
//                     uint64_t requestID);
                
// OTF2_CallbackCode MpiCollectiveBegin_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t eventPosition,
//                     void *userData,
//                     OTF2_AttributeList *attributeList);

// OTF2_CallbackCode MpiCollectiveEnd_callback(OTF2_LocationRef location,
//                     OTF2_TimeStamp time,
//                     uint64_t eventPosition,
//                     void *userData,
//                     OTF2_AttributeList *attributeList,
//                     OTF2_CollectiveOp collectiveOp,
//                     OTF2_CommRef communicator,
//                     uint32_t root,
//                     uint64_t sizeSent,
//                     uint64_t sizeReceived);                   

void set_events_callbacks(OTF2_EvtReaderCallbacks *event_callbacks);

#endif
