/**
* @file: level_one_code.cpp
* @brief Purpose: LevelOneCode class implementation
*
* GPL v3.0 Licence
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*/

#include "level_one_code.hpp"

using namespace Azo;

/*
 * @brief Standard LevelOneCode constructor
 * 
 * Creates LeveloneCode instance.
 */
LevelOneCode::LevelOneCode(engine::GameObject &gameObject){
	ASSERT(&gameObject != NULL, "The game object can't be null.");
	this->gameObject = &gameObject;
	getParents();
	findAudioController();
}


/*
 * @brief Shutdown LevelOneCode component.
 * 
 * Iterates through each created obstacle and the audioController, then deletes them.
 */
void LevelOneCode::shutdown() {
	for (auto Obstacle : mObstacleList) 
		Obstacle = nullptr;
		mAudioController = nullptr;
		mPlayer = nullptr;
	}

	void LevelOneCode::findAudioController() {
	mAudioController = (gameObject->getAudioController(typeid(engine::AudioController)));
}


/*
 * @brief Gets parents of target gameObject.
 * 
 * Used to identify gameObject's parents to use in later code.
 */
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
		else {
			//Nothing to do.
		}
	}
}


/*
 * @brief Updates LevelOneCode state.
 * 
 * Checks the level state and makes changes to position, sound and game state accordingly.
 */
void LevelOneCode::updateCode() {
	//DEBUG("Position: " << gameObject->mCurrentPosition.first );
	//DEBUG("Collected parts: " << mPlayer->mCollectedParts);
	const double PLAYER_MAX_POSITION = 300.0; 
	const int GAME_OBJECT_MAX_POSITION = -17600; 

	if (mPlayer->mCurrentPosition.first >= PLAYER_MAX_POSITION && gameObject->mCurrentPosition.first > GAME_OBJECT_MAX_POSITION) {
		const double CONTROLLER_POSITION_GAME_OBJECT = 4.0; 
		gameObject->mCurrentPosition.first -= CONTROLLER_POSITION_GAME_OBJECT;
		const int CONTROLLER_POSITION_PLAYER = 299; 
		mPlayer->mCurrentPosition.first = CONTROLLER_POSITION_PLAYER;
	} else if (mPlayer->mCurrentPosition.first >= PLAYER_MAX_POSITION) {
		mWaitingTime += engine::Game::instance.getTimer().getDeltaTime();
		mPlayer->mSpeed.first = 0.0; 
		mAudioController->stopAudio("tema_level_one");
		mPlayer->mState = PlayerState::END;

		const double MAX_LOSING_WAITING = 10000.0; 
		if (mPlayer->mCollectedParts != mPlayer->M_TOTAL_PARTS && mWaitingTime >= MAX_LOSING_WAITING) {
			mLosingParts->mObjectState = engine::ObjectState::ENABLED;
			changeOption();
			if (engine::Game::instance.inputManager.keyDownOnce(engine::Button::ENTER)) {
				chooseOption();
			}
			else {
				//Nothing to do.
			}

			const double MAX_WAITING_TIME = 2300.0; 

			if (mWaitingTime >= MAX_WAITING_TIME) {
				mLosingDeath->mObjectState = engine::ObjectState::ENABLED;
				changeOption();
				if (engine::Game::instance.inputManager.keyDownOnce(engine::Button::ENTER)) {
					chooseOption();
				}
				else {
					//Nothing to do.
				}
			}
			else {
				//Nothing to do.
			}

			if (mAudioController->getAudioState("tema_level_one") == engine::AudioState::PLAYING) {
				mAudioController->stopAudio("tema_level_one");
			}
			else {
				//Nothing to do.
			}

		}
		else {
			//Nothing to do.
		}
	}
	else {
		//Nothing to do.
	}
	updateObstaclePosition();

	if (mPlayer->mState != PlayerState::DIE) {
		updatePhysics();
	} else {
		mWaitingTime += engine::Game::instance.getTimer().getDeltaTime();

		if (mWaitingTime >= 2300.0) { 
			mLosingDeath->mObjectState = engine::ObjectState::ENABLED;
			changeOption();
			if (engine::Game::instance.inputManager.keyDownOnce(engine::Button::ENTER)){
				chooseOption();
			}
			else {
				//Nothing to do.
			}
		}
		else {
			//Nothing to do.
		}

		if (mAudioController->getAudioState("tema_level_one") == engine::AudioState::PLAYING){
			mAudioController->stopAudio("tema_level_one");
		}
		else {
			//Nothing to do.
		}
	}
}


