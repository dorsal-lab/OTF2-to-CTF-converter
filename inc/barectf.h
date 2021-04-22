#ifndef _BARECTF_H
#define _BARECTF_H

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2020 Philippe Proulx <pproulx@efficios.com>
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
 *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 *
 * The following code was generated by barectf v3.0.1
 * on 2021-04-22T16:00:33.916305.
 *
 * For more details, see <https://barectf.org/>.
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define barectf_trace_Event_Enter barectf_default_trace_Event_Enter
#define barectf_trace_Event_Leave barectf_default_trace_Event_Leave
#define barectf_trace_Event_MpiCollectiveBegin barectf_default_trace_Event_MpiCollectiveBegin
#define barectf_trace_Event_MpiCollectiveEnd barectf_default_trace_Event_MpiCollectiveEnd
#define barectf_trace_Event_MpiIrecv barectf_default_trace_Event_MpiIrecv
#define barectf_trace_Event_MpiIrecvRequest barectf_default_trace_Event_MpiIrecvRequest
#define barectf_trace_Event_MpiIsend barectf_default_trace_Event_MpiIsend
#define barectf_trace_Event_MpiIsendComplete barectf_default_trace_Event_MpiIsendComplete
#define barectf_trace_Event_MpiRecv barectf_default_trace_Event_MpiRecv
#define barectf_trace_Event_MpiRequestCancelled barectf_default_trace_Event_MpiRequestCancelled
#define barectf_trace_Event_MpiRequestTest barectf_default_trace_Event_MpiRequestTest
#define barectf_trace_Event_MpiSend barectf_default_trace_Event_MpiSend
#define barectf_trace_GlobalDef_Comm barectf_default_trace_GlobalDef_Comm
#define barectf_trace_GlobalDef_Group barectf_default_trace_GlobalDef_Group
#define barectf_trace_GlobalDef_Location barectf_default_trace_GlobalDef_Location
#define barectf_trace_GlobalDef_LocationGroup barectf_default_trace_GlobalDef_LocationGroup
#define barectf_trace_GlobalDef_Region barectf_default_trace_GlobalDef_Region
#define barectf_trace_GlobalDef_String barectf_default_trace_GlobalDef_String
#define barectf_trace_GlobalDef_SystemTreeNode barectf_default_trace_GlobalDef_SystemTreeNode

struct barectf_ctx;

uint32_t barectf_packet_size(const void *vctx);
int barectf_packet_is_full(const void *vctx);
int barectf_packet_is_empty(const void *vctx);
uint32_t barectf_packet_events_discarded(const void *vctx);
uint32_t barectf_discarded_event_records_count(const void * const vctx);
uint8_t *barectf_packet_buf(const void *vctx);
uint8_t *barectf_packet_buf_addr(const void * const vctx);
void barectf_packet_set_buf(void *vctx, uint8_t *buf, uint32_t buf_size);
uint32_t barectf_packet_buf_size(const void *vctx);
int barectf_packet_is_open(const void *vctx);
int barectf_is_in_tracing_section(const void *vctx);
volatile const int *barectf_is_in_tracing_section_ptr(const void *vctx);
int barectf_is_tracing_enabled(const void *vctx);
void barectf_enable_tracing(void *vctx, int enable);

/* barectf platform callbacks */
struct barectf_platform_callbacks {
	/* Clock source callbacks */
	uint64_t (*default_clock_get_value)(void *);

	/* Is the back end full? */
	int (*is_backend_full)(void *);

	/* Open packet */
	void (*open_packet)(void *);

	/* Close packet */
	void (*close_packet)(void *);
};

/* Common barectf context */
struct barectf_ctx {
	/* Platform callbacks */
	struct barectf_platform_callbacks cbs;

	/* Platform data (passed to callbacks) */
	void *data;

	/* Output buffer (will contain a CTF binary packet) */
	uint8_t *buf;

	/* Packet's total size (bits) */
	uint32_t packet_size;

	/* Packet's content size (bits) */
	uint32_t content_size;

	/* Current position from beginning of packet (bits) */
	uint32_t at;

	/* Size of packet header + context fields (content offset) */
	uint32_t off_content;

	/* Discarded event records counter snapshot */
	uint32_t events_discarded;

	/* Current packet is open? */
	int packet_is_open;

	/* In tracing code? */
	volatile int in_tracing_section;

	/* Tracing is enabled? */
	volatile int is_tracing_enabled;

	/* Use current/last event record timestamp when opening/closing packets */
	int use_cur_last_event_ts;
};

/* Context for data stream type `default` */
struct barectf_default_ctx {
	/* Parent */
	struct barectf_ctx parent;

	/* Config-specific members follow */
	uint32_t off_ph_magic;
	uint32_t off_ph_stream_id;
	uint32_t off_pc_packet_size;
	uint32_t off_pc_content_size;
	uint32_t off_pc_timestamp_begin;
	uint32_t off_pc_timestamp_end;
	uint32_t off_pc_events_discarded;
	uint64_t cur_last_event_ts;
};

/* Initialize context */
void barectf_init(void *vctx,
	uint8_t *buf, uint32_t buf_size,
	const struct barectf_platform_callbacks cbs, void *data);

/* Open packet for data stream type `default` */
void barectf_default_open_packet(
	struct barectf_default_ctx *sctx);

