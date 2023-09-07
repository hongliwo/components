#
# Component Makefile
#
COMPONENT_ADD_INCLUDEDIRS += ./include
COMPONENT_ADD_INCLUDEDIRS += ../../sdk/opus/include

COMPONENT_SRCDIRS += ./src

COMPONENT_ADD_LDFLAGS += sdk/opus/lib/libopus.a
