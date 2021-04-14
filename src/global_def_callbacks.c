#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <otf2/otf2.h>
#include "barectf-platform-linux-fs.h"
#include "barectf.h" 
#include "datatypes.h"
#include "global_def_callbacks.h"

#define OTF2_CALL(call) if(call != OTF2_SUCCESS) {printf("OTF2 error : %s\n", OTF2_Error_GetDescription(call)); abort();}

//SystemTreeNode global definition callback
OTF2_CallbackCode GlobalDef_SystemTreeNode_callback(void* userData,
                    OTF2_SystemTreeNodeRef self,
                    OTF2_StringRef name,
                    OTF2_StringRef className,
                    OTF2_SystemTreeNodeRef systemTreeParent){
    user_data_t* user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_SystemTreeNode(user_data->ctx, self, name, className, systemTreeParent);
    return OTF2_CALLBACK_SUCCESS;
}

//LocationGroup global definition callback
OTF2_CallbackCode GlobalDef_LocationGroup_callback(void* userData,
                    OTF2_LocationGroupRef self,
                    OTF2_StringRef name,
                    OTF2_LocationGroupType locationGroupType,
                    OTF2_SystemTreeNodeRef systemTreeParent){
    user_data_t* user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_LocationGroup(user_data->ctx, self, name, locationGroupType, systemTreeParent);
    return OTF2_CALLBACK_SUCCESS;
}

//Location global definition callback
OTF2_CallbackCode GlobalDef_Location_callback(void* userData,
                    OTF2_LocationRef self,
                    OTF2_StringRef name,
                    OTF2_LocationType locationType,
                    uint64_t numberOfEvents,
                    OTF2_LocationGroupRef locationGroup){
    user_data_t* user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Location(user_data->ctx, self, name, locationType, numberOfEvents, locationGroup);
    return OTF2_CALLBACK_SUCCESS;
}

//String global definition callback
OTF2_CallbackCode GlobalDef_String_callback(void * userData,
                    OTF2_StringRef self,
                    const char* string){
    user_data_t* user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_String(user_data->ctx, self, string);
    return OTF2_CALLBACK_SUCCESS;
}

//Region global definition callback
OTF2_CallbackCode GlobalDef_Region_callback(void * userData,
                    OTF2_RegionRef self,
                    OTF2_StringRef name,
                    OTF2_StringRef canonicalName,
                    OTF2_StringRef description,
                    OTF2_RegionRole regionRole,
                    OTF2_Paradigm paradigm,
                    OTF2_RegionFlag regionFlags,
                    OTF2_StringRef sourceFile,
                    uint32_t beginLineNumber,
                    uint32_t endLineNumber){
    user_data_t* user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Region(user_data->ctx, 
        self, 
        name, 
        canonicalName, 
        description,
        regionRole,
        paradigm,
        regionFlags,
        sourceFile,
        beginLineNumber,
        endLineNumber);
    return OTF2_CALLBACK_SUCCESS;
}

//Function that set all global definitions callbacks to an OTF2 global definition reader callbacks object
void set_global_def_callbacks(OTF2_GlobalDefReaderCallbacks* global_def_callbacks){
    OTF2_CALL(OTF2_GlobalDefReaderCallbacks_SetSystemTreeNodeCallback(global_def_callbacks,
                                                            &GlobalDef_SystemTreeNode_callback));   

    OTF2_CALL(OTF2_GlobalDefReaderCallbacks_SetLocationGroupCallback(global_def_callbacks,
                                                            &GlobalDef_LocationGroup_callback));   

    OTF2_CALL(OTF2_GlobalDefReaderCallbacks_SetLocationCallback(global_def_callbacks,
                                                            &GlobalDef_Location_callback));   

    OTF2_CALL(OTF2_GlobalDefReaderCallbacks_SetStringCallback(global_def_callbacks,
                                                            &GlobalDef_String_callback));

    OTF2_CALL(OTF2_GlobalDefReaderCallbacks_SetRegionCallback(global_def_callbacks,
                                                            &GlobalDef_Region_callback));      
}
