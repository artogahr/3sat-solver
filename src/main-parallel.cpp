#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <fstream>
#include <stdlib.h>
#include <filesystem>

void checkLinesForSAT(bool *variables_array, int line_states[][3], int line_count, int variable_count);
void iterateArray(bool* array, int array_size);
void printArray(bool* array, int array_size);
void printIntArray(int *array, int array_size);
int signum(int num);
using namespace std;
int main()
{
	string line;
	pthread_t ptid;
	bool SAT;
	ifstream current_file;
	std::string problems_path = "problems-easy/";
	// Work for each file in the problems directory
	for( const auto & entry : std::filesystem::directory_iterator( problems_path ) ){
		cout << "__________________________________" << endl;
		cout << entry.path() << ": " << endl;
		current_file.open(entry.path());
		if(!current_file.is_open()) {
			perror("Error open");
			exit(EXIT_FAILURE);
		}
		int variable_count, line_count;
		while(getline(current_file, line)) {
			stringstream ss(line);
			string word;
			ss >> word;
			if(word == "c")
				continue;
			else if (word == "p")
			{
				ss >> word; // get the word "cnf"
				ss >> word; // get variable count
				variable_count = stoi(word);
				ss >> word; // get line count
				line_count = stoi(word);
				cout << "vars and lines: " << variable_count << " " << line_count << endl;
				break;
			}
		}
		bool variables_array[variable_count+1] = {0};
		int line_states[line_count][3] = {0};
		for(int x=0; x<line_count; x++)
			for(int y=0; y<3; y++)
				line_states[x][y] = 0;
		auto current_position = current_file.tellg();

		while(variables_array[0] != 1)
		{
//			cout << "==========================" << endl;
//			cout << "Trying ";
			//printArray(variables_array, variable_count+1);
			 /* std::this_thread::sleep_for(1s); */
			current_file.seekg(current_position, current_file.beg);
			for (int j=0; j<line_count; j++)
			{
				getline(current_file, line);
				/* cout << "read line: " << line << endl; */
				stringstream ss(line);
				int input;
				for(int k=0; k<3; k++)
				{
					ss >> input;
					if (input == 0)
						break;
					else
						line_states[j][k] = input;
				}
				/* for(int z = 0; z<line_count; z++){ */
				/* 	for (int x = 0; x<3; x++) */
				/* 		cout << line_states[z][x] << " " ; */
				/* 	cout << "\t";} */
				/* cout << endl; */
			}
			//printArray(variables_array, variable_count+1);
			/* cout << "--------------------------------------------" << endl; */
			/* cout <<  "Now we try the current array state with our variable states" << endl; */
			/* else */ 
			checkLinesForSAT(variables_array, line_states, line_count, variable_count);
			/* 	cout << "UNSAT" << endl; */
			/* printArray(variables_array, variable_count+1); */
			/* printIntArray(variable_states, variable_count); */ 
			/* iterateArray(variables_array, variable_count+1); */
				iterateArray(variables_array, variable_count + 1);
		}
		current_file.close();
	}
}

void checkLinesForSAT(bool *variables_array, int line_states[][3], int line_count, int variable_count)
{
	int currentNum, index, SAT;
	volatile bool flag=false;
//#pragma omp parallel for collapse(2) shared (flag) private (SAT) 
	for (int i=0; i<line_count; i++)
	{
		if(flag) continue;
		/* cout << "Trying line "; */ 
		/* for(int j=0; j<3; j++) */
		/* 	cout << line_states[i][j] << " "; */
		/* cout << endl; */
		SAT = 0;
		for(int j=0; j<3; j++)
		{
			/* index = i; */
			currentNum = line_states[i][j];
			if (currentNum == 0)
				break;
			else if (currentNum > 0 && variables_array[currentNum] == 1)
			{
				/* cout << "sat: " << currentNum << " " << variables_array[currentNum] << endl; */
				SAT = 1;
				break;
			}
			else if (currentNum < 0 && variables_array[-currentNum] == 0)
			{
				/* cout << "sat: " << currentNum << " " << variables_array[-currentNum] << endl; */
				SAT = 1;
				break;
			}
			/* else */
			/* { */
			/* 	cout << "UNSAT: CurrentNum: " << currentNum << " compared to: " << variables_array[abs(currentNum)] << endl; */
			/* } */
		}	
		/* cout << endl; */
		//cout << "--" << endl;
		if (SAT == 0){
			//				cout << "BROKE SAT WITH LINE STATES: " ;
			//					for (int t=0; t<3; t++)
			//						cout << line_states[index][t] << " ";
			//					cout << endl;
			flag=true;
		}
	}
	if (SAT == 1){
		/* cout << endl; */
		//				cout << "YESSAT" << endl;
		printArray(variables_array, variable_count+1);
	}
}
void printIntArray(int *array, int array_size)
{ 
	cout << "Int array state: " ;
	for (int i=0; i<array_size; i++)
	{
		cout << array[i];
	}
	cout << endl;
}

void printArray(bool *array, int array_size)
{
	cout << "Variables array state: ";
	for (int i=1; i<array_size; i++)
	{
		cout << array[i];
	}
	cout << endl;
}
void iterateArray(bool* array, int array_size)
{
	bool carry = 1;
	for(int i=array_size-1; i>=0; i--)
	{
		if(array[i] == 1 && carry)
		{
			array[i] = 0;
		}
		else if (carry)
		{
			array[i] = 1;	
			break;
		}
	}
}

int signum(int num)
{
	return num >= 0 ? 1 : -1;
}
