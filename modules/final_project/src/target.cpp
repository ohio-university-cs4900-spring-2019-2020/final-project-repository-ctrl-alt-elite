#include "target.h"

#ifdef AFTR_CONFIG_USE_BOOST

using namespace Aftr;

Target* Target::New(Vector position, const std::string file)
{
	return new Target(position, file);
}

Target::Target(Vector position, const std::string file)
{
	this->target = WO::New(file, Vector(1, 1, 1), MESH_SHADING_TYPE::mstFLAT);
	this->target->setPosition(position);
}

#endif