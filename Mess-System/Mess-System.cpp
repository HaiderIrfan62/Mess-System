#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

void registration();
void bill();
void status();
void search();
void total();
void delete_record();
void display();

int main()
{
	int choice;

	bool k = false, j = false;

	char y = 'Y';

	do {
		do {
			cout << "Welcome! What do you want to do?" << endl;
			cout << "1.Register a new student." << endl;
			cout << "2.Search a student record." << endl;
			cout << "3.Change student mess status (In/Out)." << endl;
			cout << "4.Delete a student record." << endl;
			cout << "5.Show a total number of In/Out students." << endl;
			cout << "6.Calculate total bill." << endl;
			cout << "7.Display a list of existing users." << endl;
			cout << "Enter choice number: ";
			cin >> choice;

			cout << endl;

			switch (choice)
			{
			case 1:
				registration();
				k = false;
				break;
			case 2:
				search();
				k = false;
				break;
			case 3:
				status();
				k = false;
				break;
			case 4:
				delete_record();
				k = false;
				break;
			case 5:
				total();
				k = false;
				break;
			case 6:
				bill();
				k = false;
				break;
			case 7:
				display();
				k = false;
				break;
			default:
				cout << "Invalid Entry." << endl;
				k = true;
				break;
			}
		} while (k);

		do {
			cout << endl;
			cout << "Do you want to do something else?(Y/N)";
			cin >> y;
			cout << endl;

			if (!(y == 'y' || y == 'Y' || y == 'n' || y == 'N')) {
				cout << "Invalid entry." << endl;
				j = true;
			}
			else
				j = false;
		} while (j);

		system("cls");

	} while (y == 'y' || y == 'Y');

	cout << "Thank You for using the system!" << endl;

	return 0;
}

//Function for checking if the entered registration number already exists.
int check_reg(string reg)
{
	//Reading the file into a vector.
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	bool k = true;

	//Calculating total rows in the vector.
	int t_rows = all_data.size();

	//Loop for checking if registration number already exists.
	for (int row = 0; row < t_rows; row++) {
		if (reg == all_data[row][0]) {
			k = false;
		}
	}

	file.close();

	//Returning 0 or 1 in case of existing or not existing.
	if (k)
		return 1;
	else
		return 0;
}

//Function for registering new students in the data base of the mess.
void registration()
{
	string name, reg;
	string io = "out", days = "0", bill = "0";  //the current bill and number of “In” days are zero, and the mess status is “Out” by default.



	cin.ignore();             //The getline wasn't taking any input of name, this is a solution I found on the internet.

	cout << "Enter the registration number: ";
	getline(cin, reg);
	cout << "Enter the name of the student: ";
	getline(cin, name);
	cout << "What mess status do you want?";
	cin >> io;

	//Changing the default mess status, bill, indays. 
	if (io == "in" || io == "In" || io == "IN")
	{
		bill = "300";
		days = "1";
	}

	if (check_reg(reg))
	{
		//Writing to the file.
		fstream fout;

		fout.open("data.csv", ios::out | ios::app);

		fout << reg << "," << name << "," << bill << "," << io << "," << days << "\n";

		cout << "Student registered successfully!" << endl;
	}
	else {
		cout << "This student is already registered." << endl;
	}

	//Reading the file for sorting.
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();
	int t_cols = all_data[1].size();

	//Sorting the table in descending order according to the registration numbers.
	for (int i = 1; i < t_rows; i++)
	{
		for (int j = 0; j < t_cols; j++)
		{
			for (int k = i + 1; k < t_rows; k++)
			{
				if (all_data[i][0] > all_data[k][0])
				{
					string temp = all_data[i][0];
					all_data[i][0] = all_data[k][0];
					all_data[k][0] = temp;

					string temp1 = all_data[i][1];
					all_data[i][1] = all_data[k][1];
					all_data[k][1] = temp1;

					string temp2 = all_data[i][2];
					all_data[i][2] = all_data[k][2];
					all_data[k][2] = temp2;

					string temp3 = all_data[i][3];
					all_data[i][3] = all_data[k][3];
					all_data[k][3] = temp3;

					string temp4 = all_data[i][4];
					all_data[i][4] = all_data[k][4];
					all_data[k][4] = temp4;
				}
			}
		}
	}

	//Updating the file after sorting.
	fstream fout;

	//Creating a new file
	fout.open("newdata.csv", ios::out | ios::app);

	t_rows = all_data.size();

	for (int i = 0; i < t_rows; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			fout << all_data[i][j] << ",";
		}
		fout << "\n";
	}

	file.close();
	fout.close();

	//Deleting the old file.
	remove("data.csv");

	//Renaming the new file 
	int x = rename("newdata.csv", "data.csv");
}

