#include "level_one_code.hpp"

using namespace Azo;

LevelOneCode::LevelOneCode(engine::GameObject &gameObject){
	this->gameObject = &gameObject;
	getParents();
	findAudioController();
}

void LevelOneCode::shutDown() {
	for (auto Obstacle : mObstacleList) {
		Obstacle = nullptr;
	}

	mAudioController = nullptr;

	mPlayer = nullptr;
}

void LevelOneCode::findAudioController() {
	mAudioController = (gameObject->getAudioController(typeid(engine::AudioController)));
}

void LevelOneCode::getParents() {
	for (auto parent : gameObject->mParentList) {
		if (parent->getClassName() == "Player") {
			mPlayer = dynamic_cast<Player *>(parent);
		} else if (parent->getClassName() == "obstacle") {
			mObstacleList.push_back(dynamic_cast<Obstacle *>(parent));
		} else if (parent->mName == "winning_screen") {
			mWinningScreen = parent;
		} else if (parent->mName == "losing_parts") {
			mLosingParts = parent;
		} else if (parent->mName == "losing_death") {
			mLosingDeath = parent;
		} else if (parent->mName == "arrow") {
			mArrow = parent;
		}

	}
}


void LevelOneCode::updateCode() {
	//DEBUG("Position: " << gameObject->mCurrentPosition.first );
	//DEBUG("Collected parts: " << mPlayer->mCollectedParts);
	const float PLAYER_MAX_POSITION = 300.0f;
	const float GAME_OBJECT_MAX_POSITION = -17600;
	if (mPlayer->mCurrentPosition.first >= PLAYER_MAX_POSITION &&
			gameObject->mCurrentPosition.first > GAME_OBJECT_MAX_POSITION) {
		const float CONTROLLER_POSITION_GAME_OBJECT = 4.0f;
		gameObject->mCurrentPosition.first -= CONTROLLER_POSITION_GAME_OBJECT;
		const float CONTROLLER_POSITION_PLAYER = 299;
		mPlayer->mCurrentPosition.first = CONTROLLER_POSITION_PLAYER;
	} else if (mPlayer->mCurrentPosition.first >= PLAYER_MAX_POSITION) {
		mWaitingTime += engine::Game::instance.GetTimer().GetDeltaTime();
		mPlayer->mSpeed.first = 0;
		mAudioController->stopAudio("tema_level_one");
		mPlayer->mState = PlayerState::END;

		const float MAX_LOSING_WAITING = 10000.0f;
		if (mPlayer->mCollectedParts != mPlayer->M_TOTAL_PARTS && mWaitingTime >= MAX_LOSING_WAITING) {
			mLosingParts->mObjectState = engine::ObjectState::ENABLED;
			changeOption();

			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)) {
				chooseOption();
			}
			const float MAX_WAITING_TIME = 2300.0f;
			if (mWaitingTime >= MAX_WAITING_TIME) {
				mLosingDeath->mObjectState = engine::ObjectState::ENABLED;
				changeOption();
				if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)) {
					chooseOption();
				}
			}

			if (mAudioController->getAudioState("tema_level_one") == engine::AudioState::PLAYING) {
				mAudioController->stopAudio("tema_level_one");
			}
		}
	}
	updateObstaclePosition();

  	if (mPlayer->mState != PlayerState::DIE) {
    	updatePhysics();
  	} else {
	  	mWaitingTime += engine::Game::instance.GetTimer().GetDeltaTime();

	  	if (mWaitingTime >= 2300.0f) {
		  	mLosingDeath->mObjectState = engine::ObjectState::ENABLED;
		  	changeOption();
		  	if(engine::Game::instance.input_manager.KeyDownOnce(engine::Button::ENTER)){
			  	chooseOption();
		  	}
		}

	  	if (mAudioController->getAudioState("tema_level_one") == engine::AudioState::PLAYING){
		  	mAudioController->stopAudio("tema_level_one");
		}
	}
}

void LevelOneCode::changeOption() {
	switch(mCurrentOption) {
		case 1:
				mArrow->mObjectState = engine::ObjectState::ENABLED;
			mArrow->mCurrentPosition = std::make_pair(70, 260);

			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::RIGHT_ARROW)) {
				mCurrentOption = 2; // CurrentOption = 2 means Exit
			}

			break;
		case 2:

			mArrow->mCurrentPosition = std::make_pair(515, 260);

			if (engine::Game::instance.input_manager.KeyDownOnce(engine::Button::LEFT_ARROW)) {
				mCurrentOption = 1; //CurrentOption = 1 means Play
			}

			break;
	}
}

