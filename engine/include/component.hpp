/**
 * @file component.hpp
 * @brief Purpose: Contains the Component class declaration.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 *
 * This file includes its class and game object class. This happens because it implements
 * component class and uses elements of game_object on methods and behave.
*/
#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

#include <string>


namespace engine {
	/**
     * @brief A GameObject class.
  	 *
     * Reference to GameObject class.
    */
	class GameObject;

	/**
     * @brief A component state class.
  	 *
     * Define Components States to control Loops and other structures.
    */
	enum class State {
		ENABLED,
		DISABLED
	};

	/**
     * @brief A Component class.
  	 *
     * Generic Component class. It's how the engine'll see all components that will try to use it.
    */
	class Component {
//T31
	public:
		Component();
		Component(GameObject &gameObject);
		virtual void init();
		virtual void shutdown();
		virtual void draw();
		virtual void updateCode();
		virtual void enableComponent();
		virtual void disableComponent();
		bool isEnabled();

		/**
		 * @brief access the name of the class.
		 *
		 * Used to get the private attribute className.
		 *
		 * @return string that contains the scene name.
		*/
		virtual inline std::string getClassName(){
			return "Component";
		}
		protected:
			GameObject *gameObject; // represents the object of the game
			State componentState = State::ENABLED; // set the component state (based on enum class State)

	};
}

#endif
