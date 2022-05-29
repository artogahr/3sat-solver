#include <iostream>
#include <fstream>
#include <filesystem>

void iterateArray(bool* array, int array_size);
using namespace std;
int main()
{
	string line;
	ifstream current_file;
	std::string problems_path = "problems-easy/";
	// Work for each file in the problems directory
	for( const auto & entry : std::filesystem::directory_iterator( problems_path ) ){
		//cout << "__________________________________" << endl;
		//cout << entry.path() << ": " << endl;
		current_file.open(entry.path());
		if(!current_file.is_open()) {
			perror("Error open");
			exit(EXIT_FAILURE);
		}
		char a;
				int test = 0;
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
				while(variables_array[0] != 1)
				{
					for (int j=0; j<line_count; j++)
					{
						getline(current_file, line);
						stringstream ss(line);
						int input;
						while(ss >> input)
						{
						}
					}
					iterateArray(variables_array, variable_count+1);
					test++;
				}
				break;
			}
		}
		cout << "test: " << test << endl;
		current_file.close();
	}
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
