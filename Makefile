CXX = g++
RM = rm -f
CXXFLAGS = -std=c++98 -Wall -Wextra
ifdef DEBUG
	CXXFLAGS += -DDEBUG
endif

TARGET = auto_guard_test
#SRC = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*/*.cpp)
#OBJECTS = $(patsubst %.cpp,%.o,$(SRC))
ALL : clean $(TARGET)

auto_guard_test : auto_guard_test.cpp thread_base.cpp
	$(CXX) $(CXXFLAGS)  $^ -o $@


.PHONY : clean
clean:
	$(RM) $(OBJECTS)
	$(RM) $(TARGET)
