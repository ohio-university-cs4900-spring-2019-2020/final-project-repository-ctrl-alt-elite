#pragma once

#include "Model.h"
#include "WO.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{
	class Gun
	{
	public:
		static Gun* New(Vector position = Vector(25, 25, 0.2), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/ak47.obj");

		void set_position(float x, float y, float z)
		{
			gun->setPosition(Vector(x, y, z) += compensation);
		}

		void set_direction(Vector v)
		{
			std::cout << "x: " << v[0] << std::endl;
			std::cout << "y: " << v[1] << std::endl;
			std::cout << "z: " << v[2] << std::endl;

			if (v != last_direction)
			{
				gun->rotateAboutRelX(v[0]);
				gun->rotateAboutRelY(v[1]);
				gun->rotateAboutRelZ(v[2]);
			}
		}

		void set_position(Vector v)
		{
			//v += Vector(0, 0, 0.3);
			gun->setPosition(v += compensation);
		}

		Vector get_postion()
		{
			return gun->getPosition();
		}

		WO* get_world_object()
		{
			return gun;
		}

	private:
		WO* gun;

		Vector last_direction;

		Vector compensation = (0, 0, 0.28);

		Gun(Vector position = (0, 0, 0.28), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/ak47.obj");
	};
}

#endif