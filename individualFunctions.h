#ifndef IND_FUNC
#define IND_FUNC

#include <string>
#include <sstream>

using namespace std;

string addIntToString(string text, int number) {
	stringstream stream;
	stream << number;
	text += stream.str();
	return text;
}

#endif