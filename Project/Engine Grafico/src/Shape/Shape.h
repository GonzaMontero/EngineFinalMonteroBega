#ifndef SHAPE_H
#define SHAPE_H

#include "../Utils/Export.h"
#include "../Entity/Entity2D.h"

namespace Engine {

	class ENGINE_API Shape : public Entity2D 
	{
	public:
		Shape(Renderer* renderer, unsigned int vertices);
		~Shape();
		void Draw() override;

	private:
		void SetShader();
	};
}
#endif // !SHAPE_H
