# include <iostream>
# include <math.h>   //sqrt()
# include <stdlib.h>
#include <time.h>
using namespace std;

// Generates a random decimal number between a specified range
double GenerateRandom(double min, double max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    if (min > max)
    {
        std::swap(min, max);
    }
    return min + (double)rand() * (max - min) / (double)RAND_MAX;
}

int main(){
	int games=10, darts=100000;
	double piList[games], piTotal;

	double x, y, distance;
	int nInside = 0;
	
	for(int g=games; g>0; g--){
		for(int d=darts; d>0; d--){
			x = GenerateRandom(-0.5, 0.5);
			y = GenerateRandom(-0.5, 0.5);
			
			distance = sqrt((x*x) + (y*y));
			if(distance < 0.5){
				nInside++;
			}
		}
		double piEst = 4.0 * ((double)nInside/(double)darts);
		piList[g] = piEst;
		piTotal += piEst;
		nInside = 0;
	}
	double piMean = piTotal/games;
	cout << "================================\n";
	cout << "Pi is ";
	cout << piMean;
	cout << "\n\n";
	
	double standDev = 0.0;
	for(int i=0; i<games; i++){
		standDev = (piList[i] - piMean) * (piList[i] - piMean);
	}
	standDev = sqrt(standDev);
	cout << "Standard Deviation is ";
	cout << standDev;
	cout << "\n";
	cout << "================================\n";
}