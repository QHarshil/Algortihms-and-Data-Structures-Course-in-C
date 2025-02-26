CC = gcc
CFLAGS = -Wall -g
DEPS = adjlist.h dijkstra.h cities.h
OBJ = main.o adjlist.o dijkstra.o cities.o

# Rule to compile all .c files into .o files
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Rule to link all object files into the executable 'main'
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Rule to clean up object files and the executable
clean:
	rm -f $(OBJ) main

