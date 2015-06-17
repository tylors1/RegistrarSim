#ifndef REGISTRARSIM_H
#define REGISTRARSIM_H
#include "doublyList.h"
#include <iostream>
using namespace std;

class RegistrarSim{
	public:
		RegistrarSim();
		~RegistrarSim();

		string getCMDinput(int,char**);
		bool checkFileName(string);
		void readThroughFile(string);
		void runSimulation(string);
		int windowIsOpen(int*);

		double num_of_students;
		double mean_waiting;
		int median_waiting;
		int longest_waiting;
		int overten_waiting;
		double total_wait_time;


		double mean_window_idle_time;//total_idle_time/num_of_windows  this satisfies #5
		double total_idle_time;
		int num_of_windows;
		double windows_calc_num;
		int longest_idle;//satisfies #6
		int overfive_idle;//satisfies #7

		void printWindows(int*);
		void buildEmptyArray(int*);
		void calcIdleTimes(int*,int*,int*);
		bool isEmpty(int*);


		
		DoublyList<int> student_wait_times;
		DoublyList<int> wait_times_list;


};
#endif