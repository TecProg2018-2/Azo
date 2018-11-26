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
 * @brief Destructor class for Obstacle.
 *
 * Used for shutting down each one of the Obstacle's attributes so as to free
 * memory when closing the game.
 */
void Obstacle::shutdown() {
	// Each block in mBlockList must be shutdown before Obstacle can also be shut down.
	DEBUG("Calling Obstacle shutdown");
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

	// Clear any animations remaining before shutdding down Obstacle.
	if (mTurningAnimationSprites.size() > 0) {
		DEBUG("Clearing mTurningAnimationSprites that remained");
		for (auto eachAnimation : mTurningAnimationSprites) {
			if (eachAnimation != NULL) {
				delete(eachAnimation);
				eachAnimation = NULL;
			} else {
				//Nothing to do, the pointer is already null
			}
		}
	} else {
		//Nothing to do, there is no mTurningAnimationSprites
	}

	// Clear all remaining images.
	if (mObstacleImage != NULL) {
		DEBUG("Clearing mObstacleImage");
		delete(mObstacleImage);
		mObstacleImage = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}

	// Clear all remaining audio.
	if (mAudioController != NULL) {
		DEBUG("Clearing mAudioController");
		mAudioController->shutdown();
		delete(mAudioController);
		mAudioController = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}

	// Reset mCollected value.
	if (mCollected != NULL) {
		DEBUG("Reseting mCollected");
		mCollected = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}

	// Reset mTurning value.
	if (mTurning != NULL) {
		DEBUG("Reseting mTurning");
		delete(mTurning);
		mTurning = NULL;
	} else {
		//Nothing to do, the pointer is already null
	}

	// Shutdown mMachinePart code.
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
 * @brief Constructor class for Obstacle.
 *
 * Used to initialize Obstacle class variables.
 * @param name Obstacle name.
 * @param positionRelativeToParent Pair of doubles relative to position(range > 0).
 * @param obstacleType Type of obstacle according to enum class ObstacleType from obstacle.hpp .
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
			generateTurningAnimation();
			mTurning = new engine::Animation(*this, "sprites/machine_part.png", 1200.0f, mTurningAnimationSprites, 0.0, 23.0, true, 1.0);
			this->addComponent(*mTurning);

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
			mBlockList.push_back(new InvisibleBlock("block_1",
													blockPosition,
													std::make_pair(21000.0, 100.0)));
			errorCode = FunctionStatusObstacle::SUCCESS;
			break;

		case ObstacleType::WESTERN_CAR:
			blockPosition.first += 69.0;
			blockPosition.second += 20.0;
			mBlockList.push_back(new InvisibleBlock("block_2",
													blockPosition,
													std::make_pair(109.0, 143.0)));
			errorCode = FunctionStatusObstacle::SUCCESS;
			break;

		case ObstacleType::WESTERN_BOX:
			blockPosition.first += 58.0;
			blockPosition.second += 6.0;
			mBlockList.push_back(new InvisibleBlock("block_3",
													blockPosition,
													std::make_pair(63.0, 73.0)));
			errorCode = FunctionStatusObstacle::SUCCESS;
			break;

		case ObstacleType::WESTERN_RAISED_BOX:
			blockPosition.first += 35.0;
			blockPosition.second += 6.0;
			mBlockList.push_back(new InvisibleBlock("block_4",
													blockPosition,
													std::make_pair(50.0, 68.0)));
			errorCode = FunctionStatusObstacle::SUCCESS;
			break;

		case ObstacleType::WESTERN_ROCK:
			blockPosition.first += 80.0;
			blockPosition.second += 12.0;
			mBlockList.push_back(new InvisibleBlock("block_5",
													blockPosition,
													std::make_pair(4.0, 100.0)));
			errorCode = FunctionStatusObstacle::SUCCESS;
			break;

		case ObstacleType::WESTERN_SPIKE:
			blockPosition.first += 19.0;
			blockPosition.second += 23.0;
			mBlockList.push_back(new InvisibleBlock("block_6",
													blockPosition,
													std::make_pair(210.0, 92.0)));
			errorCode = FunctionStatusObstacle::SUCCESS;
			break;

		case ObstacleType::WESTERN_POST:
			blockPosition.first += 48.0;
			blockPosition.second += 32.0;
			mBlockList.push_back(new InvisibleBlock("block_7",
													blockPosition,
													std::make_pair(23.0, 106.0)));
		  errorCode = FunctionStatusObstacle::SUCCESS;
			break;

		default:
			//Nothing to do, there is no component with this type
			errorCode = FunctionStatusObstacle::WRONGTYPE;
			errorLog("Obstacle::createBlocks");
			break;
	}

}


/**
 * @brief Method for setting up animated obstacles.
 *
 * Used for generating animations for obstacles that have animated sprites.
 */
