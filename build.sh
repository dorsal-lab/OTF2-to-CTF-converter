#!/bin/bash
if [ -z "$OTF2_PATH" ]; then export OTF2_PATH=/opt/otf2; fi
export PATH=$PATH:$OTF2_PATH/bin
export C_INCLUDE_PATH=$C_INCLUDE_PATH:$OTF2_PATH/include
make otf2_converter
rm *.o