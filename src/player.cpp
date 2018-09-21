/*************************************
@file: player.cpp
@brief Purpose: player class implementation
GPL v3.0 License
Copyright (c) 2017 Azo

Notice: TheAzo, TheAzoTeam
https://github.com/TecProg2018-2/Azo

Ths file includes just player declaration because the related use of
other classes comes from it.
*************************************/

#include "player.hpp"

using namespace Azo;  //Used to avoid writing all the path from Azo context

//overloaded construcotr of Player instantiating it
Player::Player(std::string name, std::pair<double, double> currentPosition) {
	DEBUG("Player::Player method.");

	mName = name;
	mCurrentPosition = currentPosition;
	createComponents();
}

//This method free all the pointers of player. It passes through its pointers
//attributes, free them and point to null
void Player::shutdown() {

	//checks if mAnimationController is null
	if (mAnimationController != nullptr) {
		DEBUG("Shutting down mAnimationController");
		mAnimationController->shutdown();
		delete(mAnimationController);
		mAnimationController = nullptr;
	}

	//The subsequent loops will Free the corresponding sprites
	//they run all the existing sprites on their variables
	for (auto eachSprite : mWalkingAnimationSprites) {
		if (eachSprite != nullptr) {
			eachSprite = nullptr;
		}
	}

	for (auto eachSprite : mJumpingAnimationSprites) {
		if (eachSprite != nullptr) {
			eachSprite = nullptr;
		}
	}

	for (auto eachSprite : mSlidingAnimationSprites) {
		if (eachSprite != nullptr) {
			eachSprite = nullptr;
		}
	}

	for (auto eachSprite : mDyingAnimationSprites) {
		if (eachSprite != nullptr) {
			eachSprite = nullptr;
		}
	}

	//The subsequent 'ifs' checks if the variable pointer is pointing to null
	if (mWalking != nullptr) {
		delete(mWalking);
		mWalking = nullptr;
	}

	if (mJumping != nullptr) {
		delete(mJumping);
		mJumping = nullptr;
	}

	if (mSliding != nullptr) {
		delete(mSliding);
		mSliding = nullptr;
	}

	if (mDying != nullptr) {
		delete(mDying);
		mDying = nullptr;
	}

	if (mLosing != nullptr) {
		delete(mLosing);
		mLosing = nullptr;
	}

	if (mPlayerCode != nullptr) {
		mPlayerCode->shutdown();
		delete(mPlayerCode);
		mPlayerCode = nullptr;
	}
}

//This method create the components corresponding to player. Components as the
//possible animations and the possibles audios.
void Player::createComponents() {
	DEBUG("Creating Player Components.");
	generateWalkingAnimation();

	//Receives a new type of animation
	mWalking = new engine::Animation(*this,
									"sprites/CowboyRun.png",
									1000.0f,
									mWalkingAnimationSprites,
									0,
									22,
									true,
									1);

	mAnimationController = new engine::AnimationController();

	DEBUG("Adding walking animation to animation controller.");
	mAnimationController->addAnimation("walking", *mWalking);

	generateJumpingAnimation();

	mJumping = new engine::Animation(*this,
									"sprites/CowboyJump.png",
									800.0f,
									mJumpingAnimationSprites,
									0,
									7,
									false,
									1);
	mJumping->disableComponent();
	DEBUG("Adding jumping animation to animation controller");
	mAnimationController->addAnimation("jumping", *mJumping);

	generateSlidingAnimation();

	mSliding = new engine::Animation(*this,
									"sprites/CowboyDesce.png",
									800.0f,
									mSlidingAnimationSprites,
									0,
									20,
									false,
									1);
	mSliding->disableComponent();

	mAnimationController->addAnimation("sliding", *mSliding);

	generateDyingAnimation();

	mDying = new engine::Animation(*this,
								    "sprites/CowboyTonto.png",
									2000.0f,
									mDyingAnimationSprites,
									0,
									35,
									false,
									1);
	mDying->disableComponent();

	mAnimationController->addAnimation("dying", *mDying);

	generateLosingAnimation();

	mLosing = new engine::Animation(*this,
									"sprites/CowBoyDerrota.png",
									10000.0f,
									mLosingAnimationSprites,
									0,
									6,
									false,
									1);
	mLosing->disableComponent();

	mAnimationController->addAnimation("losing", *mLosing);

	generateVictoryAnimation();

	mVictory = new engine::Animation(*this,
									"sprites/victory.png",
									10.0f,
									mVictoryAnimationSprites,
									0,
									0,
									false,
									1);
	mVictory->disableComponent();

	mAnimationController->addAnimation("victory", *mVictory);

	DEBUG("Adding animation controller to Player.");
	this->addComponent(*mAnimationController);

	//Generates new audios
	mLost = new engine::AudioComponent(*this,
										"audios/derrota.ogg",
										false,
										false);

	mVictorySong = new engine::AudioComponent(*this,
												"audios/victory.ogg",
												false,
												false);

	mAudioController = new engine::AudioController();

	mAudioController->addAudio("lost", *mLost);

	mAudioController->addAudio("victory", *mVictorySong);

	this->addComponent(*mAudioController);

	DEBUG("Creating Player Code.");
	mPlayerCode = new PlayerCode(this);
	this->addComponent(*mPlayerCode);
}

