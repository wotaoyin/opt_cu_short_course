#include<iostream>
#include<thread>
#include<chrono>

void count_to_ten () {

  std::cout << " thread " << std::this_thread::get_id() << " waits 2 seconds " << std::endl;
  std::this_thread::sleep_for( std::chrono::seconds(2) ); //sleep for 2000 milliseconds
  std::cout << " thread " << std::this_thread::get_id() << " resumes " << std::endl;

  // print from 1 to 10
  for (int i = 1; i <= 10; ++i) {
    std::cout << i << std::endl;
  }
}

//  main function
int main ( ) {

  std::thread counting( count_to_ten ); // spawn a thread with count_to_a_hundred ( )
  counting.detach(); // if I don't care if the thread doesn't finish executing; 
                     // caution: when either one ends execution, its resources are released.
  // counting.join(); //if I want the thread to finish executing

  std::cout << " main thread waits 5 seconds " << std::endl;
  std::this_thread::sleep_for( std::chrono::seconds(5) );
  std::cout << " main thread resumes " << std::endl;
  std::cout << " main thread is exiting " << std::endl;

  return 0;
}
