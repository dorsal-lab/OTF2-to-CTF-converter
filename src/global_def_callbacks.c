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
#include "global_def_callbacks.h"
#include "utilities_functions.h"
#include "attribute_callbacks.h"

//Clock properties definition callback
OTF2_CallbackCode GlobalDef_ClockProperties_callback(void *userData,
                    uint64_t timerResolution,
                    uint64_t globalOffset,
                    uint64_t traceLength){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_ClockProperties(user_data->ctx, timerResolution, globalOffset, traceLength);
    return OTF2_CALLBACK_SUCCESS;
}

//Paradigm definition callback
OTF2_CallbackCode GlobalDef_Paradigm_callback(void *userData,
                    OTF2_Paradigm paradigm,
                    OTF2_StringRef name,
                    OTF2_ParadigmClass paradigmClass){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Paradigm(user_data->ctx, paradigm, name, paradigmClass);
    return OTF2_CALLBACK_SUCCESS;
}

//Paradigm property definition callback
OTF2_CallbackCode GlobalDef_ParadigmProperty_callback(void *userData,
                    OTF2_Paradigm paradigm,
                    OTF2_ParadigmProperty property,
                    OTF2_Type type,
                    OTF2_AttributeValue value){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_ParadigmProperty(user_data->ctx, paradigm, property);
    trace_global_def_attribute(user_data, type, value);
    return OTF2_CALLBACK_SUCCESS;
}

//IO Paradigm definition callback
OTF2_CallbackCode GlobalDef_IoParadigm_callback(void *userData,
                    OTF2_IoParadigmRef self,
                    OTF2_StringRef identification,
                    OTF2_StringRef name,
                    OTF2_IoParadigmClass ioParadigmClass,
                    OTF2_IoParadigmFlag ioParadigmFlags,
                    uint8_t numberOfProperties,
                    const OTF2_IoParadigmProperty *properties,
                    const OTF2_Type *types,
                    const OTF2_AttributeValue *values){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_IoParadigm(user_data->ctx, self, identification, name, ioParadigmClass, ioParadigmFlags, numberOfProperties);
    for(int i = 0; i++; i < numberOfProperties){
        barectf_trace_GlobalDef_IoParadigmProperty(user_data->ctx, self, properties[i]);
        trace_global_def_attribute(user_data, types[i], values[i]);
    }
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

//Attribute global definition callback
OTF2_CallbackCode GlobalDef_Attribute_callback(void *userData,
                    OTF2_AttributeRef self,
                    OTF2_StringRef name,
                    OTF2_StringRef description,
                    OTF2_Type type){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Attribute(user_data->ctx, self, name, description, type);
    return OTF2_CALLBACK_SUCCESS;
}

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
    barectf_trace_GlobalDef_Region(user_data->ctx, self, name, canonicalName, description, regionRole, paradigm, regionFlags, sourceFile, beginLineNumber, endLineNumber);
    return OTF2_CALLBACK_SUCCESS;
}

//Callsite global definition callback
OTF2_CallbackCode GlobalDef_Callsite_callback(void *userData,
                    OTF2_CallsiteRef self,
                    OTF2_StringRef sourceFile,
                    uint32_t lineNumber,
                    OTF2_RegionRef enteredRegion,
                    OTF2_RegionRef leftRegion){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Callsite(user_data->ctx, self, sourceFile, lineNumber, enteredRegion, leftRegion);
    return OTF2_CALLBACK_SUCCESS;
}

//Callpath global definition callback
OTF2_CallbackCode GlobalDef_Callpath_callback(void *userData,
                    OTF2_CallpathRef self,
                    OTF2_CallpathRef parent,
                    OTF2_RegionRef region){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Callpath(user_data->ctx, self, parent, region);
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
    
    barectf_trace_GlobalDef_Group(user_data->ctx, self, name, groupType, paradigm, groupFlags, numberOfMembers);
    for(uint32_t i = 0; i < numberOfMembers; i++){
        barectf_trace_GlobalDef_GroupMember(user_data->ctx, self, i, members[i]);
    }
    return OTF2_CALLBACK_SUCCESS;
}

