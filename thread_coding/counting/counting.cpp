#include<iostream>

void increment(int & x, int times){
  for(int i = 0 ; i < times; ++i){
    x=x+1;
  }
}

// main function
int main(){
  // starting number
  int x = 0;
  // increment n times
  int n = 100000000;

  // call function increment
  increment(x, n);

  // display result
  std::cout << x << std::endl;
  
  return 0;
}
