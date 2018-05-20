#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
#define ROUND_DOWN(x, s) (x/s)*s //round off as per no. of unrolls
#define ITR 100000


void func(int* c , const int* a , const int* b){ /// Scalable
    *c = *a + *b; /// Right now it is for addition
}

void operate(int* c, const int* a, const int* b, int N)
{
  int i = 0;
  //cout<<ROUND_DOWN(N,4)<<endl;
  for(; i < ROUND_DOWN(N, 4); i+=4) /// Loop Unrolling
  {
    func(&c[i] , &a[i] , &b[i]);
    func(&c[i+1] , &a[i+1] , &b[i+1]);
    func(&c[i+2] , &a[i+2] , &b[i+2]);
    func(&c[i+3] , &a[i+3] , &b[i+3]);
  }
  for(; i < N; i++) /// Strip Mining
  {
    func(&c[i] , &a[i] , &b[i]);
  }
}


void operate2(int* c, const int* a, const int* b, int N) /// Normal, without any loop unrolling
{
  int i = 0;

  for(; i < N; i++)
  {
    func(&c[i] , &a[i] , &b[i]);
  }
}

int main(){



    int a[ITR];
    int b[ITR];

    for(int i=0 ; i<ITR ; i++){
        a[i] = i;
    }

    for(int i=0 ; i<ITR ; i++){
        b[i] = 2*i;
    }

    int c[ITR];

    auto start = high_resolution_clock::now();

    operate(c,a,b,ITR);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;


    for(int i=0;i<ITR;i++)c[i] = 0;


    start = high_resolution_clock::now();

    operate2(c,a,b,ITR); /// Optimized function

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;


    cout<<c[0]<<" "<<c[1]<<" "<<c[2]<<" "<<c[3]<<" "<<c[4]<<endl;

    return 0;
}
