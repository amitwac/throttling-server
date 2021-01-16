CC = g++
CXXFLAGS = -std=c++11 -Wall -Werror -g
LIBS = -lpthread
SERVER_SRCS = main.cc throttle-server.cc process-request-worker.cc reset-token-worker.cc

all : throttleserver

throttleserver: $(SERVER_SRCS)
                $(CC) $(SERVER_SRCS) $(CXXFLAGS) $(LIBS) -o $@

clean:
    rm -f throttleserver