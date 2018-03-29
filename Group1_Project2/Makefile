CC = gcc
CFLAGS = -Wall -c
LDFLAGS = -lncurses
OBJS = Editor.o	Proj2.o textBuffer.o search.o delete.o save.o copy.o
TARGET = Proj2
DEPS = Editor.h textBuffer.h Proj2.c search.h delete.h save.h copy.h

Proj2: $(OBJS) 
	$(CC)  -o Proj2 $(OBJS) $(LDFLAGS)

Proj2.o: $(DEPS)
	$(CC) $(CFLAGS) -o Proj2.o Proj2.c $(LDFLAGS) 

Editor.o: Editor.h
	$(CC) $(CFLAGS) -o Editor.o Editor.c $(LDFLAGS)

textBuffer.o: textBuffer.h
	$(CC) $(CFLAGS) -o textBuffer.o textBuffer.c $(LDFLAGS)

#save.o: save.h
#	$(CC) $(CFLAGS) -o save.o save.c $(LDFLAGS) 

search.o: search.h
	$(CC) $(CFLAGS) -o search.o search.c $(LDFLAGS)

delete.o: delete.h
	$(CC) $(CFLAGS) -o delete.o delete.c $(LDFLAGS)

save.o: save.h
	$(CC) $(CFLAGS) -o save.o save.c $(LDFLAGS)

copypaste.o: copy.h
	$(CC) $(CFLAGS) -o copy.o copy.c $(LDFLAGS)

clean: 
	rm -f $(OBJS)
