#ifndef GUI
#define GUI

#include "player.h"
#include "painter.h"

class Gui{
protected:
	Painter* 			painter;
public:
	Gui(Painter* painter);

	void 			draw(Player *player, int ringsNumber);
};

#endif
 