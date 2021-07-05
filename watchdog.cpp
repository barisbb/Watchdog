
/// \file

/// \brief  Main function
/// \param  argc An integer argument count of the command line arguments
/// \param  argv An argument vector of the command line arguments
/// \return an integer 0 upon exit success


#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <csignal>
#include <list>
#include <vector>
#include <map>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
int num_of_process;
using namespace std;
#include <bits/stdc++.h>





unsigned int microsecond = 1000000;
string msg5 = "P";

vector<int> pids;
vector<int> ids;
string inputPath1;
string inputPath2;
pid_t p;
int unnamedPipe;
char arr1[80];
pid_t pid;
pid_t pid1;
ofstream myfile1;
ofstream myfile2;
string process_name_2;
struct timespec delta = {0 /*secs*/, 3000000 /*nanosecs*/}; //0.3 sec



int getIndex1(vector<int> pids,unsigned int chpid){
	int index=0;

	for(int i=0;i<num_of_process;i++){


		if(pids[i]==chpid){

			index=i+1;

		}
	}
	return index;
}

void writeToFile(ofstream &outputFile, string x)
{
	outputFile << x ;
	outputFile.close();
}
void signalHandler( int signum ) {

	myfile1 << ("Watchdog is terminating gracefully\n");
	myfile1.close();
	exit(signum);

}


int main(int argc, char *argv[]){



	num_of_process=stoi(argv[1]);
	inputPath1=argv[2];
	inputPath2=argv[3];
	myfile1.open(inputPath1);
	myfile2.open(inputPath2);
	char * myfifo = (char*) "/tmp/myfifo";
	mkfifo(myfifo, 0644);
	unnamedPipe = open(myfifo,O_WRONLY);
	for(int i=0;i<num_of_process;i++) // loop will run n times (n=5)
	{

		pid = fork();
		if(pid == 0)
		{

			string process_name = msg5+to_string(i+1);
			//	myfile1 << (process_name +" is started and it has a pid of " + to_string(getpid())+"\n");

			writeToFile(myfile1,process_name +" is started and it has a pid of " + to_string(getpid())+"\n");


			string msg4=process_name+" "+to_string(getpid());
			const char* msg3 = msg4.c_str();
			write(unnamedPipe, msg3, 30);



			execl("/home/baris/eclipse-workspace/process/src/process", process_name.c_str(),inputPath2.c_str(), NULL);
			break;

		}
		else{
			pids.push_back(pid);
			nanosleep(&delta, &delta);

			if(i==num_of_process-1){
				string process_name = msg5+"0";
				string msg4=process_name+" "+to_string(getpid());
				const char* msg3 = msg4.c_str();
				write(unnamedPipe, msg3, 30);




			}

		}
	}
	for(int i=2;i<num_of_process+1;i++) {
		ids.push_back(i);
	}


	while(1) {

		pid_t chpid = wait(NULL);

		int index_process_name=getIndex1(pids,chpid);



		if(index_process_name==1){

			pids.erase(pids.begin() + index_process_name-1);

			myfile1 << ("P1 is killed, all processes must be killed\nRestarting all processes")<<endl;
			printf("ddddddddd\n");
			//myfile1.close();
			//myfile1 << ("Restarting all processes\n");
			//	writeToFile(myfile1,"P1 is killed, all processes must be killed\nRestarting all processes\n");
			//	writeToFile(myfile1,"Restarting all processes\n");

			for(int i=0;i<pids.size();i++) {
				nanosleep(&delta, &delta);
				kill(pids[i] , SIGTERM);
			}
			pids = {};
			for(int j=0;j<num_of_process;j++) // loop will run n times (n=5)
			{
				pid1 = fork();
				if(pid1==0){

					//	myfile1 << ("P" +to_string(j+1)  +" is started and it has a pid of "+to_string(getpid())+"\n");

					//	myfile1.close();

					writeToFile(myfile1,"P" +to_string(j+1)  +" is started and it has a pid of "+to_string(getpid())+"\n");

					process_name_2 = msg5+to_string(j+1);

					string process_name1 = msg5+to_string(index_process_name);
					string msg4=process_name_2+" "+to_string(getpid());
					const char* msg3 = msg4.c_str();

					write(unnamedPipe, msg3, 30);
					close(unnamedPipe);


					execl("/home/baris/eclipse-workspace/process/src/process", process_name_2.c_str(),inputPath2.c_str(), NULL);

				}
				else{
					pids.insert(pids.begin() + j, pid1);
					nanosleep(&delta, &delta);

				}

			}


		}
		else if(find(ids.begin(), ids.end(), index_process_name) != ids.end()){


			pid_t zaa;
			pids.erase(pids.begin() + index_process_name-1);
			zaa = fork();

			if(zaa == 0){



				//	myfile1 << ("P" +to_string(index_process_name)+" is killed"  +"\n");
				//	myfile1 << ("Restarting P" +to_string(index_process_name)  +"\n");
				//	myfile1 << ("P" +to_string(index_process_name)  +" is started and it has a pid of "+to_string(getpid())+"\n");

				writeToFile(myfile1,"P" +to_string(index_process_name)+" is killed\nRestarting P" +to_string(index_process_name)  +"\n"+"P" +to_string(index_process_name)  +" is started and it has a pid of "+to_string(getpid())+"\n");
				//	writeToFile(myfile1,"Restarting P" +to_string(index_process_name)  +"\n");
				//	writeToFile(myfile1,"P" +to_string(index_process_name)  +" is started and it has a pid of "+to_string(getpid())+"\n");

				process_name_2 = msg5+to_string(index_process_name);
				string process_name1 = msg5+to_string(index_process_name);
				string msg4=process_name_2+" "+to_string(getpid());


				const char* msg3 = msg4.c_str();
				write(unnamedPipe, msg3, 30);
				close(unnamedPipe);

				execl("/home/baris/eclipse-workspace/process/src/process", process_name_2.c_str(),inputPath2.c_str(), NULL);

			}
			else{

				pids.insert(pids.begin() + index_process_name-1, zaa);


			}

		}


		signal(SIGTERM, signalHandler);

	}


	return 0;
}
