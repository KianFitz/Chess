#ifndef __H_BOARD_DRAWABLE
#define __H_BOARD_DRAWABLE

#include "IDrawable.h"

class Board : public IDrawable
{
public: 
	void Draw(IRenderer const* renderer) const override;

};

#endif