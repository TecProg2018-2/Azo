/**
 * @file input_manager.cpp
 * @brief Purpose: Contains general scope to the input_manager.
 *
 * GLP v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "input_manager.hpp"

using namespace engine;// Used to avoid write engine::Game engine::Game::instance;.

/**
* @brief Default constructor for the input manager.
*
* @return "void".
*/
InputManager::InputManager() {}
InputManager::~InputManager() {}

/**
* @brief test if button is pressed once.
*
* Used to set the test of key down only once.
*
* @param Button that represent user input.
*
* @return a bool that indicates the add scene success.
*/

bool InputManager::keyDownOnce(Button button) {
	ASSERT(button != -1, "button path can't be -1.");
	if (keyboardStates[button]) {
		SDL_PumpEvents();
		DEBUG("Button " << button << " is being Pressed");
		if (!keyboardStates[button]) {
			DEBUG("Button " << button << " is Released");
			return true;
		} else {
			//Nothing to do for the keyboardStates matches button
		}
	} else {
		//Nothing to do for there's no SDL_Event
	}
	return false;

}

/**
* @brief test the button state.
*
* Used to set the test of key state.
*
* @param Button that represent user input.
*
* @return a bool that indicates the add scene success.
*/
bool InputManager::keyState(Button button) {
	ASSERT(button != -1, "button path can't be -1.");
	return keyboardStates[button];
}

/**
* @brief clear.
*
* Used to clear the events.
*
* @return "void".
*/

void InputManager::clear() {
	mEventList.clear();
}

/**
* @brief update the sdl events.
*
* Used to get the keyboard state.
*
* @param _event.
*
* @return  "void".
*/
void InputManager::update(SDL_Event _event) {
	DEBUG("Getting Keyboard State");
	mEventList.push_back(_event);
	keyboardStates = SDL_GetKeyboardState(NULL);
}
