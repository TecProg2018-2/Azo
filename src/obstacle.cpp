#include "obstacle.hpp"

using namespace Azo;

Obstacle::Obstacle() {}

Obstacle::~Obstacle(){}

void Obstacle::shutDown() {
	for (auto eachBlock : mBlockList) {
		if (eachBlock != NULL) {
			eachBlock->shutDown();
			delete(eachBlock);
			eachBlock = NULL;
		}
	}

	if (mTurningAnimationSprites.size() > 0) {
		for (auto eachAnimation : mTurningAnimationSprites) {
			if (eachAnimation != NULL) {
				delete(eachAnimation);
				eachAnimation = NULL;
			}
		}
	}

	if (mObstacleImage != NULL) {
		delete(mObstacleImage);
		mObstacleImage = NULL;
	}

	if (mAudioController != NULL) {
		mAudioController->shutDown();
		delete(mAudioController);
		mAudioController = NULL;
	}

	if (mCollected != NULL) {
		mCollected = NULL;
	}

	if (mTurning != NULL) {
		delete(mTurning);
		mTurning = NULL;
	}


	if (mMachinePartCode != NULL) {
		mMachinePartCode->shutDown();
		delete(mMachinePartCode);
		mMachinePartCode = NULL;
	}
}


Obstacle::Obstacle(std::string name, std::pair<double, double> positionRelativeToParent, ObstacleType obstacleType) {
	mName = name;
	mPositionRelativeToParent = positionRelativeToParent;
	mCurrentPosition = mPositionRelativeToParent;

	mObstacleType = obstacleType;

	createComponents();
}

// Here we add the imagens/sound to the obstacle, based on its type.
void Obstacle::createComponents() {
	DEBUG("Creating obstacle components.");
	if (mObstacleType == ObstacleType::WESTERN_CAR) {
		DEBUG("obstacle is a WESTERN CAR!");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/broken_caravan.png", 1);
		this->AddComponent(*mObstacleImage);
		createBlocks();

	} else if (mObstacleType == ObstacleType::WESTERN_BOX) {
		DEBUG("obstacle is a WESTERN BOX!");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/box.png", 1);
		this->AddComponent(*mObstacleImage);
		createBlocks();

	} else if (mObstacleType == ObstacleType::WESTERN_RAISED_BOX) {
		DEBUG("obstacle is a WESTERN RAISED BOX!");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/raised_box.png", 1);
		this->AddComponent(*mObstacleImage);
		createBlocks();

	} else if (mObstacleType == ObstacleType::WESTERN_ROCK) {
		DEBUG("obstacle is a WESTERN ROCK");
		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/rock.png", 1);
		this->AddComponent(*mObstacleImage);
		createBlocks();

	} else if (mObstacleType == ObstacleType::MACHINE_PART) {
		DEBUG("obstacle is a MACHINE PART");
		mMachinePartState = MachinePartState::NON_COLLECTED;
		generateTurningAnimation();
		mTurning = new engine::Animation(*this, "sprites/machine_part.png", 1200.0f, mTurningAnimationSprites, 0, 23, true, 1);
		this->AddComponent(*mTurning);

		mAudioController = new engine::AudioController();
		mCollected = new engine::AudioComponent(*this, "audios/coleta.ogg", false, false);
		mAudioController->AddAudio("coleta", *mCollected);
		this->AddComponent(*mAudioController);

		mMachinePartCode = new MachinePartCode(this);
		this->AddComponent(*mMachinePartCode);

	} else if (mObstacleType == ObstacleType::WESTERN_SPIKE) {
		DEBUG("obstacle is a WESTERN SPIKE");

		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/Espinhos_rose.png", 1);
		this->AddComponent(*mObstacleImage);
		createBlocks();
	} else if (mObstacleType == ObstacleType::WESTERN_POST) {
		DEBUG("obstacle is a WESTERN POST");

		mObstacleImage = new engine::ImageComponent(*this, "backgrounds/obstaculoDescer2.png", 1);
		this->AddComponent(*mObstacleImage);
		createBlocks();
	} else if (mObstacleType == ObstacleType::GROUND) {
		createBlocks();
	}
}

