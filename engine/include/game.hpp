/**
 * @file game.hpp
 * @brief Purpose: Contains the Game class declaration.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
 *
 * This file implements the main game engine its declaration and state.
*/
#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "sdl2include.h"
#include "log.h"
#include "scene.hpp"
#include "timer.hpp"
#include "sdl.hpp"
#include "assets_manager.hpp"
#include "input_manager.hpp"

#include <string>
#include <map>


namespace engine {

	/**
     * @brief A GameState class.
  	 *
     * Define Game States to control Loops and other structures.
    */
	enum class GameState {
		EXIT,
		PLAY,
	};

	/**
     * @brief A Game class.
  	 *
     * Generic Game class.
	 * It's how the engine'll see all games that will try to use it.
    */
	class Game {
		public:
			static Game instance; // Global game instance.
			SDL sdlElements; // Used to access SDL class and sdl elements.
			InputManager inputManager; // Used to access the user inputs
			GameState gameState; // Define Game States to control Loops and other structures.

		public:
			Game();

			//Methods that calculate variables in main loop 
			void initializeVariables();
			void refreshObjects();
			void calculateTime();

			//Methods that run the main loop
			void run();
			void sceneHandler();

			//Methods that manipulate scenes
			void searchEvent(SDL_Event _event);
			bool addScene(engine::Scene &scene);
			void restartScene(std::string sceneName);
			void setAttributes(std::string gameName,
					   int windowWidth,
					   int windowHeight,
					   int frameRate);

			/**
			 * @brief access the Timer.
			 *
			 * Used to get the private attribute Timer.
			 *
			 * @return the game timer.
			*/
			inline Timer& getTimer(){
				return timer;
			}

			/**
			 * @brief access the assets manager.
			 *
			 * Used to get the private attribute AssetsManager.
			 *
			 * @return the game assets manager.
			*/
			inline AssetsManager& getAssetsManager(){
				return assetsManager;
			}

			void changeScene(std::string sceneName);

		private:
			bool needToChangeScene; // Used to define if there's a Change Scene to occur.
			std::map<std::string, Scene *> sceneMap; // All Scenes of the Game.
			engine::Scene *currentScene; // Contain the Current Scene of the game.
			engine::Scene *lastScene; // must contain the Last Scene of the game.
			Timer timer; // Timer to control all Game's Time.
			int frameRate; // Frames per Second of the Game (FPS).
			float frameTime; // Time of each frame of the Game (miliseconds).
			AssetsManager assetsManager; // Manager to load, unload and reference assets.


		private:
			bool startAndStopScenes();

	};
}

#endif
