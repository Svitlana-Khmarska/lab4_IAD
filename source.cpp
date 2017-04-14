#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

/*using std::cin;
using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;
*/

using namespace std;

string fname = "text.txt";

class word {
private:
	string text;
	double num_X;	// Ê³ëüê³ñòü ñë³â ó ðå÷åíí³
	double num_Y;	// Ê³ëüê³ñòü ñèìâîë³â ó ðå÷åíí³
public:
	word() {
		text = "";
		num_X = 0.0;
		num_Y = 0.0;
	}
	double get_X() { return num_X; }
	double get_Y() { return num_Y; }
	void increment_X(int n) { num_X += n; }
	void increment_Y(int n) { num_Y += n; }
	const char* get_text() { return text.data(); }
	void set_X(double X) { num_X = X; }
	void set_Y(double Y) { num_Y = Y; }
	void set_text(char *str) {
		for (int i = 0; i < strlen(str); i++) {
			text.push_back(str[i]);
		}
	}
};

vector<word> dictionary;
vector<vector<double>> evklid;

string filename;
void parseSentence(char *line);
int parseFile();
void completeDictionary();
void evklidCalculation();

int main() {

	parseFile();
	evklidCalculation();
	system("pause");
	return 0;
}

void parseSentence(char *line) {
	int strlength = strlen(line);	// dovzhyna rechennja u symvolach
	char w[100];// slovo
	int j = 0;	// nomer bukvy u slovi
	int k = 0;	// kilkist sliv u rechenni
	int l = 0;	// kilkist symvoliv u rechenni
	for (int i = 0; i < strlength; i++) {	// rachuemo kilkist sliv u rechenni
		if (!((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z'))) {
			k++;
		}
		else {
			l++;
		}
	}

	for (int i = 0; i < strlength; i++) {
		if (!((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z'))) {
			w[j] = '\0';
			word ww;
			ww.set_text(w);
			ww.set_X(l);
			ww.set_Y(k);
			dictionary.push_back(ww);
			j = 0;
		}
		else {
			w[j] = line[i];
			j++;
		}
	}

}

void completeDictionary() {
	for (int i = 0; i < dictionary.size(); i++) {
		int n = 1;
		for (int j = i + 1; j < dictionary.size(); j++) {
			if (!strcmp(dictionary[i].get_text(), dictionary[j].get_text())) {
				n++;
				dictionary[i].increment_X(dictionary[j].get_X());
				dictionary[i].increment_Y(dictionary[j].get_Y());
				dictionary[j] = dictionary[dictionary.size() - 1];
				dictionary.pop_back();
				j--;
			}
		}
		dictionary[i].set_X(dictionary[i].get_X() / n);
		dictionary[i].set_Y(dictionary[i].get_Y() / n);
	}
}

int parseFile() {
	ifstream file;
	file.open(fname, ios_base::in);
	char line[300];

	while (!file.eof()) {
		file.getline(line, 300);
		cout << line << endl;
		parseSentence(line);
	}
	for (int i = 0; i < dictionary.size(); i++) {
		cout << dictionary[i].get_text() << " \t" << dictionary[i].get_X() << "\t" << dictionary[i].get_Y() << endl;
	}
	completeDictionary();

	cout << "completed dictionary" << endl;
	for (int i = 0; i < dictionary.size(); i++) {
		cout << dictionary[i].get_text() << " \t" << dictionary[i].get_X() << "\t" << dictionary[i].get_Y() << endl;
	}

	file.close();
	return 0;
}

void evklidCalculation() {
	evklid.resize(dictionary.size());
	for (int i = 0; i < dictionary.size(); i++) {
		evklid[i].resize(dictionary.size());
	}
	for (int i = 0; i < dictionary.size(); i++) {
		for (int j = 0; j < dictionary.size(); j++) {
			if (i == j) {
				evklid[i][j] = 0.0;
			}
			else {
				double a1 = dictionary[i].get_X();
				double a2 = dictionary[j].get_X();
				double b1 = dictionary[i].get_Y();
				double b2 = dictionary[j].get_Y();
				evklid[i][j] = sqrt((a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2));
			}
		}
	}

	cout << endl << "Evklid norms:" << endl;
	for (int i = 0; i < evklid.size(); i++) {
		for (int j = 0; j < evklid[i].size(); j++) {
			cout << setw(10) << evklid[i][j];
		}
		cout << endl;
	}
}
