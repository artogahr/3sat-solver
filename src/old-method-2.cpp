#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <filesystem>

void iterateArray(bool* array, int array_size);
void printArray(bool* array, int array_size);
void printIntArray(int *array, int array_size);
int signum(int num);
using namespace std;
int main()
{
	string line;
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
		char a;
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
				int variable_count = stoi(word);
				bool variables_array[variable_count+1];			
				int variable_states[variable_count];
				for (int i=0; i<variable_count+1; i++)
					variables_array[i] = 0;
				ss >> word; // get line count
				int line_count = stoi(word);
				cout << "vars and lines: " << variable_count << " " << line_count << endl;
				cout << "starting bruteforcing" << endl;
				int iteration = 0;
				auto current_position = current_file.tellg();
				while(variables_array[0] != 1)
				{
					cout << "==========================" << endl;
					cout << "Trying variables_array " << endl;
					printArray(variables_array, variable_count+1);
					for (int i=0; i<variable_count; i++)
						variable_states[i] = 0;
					SAT = 1;
					current_file.seekg(current_position, current_file.beg);
					for (int j=0; j<=line_count; j++)
					{
						//printArray(variables_array, variable_count+1);
						getline(current_file, line);
						cout << "read line: " << line << endl;
						stringstream ss(line);
						string input;
						int inputint;
						while(ss >> inputint)
						{
							if (inputint == 0)
								continue;
							else if (inputint > 0) {
								//cout << " input bigger than 0: " << inputint << endl;
								//cout << "before: " << variable_states[inputint - 1] << endl;
								variable_states[inputint - 1]++;
								//cout << "after: " << variable_states[inputint - 1] << endl;
							}
							else{
								//cout << " input smaller than 0: " << inputint << endl;
								//cout << "before: " << variable_states[abs(inputint + 1)] << endl;
								variable_states[abs(inputint + 1)]--;
								//cout << "after: " << variable_states[abs(inputint + 1)] << endl;
							}
							//cout << inputint << signum(inputint) << " k  " << endl;
						}
						printIntArray(variable_states, variable_count);
					}
					//cout << "----------------------" << endl;
					// Now we try the current array state with our variable states
					for (int i=0; i<variable_count; i++)
					{
						if(variable_states[i] == 0)
							continue;
						else if(variable_states[i] > 0)
						{
							if (variables_array[i+1] != 1)
							{
								/* cout << "Entered bigger condition" << endl; */
								SAT = 0;
								break;
							}
						}
						else if(variable_states[i] < 0)
						{
							if (variables_array[i+1] != 0)
							{
								/* cout << "Entered smaller condition" << endl; */
								SAT = 0;
								break;
							}
						}
					}
					if (SAT == 1){
						cout << "YESSAT" << endl;
						printArray(variables_array, variable_count+1);
					}
					else 
						cout << "UNSAT" << endl;
					printArray(variables_array, variable_count+1);
					printIntArray(variable_states, variable_count); 
					iterateArray(variables_array, variable_count+1);
				}
				break;
			}
		}
		current_file.close();
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
	for (int i=0; i<array_size; i++)
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
