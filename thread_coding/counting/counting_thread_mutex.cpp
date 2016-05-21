#include<iostream>
#include<thread>
#include<vector>
#include<mutex>

std::mutex g_increment_mutex;

void increment(int & x, int times){
  for(int i = 0 ; i < times; ++i){
    g_increment_mutex.lock();
    x=x+1;
    g_increment_mutex.unlock();
  }
}

int main(){
  std::vector<std::thread> threads;
  int x = 0;
  int n = 100000;
  int nthreads = 4;
  int thread_n = n/nthreads;
  for(int i=0; i < nthreads; ++i){
    threads.push_back( std::thread(increment, std::ref(x) , thread_n ) );
  }
  for(int i=0; i < nthreads; ++i){
    threads[i].join();
  }
  std::cout << x << std::endl;
  return 0;
}