//Metric member global definition callback
OTF2_CallbackCode GlobalDef_MetricMember_callback(void *userData,
                    OTF2_MetricMemberRef self,
                    OTF2_StringRef name,
                    OTF2_StringRef description,
                    OTF2_MetricType metricType,
                    OTF2_MetricMode metricMode,
                    OTF2_Type valueType,
                    OTF2_Base base,
                    int64_t exponent,
                    OTF2_StringRef unit){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_MetricMember(user_data->ctx, self, name, description, metricType, metricMode, valueType, base, exponent, unit);
    return OTF2_CALLBACK_SUCCESS;
}

//Metric class global definition callback
OTF2_CallbackCode GlobalDef_MetricClass_callback(void *userData,
                    OTF2_MetricRef self,
                    uint8_t numberOfMetrics,
                    const OTF2_MetricMemberRef *metricMembers,
                    OTF2_MetricOccurrence metricOccurrence,
                    OTF2_RecorderKind recorderKind){
    user_data_t *user_data = (user_data_t*)userData;
    if(numberOfMetrics > 0){
        barectf_trace_GlobalDef_MetricClass(user_data->ctx, self, numberOfMetrics, metricMembers, metricOccurrence, recorderKind);
    }
    return OTF2_CALLBACK_SUCCESS;
}

//Metric instance global definition callback
OTF2_CallbackCode GlobalDef_MetricInstance_callback(void *userData,
                    OTF2_MetricRef self,
                    OTF2_MetricRef metricClass,
                    OTF2_LocationRef recorder,
                    OTF2_MetricScope metricScope,
                    uint64_t scope){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_MetricInstance(user_data->ctx, self, metricClass, recorder, metricScope, scope);
    return OTF2_CALLBACK_SUCCESS;
}

//Communicator global definition callback
OTF2_CallbackCode GlobalDef_Comm_callback(void *userData,
                    OTF2_CommRef self,
                    OTF2_StringRef name,
                    OTF2_GroupRef group,
                    OTF2_CommRef parent){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Comm(user_data->ctx, self, name, group, parent);
    return OTF2_CALLBACK_SUCCESS;
}

//Parameter global definition callback
OTF2_CallbackCode GlobalDef_Parameter_callback(void *userData,
                    OTF2_ParameterRef self,
                    OTF2_StringRef name,
                    OTF2_ParameterType parameterType){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_Parameter(user_data->ctx, self, name, parameterType);
    return OTF2_CALLBACK_SUCCESS;
}

//RmaWin global definition callback
OTF2_CallbackCode GlobalDef_RmaWin_callback(void *userData,
                    OTF2_RmaWinRef self,
                    OTF2_StringRef name,
                    OTF2_CommRef comm){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_RmaWin(user_data->ctx, self, name, comm);
    return OTF2_CALLBACK_SUCCESS;
}

//MetricClassRecorder global definition callback
OTF2_CallbackCode GlobalDef_MetricClassRecorder_callback(void *userData,
                    OTF2_MetricRef metric,
                    OTF2_LocationRef recorder){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_MetricClassRecorder(user_data->ctx, metric, recorder);
    return OTF2_CALLBACK_SUCCESS;
}

//SystemTreeNodeProperty global definition callback
OTF2_CallbackCode GlobalDef_SystemTreeNodeProperty_callback(void *userData,
                    OTF2_SystemTreeNodeRef systemTreeNode,
                    OTF2_StringRef name,
                    OTF2_Type type,
                    OTF2_AttributeValue value){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_SystemTreeNodeProperty(user_data->ctx, systemTreeNode, name);
    trace_global_def_attribute(user_data, type, value);
    return OTF2_CALLBACK_SUCCESS;
}

