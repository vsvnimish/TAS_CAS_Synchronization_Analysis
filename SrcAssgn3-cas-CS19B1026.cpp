#include<iostream>  
#include <pthread.h>
#include <sys/time.h>
#include<unistd.h>
#include<atomic>
#include <ctime>
#include <chrono>
#include <iomanip>
#include<string>
#include<algorithm>
#include <thread> 
#include <random>
#include<string.h>
#include<random>
#include<fstream>
using namespace std;
double ma=-1;
long long k, noofthreads;
double l1,l2;
struct tim{ //this structure will be used for storing timestamps
long long id; //thread id will be stored
string r;    //requested time for a particular iteration
string e;    //entered time for a particular iteration
string x;    //exited time for a particular iteration
long long rno; //particular iteration out of k iterations will be stored
double avgwait; //total amount of time spent in entry sec will be stored
};
tim* info;
atomic<int> lock;
void getTimestamp(long long id,long long n,long long gh) {//this function is for getting current time
  const auto now = std::chrono::system_clock::now();
  const auto nowAsTimeT = std::chrono::system_clock::to_time_t(now);
  const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
  now.time_since_epoch()) % 1000;
  std::stringstream nowSs;
  nowSs
      << std::put_time(std::localtime(&nowAsTimeT), "%T")
      << ':' << std::setfill('0') << std::setw(3) << nowMs.count();
  string s=nowSs.str();
  (info + id*k + n)->id=id;//thread id will be stored  we will not get synchronization isssue because each thread will acces it's own location in
                            //global array 
  if(gh==0){    //gh tells whether the thread is requesting or exiting or entering the CS
     (info + id*k + n)->r=s; 
  }
  else if(gh==1){
    (info + id*k + n)->e=s;
  }
  else if(gh==2){
   (info + id*k + n)->x=s;
  } 
  (info + id*k + n)->rno=n;//iteration "n" will be stored   
}
void entry_sec(){
  int x=0;
  int y=1;
  while(!lock.compare_exchange_strong(x,y)){//if currently cs is unlocked then this thread                                            
    x=0;                                    //will be given permission to enter CS and CS                                              
    y=1;                                    //will be locked
  } 
  //if CS is unlocked we will exit from loop
}
void exit_sec(){
 lock=0;  //this will unlock CS
}
void* testCS(void* tem){
 long long* seg =(long long*)tem;
 long long id=*seg;
 long long i;
 double number ;
 int seed =  
    chrono::system_clock::now().time_since_epoch().count(); 
    default_random_engine generator (seed);    
 struct timeval start,end;
 for(i=0;i<k;i++){
     getTimestamp(id,i,0);//current time will be stored in array 
     gettimeofday(&start, NULL);
     double ms = start.tv_sec * 1000.0 + start.tv_usec / 1000.0;      
     entry_sec();
     gettimeofday(&end, NULL);
     double sm = end.tv_sec * 1000.0 + end.tv_usec / 1000.0;
     (info + id*k + i)->avgwait=sm-ms;
     if(ma<sm-ms)//ma is maximum worst case time taken for thread to enter cs
         ma=sm-ms;//update worst case time taken for thread to enter cs even ma is global we will not get synchronization issues because
                  //we are updating ma in CS so no other thread can manipulate it while other is manipulating 
     getTimestamp(id,i,1);
     exponential_distribution<double> distribution1 (double(1/l1));
     number= distribution1(generator); 
     chrono::duration<double> period (number); 
     this_thread::sleep_for(period/1000.0);//simulation of critical section
     exit_sec();//thread will be exited from critical section
     getTimestamp(id,i,2);
     exponential_distribution<double> distribution2 (double(1/l2));
     number = distribution2(generator); 
     chrono::duration<double> period1 (number); 
     this_thread::sleep_for(period1/1000.0);//simulation of remainder section
 } 
 return NULL;     
}
bool compare(tim a,tim b){ 
 if(a.e!=b.e)//in sorting more priority will be given to entry time of CS
    return (a.e<b.e);
 if(a.id!=b.id) //second priority will be given to thread id
  return a.id>b.id;
 return !(a.rno>b.rno);//third priority will be given to iteration number out of k times
} 
int main(int argc, char *argv[]){
 long long i,j,z;
 //ifstream ci("inp.txt");
 lock=0;                    
 cin>>noofthreads>>k>>l1>>l2;
 pthread_t t[noofthreads];
 long long *sender;
 sender=(long long*)malloc(sizeof(long long)*noofthreads);
 info=new tim[noofthreads*k];
 for(i=0;i<noofthreads;i++){
    sender[i]=i;
 }
 for(i=0;i<noofthreads;i++){
    pthread_create(&t[i],NULL,testCS,&sender[i]);//thread will be created and testCS function will be executed and we will pass thread id as
                                                  //an argument to testCS
 }
 for(i=0;i<noofthreads;i++){//waiting for all slave threaeds to finish their tasks
    pthread_join(t[i],NULL);
 }
 sort(info,info+noofthreads*k,compare);//sort array based on entry time of CS
 double sum=0;
 for(i=0;i<noofthreads*k;i++){
      sum+=info[i].avgwait;//sum of all waiting time's for all threads and for all it's iteration
      cout<<info[i].rno+1<<"th CS Requested at "<<info[i].r<<" by thread "<<info[i].id+1<<"\n";
      cout<<info[i].rno+1<<"th CS Entered at "<<info[i].e<<" by thread "<<info[i].id+1<<"\n";
      cout<<info[i].rno+1<<"th CS Exited at "<<info[i].x<<" by thread "<<info[i].id+1<<"\n";
 }
 cout<<"Average time taken to enter CS by each thread : "<<sum/(noofthreads*k)<<" milliseconds\n";
 cout<<"worst case time taken to enter CS by thread : "<<ma<<" milliseconds\n";
 return 0;
}