//This method sets the configuration for winning scenario
void Player::generateVictoryAnimation() {
	mVictoryAnimationSprites.push_back(new engine::Sprite());

	/*
		Set the animation sprites coordinates (x, y)
		and its Width and Height based on its coordinates
		spriteWidth = (width - spriteX) and spriteHeight = (Height - spriteY)
	*/

	mVictoryAnimationSprites[0]->spriteX = 0;
	mVictoryAnimationSprites[0]->spriteY = 0;
	mVictoryAnimationSprites[0]->spriteWidth = 180;
	mVictoryAnimationSprites[0]->spriteHeight = 140;
}

//This method sets the configuration for winning scenario
void Player::generateLosingAnimation() {
	const int LOSING_SPRITES = 7;
	for (int i = 0; i < LOSING_SPRITES; i++) {
		mLosingAnimationSprites.push_back(new engine::Sprite());
	}

	/*
		Set the animation sprites coordinates (x, y)
		and its Width and Height based on its coordinates
		spriteWidth = (width - spriteX) and spriteHeight = (Height - spriteY)
	*/

	mLosingAnimationSprites[0]->spriteX = 1;
	mLosingAnimationSprites[0]->spriteY = 1;
	mLosingAnimationSprites[0]->spriteWidth = 70 - 1;
	mLosingAnimationSprites[0]->spriteHeight = 111 - 1;

	mLosingAnimationSprites[1]->spriteX = 72;
	mLosingAnimationSprites[1]->spriteY = 1;
	mLosingAnimationSprites[1]->spriteWidth = 141 - 72;
	mLosingAnimationSprites[1]->spriteHeight = 111 - 1;

	mLosingAnimationSprites[2]->spriteX = 1;
	mLosingAnimationSprites[2]->spriteY = 1;
	mLosingAnimationSprites[2]->spriteWidth = 70 - 1;
	mLosingAnimationSprites[2]->spriteHeight = 111 - 1;

	mLosingAnimationSprites[3]->spriteX = 72;
	mLosingAnimationSprites[3]->spriteY = 1;
	mLosingAnimationSprites[3]->spriteWidth = 141 - 72;
	mLosingAnimationSprites[3]->spriteHeight = 111 - 1;

	mLosingAnimationSprites[4]->spriteX = 1;
	mLosingAnimationSprites[4]->spriteY = 1;
	mLosingAnimationSprites[4]->spriteWidth = 70 - 1;
	mLosingAnimationSprites[4]->spriteHeight = 111 - 1;

	mLosingAnimationSprites[5]->spriteX = 72;
	mLosingAnimationSprites[5]->spriteY = 1;
	mLosingAnimationSprites[5]->spriteWidth = 141 - 72;
	mLosingAnimationSprites[5]->spriteHeight = 111 - 1;

	mLosingAnimationSprites[6]->spriteX = 147;
	mLosingAnimationSprites[6]->spriteY = 4;
	mLosingAnimationSprites[6]->spriteWidth = 209 - 147;
	mLosingAnimationSprites[6]->spriteHeight = 111 - 4;
}

