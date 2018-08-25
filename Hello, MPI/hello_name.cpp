/********************************************************************\
 hello_name.cpp
 Jeremy Campbell
 -------------
 This example is used to illustrate the use of several fundamental
 MPI routines
\********************************************************************/

#include <iostream>
#include <mpi.h>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	MPI_Init(&argc, &argv);

	// What is my id?
	int id;
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	// How many other processes are out there?
	int p;
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	// Which processor do I have?
	char hostname[MPI_MAX_PROCESSOR_NAME];
	int nameSize;
	MPI_Get_processor_name(hostname, &nameSize);

	MPI_Status status;

	// If I am the root
	if (id == 0)
	{
		char name[100];
		cout << "What is your name? ";
		cin >> name;

		for (int i = 1; i < p; i++)
		{
			MPI_Send(name, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD);
		}
	}
	else
	{
		char recvBuf[100];
		MPI_Recv(recvBuf, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

		string name = recvBuf;
		name.resize(strlen(recvBuf));
		cout << "Hello, " << name << ", from process " << id << "!" << endl;
	}	

	MPI_Finalize();
}