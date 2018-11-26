/**
     * @file menu.cpp
	 * @brief Purpose: Responsible for the Map menu screen
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#include "menu.hpp"

using namespace Azo;

/**
     * @brief function responsible for creating menu scene
     *
     * Why: Because it is necessary for the player to have access to the game menu before it starts
     */
Menu::Menu(std::string name) {
	DEBUG("Creating menu.");
	ASSERT(name != "", "The name can't be empty.");
	this->sceneName = name;
	createGameObjects();
}

/**
     * @brief function responsible for restarting the game
     *
     * Why: Because it is necessary that the player can restart the game
	 *
	 * @return "void".
     */
void Menu::restart(){
	DEBUG("Calling Menu::restart.");
	gameObjectMap.clear();
	createGameObjects();
}

/**
     * @brief function responsible for shutting down menu.
     *
     * Why: Because it is responsible for shutting down the menu
	 *
	 * @return "void".
     */
void Menu::shutdown() {
	DEBUG("Calling Menu::shutdown.");
	if(mMenu != NULL){
		mMenu = NULL;
	} else {
		// Nothing to do, Menu shut down.
	}
}

/**
     * @brief function responsible for creating game objects
     *
     * Why: Because it is necessary for the menu to have some elements in its interface
	 *
	 * @return "void".
     */
void Menu::createGameObjects() {
	DEBUG("Creating Menu GameObjects.");

	mMenu = new engine::GameObject("menu", std::make_pair(0.0, 0.0));
	ASSERT(mMenu != NULL, "The mMenu can't be null."); 

	createMenuComponents();
	this->addGameObject(*mMenu);
}

/**
     * @brief function responsible for creating game objects
     *
     * Why: Because it is necessary that the menu has some elements in its interfacece
	 *
	 * @return "void".
     */
void Menu::createMenuComponents() {
	DEBUG("Creating Menu Components.");

	DEBUG("Adding Menu audio component.");
	mMenuTheme = new engine::AudioComponent(*mMenu, "audios/TemaGame.ogg", true, true);
    ASSERT(mMenuTheme != NULL, "The mMenuTheme can't be null.");

	DEBUG("Adding Menu audio controller.");
	mAudioController = new engine::AudioController();
    ASSERT(mAudioController != NULL, "The mAudioController can't be null.");

	DEBUG("Adding Menu audio theme.");
	mAudioController->addAudio("menu_theme", *mMenuTheme);
	mMenu->addComponent(*mAudioController);

	DEBUG("Adding Menu animation controller.");
	mAnimationController = new engine::AnimationController(*mMenu);
	ASSERT(mAnimationController != NULL, "The mAnimationController can't be null.");

	generateButtonsAnimation();

	DEBUG("Generating Menu start button.");
	mStartButton = new engine::Animation(*mMenu,
					       				 "general_images/textos.png",
					       				 1.0f, // animationTime
					       				 mStartButtonSprites,
					       				 0, // startFrame
					       				 0, // endFrame
					       				 false, // loop
					       				 1.0, // zoomFactor
					       				 std::make_pair(205.0, 162.0)); // positionRelativeToObject

	ASSERT(mStartButton != NULL, "The mStartButton can't be null."); 

	mAnimationController->addAnimation("start_button", *mStartButton);

	DEBUG("Generating Menu arrow start.");
	mArrowStart = new engine::Animation(*mMenu,
					      				"general_images/textos.png",
					      				1.0f,
					      				mArrowSprites,
					      				0,
					      				0,
					      				false,
					      				1.0,
					      				std::make_pair(168.0, 162.0));
	ASSERT(mArrowStart != NULL, "The mArrowStart can't be null."); 

	mAnimationController->addAnimation("arrow_start", *mArrowStart);

	DEBUG("Generating Menu exit button.");
	mExitButton = new engine::Animation(*mMenu,
					      				"general_images/textos.png",
					      				1.0f,
					      				mExitButtonSprites,
					      				0,
					      				0,
					      				false,
										1.0,
					      				std::make_pair(551.0, 162.0));
	ASSERT(mExitButton != NULL, "The mExitButton can't be null.");

	mAnimationController->addAnimation("exit_button", *mExitButton);

	DEBUG("Generating Menu arrow exit.");
	mArrowExit = new engine::Animation(*mMenu,
					     				"general_images/textos.png",
					     				1.0f,
					     				mArrowSprites,
					     				0,
					     				0,
					     				false,
					     				1.0,
					     				std::make_pair(514.0, 162.0));
	ASSERT(mArrowExit != NULL, "The mArrowExit can't be null.");

	mArrowExit->disableComponent();

	mAnimationController->addAnimation("arrow_exit", *mArrowExit);

	DEBUG("Generating Menu sound enabled button.");
	mSoundEnabledButton = new engine::Animation(*mMenu,
						      				   "general_images/textos.png",
						      				   1.0f,
						      				   mSoundEnabledButtonSprites,
						      				   0,
						      				   0,
						      				   false,
						      				   1.0,
						      				   std::make_pair(708.0, 40.0));
	
	ASSERT(mSoundEnabledButton != NULL, "The mSoundEnabledButton can't be null.");

	mAnimationController->addAnimation("sound_enabled_button", *mSoundEnabledButton);

	DEBUG("Generating Menu sound disabled button.");
	mSoundDisabledButton = new engine::Animation(*mMenu,
												 "general_images/textos.png",
												 1.0f,
												 mSoundDisabledButtonSprites,
												 0,
												 0,
												 false,
												 1.0,
												 std::make_pair(708.0, 40.0));
	
	ASSERT(mSoundDisabledButton != NULL, "The mSoundDisabledButton can't be null.");

	DEBUG("Disabling Menu sound disabled button.");
	mSoundDisabledButton->disableComponent();

	mAnimationController->addAnimation("sound_disabled_button", *mSoundDisabledButton);

	DEBUG("Generating Menu arrow sound.");
	mArrowSound = new engine::Animation(*mMenu,
					      				"general_images/textos.png",
					      				1.0f,
					      				mArrowSprites,
					      				0,
					      				0,
					      				false,
					      				1.0,
					      				std::make_pair(676.0, 40.0));
	
	ASSERT(mArrowSound!= NULL, "The mArrowSound can't be null.");

	mArrowSound->disableComponent();

	mAnimationController->addAnimation("arrow_sound", *mArrowSound);

	mMenu->addComponent(* mAnimationController);

	DEBUG("Creating Menu background.");
	mBackground = new engine::BackgroundComponent(*mMenu, "backgrounds/menu.png");
	ASSERT(mBackground!= NULL, "The mBackground can't be null.");

	mMenu->addComponent(*mBackground);

	DEBUG("Creating the Menu code component.");
	mCode = new MenuCode(mMenu);
	ASSERT(mCode != NULL, "The mCode can't be null."); 

	mMenu->addComponent(*mCode);
}

