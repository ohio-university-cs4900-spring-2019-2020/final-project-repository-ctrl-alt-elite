#include "box.h"

#ifdef AFTR_CONFIG_USE_BOOST

using namespace Aftr;

Box* Box::New(Vector position, const std::string file)
{
	return new Box(position, file);
}

Box::Box(Vector position, const std::string file)
{
	this->box = WO::New(file, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
	this->box->setPosition(position);
}

#endif