//SystemTreeNodeDomain global definition callback
OTF2_CallbackCode GlobalDef_SystemTreeNodeDomain_callback(void *userData,
                    OTF2_SystemTreeNodeRef systemTreeNode,
                    OTF2_SystemTreeDomain systemTreeDomain){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_SystemTreeNodeDomain(user_data->ctx, systemTreeNode, systemTreeDomain);
    return OTF2_CALLBACK_SUCCESS;
}

//LocationGroupProperty global definition callback
OTF2_CallbackCode GlobalDef_LocationGroupProperty_callback(void *userData,
                    OTF2_LocationGroupRef locationGroup,
                    OTF2_StringRef name,
                    OTF2_Type type,
                    OTF2_AttributeValue value){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_LocationGroupProperty(user_data->ctx, locationGroup, name);
    trace_global_def_attribute(user_data, type, value);
    return OTF2_CALLBACK_SUCCESS;
}

//LocationProperty global definition callback
OTF2_CallbackCode GlobalDef_LocationProperty_callback(void *userData,
                    OTF2_LocationRef location,
                    OTF2_StringRef name,
                    OTF2_Type type,
                    OTF2_AttributeValue value){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_LocationProperty(user_data->ctx, location, name);
    trace_global_def_attribute(user_data, type, value);
    return OTF2_CALLBACK_SUCCESS;
}

//CartDimension global definition callback
OTF2_CallbackCode GlobalDef_CartDimension_callback(void *userData,
                    OTF2_CartDimensionRef self,
                    OTF2_StringRef name,
                    uint32_t size,
                    OTF2_CartPeriodicity cartPeriodicity){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_CartDimension(user_data->ctx, self, name, size, cartPeriodicity);
    return OTF2_CALLBACK_SUCCESS;
}

//CartTopology global definition callback
OTF2_CallbackCode GlobalDef_CartTopology_callback(void *userData,
                    OTF2_CartTopologyRef self,
                    OTF2_StringRef name,
                    OTF2_CommRef communicator,
                    uint8_t numberOfDimensions,
                    const OTF2_CartDimensionRef *cartDimensions){
    user_data_t *user_data = (user_data_t*)userData;
    if(numberOfDimensions > 0){
        barectf_trace_GlobalDef_CartTopology(user_data->ctx, self, name, communicator, numberOfDimensions, cartDimensions);
    }
    return OTF2_CALLBACK_SUCCESS;
}

//CartCoordinate global definition callback
OTF2_CallbackCode GlobalDef_CartCoordinate_callback(void *userData,
                    OTF2_CartTopologyRef cartTopology,
                    uint32_t rank,
                    uint8_t numberOfDimensions,
                    const uint32_t *coordinates){
    user_data_t *user_data = (user_data_t*)userData;
    if(numberOfDimensions > 0){
        barectf_trace_GlobalDef_CartCoordinate(user_data->ctx, cartTopology, rank, numberOfDimensions, coordinates);
    }
    return OTF2_CALLBACK_SUCCESS;
}

//SourceCodeLocation global definition callback
OTF2_CallbackCode GlobalDef_SourceCodeLocation_callback(void *userData,
                    OTF2_SourceCodeLocationRef self,
                    OTF2_StringRef file,
                    uint32_t lineNumber){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_SourceCodeLocation(user_data->ctx, self, file, lineNumber);
    return OTF2_CALLBACK_SUCCESS;
}

//CallingContext global definition callback
OTF2_CallbackCode GlobalDef_CallingContext_callback(void *userData,
                    OTF2_CallingContextRef self,
                    OTF2_RegionRef region,
                    OTF2_SourceCodeLocationRef sourceCodeLocation,
                    OTF2_CallingContextRef parent){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_CallingContext(user_data->ctx, self, region, sourceCodeLocation, parent);
    return OTF2_CALLBACK_SUCCESS;
}

