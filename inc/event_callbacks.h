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

void set_events_callbacks(OTF2_EvtReaderCallbacks *event_callbacks);

#endif
