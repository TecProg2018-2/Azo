/**
* @file obstacle.cpp
* @brief Purpose: Contains the Obstacle class methods.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "obstacle.hpp"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace Azo;

/**
* @brief Basic contructor for Obstacle.
*
* Default basic constructor for Obstacle.
*/
Obstacle::Obstacle() {}

/**
* @brief Virtual constructor for Obstacle.
*
* Default virtual constructor for Obstacle.
*/
Obstacle::~Obstacle(){}

/**
* @brief Constructor class for Obstacle.
*
* Used to initialize Obstacle class variables.
* @param name Obstacle name.
* @param positionRelativeToParent Pair of doubles relative to position(range > 0).
* @param obstacleType Type of obstacle according to enum class ObstacleType from obstacle.hpp.
*/
Obstacle::Obstacle(std::string name, std::pair<double, double> positionRelativeToParent, ObstacleType obstacleType) {
	DEBUG("Initializing Obstacle variables");
	// Initializing Obstacle variables.
	mName = name;
	ASSERT(mName != "", "name can't be empty.");
	mPositionRelativeToParent = positionRelativeToParent;
	mCurrentPosition = mPositionRelativeToParent;
	mObstacleType = obstacleType;

	DEBUG("Calling createComponents");
	createComponents();
}

/**
* @brief Destructor class for Obstacle.
*
* Used for shutting down each one of the Obstacle's attributes so as to free
* memory when closing the game.
*/
void Obstacle::shutdown() {
	DEBUG("Calling Obstacle shutdown");

	clearEachBlock();
	clearAnimations();
	clearImages();
	clearAudio();
	resetCollectedValue();
	resetSpinningValue();
	shutdownMachinePartCode();
}

/**
* @brief Method to clear eachBlock from mBlockList.
*
* Used to clear eachBlock from mBlockList.
* All of them must be shutted down before Obstacle can also be shutted down.
*/
void Obstacle::clearEachBlock(){
	for (auto eachBlock : mBlockList) {
		DEBUG("Deleting eachBlock from mBlockList");
		if (eachBlock != NULL) {
			eachBlock->shutdown();
			delete(eachBlock);
			eachBlock = NULL;
		} else {
			//Nothing to do, the pointer is already null
		}
	}
}

/**
* @brief Method to clear animations.
*
* Used to clear any animations remaining before shutting down Obstacle.
*/
void Obstacle::clearAnimations(){
	if (mSpinningAnimationSprites.size() > 0) {
		DEBUG("Clearing mSpinningAnimationSprites that remained");
		for (auto eachAnimation : mSpinningAnimationSprites) {
			if (eachAnimation != NULL) {
				delete(eachAnimation);
				eachAnimation = NULL;
			} else {
				//Nothing to do, the pointer is already null
			}
		}
	} else {
		//Nothing to do, there is no mSpinningAnimationSprites
	}
}

/**
* @brief Method to clear images.
*
* Used to clear all remaining images before shutting down Obstacle.
*/
void Obstacle::clearImages(){
	if (mObstacleImage != NULL) {
		DEBUG("Clearing mObstacleImage");
		delete(mObstacleImage);
		mObstacleImage = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}
}

/**
* @brief Method to clear audio.
*
* Used to clear all remaining audio before shutting down Obstacle.
*/
void Obstacle::clearAudio(){
	if (mAudioController != NULL) {
		DEBUG("Clearing mAudioController");
		mAudioController->shutdown();
		delete(mAudioController);
		mAudioController = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}
}

/**
* @brief Method to reset collected value.
*
* Used to reset mCollected value before shutting down Obstacle.
*/
void Obstacle::resetCollectedValue(){
	if (mCollected != NULL) {
		DEBUG("Reseting mCollected");
		mCollected = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}
}

/**
* @brief Method to reset spinning value.
*
* Used to reset mSpinning value before shutting down Obstacle.
*/
void Obstacle::resetSpinningValue(){
	if (mSpinning != NULL) {
		DEBUG("Reseting mSpinning");
		delete(mSpinning);
		mSpinning = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}
}

/**
* @brief Method to shutdown MachinePart code.
*
* Used to shutdown MachinePartCode class.
*/
void Obstacle::shutdownMachinePartCode(){
	if (mMachinePartCode != NULL) {
		DEBUG("Shutting down mMachinePartCode");
		mMachinePartCode->shutdown();
		delete(mMachinePartCode);
		mMachinePartCode = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}
}

