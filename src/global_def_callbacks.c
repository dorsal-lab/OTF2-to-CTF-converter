#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <otf2/otf2.h>
#include "barectf-platform-linux-fs.h"
#include "barectf.h" 
#include "global_def_callbacks.h"
#include "utilities_functions.h"

//SystemTreeNode global definition callback
OTF2_CallbackCode GlobalDef_SystemTreeNode_callback(void *userData,
                    OTF2_SystemTreeNodeRef self,
                    OTF2_StringRef name,
                    OTF2_StringRef className,
                    OTF2_SystemTreeNodeRef systemTreeParent){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_SystemTreeNode(user_data->ctx, self, name, className, systemTreeParent);
    return OTF2_CALLBACK_SUCCESS;
}

//LocationGroup global definition callback
OTF2_CallbackCode GlobalDef_LocationGroup_callback(void *userData,
                    OTF2_LocationGroupRef self,
                    OTF2_StringRef name,
                    OTF2_LocationGroupType locationGroupType,
                    OTF2_SystemTreeNodeRef systemTreeParent){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_LocationGroup(user_data->ctx, self, name, locationGroupType, systemTreeParent);
    return OTF2_CALLBACK_SUCCESS;
}

//Location global definition callback
OTF2_CallbackCode GlobalDef_Location_callback(void *userData,
                    OTF2_LocationRef self,
                    OTF2_StringRef name,
                    OTF2_LocationType locationType,
                    uint64_t numberOfEvents,
                    OTF2_LocationGroupRef locationGroup){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Location(user_data->ctx, self, name, locationType, numberOfEvents, locationGroup);
    return OTF2_CALLBACK_SUCCESS;
}

//String global definition callback
OTF2_CallbackCode GlobalDef_String_callback(void *userData,
                    OTF2_StringRef self,
                    const char *string){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_String(user_data->ctx, self, string);
    return OTF2_CALLBACK_SUCCESS;
}

//Region global definition callback
OTF2_CallbackCode GlobalDef_Region_callback(void *userData,
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
    user_data_t *user_data = (user_data_t*)userData;
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

//Group global definition callback
OTF2_CallbackCode GlobalDef_Group_callback(void *userData,
                    OTF2_GroupRef self,
                    OTF2_StringRef name,
                    OTF2_GroupType groupType,
                    OTF2_Paradigm paradigm,
                    OTF2_GroupFlag groupFlags,
                    uint32_t numberOfMembers,
                    const uint64_t *members){
    user_data_t *user_data = (user_data_t*)userData;
    uint64_t member = 0;
    if(numberOfMembers == 0){
        numberOfMembers = 1;
        members = &member;
    }
    barectf_trace_GlobalDef_Group(user_data->ctx, 
        self, 
        name, 
        groupType, 
        paradigm,
        groupFlags,
        numberOfMembers,
        members);
    return OTF2_CALLBACK_SUCCESS;
}

//Communicator global definition callback
OTF2_CallbackCode GlobalDef_Comm_callback(void *userData,
                    OTF2_CommRef self,
                    OTF2_StringRef name,
                    OTF2_GroupRef group,
                    OTF2_CommRef parent){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Comm(user_data->ctx, 
        self, 
        name, 
        group, 
        parent);
    return OTF2_CALLBACK_SUCCESS;
}

//Function that set all global definitions callbacks to an OTF2 global definition reader callbacks object
void set_global_def_callbacks(OTF2_GlobalDefReaderCallbacks *global_def_callbacks){
    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetSystemTreeNodeCallback(global_def_callbacks,
                                                            &GlobalDef_SystemTreeNode_callback));   

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetLocationGroupCallback(global_def_callbacks,
                                                            &GlobalDef_LocationGroup_callback));   

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetLocationCallback(global_def_callbacks,
                                                            &GlobalDef_Location_callback));   

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetStringCallback(global_def_callbacks,
                                                            &GlobalDef_String_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetRegionCallback(global_def_callbacks,
                                                            &GlobalDef_Region_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetGroupCallback(global_def_callbacks,
                                                            &GlobalDef_Group_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCommCallback(global_def_callbacks,
                                                            &GlobalDef_Comm_callback));                                                               

}
