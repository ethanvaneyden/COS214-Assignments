CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g


COMMON_OBJS = CheckpointManager.o Connector.o CsvConnector.o CsvFactory.o Pipeline.o PostgresConnector.o PostgresFactory.o RestApiConnector.o RestFactory.o RunCheckpoint.o

ENGINE = engine
TEST1   = TestSource

all: $(ENGINE)

test1: $(TEST1)


$(ENGINE): $(COMMON_OBJS) Main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST1): $(COMMON_OBJS) TestSource.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f $(ENGINE) $(TEST1)