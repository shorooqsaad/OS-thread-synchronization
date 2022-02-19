/*This program provide our attempt to solve problem2 in(sequential way):

here we use three loop for each person so
 - at first sara will finish preparing all capsules(MAX)
 - then mohammed will making coffee from all capsules that he taken from sara
 - then abdullah will serve all coffee that mohammed made
*/



#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t Prepare_Capsul;
sem_t Make_Coffee;
sem_t Serve_Coffee;

int MAX=5;
int Capsuls=0; //number of capsules that sara will prepare
int coffee=0; // number of coffee that mohammed will make

void* Sara(void *p){
Capsuls=Capsuls+1; // increment the capsules
printf("sara : capsul is ready\n");

}
void* Mohammed(void *p){
Capsuls=Capsuls-1; // decrement the capsule the mohammed take
printf("mohammed : machine is ready\n");
coffee=coffee+1; // increment the coffee that mohammed make
}
void* Abdullah(void *p){
coffee=coffee-1; // decrement the coffee the abdulaah will serve
printf("abdullah : coffee served\n");
}
int main(){

pthread_t thread[3];
/*  initializing semaphores with ZERO so we will use "post/signal" to   increment it until reach "MAX" */
sem_init(&Prepare_Capsul,0,0);
sem_init(&Make_Coffee,0,0);
sem_init(&Serve_Coffee,0,0);


printf("we want made %d cup of coffee\n\n",MAX);

 //-------------------------- SARA LOOP -------------------------------
for(int i=0;i<10;i++){
printf("%d - ",i+1);

sem_post(&Prepare_Capsul); //increment sara's lock

pthread_create(&thread[0],NULL,Sara,NULL);
pthread_join(thread[0],NULL);


if(Capsuls==MAX){
 printf("Sara mades the MAX capsuls\n");
 break;}
}
printf("\n");

 //-------------------------- MOHAMMED LOOP -------------------------------
 
for(int i=0;i<10;i++){
printf("%d - ",i+1);

sem_post(&Make_Coffee); // increment mohammed's lock

pthread_create(&thread[1],NULL,Mohammed,NULL);
pthread_join(thread[1],NULL);

if(Capsuls==0){
 printf("Mohammed Finish the all capsuls\n");
 break;}
}
printf("\n");

 //-------------------------- ABDULLAH LOOP -------------------------------
 
 
for(int i=0;i<10;i++){
printf("%d - ",i+1);

sem_post(&Serve_Coffee); // increment abdullah's lock

pthread_create(&thread[2],NULL,Abdullah,NULL);
pthread_join(thread[2],NULL);

if(coffee==0){
 printf("Abudullah serve the all coffee \n");
 break;}
}
printf("\n");

//-------------------------- FINISH LOOPs -------------------------------

//destroying semaphores
sem_destroy(&Make_Coffee);
sem_destroy(&Serve_Coffee);
sem_destroy(&Prepare_Capsul);

return 0;
}