void LevelOneCode::chooseOption() {
	switch(mCurrentOption){
		case 1:
			mAudioController->stopAllAudios();
			engine::Game::instance.ChangeScene("level_one");
			break;
		case 2:
			engine::Game::instance.ChangeScene("menu");
			break;
	}
}



void LevelOneCode::updateObstaclePosition() {
	for (auto eachObstacle : mObstacleList) {
		eachObstacle->mCurrentPosition.first = gameObject->mCurrentPosition.first + eachObstacle->mPositionRelativeToParent.first;
		eachObstacle->mCurrentPosition.second = gameObject->mCurrentPosition.second + eachObstacle->mPositionRelativeToParent.second;

		for (auto block : eachObstacle->mBlockList) {
			block->mCurrentPosition.first = gameObject->mCurrentPosition.first + block->mPositionRelativeToParent.first;
			block->mCurrentPosition.second = gameObject->mCurrentPosition.second + block->mPositionRelativeToParent.second;

			block->mCenter.first = block->mCurrentPosition.first + block->mHalfSize.first;
			block->mCenter.second = block->mCurrentPosition.second + block->mHalfSize.second;

			// DEBUG("BLock current position in X: " << block->mCurrentPosition.first);
			// DEBUG("BLock current position in Y: " << block->mCurrentPosition.second);
			// DEBUG("Block center in X: " << block->mCenter.first);
			// DEBUG("Block center in Y: " << block->mCenter.second);

		}
	}
}

void LevelOneCode::updatePhysics() {
	mPlayer->mCurrentPosition.second += mPlayer->mSpeed.second * engine::Game::instance.GetTimer().GetDeltaTime();
	double groundY = 0.0f;
	const int PLAYER_RELATIVE_POSITION = 15;
	if (mPlayer->mSpeed.second < 0.0f && hasCeiling(&groundY)) {
		mPlayer->mCurrentPosition.second = groundY + PLAYER_RELATIVE_POSITION;
		mPlayer->mAtCeiling = true;
	} else if ((mPlayer->mSpeed.second >= 0.0f || mPlayer->mState == PlayerState::SLIDE) && hasGround(&groundY)) {
		mPlayer->mCurrentPosition.second = groundY - mPlayer->mHalfSize.second - mPlayer->mHalfSize.second + PLAYER_RELATIVE_POSITION;
		mPlayer->mSpeed.second = mPlayer->M_ZERO_VECTOR.second;

		mPlayer->mOnGround = true;

		mPlayer->mCenter.first = mPlayer->mCurrentPosition.first + mPlayer->mHalfSize.first;
		mPlayer->mCenter.second = mPlayer->mCurrentPosition.second + mPlayer->mHalfSize.second;

	} else {
		mPlayer->mOnGround = false;
		mPlayer->mAtCeiling = false;
	}

	//double deltaWalked =  mPlayer->mSpeed.first * engine::Game::instance.GetTimer().GetDeltaTime();
	double deltaWalked =  mPlayer->mSpeed.first;
	// DEBUG("Speed: " << mPlayer->mSpeed.first);
	// DEBUG("Delta walked: " << deltaWalked);

	mPlayer->mCurrentPosition.first += deltaWalked;

	double wallX = 0.0;

	//Limiting player position on canvas.
	const int PLAYER_MAX_POSITION_CANVAS = 300;
	const int  GAME_OBJECT_MAX_POSITION_CANVAS = -7390;
	if (mPlayer->mCurrentPosition.first >= PLAYER_MAX_POSITION_CANVAS &&
			gameObject->mCurrentPosition.first > GAME_OBJECT_MAX_POSITION_CANVAS) {
		mPlayer->mCurrentPosition.first = PLAYER_MAX_POSITION_CANVAS;
	}

	if (mPlayer->mSpeed.first > 0 &&
	   hasWallOnRight(&wallX)) {
		DEBUG("Collision with the wall");
		mPlayer->mCurrentPosition.first = wallX - (mPlayer->mHalfSize.first * 2);
		mPlayer->mPushesLeftWall = true;
		mPlayer->mState = PlayerState::DIE;
	} else {
		mPlayer->mPushesLeftWall = false;
	}

	if (mPlayer->mSpeed.first < 0.0f &&
	   hasWallOnLeft(&wallX)) {
		mPlayer->mState = PlayerState::DIE;
	} else {
		mPlayer->mPushesRightWall = false;
	}
}

