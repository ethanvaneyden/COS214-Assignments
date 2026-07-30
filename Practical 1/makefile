CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g


COMMON_OBJS = CheckpointManager.o Connector.o CsvConnector.o CsvFactory.o Pipeline.o PostgresConnector.o PostgresFactory.o RestApiConnector.o RestFactory.o RunCheckpoint.o
COMMON_DEPS = $(COMMON_OBJS:.o=.d)

ENGINE = engine
TEST   = TestSource

all: $(ENGINE)

test: $(TEST)

$(ENGINE): $(COMMON_OBJS) Main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST): $(COMMON_OBJS) TestSource.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(COMMON_OBJS) Main.o TestSource.o
	rm -f $(COMMON_DEPS) Main.d TestSource.d
	rm -f $(ENGINE) $(TEST)