#include "ReadFile.h"

void read_csv_test(string filename, vector<int> & Volume, vector<double> & Price)
{
	string TimeSlot[27] = { "09:30:00", "09:45:00",
						   "10:00:00", "10:15:00", "10:30:00", "10:45:00",
						   "11:00:00", "11:15:00", "11:30:00", "11:45:00",
						   "12:00:00", "12:15:00", "12:30:00", "12:45:00",
						   "13:00:00", "13:15:00", "13:30:00", "13:45:00",
						   "14:00:00", "14:15:00", "14:30:00", "14:45:00",
						   "15:00:00", "15:15:00", "15:30:00", "15:45:00", "16:00:00" };

	int index1, index2;
	ifstream inFile(filename, ios::in);
	string line;
	getline(inFile, line);	// We don't need the header
	//int X = 0;
	while (getline(inFile, line)) {
		string date = line.substr(4, 11);
		string timestamp = line.substr(16, 8);
		//X++;
		if (line[32] == 'T') {	// We only keep "Trade"
			if (date <= "20-MAY-2012") {	// 1-May to 20-May
				line.erase(0, 38);	// erase characters before Price
				index1 = line.find_first_of(',');	// The comma before Volume
				if (index1 == 0)		continue;
				line.erase(0, index1 + 1);	// Erase characters before Volume
				index2 = line.find_first_of(',');	// The comma after Volume
				int volume = stoi(line.substr(0, index2));

				for (int i = 0; i < 26; i++) {
					if (timestamp >= TimeSlot[i] and timestamp < TimeSlot[i + 1])
					{
						Volume[i] += volume;
					}
						
				}
			}

			else if (date == "21-MAY-2012") {	// 21-May
				for (int N = 0; N <= 25; N++) {
					if (timestamp >= TimeSlot[N] && timestamp < TimeSlot[N+1]) {
						line.erase(0, 38);	// erase characters before Price
						index1 = line.find_first_of(',');	// The comma before Volume
						if (index1 == 0)	break;
						double price = stod(line.substr(0, index1));
						Price[N] = price;
						TimeSlot[N] = "25:00:00";
						//cout << N << "   " << TimeSlot[N] << "   " << Price[N] << endl;
						break;
					}
				}
			}		

		}

	}
}

void multi_thread(vector<string>& file_vec, vector<int>& Volume, vector<double>& Price)
{
	string file1 = file_vec[0];		string file2 = file_vec[1];		string file3 = file_vec[2];
	string file4 = file_vec[3];		string file5 = file_vec[4];		string file6 = file_vec[5];
	string file7 = file_vec[6];		string file8 = file_vec[7];		string file9 = file_vec[8];

	thread t1(read_csv_test, file1, ref(Volume), ref(Price));
	thread t2(read_csv_test, file2, ref(Volume), ref(Price));
	thread t3(read_csv_test, file3, ref(Volume), ref(Price));
	thread t4(read_csv_test, file4, ref(Volume), ref(Price));
	thread t5(read_csv_test, file5, ref(Volume), ref(Price));
	thread t6(read_csv_test, file6, ref(Volume), ref(Price));
	thread t7(read_csv_test, file7, ref(Volume), ref(Price));
	thread t8(read_csv_test, file8, ref(Volume), ref(Price));
	thread t9(read_csv_test, file9, ref(Volume), ref(Price));

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	t9.join();
}

//void read_csv(string filename, vector<int>& Volume, vector<double>& Price)
//{
//	string TimeSlot[27] = { "09:30:00", "09:45:00",
//						   "10:00:00", "10:15:00", "10:30:00", "10:45:00",
//						   "11:00:00", "11:15:00", "11:30:00", "11:45:00",
//						   "12:00:00", "12:15:00", "12:30:00", "12:45:00",
//						   "13:00:00", "13:15:00", "13:30:00", "13:45:00",
//						   "14:00:00", "14:15:00", "14:30:00", "14:45:00",
//						   "15:00:00", "15:15:00", "15:30:00", "15:45:00", "16:00:00" };
//
//	int index1, index2;
//	ifstream inFile(filename, ios::in);
//	string line;
//	getline(inFile, line);	// We don't need the header
//	//int X = 0;
//	while (getline(inFile, line)) {
//		char line_arr[1000];
//		strcpy(line_arr, line.c_str());
//		int date = line_arr[4] * 10 + line_arr[5];
//		string timestamp = "";
//		for (int i = 16; i < 24; i++)
//			timestamp += line_arr[i];
//		/*string date = line.substr(4, 11);
//		string timestamp = line.substr(16, 8);*/
//		//X++;
//		if (line[32] == 'T') {	// We only keep "Trade"
//			if (date <= 20) {	// 1-May to 20-May
//				//line.erase(0, 38);	// erase characters before Price
//				for (int i = 38; i < 48; i++) {
//					if (line_arr[i] == ',') {
//						index1 = i;
//						break;
//					}
//				}
//				if (index1 == 0)		continue;
//				//line.erase(0, index1 + 1);	// Erase characters before Volume
//				for (int i = index1 + 1; i < index1 + 15; i++) {
//					if (line_arr[i] == ',') {
//						index2 = i;
//						break;
//					}
//				}
//				//index2 = line.find_first_of(',');	// The comma after Volume
//				//int volume = stoi(line.substr(0, index2));
//				int volume = 0;
//				for (int i = index1+1; i < index2; i++) {
//					volume = volume * 10 + line_arr[i];
//				}
//				//cout << volume << endl;
//
//				for (int i = 0; i < 26; i++) {
//					if (timestamp >= TimeSlot[i] and timestamp < TimeSlot[i + 1])
//					{
//						Volume[i] += volume;
//					}
//
//				}
//			}
//
//			else if (date == 21) {	// 21-May
//				for (int N = 0; N <= 25; N++) {
//					if (timestamp >= TimeSlot[N] && timestamp < TimeSlot[N + 1]) {
//						for (int i = 38; i < 48; i++) {
//							if (line_arr[i] == ',') {
//								index1 = i;
//								break;
//							}
//						}
//						if (index1 == 0)	continue;	// Maybe Break
//						double price = stod(line.substr(38, index1));
//						Price[N] = price;
//						TimeSlot[N] = "25:00:00";
//						//cout << N << "   " << TimeSlot[N] << "   " << Price[N] << endl;
//						break;
//					}
//				}
//			}
//
//		}
//
//	}
//}