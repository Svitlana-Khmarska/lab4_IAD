fghgfd#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

class word {
private:
	string text;
	double num_X;	// Кількість слів у реченні
	double num_Y;	// Кількість символів у реченні
public:
	word(){
		text = "";
		num_X = 0.0;
		num_Y = 0.0;
	}
	double get_X(){return num_X;}
	double get_Y(){return num_Y;}
	string get_text(){return text;}
	void set_X(double X){num_X = X;}
	void set_Y(double Y){num_Y = Y;}
	void set_text(string str){text.assign(str);}
};

vector<word> dictionary;

string filename;
void parseSentence();
int parseFile();

int main(){

	parseFile();
	return 0;
}