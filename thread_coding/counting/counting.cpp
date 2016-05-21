#include<iostream>

void increment(int & x, int times){
  for(int i = 0 ; i < times; ++i){
    x=x+1;
  }
}

int main(){
  int x = 0;
  int n = 100;

  increment(x, 100);

  std::cout << x << std::endl;
  
  return 0;
}
