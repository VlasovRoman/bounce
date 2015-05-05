#ifndef MENU
#define MENU

#include "eventListener.h"
#include <vector>
#include "painter.h"

using namespace std;

struct MenuItem {
	string		text;
	bool 		enable;
};

class Menu {
protected:
	EventListener*		listener;

	vector<MenuItem>	items;

	int 				selectedItemId;

	bool				enterPressed;
public:
	Menu(EventListener* listener);

	void 				frame();

	void 				enableItem(string text);
	bool				isItemPressed(string text);
	int 				getSelectedItemId();
	void 				addItem(string text, bool enable = true);

	void 				draw(Painter* painter);

};

#endif