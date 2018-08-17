CC=clang
CXX=clang++
MKDIR=mkdir -p
SRCDIR=../source
VSTDIR=$(SRCDIR)/vst2
OUTDIR=../build/linux/x64/release
BASEFLAGS=-I$(SRCDIR) -DNDEBUG -msse4.1 -O3 -ffast-math -fPIC -Werror -Wno-unused-function -Wno-\#warnings
CFLAGS=$(BASEFLAGS) -std=c11
CXXFLAGS=$(BASEFLAGS) -std=c++11 -Wno-writable-strings -fno-exceptions -fno-rtti
HEADERS=$(wildcard $(SRCDIR)/*.h)
HEADERS+=$(wildcard $(SRCDIR)/*.hpp)
HEADERS+=aeffect.h aeffectx.h vstfxstore.h aeffeditor.h audioeffect.h audioeffectx.h

CFILES=$(wildcard $(SRCDIR)/*.c)
OBJC=$(CFILES:%.c=%.o)

CXXFILES=$(wildcard $(SRCDIR)/*.cpp)
CXXFILES+=$(wildcard $(VSTDIR)/*.cpp)
OBJCXX=$(CXXFILES:%.cpp=%.o)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

all: directories vst2

directories: $(OUTDIR)

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

vst2: $(OBJC) $(OBJCXX)
	$(CXX) -o $(OUTDIR)/{{name}}.so $^ -shared

.PHONY: clean

clean:
	rm -f $(SRCDIR)/*.o $(VSTDIR)/*.o $(OUTDIR)/*.so
