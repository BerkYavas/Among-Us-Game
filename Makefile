OBJS	= among_us.o
SOURCE	= among_us.c
CC	 = gcc
FLAGS	 = -g -c 

all: $(OBJS)
	$(CC) -g $(OBJS) -o main 


among_us.o: among_us.c
	$(CC) $(FLAGS) among_us.c -std=c99


clean:
	rm -f $(OBJS) $(OUT)
