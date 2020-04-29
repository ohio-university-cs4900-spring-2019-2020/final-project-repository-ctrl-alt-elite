#include "bullet.h"
#include "CustomBalistics.cpp"

#ifdef AFTR_CONFIG_USE_BOOST

using namespace Aftr;

Bullet* Bullet::New(Vector position, const std::string file)
{
	return new Bullet(position, file);
}

Bullet::Bullet(Vector position, const std::string file)
{
	this->bullet = WO::New(file, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
	this->bullet->setPosition(position);
}

#endif