//Function for calculating the bill.
void bill()
{
	string word, line, reg;

	cout << "Enter registration Number: ";
	cin >> reg;

	vector<vector<string>> all_data;
	vector <string> row_data;

	//Reading the file into a vector.
	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();
	bool k = true;

	//Displaying the Bill.
	for (int row = 0; row < t_rows; row++) {
		if (reg == all_data[row][0]) {
			cout << "Bill: " << all_data[row][2] << endl;
			k = false;
		}
	}

	if (k)
	{
		cout << "No record found." << endl;
	}

	file.close();
}

//Function for displaying the whole table.
void display()
{
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	//Reading the file into a vector.
	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();

	cout << "___________________________________________________" << endl;
	for (int i = 0; i < t_rows; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j == 0)
			{
				cout << "|";
			}

			cout << all_data[i][j] << ' ';

			if (j == 0)
			{
				if (all_data[i][0].length() == 6)
					cout << "  |";
				else if (all_data[i][0].length() == 7)
					cout << " |";
			}
			else if (j == 1)
			{
				if (all_data[i][1].length() == 3)
					cout << "               |";
				else if (all_data[i][1].length() == 4)
					cout << "              |";
				else if (all_data[i][1].length() == 5)
					cout << "             |";
				else if (all_data[i][1].length() == 6)
					cout << "            |";
				else if (all_data[i][1].length() == 7)
					cout << "           |";
				else if (all_data[i][1].length() == 8)
					cout << "          |";
				else if (all_data[i][1].length() == 9)
					cout << "         |";
				else if (all_data[i][1].length() == 10)
					cout << "        |";
				else if (all_data[i][1].length() == 11)
					cout << "       |";
				else if (all_data[i][1].length() == 12)
					cout << "      |";
				else if (all_data[i][1].length() == 13)
					cout << "     |";
				else if (all_data[i][1].length() == 14)
					cout << "    |";
				else if (all_data[i][1].length() == 15)
					cout << "   |";
				else if (all_data[i][1].length() == 16)
					cout << "  |";
				else if (all_data[i][1].length() == 17)
					cout << " |";
				else if (all_data[i][1].length() == 18)
					cout << "|";
			}
			else if (j == 2)
			{
				if (all_data[i][2].length() == 1)
					cout << "    |";
				else if (all_data[i][2].length() == 2)
					cout << "   |";
				else if (all_data[i][2].length() == 3)
					cout << "  |";
				else if (all_data[i][2].length() == 4)
					cout << " |";
				else if (all_data[i][2].length() == 5)
					cout << "|";
			}
			else if (j == 3)
			{
				if (all_data[i][3].length() == 2)
					cout << "    |";
				else if (all_data[i][3].length() == 3)
					cout << "   |";
				else if (all_data[i][3].length() == 6)
					cout << "|";
			}
			else if (j == 4)
			{
				if (all_data[i][4].length() == 1)
					cout << "   |";
				else if (all_data[i][4].length() == 2)
					cout << "  |";
				else if (all_data[i][4].length() == 3)
					cout << " |";
				else if (all_data[i][4].length() == 4)
					cout << "|";
			}
		}
		cout << endl;
	}
	cout << "|_________|___________________|______|_______|_____|" << endl;
}

//Function for changing In/Out status.
void status()
{
	string reg;
	cout << "Enter reg number: ";
	cin >> reg;

	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	//Reading the file into a vector.
	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();
	int t_cols = all_data[1].size();

	bool k = true;

	for (int i = 0; i < t_rows; i++)
	{
		if (reg == all_data[i][0])
		{
			if (all_data[i][3] == "in")                //Checking the In/Out status of the entered user through his registration number.
			{
				cout << "Mess Status: in" << endl;
			}
			else if (all_data[i][3] == "out")
			{
				cout << "Mess Status: out" << endl;
			}

			char choice;

			cout << "Do you want to change the mess status?(Y/N) ";
			cin >> choice;

			if (choice == 'Y' || choice == 'y')        //Changing the In/Out status of the user.       
			{
				if (all_data[i][3] == "in")
				{
					all_data[i][3] = "out";

					k = false;
				}
				else if (all_data[i][3] == "out")
				{
					all_data[i][3] = "in";

					int num = stoi(all_data[i][2]);         //Converting string to int.
					num = num + 300;

					stringstream n;                         //Converting int to string.
					n << num;
					all_data[i][2] = n.str();

					int indays = stoi(all_data[i][4]);      //Converting string to int.
					indays++;

					stringstream inday;                     //Converting int to string.
					inday << indays;
					all_data[i][4] = inday.str();

					k = false;
				}
			}
			else if (choice == 'N' || choice == 'n')
			{

			}
			else
			{
				cout << "Invalid Entry." << endl;
			}
		}
	}

	if (k)
	{
		cout << "Entry not found." << endl;
	}
	else
	{
		//Updating the file.
		fstream fout;

		fout.open("newdata.csv", ios::out);

		for (int i = 0; i < t_rows; i++)
		{
			for (int j = 0; j < t_cols; j++)
			{
				fout << all_data[i][j] << ",";
			}
			fout << "\n";
		}

		file.close();
		fout.close();

		remove("data.csv");
		rename("newdata.csv", "data.csv");

		cout << "Mess status successfully changed." << endl;
	}
}

