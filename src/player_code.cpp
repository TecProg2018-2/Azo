/*************************************
@file: player_code.cpp
@brief Purpose: player_code class implementation
GPL v3.0 License
Copyright (c) 2017 Azo

Notice: TheAzo, TheAzoTeam
https://github.com/TecProg2018-2/Azo

This file includes its class and 2 others. This happens because it implements
player_code class and uses elements of other classes on methods and behave.
*************************************/

#include "player_code.hpp"
#include "game.hpp"
#include "player.hpp"

using namespace Azo; //Used to avoid writing all the path from Azo context

/**
 * @brief default constructor for PlayerCode Object
 * @return "void".
*/

PlayerCode::PlayerCode() {}

/**
 * @brief default destructor for PlayerCode Object
 * @return "void".
*/

PlayerCode::~PlayerCode() {}

/**
 * @brief overwritten constructor for the PlayerCode object.
 * @param pointer reffering to player
 * @return "void".
*/

PlayerCode::PlayerCode(Player *player) {
	mPlayer = player;
	mPlayer->mState = PlayerState::WALK;
	mPlayer->mOnGround = true;
	FindAnimationController();
	findAudioController();
}

/**
 * @brief gets the animation.
 * find and sets the corresponding mPlayer animation
 * @return 'void'.
*/

void PlayerCode::FindAnimationController() {
	 mAnimationController = (mPlayer->getAnimationController(typeid(engine::AnimationController)));
}

/**
 * @brief gets the audio.
 * find and sets the corresponding mPlayer audio
 * @return 'void'.
*/

void PlayerCode::findAudioController() {
	 mAudioController = (mPlayer->getAudioController(typeid(engine::AudioController)));
}

/**
 * @brief free the animation pointer
 * when charcter dies, free the animation pointer
 * @return 'void'.
*/

void PlayerCode::shutdown(){
	if (mAnimationController != NULL) {
		 mAnimationController = NULL;

	}
}

/**
 * @brief handle player behaviour
 * defines what happens in each case of player's state
 * according to enum class PlayerStae
 * @return 'void'.
*/


void PlayerCode::updateCode() {
	//It decides case according to the state of mPlayer object.
	//Happens to call the right effects of this state
	switch (mPlayer->mState) {
		case PlayerState::WALK:

			mAnimationController->startUniqueAnimation("walking"); //sets the corresponding animation to the state WALK

			//Check if player hit some obstacle
			if(mPlayer->mPushesRightWall || mPlayer->mPushesLeftWall) {
				//DEBUG("Update code method. Player Speed in X: " << mPlayer->mSpeed.first);
				mPlayer->mSpeed.first = mPlayer->M_ZERO_VECTOR.first; //clear mPlayer walking speed
			} else {
				mPlayer->mSpeed.first = mPlayer->M_WALKING_SPEED;
				//DEBUG("PLAYER SHOULD HAVE SPEED! PLAYER SPEED " << mPlayer->mSpeed.first);
			}

			//check if button 'w' is pressed
			if(engine::Game::instance.inputManager.keyState(engine::Button::W)) {
				//DEBUG("W pressed!");
				mPlayer->mState = PlayerState::JUMP; //Updates mPlayer's state to JUMP
				mPlayer->mSpeed.second = mPlayer->M_JUMPING_SPEED; // Jumping speed.

			} else if (!mPlayer->mOnGround) { //checks if character is not on ground
				//DEBUG("Player isn't on ground. (WALK)");
				mPlayer->mState = PlayerState::JUMP; //Updates mPlayer's state to JUMP
			}

			//checks if button 'S' is pressed
			if(engine::Game::instance.inputManager.keyState(engine::Button::S)) {
				mPlayer->mState = PlayerState::SLIDE; //Updates mPlayer's state to SLIDE
			}

			break;

		case PlayerState::JUMP:

			//checks if character is on ground
			if (mPlayer->mOnGround) {
				mPlayer->mState = PlayerState::WALK; //Updates mPlayer's state to WALK
			}

			mAnimationController->startUniqueAnimation("jumping"); //sets the corresponding animation to the state WALK

			mPlayer->mSpeed.second += (mPlayer->M_GRAVITY * engine::Game::instance.getTimer().getDeltaTime());
			//DEBUG("UpdateCode method. Player Speed in Y: " << mPlayer->m_speed.second);

			//Check if player hit some obstacle
			if (mPlayer->mPushesRightWall) {
				mPlayer->mSpeed.first = mPlayer->M_ZERO_VECTOR.first; //clear mPlayer walking speed
			} else {
				mPlayer->mSpeed.first = mPlayer->M_WALKING_SPEED;         // Walking speed.
			}

			break;

		case PlayerState::SLIDE:
			mAnimationController->startUniqueAnimation("sliding"); //sets the corresponding animation to the state SLIDE

			//check if character was sliding
			if (mAnimationController->getAnimationStatus("sliding") == engine::AnimationState::FINISHED) {
				mPlayer->mState = PlayerState::WALK; //updates mPlayer's state to WALK
				break;
			}

			// sets the normal speed of walking
			mPlayer->mSpeed.second += (mPlayer->M_GRAVITY * engine::Game::instance.getTimer().getDeltaTime());
			//DEBUG("Player speed: " << mPlayer->mSpeed.second);

			//Check if player hit some obstacle
			if (mPlayer->mPushesRightWall) {
				mPlayer->mSpeed.first = mPlayer->M_ZERO_VECTOR.first; //clear mPlayer walking speed
				mPlayer->mState = PlayerState::WALK; //Updates mPlayer's state to WALK
			}

			//check if button 'W' is pressed
			if (engine::Game::instance.inputManager.keyState(engine::Button::W)) {
				mPlayer->mState = PlayerState::JUMP; //Updates mPlayer's state to JUMP
				mPlayer->mSpeed.second = mPlayer->M_JUMPING_SPEED; //normal jump speed of character
			}

			break;
		case PlayerState::DIE:
			mAnimationController->startUniqueAnimation("dying"); //sets the corresponding animation to the state DIE

			mAudioController->playAudio("lost"); //sets the corresponding audio to the state DIE

			break;
		case PlayerState::END:
			//checks if player collected parts is less that the total
			if (mPlayer->mCollectedParts < mPlayer->M_TOTAL_PARTS) {
				mAnimationController->startUniqueAnimation("losing"); // sets the corresponding animation to losing in END state
				//checks if animationStatus is losing
				if (mAnimationController->getAnimationStatus("losing") == engine::AnimationState::FINISHED) {
					mAudioController->playAudio("lost"); // sets the corresponding audio to losing in END state
				}
			} else {
				mAnimationController->startUniqueAnimation("victory"); // sets the corresponding animation to victory in END state
				mAudioController->playAudio("victory"); // sets the corresponding audio to victory in END state
			}

			break;
	}
}
