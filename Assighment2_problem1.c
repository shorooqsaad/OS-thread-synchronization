#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t lock; // lock controlling access to threads
int length=10; // shared size of array
int arr[]={44,50,38,96,42,47,40,39,46,50};// shared array for all threads

 
 
  // ---------- Median Thread -------------- //
void *MedianRunner(void *arg){  
int median;
int temp;

pthread_mutex_lock(&lock); // aquiring lock
 
        //Sort the array in ascending order    
for (int i = 0; i < length; i++) {    
for (int j = i+1; j < length; j++) {    
if(arr[i] > arr[j]) {    
temp = arr[i];    
arr[i] = arr[j];    
arr[j] = temp;    
}}}
  if (length%2 ==1 ){
    median=arr[(length+1)/2-1];}// check median for odd array
  else{
    median=(arr[length/2-1]+arr[length/2])/2;}//check median for even array
       
          printf("\n \nThe median value is %d | " , median);
       
pthread_mutex_unlock(&lock); // releasing lock
return(NULL); // thread exits (dies)
}    
   
           
           
    // ---------- Mean Thread -------------- //  
     
void *MeanRunner( void *arg){
double mean;

pthread_mutex_lock(&lock);  // acquiring lock
 
for (int i = 0; i < length; i++) {    
mean=mean+arr[i];} // sum all the elements
mean=mean/length; // divided by the number of elements
       
       printf("The mean value is %.1f | " , mean);
   
pthread_mutex_unlock(&lock); // releasing lock
return (NULL);// thread exits (dies)
}
   
   
   
   // ---------- Prime Thread -------------- //  
     
void *PrimeRunner(void *arg){
int j,p=0;

pthread_mutex_lock(&lock); // acquiring lock  

printf("The prime number is ");
   
for(int i=0 ; i<length ; i++){
j=2,p=1;
  // cheack for all prime number(devidable only by 1 and itself)  
  while(j<arr[i]){
        if(arr[i]%j==0){
        p=0;
        break;}
        j++;}
        if(p==1){
        printf("%d , ",arr[i]);}}
        printf("\n");
       
       
pthread_mutex_unlock(&lock); // releasing lock
return (NULL) ;// thread exits (dies)
}
 
 
       

int main(int argc, char *argv[]){
//the parameter just for if we wanna to input in compiler

pthread_t thread[3];

printf("\n");

for(int i=0 ; i<length ; i++) // will walk for all elementa in the array
printf("%d ,",arr[i]);  

// initialaizing mutex
        if(pthread_mutex_init(&lock,NULL) != 0 ){
        printf("\n mutex init has failed ");
        return 1;
        }
       
       pthread_create(&thread[0],NULL,MedianRunner,NULL);
       pthread_join(thread[0],NULL);
       
       
       pthread_create(&thread[1],NULL,MeanRunner,NULL);
       pthread_join(thread[1],NULL);
       
       pthread_create(&thread[2],NULL,PrimeRunner,NULL);
       pthread_join(thread[2],NULL);
     
 
         
 
 // destroying mutex      
pthread_mutex_destroy(&lock);
       
return 0;  



/*   this modification if we want to input the size of threads from           compiler  and the array as an input from the user:  


if(argc != 2 ){
printf("no");
exit(1);}


int size;
size=atoi(argv[1]);
pthread_t thread[size];



int enter;
for(int i=0 ; i<length ; i++){
scanf(" %d ", &enter);
arr[i]=enter;}
*/
   
}