bool LevelOneCode::hasGround(double *groundY) {
	std::pair<double, double> playerBottomLeft = mPlayer->calcBottomLeft();
	std::pair<double, double> playerTopRight = mPlayer->calcTopRight();

	double playerTop = playerTopRight.second;
	double playerBottom = playerBottomLeft.second;
	double playerLeft = playerBottomLeft.first;
	double playerRight = playerTopRight.first;

	for (auto eachObstacle : mObstacleList) {

		// If the obstacle is a machine part, we check the collision without invisible blocks (since it has animation).
		// If it collides, we return false (so the position isn't updated) and change the state of the machine part.
		// TODO(Roger): Update the collision methods so they return the colliding object.
		// TODO(Roger): Create states to the machine parts.

		if (eachObstacle->mObstacleType == ObstacleType::MACHINE_PART) {
			std::pair<double, double> blockBottomLeft = eachObstacle->calcBottomLeft();
			std::pair<double, double> blockTopRight = eachObstacle->calcTopRight();

			double blockRight = blockTopRight.first;
			double blockLeft = blockBottomLeft.first;
			double blockTop = blockTopRight.second;

			if (playerLeft <= blockRight &&
			   playerRight >= blockLeft &&
			   playerBottom > blockTop &&
			   playerTop < blockTop) {

				// Collided.
				eachObstacle->mMachinePartState = MachinePartState::COLLECTED;
				mPlayer->mCollectedParts++;
				mObstacleList.remove(eachObstacle);

				return false;
			}
		} else {
			for (auto eachBlock : eachObstacle->mBlockList) {
				std::pair<double, double> blockBottomLeft = eachBlock->calcBottomLeft();
				std::pair<double, double> blockTopRight = eachBlock->calcTopRight();

				double blockRight = blockTopRight.first;
				double blockLeft = blockBottomLeft.first;
				double blockTop = blockTopRight.second;

				// DEBUG("obstacle: " << eachObstacle->mName);
				// DEBUG("Player left: " << playerLeft);
				// DEBUG("Player right: " << playerRight);
				// DEBUG("Player top: " << playerTop);
				// DEBUG("Player bottom: " << playerBottom);
				// DEBUG("Block left: " << blockLeft);
				// DEBUG("Block right: " << blockRight);
				// DEBUG("Block top: " << blockTop);

				if (playerLeft <= blockRight &&
				   playerRight >= blockLeft &&
				   playerBottom > blockTop &&
				   playerTop < blockTop) {

					*groundY = blockTop;

					if (eachObstacle->mObstacleType == ObstacleType::WESTERN_ROCK ||
					   eachObstacle->mObstacleType == ObstacleType::WESTERN_SPIKE ||
					   eachObstacle->mObstacleType == ObstacleType::WESTERN_POST) {
						mPlayer->mState = PlayerState::DIE;
					}

					return true;
				}
			}
		}
	}

	return false;
}

