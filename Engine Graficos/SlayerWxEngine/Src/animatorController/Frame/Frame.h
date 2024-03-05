#ifndef FRAME_H
#define FRAME_H
#include "export/export.h"

struct UVcoords
{
	float U;
	float V;
};

class SlayerWxEngine_API Frame
{
public:
	UVcoords coords[4];
	Frame();
	~Frame();

private:

};
#endif
