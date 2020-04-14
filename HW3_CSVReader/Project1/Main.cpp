#include "csv.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    //io::csvreader<13> in("spy_may_2012.csv");
    //in.read_header(io::ignore_extra_column, "#ric", "date[g]", "time[g]", "gmt offset", "type", 
    //    "price", "volume", "market vwap", "bid price", "bid size", "ask price", "ask size", "qualifiers");
    //string ric;     string date;               string gmt;     string type;
    //double price;   int volume;     double market;      double bid_price; 
    //int bid_size;   double ask_price;   int ask_size;   string qualifiers;
    io::CSVReader<5> in("SPY_MAY_2012.csv");
    in.read_header(io::ignore_extra_column, "Date[G]", "Time[G]", "Type", "Price", "Volume");
    string date;    string time;     string type;
    double price;   int volume;

    vector<int> Volume(26);
    vector<double> Price(26);
    string TimeSlot[27] = { "09:30:00", "09:45:00",
                           "10:00:00", "10:15:00", "10:30:00", "10:45:00",
                           "11:00:00", "11:15:00", "11:30:00", "11:45:00",
                           "12:00:00", "12:15:00", "12:30:00", "12:45:00",
                           "13:00:00", "13:15:00", "13:30:00", "13:45:00",
                           "14:00:00", "14:15:00", "14:30:00", "14:45:00",
                           "15:00:00", "15:15:00", "15:30:00", "15:45:00", "16:00:00" };

    string TimeInterval[27];
    copy(TimeSlot, TimeSlot + 27, TimeInterval);    // We need another timeinterval to use

    while (in.read_row(date, time, type, price, volume)) {
        // do stuff with the data
        if (type == "Trade") {
            if (date <= "20-MAY-2012") {
                for (int i = 0; i < 26; i++) {
                    if (time >= TimeSlot[i] and time < TimeSlot[i + 1])
                        Volume[i] += volume;
                }
            }
            else if (date == "21-MAY-2012") {	// 21-May
                for (int N = 0; N <= 25; N++) {
                    if (time >= TimeSlot[N] && time < TimeSlot[N + 1]) {
                        Price[N] = price;
                        TimeSlot[N] = "25:00:00";
                        break;
                    }
                }
            }
        }
    }

    fstream fout;
    fout.open("Outputs.csv", 'w');
    cout << setw(15) << "Time Interval" << setw(15) << "Quantity" << setw(15) << "Price" << endl;
    fout << "Time Interval" << "," << "Quantity" << "," << "Price" << endl;
    for (int i = 0; i < 26; i++)
    {
        Volume[i] /= 14;
        cout << TimeInterval[i] << setw(15) << Volume[i] << setw(15) << Price[i] << endl;
        fout << TimeInterval[i] << "," << Volume[i] << "," << Price[i] << endl;
    }
    fout.close();
}