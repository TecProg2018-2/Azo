/**
 * @file game_object.hpp
 * @brief Purpose: Contains the Game Object class declaration.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 *
 * This file implements the main game object component its declaration and state.
*/
#ifndef gameObject_HPP
#define gameObject_HPP

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <list>

#include "animation.hpp"
#include "sdl2include.h"
#include "component.hpp"
#include "animation_controller.hpp"
#include "audio_controller.hpp"

namespace engine {

	/**
     * @brief A ObjectState class.
  	 *
     * Define Game Object States to control Loops and other structures.
    */
	enum ObjectState {
		ENABLED,
		DISABLED,
	};

	/**
     * @brief A Game Object class.
  	 *
     * Generic Game Object class. It's how the engine'll see all game objects that will try to use it.
    */
	class GameObject {

		public:
			std::pair<double, double> mCurrentPosition; // Game object's left upper corner coordinates.
			std::pair<double, double> mSize; // Pair that contains X and Y sizes, respectively.
			std::pair<double, double> mCenter; // Center position of game object.
			std::pair<double, double> mHalfSize; // Pair of half size of game object.
			std::list<GameObject *> mParentList; // All parents of game object
			std::string mName; // Name of game object
			ObjectState mObjectState = ObjectState::ENABLED; // Sets the game object state

		public:
			GameObject();
			GameObject(std::string gameObjectName,
					std::pair<double, double> currentPosition);
			void addComponent(Component &component);
			AnimationController* getAnimationController(std::type_index componentType);
			AudioController* getAudioController(std::type_index componentType);
			virtual void init();
			virtual void draw();
			virtual void shutdown();
			virtual void updateCode();
			virtual inline std::string getClassName(){ return "GameObject";}
			std::pair<double, double> calcBottomLeft();
			std::pair<double, double> calcBottomRight();
			std::pair<double, double> calcTopLeft();
			std::pair<double, double> calcTopRight();
			std::pair<double, double> calcRightUp();
			std::pair<double, double> calcRightDown();
			std::pair<double, double> calcLeftUp();
			std::pair<double, double> calcLeftDown();

		protected:
			std::unordered_multimap<std::type_index, Component *> mComponentMap; // Component that represents game object's map.
	};

}

#endif
