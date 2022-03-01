#include "Entity2D.h"

Entity2D::Entity2D(Renderer* _renderer): Entity(_renderer)
{
}

Entity2D::Entity2D(): Entity()
{

}

void Entity2D::SetRenderer(Renderer* _renderer)
{
	renderer = _renderer;
}