//This method sets the walking sprites on its desgined variables
void Player::generateWalkingAnimation() {
	DEBUG("Generating Player walking animation.");
	const int WALKING_SPRITES = 23;
	//A loop to run all the 23 spaces of the mAnimationSprites vector
	for (int i = 0; i < WALKING_SPRITES; i++) {
		mWalkingAnimationSprites.push_back(new engine::Sprite());
	}//FOR - at the end it will have created the vector of animation sprite with desired number of spaces

	/*
		Set the animation sprites coordinates (x, y)
		and its Width and Height based on its coordinates
		spriteWidth = (width - spriteX) and spriteHeight = (Height - spriteY)
	*/

	mWalkingAnimationSprites[0]->spriteX = 2;
	mWalkingAnimationSprites[0]->spriteY = 34;
	mWalkingAnimationSprites[0]->spriteWidth = 67 - 2;
	mWalkingAnimationSprites[0]->spriteHeight = 139 - 34;

	mWalkingAnimationSprites[1]->spriteX = 71;
	mWalkingAnimationSprites[1]->spriteY = 34;
	mWalkingAnimationSprites[1]->spriteWidth = 136 - 71;
	mWalkingAnimationSprites[1]->spriteHeight = 139 - 34;

	mWalkingAnimationSprites[2]->spriteX = 137;
	mWalkingAnimationSprites[2]->spriteY = 34;
	mWalkingAnimationSprites[2]->spriteWidth = 202 - 137;
	mWalkingAnimationSprites[2]->spriteHeight = 139 - 34;

	mWalkingAnimationSprites[3]->spriteX = 203;
	mWalkingAnimationSprites[3]->spriteY = 20;
	mWalkingAnimationSprites[3]->spriteWidth = 273 - 203;
	mWalkingAnimationSprites[3]->spriteHeight = 139 - 20;

	mWalkingAnimationSprites[4]->spriteX = 274;
	mWalkingAnimationSprites[4]->spriteY = 20;
	mWalkingAnimationSprites[4]->spriteWidth = 344 - 274;
	mWalkingAnimationSprites[4]->spriteHeight = 139 - 20;

	mWalkingAnimationSprites[5]->spriteX = 345;
	mWalkingAnimationSprites[5]->spriteY = 20;
	mWalkingAnimationSprites[5]->spriteWidth = 415 - 345;
	mWalkingAnimationSprites[5]->spriteHeight = 139 - 20;

	mWalkingAnimationSprites[6]->spriteX = 416;
	mWalkingAnimationSprites[6]->spriteY = 26;
	mWalkingAnimationSprites[6]->spriteWidth = 501 - 416;
	mWalkingAnimationSprites[6]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[7]->spriteX = 502;
	mWalkingAnimationSprites[7]->spriteY = 26;
	mWalkingAnimationSprites[7]->spriteWidth = 585 - 502;
	mWalkingAnimationSprites[7]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[8]->spriteX = 587;
	mWalkingAnimationSprites[8]->spriteY = 26;
	mWalkingAnimationSprites[8]->spriteWidth = 672 - 587;
	mWalkingAnimationSprites[8]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[9]->spriteX = 673;
	mWalkingAnimationSprites[9]->spriteY = 26;
	mWalkingAnimationSprites[9]->spriteWidth = 744 - 673;
	mWalkingAnimationSprites[9]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[10]->spriteX = 745;
	mWalkingAnimationSprites[10]->spriteY = 26;
	mWalkingAnimationSprites[10]->spriteWidth = 816 - 745;
	mWalkingAnimationSprites[10]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[11]->spriteX = 889;
	mWalkingAnimationSprites[11]->spriteY = 26;
	mWalkingAnimationSprites[11]->spriteWidth = 960 - 889;
	mWalkingAnimationSprites[11]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[12]->spriteX = 961;
	mWalkingAnimationSprites[12]->spriteY = 34;
	mWalkingAnimationSprites[12]->spriteWidth = 1029 - 961;
	mWalkingAnimationSprites[12]->spriteHeight = 139 - 34;

	mWalkingAnimationSprites[13]->spriteX = 1031;
	mWalkingAnimationSprites[13]->spriteY = 34;
	mWalkingAnimationSprites[13]->spriteWidth = 1099 - 1031;
	mWalkingAnimationSprites[13]->spriteHeight = 139 - 34;

	mWalkingAnimationSprites[14]->spriteX = 1100;
	mWalkingAnimationSprites[14]->spriteY = 20;
	mWalkingAnimationSprites[14]->spriteWidth = 1165 - 1100;
	mWalkingAnimationSprites[14]->spriteHeight = 139 - 20;

	mWalkingAnimationSprites[15]->spriteX = 1166;
	mWalkingAnimationSprites[15]->spriteY = 20;
	mWalkingAnimationSprites[15]->spriteWidth = 1231 - 1166;
	mWalkingAnimationSprites[15]->spriteHeight = 139 - 20;

	mWalkingAnimationSprites[16]->spriteX = 1232;
	mWalkingAnimationSprites[16]->spriteY = 20;
	mWalkingAnimationSprites[16]->spriteWidth = 1296 - 1232;
	mWalkingAnimationSprites[16]->spriteHeight = 139 - 20;

	mWalkingAnimationSprites[17]->spriteX = 1297;
	mWalkingAnimationSprites[17]->spriteY = 26;
	mWalkingAnimationSprites[17]->spriteWidth = 1382 - 1297;
	mWalkingAnimationSprites[17]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[18]->spriteX = 1383;
	mWalkingAnimationSprites[18]->spriteY = 26;
	mWalkingAnimationSprites[18]->spriteWidth = 1468 - 1383;
	mWalkingAnimationSprites[18]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[19]->spriteX = 1469;
	mWalkingAnimationSprites[19]->spriteY = 26;
	mWalkingAnimationSprites[19]->spriteWidth = 1554 - 1469;
	mWalkingAnimationSprites[19]->spriteHeight = 139 - 26;

	mWalkingAnimationSprites[20]->spriteX = 1555;
	mWalkingAnimationSprites[20]->spriteY = 29;
	mWalkingAnimationSprites[20]->spriteWidth = 1629 - 1555;
	mWalkingAnimationSprites[20]->spriteHeight = 139 - 29;

	mWalkingAnimationSprites[21]->spriteX = 1631;
	mWalkingAnimationSprites[21]->spriteY = 29;
	mWalkingAnimationSprites[21]->spriteWidth = 1707 - 1631;
	mWalkingAnimationSprites[21]->spriteHeight = 139 - 29;

	mWalkingAnimationSprites[22]->spriteX = 1709;
	mWalkingAnimationSprites[22]->spriteY = 29;
	mWalkingAnimationSprites[22]->spriteWidth = 1784 - 1709;
	mWalkingAnimationSprites[22]->spriteHeight = 139 - 29;
}

