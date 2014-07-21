#include "menu.h"

Menu::Menu(EventListener* listener) {
	this->listener = listener;
	itemsCount = 0;
	cursor = -1;
	enterPressed = false;
}

void Menu::frame() {
	enterPressed = false;
	if(listener->isKeyDown(KEY_UP)){
		cursor--;
		if(cursor < 0) {
			cursor = items.size() - 1;
		}
	}
	if(listener->isKeyDown(KEY_DOWN)) {
		cursor++;
		if(cursor > items.size() - 1) {
			cursor = 0;
		}
	}
	if(listener->isKeyDown(KEY_ENTER)) {
		enterPressed = true;
	}
}

int Menu::getItemId() {
	if(enterPressed) {
		return cursor;
	}
	else
		return -1;
}

void Menu::addItem(string item) {
	items.push_back(item);
}

void Menu::draw(Painter* painter) {
	painter->drawMenuBackground();

	for(int i = 0; i < items.size(); i++) {
		painter->drawText(15, 15 + i * 32, items[i], 255, 255, 255);
	}

	painter->drawMenuItemSelector(15, 15 + cursor * 32);
}