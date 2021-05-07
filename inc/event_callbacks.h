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
#include <otf2/otf2.h>

OTF2_CallbackCode Enter_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    OTF2_RegionRef region);

OTF2_CallbackCode Leave_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    OTF2_RegionRef region);

OTF2_CallbackCode MpiSend_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time, uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength);

OTF2_CallbackCode MpiIsend_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time, uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList *attributes,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength,
                    uint64_t requestID);

OTF2_CallbackCode MpiIsendComplete_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t requestID);

OTF2_CallbackCode MpiIrecvRequest_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t requestID);                   

OTF2_CallbackCode MpiRecv_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    uint32_t sender,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength);

OTF2_CallbackCode MpiIrecv_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void *userData,
                    OTF2_AttributeList *attributes,
                    uint32_t sender,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength,
                    uint64_t requestID);

OTF2_CallbackCode MpiRequestTest(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t requestID);

OTF2_CallbackCode MpiRequestCancelled_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    uint64_t requestID);
                
OTF2_CallbackCode MpiCollectiveBegin_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList);

OTF2_CallbackCode MpiCollectiveEnd_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t eventPosition,
                    void *userData,
                    OTF2_AttributeList *attributeList,
                    OTF2_CollectiveOp collectiveOp,
                    OTF2_CommRef communicator,
                    uint32_t root,
                    uint64_t sizeSent,
                    uint64_t sizeReceived);                   

void set_events_callbacks(OTF2_EvtReaderCallbacks *event_callbacks);