//This method sets the jumping sprites on its desgined variables
void Player::generateJumpingAnimation() {
	DEBUG("Generating Player Jumping Animation.");
	const int JUMPING_SPRITES = 8;
	//create a vector with designed number of sprites
	for (int i = 0; i < JUMPING_SPRITES; i++) {
		mJumpingAnimationSprites.push_back(new engine::Sprite());
	}//FOR - the vector will have been created

	/*
		Set the animation sprites coordinates (x, y)
		and its Width and Height based on its coordinates
		spriteWidth = (width - spriteX) and spriteHeight = (Height - spriteY)
	*/

	mJumpingAnimationSprites[0]->spriteX = 20;
	mJumpingAnimationSprites[0]->spriteY = 22;
	mJumpingAnimationSprites[0]->spriteWidth = 94 - 20;
	mJumpingAnimationSprites[0]->spriteHeight = 127 - 22;

	mJumpingAnimationSprites[1]->spriteX = 14;
	mJumpingAnimationSprites[1]->spriteY = 168;
	mJumpingAnimationSprites[1]->spriteWidth = 97 - 24;
	mJumpingAnimationSprites[1]->spriteHeight = 267 - 168;

	mJumpingAnimationSprites[2]->spriteX = 8;
	mJumpingAnimationSprites[2]->spriteY = 282;
	mJumpingAnimationSprites[2]->spriteWidth = 103 - 8;
	mJumpingAnimationSprites[2]->spriteHeight = 398 - 282;

	mJumpingAnimationSprites[3]->spriteX = 8;
	mJumpingAnimationSprites[3]->spriteY = 422;
	mJumpingAnimationSprites[3]->spriteWidth = 103 - 8;
	mJumpingAnimationSprites[3]->spriteHeight = 538 - 422;

	mJumpingAnimationSprites[4]->spriteX = 16;
	mJumpingAnimationSprites[4]->spriteY = 562;
	mJumpingAnimationSprites[4]->spriteWidth = 97 - 16;
	mJumpingAnimationSprites[4]->spriteHeight = 678 - 562;

	mJumpingAnimationSprites[5]->spriteX = 16;
	mJumpingAnimationSprites[5]->spriteY = 702;
	mJumpingAnimationSprites[5]->spriteWidth = 97 - 16;
	mJumpingAnimationSprites[5]->spriteHeight = 818 - 702;

	mJumpingAnimationSprites[6]->spriteX = 16;
	mJumpingAnimationSprites[6]->spriteY = 842;
	mJumpingAnimationSprites[6]->spriteWidth = 99 - 16;
	mJumpingAnimationSprites[6]->spriteHeight = 958 - 842;

	mJumpingAnimationSprites[7]->spriteX = 14;
	mJumpingAnimationSprites[7]->spriteY = 997;
	mJumpingAnimationSprites[7]->spriteWidth = 83 - 20;
	mJumpingAnimationSprites[7]->spriteHeight = 1107 - 997;
}

