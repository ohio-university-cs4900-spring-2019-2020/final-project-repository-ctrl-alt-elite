#pragma once

#include "Model.h"
#include "WO.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{
	class Target
	{
	public:
		static Target* New(Vector position = Vector(25, 25, 0.2), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/shtfrtr.dae");

		void set_position(float x, float y, float z)
		{
			target->setPosition(Vector(x, y, z) += compensation);
			target->rotateAboutGlobalZ(-45);
		}

		void set_position(Vector v)
		{
			//v += Vector(0, 0, 0.3);
			target->setPosition(v += compensation);
			target->rotateAboutGlobalZ(-45);
		}

		Vector get_postion()
		{
			return target->getPosition();
		}

		WO* get_world_object()
		{
			return target;
		}

	private:
		WO* target;

		Vector compensation = (0, 0, 0.28);

		Target(Vector position = (0, 0, 0.28), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/shtfrtr.dae");
	};
}

#endif