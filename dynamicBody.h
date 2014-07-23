#ifndef DYNAMIC_BODY
#define DYNAMIC_BODY

#include <Box2D/Box2D.h>

class iDynamicBody {
protected:
	b2BodyDef		bodyDef;
	b2Body*			body;

	void 			initStaticBodyDef(b2BodyDef* _body = NULL);
	void 			initDynamicBodyDef(b2BodyDef* _body = NULL);
public:
	iDynamicBody();
	virtual 	~iDynamicBody();
	
	virtual void 		initBody(b2World* world, float x, float y) = 0;
	virtual b2Body*		getBody();
};

#endif