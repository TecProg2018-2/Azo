/**
* @file: player.cpp
* @brief Purpose: player class implementation
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file includes just player declaration because the related use of
* other classes comes from it.
*/
#include "player.hpp"

using namespace Azo;  //Used to avoid writing all the path from Azo context

//overloaded constructor of Player instantiating it
Player::Player(std::string name, std::pair<double, double> currentPosition) {
	DEBUG("Player::Player method.");

	mName = name;
	mCurrentPosition = currentPosition;
	createComponents();
}

//This method create the components corresponding to player. Components as the
//possible animations and the possibles audios.
void Player::createComponents() {
	DEBUG("Creating Player Components.");

	generateWalkingAnimation();
	mWalking = new engine::Animation(
		*this,
		"sprites/CowboyRun.png",
		1000.0f,
		mWalkingAnimationSprites,
		0,
		22,
		true,
		1
	);
	mAnimationController = new engine::AnimationController();
	DEBUG("Adding walking animation to animation controller.");
	mAnimationController->addAnimation("walking", *mWalking);

	generateJumpingAnimation();
	mJumping = new engine::Animation(
		*this,
		"sprites/CowboyJump.png",
		800.0f,
		mJumpingAnimationSprites,
		0,
		7,
		false,
		1
	);
	mJumping->disableComponent();
	DEBUG("Adding jumping animation to animation controller");
	mAnimationController->addAnimation("jumping", *mJumping);

	generateSlidingAnimation();
	mSliding = new engine::Animation(
		*this,
		"sprites/CowboyDesce.png",
		800.0f,
		mSlidingAnimationSprites,
		0,
		20,
		false,
		1
	);
	mSliding->disableComponent();
	mAnimationController->addAnimation("sliding", *mSliding);

	generateDyingAnimation();
	mDying = new engine::Animation(
		*this,
		"sprites/CowboyTonto.png",
		2000.0f,
		mDyingAnimationSprites,
		0,
		35,
		false,
		1
	);
	mDying->disableComponent();
	mAnimationController->addAnimation("dying", *mDying);

	generateLosingAnimation();
	mLosing = new engine::Animation(
		*this,
		"sprites/CowBoyDerrota.png",
		10000.0f,
		mLosingAnimationSprites,
		0,
		6,
		false,
		1
	);
	mLosing->disableComponent();
	mAnimationController->addAnimation("losing", *mLosing);

	generateVictoryAnimation();
	mVictory = new engine::Animation(
		*this,
		"sprites/victory.png",
		10.0f,
		mVictoryAnimationSprites,
		0,
		0,
		false,
		1
	);
	mVictory->disableComponent();
	mAnimationController->addAnimation("victory", *mVictory);

	DEBUG("Adding animation controller to Player.");
	this->addComponent(*mAnimationController);

	//Generates new audios
	mLost = new engine::AudioComponent(
		*this,
		"audios/derrota.ogg",
		false,
		false
	);
	mVictorySong = new engine::AudioComponent(
		*this,
		"audios/victory.ogg",
		false,
		false
	);
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

	mVictoryAnimationSprites[0]->setSpriteX((unsigned int)0);
	mVictoryAnimationSprites[0]->setSpriteY((unsigned int)0);
	mVictoryAnimationSprites[0]->setSpriteWidth((unsigned int)180);
	mVictoryAnimationSprites[0]->setSpriteHeight((unsigned int)140);
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

	mLosingAnimationSprites[0]->setSpriteX((unsigned int)1);
	mLosingAnimationSprites[0]->setSpriteY((unsigned int)1);
	mLosingAnimationSprites[0]->setSpriteWidth((unsigned int)70 - 1);
	mLosingAnimationSprites[0]->setSpriteHeight((unsigned int)111 - 1);

	mLosingAnimationSprites[1]->setSpriteX((unsigned int)72);
	mLosingAnimationSprites[1]->setSpriteY((unsigned int)1);
	mLosingAnimationSprites[1]->setSpriteWidth((unsigned int)141 - 72);
	mLosingAnimationSprites[1]->setSpriteHeight((unsigned int)111 - 1);

	mLosingAnimationSprites[2]->setSpriteX((unsigned int)1);
	mLosingAnimationSprites[2]->setSpriteY((unsigned int)1);
	mLosingAnimationSprites[2]->setSpriteWidth((unsigned int)70 - 1);
	mLosingAnimationSprites[2]->setSpriteHeight((unsigned int)111 - 1);

	mLosingAnimationSprites[3]->setSpriteX((unsigned int)72);
	mLosingAnimationSprites[3]->setSpriteY((unsigned int)1);
	mLosingAnimationSprites[3]->setSpriteWidth((unsigned int)(unsigned int)141 - 72);
	mLosingAnimationSprites[3]->setSpriteHeight((unsigned int)111 - 1);

	mLosingAnimationSprites[4]->setSpriteX((unsigned int)1);
	mLosingAnimationSprites[4]->setSpriteY((unsigned int)1);
	mLosingAnimationSprites[4]->setSpriteWidth((unsigned int)70 - 1);
	mLosingAnimationSprites[4]->setSpriteHeight((unsigned int)111 - 1);

	mLosingAnimationSprites[5]->setSpriteX((unsigned int)72);
	mLosingAnimationSprites[5]->setSpriteY((unsigned int)1);
	mLosingAnimationSprites[5]->setSpriteWidth((unsigned int)141 - 72);
	mLosingAnimationSprites[5]->setSpriteHeight((unsigned int)111 - 1);

	mLosingAnimationSprites[6]->setSpriteX((unsigned int)147);
	mLosingAnimationSprites[6]->setSpriteY((unsigned int)4);
	mLosingAnimationSprites[6]->setSpriteWidth((unsigned int)209 - 147);
	mLosingAnimationSprites[6]->setSpriteHeight((unsigned int)111 - 4);
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

	mWalkingAnimationSprites[0]->setSpriteX((unsigned int)2);
	mWalkingAnimationSprites[0]->setSpriteY((unsigned int)34);
	mWalkingAnimationSprites[0]->setSpriteWidth((unsigned int)67 - 2);
	mWalkingAnimationSprites[0]->setSpriteHeight((unsigned int)139 - 34);

	mWalkingAnimationSprites[1]->setSpriteX((unsigned int)71);
	mWalkingAnimationSprites[1]->setSpriteY((unsigned int)34);
	mWalkingAnimationSprites[1]->setSpriteWidth((unsigned int)136 - 71);
	mWalkingAnimationSprites[1]->setSpriteHeight((unsigned int)139 - 34);

	mWalkingAnimationSprites[2]->setSpriteX((unsigned int)137);
	mWalkingAnimationSprites[2]->setSpriteY((unsigned int)34);
	mWalkingAnimationSprites[2]->setSpriteWidth((unsigned int)202 - 137);
	mWalkingAnimationSprites[2]->setSpriteHeight((unsigned int)139 - 34);

	mWalkingAnimationSprites[3]->setSpriteX((unsigned int)203);
	mWalkingAnimationSprites[3]->setSpriteY((unsigned int)20);
	mWalkingAnimationSprites[3]->setSpriteWidth((unsigned int)273 - 203);
	mWalkingAnimationSprites[3]->setSpriteHeight((unsigned int)139 - 20);

	mWalkingAnimationSprites[4]->setSpriteX((unsigned int)274);
	mWalkingAnimationSprites[4]->setSpriteY((unsigned int)20);
	mWalkingAnimationSprites[4]->setSpriteWidth((unsigned int)344 - 274);
	mWalkingAnimationSprites[4]->setSpriteHeight((unsigned int)139 - 20);

	mWalkingAnimationSprites[5]->setSpriteX((unsigned int)345);
	mWalkingAnimationSprites[5]->setSpriteY((unsigned int)20);
	mWalkingAnimationSprites[5]->setSpriteWidth((unsigned int)415 - 345);
	mWalkingAnimationSprites[5]->setSpriteHeight((unsigned int)139 - 20);

	mWalkingAnimationSprites[6]->setSpriteX((unsigned int)416);
	mWalkingAnimationSprites[6]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[6]->setSpriteWidth((unsigned int)501 - 416);
	mWalkingAnimationSprites[6]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[7]->setSpriteX((unsigned int)502);
	mWalkingAnimationSprites[7]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[7]->setSpriteWidth((unsigned int)585 - 502);
	mWalkingAnimationSprites[7]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[8]->setSpriteX((unsigned int)587);
	mWalkingAnimationSprites[8]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[8]->setSpriteWidth((unsigned int)672 - 587);
	mWalkingAnimationSprites[8]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[9]->setSpriteX((unsigned int)673);
	mWalkingAnimationSprites[9]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[9]->setSpriteWidth((unsigned int)744 - 673);
	mWalkingAnimationSprites[9]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[10]->setSpriteX((unsigned int)745);
	mWalkingAnimationSprites[10]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[10]->setSpriteWidth((unsigned int)816 - 745);
	mWalkingAnimationSprites[10]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[11]->setSpriteX((unsigned int)889);
	mWalkingAnimationSprites[11]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[11]->setSpriteWidth((unsigned int)960 - 889);
	mWalkingAnimationSprites[11]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[12]->setSpriteX((unsigned int)961);
	mWalkingAnimationSprites[12]->setSpriteY((unsigned int)34);
	mWalkingAnimationSprites[12]->setSpriteWidth((unsigned int)1029 - 961);
	mWalkingAnimationSprites[12]->setSpriteHeight((unsigned int)139 - 34);

	mWalkingAnimationSprites[13]->setSpriteX((unsigned int)1031);
	mWalkingAnimationSprites[13]->setSpriteY((unsigned int)34);
	mWalkingAnimationSprites[13]->setSpriteWidth((unsigned int)1099 - 1031);
	mWalkingAnimationSprites[13]->setSpriteHeight((unsigned int)139 - 34);

	mWalkingAnimationSprites[14]->setSpriteX((unsigned int)1100);
	mWalkingAnimationSprites[14]->setSpriteY((unsigned int)20);
	mWalkingAnimationSprites[14]->setSpriteWidth((unsigned int)1165 - 1100);
	mWalkingAnimationSprites[14]->setSpriteHeight((unsigned int)139 - 20);

	mWalkingAnimationSprites[15]->setSpriteX((unsigned int)1166);
	mWalkingAnimationSprites[15]->setSpriteY((unsigned int)20);
	mWalkingAnimationSprites[15]->setSpriteWidth((unsigned int)1231 - 1166);
	mWalkingAnimationSprites[15]->setSpriteHeight((unsigned int)139 - 20);

	mWalkingAnimationSprites[16]->setSpriteX((unsigned int)1232);
	mWalkingAnimationSprites[16]->setSpriteY((unsigned int)20);
	mWalkingAnimationSprites[16]->setSpriteWidth((unsigned int)1296 - 1232);
	mWalkingAnimationSprites[16]->setSpriteHeight((unsigned int)139 - 20);

	mWalkingAnimationSprites[17]->setSpriteX((unsigned int)1297);
	mWalkingAnimationSprites[17]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[17]->setSpriteWidth((unsigned int)1382 - 1297);
	mWalkingAnimationSprites[17]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[18]->setSpriteX((unsigned int)1383);
	mWalkingAnimationSprites[18]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[18]->setSpriteWidth((unsigned int)1468 - 1383);
	mWalkingAnimationSprites[18]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[19]->setSpriteX((unsigned int)1469);
	mWalkingAnimationSprites[19]->setSpriteY((unsigned int)26);
	mWalkingAnimationSprites[19]->setSpriteWidth((unsigned int)1554 - 1469);
	mWalkingAnimationSprites[19]->setSpriteHeight((unsigned int)139 - 26);

	mWalkingAnimationSprites[20]->setSpriteX((unsigned int)1555);
	mWalkingAnimationSprites[20]->setSpriteY((unsigned int)29);
	mWalkingAnimationSprites[20]->setSpriteWidth((unsigned int)1629 - 1555);
	mWalkingAnimationSprites[20]->setSpriteHeight((unsigned int)139 - 29);

	mWalkingAnimationSprites[21]->setSpriteX((unsigned int)1631);
	mWalkingAnimationSprites[21]->setSpriteY((unsigned int)29);
	mWalkingAnimationSprites[21]->setSpriteWidth((unsigned int)1707 - 1631);
	mWalkingAnimationSprites[21]->setSpriteHeight((unsigned int)139 - 29);

	mWalkingAnimationSprites[22]->setSpriteX((unsigned int)1709);
	mWalkingAnimationSprites[22]->setSpriteY((unsigned int)29);
	mWalkingAnimationSprites[22]->setSpriteWidth((unsigned int)1784 - 1709);
	mWalkingAnimationSprites[22]->setSpriteHeight((unsigned int)139 - 29);
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

	mJumpingAnimationSprites[0]->setSpriteX((unsigned int)20);
	mJumpingAnimationSprites[0]->setSpriteY((unsigned int)22);
	mJumpingAnimationSprites[0]->setSpriteWidth((unsigned int)94 - 20);
	mJumpingAnimationSprites[0]->setSpriteHeight((unsigned int)127 - 22);

	mJumpingAnimationSprites[1]->setSpriteX((unsigned int)14);
	mJumpingAnimationSprites[1]->setSpriteY((unsigned int)168);
	mJumpingAnimationSprites[1]->setSpriteWidth((unsigned int)97 - 24);
	mJumpingAnimationSprites[1]->setSpriteHeight((unsigned int)267 - 168);

	mJumpingAnimationSprites[2]->setSpriteX((unsigned int)8);
	mJumpingAnimationSprites[2]->setSpriteY((unsigned int)282);
	mJumpingAnimationSprites[2]->setSpriteWidth((unsigned int)103 - 8);
	mJumpingAnimationSprites[2]->setSpriteHeight((unsigned int)398 - 282);

	mJumpingAnimationSprites[3]->setSpriteX((unsigned int)8);
	mJumpingAnimationSprites[3]->setSpriteY((unsigned int)422);
	mJumpingAnimationSprites[3]->setSpriteWidth((unsigned int)103 - 8);
	mJumpingAnimationSprites[3]->setSpriteHeight((unsigned int)538 - 422);

	mJumpingAnimationSprites[4]->setSpriteX((unsigned int)16);
	mJumpingAnimationSprites[4]->setSpriteY((unsigned int)562);
	mJumpingAnimationSprites[4]->setSpriteWidth((unsigned int)97 - 16);
	mJumpingAnimationSprites[4]->setSpriteHeight((unsigned int)678 - 562);

	mJumpingAnimationSprites[5]->setSpriteX((unsigned int)16);
	mJumpingAnimationSprites[5]->setSpriteY((unsigned int)702);
	mJumpingAnimationSprites[5]->setSpriteWidth((unsigned int)97 - 16);
	mJumpingAnimationSprites[5]->setSpriteHeight((unsigned int)818 - 702);

	mJumpingAnimationSprites[6]->setSpriteX((unsigned int)16);
	mJumpingAnimationSprites[6]->setSpriteY((unsigned int)842);
	mJumpingAnimationSprites[6]->setSpriteWidth((unsigned int)99 - 16);
	mJumpingAnimationSprites[6]->setSpriteHeight((unsigned int)958 - 842);

	mJumpingAnimationSprites[7]->setSpriteX((unsigned int)14);
	mJumpingAnimationSprites[7]->setSpriteY((unsigned int)997);
	mJumpingAnimationSprites[7]->setSpriteWidth((unsigned int)83 - 20);
	mJumpingAnimationSprites[7]->setSpriteHeight((unsigned int)1107 - 997);
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

	mSlidingAnimationSprites[0]->setSpriteX((unsigned int)1);
	mSlidingAnimationSprites[0]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[0]->setSpriteWidth((unsigned int)107 - 1);
	mSlidingAnimationSprites[0]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[1]->setSpriteX((unsigned int)109);
	mSlidingAnimationSprites[1]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[1]->setSpriteWidth((unsigned int)215 - 109);
	mSlidingAnimationSprites[1]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[2]->setSpriteX((unsigned int)217);
	mSlidingAnimationSprites[2]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[2]->setSpriteWidth((unsigned int)323 - 217);
	mSlidingAnimationSprites[2]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[3]->setSpriteX((unsigned int)325);
	mSlidingAnimationSprites[3]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[3]->setSpriteWidth((unsigned int)431 - 325);
	mSlidingAnimationSprites[3]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[4]->setSpriteX((unsigned int)433);
	mSlidingAnimationSprites[4]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[4]->setSpriteWidth((unsigned int)539 - 433);
	mSlidingAnimationSprites[4]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[5]->setSpriteX((unsigned int)541);
	mSlidingAnimationSprites[5]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[5]->setSpriteWidth((unsigned int)647 - 541);
	mSlidingAnimationSprites[5]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[6]->setSpriteX((unsigned int)649);
	mSlidingAnimationSprites[6]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[6]->setSpriteWidth((unsigned int)755 - 649);
	mSlidingAnimationSprites[6]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[7]->setSpriteX((unsigned int)757);
	mSlidingAnimationSprites[7]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[7]->setSpriteWidth((unsigned int)863 - 757);
	mSlidingAnimationSprites[7]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[8]->setSpriteX((unsigned int)865);
	mSlidingAnimationSprites[8]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[8]->setSpriteWidth((unsigned int)971 - 865);
	mSlidingAnimationSprites[8]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[9]->setSpriteX((unsigned int)979);
	mSlidingAnimationSprites[9]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[9]->setSpriteWidth((unsigned int)1079 - 979);
	mSlidingAnimationSprites[9]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[10]->setSpriteX((unsigned int)1087);
	mSlidingAnimationSprites[10]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[10]->setSpriteWidth((unsigned int)1187 - 1087);
	mSlidingAnimationSprites[10]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[11]->setSpriteX((unsigned int)1195);
	mSlidingAnimationSprites[11]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[11]->setSpriteWidth((unsigned int)1295 - 1195);
	mSlidingAnimationSprites[11]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[12]->setSpriteX((unsigned int)1303);
	mSlidingAnimationSprites[12]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[12]->setSpriteWidth((unsigned int)1403 - 1303);
	mSlidingAnimationSprites[12]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[13]->setSpriteX((unsigned int)1411);
	mSlidingAnimationSprites[13]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[13]->setSpriteWidth((unsigned int)1511 - 1411);
	mSlidingAnimationSprites[13]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[14]->setSpriteX((unsigned int)1519);
	mSlidingAnimationSprites[14]->setSpriteY((unsigned int)59);
	mSlidingAnimationSprites[14]->setSpriteWidth((unsigned int)1619 - 1519);
	mSlidingAnimationSprites[14]->setSpriteHeight((unsigned int)139 - 59);

	mSlidingAnimationSprites[15]->setSpriteX((unsigned int)1640);
	mSlidingAnimationSprites[15]->setSpriteY((unsigned int)40);
	mSlidingAnimationSprites[15]->setSpriteWidth((unsigned int)1727 - 1640);
	mSlidingAnimationSprites[15]->setSpriteHeight((unsigned int)139 - 40);

	mSlidingAnimationSprites[16]->setSpriteX((unsigned int)1748);
	mSlidingAnimationSprites[16]->setSpriteY((unsigned int)40);
	mSlidingAnimationSprites[16]->setSpriteWidth((unsigned int)1853 - 1748);
	mSlidingAnimationSprites[16]->setSpriteHeight((unsigned int)139 - 40);

	mSlidingAnimationSprites[17]->setSpriteX((unsigned int)1856);
	mSlidingAnimationSprites[17]->setSpriteY((unsigned int)40);
	mSlidingAnimationSprites[17]->setSpriteWidth((unsigned int)1943 - 1856);
	mSlidingAnimationSprites[17]->setSpriteHeight((unsigned int)139 - 40);

	mSlidingAnimationSprites[18]->setSpriteX((unsigned int)1964);
	mSlidingAnimationSprites[18]->setSpriteY((unsigned int)40);
	mSlidingAnimationSprites[18]->setSpriteWidth((unsigned int)2051 - 1964);
	mSlidingAnimationSprites[18]->setSpriteHeight((unsigned int)139 - 40);

	mSlidingAnimationSprites[19]->setSpriteX((unsigned int)2072);
	mSlidingAnimationSprites[19]->setSpriteY((unsigned int)40);
	mSlidingAnimationSprites[19]->setSpriteWidth((unsigned int)2159 - 2072);
	mSlidingAnimationSprites[19]->setSpriteHeight((unsigned int)139 - 40);

	mSlidingAnimationSprites[20]->setSpriteX((unsigned int)2180);
	mSlidingAnimationSprites[20]->setSpriteY((unsigned int)40);
	mSlidingAnimationSprites[20]->setSpriteWidth((unsigned int)2267 - 2180);
	mSlidingAnimationSprites[20]->setSpriteHeight((unsigned int)139 - 40);
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

	mDyingAnimationSprites[0]->setSpriteX((unsigned int)4);
	mDyingAnimationSprites[0]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[0]->setSpriteWidth((unsigned int)73 - 4);
	mDyingAnimationSprites[0]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[1]->setSpriteX((unsigned int)112);
	mDyingAnimationSprites[1]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[1]->setSpriteWidth((unsigned int)181 - 112);
	mDyingAnimationSprites[1]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[2]->setSpriteX((unsigned int)220);
	mDyingAnimationSprites[2]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[2]->setSpriteWidth((unsigned int)289 - 220);
	mDyingAnimationSprites[2]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[3]->setSpriteX((unsigned int)328);
	mDyingAnimationSprites[3]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[3]->setSpriteWidth((unsigned int)397 - 328);
	mDyingAnimationSprites[3]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[4]->setSpriteX((unsigned int)436);
	mDyingAnimationSprites[4]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[4]->setSpriteWidth((unsigned int)505 - 436);
	mDyingAnimationSprites[4]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[5]->setSpriteX((unsigned int)544);
	mDyingAnimationSprites[5]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[5]->setSpriteWidth((unsigned int)613 - 544);
	mDyingAnimationSprites[5]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[6]->setSpriteX((unsigned int)652);
	mDyingAnimationSprites[6]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[6]->setSpriteWidth((unsigned int)721 - 652);
	mDyingAnimationSprites[6]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[7]->setSpriteX((unsigned int)760);
	mDyingAnimationSprites[7]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[7]->setSpriteWidth((unsigned int)829 - 760);
	mDyingAnimationSprites[7]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[8]->setSpriteX((unsigned int)868);
	mDyingAnimationSprites[8]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[8]->setSpriteWidth((unsigned int)937 - 868);
	mDyingAnimationSprites[8]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[9]->setSpriteX((unsigned int)976);
	mDyingAnimationSprites[9]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[9]->setSpriteWidth((unsigned int)1045 - 976);
	mDyingAnimationSprites[9]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[10]->setSpriteX((unsigned int)1084);
	mDyingAnimationSprites[10]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[10]->setSpriteWidth((unsigned int)1153 - 1084);
	mDyingAnimationSprites[10]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[11]->setSpriteX((unsigned int)1192);
	mDyingAnimationSprites[11]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[11]->setSpriteWidth((unsigned int)1261 - 1192);
	mDyingAnimationSprites[11]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[12]->setSpriteX((unsigned int)1300);
	mDyingAnimationSprites[12]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[12]->setSpriteWidth((unsigned int)1369 - 1300);
	mDyingAnimationSprites[12]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[13]->setSpriteX((unsigned int)1408);
	mDyingAnimationSprites[13]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[13]->setSpriteWidth((unsigned int)1477 - 1408);
	mDyingAnimationSprites[13]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[14]->setSpriteX((unsigned int)1516);
	mDyingAnimationSprites[14]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[14]->setSpriteWidth((unsigned int)1585 - 1516);
	mDyingAnimationSprites[14]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[15]->setSpriteX((unsigned int)1624);
	mDyingAnimationSprites[15]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[15]->setSpriteWidth((unsigned int)1693 - 1624);
	mDyingAnimationSprites[15]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[16]->setSpriteX((unsigned int)1732);
	mDyingAnimationSprites[16]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[16]->setSpriteWidth((unsigned int)1801 - 1732);
	mDyingAnimationSprites[16]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[17]->setSpriteX((unsigned int)1840);
	mDyingAnimationSprites[17]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[17]->setSpriteWidth((unsigned int)1909 - 1840);
	mDyingAnimationSprites[17]->setSpriteHeight((unsigned int)138 - 47);

	mDyingAnimationSprites[18]->setSpriteX((unsigned int)1948);
	mDyingAnimationSprites[18]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[18]->setSpriteWidth((unsigned int)2017 - 1948);
	mDyingAnimationSprites[18]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[19]->setSpriteX((unsigned int)2056);
	mDyingAnimationSprites[19]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[19]->setSpriteWidth((unsigned int)2152 - 2056);
	mDyingAnimationSprites[19]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[20]->setSpriteX((unsigned int)2164);
	mDyingAnimationSprites[20]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[20]->setSpriteWidth((unsigned int)2233 - 2164);
	mDyingAnimationSprites[20]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[21]->setSpriteX((unsigned int)2272);
	mDyingAnimationSprites[21]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[21]->setSpriteWidth((unsigned int)2341 - 2272);
	mDyingAnimationSprites[21]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[22]->setSpriteX((unsigned int)2380);
	mDyingAnimationSprites[22]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[22]->setSpriteWidth((unsigned int)2449 - 2380);
	mDyingAnimationSprites[22]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[23]->setSpriteX((unsigned int)2488);
	mDyingAnimationSprites[23]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[23]->setSpriteWidth((unsigned int)2557 - 2488);
	mDyingAnimationSprites[23]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[24]->setSpriteX((unsigned int)2596);
	mDyingAnimationSprites[24]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[24]->setSpriteWidth((unsigned int)2665 - 2596);
	mDyingAnimationSprites[24]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[25]->setSpriteX((unsigned int)2704);
	mDyingAnimationSprites[25]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[25]->setSpriteWidth((unsigned int)2773 - 2704);
	mDyingAnimationSprites[25]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[26]->setSpriteX((unsigned int)2812);
	mDyingAnimationSprites[26]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[26]->setSpriteWidth((unsigned int)2881 - 2812);
	mDyingAnimationSprites[26]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[27]->setSpriteX((unsigned int)2920);
	mDyingAnimationSprites[27]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[27]->setSpriteWidth((unsigned int)2989 - 2920);
	mDyingAnimationSprites[27]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[28]->setSpriteX((unsigned int)3028);
	mDyingAnimationSprites[28]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[28]->setSpriteWidth((unsigned int)3097 - 3028);
	mDyingAnimationSprites[28]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[29]->setSpriteX((unsigned int)3136);
	mDyingAnimationSprites[29]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[29]->setSpriteWidth((unsigned int)3205 - 3136);
	mDyingAnimationSprites[29]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[30]->setSpriteX((unsigned int)3244);
	mDyingAnimationSprites[30]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[30]->setSpriteWidth((unsigned int)3313 - 3244);
	mDyingAnimationSprites[30]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[31]->setSpriteX((unsigned int)3352);
	mDyingAnimationSprites[31]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[31]->setSpriteWidth((unsigned int)3421 - 3352);
	mDyingAnimationSprites[31]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[32]->setSpriteX((unsigned int)3460);
	mDyingAnimationSprites[32]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[32]->setSpriteWidth((unsigned int)3529 - 3460);
	mDyingAnimationSprites[32]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[33]->setSpriteX((unsigned int)3568);
	mDyingAnimationSprites[33]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[33]->setSpriteWidth((unsigned int)3637 - 3568);
	mDyingAnimationSprites[33]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[34]->setSpriteX((unsigned int)3676);
	mDyingAnimationSprites[34]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[34]->setSpriteWidth((unsigned int)3745 - 3676);
	mDyingAnimationSprites[34]->setSpriteHeight((unsigned int)139 - 47);

	mDyingAnimationSprites[35]->setSpriteX((unsigned int)3784);
	mDyingAnimationSprites[35]->setSpriteY((unsigned int)47);
	mDyingAnimationSprites[35]->setSpriteWidth((unsigned int)3853 - 3784);
	mDyingAnimationSprites[35]->setSpriteHeight((unsigned int)139 - 47);
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
	} else {
		//mAnimationController is not null
	}

	//The subsequent loops will Free the corresponding sprites
	//they run all the existing sprites on their variables
	for (auto eachSprite : mWalkingAnimationSprites) {
		//ASSERT(eachSprite == nullptr, "Walking sprite error");
		if (eachSprite != nullptr) {
			eachSprite = nullptr;
		} else {
			//null pointer
		}
	}

	for (auto eachSprite : mJumpingAnimationSprites) {
		//ASSERT(eachSprite == nullptr, "Jumping sprite error");
		if (eachSprite != nullptr) {
			eachSprite = nullptr;
		} else {
			//null pointer
		}
	}

	for (auto eachSprite : mSlidingAnimationSprites) {
		//ASSERT(eachSprite == nullptr, "Sliding sprite error");
		if (eachSprite != nullptr) {
			eachSprite = nullptr;
		} else {
			//null pointer
		}
	}

	for (auto eachSprite : mDyingAnimationSprites) {
		//ASSERT(eachSprite == nullptr, "Dying sprite error");
		if (eachSprite != nullptr) {
			eachSprite = nullptr;
		} else {
			//null pointer
		}

		//The subsequent 'ifs' checks if the variable pointer is pointing to null
		//ASSERT(mWalking == nullptr, "Walking component pointer error");
		if (mWalking != nullptr) {
			delete(mWalking);
			mWalking = nullptr;
		} else {
			//null pointer
		}

		//ASSERT(mJumping == nullptr, "Jumping component pointer error");
		if (mJumping != nullptr) {
			delete(mJumping);
			mJumping = nullptr;
		} else {
			//null pointer
		}

		//ASSERT(mSliding == nullptr, "Sliding component pointer error");
		if (mSliding != nullptr) {
			delete(mSliding);
			mSliding = nullptr;
		} else {
			//null pointer
		}

		//ASSERT(mDying == nullptr, "Dying component pointer error");
		if (mDying != nullptr) {
			delete(mDying);
			mDying = nullptr;
		} else {
			//null pointer
		}

		//ASSERT(mLosing == nullptr, "Losing component pointer error");
		if (mLosing != nullptr) {
			delete(mLosing);
			mLosing = nullptr;
		} else {
			//null pointer
		}

		//ASSERT(mPlayerCode == nullptr, "PlayerCode component pointer error");
		if (mPlayerCode != nullptr) {
			mPlayerCode->shutdown();
			delete(mPlayerCode);
			mPlayerCode = nullptr;
		} else {
			//null pointer
		}
	}
}
