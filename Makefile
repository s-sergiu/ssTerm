LDLIBS += `pkg-config --libs x11`
CFLAGS += -std=c99 -Wall -Wextra `pkg-config --cflags x11`

all: main

eduterm: main.c

clean:
	rm main

.PHONY: all clean
