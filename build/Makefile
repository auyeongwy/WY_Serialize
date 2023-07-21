CC = g++
CFLAGS = -O2 -Wall -march=native -DENABLE_WY_DEBUGIO
#CFLAGS = -Wall -std=c++17 -fsanitize=address -static-libasan -g3 -march=native -DENABLE_WY_DebugIO
BUILD = ../build
SRC = ../src
LIB = -L$(BUILD)
TARGETLIB = $(BUILD)/lib_WY_Serialize.a
HEADERS = $(SRC)/WY_SerializeAgent.hpp $(SRC)/WY_SerializeDef.hpp $(SRC)/WY_SerializeObj.hpp $(SRC)/WY_DebugIO.hpp $(SRC)/WY_SerializeTypes.hpp
OBJS = $(BUILD)/WY_SerializeAgent.o $(BUILD)/WY_DebugIO.o $(BUILD)/WY_SerializeMgr.o
DEMOOBJS = $(BUILD)/DemoObj1.o $(BUILD)/DemoObj2.o 

.PHONY: clean distclean object_msg demo_msg

all: $(TARGETLIB) $(BUILD)/Demo 

$(BUILD)/Demo: $(SRC)/Demo.cpp $(HEADERS) $(TARGETLIB) demo_msg $(DEMOOBJS)
	$(CC) $(CFLAGS) $(LIB) $(SRC)/Demo.cpp $(DEMOOBJS) $(TARGETLIB) -o $(BUILD)/Demo

$(BUILD)/DemoObj1.o: $(HEADERS) $(SRC)/DemoObj1.hpp $(SRC)/DemoObj1.cpp
	$(CC) $(CFLAGS) $(SRC)/DemoObj1.cpp -c -o $(BUILD)/DemoObj1.o

$(BUILD)/DemoObj2.o: $(HEADERS) $(SRC)/DemoObj2.hpp $(SRC)/DemoObj2.cpp
	$(CC) $(CFLAGS) $(SRC)/DemoObj2.cpp -c -o $(BUILD)/DemoObj2.o

$(TARGETLIB): object_msg $(OBJS)
	@echo Building the WY_Serialize library...
	ar rcs $(TARGETLIB) $(OBJS)

$(BUILD)/WY_SerializeMgr.o: $(HEADERS) $(SRC)/WY_SerializeMgr.hpp $(SRC)/WY_SerializeMgr.cpp
	$(CC) $(CFLAGS) $(SRC)/WY_SerializeMgr.cpp -c -o $(BUILD)/WY_SerializeMgr.o

$(BUILD)/WY_SerializeAgent.o: $(HEADERS) $(SRC)/WY_SerializeAgent.cpp
	$(CC) $(CFLAGS) $(SRC)/WY_SerializeAgent.cpp -c	-o $(BUILD)/WY_SerializeAgent.o

$(BUILD)/WY_DebugIO.o: $(HEADERS) $(SRC)/WY_DebugIO.cpp
	$(CC) $(CFLAGS) $(SRC)/WY_DebugIO.cpp -c -o $(BUILD)/WY_DebugIO.o

object_msg:
	@echo Building objects...

demo_msg:
	@echo Building Demo application...

clean:
	rm -f $(BUILD)/*.o

distclean: clean
	rm -f $(TARGETLIB)
	rm -f $(BUILD)/Demo
