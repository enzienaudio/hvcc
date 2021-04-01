CC=clang
CXX=clang++
COMMONFLAGS=-Werror -Wno-unused-function -Wno-\#warnings -DHV_SIMD_NONE
CFLAGS=-std=c11 $(COMMONFLAGS)
CXXFLAGS=-std=c++11 -fno-exceptions -fno-rtti $(COMMONFLAGS)

DEPS= \
HvHeavyInternal.h \
HeavyContextInterface.hpp \
HvControlPrint.h \
HvControlBinop.h \
Heavy_heavy.hpp \
Heavy_heavy.h \
HvMessagePool.h \
HvMessageQueue.h \
HvLightPipe.h \
HvHeavy.h \
HeavyContext.hpp \
HvTable.h \
HvMessage.h \
HvUtils.h \
HvControlUnop.h \
HvMath.h \
HvControlCast.h

OBJ= \
HvMessageQueue.o \
HvHeavy.o \
Heavy_heavy.o \
HvUtils.o \
HvLightPipe.o \
test_control.o \
HvMessagePool.o \
HvControlCast.o \
HvControlUnop.o \
HvTable.o \
HvControlPrint.o \
HeavyContext.o \
HvMessage.o \
HvControlBinop.o

all: main

# compile only, C source
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# compile only, C++ source
%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# link
main: $(OBJ)
	$(CXX) -o /home/dreamer/Sources/_downloads/_enzienaudio/hvcc/tests/build/heavy $^

.PHONY: clean

clean:
	rm -f $(OBJ)