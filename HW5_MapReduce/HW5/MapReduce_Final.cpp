#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <windows.h>

using namespace std;

string DataCollection = "web,wed,green,sun,moon,land,part,web,green\ngreen,web,part,land,moon,sun,green,wed,web\nmoon,land,part,web,green,web,wed,green,sun";
map<int, vector<string> > WordLists;
map<string, int> ResultTable;
const int input_size = 27;
const int no_of_threads = 3;
int word_list_size = 0;


class Parser {
public:
	void operator()(string SubDataCollection, int index, char delimiter)
	{
		string word;
		istringstream wordStream(SubDataCollection);
		while (getline(wordStream, word, delimiter))
		{
			WordLists[index].push_back(word);
			word_list_size++;
		}
	}
};

class Counter
{
public:
	void operator()(map<string, int> *pResultTable, int index)
	{
		while (word_list_size != input_size);
		for (int i = 0; i < WordLists[index].size(); i++)
		{
			int count = (*pResultTable)[string(WordLists[index][i])];
			count = count + 1;
			(*pResultTable)[string(WordLists[index][i])] = count;
		}
	}
};

class WordCounter
{
private:
	map<string, int> ResultTables[no_of_threads];
	map<int, string> DataCollections;
public:
	WordCounter()
	{
		string subDataCollction;
		istringstream dataStream(DataCollection);
		int count = 0;
		while (getline(dataStream, subDataCollction, '\n'))
		{
			//cout << subDataCollction << endl;
			DataCollections.insert(pair<int, string>(count, subDataCollction));
			count++;
		}
	}

	void Map()
	{
		thread parser1(Parser(), DataCollections[0], 0, ',');
		thread parser2(Parser(), DataCollections[1], 1, ',');
		thread parser3(Parser(), DataCollections[2], 2, ',');

		thread counter1(Counter(), &ResultTables[0], 0);
		thread counter2(Counter(), &ResultTables[1], 1);
		thread counter3(Counter(), &ResultTables[2], 2);

		parser1.join();
		parser2.join();
		parser3.join();

		counter1.join();
		counter2.join();
		counter3.join();

	}
	void Reduce()
	{
		for (int i = 0; i < no_of_threads; i++)
		{
			for (map<string, int>::iterator itr = ResultTables[i].begin(); itr != ResultTables[i].end(); itr++)
				ResultTable[itr->first] += itr->second;
		}
	}
};

int main()
{
	WordCounter wordcounter;
	wordcounter.Map();
	wordcounter.Reduce();

	for (map<string, int>::iterator itr = ResultTable.begin(); itr != ResultTable.end(); itr++)
		cout << itr->first << "	" << itr->second << endl;
	return 0;

}
/*
green   6
land    3
moon    3
part    3
sun     3
web     6
wed     3
*/

