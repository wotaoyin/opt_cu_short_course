#include"barrier.h"
#include<iostream>
#include<random>
#include<thread>

double dot(double* result, double* arr1, int stride1, double* arr2, int stride2, int size);

//serial matrix mult
void matrix_mult(double* matrix,int m, int n, double* v_in, double* v_out);

//serial matrix transpose mult
void matrix_transpose_mult(double* matrix,int m, int n, double* v_in, double* v_out);

//calculate error
void norm_squared_diff(double* result, double * arr1, int stride1, double * arr2, int stride2, int size);

void worker(double* matrix,int m, int n, double* x, double* y, int start, int start_tranpose, int block_size, int block_size_tranpose, spin_barrier& bar){
  
    for( int i=0; i< block_size; ++i ){
      dot( &y[i+start], matrix+(start+i)*n, 1, x,1,n);
    }
    bar.wait();
    for( int i=0; i< block_size_tranpose; ++i ){
      dot( &x[i+start_tranpose], matrix+i+start_tranpose, n, y,1,m);
    }  
} 


int main(){

  int m=4000;
  int n=2000;
  
  double* matrix= new double[m*n];
  double* x= new double[n];
  double* y= new double[m];
  double* y_true= new double[m];
  double* x_true= new double[m];
  
  

  std::default_random_engine gen;
  std::normal_distribution<double> distr(0,1); //mean 0 std 1

  for(int i=0; i< m*n; ++i){
    matrix[i] = distr(gen);
  }
  for(int i=0; i< m; ++i){
    y[i] = distr(gen);
  }
  for(int i=0; i< n; ++i){
    x[i] = distr(gen);
  }

  
  std::chrono::time_point<std::chrono::system_clock> start, end;
  std::chrono::duration<double> elapsed_seconds;
  start = std::chrono::system_clock::now();
  //calculate ATAx serial
  matrix_mult(matrix,m, n,x,y_true);
  matrix_transpose_mult(matrix,m,n,y_true,x_true);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end-start;
  std:: cout << "elapsed time: " << elapsed_seconds.count() << "s\n"; 
  

  //multithreading information
  int nthreads = 4;
  spin_barrier bar(nthreads);
  //variables for matrix multiplication
  int block_size = m/nthreads;
  int remainder_block = m- (nthreads-1)* block_size;
  
  //variables for matrix transpose multiplication
  int block_size_transpose = n/nthreads;
  int remainder_block_transpose = n- (nthreads-1)* block_size_transpose;


  start = std::chrono::system_clock::now();
  //calculate distributed naive
  std::vector<std::thread> threads;

  //compute y=Ax
  int block_start = 0;
  int block_start_transpose = 0;
  for(size_t i=0; i < nthreads-1; ++i){
    threads.push_back( std::thread(worker, matrix, m, n,  x,  y, block_start,block_start_transpose, block_size,block_size_transpose, std::ref(bar)  )  );
    block_start += block_size;
    block_start_transpose += block_size_transpose;
  }
  threads.push_back( std::thread(worker, matrix, m, n,  x,  y, block_start,block_start_transpose, remainder_block, remainder_block_transpose, std::ref(bar)  ) );
  
  for(size_t i=0; i < nthreads; ++i){
    threads[i].join();
  }
  end = std::chrono::system_clock::now();
  elapsed_seconds = end-start;
  std:: cout << "elapsed time: " << elapsed_seconds.count() << "s\n"; 
  
  double diff=0;
  norm_squared_diff(&diff,y,1,y_true,1,m);
  std::cout << "difference in serial versus multithread Ax is " << diff << std::endl;
  norm_squared_diff(&diff,x,1,x_true,1,n);
  std::cout << "difference in serial versus multithread ATAx is " << diff << std::endl;
  
  delete[] matrix;
  delete[] x;
  delete[] y_true;
  delete[] y;
  delete[] x_true;
}


double dot(double* result, double* arr1, int stride1, double* arr2, int stride2, int size){

  int loc1,loc2;
  loc1 = loc2 = 0;
  double local_result = 0;
  for(int i=0; i< size;++i){
    local_result += arr1[loc1] * arr2[loc2];
    loc1+=stride1;
    loc2+=stride2;
  }
  *result=local_result;

}

//serial matrix mult
void matrix_mult(double* matrix,int m, int n, double* v_in, double* v_out){
  for(size_t i=0; i < m; ++i){
    dot( &v_out[i], matrix+i*n, 1, v_in,1,n);
  }   
}

//serial matrix transpose mult
void matrix_transpose_mult(double* matrix,int m, int n, double* v_in, double* v_out){
  for(size_t i=0; i < n; ++i){
    dot( &v_out[i], matrix+i, n, v_in, 1 , m);
  }   
}

void norm_squared_diff(double* result, double * arr1, int stride1, double * arr2, int stride2, int size){
  int loc1,loc2;
  loc1 = loc2 = 0;
  double local_result = 0;
  for(int i=0; i< size;++i){
    double temp = arr1[loc1]-arr2[loc2];
    local_result += temp*temp;
    loc1+=stride1;
    loc2+=stride2;
  }
  *result=local_result;
}
