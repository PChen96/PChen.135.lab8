#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

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
	World negRG;
	int indexneg=0;
	
	for(int i =0; i < w.numcountries ; i++){//scaning struct w
		if (w.countries[i].relativeGrowth<0){
			if(indexneg == 0){//first data in struct negRG
				negRG.countries[i]=w.countries[i];
				indexneg++;
				}
			for(int counter =0; counter< indexneg; counter++){//another loop to determine next data goes before or after it
				if(w.countries[i].pop[7]>negRG.countries[i].pop[7]){//if less than previous pop in 2015
					for(int l = indexneg; l>= counter; l--){				//if more than previous pop in 2015
					negRG.countries[l+1]=negRG.countries[l];
					}
					negRG.countries[counter]=w.countries[i];
					cout<<"yes"<<endl;

				}
				if(w.countries[i].pop[7]<negRG.countries[i].pop[7]){//if more than previous pop in 2015
					for(int l = indexneg; l>= 0; l--){				//if less than previous pop in 2015
					negRG.countries[l+1]=negRG.countries[l];
					}
					negRG.countries[0]=w.countries[i];
					cout<<"no"<<endl;

				}
			}
		}		
	}
	for(int i = 0; i < 6 ; i++){
	cout<<w.countries[i].name
	<<'\t'<<w.countries[i].relativeGrowth
	<<setw(5)<<w.countries[i].pop[7]
	<<endl;
	}
	
	for(int i = 0; i < indexneg ; i++){
	cout<<negRG.countries[i].name
	<<'\t'<<negRG.countries[i].relativeGrowth
	<<setw(5)<<negRG.countries[i].pop[7]
	<<endl;
	}
}

void readData(World &world, int &indexmin, int &indexmax){

	ifstream f;
	f.open("population.txt");

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

