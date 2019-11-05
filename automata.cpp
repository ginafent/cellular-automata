#include <bitset>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <experimental/random>
//how will user set this?
//not sure how can be changed during runtime
#define SIZE 8
using namespace std;
bool writeToFile = true;



//user making first generation themself - bit by bit
bitset<SIZE> userMakeFirstGen()
{

	bitset<SIZE> firstGen;

	//boolean to determine the while loop
	bool wrongInput;

	//do while input is invalid (wrongInput = true)
	do
	{
		//set to false initially
		wrongInput = false;
		cout << "Enter first generation one bit at a time (using 1s and 0s):" << endl;

		//loop the size of generation to populate bitset
		for (int i=0; i<SIZE; i++)
		{

			int input; 
			cin >> input;

			//check that its being entered one number at a time
			if (std::to_string(input).length() > 1 || std::to_string(input).length() > SIZE)
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Please enter one at a time." << endl << endl;
				wrongInput = true;
				break;
			}
			//check the input is a 1 or 0 
			else if ((input != 0 && input != 1) || (cin.fail()))
			{
				cin.clear();
				cin.ignore(256, '\n');
				cout << endl << "Only use 1 or 0." << endl;
				wrongInput = true;
				break;
			}
			else
			{
				//assign to the bitset
				firstGen[i] = input;	
			}
		}

	}while (wrongInput == true);


	//return the full bitset
	return firstGen;
}


//generate first generation randomly
bitset<SIZE> generateFirstGenRandomly()
{
	bitset<SIZE> firstGen;

	//loop through empty bitset and populate randomly
	for (int i = 0; i <SIZE; i++)
	{
		//assign random int either 1 or 0
		firstGen[i] = std::experimental::randint(0,1);
	}

	//return full bitset
	return firstGen;
}


//write generation to file - pass each generation in to append to file
//user defined filename too
void writeGenToFile(bitset<SIZE> gen, string filename)
{
	ofstream genFile;
	//open file in append mode - so not overwriting
	genFile.open(filename, fstream::app);
	genFile << gen;
	genFile << '\n';
	genFile.close();
}


void runGen() {
	string filename;
	//some user input - needs validated
	int generations;
	cout << "How many generations: ";
	cin >> generations;

	if (writeToFile == true) { //set to true but should ask user at start
	cout << "Name of file to save to: ";
	cin >> filename; }


//2 choices for first generation (user pick how they want it made at start)
	//1. completely random
	int selection;
	cout<<"\n1. Generate random first gen";
	cout<<"\n2. Create your own first generation";
	cout<<"\n3. Exit\n";
	cout<<"\nEnter selection: ";

	// read the input
	cin>>selection;

if (selection == 1) {
	bitset<SIZE> grid = generateFirstGenRandomly();

	//2. make themself bit by bit
	//bitset<SIZE> grid = userMakeFirstGen();
  

  	//printing first gen
	std::cout << grid.to_string() << "\n" ;

	for(int i = 0 ; i < generations ; i++)
	{
		//write each gen to file 
		//check if they want to do this during menu
		if (writeToFile == true)
		{
			writeGenToFile(grid, filename);
		}
		for(int j = 1; j < (SIZE -1 ); j++)
		{ 		
			if(grid[j] == 1)
			{
				grid.set(j-1);
				grid.set(j+1);
				grid.reset(j);
				j++;
			}
			
		}
		
		std::cout << grid.to_string() << "\n" ;

	} 
} else if (selection == 2) { 

	bitset<SIZE> grid = userMakeFirstGen();
  

  	//printing first gen
	std::cout << grid.to_string() << "\n" ;

	for(int i = 0 ; i < generations ; i++)
	{
		//write each gen to file 
		//check if they want to do this during menu
		if (writeToFile == true)
		{
			writeGenToFile(grid, filename);
		}
		for(int j = 1; j < (SIZE -1 ); j++)
		{ 		
			if(grid[j] == 1)
			{
				grid.set(j-1);
				grid.set(j+1);
				grid.reset(j);
				j++;
			}
			
		}
		
		std::cout << grid.to_string() << "\n" ;

	} 
} else if (selection == 3) {
	
}

else {
	cout<<"\nInvalid selection!";
	runGen();
}

 }

void menu() {
int selection;

cout<<"\n Menu";
cout<<"\n========";
cout<<"\n 1. Run";
cout<<"\n 2. Game of life";
cout<<"\n 3. Turn save off/on";
cout<<"\n 4. Exit\n";
cout<<"\nEnter selection: ";

// read the input
cin>>selection;

switch(selection)

{

case 1 :
runGen();
break;
case 2 :{cout<<"\n game of life";}
break;
case 3 :
if (writeToFile == true) {
	writeToFile = false;
	{cout<<"\n Auto save is now OFF";}
} else {
	writeToFile = true;
	{cout<<"\n Auto save is now ON";}
}
break;
case 4 :{cout<<"\n Goodbye! ";}
exit(0);
break;

// other than A, M, D and X...
default : cout<<"\n Invalid selection";
// no break in the default case
}

cout<<"\n";
menu();
}


int main()
{
menu();
}