bool LevelOneCode::hasWallOnRight(double *wallX) {
	std::pair<double, double> playerBottomLeft = mPlayer->calcBottomLeft();
	std::pair<double, double> playerTopRight = mPlayer->calcTopRight();

	double playerTop = playerTopRight.second;
	double playerBottom = playerBottomLeft.second;
	double playerLeft = playerBottomLeft.first;
	double playerRight = playerTopRight.first;

	for (auto eachObstacle : mObstacleList) {
		const int DISTANCE_RIGHT = 5;
		const int DISTANCE_LEFT = 5;
		const int DISTANCE_TOP = 16;
		const int DISTANCE_BOTTOM = 16;

		if (eachObstacle->mObstacleType == ObstacleType::MACHINE_PART) {
			std::pair<double, double> blockBottomLeft = eachObstacle->calcBottomLeft();
			std::pair<double, double> blockTopRight = eachObstacle->calcTopRight();

			// These magic numbers are used because the walls must be a bit at the front of the top
			double blockRight = blockTopRight.first + DISTANCE_RIGHT;
			double blockLeft = blockBottomLeft.first - DISTANCE_LEFT;
			double blockTop = blockTopRight.second + DISTANCE_TOP;
			double blockBottom = blockBottomLeft.second - DISTANCE_BOTTOM;



			if (playerLeft < blockLeft &&
			   playerLeft < blockRight &&
			   playerTop <= blockBottom &&
			   playerBottom >= blockTop &&
			   playerRight >= blockLeft) {

				eachObstacle->mMachinePartState = MachinePartState::COLLECTED;
				mPlayer->mCollectedParts++;
				mObstacleList.remove(eachObstacle);

				return false;
			}
		} else {

			for (auto eachBlock : eachObstacle->mBlockList) {

				std::pair<double, double> blockBottomLeft = eachBlock->calcBottomLeft();
				std::pair<double, double> blockTopRight = eachBlock->calcTopRight();

				// These magic numbers are used because the walls must be a bit at the front of the top.
				double blockRight = blockTopRight.first + DISTANCE_RIGHT;
				double blockLeft = blockBottomLeft.first - DISTANCE_LEFT;
				double blockTop = blockTopRight.second + DISTANCE_TOP;
				double blockBottom = blockBottomLeft.second - DISTANCE_BOTTOM;

				// DEBUG("obstacle: " << eachObstacle->mName);
				// DEBUG("Game object position x: " << gameObject->mCurrentPosition.first);
				// DEBUG("Game object position y: " << gameObject->mCurrentPosition.second);
				//
				// DEBUG("obstacle position x: " << eachObstacle->mCurrentPosition.first);
				// DEBUG("obstacle position y: " << eachObstacle->mCurrentPosition.second);
				//
				// DEBUG("Player left: " << playerLeft);
				// DEBUG("Player right: " << playerRight);
				// DEBUG("Player top: " << playerTop);
				// DEBUG("Player bottom: " << playerBottom);
				// DEBUG("Block left: " << blockLeft);
				// DEBUG("Block right: " << blockRight);
				// DEBUG("Block top: " << blockTop);
				// DEBUG("Block bottom: " << blockBottom);

				if (playerLeft < blockLeft &&
				   playerLeft < blockRight &&
				   playerTop <= blockBottom &&
				   playerBottom >= blockTop &&
				   playerRight >= blockLeft) {

					if (eachObstacle->mObstacleType == ObstacleType::WESTERN_POST) {
						mPlayer->mState = PlayerState::DIE;
					}

					*wallX = blockLeft - 1.0f;
					return true;
				}

			}
		}
	}

	return false;
}

bool LevelOneCode::hasWallOnLeft(double *wallX) {
	std::pair<double, double> playerBottomLeft = mPlayer->calcBottomLeft();
	std::pair<double, double> playerTopRight = mPlayer->calcTopRight();

	double playerTop = playerTopRight.second;
	double playerBottom = playerBottomLeft.second;
	double playerLeft = playerBottomLeft.first;
	double playerRight = playerTopRight.first;

	for (auto eachObstacle : mObstacleList) {

		for (auto eachBlock : eachObstacle->mBlockList) {

			std::pair<double, double> blockBottomLeft = eachBlock->calcBottomLeft();
			std::pair<double, double> blockTopRight = eachBlock->calcTopRight();

			double blockRight = blockTopRight.first;
			double blockTop = blockTopRight.second;
			double blockBottom = blockBottomLeft.second;


			if (playerLeft <= blockRight &&
			   playerRight > blockRight &&
			   playerTop <= blockBottom &&
			   playerBottom >= blockTop) {

				*wallX = blockRight + 1.0f;
				return true;
			}

		}
	}

	return false;
}

bool LevelOneCode::hasCeiling(double *groundY) {
	std::pair<double, double> playerBottomLeft = mPlayer->calcBottomLeft();
	std::pair<double, double> playerTopRight = mPlayer->calcTopRight();

	double playerTop = playerTopRight.second;
	double playerBottom = playerBottomLeft.second;
	double playerLeft = playerBottomLeft.first;
	double playerRight = playerTopRight.first;


	for (auto eachObstacle : mObstacleList) {

		for (auto eachBlock : eachObstacle->mBlockList) {
			std::pair<double, double> blockBottomLeft = eachBlock->calcBottomLeft();
			std::pair<double, double> blockTopRight = eachBlock->calcTopRight();

			double blockLeft = blockBottomLeft.first;
			double blockRight = blockTopRight.first;
			double blockTop = blockTopRight.second;
			double blockBottom = blockBottomLeft.second;

			if (playerLeft >= blockLeft &&
			   playerRight <= blockRight &&
			   playerTop <= blockBottom &&
			   playerBottom >= blockTop &&
			   playerTop >= blockTop) {

				if (eachObstacle->mObstacleType == ObstacleType::WESTERN_POST) {
					mPlayer->mState = PlayerState::DIE;
				}

				*groundY = blockBottom;
				return true;
			}
		}
	}
	return false;
	}