/*
 * @brief Changes option.
 * 
 * Used on Menus to change buttons.
 */
void LevelOneCode::changeOption() {
	switch(mCurrentOption) {
		case 1:
			mArrow->mObjectState = engine::ObjectState::ENABLED;
			mArrow->mCurrentPosition = std::make_pair(70, 260);
			if (engine::Game::instance.inputManager.keyDownOnce(engine::Button::RIGHT_ARROW)) {
				mCurrentOption = 2; //CurrentOption = 2 means Exit
			}
			else {
				//Nothing to do.
			}
			break;
		case 2:
			mArrow->mCurrentPosition = std::make_pair(515, 260);
			if (engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)) {
				mCurrentOption = 1; //CurrentOption = 1 means Play
			}
			else {
				//Nothing to do.
			}
			break;
		default:
			// Nothing to do.
			break;			
	}
}


/*
 * @brief Selects option.
 * 
 * Confirms user input on menu and changes the game scene.
 */
void LevelOneCode::chooseOption() {
	switch(mCurrentOption){
		case 1:
			mAudioController->stopAllAudios();
			engine::Game::instance.changeScene("level_one");
			break;
		case 2:
			engine::Game::instance.changeScene("menu");
			break;
	}
}


/*
 * @brief Self-explanatory.
 * 
 * Iterates through each obstacle and updates its position.
 */
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


/*
 * @brief Sets max position for player.
 * 
 * Automatically updates player's position in case it exceeds the limit.
 */
void LevelOneCode::maxPosition(Player *mPlayer, engine::GameObject *gameObject){
	const int PLAYER_MAX_POSITION_CANVAS = 300;
	const int  GAME_OBJECT_MAX_POSITION_CANVAS = -7390;

	if (mPlayer->mCurrentPosition.first >= PLAYER_MAX_POSITION_CANVAS &&
		gameObject->mCurrentPosition.first > GAME_OBJECT_MAX_POSITION_CANVAS) {
			mPlayer->mCurrentPosition.first = PLAYER_MAX_POSITION_CANVAS;
	} else {
			//Nothing to do.
	}
}


/*
 * @brief Checks for player collisions.
 * 
 * Checks player's position and calls collision handlers.
 */
void LevelOneCode::checkCollisions(Player *mPlayer){
	double wallX = 0.0;
	//Check wall on right
	if (mPlayer->mSpeed.first > 0 && hasWallOnRight(&wallX)) {
		DEBUG("Collision with the wall"); 
		mPlayer->mCurrentPosition.first = wallX - (mPlayer->mHalfSize.first * 2);
		mPlayer->mPushesLeftWall = true;
		mPlayer->mState = PlayerState::DIE;
	} else {
		mPlayer->mPushesLeftWall = false;
	}

	//Check wall on left
	if (mPlayer->mSpeed.first < 0.0 && hasWallOnLeft(&wallX)) { 
		mPlayer->mState = PlayerState::DIE;
	} else {
		mPlayer->mPushesRightWall = false;
	}
}


/*
 * @brief Checks whether player is on the ground, sliding or jumping.
 * 
 * Checks player position according to relative position and speed.
 */
void LevelOneCode::checkJumpSlide(Player *mPlayer){
	mPlayer->mCurrentPosition.second += mPlayer->mSpeed.second * engine::Game::instance.getTimer().getDeltaTime();
	double groundY = 0.0; 
	const int PLAYER_RELATIVE_POSITION = 15;

	if (mPlayer->mSpeed.second < 0.0 && hasCeiling(&groundY)) { 
		mPlayer->mCurrentPosition.second = groundY + PLAYER_RELATIVE_POSITION;
		mPlayer->mAtCeiling = true;
	} else if ((mPlayer->mSpeed.second >= 0.0 || mPlayer->mState == PlayerState::SLIDE) && hasGround(&groundY)) { 
		mPlayer->mCurrentPosition.second = groundY - mPlayer->mHalfSize.second - mPlayer->mHalfSize.second + PLAYER_RELATIVE_POSITION;
		mPlayer->mSpeed.second = mPlayer->M_ZERO_VECTOR.second;
		mPlayer->mOnGround = true;
		mPlayer->mCenter.first = mPlayer->mCurrentPosition.first + mPlayer->mHalfSize.first;
		mPlayer->mCenter.second = mPlayer->mCurrentPosition.second + mPlayer->mHalfSize.second;
	} else {
		mPlayer->mOnGround = false;
		mPlayer->mAtCeiling = false;
	}
}


