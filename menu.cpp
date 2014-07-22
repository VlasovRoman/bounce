#include "menu.h"

Menu::Menu(EventListener* listener) {
	this->listener = listener;
	itemsCount = 0;
	cursor = -1;
	enterPressed = false;
	count = 0;
	countMax = 75;
}

void Menu::init() {	
	bool is = false;
	for(int i = 0; i < items.size(); i++) {
		if(items[i].enable && !is) {
			items[i].selected = true;
			is = true;
		}
		else
			items[i].selected = false;
	}
}

void Menu::frame() {

	enterPressed = false;
	if(count == 0) {
		if(listener->isKeyDown(KEY_UP)){
			// cursor--;
			// if(cursor < 0) {
			// 	cursor = items.size() - 1;
			// }
			for(int i = 0; i < items.size(); i++) {
				if(items[i].selected) {
					int nextCursor = i - 1;
					while(items[nextCursor].enable == false) {
						nextCursor--;
						if(nextCursor < 0) {
							nextCursor = items.size();
						}
					} 
					items[nextCursor].selected = true;
					items[i].selected = false;
					break;
				}
			}
		}
		if(listener->isKeyDown(KEY_DOWN)) {
			for(int i = 0; i < items.size(); i++) {
				if(items[i].selected) {
					int nextCursor = i + 1;
					while(items[nextCursor].enable == false) {
						nextCursor++;
						if(nextCursor >= items.size()) {
							nextCursor = 0;
						}
					} 
					items[nextCursor].selected = true;
					items[i].selected = false;
					break;
				}
			}
		}
		if(listener->isKeyDown(KEY_ENTER)) {
			enterPressed = true;
		}
			count = 3;
	}
	else
		count--;
}

int Menu::getItemId() {
	if(enterPressed) {
		return cursor;
	}
	else
		return -1;
}

void Menu::addItem(string text, bool enable) {
	MenuItem item = {text, enable};
	items.push_back(item);
}

void Menu::draw(Painter* painter) {
	painter->drawMenuBackground();

	int di = 0;

	for(int i = 0; i < items.size(); i++) {
		if(items[i].enable == false) {
			di++;
		}
		else {
			painter->drawText(15, 15 + (i - di) * 32, items[i].text, 0, 0, 0);
			if(items[i].selected == true) {
				painter->drawMenuItemSelector(12, 15 + (i - di) * 32);
			}
		}
	}

	// for(int i = 0; i < items.size(); i++) {
	// 	i
	// }

}

bool Menu::isItemPressed(string text) {
	if(enterPressed) {
		for(int i = 0; i < items.size(); i++) {
			if(items[i].text == text) {
				return items[i].selected;
			}
		}
	}
}