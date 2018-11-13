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
	DEBUG("Calling AnimationController::AnimationController");
	this->componentState = State::ENABLED;
}

AnimationController::AnimationController(GameObject &gameObject) {
	DEBUG("Calling AnimationController::AnimationController");
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");
	this->gameObject = &gameObject;
	this->componentState = State::ENABLED;
}

void AnimationController::init() {
	DEBUG("Calling AnimationController::init");
	for (auto animationRow : mAnimationMap) {
		auto animation = animationRow.second;
		animation->init();
		ASSERT(animation != NULL, "animation can't be null");
	}
}

void AnimationController::shutdown() {
	DEBUG("Shutting down AnimationController");
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
	DEBUG("Drawing AnimationController");
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
	DEBUG("Calling AnimationController::addAnimation");
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
	DEBUG("Calling AnimationController::startUniqueAnimation");
	ASSERT(
		animationName != "",
		"AnimationController::startUniqueAnimation, animationName is empty."
	);
	auto animationToBePlayed = mAnimationMap.find(animationName);
	ASSERT(
		animationToBePlayed->second != NULL,
		"AnimationController::startUniqueAnimation, animationToBePlayed is empty."
	);

	//Default is to fail
	if (animationToBePlayed == mAnimationMap.end()) {
		ERROR("Animation " << animationName << "doesn't exist!");
	} else {
		//Nothing to do
	}

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
	DEBUG("Calling AnimationController::startAnimation");
	ASSERT(
		animationName != "",
		"AnimationController::startAnimation, animationName is empty."
	);
	auto animationToBePlayed = mAnimationMap.find(animationName);
	ASSERT(
		animationToBePlayed->second != NULL,
		"AnimationController::startAnimation, animationToBePlayed is empty."
	);

	//Default is to fail
	if (animationToBePlayed == mAnimationMap.end()) {
		ERROR("Animation " << animationName << "doesn't exist!");
	} else {
		//Nothing to do
	}

	if (!animationToBePlayed->second->isEnabled()) {
		animationToBePlayed->second->enableComponent();
		animationToBePlayed->second->mState = AnimationState::PLAYING;
	} else {
		//Nothing to do
	}
}


void AnimationController::stopAnimation(std::string animationName) {
	DEBUG("Calling AnimationController::stopAnimation");
	ASSERT(
		animationName != "",
		"AnimationController::stopAnimation, animationName is empty."
	);
	auto animationToBePlayed = mAnimationMap.find(animationName);
	ASSERT(
		animationToBePlayed->second != NULL,
		"AnimationController::stopAnimation, animationToBePlayed is empty."
	);

	if (animationToBePlayed != mAnimationMap.end()) {
		animationToBePlayed->second->disableComponent();
	} else {
		ERROR("Animation couldn't be found!");
	}
}

AnimationState AnimationController::getAnimationStatus(std::string animationName) {
	DEBUG("Calling AnimationController::getAnimationStatus");
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
