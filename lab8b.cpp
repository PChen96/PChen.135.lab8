/*
  Author:Phillip Chen
  Course: 136
  Instructor: Alex Vikolaev
  Assignment: Lab 7 Task 6
  Description:
    The program reads a file nad puts it into a structure (type Word) called w.
    It calculates the countries relative growth rate and then
    outputs the maximum and minimum countries in terminal.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
const int MAXCOUNTRIES = 500;

struct Country{
	string name;
	int pop[8];
	double relativeGrowth;
	};
	
struct World{
	int numcountries;
	Country countries[MAXCOUNTRIES];
	};
	
void readData(World &world, int &indexmin, int &indexmax);

int main(){						
	World w;
	int indexmin, indexmax;
    readData(w, indexmin, indexmax);
    cout<<"Maximum"<<w.countries[indexmax].name<<" "<<(w.countries[indexmax].relativeGrowth)*100<<"%"<<endl;
    cout<<"Minimum"<<w.countries[indexmin].name<<" "<<(w.countries[indexmin].relativeGrowth)*100<<"%"<<endl;

}

void readData(World &world, int &indexmin, int &indexmax){

	ifstream f;
	f.open("population.csv");

	if (f.fail()){
		cout<<"Cannot find file"<<endl;
		exit(1);//cstdlib library
		}

	string nm;
	double p50,p70,p90,p10,p15;
	world.numcountries=0;
	double min = 0;
	double max = 0;
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
		c.relativeGrowth=(p15 - p50) / p50;
			
		world.countries[world.numcountries] = c;

		if (world.countries[world.numcountries].relativeGrowth < min){
			min=world.countries[world.numcountries].relativeGrowth;
			indexmin=world.numcountries;
			}
		if (world.countries[world.numcountries].relativeGrowth > max){
			max=world.countries[world.numcountries].relativeGrowth;
			indexmax=world.numcountries;
			}
			
		world.numcountries++;
	}
}