//Function for searching a record.
void search()
{
	string word, line, reg;

	cout << "Enter registration number: ";
	cin >> reg;
	cout << endl;

	vector<vector<string>> all_data;
	vector <string> row_data;

	//Reading the file into a vector.
	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();
	bool k = true;

	//Displaying the data of the user.
	for (int row = 0; row < t_rows; row++) {
		if (reg == all_data[row][0]) {
			cout << "Registration number: " << all_data[row][0] << endl;
			cout << "Student Name: " << all_data[row][1] << endl;
			cout << "Bill: " << all_data[row][2] << endl;
			cout << "In/Out Status: " << all_data[row][3] << endl;
			cout << "Total number of In days: " << all_data[row][4] << endl;
			k = false;
		}
	}

	if (k)
	{
		char choice;

		cout << "No record found." << endl;
		cout << "Do you want to register this student?(Y/N) ";
		cin >> choice;
		cout << endl;

		if (choice == 'Y' || choice == 'y')
		{
			registration();
		}
		else if (choice == 'N' || choice == 'n')
		{

		}
		else
		{
			cout << "Invalid Entry." << endl;
		}
	}

	file.close();
}

//Function for calculating the total number of in and out students.
void total()
{
	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	//Reading the file into a vector.
	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	file.close();

	int t_rows = all_data.size();
	int inctr = 0, outctr = 0;

	for (int i = 0; i < t_rows; i++)
	{
		if (all_data[i][3] == "in")
		{
			inctr++;
		}
		else
		{
			outctr++;
		}
	}

	cout << "Total number of in students are: " << inctr << endl;
	cout << "Total number of out students are: " << --outctr << endl;
}

//Function for deleting a record.
void delete_record()
{
	string reg;
	cout << "Enter reg number: ";
	cin >> reg;

	string word, line;

	vector<vector<string>> all_data;
	vector <string> row_data;

	//Reading file into a vector.
	fstream file("data.csv", ios::in);

	while (getline(file, line))
	{
		row_data.clear();

		stringstream str(line);

		while (getline(str, word, ',')) {
			row_data.push_back(word);
		}
		all_data.push_back(row_data);
	}

	int t_rows = all_data.size();

	bool k = true;

	if (t_rows > 1)
	{
		for (int i = 0; i < t_rows; i++)
		{
			if (all_data[i][0] == reg)
			{
				for (int j = 0; j < 5; j++)
				{
					all_data[i][j] = "delete";           //Converting data in the row to be deleted to delete. 
				}
				k = false;
			}
		}

		//Sorting the table so that the deleted row goes at the end.
		for (int i = 1; i < t_rows; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = i + 1; k < t_rows; k++)
				{
					if (all_data[i][0] > all_data[k][0])
					{
						string temp = all_data[i][0];
						all_data[i][0] = all_data[k][0];
						all_data[k][0] = temp;

						string temp1 = all_data[i][1];
						all_data[i][1] = all_data[k][1];
						all_data[k][1] = temp1;

						string temp2 = all_data[i][2];
						all_data[i][2] = all_data[k][2];
						all_data[k][2] = temp2;

						string temp3 = all_data[i][3];
						all_data[i][3] = all_data[k][3];
						all_data[k][3] = temp3;

						string temp4 = all_data[i][4];
						all_data[i][4] = all_data[k][4];
						all_data[k][4] = temp4;
					}
				}
			}
		}

		if (k)
		{
			cout << "Entry not found." << endl;
		}
		else
		{
			fstream fout;

			fout.open("newdata.csv", ios::out | ios::app);

			t_rows = all_data.size() - 1;           //Loop will run for 1 less row which is the row to be deleted.

			for (int i = 0; i < t_rows; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					fout << all_data[i][j] << ",";
				}
				fout << "\n";
			}

			file.close();
			fout.close();

			remove("data.csv");
			rename("newdata.csv", "data.csv");

			cout << "Record deleted succesfully!" << endl;
		}
	}
	else
	{
		cout << "The data base is empty." << endl;
	}
}
