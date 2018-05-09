/*
  Author:Phillip Chen
  Course: 136
  Instructor: Alex Vikolaev
  Assignment: Lab 7 Task 6
  Description:
    The program reads a file nad puts it into a structure (type Word) called w.
    Then it outputs the name of the country and its population at 2000.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
const int MAXCOUNTRIES = 500;

struct Country{
	string name;
	int pop[8];
	};
	
struct World{
	int numcountries;
	Country countries[MAXCOUNTRIES];
	};
	
void readData(World &world);

int main(){						
	World w;
    readData(w);
    for(int i = 0; i<w.numcountries; i++)
   	{
    	cout<<w.countries[i].name<<" "<<w.countries[i].pop[6]<<endl;
   	}
}

void readData(World &world){

	ifstream f;
	f.open("population.csv");

	if (f.fail()){
		cout<<"Cannot find file"<<endl;
		exit(1);//cstdlib library
		}

	string nm;
	double p50,p70,p90,p10,p15;
	world.numcountries=0;

	while (f>>p50>>p70>>p90>>p10>>p15){
		getline(f,nm);
			Country c;
			c.name =nm;
			c.pop[0]= p50;
			c.pop[1]= (p50+p70)/2;
			c.pop[2]= p70;
			c.pop[3]= (p70+p90)/2;
			c.pop[4]= p90;
			c.pop[5]= (p90+p10)/2;
			c.pop[6]= p10;
			c.pop[7]= p15;
			
			world.countries[world.numcountries] = c;
			
			world.numcountries++;
		}
	}

