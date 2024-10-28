stat: pointcloud.o bmp.o util.o
	gcc pointcloud.o bmp.o util.o -o stat 

pointcloud.o: pointcloud.c pointcloud.h util.h
	gcc -c pointcloud.c 

bmp.o: bmp.c bmp.h
	gcc -c bmp.c

util.o: util.c util.h
	gcc -c util.c
clean:
	rm -f *.o stat