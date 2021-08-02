TARGETS=benchmark

CROSS_TOOL =
CC_CPP = $(CROSS_TOOL)g++

CFLAGS= -Wall -Werror -g

all: clean $(TARGETS)

$(TARGETS):
	$(CC_CPP) $(CFLAGS) $@.cpp -o $@

clean:
	rm -f $(TARGETS)