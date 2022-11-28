find_path(OTF2_INCLUDE_DIR otf2/otf2.h
    ${OTF2_PATH}/include
    /opt/otf2/include
    $ENV{HOME}/opt/include
    /usr/opt/otf2/include
    /usr/include
    /usr/local/include
)

find_library(OTF2_LIBRARY otf2
    ${OTF2_PATH}/lib
    /opt/otf2/lib
    $ENV{HOME}/opt/lib
    /usr/opt/otf2/lib
    /usr/lib
    /usr/local/lib
)

if(OTF2_INCLUDE_DIR AND OTF2_LIBRARY)
    set(OTF2_FOUND "yes")
endif()

if(NOT OTF2_FOUND)
    message("OTF2 Installation was not found. Please provide the OTF2 path in OTF2_PATH.")
endif()
