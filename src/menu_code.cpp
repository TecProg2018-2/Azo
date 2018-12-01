/**
     * @file menu_code.cpp
     * @brief Purpose: Archive responsible for the operation of the ' menu '
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#include "game.hpp"
#include "menu_code.hpp"
#include <ctime>
#include <fstream>
#include <iostream>


using namespace Azo;

/**
     * @brief function responsible for building menu
     *
     * Why: Used to build menu on the map
     *
	 * @param Gameobject that is the creation object of the ' menu '
     */
MenuCode::MenuCode(engine::GameObject *gameObject){
	DEBUG("Creating MenuCode.");
	ASSERT(&gameObject != NULL, "GameObject can't be null.");
	this->gameObject = gameObject; // Variable responsible for game object.
	ASSERT(this->gameObject == gameObject, "gameObject must have correct value.");
	findAudioController();
	findAnimationController();
}
/**
     * @brief function responsible for finding animation controller
     *
     * Why: Used to control the animation of the game
     *
     * @return "void".
     */
void MenuCode::findAnimationController(){
	DEBUG("Finding animation controller on menu code.");
	mAnimationController = (gameObject->getAnimationController(typeid(engine::AnimationController)));
	if(mAnimationController == NULL) {
		errorCode = FunctionStatus::NULLPOINTER;
		errorLog("MenuCode::findAnimationController");
	} else {
		errorCode = FunctionStatus::SUCCESS;
	}
}

/**
     * @brief function responsible for finding audio controller
     *
     * Why: Used to control game audio
     *
     * @return "void".
     */
void MenuCode::findAudioController(){
	DEBUG("Finding audio controller on menu code.");
	mAudioController = (gameObject->getAudioController(typeid(engine::AudioController)));
	if(mAudioController == NULL) {
		errorCode = FunctionStatus::NULLPOINTER;
		errorLog("MenuCode::findAudioController");
	} else {
		errorCode = FunctionStatus::SUCCESS;
	}
}

/**
     * @brief function responsible for selecting game option
     *
     * Why: Used so that the user can select the options in the menu
     *
     * @return "void".
     */
void MenuCode::changeOption(){

	//
	switch (mCurrentButton) {
		// Start Option.
		case ButtonType::START_BUTTON:

			mAnimationController->startAnimation("arrow_start");

			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				DEBUG("Exit Button is selected.");
				mAnimationController->stopAnimation("arrow_start");

				mCurrentButton = ButtonType::EXIT_BUTTON;

			} else if (engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)) {
				DEBUG("Sound Button is selected.");
				mAnimationController->stopAnimation("arrow_start");
				mCurrentButton = ButtonType::SOUND_BUTTON;
			}

			break;
		// Exit Option.
		case ButtonType::EXIT_BUTTON:
			mAnimationController->startAnimation("arrow_exit");

			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				DEBUG("Sound Button is selected.");
				mAnimationController->stopAnimation("arrow_exit");

				mCurrentButton = ButtonType::SOUND_BUTTON;
			} else if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)){
				DEBUG("Start Button is selected.");
				mAnimationController->stopAnimation("arrow_exit");

				mCurrentButton = ButtonType::START_BUTTON;
			}

			break;
		// Sound Option.
		case ButtonType::SOUND_BUTTON:
			mAnimationController->startAnimation("arrow_sound");

			if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::RIGHT_ARROW)){
				DEBUG("Start Button is selected.");
				mAnimationController->stopAnimation("arrow_sound");

				// Go back to the first option.
				mCurrentButton = ButtonType::START_BUTTON;

			} else if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::LEFT_ARROW)){
				DEBUG("Exit Button is selected.");
				mAnimationController->stopAnimation("arrow_sound");

				mCurrentButton = ButtonType::EXIT_BUTTON;
			}
			break;
		default:
			// Nothing to do, no button defined.
			break;
	}
}


/**
     * @brief function responsible for updating game states
     *
     * Why: Used so that the game can consistently respond to the player's inputs
     *
     * @return "void".
     */
void MenuCode::updateCode(){
	if(engine::Game::instance.inputManager.keyDownOnce(engine::Button::ENTER)){

		//Switch responsable for verify buton selected in menu screen
		switch (mCurrentButton) {
			case ButtonType::START_BUTTON:
				DEBUG("Start button selected.");
				mAudioController->stopAudio("menu_theme");
				engine::Game::instance.changeScene("level_one");
				break;
			case ButtonType::EXIT_BUTTON:
				DEBUG("Exit button selected.");
				engine::Game::instance.gameState = engine::GameState::EXIT; // Variable responsible for the state of game.
				break;
			case ButtonType::SOUND_BUTTON:
				DEBUG("Sound button selected.");
				if(mAudioController->getAudioState("menu_theme") == engine::AudioState::PLAYING){
					DEBUG("Stop Sound.");
					mAudioController->pauseAudio("menu_theme");
					mAnimationController->stopAnimation("sound_enabled_button");
					mAnimationController->startAnimation("sound_disabled_button");
				} else {
					DEBUG("Restart Sound.");
					// Audio not currently playing, so start it again.
					mAudioController->playAudio("menu_theme");
					mAnimationController->startAnimation("sound_enabled_button");
					mAnimationController->stopAnimation("sound_disabled_button");
				}
				break;
			default:
				// Nothing to do, no button selected.
				break;
		}
	}
	changeOption();
}

void MenuCode::errorLog(std::string file){
    std::ofstream outfile;
    outfile.open("../errorLog.txt", std::ofstream::out | std::ofstream::app);
    time_t now = time(0);
	std::string dt = ctime(&now);
    std::string message = "===============\n";
	message += "Function: " + file + "\n";
    message += "Date: " + dt + "\n";

	//Bolck responsable for manage types of error.
    switch(errorCode) {
        case FunctionStatus::DIVIBYZERO:
            message += "Error: division by zero\n";
            break;
        case FunctionStatus::EMPTYSTRING:
            message += "empty String\n";
            break;
        case FunctionStatus::NULLPOINTER:
            message += "null pointer\n";
            break;
		case FunctionStatus::WRONGTYPE:
            message += "wrong type\n";
            break;
        default:
            message = "";
			break;
    }
    outfile << message;
    outfile.close();
}
