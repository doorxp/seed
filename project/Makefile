PROJECT=libSeed.a
include Objects.in
TARGET = ../bin/$(PROJECT)

SEEDSDK=/media/d/SDK

AR = ar
AR_PARAM = cru
AS = as
NM = nm
STRIP = strip
LD = ld
GCC = g++
CFLAGS = -Wall -g -fPIC `sdl-config --cflags` $(CDEFS) -I$(SEEDSDK)/seed/include
CDEFS = -D_SDL_ -DDEBUG -DYMEM_DEBUG -DYMEM_PARANOID_CHECK -DSEED_ENABLE_PROFILER -DLINUX
LFLAGS = `sdl-config --libs` -lSDL_image -lopenal -lGL -lseed -logg -lvorbis -lvorbisfile -loggz -loggplay -ltheora
CPPFLAGS = $(CFLAGS)
LIBS =

all:	$(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) $(AR_PARAM) $(TARGET) $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(TARGET) *~
