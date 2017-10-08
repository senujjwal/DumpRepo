#include<iostream>
#include<fstream>
#include<omp.h>

using namespace std;

double* PIC(ifstream dataFile)
{

}

int main()
{
	int threads=omp_get_max_threads();
	omp_set_num_threads(threads);									//Initialize threads

	ifstream dataFile("F:\\Data.dat");
	double *cluster = PIC(dataFile);

	return 0;
}