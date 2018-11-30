/**
* @file animation_controller.cpp
* @brief Purpose: Contains the animaton controller component.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main game component its declaration and state.
*/
#include "animation_controller.hpp"

using namespace engine;

AnimationController::AnimationController() {
	//DEBUG("Calling AnimationController::AnimationController");
	//This function is just changing the state of componentState to enabled.
	this->componentState = State::ENABLED;
}

AnimationController::AnimationController(GameObject &gameObject) {
	//DEBUG("Calling AnimationController::AnimationController");
	//This function paragraph receives the gameObject and enables the
	//componentState. Its important because the gameObject is the specific
	// object to whom the animation is going to refer.
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

void AnimationController::init() {
	//DEBUG("Calling AnimationController::init");
	//This function paragraph initialize the animations on the map.
	for (auto animationRow : mAnimationMap) {
		auto animation = animationRow.second;
		animation->init();
		ASSERT(animation != NULL, "animation can't be null");
	}
}

void AnimationController::shutdown() {
	//DEBUG("Shutting down AnimationController");
	//This function paragraph shutdown the refered animations.
	for (auto animationRow : mAnimationMap) {
		auto animation = animationRow.second;
		ASSERT(
			animation != NULL,
			"AnimationController::shutdown, animation map can't be null"
		);
		animation->shutdown();
	}
}

void AnimationController::draw() {
	//DEBUG("Drawing AnimationController");
	//This function paragraph draws on the screen the refered animations.
	for (auto animationRow : mAnimationMap) {
		auto animation = animationRow.second;
		ASSERT(
			animation != NULL,
			"AnimationController::draw, animation map can't be null"
		);
		if (animation->isEnabled()) {
			animation->draw();
		} else {
			//Nothing to do
		}
	}
}

void AnimationController::addAnimation(std::string animationName, Animation &animation) {
	//DEBUG("Calling AnimationController::addAnimation");
	//This function paragraph adds new animations on the list.
	ASSERT(
		animationName != "",
		"AnimationController::addAnimation, animationName is empty."
	);
	ASSERT(&animation != NULL, "The animation can't be null.");
	std::pair<std::string, Animation *> newAnimation(animationName, &animation);
	ASSERT(
		newAnimation.second != NULL,
		"AnimationController::addAnimation, newAnimation can't be null"
	);
	ASSERT(
		newAnimation.first != "",
		"AnimationController::addAnimation, newAnimation must have a name"
	);
	mAnimationMap.insert(newAnimation);
}

void AnimationController::startUniqueAnimation(std::string animationName) {
	//DEBUG("Calling AnimationController::startUniqueAnimation");
	//This function paragraph rows through the animations list and selects them
	//to be played.
	ASSERT(
		animationName != "",
		"AnimationController::startUniqueAnimation, animationName is empty."
	);
	auto animationToBePlayed = mAnimationMap.find(animationName);
	ASSERT(
		animationToBePlayed->second != NULL,
		"AnimationController::startUniqueAnimation, animationToBePlayed is empty."
	);


	//This function paragraph verifies if the selected animation adress is not
	//the last on the list
	//Default is to fail
	if (animationToBePlayed == mAnimationMap.end()) {
		ERROR("Animation " << animationName << "doesn't exist!");
	} else {
		//Nothing to do
	}



	//This fucntion paragraph verifies and sets the state of animations on
	//the list. It verifies if its to end the animations or to let them follow.
	if (animationToBePlayed->second->mState == AnimationState::STOPPED) {
		for (auto eachAnimation : mAnimationMap) {
			eachAnimation.second->disableComponent();
			eachAnimation.second->mState = AnimationState::STOPPED;
		}
		if (animationToBePlayed != mAnimationMap.end()) {
			animationToBePlayed->second->enableComponent();
			animationToBePlayed->second->mState = AnimationState::PLAYING;
		} else {
			//Nothing to do
		}
	} else {
		//Nothing to do
	}
}

void AnimationController::startAnimation(std::string animationName) {
	//DEBUG("Calling AnimationController::startAnimation");
	//This function paragraph rows through the animations list and selects them
	//to start playing.
	ASSERT(
		animationName != "",
		"AnimationController::startAnimation, animationName is empty."
	);
	auto animationToBePlayed = mAnimationMap.find(animationName);
	ASSERT(
		animationToBePlayed->second != NULL,
		"AnimationController::startAnimation, animationToBePlayed is empty."
	);



	//This function paragraph verifies if the selected animation adress is not
	//the last on the list
	//Default is to fail
	if (animationToBePlayed == mAnimationMap.end()) {
		ERROR("Animation " << animationName << "doesn't exist!");
	} else {
		//Nothing to do
	}


	//This function paragraph verifies if the animation is set to be played.
	//If not, the functions sets it to start playing
	if (!animationToBePlayed->second->isEnabled()) {
		animationToBePlayed->second->enableComponent();
		animationToBePlayed->second->mState = AnimationState::PLAYING;
	} else {
		//Nothing to do
	}
}


void AnimationController::stopAnimation(std::string animationName) {
	//DEBUG("Calling AnimationController::stopAnimation");
	//This function paragraph rows through the animations list and selects them
	//to be stopped.
	ASSERT(
		animationName != "",
		"AnimationController::stopAnimation, animationName is empty."
	);
	auto animationToBePlayed = mAnimationMap.find(animationName);
	ASSERT(
		animationToBePlayed->second != NULL,
		"AnimationController::stopAnimation, animationToBePlayed is empty."
	);


	//This function paragraph disables the animations components and sets them
	//not to be played.
	if (animationToBePlayed != mAnimationMap.end()) {
		animationToBePlayed->second->disableComponent();
	} else {
		ERROR("Animation couldn't be found!");
	}
}

AnimationState AnimationController::getAnimationStatus(std::string animationName) {
	//DEBUG("Calling AnimationController::getAnimationStatus");
	//This function paragraph rows through the animations list and then
	//receive their status and return them.
	ASSERT(
		animationName != "",
		"AnimationController::stopAnimation, animationName is empty."
	);
	auto animation = mAnimationMap.find(animationName);
	ASSERT(
		animation->second != NULL,
		"AnimationController::getAnimationStatus, animation is empty."
	);

	if (animation != mAnimationMap.end()) {
		return animation->second->mState;
	} else {
		ERROR("Animation couldn't be found!");
	}
}
