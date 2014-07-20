#include "gameObject.h" 
#include <iostream>

using namespace std;

GameObject::GameObject(OBJECT_TYPE type) : iDynamicBody() {
	this->type = type;
}

GameObject::~GameObject() {}

OBJECT_TYPE GameObject::getType() {
	return type;
}