//CallingContextProperty global definition callback
OTF2_CallbackCode GlobalDef_CallingContextProperty_callback(void *userData,
                    OTF2_CallingContextRef callingContext,
                    OTF2_StringRef name,
                    OTF2_Type type,
                    OTF2_AttributeValue value){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_CallingContextProperty(user_data->ctx, callingContext, name);
    trace_global_def_attribute(user_data, type, value);
    return OTF2_CALLBACK_SUCCESS;
}

//InterruptGenerator global definition callback
OTF2_CallbackCode GlobalDef_InterruptGenerator_callback(void *userData,
                    OTF2_InterruptGeneratorRef self,
                    OTF2_StringRef name,
                    OTF2_InterruptGeneratorMode interruptGeneratorMode,
                    OTF2_Base base,
                    int64_t exponent,
                    uint64_t period){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_InterruptGenerator(user_data->ctx, self, name, interruptGeneratorMode, base, exponent, period);
    return OTF2_CALLBACK_SUCCESS;
}

//IoFileProperty global definition callback
OTF2_CallbackCode GlobalDef_IoFileProperty_callback(void *userData,
                    OTF2_IoFileRef ioFile,
                    OTF2_StringRef name,
                    OTF2_Type type,
                    OTF2_AttributeValue value){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_IoFileProperty(user_data->ctx, ioFile, name);
    trace_global_def_attribute(user_data, type, value);
    return OTF2_CALLBACK_SUCCESS;
}

//IoRegularFile global definition callback
OTF2_CallbackCode GlobalDef_IoRegularFile_callback(void *userData,
                    OTF2_IoFileRef self,
                    OTF2_StringRef name,
                    OTF2_SystemTreeNodeRef scope){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_IoRegularFile(user_data->ctx, self, name, scope);
    return OTF2_CALLBACK_SUCCESS;
}

//IoDirectory global definition callback
OTF2_CallbackCode GlobalDef_IoDirectory_callback(void *userData,
                    OTF2_IoFileRef self,
                    OTF2_StringRef name,
                    OTF2_SystemTreeNodeRef scope){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_IoDirectory(user_data->ctx, self, name, scope);
    return OTF2_CALLBACK_SUCCESS;
}

//IoHandle global definition callback
OTF2_CallbackCode GlobalDef_IoHandle_callback(void *userData,
                    OTF2_IoHandleRef self,
                    OTF2_StringRef name,
                    OTF2_IoFileRef file,
                    OTF2_IoParadigmRef ioParadigm,
                    OTF2_IoHandleFlag ioHandleFlags,
                    OTF2_CommRef comm,
                    OTF2_IoHandleRef parent){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_IoHandle(user_data->ctx, self, name, file, ioParadigm, ioHandleFlags, comm, parent);
    return OTF2_CALLBACK_SUCCESS;
}

//IoPreCreatedHandleState global definition callback
OTF2_CallbackCode GlobalDef_IoPreCreatedHandleState_callback(void *userData,
                    OTF2_IoHandleRef ioHandle,
                    OTF2_IoAccessMode mode,
                    OTF2_IoStatusFlag statusFlags){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_IoPreCreatedHandleState(user_data->ctx, ioHandle, mode, statusFlags);
    return OTF2_CALLBACK_SUCCESS;
}

//CallpathParameter global definition callback
OTF2_CallbackCode GlobalDef_CallpathParameter_callback(void *userData,
                    OTF2_CallpathRef callpath,
                    OTF2_ParameterRef parameter,
                    OTF2_Type type,
                    OTF2_AttributeValue value){
    user_data_t *user_data = (user_data_t*)userData;
    barectf_trace_GlobalDef_CallpathParameter(user_data->ctx, callpath, parameter);
    trace_global_def_attribute(user_data, type, value);
    return OTF2_CALLBACK_SUCCESS;
}

