all: a1 addauthor post.c post

a1: main.c functions.c functions.h
	gcc -Wall -ansi main.c functions.c -g -o a1
	
addauthor: addauthor.o libstream.a
	gcc addauthor.o -g -o addauthor -lstream -L.
	
libstream.a: stream.c stream.h
	gcc -Wall -ansi -c stream.c -o stream.o;\
	ar cr libstream.a stream.o
	
addauthor.o: addauthor.c stream.h
	gcc -Wall -ansi -c addauthor.c -o addauthor.o -g
	
post.c: a1 post.cc
	./a1 post.cc
	
post: post.o stream.h
	gcc -Wall -ansi post.o -o post -g -lstream -L.
	
post.o: post.c stream.h
	gcc -Wall -ansi -c post.c -o post.o -g

clean:
	rm *.o
