#include<stdio.h> 
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>

void *thread_function();
pthread_mutex_t l;
int wait_time=0,turnaround_time=0,n;

int main()
{

pthread_mutex_init(&l,NULL);
pthread_t a_thread;
pthread_create(&a_thread,NULL, thread_function, NULL);
pthread_join(a_thread,NULL);
printf("\n=======================================\n\n");
printf("Thread joined\n");
printf("\nAverage Waiting Time= %f\n",wait_time*1.0/n); 
sleep(1);
printf("Avg Turnaround Time = %f",turnaround_time*1.0/n);

}

void *thread_function() 
{
  int count,j,time,remain,flag=0,timequ; 
  int at[10],bt[10],rt[10]; 
  printf("Enter Total Process:\t "); 
  scanf("%d",&n); 
  remain=n; 
  for(count=0;count<n;count++) 
  {
    pthread_mutex_lock(&l); 
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1); 
    scanf("%d",&at[count]); 
    scanf("%d",&bt[count]); 
    rt[count]=bt[count];
    pthread_mutex_unlock(&l); 
  } 
  printf("Enter Time Quantum:\t"); 
  scanf("%d",&timequ); 
  printf("\n\nProcess\t||| Turnaround Time ||| Waiting Time\n\n"); 
  printf("=======================================\n\n");
  for(time=0,count=0;remain!=0;) 
  { 
    if(rt[count]<=timequ && rt[count]>0) 
    { 
      time+=rt[count]; 
      rt[count]=0; 
      flag=1; 
    } 
    else if(rt[count]>0) 
    { 
      rt[count]-=timequ; 
      time+=timequ; 
    } 
    if(rt[count]==0 && flag==1) 
    { 
      remain--; 
      printf("P[%d]\t|||\t  %d\t    |||\t  %d\n",count+1,time-at[count],time-at[count]-bt[count]); 
      wait_time+=time-at[count]-bt[count]; 
      turnaround_time+=time-at[count]; 
      flag=0; 
    } 
    if(count==n-1) 
      count=0; 
    else if(at[count+1]<=time) 
      count++; 
    else 
      count=0; 
  }  
}
