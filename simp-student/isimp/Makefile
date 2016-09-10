SHARED_DIR = ../shared

SRCS = $(SHARED_DIR)/global.cpp \
	$(SHARED_DIR)/Memory.cpp \
	$(SHARED_DIR)/RegFile.cpp \
	$(SHARED_DIR)/Instruction.cpp \
	$(SHARED_DIR)/Reg.cpp \
	$(SHARED_DIR)/CombLogic.cpp \
	$(SHARED_DIR)/Cache.cpp \
	$(SHARED_DIR)/Pipeline.cpp \
	Pipe2Stage.cpp isimp-main.cpp

CPP = g++
CFLAGS = 
INCLUDES = -I$(SHARED_DIR)
LFLAGS = -g
LIBS =

OBJS = $(SRCS:.cpp=.o)

all: isimp.x

isimp.x: $(OBJS)
	$(CPP) $(CFLAGS) $(INCLUDES) -o $@ $(OBJS) $(LFLAGS) $(LIBS)

	
%.cpp: %.h

.cpp.o:
	$(CPP) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	rm -f *.o *.x *.bak

depend:
	makedepend -Y$(SHARED_DIR) --$(CFLAGS)-- $(SRCS)

# DO NOT DELETE

../shared/global.o: ../shared/global.h
../shared/Memory.o: ../shared/Memory.h ../shared/global.h ../shared/elf.h
../shared/RegFile.o: ../shared/RegFile.h ../shared/global.h
../shared/Instruction.o: ../shared/Instruction.h ../shared/global.h
../shared/Instruction.o: ../shared/RegFile.h ../shared/Memory.h
../shared/Reg.o: ../shared/Reg.h ../shared/global.h ../shared/Instruction.h
../shared/CombLogic.o: ../shared/CombLogic.h
../shared/Cache.o: ../shared/Cache.h ../shared/global.h ../shared/Memory.h
../shared/Pipeline.o: ../shared/Pipeline.h ../shared/global.h ../shared/Reg.h
../shared/Pipeline.o: ../shared/Instruction.h ../shared/CombLogic.h
../shared/Pipeline.o: ../shared/RegFile.h ../shared/Memory.h
../shared/Pipeline.o: ../shared/Cache.h
Pipe2Stage.o: Pipe2Stage.h ../shared/global.h ../shared/Pipeline.h
Pipe2Stage.o: ../shared/Reg.h ../shared/Instruction.h ../shared/CombLogic.h
Pipe2Stage.o: ../shared/RegFile.h ../shared/Memory.h ../shared/Cache.h
mipsim-main.o: Pipe2Stage.h ../shared/global.h ../shared/Pipeline.h
mipsim-main.o: ../shared/Reg.h ../shared/Instruction.h ../shared/CombLogic.h
mipsim-main.o: ../shared/RegFile.h ../shared/Memory.h ../shared/Cache.h