/**
* @brief Method for creating components to Obstacle.
*
* Used for creating components according to its type (AudioComponent or ImageComponent).
*/
void Obstacle::createComponents() {
	DEBUG("Creating obstacle components.");
	// If and else if blocks for each ObstacleType and its respective initialization.

	switch (mObstacleType) {
		case ObstacleType::WESTERN_CAR:
		DEBUG("obstacle is a WESTERN CAR!");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1.0);
		ASSERT(mObstacleImage != NULL, "ObstacleType::WESTERN_CAR, mObstacleImage can't be NULL.");
		this->addComponent(*mObstacleImage);
		createBlocks();
		break;

		case ObstacleType::WESTERN_BOX:
		DEBUG("obstacle is a WESTERN BOX!");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/box.png", 1.0);
		ASSERT(mObstacleImage != NULL, "ObstacleType::WESTERN_BOX, mObstacleImage can't be NULL.");
		this->addComponent(*mObstacleImage);
		createBlocks();
		errorCode = FunctionStatusObstacle::SUCCESS;
		break;

		case ObstacleType::WESTERN_RAISED_BOX:
		DEBUG("obstacle is a WESTERN RAISED BOX!");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/raised_box.png", 1.0);
		ASSERT(mObstacleImage != NULL, "ObstacleType::WESTERN_RAISED_BOX, mObstacleImage can't be NULL.");
		this->addComponent(*mObstacleImage);
		createBlocks();
		errorCode = FunctionStatusObstacle::SUCCESS;
		break;

		case ObstacleType::WESTERN_ROCK:
		DEBUG("obstacle is a WESTERN ROCK");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/rock.png", 1.0);
		ASSERT(mObstacleImage != NULL, "ObstacleType::WESTERN_ROCK, mObstacleImage can't be NULL.");
		this->addComponent(*mObstacleImage);
		createBlocks();
		errorCode = FunctionStatusObstacle::SUCCESS;
		break;

		case ObstacleType::MACHINE_PART:
		DEBUG("obstacle is a MACHINE PART");
		mMachinePartState = MachinePartState::NON_COLLECTED;
		generateSpinAnimation();
		mSpinning = new engine::Animation(*this, "sprites/machine_part.png", 1200.0f, mSpinningAnimationSprites, 0.0, 23.0, true, 1.0);
		this->addComponent(*mSpinning);

		mAudioController = new engine::AudioController();
		ASSERT(mAudioController != NULL, "engine::AudioController, AudioController can't be NULL.");
		mCollected = new engine::AudioComponent(*this, "audios/coleta.ogg", false, false);
		ASSERT(mCollected != NULL, "engine::AudioComponent, AudioComponent can't be NULL.");
		mAudioController->addAudio("coleta", *mCollected);
		this->addComponent(*mAudioController);

		mMachinePartCode = new MachinePartCode(this);
		ASSERT(mMachinePartCode != NULL, "MachinePartCode, mMachinePartCode can't return NULL.");
		this->addComponent(*mMachinePartCode);
		errorCode = FunctionStatusObstacle::SUCCESS;
		break;

		case ObstacleType::WESTERN_SPIKE:
		DEBUG("obstacle is a WESTERN SPIKE");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/Espinhos_rose.png", 1.0);
		ASSERT(mObstacleImage != NULL, "engine::ImageComponent, mObstacleImage can't be NULL.");
		this->addComponent(*mObstacleImage);
		createBlocks();
		errorCode = FunctionStatusObstacle::SUCCESS;
		break;

		case ObstacleType::WESTERN_POST:
		DEBUG("obstacle is a WESTERN POST");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/obstaculoDescer2.png", 1.0);
		ASSERT(mObstacleImage != NULL, "engine::ImageComponent, mObstacleImage can't be NULL.");
		this->addComponent(*mObstacleImage);
		createBlocks();
		errorCode = FunctionStatusObstacle::SUCCESS;
		break;

		case ObstacleType::GROUND:
		DEBUG("obstacle is ground type");
		createBlocks();
		errorCode = FunctionStatusObstacle::SUCCESS;
		break;

		default:
		//Nothing to do, there is no component with this type
		errorCode = FunctionStatusObstacle::WRONGTYPE;
		errorLog("Obstacle::createComponents");
		break;
	}
}

/**
* @brief Method for creating blocks.
*
* Used to create invisible objects that compose the Obstacle based on the type
* of the object.
* Note that the name of the InvisibleBlock is only for internal use.
*/
void Obstacle::createBlocks() {
	/*
	We initialize the block' position as the position relative to parent of the obstacle.
	This way we can position things inside the obstacle just by adding values to the position.
	*/
	std::pair<double, double> blockPosition = mPositionRelativeToParent;

	// If and else if blocks for setting obstacle position based on its type ObstacleType.
	switch (mObstacleType) {
		DEBUG("Setting obstacle position");

		case ObstacleType::GROUND:
		setObstaclePosition("block_1", blockPosition, 21000.0, 100.0);
		break;

		case ObstacleType::WESTERN_CAR:
		blockPosition.first += 69.0;
		blockPosition.second += 20.0;
		setObstaclePosition("block_2", blockPosition, 109.0, 143.0);
		break;

		case ObstacleType::WESTERN_BOX:
		blockPosition.first += 58.0;
		blockPosition.second += 6.0;
		setObstaclePosition("block_3", blockPosition, 63.0, 73.0);
		break;

		case ObstacleType::WESTERN_RAISED_BOX:
		blockPosition.first += 35.0;
		blockPosition.second += 6.0;
		setObstaclePosition("block_4", blockPosition, 50.0, 68.0);
		break;

		case ObstacleType::WESTERN_ROCK:
		blockPosition.first += 80.0;
		blockPosition.second += 12.0;
		setObstaclePosition("block_5", blockPosition, 4.0, 100.0);
		break;

		case ObstacleType::WESTERN_SPIKE:
		blockPosition.first += 19.0;
		blockPosition.second += 23.0;
		setObstaclePosition("block_6", blockPosition, 210.0, 92.0);
		break;

		case ObstacleType::WESTERN_POST:
		blockPosition.first += 48.0;
		blockPosition.second += 32.0;
		setObstaclePosition("block_7", blockPosition, 23.0, 106.0);
		break;

		default:
		//Nothing to do, there is no component with this type
		errorCode = FunctionStatusObstacle::WRONGTYPE;
		errorLog("Obstacle::createBlocks");
		break;
	}
}