/**
     * @brief function responsible for generating button animations
     *
     * Why: For aesthetic purposes
	 *
	 * @return "void"
     */
void Menu::generateButtonsAnimation() {
	DEBUG("Generating Menu start button sprites.");
	mStartButtonSprites.push_back(new engine::Sprite());

	/*
		Set the animation sprites coordinates (x, y)
		and its Width and Height based on its coordinates
		spriteWidth = (width - spriteX) and spriteHeight = (Height - spriteY)
	*/

	DEBUG("Setting Menu start button sprites position.");
	mStartButtonSprites[0]->setSpriteX((unsigned int)43);
	mStartButtonSprites[0]->setSpriteY((unsigned int)452);
	mStartButtonSprites[0]->setSpriteWidth((unsigned int)(161 - 43));
	mStartButtonSprites[0]->setSpriteHeight((unsigned int)(478 - 452));

	DEBUG("Generating Menu exit button sprites.");
	mExitButtonSprites.push_back(new engine::Sprite());

	DEBUG("Setting Menu exit button sprites position.");
	mExitButtonSprites[0]->setSpriteX((unsigned int)207);
	mExitButtonSprites[0]->setSpriteY((unsigned int)413);
	mExitButtonSprites[0]->setSpriteWidth((unsigned int)(280 - 207));
	mExitButtonSprites[0]->setSpriteHeight((unsigned int)(441 - 413));

	DEBUG("Generating Menu sound enabled button sprites.");
	mSoundEnabledButtonSprites.push_back(new engine::Sprite());

	DEBUG("Setting Menu sound enabled button sprites position.");
	mSoundEnabledButtonSprites[0]->setSpriteX((unsigned int)660);
	mSoundEnabledButtonSprites[0]->setSpriteY((unsigned int)46);
	mSoundEnabledButtonSprites[0]->setSpriteWidth((unsigned int)(702 - 660));
	mSoundEnabledButtonSprites[0]->setSpriteHeight((unsigned int)(77 - 46));

	DEBUG("Generating Menu sound disabled button sprites.");
	mSoundDisabledButtonSprites.push_back(new engine::Sprite());

	DEBUG("Generating Menu sound disabled button sprites position.");
	mSoundDisabledButtonSprites[0]->setSpriteX((unsigned int)608);
	mSoundDisabledButtonSprites[0]->setSpriteY((unsigned int)46);
	mSoundDisabledButtonSprites[0]->setSpriteWidth((unsigned int)(646 - 608));
	mSoundDisabledButtonSprites[0]->setSpriteHeight((unsigned int)(77 - 46));

	DEBUG("Generating Menu arrow sprites.");
	mArrowSprites.push_back(new engine::Sprite());

	DEBUG("Generating Menu arrow sprites position.");
	mArrowSprites[0]->setSpriteX((unsigned int)582);
	mArrowSprites[0]->setSpriteY((unsigned int)433);
	mArrowSprites[0]->setSpriteWidth((unsigned int)(598 - 582));
	mArrowSprites[0]->setSpriteHeight((unsigned int)(459 - 433));
}