//This method sets the sliding sprites on its desgined variables
void Player::generateSlidingAnimation() {
	const int SLIDING_SPRITES = 21;
	//create a vector with designed number of sprites
	for (int i = 0; i < SLIDING_SPRITES; i++) {
		mSlidingAnimationSprites.push_back(new engine::Sprite());
	} // FOR - vector will have been created

	/*
		Set the animation sprites coordinates (x, y)
		and its Width and Height based on its coordinates
		spriteWidth = (width - spriteX) and spriteHeight = (Height - spriteY)
	*/

	mSlidingAnimationSprites[0]->spriteX = 1;
	mSlidingAnimationSprites[0]->spriteY = 59;
	mSlidingAnimationSprites[0]->spriteWidth = 107 - 1;
	mSlidingAnimationSprites[0]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[1]->spriteX = 109;
	mSlidingAnimationSprites[1]->spriteY = 59;
	mSlidingAnimationSprites[1]->spriteWidth = 215 - 109;
	mSlidingAnimationSprites[1]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[2]->spriteX = 217;
	mSlidingAnimationSprites[2]->spriteY = 59;
	mSlidingAnimationSprites[2]->spriteWidth = 323 - 217;
	mSlidingAnimationSprites[2]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[3]->spriteX = 325;
	mSlidingAnimationSprites[3]->spriteY = 59;
	mSlidingAnimationSprites[3]->spriteWidth = 431 - 325;
	mSlidingAnimationSprites[3]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[4]->spriteX = 433;
	mSlidingAnimationSprites[4]->spriteY = 59;
	mSlidingAnimationSprites[4]->spriteWidth = 539 - 433;
	mSlidingAnimationSprites[4]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[5]->spriteX = 541;
	mSlidingAnimationSprites[5]->spriteY = 59;
	mSlidingAnimationSprites[5]->spriteWidth = 647 - 541;
	mSlidingAnimationSprites[5]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[6]->spriteX = 649;
	mSlidingAnimationSprites[6]->spriteY = 59;
	mSlidingAnimationSprites[6]->spriteWidth = 755 - 649;
	mSlidingAnimationSprites[6]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[7]->spriteX = 757;
	mSlidingAnimationSprites[7]->spriteY = 59;
	mSlidingAnimationSprites[7]->spriteWidth = 863 - 757;
	mSlidingAnimationSprites[7]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[8]->spriteX = 865;
	mSlidingAnimationSprites[8]->spriteY = 59;
	mSlidingAnimationSprites[8]->spriteWidth = 971 - 865;
	mSlidingAnimationSprites[8]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[9]->spriteX = 979;
	mSlidingAnimationSprites[9]->spriteY = 59;
	mSlidingAnimationSprites[9]->spriteWidth = 1079 - 979;
	mSlidingAnimationSprites[9]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[10]->spriteX = 1087;
	mSlidingAnimationSprites[10]->spriteY = 59;
	mSlidingAnimationSprites[10]->spriteWidth = 1187 - 1087;
	mSlidingAnimationSprites[10]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[11]->spriteX = 1195;
	mSlidingAnimationSprites[11]->spriteY = 59;
	mSlidingAnimationSprites[11]->spriteWidth = 1295 - 1195;
	mSlidingAnimationSprites[11]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[12]->spriteX = 1303;
	mSlidingAnimationSprites[12]->spriteY = 59;
	mSlidingAnimationSprites[12]->spriteWidth = 1403 - 1303;
	mSlidingAnimationSprites[12]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[13]->spriteX = 1411;
	mSlidingAnimationSprites[13]->spriteY = 59;
	mSlidingAnimationSprites[13]->spriteWidth = 1511 - 1411;
	mSlidingAnimationSprites[13]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[14]->spriteX = 1519;
	mSlidingAnimationSprites[14]->spriteY = 59;
	mSlidingAnimationSprites[14]->spriteWidth = 1619 - 1519;
	mSlidingAnimationSprites[14]->spriteHeight = 139 - 59;

	mSlidingAnimationSprites[15]->spriteX = 1640;
	mSlidingAnimationSprites[15]->spriteY = 40;
	mSlidingAnimationSprites[15]->spriteWidth = 1727 - 1640;
	mSlidingAnimationSprites[15]->spriteHeight = 139 - 40;

	mSlidingAnimationSprites[16]->spriteX = 1748;
	mSlidingAnimationSprites[16]->spriteY = 40;
	mSlidingAnimationSprites[16]->spriteWidth = 1853 - 1748;
	mSlidingAnimationSprites[16]->spriteHeight = 139 - 40;

	mSlidingAnimationSprites[17]->spriteX = 1856;
	mSlidingAnimationSprites[17]->spriteY = 40;
	mSlidingAnimationSprites[17]->spriteWidth = 1943 - 1856;
	mSlidingAnimationSprites[17]->spriteHeight = 139 - 40;

	mSlidingAnimationSprites[18]->spriteX = 1964;
	mSlidingAnimationSprites[18]->spriteY = 40;
	mSlidingAnimationSprites[18]->spriteWidth = 2051 - 1964;
	mSlidingAnimationSprites[18]->spriteHeight = 139 - 40;

	mSlidingAnimationSprites[19]->spriteX = 2072;
	mSlidingAnimationSprites[19]->spriteY = 40;
	mSlidingAnimationSprites[19]->spriteWidth = 2159 - 2072;
	mSlidingAnimationSprites[19]->spriteHeight = 139 - 40;

	mSlidingAnimationSprites[20]->spriteX = 2180;
	mSlidingAnimationSprites[20]->spriteY = 40;
	mSlidingAnimationSprites[20]->spriteWidth = 2267 - 2180;
	mSlidingAnimationSprites[20]->spriteHeight = 139 - 40;
}

