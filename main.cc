/*
File: main.cc
Author: Jorge Gonzalez
Procedures:
- main - simulates three partitioning practices, equal, unequal and dynamic
 */
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;


struct process                                                            // struct that will hold the information for each partition and process
{                                                                         // will contain the memory size for each process in a cetain range as well for each partition
  int memory_size;                                                        // time unit randomize in a certain range where it will decrement over time
  int time_to_execute;                                                    // will determine if the partition is empty or not
  bool empty = true;
}memory;

/*********************************************
int main()
Author: Jorge Gonzalez
Date: 10/13/19
Description: Runs a simulation for the three types of partitioning for 1000 processes,runs 1000 simulations.
*****NOTE: since it runs 1000 simulations for 1000 processes, the program takes a long time to finish****
Parameter:
main O/P  int   status code
**********************************************/
int main()
{
  process num1[1000];                                                     // 1000 processes will be simulated
  process num2[7];                                                        // 7 partitions will be used for equal and unequal partitioning
  process *processes = new process[1000];                                 // pointer for the processes and partitions
  process *partitions = new process[7];

  int memoryRange, timeRange;
  int numPartitions = sizeof(num2)/sizeof(num2[0]);                       //determine the number of partitions and processes in the array
  int numProcesses = sizeof(num1)/sizeof(num1[0]);

  srand (time(NULL));                                                     // set a random seed 

  for(int i = 0; i < numPartitions; i++) 
    {
      partitions[i].memory_size = 7;                                      // partitions will have a set size of 7mb, used for equal partitioning
    }
  
  for(int i = 0; i < numProcesses; i++)                                   // every process will have a random memory size and time unit to execute, within a certain range 
    {
      memoryRange = rand() % 8 + 1;
      processes[i].memory_size = memoryRange;
      timeRange = rand() % 10 + 1;
      processes[i].time_to_execute = timeRange;
    }

    
 
  int time = 0;                                                           // time unit counter start at 0
  int totalTime = 0, totalTime2 = 0, totalTime3 = 0;
                                                                          // **this segment is for equal partitioning**   
  //  for(int round = 0; round < 1000; round++)                               //run 1000 simulations
	// {
  for(int i = 0; i < numProcesses; i++)                                   // outer loop that will go through each process 
      {
      outerloop:                                                          //label to jump back to if an empty spot was found
	time++;                                                           //time incremented every time looped
	for(int y = 0; y < numPartitions; y++)                            // loop through every partition to check if it is empty
	  {
	    cout << "current process: " << i << endl;
	    cout << "testing for partition: " << y << endl;
	    if(partitions[y].empty == true)                               //if empty, enter partition and set the time unit as well as mark it as nonempty
	      {
		cout << "partition was empty, entering..." << endl;
		partitions[y].time_to_execute = processes[i].time_to_execute;
		partitions[y].empty = false;
		goto outerloop;                                           // jump back to the beginning of the partitions
	      }
	    else{                                                         //if current partition is full, display message on move on to the next one
	      cout << "partition was full, next..." << endl;
	    }
	    
	    if(partitions[y].time_to_execute > 0)                         //if the time unit is greater than 0, decrement it by 1 and display it
	      {
		partitions[y].time_to_execute -= 1;
		cout << "execution timer: " << partitions[y].time_to_execute << endl;
		if(partitions[y].time_to_execute == 0 || partitions[y].time_to_execute < 0) //when time unit finally reaches 0, open the partition back up by setting empty variable to true
		  {
		    cout <<"partition has opened" << endl;
		    partitions[y].empty = true;
		  }
	      }
	    //if all partitions are full, display message
	   
	  }
	//if all partitions are full, display message
	if(partitions[0].empty == false && partitions[1].empty == false && partitions[2].empty == false && partitions[3].empty == false && partitions[4].empty == false && partitions[5].empty == false && partitions[6].empty == false)
	  {
	    cout << "all were full restarting search" << endl;
	    i = i-1;
	  }
	
	totalTime = totalTime + time;
      }
  // }
  //after every process is finished, display the time unit it took to finish
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Done..." << endl;
   cout << "time for equal partitioning: " << time << endl;
   cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
 
   /*
     this section focuses on unequal partitioning
    */
   process *unequalProcess = new process[1000];                              // set new processes and partition pointers
  process *unequalPartition = new process[7];

  for(int i = 0; i < numProcesses; i++)
    {
      memoryRange = rand() % 16 + 1;
      unequalProcess[i].memory_size = memoryRange;
      timeRange = rand() % 10 + 1;
      unequalProcess[i].time_to_execute = timeRange;
    }
  unequalPartition[0].memory_size = 2;                                      //following initialization sets memory sizes for the partitions
  unequalPartition[1].memory_size = 4;
  unequalPartition[2].memory_size = 6;
  unequalPartition[3].memory_size = 8;
  unequalPartition[4].memory_size = 8;
  unequalPartition[5].memory_size = 12;
  unequalPartition[6].memory_size = 16;

  int time2 = 0;                                                            // second time counter for unequal partitioning
  // for(int round = 0; round < 1000; round++)
  // {
  for(int i = 0; i < numProcesses; i++)                                     // loop through every processes
	{
	outerloop2:                                                         // label to jump back to after partition is found open
	  time2++;                                                          // increment timer
	  for(int y = 0; y < numPartitions; y++)                            // go through each partition to check if it is empty and if the process is small enough to fit in the partition
	    {
	      cout << "current process: " << i << endl;
	      cout << "testing for partition: " << y << endl;
	      if(unequalPartition[y].empty == true && unequalProcess[i].memory_size <= unequalPartition[y].memory_size)  //if process fits in partition and if the partition is free, insert it and set empty as false
		{
		  unequalPartition[y].time_to_execute = unequalProcess[i].time_to_execute;
		  unequalPartition[y].empty = false;
		  goto outerloop2;
		}
	      else                                                           // else display message and move on
		{
		  cout << "partition was full, next..." << endl;
		}
	      if(unequalPartition[y].time_to_execute > 0)                   //if the time unit for the process in the partition is greater than 0, decrement it by 1
		{
		  unequalPartition[y].time_to_execute -=1;
		  cout << "Execution timer: " << unequalPartition[y].time_to_execute << endl;  
		  if(unequalPartition[y].time_to_execute == 0 || unequalPartition[y].time_to_execute < 0)              //if the timer reaches zero, open up the partition
		    {
		      cout <<"partition has opened" << endl;
		      unequalPartition[y].empty = true;
		    }
		}
	    }
	      //if all partitions are full, display message
	  if(unequalPartition[0].empty == false && unequalPartition[1].empty == false && unequalPartition[2].empty == false && unequalPartition[3].empty == false && unequalPartition[4].empty == false && unequalPartition[5].empty == false && unequalPartition[6].empty == false)
	    {
	      cout << "all partitions were full, restarting search" << endl;
	      i = i-1;
	    }
	    }
  totalTime2 = totalTime2 + time2;
  // }

  // once done, display time for unequal partitioning and equal partitioning
      cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
      cout << "Done..." << endl;
      cout << "Time for unequal partitioning: " << time2 << endl;
      cout << "Time for equal partitioning: " << time << endl;
      cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
   
      process *dynamicProcess = new process[1000];                                            //this section focuses on dynamic partitioning
      process dynamicPartition[6];                                                         // create a 2D array that will hold certain amount of processes in the partition

      for(int i = 0; i < numProcesses; i++)
	{
	  memoryRange = rand() % 16 + 1;
	  dynamicProcess[i].memory_size = memoryRange; 
	  timeRange = rand() % 10 + 1;
	  dynamicProcess[i].time_to_execute = timeRange;
	  
	}
      for(int i = 0; i < 5; i++)
	{
	  dynamicPartition[i].memory_size = 0;
	  dynamicPartition[i].time_to_execute = 0;
	}
      int time3 = 0;                                                                          // create new timer for dynamic partitioning
      int size = 0;
      //  for(int round = 0; round < 1000; round++)
      //	{
      for(int i = 0; i < numProcesses;i++)                                                    // loop through every processes
	{
	outerloop3:
	  size = 0;
	  time3++;                                                                            // increment timer
	  for(int y = 0; y < 5; y++)                                                          // loop through each process that is in the partition, if any
	    {
	      size = dynamicProcess[i].memory_size;                                     // count the amount of memory in the partition with the current process
	      for(int k = 0; k < 5; k++)
		{
		  size += dynamicPartition[k].memory_size;
		}
	      if(size < 64)                                                                   // if the amount of memory is less than the limit, insert it
		{
		  if(dynamicPartition[y].empty == true)                                    // check as well if there is any space left in the partition 
		    {
		      dynamicPartition[y].memory_size = dynamicProcess[i].memory_size;                  //insert the memory size as well as the time unit
		      dynamicPartition[y].time_to_execute = dynamicProcess[i].time_to_execute;
		      dynamicPartition[y].empty = false;                                    // mark the section of the partition as full
		      goto outerloop3;                                                       // jump back to the beginning
		    } 
		}
	      else                                                                           //if not enough space for the process, display message
		{
		  cout << "partition was full, waiting till empty spot is open..." << endl;
		}
	      if(dynamicPartition[y].time_to_execute > 0)                                 // if the timer for the process in the partition is greater than 0, decrement it by 1
		{
		  dynamicPartition[y].time_to_execute-=1;
		  cout << "Partition: " << y << "..Execution time: " << dynamicPartition[y].time_to_execute << endl;
		  if(dynamicPartition[y].time_to_execute == 0)                            // if the timer equals 0, free that space up from the partition
		    {
		      cout <<"partition" << y << " has opened" << endl;
		      dynamicPartition[y].empty = true;
		    }
		}
	    }
	      // if all space is taken, notify the user and restart the search
	      if(dynamicPartition[0].empty == false && dynamicPartition[1].empty == false && dynamicPartition[2].empty == false && dynamicPartition[3].empty == false && dynamicPartition[4].empty == false && dynamicPartition[5].empty == false)
		{
		  cout << "All partitions are full, restarting search" << endl;
		  i = i-1;
		}
	    }
	
      totalTime3 += time3;
      //	}
                          
      int avgTime, avgTime2, avgTime3;

      avgTime = totalTime / 1000;
      avgTime2 = totalTime2 / 1000;
      avgTime3 = totalTime3 / 1000;
                                                                    //displays all the time it took to finish 1000 processes in the three kind of partitioning
      cout << "++++++++++++++++++++++++++++++++++++++++" << endl;
      cout << "Done..." << endl;
      cout << "Time for equal partitioning: " << time << endl;	
      cout << "Time for unequal partitioning: " << time2 << endl;
      cout << "Time for dynamic partitioning: " << time3 << endl;
      cout << "++++++++++++++++++++++++++++++++++++++++" << endl;

}
