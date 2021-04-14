#include <stdint.h>
#include <otf2/otf2.h>

OTF2_CallbackCode Enter_callback(OTF2_LocationRef location, OTF2_TimeStamp time, uint64_t event_position, void* userData, OTF2_AttributeList* attributes, OTF2_RegionRef region);
OTF2_CallbackCode Leave_callback(OTF2_LocationRef location, OTF2_TimeStamp time, uint64_t event_position, void* userData, OTF2_AttributeList* attributes, OTF2_RegionRef region);

void set_events_callbacks(OTF2_EvtReaderCallbacks* event_callbacks);