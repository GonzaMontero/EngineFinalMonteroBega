#ifndef INPUT_H
#define INPUT_H
#include "export/Export.h"
#include "keycode/Keycode.h"
struct GLFWwindow;
class SlayerWxEngine_API Input
{
private:

public:
	bool GetKey(int keycode, GLFWwindow* window);
	Input();
	~Input();
};
#endif