//This method sets the jumping sprites on its desgined variables
void Player::generateDyingAnimation() {
	const int DYING_SPRITES = 36;
	//create a vector with designed number of sprites
	for (int i = 0; i < DYING_SPRITES; i++) {
		mDyingAnimationSprites.push_back(new engine::Sprite());
	}//FOR - vector will have been created

	/*
		Set the animation sprites coordinates (x, y)
		and its Width and Height based on its coordinates
		spriteWidth = (width - spriteX) and spriteHeight = (Height - spriteY)
	*/

	mDyingAnimationSprites[0]->spriteX = 4;
	mDyingAnimationSprites[0]->spriteY = 47;
	mDyingAnimationSprites[0]->spriteWidth = 73 - 4;
	mDyingAnimationSprites[0]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[1]->spriteX = 112;
	mDyingAnimationSprites[1]->spriteY = 47;
	mDyingAnimationSprites[1]->spriteWidth = 181 - 112;
	mDyingAnimationSprites[1]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[2]->spriteX = 220;
	mDyingAnimationSprites[2]->spriteY = 47;
	mDyingAnimationSprites[2]->spriteWidth = 289 - 220;
	mDyingAnimationSprites[2]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[3]->spriteX = 328;
	mDyingAnimationSprites[3]->spriteY = 47;
	mDyingAnimationSprites[3]->spriteWidth = 397 - 328;
	mDyingAnimationSprites[3]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[4]->spriteX = 436;
	mDyingAnimationSprites[4]->spriteY = 47;
	mDyingAnimationSprites[4]->spriteWidth = 505 - 436;
	mDyingAnimationSprites[4]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[5]->spriteX = 544;
	mDyingAnimationSprites[5]->spriteY = 47;
	mDyingAnimationSprites[5]->spriteWidth = 613 - 544;
	mDyingAnimationSprites[5]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[6]->spriteX = 652;
	mDyingAnimationSprites[6]->spriteY = 47;
	mDyingAnimationSprites[6]->spriteWidth = 721 - 652;
	mDyingAnimationSprites[6]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[7]->spriteX = 760;
	mDyingAnimationSprites[7]->spriteY = 47;
	mDyingAnimationSprites[7]->spriteWidth = 829 - 760;
	mDyingAnimationSprites[7]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[8]->spriteX = 868;
	mDyingAnimationSprites[8]->spriteY = 47;
	mDyingAnimationSprites[8]->spriteWidth = 937 - 868;
	mDyingAnimationSprites[8]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[9]->spriteX = 976;
	mDyingAnimationSprites[9]->spriteY = 47;
	mDyingAnimationSprites[9]->spriteWidth = 1045 - 976;
	mDyingAnimationSprites[9]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[10]->spriteX = 1084;
	mDyingAnimationSprites[10]->spriteY = 47;
	mDyingAnimationSprites[10]->spriteWidth = 1153 - 1084;
	mDyingAnimationSprites[10]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[11]->spriteX = 1192;
	mDyingAnimationSprites[11]->spriteY = 47;
	mDyingAnimationSprites[11]->spriteWidth = 1261 - 1192;
	mDyingAnimationSprites[11]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[12]->spriteX = 1300;
	mDyingAnimationSprites[12]->spriteY = 47;
	mDyingAnimationSprites[12]->spriteWidth = 1369 - 1300;
	mDyingAnimationSprites[12]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[13]->spriteX = 1408;
	mDyingAnimationSprites[13]->spriteY = 47;
	mDyingAnimationSprites[13]->spriteWidth = 1477 - 1408;
	mDyingAnimationSprites[13]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[14]->spriteX = 1516;
	mDyingAnimationSprites[14]->spriteY = 47;
	mDyingAnimationSprites[14]->spriteWidth = 1585 - 1516;
	mDyingAnimationSprites[14]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[15]->spriteX = 1624;
	mDyingAnimationSprites[15]->spriteY = 47;
	mDyingAnimationSprites[15]->spriteWidth = 1693 - 1624;
	mDyingAnimationSprites[15]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[16]->spriteX = 1732;
	mDyingAnimationSprites[16]->spriteY = 47;
	mDyingAnimationSprites[16]->spriteWidth = 1801 - 1732;
	mDyingAnimationSprites[16]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[17]->spriteX = 1840;
	mDyingAnimationSprites[17]->spriteY = 47;
	mDyingAnimationSprites[17]->spriteWidth = 1909 - 1840;
	mDyingAnimationSprites[17]->spriteHeight = 138 - 47;

	mDyingAnimationSprites[18]->spriteX = 1948;
	mDyingAnimationSprites[18]->spriteY = 47;
	mDyingAnimationSprites[18]->spriteWidth = 2017 - 1948;
	mDyingAnimationSprites[18]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[19]->spriteX = 2056;
	mDyingAnimationSprites[19]->spriteY = 47;
	mDyingAnimationSprites[19]->spriteWidth = 2152 - 2056;
	mDyingAnimationSprites[19]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[20]->spriteX = 2164;
	mDyingAnimationSprites[20]->spriteY = 47;
	mDyingAnimationSprites[20]->spriteWidth = 2233 - 2164;
	mDyingAnimationSprites[20]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[21]->spriteX = 2272;
	mDyingAnimationSprites[21]->spriteY = 47;
	mDyingAnimationSprites[21]->spriteWidth = 2341 - 2272;
	mDyingAnimationSprites[21]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[22]->spriteX = 2380;
	mDyingAnimationSprites[22]->spriteY = 47;
	mDyingAnimationSprites[22]->spriteWidth = 2449 - 2380;
	mDyingAnimationSprites[22]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[23]->spriteX = 2488;
	mDyingAnimationSprites[23]->spriteY = 47;
	mDyingAnimationSprites[23]->spriteWidth = 2557 - 2488;
	mDyingAnimationSprites[23]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[24]->spriteX = 2596;
	mDyingAnimationSprites[24]->spriteY = 47;
	mDyingAnimationSprites[24]->spriteWidth = 2665 - 2596;
	mDyingAnimationSprites[24]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[25]->spriteX = 2704;
	mDyingAnimationSprites[25]->spriteY = 47;
	mDyingAnimationSprites[25]->spriteWidth = 2773 - 2704;
	mDyingAnimationSprites[25]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[26]->spriteX = 2812;
	mDyingAnimationSprites[26]->spriteY = 47;
	mDyingAnimationSprites[26]->spriteWidth = 2881 - 2812;
	mDyingAnimationSprites[26]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[27]->spriteX = 2920;
	mDyingAnimationSprites[27]->spriteY = 47;
	mDyingAnimationSprites[27]->spriteWidth = 2989 - 2920;
	mDyingAnimationSprites[27]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[28]->spriteX = 3028;
	mDyingAnimationSprites[28]->spriteY = 47;
	mDyingAnimationSprites[28]->spriteWidth = 3097 - 3028;
	mDyingAnimationSprites[28]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[29]->spriteX = 3136;
	mDyingAnimationSprites[29]->spriteY = 47;
	mDyingAnimationSprites[29]->spriteWidth = 3205 - 3136;
	mDyingAnimationSprites[29]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[30]->spriteX = 3244;
	mDyingAnimationSprites[30]->spriteY = 47;
	mDyingAnimationSprites[30]->spriteWidth = 3313 - 3244;
	mDyingAnimationSprites[30]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[31]->spriteX = 3352;
	mDyingAnimationSprites[31]->spriteY = 47;
	mDyingAnimationSprites[31]->spriteWidth = 3421 - 3352;
	mDyingAnimationSprites[31]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[32]->spriteX = 3460;
	mDyingAnimationSprites[32]->spriteY = 47;
	mDyingAnimationSprites[32]->spriteWidth = 3529 - 3460;
	mDyingAnimationSprites[32]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[33]->spriteX = 3568;
	mDyingAnimationSprites[33]->spriteY = 47;
	mDyingAnimationSprites[33]->spriteWidth = 3637 - 3568;
	mDyingAnimationSprites[33]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[34]->spriteX = 3676;
	mDyingAnimationSprites[34]->spriteY = 47;
	mDyingAnimationSprites[34]->spriteWidth = 3745 - 3676;
	mDyingAnimationSprites[34]->spriteHeight = 139 - 47;

	mDyingAnimationSprites[35]->spriteX = 3784;
	mDyingAnimationSprites[35]->spriteY = 47;
	mDyingAnimationSprites[35]->spriteWidth = 3853 - 3784;
	mDyingAnimationSprites[35]->spriteHeight = 139 - 47;
}
