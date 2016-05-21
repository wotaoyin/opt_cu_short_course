all: matrix_mult.exe matrix_mult_worker.exe matrix_mult_worker_barrier.exe matrix_mult_worker_scheduler.exe

matrix_mult.exe: matrix_mult.o
	g++ matrix_mult.o -std=c++11 -o matrix_mult.exe
matrix_mult_worker.exe: matrix_mult_worker.o
	g++ matrix_mult_worker.o -std=c++11 -o matrix_mult_worker.exe
matrix_mult_worker_barrier.exe: matrix_mult_worker_barrier.o barrier.o
	g++ matrix_mult_worker_barrier.o barrier.o -std=c++11 -o matrix_mult_worker_barrier.exe
matrix_mult_worker_scheduler.exe: matrix_mult_worker_scheduler.o scheduler.h
	g++ matrix_mult_worker_scheduler.o -std=c++11 -o matrix_mult_worker_scheduler.exe 

barrier.o: barrier.h barrier.cpp
	g++ barrier.cpp  -std=c++11 -c -o barrier.o
matrix_mult.o: matrix_mult.cpp
	g++ matrix_mult.cpp -std=c++11 -c -o matrix_mult.o
matrix_mult_worker.o: matrix_mult_worker.cpp
	g++ matrix_mult_worker.cpp -std=c++11 -c -o matrix_mult_worker.o
matrix_mult_worker_barrier.o: matrix_mult_worker_barrier.cpp
	g++ matrix_mult_worker_barrier.cpp -std=c++11 -c -o matrix_mult_worker_barrier.o

matrix_mult_worker_scheduler.o: matrix_mult_worker_scheduler.cpp scheduler.h
	g++ matrix_mult_worker_scheduler.cpp -std=c++11 -c -o matrix_mult_worker_scheduler.o

clean:
	rm -f matrix_mult.exe
	rm -f matrix_mult_worker.exe
	rm -f matrix_mult_worker_barrier.exe