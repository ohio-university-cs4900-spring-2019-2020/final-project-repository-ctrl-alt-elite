#include "gun.h"

#ifdef AFTR_CONFIG_USE_BOOST

using namespace Aftr;

Gun* Gun::New(Vector position, const std::string file)
{
	return new Gun(position, file);
}

Gun::Gun(Vector position, const std::string file)
{
	this->gun = WO::New(file, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
	this->gun->setPosition(position);
}

#endif