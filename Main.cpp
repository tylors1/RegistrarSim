#include <iostream>

#include "registrarSim.h"
using namespace std;
int main(int argc, char** argv){
	
	RegistrarSim test;
	string x = test.getCMDinput(argc,argv);
	
	bool me = test.checkFileName(x);

	
	//cout<<"the file: "<< x << endl;
	test.runSimulation(x);
	
	
	return 0;
}