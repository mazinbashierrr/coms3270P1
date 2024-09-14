stat: pointcloud.o
	gcc pointcloud.o -o stat 

pointcloud.o: pointcloud.c pointcloud.h
	gcc -c pointcloud.c 

clean:
	rm -f *.o stat