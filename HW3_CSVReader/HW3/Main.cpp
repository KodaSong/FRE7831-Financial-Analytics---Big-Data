#include "ReadFile.h"

/* We have 19347448 rows from 1-May to 20-May
We have 20647277 rows from 1-May to 21-May*/

/* First I used Python to make the huge dataset into 9 small datasets
	In this way, I can use multithreading to speed the whole process
	All the data are in Data.zip*/

int main()
{
	vector<int> Volume(26);
	vector<double> Price(26);

	string TimeSlot[27] = { "09:30:00", "09:45:00",
						   "10:00:00", "10:15:00", "10:30:00", "10:45:00",
						   "11:00:00", "11:15:00", "11:30:00", "11:45:00",
						   "12:00:00", "12:15:00", "12:30:00", "12:45:00",
						   "13:00:00", "13:15:00", "13:30:00", "13:45:00",
						   "14:00:00", "14:15:00", "14:30:00", "14:45:00",
						   "15:00:00", "15:15:00", "15:30:00", "15:45:00", "16:00:00" };

	vector<string> file_vec;
	file_vec.push_back("Data1.csv");	file_vec.push_back("Data2.csv");	file_vec.push_back("Data3.csv");
	file_vec.push_back("Data4.csv");	file_vec.push_back("Data5.csv");	file_vec.push_back("Data6.csv");
	file_vec.push_back("Data7.csv");	file_vec.push_back("Data8.csv");	file_vec.push_back("Data9.csv");

	multi_thread(file_vec, Volume, Price);
	//read_csv(filename, Volume, Price);
	//read_csv_test(filename, Volume, Price);

	ofstream fout;
	fout.open("Outputs.csv");
	
	cout << setw(15) << "Time Interval" << setw(15) << "Quantity" << setw(15) << "Price" << endl;
	fout << "Time Interval" << setw(15) << "Quantity" << setw(15) << "Price" << endl;
	for (int i = 0; i < 26; i++)
	{
		Volume[i] /= 14;
		cout << TimeSlot[i] << setw(15) << Volume[i] << setw(15) << Price[i] << endl;
		fout << TimeSlot[i] << setw(15) << Volume[i] << setw(15) << Price[i] << endl;
	}

	return 0;
}