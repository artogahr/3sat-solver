#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <filesystem>

void iterateArray(bool* array, int array_size);
void printArray(bool* array, int array_size);
bool signum(int num);
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
				for (int i=0; i<variable_count; i++)
					variables_array[i] = 0;
				ss >> word; // get line count
				int line_count = stoi(word);
				cout << "vars and lines: " << variable_count << " " << line_count << endl;
				cout << "starting bruteforcing" << endl;
				int iteration = 0;
				auto current_position = current_file.tellg();
				while(variables_array[0] != 1)
				{
					SAT = 1;
					current_file.seekg(current_position, current_file.beg);
					for (int j=0; j<line_count; j++)
					{
					printArray(variables_array, variable_count+1);
						getline(current_file, line);
						cout << line << endl;
						stringstream ss(line);
						string input;
						int input1, input2, input3, zeroInput;
						while(ss >> input1 >> input2 >> input3 >> zeroInput)
						{
							cout << input1 << "/" << variables_array[abs(input1)] << "/" << signum(input1) << endl;
							cout << input2 << "/" << variables_array[abs(input2)] << "/" << signum(input2) << endl;
							cout << input3 << "/" << variables_array[abs(input3)] << "/" << signum(input3) << endl;
							if (variables_array[abs(input1)] == signum(input1) || 
									variables_array[abs(input2)] == signum(input2) || 
									variables_array[abs(input3)] == signum(input3))
								continue;
							else
							{
								//cout << variables_array[abs(input1)] << signum(input1) << endl;
								//cout << variables_array[abs(input2)] << signum(input2) << endl;
								SAT = 0;
								break;
							}
						}
						if (!SAT) {
							cout << "broke 1" << endl;
							//break;
						}
					}
					if (SAT){
						cout << "satisfied by " ;
					//printArray(variables_array, variable_count+1);
					cout << endl;
					}
					iterateArray(variables_array, variable_count+1);
				}
				break;
			}
		}
		current_file.close();
	}
}

void printArray(bool *array, int array_size)
{
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

bool signum(int num)
{
	return num >= 0;
}
