/**
* @file animation.cpp
* @brief Purpose: Controls animaton.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main game component its declaration and state.
*/
#include "animation.hpp"
#include "game.hpp"

using namespace engine;

const int ANIMATION_NULL_VALUE = 0;
const int FRAME_VALUE = 1;
const int CURRENT_SPRITE = 0;
const float DIVISOR_NUMBER = 2.0f;
const float CURRENT_ANIMATION_TIME = 0.0f;

Animation::Animation() {}

Animation::Animation(
	GameObject & gameObject,
	std::string imagePath,
	float animationTime,
	std::vector<Sprite *> spriteList,
	int startFrame,
	int endFrame,
	bool loop,
	double zoomFactor
) {
	DEBUG("Calling Animation::Animation");
	ASSERT(imagePath != "", "Animation::Animation, imagePath is empty.");
	ASSERT(
		animationTime > ANIMATION_NULL_VALUE,
		"Animation time can't be zero or less."
	);
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");
	//This function paragraph builds the initial stats of the animations
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->mAnimationTime = animationTime;
	this->mSpriteList = spriteList;
	this->mStartFrame = startFrame;
	this->mEndFrame = endFrame;
	ASSERT((endFrame - startFrame + FRAME_VALUE), "division by zero.");
	this->mEachFrameTime = animationTime / (endFrame - startFrame + FRAME_VALUE);
	this->mCurrentAnimationTime = CURRENT_ANIMATION_TIME;
	this->mLoop = loop;
	this->zoomFactor = zoomFactor;
	this->mCurrentSprite = startFrame;
}


Animation::Animation(
	GameObject & gameObject,
	std::string imagePath,
	float animationTime,
	std::vector<Sprite *> spriteList,
	int startFrame,
	int endFrame,
	bool loop,
	double zoomFactor,
	std::pair<double, double> positionRelativeToObject
) {
	DEBUG("Calling Animation::Animation");
	ASSERT(imagePath != "", "Animation::CreateAnimation, imagePath is empty.");
	ASSERT(
		animationTime > ANIMATION_NULL_VALUE,
		"Animation time can't be zero or less."
	);
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");

	//This function paragraph rebuilds the initial stats of the animations
	//but also adds a new variable that is the positionRelativeToObject
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->mAnimationTime = animationTime;
	this->mSpriteList = spriteList;
	this->mStartFrame = startFrame;
	this->mEndFrame = endFrame;
	ASSERT((endFrame - startFrame + FRAME_VALUE), "division by zero.");
	this->mEachFrameTime = animationTime / (endFrame - startFrame + FRAME_VALUE);
	this->mCurrentAnimationTime = CURRENT_ANIMATION_TIME;
	this->mLoop = loop;
	this->zoomFactor = zoomFactor;
	this->mCurrentSprite = startFrame;
	this->mPositionRelativeToObject = positionRelativeToObject;
}

Animation::~Animation() {}

void Animation::shutdown() {
	//this function paragraph deletes the sprites in a list
	DEBUG("Shutting down Animation");
	if (mSpriteList.size() > 0) {
		for (auto eachSprite : mSpriteList) {
			delete(eachSprite);
			eachSprite = NULL;
		}
	} else {
		//Nothing to do
	}
}

void Animation::draw() {
	//This function paragraph is responsible for bringing together
	//other functions to be able to draw the animations.
	//DEBUG("Drawing Animation");
	checkLimits();
	updateQuad();
	updateGameObjectMeasures();
	SDL_RenderCopy(
		Game::instance.sdlElements.getCanvas(),
		imageTexture,
		&renderQuad,
		&canvasQuad
	);
	updateFrameBasedOntime();
}

void Animation::disableComponent() {
	//DEBUG("Disabling Animation Component");
	//This function paragraph disables the component state of the animation
	this->componentState = State::DISABLED;
	mCurrentAnimationTime = CURRENT_ANIMATION_TIME;
	mCurrentSprite = mStartFrame;
}

void Animation::checkLimits() {
	//DEBUG("Checking Animation Limits");
	//This function verifies the limits of the animation related to the frames
	if(mCurrentSprite > mEndFrame) {
		if (mLoop) {
			mCurrentSprite = CURRENT_SPRITE;
			mCurrentAnimationTime = CURRENT_ANIMATION_TIME;
			mState = AnimationState::STOPPED;
		} else {
			mCurrentSprite = mEndFrame;
			mState = AnimationState::FINISHED;
		}
	}
}

void Animation::updateQuad() {
	//DEBUG("Updating Animation Quad");
	//This function paragraph generates the renderQuad with
	//the current sprite and its informations
	renderQuad = {
		mSpriteList[mCurrentSprite]->getSpriteX(),
		mSpriteList[mCurrentSprite]->getSpriteY(),
		mSpriteList[mCurrentSprite]->getSpriteWidth(),
		mSpriteList[mCurrentSprite]->getSpriteHeight()
	};



	//Updating canvas quad.
	//This function paragraph updates the canvasQuad values
	//according to the relative object and zoom
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		(int)(mSpriteList[mCurrentSprite]->getSpriteWidth() * zoomFactor),
		(int)(mSpriteList[mCurrentSprite]->getSpriteHeight() * zoomFactor),
	};
}

void Animation::updateFrameBasedOntime() {
	//DEBUG("Calling Animation::updateFrameBasedOntime");
	//This function paragraph updates the frame with the time
	mCurrentAnimationTime += Game::instance.getTimer().getDeltaTime();
	ASSERT((mEachFrameTime + mStartFrame) != 0, "Division by zero");

	mCurrentSprite = mCurrentAnimationTime / mEachFrameTime + mStartFrame;
}

void Animation::updateGameObjectMeasures() {
	//DEBUG("Calling Animation::updateGameObjectMeasures");
	//This function paragraph updates the game Object measues according
	//to the zoom 
	ASSERT(
		DIVISOR_NUMBER != 0,
		"Animation::updateGameObjectMeasures, DIVISOR_NUMBER can't be zero."
	);

	gameObject->mHalfSize.first
	= mSpriteList[mCurrentSprite]->getSpriteWidth() * zoomFactor / DIVISOR_NUMBER;

	gameObject->mHalfSize.second
	= mSpriteList[mCurrentSprite]->getSpriteHeight() * zoomFactor / DIVISOR_NUMBER;

	gameObject->mCenter.first
	= gameObject->mCurrentPosition.first + gameObject->mHalfSize.first;

	gameObject->mCenter.second
	= gameObject->mCurrentPosition.second + gameObject->mHalfSize.second;
}
