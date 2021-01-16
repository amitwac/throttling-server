CC = g++
CXXFLAGS = -std=c++11 -Wall -Werror -g
CLIENT_SRCS = main.cc generate-client-req.cc

all : generaterequest

generaterequest: $(CLIENT_SRCS)
				$(CC) $(CLIENT_SRCS) $(CXXFLAGS) -o $@

clean:
	rm -f generaterequest