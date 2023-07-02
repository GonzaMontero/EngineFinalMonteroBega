#ifndef FRAME_H
#define FRAME_H
struct coord {
	float u;
	float v;
};
class Frame {
public:
	Frame() {}
	~Frame() {}
	coord frameCoordinates[4];
};
#endif // FRAME_H