//Function that set all global definitions callbacks to an OTF2 global definition reader callbacks object
void set_global_def_callbacks(OTF2_GlobalDefReaderCallbacks *global_def_callbacks){
    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetClockPropertiesCallback(global_def_callbacks,
                                                            &GlobalDef_ClockProperties_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetParadigmCallback(global_def_callbacks,
                                                            &GlobalDef_Paradigm_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetParadigmPropertyCallback(global_def_callbacks,
                                                            &GlobalDef_ParadigmProperty_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetIoParadigmCallback(global_def_callbacks,
                                                            &GlobalDef_IoParadigm_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetStringCallback(global_def_callbacks,
                                                            &GlobalDef_String_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetAttributeCallback(global_def_callbacks,
                                                            &GlobalDef_Attribute_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetSystemTreeNodeCallback(global_def_callbacks,
                                                            &GlobalDef_SystemTreeNode_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetLocationGroupCallback(global_def_callbacks,
                                                            &GlobalDef_LocationGroup_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetLocationCallback(global_def_callbacks,
                                                            &GlobalDef_Location_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetRegionCallback(global_def_callbacks,
                                                            &GlobalDef_Region_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCallsiteCallback(global_def_callbacks,
                                                            &GlobalDef_Callsite_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCallpathCallback(global_def_callbacks,
                                                            &GlobalDef_Callpath_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetGroupCallback(global_def_callbacks,
                                                            &GlobalDef_Group_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetMetricMemberCallback(global_def_callbacks,
                                                            &GlobalDef_MetricMember_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetMetricClassCallback(global_def_callbacks,
                                                            &GlobalDef_MetricClass_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetMetricInstanceCallback(global_def_callbacks,
                                                            &GlobalDef_MetricInstance_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCommCallback(global_def_callbacks,
                                                            &GlobalDef_Comm_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetParameterCallback(global_def_callbacks,
                                                            &GlobalDef_Parameter_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetRmaWinCallback(global_def_callbacks,
                                                            &GlobalDef_RmaWin_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetMetricClassRecorderCallback(global_def_callbacks,
                                                            &GlobalDef_MetricClassRecorder_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetSystemTreeNodePropertyCallback(global_def_callbacks,
                                                            &GlobalDef_SystemTreeNodeProperty_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetSystemTreeNodeDomainCallback(global_def_callbacks,
                                                            &GlobalDef_SystemTreeNodeDomain_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetLocationGroupPropertyCallback(global_def_callbacks,
                                                            &GlobalDef_LocationGroupProperty_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetLocationPropertyCallback(global_def_callbacks,
                                                            &GlobalDef_LocationProperty_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCartDimensionCallback(global_def_callbacks,
                                                            &GlobalDef_CartDimension_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCartTopologyCallback(global_def_callbacks,
                                                            &GlobalDef_CartTopology_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCartCoordinateCallback(global_def_callbacks,
                                                            &GlobalDef_CartCoordinate_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetSourceCodeLocationCallback(global_def_callbacks,
                                                            &GlobalDef_SourceCodeLocation_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCallingContextCallback(global_def_callbacks,
                                                            &GlobalDef_CallingContext_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCallingContextPropertyCallback(global_def_callbacks,
                                                            &GlobalDef_CallingContextProperty_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetInterruptGeneratorCallback(global_def_callbacks,
                                                            &GlobalDef_InterruptGenerator_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetIoFilePropertyCallback(global_def_callbacks,
                                                            &GlobalDef_IoFileProperty_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetIoRegularFileCallback(global_def_callbacks,
                                                            &GlobalDef_IoRegularFile_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetIoDirectoryCallback(global_def_callbacks,
                                                            &GlobalDef_IoDirectory_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetIoHandleCallback(global_def_callbacks,
                                                            &GlobalDef_IoHandle_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetIoPreCreatedHandleStateCallback(global_def_callbacks,
                                                            &GlobalDef_IoPreCreatedHandleState_callback));

    OTF2_Call(OTF2_GlobalDefReaderCallbacks_SetCallpathParameterCallback(global_def_callbacks,
                                                            &GlobalDef_CallpathParameter_callback));
}
