/*************************************
@file: player.hpp
@brief Purpose: player class Declaration
GPL v3.0 License
Copyright (c) 2017 Azo

Notice: TheAzo, TheAzoTeam
https://github.com/TecProg2018-2/Azo


This file contains several other classes. It happens because player class
relates to others in many of its attributes and methods.
*************************************/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>
#include <string>

#include "game_object.hpp"
#include "sprite.hpp"

#include "player_code.hpp"
#include "obstacle.hpp"

namespace Azo {  //Used to avoid writing all the path from Azo context

	/**
	* @brief PlayerState enum class
	* This class is used to define the possible player's state.
	* player's behaviour is updated according to this states.
	*/
	enum class PlayerState {
		WALK,
		JUMP,
		SLIDE,
		DIE,
		END,
	};

	/**
	* @brief Player class
	* This class is used to characterize player and set its configurations and behaviour
	*/
	class Player : public engine::GameObject { //This class is used to characterize player and set
																						 //its configuration.
		private:
			engine::AnimationController *mAnimationController; //pointer to corresponding current animation
			engine::AudioController *mAudioController; //pointer to corresponding current audio

			// Add new audios here.
			engine::AudioComponent *mLost; //pointer to corresponding audio
			engine::AudioComponent *mVictorySong; //pointer to corresponding audio

			// Add new animations here.
			engine::Animation *mWalking; //pointer to corresponding animation
			engine::Animation *mJumping; //pointer to corresponding animation
			engine::Animation *mSliding; //pointer to corresponding animation
			engine::Animation *mDying; //pointer to corresponding animation
			engine::Animation *mLosing; //pointer to corresponding animation
			engine::Animation *mVictory; //pointer to corresponding animation

			// Add new sprite vectors here.
			std::vector<engine::Sprite *> mWalkingAnimationSprites; //pointer to corresponding sprite
			std::vector<engine::Sprite *> mJumpingAnimationSprites; //pointer to corresponding sprite
			std::vector<engine::Sprite *> mSlidingAnimationSprites; //pointer to corresponding sprite
			std::vector<engine::Sprite *> mDyingAnimationSprites; //pointer to corresponding sprite
			std::vector<engine::Sprite *> mLosingAnimationSprites; //pointer to corresponding sprite
			std::vector<engine::Sprite *> mVictoryAnimationSprites; //pointer to corresponding sprite

			PlayerCode *mPlayerCode;

		public:
			const std::pair<double, double> M_ZERO_VECTOR = std::make_pair(0.0f, 0.0f); //constant pair of double. Always [0.0f, 0.0f]
			const double M_GRAVITY = 0.003f; //constant double for gravity. The vertical movement
			const double M_JUMPING_SPEED = -1.0f; //constante double. Used along M_GRAVITY to set the vertical movement.
			//Vertical speed should be negative, so the character goes up on canvas.
			const double M_WALKING_SPEED = 4.8f; //constant double for speed. The horizontal movement
			const int M_TOTAL_PARTS = 25; //constant integer for the total parts objects present in game

			PlayerState mState; //PlayerState variable of PlayerState enum class
			std::pair<double, double> mSpeed; //pair of double to set mSpeed

			bool mPushesRightWall; // boolean variable, 1 = true, 0 = false
			bool mPushesLeftWall; // boolean variable, 1 = true, 0 = false
			bool mAtCeiling; // boolean variable, 1 = true, 0 = false
			bool mOnGround; // boolean variable, 1 = true, 0 = false

			int mCollectedParts = 0; // integer, ranges 0 to 25

		private:
			void createComponents();

			// Add new methods to generate the sprite vectors here.
			void generateWalkingAnimation();
			void generateJumpingAnimation();
			void generateSlidingAnimation();
			void generateDyingAnimation();
			void generateLosingAnimation();
			void generateVictoryAnimation();

			inline std::string getClassName(){
				return "Player";
			}

		public:
			Player();
			Player(std::string name, std::pair<double, double> currentPosition);
			void shutdown();
	};
}

#endif
