/**
 * @file game.cpp
 * @brief Purpose: Contains general scope to the game.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 *
 * This file is responsible for create the model to all game and scene management.
*/
#include "sdl2include.h"
#include "game.hpp"
#include <iostream>
#include <cstdlib>

using namespace engine; // Used to avoid write engine::Game engine::Game::instance;.

Game Game::instance; // Used to initialize in fact the static instance of game;

/**
 * @brief Default constructor for the Game component.
 *
 * @return "void".
*/
Game::Game(){
	this->needToChangeScene = false;
	this->currentScene = NULL;
	this->lastScene = NULL;
	this->frameRate = 60;
}

/**
 * @brief Main Game Loop and SDL Initiators.
 *
 * Run all the game.
 *
 * @return "void".
*/
void Game::run(){

	// Initialize all SDL attributes, create the window and set state to play.
	sdlElements.initSDL();
	sdlElements.createWindow();
	gameState = engine::GameState::PLAY;

	frameTime = 1000.0f / frameRate; // Calculate the time of a game frame (miliseconds).

	INFO("Starting Main Loop Game.");
	while(gameState == engine::GameState::PLAY){
		timer.step(); // Get the current time.

		if(startAndStopScenes() == false){
			break;
		}

		SDL_Event _event; // Reading input (events).

		// "Search" for a event that will close the Game.
		while(SDL_PollEvent(&_event)){
			switch(_event.type){
				case SDL_QUIT:
					gameState = engine::GameState::EXIT;
					break;
				default:
					inputManager.update(_event); // Check for user inputs.
					break;
			}
		}

		// Clean and Draw the Scene to refreh animations and objects.
		SDL_RenderClear(sdlElements.getCanvas());
		currentScene->draw();
		SDL_RenderPresent(sdlElements.getCanvas());

		currentScene->updateCode();

		inputManager.clear();

		timer.DeltaTime(); // Calculating elapsed time from the start of this frame until now.

		/**
		 * If the time that has passed until now was faster than the frame's time,
		 * is needed wait the time necessary to complete a frame's time.
		*/
		if(frameTime > timer.getDeltaTime()){
			SDL_Delay(frameTime - timer.getDeltaTime());
		}

		timer.DeltaTime();

	}

	INFO("Finishing Main Loop.");

	INFO("Shutting down SDL.");
	sdlElements.terminateSDL();
}

/**
 * @brief add scenes to the game.
 *
 * Used to add a Scene to map that have all Game's Scenes.
 *
 * @param Scene that represent a game stage.
 *
 * @return a bool that indicates the add scene success.
*/
bool Game::addScene(Scene &scene){
	ASSERT(&scene != NULL, "The scene can't be null.");
	auto sceneName = scene.getSceneName();
	ASSERT(sceneName != "", "Scene name can't be null.");

	if(sceneMap.find(sceneName) != sceneMap.end()){
		ERROR("Scene already exists!");
		return false;
	}

	sceneMap[sceneName] = &scene;
	ASSERT(sceneMap[sceneName] == &scene, "Scene must be added to map.");

	return true;
}

/**
 * @brief Restart game scene.
 *
 * Load the scene. Used every time a scene needs to be reseted.
 *
 * @param sceneName string that has the scene name.
 *
 * @return "void".
*/
void Game::restartScene(std::string sceneName){
	ASSERT(sceneName != "", "The scene name can't be blank.");
	auto scene = sceneMap[sceneName];
	ASSERT(&scene != NULL, "Scene can't be null.");

	scene->restart();
}
/**
 * @brief set the game attributtes to SDL instance.
 *
 * Transfer the game attributes to SDL instace and set Game's frameRate.
 *
 * @param gameName string that has the name of the game
 * @param windowWidth sets the width of the game screen
 * @param windowHeight sets the height of the game screen
 * @param frameRate Frames per Second of the Game (FPS).
 *
 * @return "void".
*/
void Game::setAttributes(std::string gameName, int windowWidth, int windowHeight, int frameRate){
	ASSERT(gameName != "", "The game name can't be blank.");
	ASSERT(windowWidth >= 0, "The window width can't be lower than zero.");
	ASSERT(windowHeight >= 0, "The window height can't be lower than zero.");
	ASSERT(frameRate >= 0, "The frame rate can't be lower than zero.");

	sdlElements.setSDLAttributes(gameName, windowWidth, windowHeight);
	this->frameRate = frameRate;
}

/**
 * @brief change the game scene.
 *
 * Perform the necessary checks and prepare the structure to switch Scenes.
 *
 * @param sceneName string that has the scene name
 *
 * @return "void".
*/
void Game::changeScene(std::string sceneName){
	ASSERT(sceneName != "", "The scene name can't be blank.");
	INFO("Changing Scenes.");
	if(sceneMap.find(sceneName) == sceneMap.end()){
		ERROR("Scene not found!");
	}

	lastScene = currentScene;
	currentScene = sceneMap[sceneName];
	needToChangeScene = true;
}

/**
 * @brief switch the game scene
 *
 * Perform scene switching effectively.
 *
 * @param sceneName string that has the scene name
 *
 * @return bool that represents the success on change scene.
*/
bool Game::startAndStopScenes(){
	if(needToChangeScene){
		if(currentScene == NULL){
			ERROR("No scenes to run!");
			return false;
		}else{
			// If the last scene is equal the current scene, we still need
			// to delete all keys from the game object map on scene.
			if(lastScene != NULL && lastScene->getSceneName() == currentScene->getSceneName()){
				currentScene->deleteKeyList();
			}

			if (currentScene->mState == SceneState::RUNNED) {
				currentScene->restart();
				currentScene->mState = SceneState::FIRST_TIME;
			} else {
				//Nothing to do, scene state is different
			}

			if (currentScene->mState == SceneState::FIRST_TIME) {
				currentScene->mState = SceneState::RUNNED;
			} else {
				//Nothing to do, scene state is different
			}

			currentScene->init();

			if(lastScene != NULL){
				INFO("Shuting down scene!");
				if(lastScene->getSceneName() != currentScene->getSceneName()){
					lastScene->shutdown();
				}
			}

			needToChangeScene = false;
		}
	}

	return true;
}
