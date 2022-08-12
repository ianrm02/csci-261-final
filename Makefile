TARGET = FP
SRC_FILES = main.cpp

CXX = g++

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

%.o: %.cpp
	$(CXX) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)