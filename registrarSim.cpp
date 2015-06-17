#include <iostream>
#include "registrarSim.h"
#include "genericQueue.h"
#include <fstream>
#include "doublyList.h"
#include <cmath>
using namespace std;

RegistrarSim::RegistrarSim(){
	overfive_idle=0;
	total_idle_time = 0;
	mean_window_idle_time=0;
	num_of_windows=0;
	longest_idle=0;//satisfies #6
	windows_calc_num=0;
	num_of_students=0;


	//for questions 1-4
	total_wait_time = 0;
	mean_waiting = 0;

	//still have yet to be calculated, can only be done once LL is sorted
	median_waiting=0;
	longest_waiting=0;
	overten_waiting=0;
	
	
	
	
	
}
RegistrarSim::~RegistrarSim(){
	//cout<<"object destroyed"<<endl;
}
//this function grabs the file that the user types into the command line
string RegistrarSim::getCMDinput(int argc, char* argv[]){
	string fileIn =  "";
    for(int i = 1; i < argc;)//argc the number of arguements
    {
        fileIn += argv[i];//argv the array of arguements
        if(++i != argc)
            fileIn += " ";
    }
    return fileIn;
}
//this function tests to see if the user-cmd input is a valid file
bool RegistrarSim::checkFileName(string userFile){
	if(userFile.empty()){
		cout<<"no user input"<<endl;
		return false;
	}
	else{
		fstream tryread(userFile.c_str());
		if (tryread.is_open()){
			tryread.close();
			return true;
		}
		else{
			return false;
		}
	}

}
void RegistrarSim::runSimulation(string theUserFile){
	GenQueue<int> theQueue;
	int* the_windows;
	int* idle_times;
	int* spotOF;//this keeps track if a window has been open over 5 mins
			
	ifstream readingFile(theUserFile.c_str());
	int temp;
	int count = 0;//count will only be zero for the first time through the loop in order to get the number of windows open
	int numOfPeople = 0;
	int theTime = 1;
	//this while loop sorts through the data
	while(!readingFile.eof()){
		//printWindows(the_windows);
		//cout<<"the queue"<<endl;
		//theQueue.printQueue();
		readingFile>>temp;

		
		if(numOfPeople != 0){
		
			//if a window is open you don't need to add to queue
			
			if(windowIsOpen(the_windows)!=-1){
				
				the_windows[windowIsOpen(the_windows)]=temp;
			
			}
			else{
			
				theQueue.insert(temp);
				student_wait_times.addBack(0);
			}
			calcIdleTimes(idle_times,the_windows,spotOF);
			numOfPeople--;
			count = 1;
		}
		else{
			if(count == 0){
				num_of_windows = temp;
				windows_calc_num = temp;
				the_windows = new int[num_of_windows];
				idle_times = new int[num_of_windows];
				spotOF = new int[num_of_windows];
				buildEmptyArray(spotOF);
				buildEmptyArray(idle_times);
				buildEmptyArray(the_windows);//set all values in array = to 0
			}
			//set the time
			else if (count == 1){
				if(theTime!=temp){
					//calculate waiting time between each time bracket 
					int difference = temp - theTime;
					//calc between times
					while(difference!=0){
						total_wait_time+=theQueue.getSize();
						


						for(int i = 0; i < num_of_windows; ++i){
							if(the_windows[i]!=0){
								the_windows[i]-=1;


							
							}
							else{
								total_idle_time+=1;
								idle_times[i]+=1;
								the_windows[i]=theQueue.remove();

								wait_times_list.addBack(student_wait_times.removeFront());//when a student leaves the LL that calculates the wait-time, add that time to wait_time_list
								//to keep track of total time each student spent in line
								//there are two LL one to keep track of the time spent in the queue and one to store the total time spent in queue
								//wait_times_list is the one you need to sort for calculating questions 1-4
								//there has to be two LL because you need to stop adding to the wait-time of the student if the student left the queue
							}

						}
						//cout<<"student_wait_times"<<endl;
						//student_wait_times.printList();
						student_wait_times.addToData();
						


						difference-=1;
					
					}
					

				}
				theTime = temp;
			}
			else if (count == 2){
				numOfPeople = temp;
				num_of_students += temp;
			}
			else{
				cout<<"there was an error"<<endl;
			}
			count++;
		}
		
	}
	//cout<<"ENTER LAST LOOP%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;

	//this is after the file has been read and the queue and windows aren't empty yet
	while(!isEmpty(the_windows)){

		//printWindows(the_windows);
		total_wait_time+=theQueue.getSize();
		for(int i = 0; i < num_of_windows; ++i){
			if(the_windows[i]!=0){
				the_windows[i]-=1;
			}
			else{
				total_idle_time+=1;
				idle_times[i]+=1;
				if(!theQueue.isEmpty()){
					the_windows[i]=theQueue.remove();
					wait_times_list.addBack(student_wait_times.removeFront());
				}
			}
		}
		//student_wait_times.printList();
		student_wait_times.addToData();
		calcIdleTimes(idle_times,the_windows,spotOF);

	}
	//theQueue.printQueue();





	cout<<"Max wait time for each person"<<endl;
	wait_times_list.printList();

	wait_times_list.sortList();
	//cout<<"after sorted"<<endl;
	//wait_times_list.printList();

	cout<<"Longest Waiting: "<<wait_times_list.getBack()<<endl;
	overten_waiting = wait_times_list.overTen();
	cout<<"Waiting over ten mins: "<< overten_waiting<<endl;
	median_waiting = wait_times_list.getMedian();
	cout<<"Median waiting: "<<median_waiting<<endl;



	//mean_waiting=total_wait_time/num_of_students;
	mean_waiting=wait_times_list.getMean();
	cout<<"Mean waiting: "<<mean_waiting<<endl;
	cout<<"Over five: "<<overfive_idle<<endl;
	cout<<"Longest idle: "<<longest_idle<<endl;
	mean_window_idle_time=total_idle_time/windows_calc_num;
	
	cout<<"Mean window idle time: "<<mean_window_idle_time<<endl;
	//theQueue.printQueue();

}
void RegistrarSim::calcIdleTimes(int* i, int* w, int* s){
	
	for(int k = 0; k < num_of_windows; ++k){
		if(w[k]!=0){
			
			i[k]=0;
		}
		if(i[k]>=5){
			
			//this statement checks to see if that window was already open over 5 minutes
			if(s[k]!=1){
				overfive_idle+=1;
				s[k]=1;
			}
			if(i[k]>longest_idle){
				longest_idle = i[k];//if the idle time is greater than the current longest update it
			}
		}
	}
}
//build an array of zeroes
void RegistrarSim::buildEmptyArray(int* w){
	for(int i = 0; i < num_of_windows; ++i)
	{
		w[i]=0;
	}

}
//print arrays to screen to see what's going on
void RegistrarSim::printWindows(int* w){
	cout<<"printing windows"<<endl;
	for(int i = 0; i < num_of_windows; ++i){
		cout<<w[i]<<endl;
	}
}

//finds the first spot that has an open window and returns it so you can add a person from the queue to that window
int RegistrarSim::windowIsOpen(int* windows){
	for(int i = 0; i < num_of_windows; ++i){
		
		if(windows[i] == 0){
		
			return i;
		}
	}
	return -1;
	cout<<"All the windows are full"<<endl;
}
bool RegistrarSim::isEmpty(int* windows){
	
	for(int i = 0; i < num_of_windows; ++i){
		if(windows[i]!=0){
			return 0;
		}
	}
	return 1;
}