// Here we create the invisible objects that make the obstacle.
// The name attribute of the InvisibleBlock isn't needed. It's for testing only.
// It's important to create the blocks based on the type of the object.
void Obstacle::createBlocks() {

	// We initialize the block' position as the position relative to parent of the obstacle.
	// This way we can position things inside the obstacle just by adding values.
	std::pair<double, double> blockPosition = mPositionRelativeToParent;

	//setting obstacle position based on its type

	if (mObstacleType == ObstacleType::GROUND) {
		//	DEBUG("Creating invisible block for the ground.");
		mBlockList.push_back(new InvisibleBlock("block_1", blockPosition, std::make_pair(21000, 100))); //obstacle size
		//	DEBUG("List size: " << mBlockList.size());
	} else if (mObstacleType == ObstacleType::WESTERN_CAR) {

		blockPosition.first += 69;
		blockPosition.second += 20;

		mBlockList.push_back(new InvisibleBlock("block_2", blockPosition, std::make_pair(109, 143)));
	} else if (mObstacleType == ObstacleType::WESTERN_BOX) {
		blockPosition.first += 58;
		blockPosition.second += 6;

		mBlockList.push_back(new InvisibleBlock("block_3", blockPosition, std::make_pair(63, 73)));
	} else if (mObstacleType == ObstacleType::WESTERN_RAISED_BOX) {
		blockPosition.first += 35;
		blockPosition.second += 6;

		mBlockList.push_back(new InvisibleBlock("block_4", blockPosition, std::make_pair(50, 68)));
	} else if (mObstacleType == ObstacleType::WESTERN_ROCK) {
		blockPosition.first += 80;
		blockPosition.second += 12;

		mBlockList.push_back(new InvisibleBlock("block_5", blockPosition, std::make_pair(4, 100)));
	} else if (mObstacleType == ObstacleType::WESTERN_SPIKE) {
		blockPosition.first += 19;
		blockPosition.second += 23;

		mBlockList.push_back(new InvisibleBlock("block_6", blockPosition, std::make_pair(210, 92)));
	} else if (mObstacleType == ObstacleType::WESTERN_POST) {
		blockPosition.first += 48;
		blockPosition.second += 32;

		mBlockList.push_back(new InvisibleBlock("block_7", blockPosition, std::make_pair(23, 106)));
	}

}

