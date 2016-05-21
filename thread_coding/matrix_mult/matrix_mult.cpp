#include<iostream>
#include<random>
#include<thread>

double dot(double* result, double* arr1, int stride1, double* arr2, int stride2, int size);

//serial matrix mult
void matrix_mult(double* matrix,int m, int n, double* v_in, double* v_out);

//serial matrix transpose mult
void matrix_transpose_mult(double* matrix,int m, int n, double* v_in, double* v_out);

void mm_worker(double *  matrix, int m, int n, double * v_out, double* v_in, int block_size, int block_start){

  for(int i=0; i< block_size; ++i){
    dot( &v_out[block_start+i], &matrix[(block_start+i)*n], 1, v_in, 1, n  );
  }


}

  void mtm_worker(double *  matrix, int m, int n, double * v_out, double* v_in, int block_size, int block_start){

  for(int i=0; i< block_size; ++i){
    dot( &v_out[block_start+i], &matrix[(block_start+i)], n, v_in, 1, m  );
  }

}


//calculate error
void norm_squared_diff(double* result, double * arr1, int stride1, double * arr2, int stride2, int size);

// main function
int main() {

  int m=200; // rows
  int n=100; // columns
  
  double* matrix= new double[m*n]; // m-by-n matrix
  double* x= new double[n]; // n-vector x 
  double* y= new double[m]; // m-vector y
  double* y_true= new double[m]; // true x
  double* x_true= new double[m]; // true y
  
  

  std::default_random_engine gen; // random number engine
  std::normal_distribution<double> distr(0,1); //mean 0 std 1

  // generate a random matrix
  for(int i=0; i< m*n; ++i){
    matrix[i] = distr(gen);
  }
  // generate a random vector
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
  matrix_mult(matrix, m, n, x, y_true);
  matrix_transpose_mult(matrix, m, n, y_true, x_true);
  end = std::chrono::system_clock::now();
  elapsed_seconds = end-start;
  std:: cout << "elapsed time: " << elapsed_seconds.count() << "s\n"; 

  //multithreading information
  int nthreads = 1;
  int block_start = 0;
  
  //variables for matrix multiplication
  int block_size = m/nthreads;
  int remainder_block = m- (nthreads-1)* block_size;
  
  //variables for matrix transpose multiplication
  int block_size_transpose = n/nthreads;
  int remainder_block_transpose = n- (nthreads-1)* block_size_transpose;


  start = std::chrono::system_clock::now();
  //calculate distributed naive
  std::vector<std::thread> threads;

  for(size_t i=0; i < nthreads-1; ++i){
    threads.push_back( std::thread(mm_worker, matrix, m,n,y,x,block_size, i*block_size ) ) ;
  }
  threads.push_back( std::thread( mm_worker, matrix, m,n,y,x,remainder_block, (nthreads-1)*block_size   ));
  
  for(size_t i=0; i < nthreads; ++i){
    threads[i].join();
  }

  threads.clear();
  
  for(size_t i=0; i < nthreads-1; ++i){
    threads.push_back( std::thread(mtm_worker, matrix, m,n,x,y,block_size_transpose, i*block_size_transpose    ) ) ;
  }
  threads.push_back( std::thread( mtm_worker, matrix, m,n,x,y,remainder_block_transpose, (nthreads-1)*block_size_transpose   ));
  
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
void matrix_mult(double* matrix, int m, int n, double* v_in, double* v_out){
  for(size_t i=0; i < m; ++i){
    dot(&v_out[i], matrix+i*n, 1, v_in, 1, n);
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
