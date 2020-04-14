#include <iostream>
#include <thread>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

//vector<string> WordList;
//map<string, int> ResultTable;
//
//const int input_size = 735;
//const int no_of_threads = 3;

string DataCollection = "web,wed,green,sun,moon,land,part,web,green\ngreen,web,part,land,moon,sun,green,wed,web\nmoon,land,part,web,green,web,wed,green,sun";
map<int, vector<string> > WordLists;
map<string, int> ResultTable;
const int input_size = 27;
const int no_of_threads = 3;
int word_list_size = 0;


class Parser {
public:
	/*void operator()(char delimiter)
	{*/
	void operator()(string SubDataCollection, int index, char delimiter)
	{
		ifstream inFile("4727.txt", ios::in);
		string DataCollection;
		getline(inFile, DataCollection);

		while (true)
		{
			int index = DataCollection.find(",");	// If there is no ",", index == -1
			if (index < 0)
				break;
			DataCollection = DataCollection.replace(index, 1, "");	// Replace all "," with ""
		}
		// Transform all chars into lower chars
		transform(DataCollection.begin(), DataCollection.end(), DataCollection.begin(), ::tolower);	

		string word;
		istringstream wordStream(DataCollection);	// Read each word from DataCollection to wordStream
		while (getline(wordStream, word, delimiter))	// cin word from wordStream into word after each delimiter
		{
			//cout << word << endl;
			WordList.push_back(word);
		}
	}
};

class Counter
{
public:
	void operator()(map<string, int> *pResultTable, int start)
	{
		while (WordList.size() != input_size);
		for (int i = start; i < start + input_size/no_of_threads; i++)	// Start and End position
		{
			/*int count = (*pResultTable)[string(WordList[i])];
			count = count + 1;
			(*pResultTable)[string(WordList[i])] = count;*/
			(*pResultTable)[string(WordList[i])]++;  // Construct a map for each element in vector WordList
		}
	}
};

class WordCounter
{
private:
	map<string, int> ThreadResultTable[no_of_threads];
public:
	void Map()
	{
		thread parser(Parser(), ' ');
		thread counter1(Counter(), &ThreadResultTable[0], 0);
		thread counter2(Counter(), &ThreadResultTable[1], 245);	//245
		thread counter3(Counter(), &ThreadResultTable[2], 490);	//490

		parser.join();
		counter1.join();
		counter2.join();
		counter3.join();
	}
	void Reduce()
	{
		// Reduce Maps and Combine
		for (int i = 0; i < no_of_threads; i++)
		{
			for (map<string, int>::iterator itr = ThreadResultTable[i].begin(); itr != ThreadResultTable[i].end(); itr++)
				ResultTable[itr->first] += itr->second;	// Combine small maps into one big map
		}
	}
};

int main()
{
	fstream fout;
	fout.open("Results.txt", 'w');
	string line;
	ifstream inFile("4727.txt", ios::in);
	getline(inFile, line);
	//cout << line;
	
	WordCounter wordcounter;

	wordcounter.Map();
	wordcounter.Reduce();

	for (map<string, int>::iterator itr = ResultTable.begin(); itr != ResultTable.end(); itr++)
	{
		cout << itr->first << "	" << itr->second << endl;
		//fout << itr->first << "	" << itr->second << endl;
	}
		
	fout.close();
	

	return 0;
}

/*	Also outputs in "Results.txt"
(gnp)	1
18	1
18.5	1
19	1
1978	2
1981	6
1986	4
1987	5
1988	2
2.7	2
200	2
23.8	1
3.5	1
5.3	1
600	1
a	8
above	1
absorbed	1
act	1
added	1
adding	1
administration	3
advisers	2
all	2
allows	1
also	3
american	2
amounted	2
an	2
and	14
another	1
any	2
appropriate	1
approximately	2
arbitrarily	1
are	3
argued	2
as	1
asked	1
assets	1
at	4
attainable	1
average	1
avoiding	1
back	1
based	1
be	3
because	2
beryl	1
between	1
big	1
biggest	1
bill	1
billion	5
broken	1
budget	10
but	1
by	11
call	1
can	1
cause	1
caused	1
chairman	1
change	1
changes	1
close	1
closely	1
compared	1
congress	1
congressional	2
consequences	1
contrary	1
contrast	1
conventional	1
correction	1
could	1
council	2
creative	1
cut	7
cuts	1
cutting	2
day	2
decisions	2
decrease	1
defence	1
deficit	10
deficits	1
demands	2
desire	1
dictate	1
director	1
disagree	1
dislike	2
distrust	1
dlrs	6
dollar	1
doomed	1
down	1
economic	6
economy	1
eliminated	1
employment	1
ending	1
enforce	1
enormously	1
estimates	1
exceeded	1
expenditure	1
extraordinary	1
fail	1
family	1
federal	4
feel	1
few	1
first	1
fiscal	5
for	5
foster	1
fostering	1
four	1
from	3
further	1
general	1
gnp	4
good	1
goods	1
government	5
governments	1
gramm-rudman-hollings	1
greatly	1
gross	1
growth	3
had	1
has	1
have	2
having	1
he	8
helped	1
higher	1
history	1
hope	1
however	1
hurt	1
i	2
ideological	1
if	1
impact	1
in	15
incentives	1
income	1
increase	6
increases	2
indeed	1
induced	1
inflation	2
influence	1
is	9
it	4
its	2
large	1
last	1
latest	1
laws	1
leaving	1
level	2
like	2
likelihood	1
likely	1
limit	1
line-item	1
linked	1
little	1
local	1
long-run	1
looks	3
lot	1
lower	1
lowers	1
making	1
me	1
measures	1
meet	1
merely	1
met	1
methods	1
military	1
misguided	1
mistake	2
more	2
moving	1
nation	1
national	3
needed	1
net	1
new	3
no	1
not	4
now	2
numerical	1
occurred	1
of	28
office	2
officials	1
on	5
one	1
opposition	1
options	1
or	1
our	2
outcome	1
output	1
parts	1
past	1
payday	1
pct	6
penner	8
people	1
percentage	1
permanently	1
plan	1
pledge	1
points	1
policy	1
president	1
pretty	2
private	1
process	3
product	1
production	1
programs	1
projects	1
questioned	1
rate	1
rates	1
reagan	1
real	1
receipts	1
reduce	1
reducing	1
reduction	2
reductions	1
reform	3
reiterated	1
rejecting	1
related	1
remain	2
reports	2
reserve	1
responsibility	1
responsible	1
resulted	1
revenue	1
revolt	1
rolled	1
root	1
roughly	1
rudolph	2
safe	1
said	18
sales	1
same	1
saved	1
saying	1
sees	1
senior	1
september	1
services	1
sets	1
share	2
shifting	1
should	1
signal	1
significantly	1
simply	1
since	1
spending	8
sponsored	1
sprinkel	9
state	2
still	1
strong	1
succeed	1
such	1
suggest	1
suggested	1
sustained	1
symposium	1
system	1
targets	3
tax	13
taxes	3
taxing	1
temporary	1
than	1
that	10
the	58
their	2
there	1
therefore	1
they	1
this	4
time	1
timing	1
to	19
told	1
track	1
trade	1
tries	1
turmoil	1
turned	1
two	3
university	1
unpleasant	1
us	3
very	1
veto	2
virtually	1
votes	1
was	3
wasteful	1
way	1
we	1
were	2
what	1
which	3
while	2
widespread	1
will	6
wisdom	1
with	3
without	2
would	1
year	1
years	1
york	1

*/
