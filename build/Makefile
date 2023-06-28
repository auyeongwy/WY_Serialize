CC = g++
CFLAGS = -O2 -Wall -march=native
#CFLAGS = -Wall -O2 -std=c++17 -fsanitize=address -static-libasan -g3 -march=native
BUILD = ../build
SRC = ../src
LIB = -L$(BUILD)
TARGETLIB = $(BUILD)/WY_Serialize.a
HEADERS = $(SRC)/WY_SerializeAgent.hpp $(SRC)/WY_SerializeDef.hpp $(SRC)/WY_SerializeObj.hpp $(SRC)/WY_DebugIO.hpp $(SRC)/WY_SerializeTypes.hpp
OBJS = $(BUILD)/WY_SerializeAgent.o $(BUILD)/WY_DebugIO.o $(BUILD)/WY_SerializeMgr.o
DEMOOBJS = $(BUILD)/DemoObj1.o $(BUILD)/DemoObj2.o 

.PHONY: clean distclean

all: $(TARGETLIB) $(BUILD)/Demo 

$(BUILD)/Demo: $(SRC)/Demo.cpp $(HEADERS) $(DEMOOBJS) $(TARGETLIB)
	@echo Building Demo application...
	$(CC) $(CFLAGS) $(LIB) $(SRC)/Demo.cpp $(DEMOOBJS) $(TARGETLIB) -o $(BUILD)/Demo
	@echo ... Completed

$(BUILD)/DemoObj1.o: $(HEADERS) $(SRC)/DemoObj1.hpp $(SRC)/DemoObj1.cpp
	$(CC) $(CFLAGS) $(SRC)/DemoObj1.cpp -c -o $(BUILD)/DemoObj1.o

$(BUILD)/DemoObj2.o: $(HEADERS) $(SRC)/DemoObj2.hpp $(SRC)/DemoObj2.cpp
	$(CC) $(CFLAGS) $(SRC)/DemoObj2.cpp -c -o $(BUILD)/DemoObj2.o

$(TARGETLIB): $(OBJS)
	@echo Building the WY_Serialize library...
	ar rcs $(TARGETLIB) $(OBJS)
	@echo ... Completed

$(BUILD)/WY_SerializeMgr.o: $(HEADERS) $(SRC)/WY_SerializeMgr.hpp $(SRC)/WY_SerializeMgr.cpp
	$(CC) $(CFLAGS) $(SRC)/WY_SerializeMgr.cpp -c -o $(BUILD)/WY_SerializeMgr.o

$(BUILD)/WY_SerializeAgent.o: $(HEADERS) $(SRC)/WY_SerializeAgent.cpp
	$(CC) $(CFLAGS) $(SRC)/WY_SerializeAgent.cpp -c	-o $(BUILD)/WY_SerializeAgent.o

$(BUILD)/WY_DebugIO.o: $(HEADERS) $(SRC)/WY_DebugIO.cpp
	$(CC) $(CFLAGS) $(SRC)/WY_DebugIO.cpp -c -o $(BUILD)/WY_DebugIO.o

clean:
	rm -f $(BUILD)/*.o

distclean: clean
	rm -f $(TARGETLIB)
	rm -f $(BUILD)/Demo
