

#include <iostream>
#include <iostream>
#include <fstream>
#include <bitset>
#include <algorithm> //for reverse()
#include <experimental/random>
#define SIZE 8
using namespace std;
bool writeToFile = true;
//array for binary
int binary[8];



void convertToBinary(int decimal)
{

//add the remainers to array
for (int i=0; i<8; i++)
{
 if (decimal != 0)
 {
  // %2 gets remainder of dividing by 2
  binary[i]=decimal%2;
 
  decimal = decimal /2;
 }
 else
 {
  // just add 0 to make up 8 bits
  binary[i]=0;
 }
}
//binary bit currently stored backwards
//reverse items in array
reverse(binary, binary+8);

//just printing it out
for (int x=0; x<8;x++)
{
 cout << binary[x];
}
cout << endl;
}


void ruleCreation() {
  int rule;
  cout << "What rule do you want to use? (0-255?)";
  cin >> rule;

  convertToBinary(rule);
}



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

void writeGenToFile(bitset<SIZE> gen)
{
	ofstream genFile;
	//open file in append mode 
	//so not overwriting
	genFile.open("generations.txt", fstream::app);
	genFile << gen;
	genFile << '\n';
	genFile.close();
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

//containts all combinations for the automata rules and generates new lines
bitset<SIZE> nextGen(bitset<SIZE>x_old)
{
	writeGenToFile(x_old);
  bitset<SIZE> x;


for (int i = 0; i<SIZE-1; i++) {
          // 111 parent generates 0 child if binary[0] (rule 1) is 0
  if ((binary[0] == 0) && ( x_old[i-1] == 1 && x_old[i] == 1 && x_old[i+1] == 1 ))  { 
      x[i] = 0;
    } else if ((binary[0] != 0) && ( x_old[i-1] == 1 && x_old[i] == 1 && x_old[i+1] == 1 )){ 
      //if binary[0] is not 0 then 111 generates 1 child
      x[i] = 1;
    }

    // 110 parent generates 0 child if binary[1] (rule 2) is 0
     if ((binary[1] == 0) && ( x_old[i-1] == 1 && x_old[i] == 1 && x_old[i+1] == 0 ))  { 
      x[i] = 0;
    } else if ((binary[1] != 0) && ( x_old[i-1] == 1 && x_old[i] == 1 && x_old[i+1] == 0 )){ 
      //if binary[0] is not 0 then 110 generates 1 child
      x[i] = 1;
    }

     // 101 parent generates 0 child if binary[2] (rule 3) is 0
     if ((binary[2] == 0) && ( x_old[i-1] == 1 && x_old[i] == 0 && x_old[i+1] == 1 ))  { 
      x[i] = 0;
    } else if ((binary[2] != 0) && ( x_old[i-1] == 1 && x_old[i] == 0 && x_old[i+1] == 1 )){ 
      //if binary[0] is not 0 then 101 generates 1 child
      x[i] = 1;
    }

    // 100 parent generates 0 child if binary[3] (rule 4) is 0
     if ((binary[3] == 0) && ( x_old[i-1] == 1 && x_old[i] == 0 && x_old[i+1] == 0 ))  { 
      x[i] = 0;
    } else if ((binary[3] != 0) && ( x_old[i-1] == 1 && x_old[i] == 0 && x_old[i+1] == 0 )){ 
      //if binary[3] is not 0 then 100 generates 1 child
      x[i] = 1;
    }

     // 011 parent generates 0 child if binary[4] (rule 5) is 0
     if ((binary[4] == 0) && ( x_old[i-1] == 0 && x_old[i] == 1 && x_old[i+1] == 1 ))  { 
      x[i] = 0;
    } else if ((binary[4] != 0) && ( x_old[i-1] == 0 && x_old[i] == 1 && x_old[i+1] == 1 )){ 
      //if binary[4] is not 0 then 011 generates 1 child
      x[i] = 1;
    }

     // 010 parent generates 0 child if binary[5] (rule 6) is 0
     if ((binary[5] == 0) && ( x_old[i-1] == 0 && x_old[i] == 1 && x_old[i+1] == 0 ))  { 
      x[i] = 0;
    } else if ((binary[5] != 0) && ( x_old[i-1] == 0 && x_old[i] == 1 && x_old[i+1] == 0 )){ 
      //if binary[5] is not 0 then 010 generates 1 child
      x[i] = 1;
    }

     // 001 parent generates 0 child if binary[6] (rule 7) is 0
     if ((binary[6] == 0) && ( x_old[i-1] == 0 && x_old[i] == 0 && x_old[i+1] == 1 ))  { 
      x[i] = 0;
    } else if ((binary[6] != 0) && ( x_old[i-1] == 0 && x_old[i] == 0 && x_old[i+1] == 1 )){ 
      //if binary[6] is not 0 then 001 generates 1 child
      x[i] = 1;
    }

     // 000 parent generates 0 child if binary[7] (rule 8) is 0
     if ((binary[7] == 0) && ( x_old[i-1] == 0 && x_old[i] == 0 && x_old[i+1] == 0 ))  { 
      x[i] = 0;
    } else if ((binary[7] != 0) && ( x_old[i-1] == 0 && x_old[i] == 0 && x_old[i+1] == 0 )){ 
      //if binary[7] is not 0 then 000 generates 1 child
      x[i] = 1;
    }
  }

  //print out new gen
  for (int j=0; j< x.size(); j++)
  { 
    cout << x[j];
  }
  cout << endl;

  return x;
  }

void runGen() {
     string filename;
    
     bitset<SIZE> x_old;
    bitset<SIZE> x;
    bitset<SIZE> def(string("000010000"));

    int gens = 0;
    int error, error2;


// input validation loop
do
{
    error = 0;
    cout << "How many generations (at least 1): ";
    cin >> gens;
    if (cin.fail())
    {
        cout << "Please enter a valid integer" << endl;
        error = 1;
        cin.clear();
        cin.ignore(80, '\n');
    }
}while(error == 1 || gens<1);
  

    if (writeToFile == true) { //set to true but should ask user at start
  cout << "\nChoose a new name to create a new file, or an existing name to add to that file\n";
  cout << "Name of file to save to: ";
  cin >> filename; }


  //2 choices for first generation (user pick how they want it made at start)
  int selection;
  cout<<"\n1. Generate random first gen";
  cout<<"\n2. Create your own first generation";
  cout<<"\n3. Generate default first generation";
  cout<<"\n4. Exit program\n";
  cout<<"\nEnter selection: ";
do {

  error2 = 0;
  // read the input
  cin>>selection;
   if (cin.fail())
    {
        cout << "Please enter a valid integer (1-4)" << endl;
        error = 1;
        cin.clear();
        cin.ignore(80, '\n');
        cin>>selection;
    }

    if (selection == 1) {
        x_old = generateFirstGenRandomly();
    }

    else if (selection == 2) {
      x_old = userMakeFirstGen();
    }

    else if (selection == 3) {
      x_old = def;

    } else if (selection == 4) {
      exit(1);

    } else {
      error2=1;
      cout<<"\nThat is not a valid selection, try again (1-4)";
    }

  }while(error2 == 1);


    //print starting gen
    for (int i=0; i< x_old.size(); i++)
    {
        cout << x_old[i];
    }
    cout << endl;

    //make other gens 
    for (int i=0; i<gens-1; i++)
    {
      x = nextGen(x_old);
      x_old = x;
    }
   
}



void menu() {
int selection;
int error;

cout<<"\n Menu";
cout<<"\n========";
cout<<"\n 1. Run";
cout<<"\n 2. Game of life";
cout<<"\n 3. Turn save off/on";
cout<<"\n 4. Exit\n";
cout<<"\nEnter selection: ";

// read the input
cin>>selection;
do {
  error=0;
  if (cin.fail())
    {
        cout << "Please enter a valid integer (1-4)" << endl;
        error = 1;
        cin.clear();
        cin.ignore(80, '\n');
        cin>>selection;
    }
}while(error == 1);

switch(selection)

{

case 1 :
ruleCreation();
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


  int main() {
menu();
}

