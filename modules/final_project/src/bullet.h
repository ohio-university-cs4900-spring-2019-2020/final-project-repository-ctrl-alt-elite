#pragma once

#include "Model.h"
#include "WO.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{
	class Bullet
	{
	public:
		static Bullet* New(Vector position = Vector(25, 25, 0.2), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/shareablebullet.dae");

		void set_position(float x, float y, float z)
		{
			bullet->setPosition(Vector(x, y, z) += compensation);
			//bullet->rotateAboutRelX(45);
			//bullet->rotateAboutRelY(45);
			//bullet->rotateAboutGlobalZ(-45);
		}

		void set_position(Vector v)
		{
			//v += Vector(0, 0, 0.3);
			bullet->setPosition(v += compensation);
			//bullet->rotateAboutRelZ(45);
			//bullet->rotateAboutRelY(45);
			//bullet->rotateAboutGlobalZ(-45);
		}

		Vector get_postion()
		{
			return bullet->getPosition();
		}

		WO* get_world_object()
		{
			return bullet;
		}

	private:
		WO* bullet;

		Vector compensation = (0, 0, 0.28);

		Bullet(Vector position = (0, 0, 0.28), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/shareablebullet.dae");
	};
}

#endif