/*
 * @brief Updates player's position.
 * 
 * Changes player position according to current speed.
 */
void LevelOneCode::updatePlayerPosition(Player *mPlayer){
	double deltaWalked =  mPlayer->mSpeed.first;
	//Updates position in relation to current speed
	mPlayer->mCurrentPosition.first += deltaWalked;
}


/*
 * @brief Updates player's physics.
 * 
 * 
 */
void LevelOneCode::updatePhysics() {	
	//Check if player is on air or sliding
	checkJumpSlide(mPlayer);
	updatePlayerPosition(mPlayer);
	//Limiting player position on canvas.
	maxPosition(mPlayer, gameObject);
	//Updating player state in relation to obstacles
	checkCollisions(mPlayer);
}


/*
 * @brief Updates player on ground collisions.
 * 
 * 
 */
void LevelOneCode::handleCollisionGround(Obstacle *obstacle, Player *mPlayer){
	if (obstacle->mObstacleType == ObstacleType::WESTERN_POST) {
		mPlayer->mState = PlayerState::DIE;
	}
	else {
		//Nothing to do
	}
}


/*
 * @brief Updates player and wall side collisions.
 * 
 * 
 */
void LevelOneCode::handleCollisionSide(Obstacle *obstacle, Player *mPlayer, double *wallX, double offset, double blockSide){
	if (obstacle->mObstacleType == ObstacleType::WESTERN_POST) {
		mPlayer->mState = PlayerState::DIE;
	}
	else {
		//Nothing to do
	}
	*wallX = blockSide + offset;
}


/*
 * @brief Updates player and ceiling on ceiling collisions.
 * 
 * 
 */
void LevelOneCode::handleCollisionCeiling(Obstacle *obstacle, Player *mPlayer, double *groundY, double blockBottom){
	if (obstacle->mObstacleType == ObstacleType::WESTERN_POST) {
		mPlayer->mState = PlayerState::DIE;
	}
	else {
		//Nothing to do
	}
	*groundY = blockBottom;
}


/*
 * @brief Makes it so collisions with MachineParts collects them.
 * 
 * 
 */
bool LevelOneCode::collectMachinePart(double playerTop, double playerBottom, double playerRight, double playerLeft,
									  Obstacle *obstacle, Player *mPlayer, std::list<Obstacle *> mObstacleList){

    std::pair<double, double> blockBottomLeft = obstacle->calcBottomLeft();
	std::pair<double, double> blockTopRight = obstacle->calcTopRight();

	const int DISTANCE_LEFT = 5;
	const int DISTANCE_TOP = 16; 
	const int DISTANCE_RIGHT = 5;
	const int DISTANCE_BOTTOM = 16;
	// These magic numbers are used because the walls must be a bit at the front of the top
	double blockRight = blockTopRight.first + DISTANCE_RIGHT;
	double blockLeft = blockBottomLeft.first - DISTANCE_LEFT;
	double blockTop = blockTopRight.second + DISTANCE_TOP;
	double blockBottom = blockBottomLeft.second - DISTANCE_BOTTOM;

	if (playerLeft < blockLeft && playerLeft < blockRight &&
		playerTop <= blockBottom && playerBottom >= blockTop &&
		playerRight >= blockLeft) {

		obstacle->mMachinePartState = MachinePartState::COLLECTED;
		mPlayer->mCollectedParts++;
		mObstacleList.remove(obstacle);

		return true;
	} else {
		//Nothing to do.
		return false;
	}
}


/*
 * @brief Checks if player is touching the ground.
 * 
 * 
 */
