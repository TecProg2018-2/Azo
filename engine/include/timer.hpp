/** 
  * @file timer.hpp
  * @brief Purpose: Contains the Timer class declaration.
  * 
  * GPL v3.0 License
  * Copyright (c) 2017 Azo
  *
  * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
 */
#ifndef TIMER_HPP
#define TIMER_HPP

#include "sdl2include.h"

namespace engine {
 
	//@brief class to calculate time operations	 
	class Timer {
		private:
			unsigned int startTicks;
			unsigned int elapsedTicks;
			float deltaTime;
		public:
			Timer();
			~Timer();

			void Reset();
			void DeltaTime();
			void step();
			float getDeltaTime();
	};
}

#endif