void Obstacle::generateTurningAnimation() {
	DEBUG("Generating animations of animated obstacles");
	// Default animation speed is 24 frames per second.
	const int NUMBER_SPRITES_TURNING_ANIMATION = 24;
	// Fill sprites animation up to the NUMBER_SPRITES_TURNING_ANIMATION const.
	for (int i = 0; i < NUMBER_SPRITES_TURNING_ANIMATION; i++) {
		mTurningAnimationSprites.push_back(new engine::Sprite());
	}

	/*
      Set the animation sprite coordinates (x, y)
      and its Width and Height based on its coordinates (width - spriteX) and (Height - spriteY).
  	*/

	DEBUG("Setting loaded animated Sprite 0");
	mTurningAnimationSprites[0]->setSpriteX((unsigned int)13);
	mTurningAnimationSprites[0]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[0]->setSpriteWidth((unsigned int)(49 - 13));
	mTurningAnimationSprites[0]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 1");
	mTurningAnimationSprites[1]->setSpriteX((unsigned int)50);
	mTurningAnimationSprites[1]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[1]->setSpriteWidth((unsigned int)(86 - 50));
	mTurningAnimationSprites[1]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 2");
	mTurningAnimationSprites[2]->setSpriteX((unsigned int)87);
	mTurningAnimationSprites[2]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[2]->setSpriteWidth((unsigned int)(123 - 87));
	mTurningAnimationSprites[2]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 3");
	mTurningAnimationSprites[3]->setSpriteX((unsigned int)124);
	mTurningAnimationSprites[3]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[3]->setSpriteWidth((unsigned int)(160 - 124));
	mTurningAnimationSprites[3]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 4");
	mTurningAnimationSprites[4]->setSpriteX((unsigned int)161);
	mTurningAnimationSprites[4]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[4]->setSpriteWidth((unsigned int)(197 - 161));
	mTurningAnimationSprites[4]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 5");
	mTurningAnimationSprites[5]->setSpriteX((unsigned int)198);
	mTurningAnimationSprites[5]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[5]->setSpriteWidth((unsigned int)(234 - 198));
	mTurningAnimationSprites[5]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 6");
	mTurningAnimationSprites[6]->setSpriteX((unsigned int)240);
	mTurningAnimationSprites[6]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[6]->setSpriteWidth((unsigned int)(271 - 240));
	mTurningAnimationSprites[6]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 7");
	mTurningAnimationSprites[7]->setSpriteX((unsigned int)277);
	mTurningAnimationSprites[7]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[7]->setSpriteWidth((unsigned int)(308 - 277));
	mTurningAnimationSprites[7]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 8");
	mTurningAnimationSprites[8]->setSpriteX((unsigned int)314);
	mTurningAnimationSprites[8]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[8]->setSpriteWidth((unsigned int)(345 - 314));
	mTurningAnimationSprites[8]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 9");
	mTurningAnimationSprites[9]->setSpriteX((unsigned int)351);
	mTurningAnimationSprites[9]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[9]->setSpriteWidth((unsigned int)(382 - 351));
	mTurningAnimationSprites[9]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 10");
	mTurningAnimationSprites[10]->setSpriteX((unsigned int)388);
	mTurningAnimationSprites[10]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[10]->setSpriteWidth((unsigned int)(419 - 388));
	mTurningAnimationSprites[10]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 11");
	mTurningAnimationSprites[11]->setSpriteX((unsigned int)425);
	mTurningAnimationSprites[11]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[11]->setSpriteWidth((unsigned int)(456 - 425));
	mTurningAnimationSprites[11]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 12");
	mTurningAnimationSprites[12]->setSpriteX((unsigned int)461);
	mTurningAnimationSprites[12]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[12]->setSpriteWidth((unsigned int)(497 - 461));
	mTurningAnimationSprites[12]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 13");
	mTurningAnimationSprites[13]->setSpriteX((unsigned int)461);
	mTurningAnimationSprites[13]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[13]->setSpriteWidth((unsigned int)(497 - 461));
	mTurningAnimationSprites[13]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 14");
	mTurningAnimationSprites[14]->setSpriteX((unsigned int)461);
	mTurningAnimationSprites[14]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[14]->setSpriteWidth((unsigned int)(497 - 461));
	mTurningAnimationSprites[14]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 15");
	mTurningAnimationSprites[15]->setSpriteX((unsigned int)461);
	mTurningAnimationSprites[15]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[15]->setSpriteWidth((unsigned int)(497 - 461));
	mTurningAnimationSprites[15]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 16");
	mTurningAnimationSprites[16]->setSpriteX((unsigned int)461);
	mTurningAnimationSprites[16]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[16]->setSpriteWidth((unsigned int)(497 - 461));
	mTurningAnimationSprites[16]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 17");
	mTurningAnimationSprites[17]->setSpriteX((unsigned int)461);
	mTurningAnimationSprites[17]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[17]->setSpriteWidth((unsigned int)(497 - 461));
	mTurningAnimationSprites[17]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 18");
	mTurningAnimationSprites[18]->setSpriteX((unsigned int)689);
	mTurningAnimationSprites[18]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[18]->setSpriteWidth((unsigned int)(720 - 689));
	mTurningAnimationSprites[18]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 19");
	mTurningAnimationSprites[19]->setSpriteX((unsigned int)726);
	mTurningAnimationSprites[19]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[19]->setSpriteWidth((unsigned int)(757 - 726));
	mTurningAnimationSprites[19]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 20");
	mTurningAnimationSprites[20]->setSpriteX((unsigned int)763);
	mTurningAnimationSprites[20]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[20]->setSpriteWidth((unsigned int)(794 - 763));
	mTurningAnimationSprites[20]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 21");
	mTurningAnimationSprites[21]->setSpriteX((unsigned int)800);
	mTurningAnimationSprites[21]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[21]->setSpriteWidth((unsigned int)(831 - 800));
	mTurningAnimationSprites[21]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 22");
	mTurningAnimationSprites[22]->setSpriteX((unsigned int)837);
	mTurningAnimationSprites[22]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[22]->setSpriteWidth((unsigned int)(868 - 837));
	mTurningAnimationSprites[22]->setSpriteHeight((unsigned int)(47 - 11));

	DEBUG("Setting loaded animated Sprite 23");
	mTurningAnimationSprites[23]->setSpriteX((unsigned int)874);
	mTurningAnimationSprites[23]->setSpriteY((unsigned int)11);
	mTurningAnimationSprites[23]->setSpriteWidth((unsigned int)(905 - 874));
	mTurningAnimationSprites[23]->setSpriteHeight((unsigned int)(47 - 11));

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
