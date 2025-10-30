#ifndef __H_BOARD_DRAWABLE
#define __H_BOARD_DRAWABLE

#include "IDrawable.h"

class Board : IDrawable
{
public: 
	void Draw(IRenderer const* renderer) const override;

};

#endif