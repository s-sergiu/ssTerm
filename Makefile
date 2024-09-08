NAME = ssTerm
LDLIBS += `pkg-config --libs x11`
CFLAGS += -Werror -Wall -Wextra `pkg-config --cflags x11`

all: main.c
	cc $(CFLAGS) $(LDLIBS) main.c -o $(NAME)

clean:

fclean: clean 
	rm $(NAME)

re : fclean all

.PHONY: all clean
