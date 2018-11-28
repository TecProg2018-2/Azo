/**
 * @file: level_one.hpp
 * @brief Purpose: LevelOne class declaration
 *
 * GPL v3.0 Licence
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
*/

#ifndef LEVEL_ONE
#define LEVEL_ONE

#include "scene.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "level_one_code.hpp"
#include "audio_controller.hpp"

namespace Azo {
	/**
   * @brief Class for possible errors types.
   *
   * Enum class used to differentiate errors
   */
  enum class FunctionStatusLevelOne {
    DIVIBYZERO,
    NULLPOINTER,
    EMPTYSTRING,
    WRONGTYPE,
    SUCCESS,
  };

	/**
	* @brief LevelOne class
	* This class is used to manage creation and behavior of
	* game objects, menus and parents.
	*/
	class LevelOne : public engine::Scene {
		private:
			//pointers that refers to the background of diferent gameover screens/menus
			engine::BackgroundComponent *mWinningScreen;
			engine::BackgroundComponent *mLosingPartsScreen;
			engine::BackgroundComponent *mLosingDeathScreen;
			//pointers that refers to the game object of diferent gameover screens/menus
			engine::GameObject *mWinningScreenObject;
			engine::GameObject *mLosingPartsScreenObject;
			engine::GameObject *mLosingDeathScreenObject;
			//pointers that refers to the selection arrow of some menus
			engine::GameObject *mArrow;
			engine::ImageComponent *mArrowImage;
			//pointers that refers to different backgrounds of the game
			engine::ImageComponent *mLevelBackground1;
			engine::ImageComponent *mLevelBackground2;
			engine::ImageComponent *mLevelBackground3;

			engine::GameObject *mLevelOne;	//pointer that refer to level game object. Contains things such as background, theme, etc.

			// Add new components to level one here.

			engine::AudioController *mAudioController; //pointer that refers to the controller of the audio of level one
			engine::AudioComponent *mLevelTheme; //pointer that refers to the audio that plays at level one

			LevelOneCode *mLevelCode;
			Player *mPlayer;

			// Add obstacles here

			//pointers that refers to obstacles' game objects
			Obstacle *mObstacleCar1;
			Obstacle *mSpike1;
			Obstacle *mObstacleAerial1;
			Obstacle *mPart1;
			Obstacle *mObstacleAerial2;
			Obstacle *mObstacleAerial3;
			Obstacle *mPart2;
			Obstacle *mObstacleBox1;
			Obstacle *mObstacleBox2;
			Obstacle *mObstacleAerial4;
			Obstacle *mPart3;
			Obstacle *mObstacleCar2;
			Obstacle *mPart4;
			Obstacle *mObstacleAerial5;
			Obstacle *mObstacleAerial6;
			Obstacle *mPart5;
			Obstacle *mObstacleBox3;
			Obstacle *mObstacleRock1;
			Obstacle *mPart6;
			Obstacle *mObstacleAerial7;
			Obstacle *mObstacleRock2;
			Obstacle *mPart7;
			Obstacle *mObstacleAerial8;
			Obstacle *mObstacleAerial9;
			Obstacle *mPart8;
			Obstacle *mPart1_1;
			Obstacle *mPart41;
			Obstacle *mPart7_1;
			Obstacle *mPart9;
			Obstacle *mObstacleAerial10;
			Obstacle *mPart10;
			Obstacle *mObstacleBox01;
			Obstacle *mObstacleBox21;
			Obstacle *mObstacleCar3;
			Obstacle *mPart11;
			Obstacle *mObstacleAerial11;
			Obstacle *mPart12;
			Obstacle *mObstacleAerial12;
			Obstacle *mPart13;
			Obstacle *mPart14;
			Obstacle *mPart15;
			Obstacle *mPart16;
			Obstacle *mObstacleAerial13;
			Obstacle *mSpike2;
			Obstacle *mObstacleBox4;
			Obstacle *mSpike3;
			Obstacle *mObstacleBox5;
			Obstacle *mSpike4;
			Obstacle *mObstacleBox6;
			Obstacle *mObstacleAerial14;
			Obstacle *mObstacleBox7;
			Obstacle *mObstacleAerial15;
			Obstacle *mPart17;
			Obstacle *mObstacleRock3;
			Obstacle *mObstacleBox8;
			Obstacle *mPart18;
			Obstacle *mObstacleAerial16;
			Obstacle *mObstacleRock4;
			Obstacle *mObstacleRock5;
			Obstacle *mObstacleAerial17;
			Obstacle *mObstacleBox9;
			Obstacle *mObstacleBox10;
			Obstacle *mObstacleAerial18;
			Obstacle *mObstacleAerial19;
			Obstacle *mPart19;
			Obstacle *mObstacleRock6;
			Obstacle *mObstacleRock7;
			Obstacle *mObstacleRock8;
			Obstacle *mObstacleCar4;
			Obstacle *mPart20;
			Obstacle *mObstacleCar5;
			Obstacle *mSpike5;
			Obstacle *mObstacleBox11;
			Obstacle *mObstacleAerial20;
			Obstacle *mPart21;
			Obstacle *mObstacleAerial21;
			Obstacle *mObstacleRock9;
			Obstacle *mObstacleAerial22;
			Obstacle *mPart22;
			Obstacle *mGround;
			FunctionStatusLevelOne errorCode = FunctionStatusLevelOne::SUCCESS;

		public:
			LevelOne();
			LevelOne(std::string name);
			void restart(); //function that restarts level one

		private:
			void createGameObjects(); //function that add new objects to level one
			void createSceneGeneral();
			void createObstacleCar();
			void createObstacleSpike();
			void createObstacleBox();
			void createObstacleAerial();
			void createPart();
			void createObstacleRock();
			void createEndingScreen(); //functon that add the ending menu to level one
			void addLevelParents(); //function that add parents to level one. Use after adding objects that collide.
			void errorLog(std::string file);

	};
}

#endif
