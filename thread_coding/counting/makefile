all: counting  counting_thread counting_thread_atomic counting_thread_mutex

counting: counting.cpp
	g++ counting.cpp -o counting.exe
counting_thread: counting_thread.cpp
	g++ counting_thread.cpp -pthread -std=c++11 -o counting_thread.exe
counting_thread_atomic: counting_thread_atomic.cpp
	g++ counting_thread_atomic.cpp -std=c++11 -o counting_thread_atomic.exe
counting_thread_mutex: counting_thread_mutex.cpp
	g++ counting_thread_mutex.cpp -std=c++11 -o counting_thread_mutex.exe
	
clean:
	rm -f counting.exe
	rm -f counting_thread.exe
	rm -f counting_thread_mutex.exe
	rm -f counting_thread_atomic.exe