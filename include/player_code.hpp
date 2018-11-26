/**
 * @file: player_code.hpp
 * @brief Purpose: player_code class declaration
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 *
 * This file contains more than one classs, because it has elements that behave
 * like this other classes.
*/
#ifndef PLAYER_CODE
#define PLAYER_CODE

#include "code_component.hpp"
#include "animation_controller.hpp"

namespace Azo { //Used to avoid writing all the path from Azo context
	class Player;

	/**
	* @brief PlayerCode class
	* This class is used to controll the player's character behaviour.
	* It updates player's animation and audios according to the events.
	*/
	class PlayerCode : public engine::CodeComponent {
		public:
			PlayerCode();
			virtual ~PlayerCode();
			PlayerCode(Player *player);
			void shutdown();

		private:
			Player *mPlayer = nullptr; //Pointer that reffer the player character when created
			engine::AnimationController *mAnimationController = nullptr; //Pointer that handle the animations according to player's behaviour
			engine::AudioController *mAudioController = nullptr; // Pointer that handle the sounds corresponding player's behavour

			void updateCode();
			void updatePhysics();
			void findAnimationController();
			void findAudioController();

	};
}

#endif
