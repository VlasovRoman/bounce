#ifndef MENU
#define MENU

#include "eventListener.h"
#include <vector>
#include "painter.h"
using namespace std;

class Menu {
protected:
	int 				itemsCount;
	EventListener*		listener;

	vector<string> 		items;

	int 				cursor;
	bool				enterPressed;

public:
	Menu(EventListener* listener);

	void 				frame();

	int 				getItemId();
	void 				addItem(string text);

	void 				draw(Painter* painter);

};

#endif