/**
* @brief Method for setting obstacle position.
*
* Used for setting obstacle position.
* @param blockName Name of block that will be set.
* @param blockPosition Pair of doubles relative to block position.
* @param pairFirst Number that indicates first number of pair set.
* @param pairSecond Number that indicates second number of pair set.
*/
void Obstacle::setObstaclePosition(
	std::string blockName,
	std::pair<double, double> blockPosition,
	double pairFirst,
	double pairSecond
) {
	mBlockList.push_back(
		new InvisibleBlock(
			blockName,
			blockPosition,
			std::make_pair(pairFirst, pairSecond)
		)
	);
	errorCode = FunctionStatusObstacle::SUCCESS;
}

/**
* @brief Method for loading up sprites to animations.
*
* Used for generating MachinePart spin animation.
*/
void Obstacle::generateSpinAnimation() {
	DEBUG("Generating animations of animated obstacles");

	const int NUMBER_SPRITES_SPIN_ANIMATION = 24; // Default animation speed is 24 frames per second.
	// Fill sprites animation up to the NUMBER_SPRITES_SPIN_ANIMATION const.
	for (int i = 0; i < NUMBER_SPRITES_SPIN_ANIMATION; i++) {
		mSpinningAnimationSprites.push_back(new engine::Sprite());
	}

	// Set the animation sprite coordinates (x, y), its width and height
	setLoadedAnimatedSprite(0, 13);
	setLoadedAnimatedSprite(1, 50);
	setLoadedAnimatedSprite(2, 87);
	setLoadedAnimatedSprite(3, 124);
	setLoadedAnimatedSprite(4, 161);
	setLoadedAnimatedSprite(5, 198);
	setLoadedAnimatedSprite(6, 240);
	setLoadedAnimatedSprite(7, 277);
	setLoadedAnimatedSprite(8, 314);
	setLoadedAnimatedSprite(9, 351);
	setLoadedAnimatedSprite(10, 388);
	setLoadedAnimatedSprite(11, 425);
	setLoadedAnimatedSprite(12, 461);
	setLoadedAnimatedSprite(13, 461);
	setLoadedAnimatedSprite(14, 461);
	setLoadedAnimatedSprite(15, 461);
	setLoadedAnimatedSprite(16, 461);
	setLoadedAnimatedSprite(17, 461);
	setLoadedAnimatedSprite(18, 689);
	setLoadedAnimatedSprite(19, 726);
	setLoadedAnimatedSprite(20, 763);
	setLoadedAnimatedSprite(21, 800);
	setLoadedAnimatedSprite(22, 837);
	setLoadedAnimatedSprite(23, 874);
}

/**
* @brief Method for setting up loaded obstacles' sprites.
*
* Used for setting spin animation sprite coordinates, width and height
* @param spriteNumber Number that indicates index of sprite.
* @param spriteX Number that indicates 'x' coordinate of sprite.
*/
void Obstacle::setLoadedAnimatedSprite(
	unsigned int spriteNumber,
	unsigned int spriteX
) {
	const unsigned int SPRITE_Y = 11;
	const unsigned int SPRITE_WIDTH = 36;
	const unsigned int SPRITE_HEIGHT = 36;

	DEBUG("Setting loaded animated Sprite " << spriteNumber);
	mSpinningAnimationSprites[spriteNumber]->setSpriteX(spriteX);
	mSpinningAnimationSprites[spriteNumber]->setSpriteY(SPRITE_Y);
	mSpinningAnimationSprites[spriteNumber]->setSpriteWidth(SPRITE_WIDTH);
	mSpinningAnimationSprites[spriteNumber]->setSpriteHeight(SPRITE_HEIGHT);
}

void Obstacle::errorLog(std::string file) {
	std::ofstream outfile;
	outfile.open("../errorLog.txt", std::ofstream::out | std::ofstream::app);
	time_t now = time(0);
	std::string dt = ctime(&now);
	std::string message = "===============\n";
	message += "Function: " + file + "\n";
	message += "Date: " + dt + "\n";

	switch(errorCode) {
		case FunctionStatusObstacle::WRONGTYPE:
		message += "wrong type\n";
		break;
		default:
		outfile << "wrong type" << std::endl;
	}
	outfile << message;
	outfile.close();
}
