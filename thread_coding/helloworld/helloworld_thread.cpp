#include<iostream> 
#include<thread>

void hello_world( ) {
  std::cout << "Hello World from thread: " << std::this_thread::get_id()  << std::endl;
}

int main( ) {
  auto id = std::this_thread::get_id();
  std::cout << "Primary thread: " << id << std::endl;
  std::thread hello(hello_world); //spawn a thread to execute print "Hello World"
  hello.join();
 
  return 0; 
}
