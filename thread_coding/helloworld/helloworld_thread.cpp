#include<iostream> 
#include<thread>

void hello_world () {
  std::cout << "Hello World from thread: " << std::this_thread::get_id()  << std::endl;
}

// main function
int main () {
  // obtain the id of this thread
  auto id = std::this_thread::get_id();
  // display thread
  std::cout << "Primary thread: " << id << std::endl;

  // spawn a thread to execute print "Hello World" 
  std::thread slave_thread(hello_world);
  // spawn another thread
  std::thread third_thread(hello_world);

  // wait for the thread to finish
  slave_thread.join();
  third_thread.join();
 
  return 0; 
}
