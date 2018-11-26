/**
 * @file code_component.hpp
 * @brief Purpose: Contains the Code Component class declaration.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo

 * This file includes its class and component class. This happens because it implements
 * code_component class and uses elements of component on methods and behave.
*/
#ifndef CODE_COMPONENT_HPP
#define CODE_COMPONENT_HPP

#include "game_object.hpp"
#include "component.hpp"
#include "game.hpp"
#include "timer.hpp"


namespace engine{
	/**
     * @brief A Code Component class.
  	 *
     * Generic Component class.
	 * It's how the engine'll see all components that will try to use it.
    */
	class CodeComponent : public Component{
		public:
			CodeComponent();
			CodeComponent(GameObject &gameObject);

			void init();
			void shutdown();
			void updateCode();
	};
}

#endif
