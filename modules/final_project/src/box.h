#pragma once

#include "Model.h"
#include "WO.h"

#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr
{
	class Box
	{
		public:
			static Box* New(Vector position = Vector(25, 25, 0.2), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/WOOD_PLANTER_BOXES_10K.dae");

			void set_position(float x, float y, float z)
			{
				box->setPosition(Vector(x, y, z) += compensation);
				//box->rotateAboutRelX(45);
				//box->rotateAboutRelY(45);
				box->rotateAboutGlobalZ(-45);
			}

			void set_position(Vector v)
			{
				//v += Vector(0, 0, 0.3);
				box->setPosition(v += compensation);
				//box->rotateAboutRelZ(45);
				//box->rotateAboutRelY(45);
				box->rotateAboutGlobalZ(-45);
			}

			Vector get_postion()
			{
				return box->getPosition();
			}

			WO* get_world_object()
			{
				return box;
			}

		private:
			WO* box;

			Vector compensation = (0, 0, 0.28);

			Box(Vector position = (0, 0, 0.28), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/WOOD_PLANTER_BOXES_10K.dae");
	};
}

#endif