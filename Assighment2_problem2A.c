/*This program provide our attempt to solve problem2(concrruncy way) :

here we use one loop for all persons so
 - at first sara will finish preparing one capsule
 - then mohammed will making coffee from this capsule that he taken from sara
 - then abdullah will serve the coffee that mohammed made
 
 so these steps will repeated until reach the MAX
*/


#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


// global varibles
// initializing semaphores
sem_t Prepare_Capsul;
sem_t Make_Coffee;
sem_t Serve_Coffee;
sem_t Machine;
int MAX=5;



void* Sara(void *p){
printf("sara : capsul is ready\n");}


void* Mohammed(void *p){
printf("mohammed : machine is ready\n");}


void* Abdullah(void *p){
printf("abdullah : coffee served\n");}



int main(){

pthread_t thread[3];
/*  initializing semaphores with MAX varible so we will use "wait" to   decrement it until reach "ZERO" */
sem_init(&Prepare_Capsul,0,MAX);
sem_init(&Make_Coffee,0,MAX);
sem_init(&Serve_Coffee,0,MAX);

// initializing binary semaphore
sem_init(&Machine,0,1);

printf("we want made %d cups of coffee\n\n",MAX);

for(int i=0;i<10;i++){ // assume a random number for loop
printf("%d- \n",i+1);


 //--------------------------START WITH SARA-------------------------------
 
sem_wait(&Prepare_Capsul); // acquire sara's lock
sem_wait(&Machine); // acquire machine so mohammed can't use it

pthread_create(&thread[0],NULL,Sara,NULL);
pthread_join(thread[0],NULL);

MAX=MAX-1; // decrement MAX if sara made a capsule
sem_post(&Machine); // release machine so mohammed can use it

 //--------------------------START WITH MOHAMMED--------------------------

 
sem_wait(&Make_Coffee); // acquire mohammed's lock
sem_wait(&Machine); // aquire machine so he can only use it

pthread_create(&thread[1],NULL,Mohammed,NULL);
pthread_join(thread[1],NULL);

sem_post(&Machine); // release it

 //--------------------------START WITH ABDULLAH---------------------------


sem_wait(&Serve_Coffee); // acquire abdullah's lock

pthread_create(&thread[2],NULL,Abdullah,NULL);
pthread_join(thread[2],NULL);

if(MAX==0){ // here sara will stop made capsules
printf("\nSara reach the MAX capsules\n");
// our code work concurrency so when sara exceed the MAX both mohammed and   abullah shall stop working
break;} // will stop working in for loop

}
// destroying semaphores
sem_destroy(&Machine);
sem_destroy(&Make_Coffee);
sem_destroy(&Serve_Coffee);
sem_destroy(&Prepare_Capsul);

return 0;
}