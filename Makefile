#CXXFLAGS += -fPIC
CXXFLAGS += -O3
CXXFLAGS += -std=c++11

INCLUDES = $(wildcard *.h)
	
all: $(INCLUDES) test
	
test:ABitReader.o AString.o RefBase.o TextOutput.o SharedBuffer.o test.o AMessage.o AHandler.o ALooper.o VectorImpl.o AAtomizer.o String8.o String16.o Unicode.o Debug.o Flattenable.o Static.o ALooperRoster.o Threads.o
	$(CXX) -pthread -o $@ $^ $(CXXFLAGS)

clean:
	rm *.o -rf
	rm test -rf
	rm log.txt -rf