/* Close packet for data stream type `default` */
void barectf_default_close_packet(struct barectf_default_ctx *sctx);

/* Trace (data stream type `default`, event record type `Event_Enter`) */
void barectf_default_trace_Event_Enter(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint32_t p_regionRef);

/* Trace (data stream type `default`, event record type `Event_Leave`) */
void barectf_default_trace_Event_Leave(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint32_t p_regionRef);

/* Trace (data stream type `default`, event record type `Event_MpiCollectiveBegin`) */
void barectf_default_trace_Event_MpiCollectiveBegin(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef);

/* Trace (data stream type `default`, event record type `Event_MpiCollectiveEnd`) */
void barectf_default_trace_Event_MpiCollectiveEnd(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint8_t p_collectiveOp,
	uint32_t p_communicator,
	uint32_t p_root,
	uint64_t p_sizeSent,
	uint64_t p_sizeReceived);

/* Trace (data stream type `default`, event record type `Event_MpiIrecv`) */
void barectf_default_trace_Event_MpiIrecv(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint32_t p_receiver,
	uint32_t p_communicator,
	uint32_t p_msgTag,
	uint64_t p_msgLength,
	uint64_t p_requestID);

/* Trace (data stream type `default`, event record type `Event_MpiIrecvRequest`) */
void barectf_default_trace_Event_MpiIrecvRequest(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint64_t p_requestID);

/* Trace (data stream type `default`, event record type `Event_MpiIsend`) */
void barectf_default_trace_Event_MpiIsend(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint32_t p_receiver,
	uint32_t p_communicator,
	uint32_t p_msgTag,
	uint64_t p_msgLength,
	uint64_t p_requestID);

/* Trace (data stream type `default`, event record type `Event_MpiIsendComplete`) */
void barectf_default_trace_Event_MpiIsendComplete(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint64_t p_requestID);

/* Trace (data stream type `default`, event record type `Event_MpiRecv`) */
void barectf_default_trace_Event_MpiRecv(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint32_t p_sender,
	uint32_t p_communicator,
	uint32_t p_msgTag,
	uint64_t p_msgLength);

/* Trace (data stream type `default`, event record type `Event_MpiRequestCancelled`) */
void barectf_default_trace_Event_MpiRequestCancelled(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint64_t p_requestID);

/* Trace (data stream type `default`, event record type `Event_MpiRequestTest`) */
void barectf_default_trace_Event_MpiRequestTest(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint64_t p_requestID);

/* Trace (data stream type `default`, event record type `Event_MpiSend`) */
void barectf_default_trace_Event_MpiSend(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint32_t p_receiver,
	uint32_t p_communicator,
	uint32_t p_msgTag,
	uint64_t p_msgLength);

/* Trace (data stream type `default`, event record type `GlobalDef_Comm`) */
void barectf_default_trace_GlobalDef_Comm(struct barectf_default_ctx *sctx,
	uint32_t p_commRef,
	uint32_t p_name,
	uint32_t p_groupRef,
	uint32_t p_parent);

/* Trace (data stream type `default`, event record type `GlobalDef_Group`) */
void barectf_default_trace_GlobalDef_Group(struct barectf_default_ctx *sctx,
	uint32_t p_groupRef,
	uint32_t p_name,
	uint8_t p_groupType,
	uint8_t p_paradigm,
	uint32_t p_groupFlags,
	uint32_t p___members_len,
	const uint64_t *p_members);

/* Trace (data stream type `default`, event record type `GlobalDef_Location`) */
void barectf_default_trace_GlobalDef_Location(struct barectf_default_ctx *sctx,
	uint64_t p_locationRef,
	uint32_t p_name,
	uint8_t p_locationType,
	uint64_t p_numberOfEvents,
	uint32_t p_locationGroupRef);

/* Trace (data stream type `default`, event record type `GlobalDef_LocationGroup`) */
void barectf_default_trace_GlobalDef_LocationGroup(struct barectf_default_ctx *sctx,
	uint32_t p_locationGroupRef,
	uint32_t p_name,
	uint8_t p_locationGroupType,
	uint32_t p_systemTreeNodeRef);

/* Trace (data stream type `default`, event record type `GlobalDef_Region`) */
void barectf_default_trace_GlobalDef_Region(struct barectf_default_ctx *sctx,
	uint32_t p_regionRef,
	uint32_t p_name,
	uint32_t p_canonicalName,
	uint32_t p_description,
	uint8_t p_regionRole,
	uint8_t p_paradigm,
	uint32_t p_regionFlag,
	uint32_t p_sourceFile,
	uint32_t p_beginLineNumber,
	uint32_t p_endLineNumber);

/* Trace (data stream type `default`, event record type `GlobalDef_String`) */
void barectf_default_trace_GlobalDef_String(struct barectf_default_ctx *sctx,
	uint32_t p_stringRef,
	const char *p_stringValue);

/* Trace (data stream type `default`, event record type `GlobalDef_SystemTreeNode`) */
void barectf_default_trace_GlobalDef_SystemTreeNode(struct barectf_default_ctx *sctx,
	uint32_t p_systemTreeNodeRef,
	uint32_t p_name,
	uint32_t p_className,
	uint32_t p_systemTreeParent);

#ifdef __cplusplus
}
#endif

#endif /* _BARECTF_H */
