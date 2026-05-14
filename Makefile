CC      = clang
CFLAGS  = -Wall -Wextra -Wpedantic -Werror -O2
HEADER = game.h randi.h strings.h

lcr: lcr.o game.o randi.o
	$(CC) lcr.o game.o randi.o -o lcr

lcr.o: lcr.c $(HEADER)
	$(CC) $(CFLAGS) -c lcr.c

game.o: game.c $(HEADER)
	$(CC) $(CFLAGS) -c game.c

randi.o: randi.c randi.h
	$(CC) $(CFLAGS) -c randi.c

clean:
	rm -f *.o lcr
