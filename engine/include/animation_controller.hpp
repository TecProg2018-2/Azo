/**
* @file animation_controller.hpp
* @brief Purpose: Controls animaton.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main animation controller its declaration and state.
*/
#ifndef ANIMATION_CONTROLLER_HPP
#define ANIMATION_CONTROLLER_HPP

#include "animation.hpp"
#include "log.h"

#include <map>
#include <iostream>
namespace engine {

	/**
	* @brief An Animation controller class.
	*
	* Generic Component class.
	* It's how the engine'll controll how animation works.
	*/
	class AnimationController : public Animation {
	public:
		void addAnimation(std::string animationName, Animation &animation);
		void startUniqueAnimation(std::string animationName);
		void startAnimation(std::string animationName);
		void stopAnimation(std::string animationName);
		AnimationState getAnimationStatus(std::string animationName);

	private:
		std::map <std::string, Animation *> mAnimationMap;

	public:
		AnimationController();
		AnimationController(GameObject &gameObject);
		
		void init();
		void shutdown();
		void draw();
		void nextSprite(std::string name);
		inline std::string getClassName(){
			return "AnimationController";
		}
	};
}

#endif
