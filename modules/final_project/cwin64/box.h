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
				box->setPosition(Vector(x, y, z));
			}

			void set_position(Vector v)
			{
				box->setPosition(v);
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

			Box(Vector position = Vector(25, 25, .2), const std::string file = ManagerEnvironmentConfiguration::getLMM() + "/models/WOOD_PLANTER_BOXES_10K.dae");
	};
}

#endif