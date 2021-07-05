
/// \file

///
/// ... text ...
///




#include <fstream>
#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;
string process_name;
string file_name; 
string msg5 = "P";
std::ofstream outfile;
struct timespec delta = {0 /*secs*/, 300000000 /*nanosecs*/}; //0.3 sec
void signalHandler( int signum ) {
	//cout << "Interrupt signal (" << signum << ") received.\n";
	outfile.open(file_name.c_str(), std::ios_base::app);
	if(signum==15){

		outfile << (process_name+" received signal " + to_string(signum)+ ", terminating gracefully"+"\n");

		exit(signum);
	}
	else{
		outfile << (process_name+" received signal " + to_string(signum)+"\n");

	}
	outfile.close();

}


int main(int argc,char *argv[]) {


/// Comments I would like to be documented in as well
	process_name=argv[0];
	file_name=argv[1];



	outfile.open(file_name.c_str(), std::ios_base::app);

	outfile << (process_name +" is waiting for a signal"+"\n");
	outfile.close();


	signal(SIGINT, signalHandler);
	signal(SIGHUP, signalHandler);
	signal(SIGILL, signalHandler);
	signal(SIGTRAP, signalHandler);
	signal(SIGFPE, signalHandler);
	signal(SIGSEGV, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGXCPU, signalHandler);
	while(1) {
		sleep(1);

	}
return 1;
}

