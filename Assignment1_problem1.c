#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>



int array[5][5]={{1,2,3,4,5} , {2,3,5,1,4} , {3,4,2,5,1} , {5,1,4,2,3} ,{4,5,1,3,2} };
int size=5; //n size of the latin matrix
int result=0;//counter for invalid case , will check this later.
// these data are shared by all processes.


//-----------------threads call this function for check rows---------------
void *row(void *RowN){

int R1=0;
int R2=0;
int R3=0;
int R4=0;
int R5=0;
// these counters for each element in a row

int RowNum=(int *)RowN; // casting to int

for(int j=0; j<size;j++){
// loop walk row by row and increment if he find the given number.

if(array[RowNum][j]==1) R1=R1+1;
if(array[RowNum][j]==2) R2=R2+1;
if(array[RowNum][j]==3) R3=R3+1;
if(array[RowNum][j]==4) R4=R4+1;
if(array[RowNum][j]==5) R5=R5+1;
}

if(R1>1 || R2>1 || R3>1 || R4>1 || R5>1 ){
// if statment for check the counters weather repeated more than one.

printf("Row : %d is invalid \n",RowNum);
result=result+1;//increment the result ,"invalid situation"
}
else{

printf("Row : %d is valid \n",RowNum);
}
}

//-------------threads call this function for check columns---------------
void *column(void *ColumnN){

int C1=0;
int C2=0;
int C3=0;
int C4=0;
int C5=0;
// these counters for each element in a column

int ColumnNum=(int *)ColumnN; //casting to int

for(int j=0; j<size;j++){
// loop walk column by column and increment if he find the given number.
if(array[j][ColumnNum]==1) C1=C1+1;
if(array[j][ColumnNum]==2) C2=C2+1;
if(array[j][ColumnNum]==3) C3=C3+1;
if(array[j][ColumnNum]==4) C4=C4+1;
if(array[j][ColumnNum]==5) C5=C5+1;
}

if(C1>1 || C2>1 || C3>1 || C4>1 || C5>1){
//if statment for check the counters weather repeated more than one.

printf("Column : %d is invalid \n",ColumnNum);
result=result+1; //increment the result ,"invalid situation"
}
else{

printf("Column : %d is valid \n",ColumnNum);}
}

//******* Main method ************
int main(){


pthread_t thread1,thread2; // declare names of threads.



// print the matrix .
printf("\n    The Matrix       \n");printf("\n");
for(int i=0 ; i<size ; i++){ //nested loop for printing the matrix
for(int j=0 ; j<size ; j++){
printf("%d , ",array[i][j]);
}
printf("\n");
}

printf("\nRows Check : \n");printf("\n");

//-------------------thread1---------------------------

for(int i=0;i<size;i++){ // loop for each row.
pthread_create(&thread1,NULL,row,i); // i indicate the row number starting with 0.
pthread_join(thread1,NULL);// pass to row runner.
}

printf("\nColumns Check : \n");printf("\n");

//-------------------thread2---------------------------

for(int i=0;i<size;i++){ // loop for each column
pthread_create(&thread2,NULL,column,i); // i indicate the column number starting with 0.
pthread_join(thread2,NULL); // pass to column runner.
}
//-----------------checking latin matrix-------------------
if(result>0)// final result for validity of entire matrix
printf("\nLatin square is invalid . \n");
else
printf("\nLatin square is valid . \n");


return 0;
}
// Raghad Alshabana - Shoroq Alarifi

