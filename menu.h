#ifndef MENU
#define MENU

#include "eventListener.h"
#include <vector>
#include "painter.h"
using namespace std;

struct MenuItem {
	string		text;
	bool 		enable;
	bool		selected;
};


class Menu {
protected:
	int 				count;
	int 				countMax;
	int 				itemsCount;
	EventListener*		listener;

	vector<MenuItem>	items;

	int 				cursor;
	int 				selectedItemId;

	bool				enterPressed;

public:
	Menu(EventListener* listener);

	void 				frame();

	void 				init();

	bool				isItemPressed(string text);
	int 				getItemId();
	void 				addItem(string text, bool enable = true);

	void 				draw(Painter* painter);

};

#endif