#include "menu.h"
#include <iostream>

using namespace std;

Menu::Menu(EventListener* listener) {
	this->listener = listener;
	selectedItemId = -1;
}

void Menu::frame() {
	listener->listen();

	int nextId = 0;
 	if(listener->isKeyDown(KEY_UP) || listener->isKeyDown(KEY_DOWN)){
 		if(listener->isKeyDown(KEY_DOWN)) {
 			nextId = 1;
 		}
 		else
 			nextId = -1;

 		int nextCursor = selectedItemId + nextId;

 		while(items[nextCursor].enable == false) {
 			nextCursor = nextCursor + nextId;
 		}

 		if(nextCursor < 0)
 			nextCursor = items.size() - 1;
 		if(nextCursor >= items.size()) 
 			nextCursor = 0;

 		selectedItemId = nextCursor;
	}

	enterPressed = false;

 	if(listener->isKeyDown(KEY_ENTER)) {
 		enterPressed = true;
 	}
}

int Menu::getSelectedItemId() {
	return selectedItemId;
}

void Menu::addItem(string text, bool enable) {

	MenuItem item = {text, enable};
	items.push_back(item);

	if(items.size() >= 1) {
		selectedItemId = 0;
	}
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
			if(i == selectedItemId) {
				painter->drawMenuItemSelector(12, 15 + (i - di) * 32);
			}
		}
	}
}

bool Menu::isItemPressed(string text) {
	if(enterPressed) {
		for(int i = 0; i < items.size(); i++) {
			if(items[i].text == text && i == selectedItemId) {
				return true;
			}
		}
	}

}

void Menu::enableItem(string text) {
	for(int i = 0; i < items.size(); i++) {
		if(items[i].text == text) {
			items[i].enable = true;
		}
	}
}