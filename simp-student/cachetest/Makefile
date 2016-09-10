SHARED_DIR = ../shared

SRCS = $(SHARED_DIR)/global.cpp \
	$(SHARED_DIR)/Memory.cpp \
	$(SHARED_DIR)/Cache.cpp \
	cachetest.cpp

CPP = g++
CFLAGS = 
INCLUDES = -I$(SHARED_DIR)
LFLAGS = -g
LIBS =

OBJS = $(SRCS:.cpp=.o)

all: cachetest.x

cachetest.x: $(OBJS)
	$(CPP) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

	
%.cpp: %.h

.cpp.o:
	$(CPP) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm -f *.o *.x

depend:
	makedepend -Y$(SHARED_DIR) --$(CFLAGS)-- $(SRCS)

# DO NOT DELETE

../shared/global.o: ../shared/global.h
../shared/Memory.o: ../shared/Memory.h ../shared/global.h ../shared/elf.h
../shared/Cache.o: ../shared/Cache.h ../shared/global.h ../shared/Memory.h
cachetest.o: ../shared/global.h ../shared/Memory.h ../shared/Cache.h
