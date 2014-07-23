#include "dynamicBody.h"

iDynamicBody::iDynamicBody() {
	body = NULL;
}
iDynamicBody::~iDynamicBody() {
}

void iDynamicBody::initStaticBodyDef(b2BodyDef* _bodyDef) {
	if(_bodyDef == NULL) {
		_bodyDef = &bodyDef;
	}

	_bodyDef->type = b2_staticBody;
	_bodyDef->fixedRotation = true;
	_bodyDef->userData = this;
}

void iDynamicBody::initDynamicBodyDef(b2BodyDef* _bodyDef) {
	if(_bodyDef == NULL) {
		_bodyDef = &bodyDef;
	}
	_bodyDef->type = b2_dynamicBody;
	_bodyDef->linearDamping = 0;
	_bodyDef->fixedRotation = true;
	_bodyDef->allowSleep = false;
	_bodyDef->userData = this;
}

b2Body*	iDynamicBody::getBody() {
	return body;
}