bool LevelOneCode::hasGround(double *groundY) {
	ASSERT(*groundY == 0.0,"groundY must be initialized at 0.0");
	std::pair<double, double> playerBottomLeft = mPlayer->calcBottomLeft();
	std::pair<double, double> playerTopRight = mPlayer->calcTopRight();

	double playerTop = playerTopRight.second;
	double playerBottom = playerBottomLeft.second;
	double playerLeft = playerBottomLeft.first;
	double playerRight = playerTopRight.first;

	for (auto eachObstacle : mObstacleList) {
		// If the obstacle is a machine part, we check the collision without invisible blocks (since it has animation).
		// If it collides, we return false (so the position isn't updated) and change the state of the machine part.
		// TODO(Roger): update the collision methods so they return the colliding object.
		// TODO(Roger): Create states to the machine parts.

		if (eachObstacle->mObstacleType == ObstacleType::MACHINE_PART) {
			std::pair<double, double> blockBottomLeft = eachObstacle->calcBottomLeft();
			std::pair<double, double> blockTopRight = eachObstacle->calcTopRight();

			double blockRight = blockTopRight.first;
			double blockLeft = blockBottomLeft.first;
			double blockTop = blockTopRight.second;

			if (playerLeft <= blockRight && playerRight >= blockLeft &&
				playerBottom > blockTop && playerTop < blockTop) {
				// Collided.
				eachObstacle->mMachinePartState = MachinePartState::COLLECTED;
				mPlayer->mCollectedParts++;
				mObstacleList.remove(eachObstacle);
				return false;
			} else {
				//Nothing to do.
			}
		} else {
			for (auto eachBlock : eachObstacle->mBlockList) {
				std::pair<double, double> blockBottomLeft = eachBlock->calcBottomLeft();
				std::pair<double, double> blockTopRight = eachBlock->calcTopRight();

				double blockRight = blockTopRight.first;
				double blockLeft = blockBottomLeft.first;
				double blockTop = blockTopRight.second;

				if (playerLeft <= blockRight && playerRight >= blockLeft &&
					playerBottom > blockTop && playerTop < blockTop) {
						*groundY = blockTop;
					handleCollisionGround(eachObstacle, mPlayer);
					return true;
				} else {
					//Nothing to do.
				}
			}
		}
	}

	return false;
}


/*
 * @brief Checks if there is an obstacle on the right of player.
 * 
 * 
 */
bool LevelOneCode::hasWallOnRight(double *wallX) {
	ASSERT(*wallX == 0.0,"wallX must be initialized at 0.0");
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
				if(collectMachinePart(playerTop, playerBottom, playerRight, playerLeft,
									  eachObstacle, mPlayer, mObstacleList)){
					// Abort if MachinePart collected, nothing to collide with
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

					if (playerLeft < blockLeft && playerLeft < blockRight &&
						playerTop <= blockBottom && playerBottom >= blockTop &&
						playerRight >= blockLeft) {
							
							handleCollisionSide(eachObstacle, mPlayer, wallX, -1.0, blockLeft);
							return true;
					}
						else {
							//Nothing to do.
						}
			}
		}
	}
	return false;
}


/*
 * @brief Checks if there is an obstacle on left of player.
 * 
 * 
 */
bool LevelOneCode::hasWallOnLeft(double *wallX) {
	ASSERT(*wallX == 0.0,"wallX must be initialized at 0.0");
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

			if (playerLeft <= blockRight && playerRight > blockRight &&
				playerTop <= blockBottom && playerBottom >= blockTop) {
				handleCollisionSide(eachObstacle, mPlayer, wallX, +1.0, blockRight);
				return true;
			}
		}
	}
	return false;
}


/*
 * @brief Checks if there is a ceiling on top of player.
 * 
 * 
 */
bool LevelOneCode::hasCeiling(double *groundY) {
ASSERT(*groundY == 0.0,"groundY must be initialized at 0.0");
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

		if (playerLeft >= blockLeft && playerRight <= blockRight &&
			playerTop <= blockBottom && playerBottom >= blockTop &&
			playerTop >= blockTop) {
				handleCollisionCeiling(eachObstacle, mPlayer, groundY, blockBottom);
				return true;
			} else {
				//Nothing to do
			}
		}
	}
	return false;
}