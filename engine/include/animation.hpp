/**
* @file animation.hpp
* @brief Purpose: Defines the general scope of animation.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main animation component its declaration and state.
*/
#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include "sdl2include.h"
#include "image_component.hpp"
#include "sprite.hpp"
#include <vector>

namespace engine {

	enum class AnimationState {
		PLAYING,
		STOPPED,
		FINISHED,
	};

	class Animation : public ImageComponent {
	public:
		std::string animationName;
		AnimationState mState = AnimationState::STOPPED;

	private:
		std::vector<Sprite *> mSpriteList;
		int mCurrentSprite;
		int mStartFrame;
		int mEndFrame;
		float mCurrentAnimationTime;
		int mEachFrameTime;
		float mAnimationTime;
		bool mLoop;
		//std::pair<double, double> mPositionRelativeToObject;

		void checkLimits();
		void updateQuad();
		void updateFrameBasedOntime();
		void updateGameObjectMeasures();

	public:
		Animation();
		Animation(
			GameObject & gameObject,
			std::string imagePath,
			float animationTime,
			std::vector<Sprite *> spriteList,
			int startFrame,
			int endFrame,
			bool loop,
			double zoomFactor
		);
		Animation(
			GameObject & gameObject,
			std::string imagePath,
			float animationTime,
			std::vector<Sprite *> spriteList,
			int startFrame,
			int endFrame,
			bool loop,
			double zoomFactor,
			std::pair<double, double> positionRelativeToObject
		);
		virtual ~Animation();

		void shutdown();
		void draw();
		void disableComponent();
		inline std::string getClassName(){
			return "Animation";
		}
	};
}

#endif
