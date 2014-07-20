#include "dynamicBody.h"

iDynamicBody::iDynamicBody() {
	body = NULL;
}
iDynamicBody::~iDynamicBody() {
}

b2Body*	iDynamicBody::getBody() {
	return body;
}