void Obstacle::generateTurningAnimation() {
	const int NUMBER_SPRITES_TURNING_ANIMATION = 24;
	for (int i = 0; i < NUMBER_SPRITES_TURNING_ANIMATION; i++) {
		mTurningAnimationSprites.push_back(new engine::Sprite());
	}

	/*
    Set the animation sprite coordinates (x, y)
    and its Width and Height based on its coordinates (width - spriteX) and (Height - spriteY)
  */

	mTurningAnimationSprites[0]->spriteX = 13;
	mTurningAnimationSprites[0]->spriteY = 11;
	mTurningAnimationSprites[0]->spriteWidth = 49 - 13;
	mTurningAnimationSprites[0]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[1]->spriteX = 50;
	mTurningAnimationSprites[1]->spriteY = 11;
	mTurningAnimationSprites[1]->spriteWidth = 86 - 50;
	mTurningAnimationSprites[1]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[2]->spriteX = 87;
	mTurningAnimationSprites[2]->spriteY = 11;
	mTurningAnimationSprites[2]->spriteWidth = 123 - 87;
	mTurningAnimationSprites[2]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[3]->spriteX = 124;
	mTurningAnimationSprites[3]->spriteY = 11;
	mTurningAnimationSprites[3]->spriteWidth = 160 - 124;
	mTurningAnimationSprites[3]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[4]->spriteX = 161;
	mTurningAnimationSprites[4]->spriteY = 11;
	mTurningAnimationSprites[4]->spriteWidth = 197 - 161;
	mTurningAnimationSprites[4]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[5]->spriteX = 198;
	mTurningAnimationSprites[5]->spriteY = 11;
	mTurningAnimationSprites[5]->spriteWidth = 234 - 198;
	mTurningAnimationSprites[5]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[6]->spriteX = 240;
	mTurningAnimationSprites[6]->spriteY = 11;
	mTurningAnimationSprites[6]->spriteWidth = 271 - 240;
	mTurningAnimationSprites[6]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[7]->spriteX = 277;
	mTurningAnimationSprites[7]->spriteY = 11;
	mTurningAnimationSprites[7]->spriteWidth = 308 - 277;
	mTurningAnimationSprites[7]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[8]->spriteX = 314;
	mTurningAnimationSprites[8]->spriteY = 11;
	mTurningAnimationSprites[8]->spriteWidth = 345 - 314;
	mTurningAnimationSprites[8]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[9]->spriteX = 351;
	mTurningAnimationSprites[9]->spriteY = 11;
	mTurningAnimationSprites[9]->spriteWidth = 382 - 351;
	mTurningAnimationSprites[9]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[10]->spriteX = 388;
	mTurningAnimationSprites[10]->spriteY = 11;
	mTurningAnimationSprites[10]->spriteWidth = 419 - 388;
	mTurningAnimationSprites[10]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[11]->spriteX = 425;
	mTurningAnimationSprites[11]->spriteY = 11;
	mTurningAnimationSprites[11]->spriteWidth = 456 - 425;
	mTurningAnimationSprites[11]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[12]->spriteX = 461;
	mTurningAnimationSprites[12]->spriteY = 11;
	mTurningAnimationSprites[12]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[12]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[13]->spriteX = 461;
	mTurningAnimationSprites[13]->spriteY = 11;
	mTurningAnimationSprites[13]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[13]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[14]->spriteX = 461;
	mTurningAnimationSprites[14]->spriteY = 11;
	mTurningAnimationSprites[14]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[14]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[15]->spriteX = 461;
	mTurningAnimationSprites[15]->spriteY = 11;
	mTurningAnimationSprites[15]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[15]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[16]->spriteX = 461;
	mTurningAnimationSprites[16]->spriteY = 11;
	mTurningAnimationSprites[16]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[16]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[17]->spriteX = 461;
	mTurningAnimationSprites[17]->spriteY = 11;
	mTurningAnimationSprites[17]->spriteWidth = 497 - 461;
	mTurningAnimationSprites[17]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[18]->spriteX = 689;
	mTurningAnimationSprites[18]->spriteY = 11;
	mTurningAnimationSprites[18]->spriteWidth = 720 - 689;
	mTurningAnimationSprites[18]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[19]->spriteX = 726;
	mTurningAnimationSprites[19]->spriteY = 11;
	mTurningAnimationSprites[19]->spriteWidth = 757 - 726;
	mTurningAnimationSprites[19]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[20]->spriteX = 763;
	mTurningAnimationSprites[20]->spriteY = 11;
	mTurningAnimationSprites[20]->spriteWidth = 794 - 763;
	mTurningAnimationSprites[20]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[21]->spriteX = 800;
	mTurningAnimationSprites[21]->spriteY = 11;
	mTurningAnimationSprites[21]->spriteWidth = 831 - 800;
	mTurningAnimationSprites[21]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[22]->spriteX = 837;
	mTurningAnimationSprites[22]->spriteY = 11;
	mTurningAnimationSprites[22]->spriteWidth = 868 - 837;
	mTurningAnimationSprites[22]->spriteHeight = 47 - 11;

	mTurningAnimationSprites[23]->spriteX = 874;
	mTurningAnimationSprites[23]->spriteY = 11;
	mTurningAnimationSprites[23]->spriteWidth = 905 - 874;
	mTurningAnimationSprites[23]->spriteHeight = 47 - 11;

}
