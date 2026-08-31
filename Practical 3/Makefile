CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -g

TARGET = expo

SRCS = $(wildcard *.cpp)

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./expo

.PHONY: all clean