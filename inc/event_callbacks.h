#include <stdint.h>
#include <otf2/otf2.h>

OTF2_CallbackCode Enter_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList* attributes,
                    OTF2_RegionRef region);

OTF2_CallbackCode Leave_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList* attributes,
                    OTF2_RegionRef region);

OTF2_CallbackCode MpiSend_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time, uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList* attributes,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength);

OTF2_CallbackCode MpiIsend_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time, uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList* attributes,
                    uint32_t receiver,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength,
                    uint64_t requestID);

OTF2_CallbackCode MpiRecv_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList* attributes,
                    uint32_t sender,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength);

OTF2_CallbackCode MpiIrecv_callback(OTF2_LocationRef location,
                    OTF2_TimeStamp time,
                    uint64_t event_position,
                    void* userData,
                    OTF2_AttributeList* attributes,
                    uint32_t sender,
                    OTF2_CommRef communicator,
                    uint32_t msgTag,
                    uint64_t msgLength,
                    uint64_t requestID);

void set_events_callbacks(OTF2_EvtReaderCallbacks* event_callbacks);