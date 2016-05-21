all: helloworld helloworld_func helloworld_thread

helloworld: helloworld.cpp
	g++ helloworld.cpp -o helloworld.exe

helloworld_func: helloworld_func.cpp
	g++ helloworld_func.cpp -o helloworld_func.exe

helloworld_thread: helloworld_thread.cpp
	g++ helloworld_thread.cpp -std=c++11 -o helloworld_thread.exe

clean:
	rm -f helloworld.exe
	rm -f helloworld_func.exe
	rm -f helloworld_thread.exe
