/**
 * @file: level_one.cpp
 * @brief Purpose: LevelOne class implementation
 *
 * GPL v3.0 Licence
 * Copyright (c) 2017 Azo
 *
 * Notice: TheAzo, TheAzoTeam
 * https://github.com/TecProg2018-2/Azo
*/

#include "level_one.hpp"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace Azo;

LevelOne::LevelOne() {}

//constructor that inits level one and its game objects
LevelOne::LevelOne(std::string name){
	ASSERT(name != "", "Name can`t be blank.");
	this->sceneName = name;
	createGameObjects();
}

//function that restarts level one
void LevelOne::restart(){
	gameObjectMap.clear();
	//To Do: add objects to be recreated one by one here, instead of recalling createGameObjects.
	createGameObjects();
}

//function that create all new game objects of level one in order.
void LevelOne::createGameObjects() {
	DEBUG("Creating LevelOne GameObjects.");
	//creating main game object of level one
	DEBUG("Creating LevelOne Object."); // technique 29
	mLevelOne = new engine::GameObject("level_one", std::make_pair(0, 0));
	//instantiates level one background
	mLevelBackground1 = new engine::ImageComponent(*mLevelOne, "backgrounds/level_one_part_one.png", 1);
	mLevelOne->addComponent(*mLevelBackground1);
	mLevelBackground2 = new engine::ImageComponent(*mLevelOne, "backgrounds/level_one_part_two.png", 1, std::make_pair(8188, 0));
	mLevelOne->addComponent(*mLevelBackground2);
	mLevelBackground3 = new engine::ImageComponent(*mLevelOne, "backgrounds/level_one_part_three.png", 1, std::make_pair(16379, 0));
	mLevelOne->addComponent(*mLevelBackground3);
	//instantiates level one audio, and its controller
	mAudioController = new engine::AudioController();
	mLevelTheme = new engine::AudioComponent(*mLevelOne, "audios/banjo.ogg", true, true);
	mAudioController->addAudio("tema_level_one", *mLevelTheme);
	mLevelOne->addComponent(*mAudioController);
	this->addGameObject(*mLevelOne);
	if(mLevelBackground1 == NULL) {
		errorCode = FunctionStatusLevelOne::NULLPOINTER;
		errorLog("LevelOne::findLevelBackground1"); // technique 32
	} else {
		errorCode = FunctionStatusLevelOne::SUCCESS;
	}
	if(mLevelBackground2 == NULL) {
		errorCode = FunctionStatusLevelOne::NULLPOINTER;
		errorLog("LevelOne::findLevelBackground2"); // technique 32
	} else {
		errorCode = FunctionStatusLevelOne::SUCCESS;
	}
	if(mLevelBackground3 == NULL) {
		errorCode = FunctionStatusLevelOne::NULLPOINTER;
		errorLog("LevelOne::findLevelBackground3"); // technique 32
	} else {
		errorCode = FunctionStatusLevelOne::SUCCESS;
	}
	if(mAudioController == NULL) {
    errorCode = FunctionStatusLevelOne::NULLPOINTER;
    errorLog("LevelOne::findAudioController"); // technique 32
  } else {
    errorCode = FunctionStatusLevelOne::SUCCESS;
  }
	if(mLevelTheme == NULL) {
    errorCode = FunctionStatusLevelOne::NULLPOINTER;
    errorLog("LevelOne::findLevelTheme"); // technique 32
  } else {
    errorCode = FunctionStatusLevelOne::SUCCESS;
  }
	//instantiates level one ground
	DEBUG("Creating ground."); //technique 29
	mGround = new Obstacle("ground", std::make_pair(0, 404.5), ObstacleType::GROUND);
	this->addGameObject(*mGround);

	//from here, all block instantiates the level game objects in order
	DEBUG("Creating obstacle car 1."); //technique 29
	mObstacleCar1 = new Obstacle("obstacle_car_1", std::make_pair(1135, 300), ObstacleType::WESTERN_CAR);
	this->addGameObject(*mObstacleCar1);

	DEBUG("Creating spike 1."); //technique 29
	mSpike1 = new Obstacle("obstacle_spike_1", std::make_pair(1349, 340), ObstacleType::WESTERN_SPIKE);
	this->addGameObject(*mSpike1);

	DEBUG("Creating obstacle box 0_1."); //technique 29
	mObstacleBox01 = new Obstacle("obstacle_box_0_1", std::make_pair(1309, 310), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox01);

	DEBUG("Creating obstacle aerial 1 - box."); //technique 29
	mObstacleAerial1 = new Obstacle("obstacle_aerial_1", std::make_pair(1350, 250), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleAerial1);

	DEBUG("Creating part 1."); //technique 29
	mPart1 = new Obstacle("part_1", std::make_pair(1500, 80), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart1);

	DEBUG("Creating obstacle aerial 2 - post."); //technique 29
	mObstacleAerial2 = new Obstacle("obstacle_aerial_2", std::make_pair(1755, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial2);

	DEBUG("Creating part 1_1."); //technique 29
	mPart1_1 = new Obstacle("part_1_1", std::make_pair(1890, 370), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart1_1);

	DEBUG("Creating obstacle aerial 3 - post."); //technique 29
	mObstacleAerial3 = new Obstacle("obstacle_aerial_3", std::make_pair(2030, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial3);

	DEBUG("Creating part 2."); //technique 29
	mPart2 = new Obstacle("part_2", std::make_pair(2225, 200), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart2);

	DEBUG("Creating obstacle box 1."); //technique 29
	mObstacleBox1 = new Obstacle("obstacle_box_1", std::make_pair(2225, 300), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox1);

	DEBUG("Creating obstacle box 2."); //technique 29
	mObstacleBox2 = new Obstacle("obstacle_box_2", std::make_pair(2645, 300), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox2);

	DEBUG("Creating obstacle box 2_1."); //technique 29
	mObstacleBox21 = new Obstacle("obstacle_box_2_1", std::make_pair(2779, 300), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox21);

	DEBUG("Creating obstacle aerial 4 - box."); //technique 29
	mObstacleAerial4 = new Obstacle("obstacle_aerial_4", std::make_pair(2820, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleAerial4);

	DEBUG("Creating part 3."); //technique 29
	mPart3 = new Obstacle("part_3", std::make_pair(2975, 310), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart3);

	DEBUG("Creating obstacle car 2."); //technique 29
	mObstacleCar2 = new Obstacle("obstacle_car_2", std::make_pair(3040, 300), ObstacleType::WESTERN_CAR);
	this->addGameObject(*mObstacleCar2);

	DEBUG("Creating part 4."); //technique 29
	mPart4 = new Obstacle("part_4", std::make_pair(3285, 100), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart4);

	DEBUG("Creating obstacle aerial 5 - post."); //technique 29
	mObstacleAerial5 = new Obstacle("obstacle_aerial_5", std::make_pair(3510, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial5);

	DEBUG("Creating part 4_1."); //technique 29
	mPart41 = new Obstacle("part_4_1", std::make_pair(3655, 370), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart41);

	DEBUG("Creating obstacle aerial 6 - post."); //technique 29
	mObstacleAerial6 = new Obstacle("obstacle_aerial_6", std::make_pair(3675, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial6);

	DEBUG("Creating part 5."); //technique 29
	mPart5 = new Obstacle("part_5", std::make_pair(3975, 200), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart5);

	DEBUG("Creating obstacle box 3."); //technique 29
	mObstacleBox3 = new Obstacle("obstacle_box_3", std::make_pair(3975, 300), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox3);

	DEBUG("Creating obstacle rock 1"); //technique 29
	mObstacleRock1 = new Obstacle("obstacle_rock_1", std::make_pair(4300, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock1);

	DEBUG("Creating part 6."); //technique 29
	mPart6 = new Obstacle("part_6", std::make_pair(4460, 350), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart6);

	DEBUG("Creating obstacle aerial 7 - post."); //technique 29
	mObstacleAerial7 = new Obstacle("obstacle_aerial_7", std::make_pair(4660, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial7);

	DEBUG("Creating obstacle rock 2"); //technique 29
	mObstacleRock2 = new Obstacle("obstacle_rock_2", std::make_pair(4855, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock2);

	DEBUG("Creating part 7."); //technique 29
	mPart7 = new Obstacle("part_7", std::make_pair(5015, 350), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart7);

	DEBUG("Creating obstacle aerial 8 - post."); //technique 29
	mObstacleAerial8 = new Obstacle("obstacle_aerial_8", std::make_pair(5215, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial8);

	DEBUG("Creating part 7_1."); //technique 29
	mPart7_1 = new Obstacle("part_7_1", std::make_pair(5360, 370), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart7_1);

	DEBUG("Creating obstacle aerial 9 - post."); //technique 29
	mObstacleAerial9 = new Obstacle("obstacle_aerial_9", std::make_pair(5380, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial9);

	DEBUG("Creating part 8."); //technique 29
	mPart8 = new Obstacle("part_8", std::make_pair(5570, 200), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart8);

	DEBUG("Creating part 9."); //technique 29
	mPart9 = new Obstacle("part_9", std::make_pair(6100, 370), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart9);

	DEBUG("Creating obstacle aerial 10 - post."); //technique 29
	mObstacleAerial10 = new Obstacle("obstacle_aerial_10", std::make_pair(6150, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial10);

	DEBUG("Creating part 10."); //technique 29
	mPart10 = new Obstacle("part_10", std::make_pair(6340, 200), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart10);

	DEBUG("Creating obstacle car 3."); //technique 29
	mObstacleCar3 = new Obstacle("obstacle_car_3", std::make_pair(6700, 300), ObstacleType::WESTERN_CAR);
	this->addGameObject(*mObstacleCar3);

	DEBUG("Creating part 11."); //technique 29
	mPart11 = new Obstacle("part_11", std::make_pair(6890, 80), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart11);

	DEBUG("Creating obstacle aerial 11 - post."); //technique 29
	mObstacleAerial11 = new Obstacle("obstacle_aerial_11", std::make_pair(7005, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial11);

	DEBUG("Creating part 12."); //technique 29
	mPart12 = new Obstacle("part_12", std::make_pair(7160, 370), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart12);

	DEBUG("Creating obstacle aerial 12 - post."); //technique 29
	mObstacleAerial12 = new Obstacle("obstacle_aerial_12", std::make_pair(7180, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial12);

	DEBUG("Creating part 13."); //technique 29
	mPart13 = new Obstacle("part_13", std::make_pair(7540, 220), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart13);

	DEBUG("Creating part 14."); //technique 29
	mPart14 = new Obstacle("part_14", std::make_pair(7830, 220), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart14);

	DEBUG("Creating part 15."); //technique 29
	mPart15 = new Obstacle("part_15", std::make_pair(8040, 220), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart15);

	DEBUG("Creating part 16."); //technique 29
	mPart16 = new Obstacle("part_16", std::make_pair(8390, 200), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart16);

	DEBUG("Creating obstacle aerial 13 - post."); //technique 29
	mObstacleAerial13 = new Obstacle("obstacle_aerial_13", std::make_pair(8570, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial13);

	DEBUG("Creating spike 2."); //technique 29
	mSpike2 = new Obstacle("obstacle_spike_2", std::make_pair(8880, 330), ObstacleType::WESTERN_SPIKE);
	this->addGameObject(*mSpike2);

	DEBUG("Creating obstacle box 4."); //technique 29
	mObstacleBox4 = new Obstacle("obstacle_box_4", std::make_pair(8820, 300), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox4);

	DEBUG("Creating spike 3."); //technique 29
	mSpike3 = new Obstacle("obstacle_spike_3", std::make_pair(9120, 330), ObstacleType::WESTERN_SPIKE);
	this->addGameObject(*mSpike3);

	DEBUG("Creating obstacle box 5."); //technique 29
	mObstacleBox5 = new Obstacle("obstacle_box_5", std::make_pair(9117, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleBox5);

	DEBUG("Creating spike 4."); //technique 29
	mSpike4 = new Obstacle("obstacle_spike_4", std::make_pair(9360, 330), ObstacleType::WESTERN_SPIKE);
	this->addGameObject(*mSpike4);

	DEBUG("Creating obstacle box 6."); //technique 29
	mObstacleBox6 = new Obstacle("obstacle_box_6", std::make_pair(9358, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleBox6);

	DEBUG("Creating obstacle aerial 14 - box."); //technique 29
	mObstacleAerial14 = new Obstacle("obstacle_aerial_14", std::make_pair(9358, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleAerial14);

	DEBUG("Creating obstacle box 7."); //technique 29
	mObstacleBox7 = new Obstacle("obstacle_box_7", std::make_pair(9599, 300), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleBox7);

	DEBUG("Creating obstacle aerial 15 - box."); //technique 29
	mObstacleAerial15 = new Obstacle("obstacle_aerial_15", std::make_pair(9599, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleAerial15);

	DEBUG("Creating part 17."); //technique 29
	mPart17 = new Obstacle("part_17", std::make_pair(9770, 350), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart17);

	DEBUG("Creating obstacle rock 3"); //technique 29
	mObstacleRock3 = new Obstacle("obstacle_rock_3", std::make_pair(10070, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock3);

	DEBUG("Creating obstacle box 8."); //technique 29
	mObstacleBox8 = new Obstacle("obstacle_box_8", std::make_pair(10480, 310), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox8);

	DEBUG("Creating part 18."); //technique 29
	mPart18 = new Obstacle("part_18", std::make_pair(10560, 200), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart18);

	DEBUG("Creating obstacle aerial 16 - post."); //technique 29
	mObstacleAerial16 = new Obstacle("obstacle_aerial_16", std::make_pair(10730, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial16);

	DEBUG("Creating obstacle rock 4"); //technique 29
	mObstacleRock4 = new Obstacle("obstacle_rock_4", std::make_pair(10930, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock4);

	DEBUG("Creating obstacle rock 5"); //technique 29
	mObstacleRock5 = new Obstacle("obstacle_rock_5", std::make_pair(11180, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock5);

	DEBUG("Creating obstacle aerial 17 - post."); //technique 29
	mObstacleAerial17 = new Obstacle("obstacle_aerial_17", std::make_pair(11465, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial17);

	DEBUG("Creating obstacle box 9."); //technique 29
	mObstacleBox9 = new Obstacle("obstacle_box_9", std::make_pair(11850, 300), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox9);

	DEBUG("Creating obstacle box 10."); //technique 29
	mObstacleBox10 = new Obstacle("obstacle_box_10", std::make_pair(11984, 300), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox10);

	DEBUG("Creating obstacle aerial 18 - box."); //technique 29
	mObstacleAerial18 = new Obstacle("obstacle_aerial_18", std::make_pair(12025, 240), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleAerial18);

	DEBUG("Creating part 19."); //technique 29
	mPart19 = new Obstacle("part_19", std::make_pair(12180, 340), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart19);

	DEBUG("Creating obstacle aerial 19 - post."); //technique 29
	mObstacleAerial19 = new Obstacle("obstacle_aerial_19", std::make_pair(12370, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial19);

	DEBUG("Creating obstacle rock 6"); //technique 29
	mObstacleRock6 = new Obstacle("obstacle_rock_6", std::make_pair(12600, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock6);

	DEBUG("Creating obstacle rock 7"); //technique 29
	mObstacleRock7 = new Obstacle("obstacle_rock_7", std::make_pair(12850, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock7);

	DEBUG("Creating obstacle rock 8"); //technique 29
	mObstacleRock8 = new Obstacle("obstacle_rock_8", std::make_pair(13100, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock8);

	DEBUG("Creating obstacle car 4."); //technique 29
	mObstacleCar4 = new Obstacle("obstacle_car_4", std::make_pair(13570, 300), ObstacleType::WESTERN_CAR);
	this->addGameObject(*mObstacleCar4);

	DEBUG("Creating part 20."); //technique 29
	mPart20 = new Obstacle("part_20", std::make_pair(13860, 70), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart20);

	DEBUG("Creating obstacle car 5."); //technique 29
	mObstacleCar5 = new Obstacle("obstacle_car_5", std::make_pair(14200, 300), ObstacleType::WESTERN_CAR);
	this->addGameObject(*mObstacleCar5);

	DEBUG("Creating spike 5."); //technique 29
	mSpike5 = new Obstacle("obstacle_spike_5", std::make_pair(14414, 340), ObstacleType::WESTERN_SPIKE);
	this->addGameObject(*mSpike5);

	DEBUG("Creating obstacle box 11."); //technique 29
	mObstacleBox11 = new Obstacle("obstacle_box_11", std::make_pair(14374, 310), ObstacleType::WESTERN_BOX);
	this->addGameObject(*mObstacleBox11);

	DEBUG("Creating obstacle aerial 20 - box."); //technique 29
	mObstacleAerial20 = new Obstacle("obstacle_aerial_20", std::make_pair(14415, 250), ObstacleType::WESTERN_RAISED_BOX);
	this->addGameObject(*mObstacleAerial20);

	DEBUG("Creating part 21."); //technique 29
	mPart21 = new Obstacle("part_21", std::make_pair(14565, 80), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart21);

	DEBUG("Creating obstacle aerial 21 - post."); //technique 29
	mObstacleAerial21 = new Obstacle("obstacle_aerial_21", std::make_pair(14820, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial21);

	DEBUG("Creating obstacle rock 9"); //technique 29
	mObstacleRock9 = new Obstacle("obstacle_rock_9", std::make_pair(15000, 340), ObstacleType::WESTERN_ROCK);
	this->addGameObject(*mObstacleRock9);

	DEBUG("Creating obstacle aerial 22 - post."); //technique 29
	mObstacleAerial22 = new Obstacle("obstacle_aerial_22", std::make_pair(15300, 185), ObstacleType::WESTERN_POST);
	this->addGameObject(*mObstacleAerial22);

	DEBUG("Creating part 22."); //technique 29
	mPart22 = new Obstacle("part_22", std::make_pair(15530, 140), ObstacleType::MACHINE_PART);
	this->addGameObject(*mPart22);
	//instantiates player at level one
	DEBUG("Creating Player."); //technique 29
	mPlayer = new Player("player", std::make_pair(165, 280));
	this->addGameObject(*mPlayer);

	createEndingScreen();
	addLevelParents();

	mLevelCode = new LevelOneCode(*mLevelOne);
	mLevelOne->addComponent(*mLevelCode);
}

//function that instantiate game over screen/menu
void LevelOne::createEndingScreen() {
	mWinningScreenObject = new engine::GameObject("winning_screen", std::make_pair(0, 0));
	mWinningScreenObject->mObjectState = engine::ObjectState::DISABLED;
	mWinningScreen = new engine::BackgroundComponent(*mWinningScreenObject, "general_images/tela_vitoria.png");
	mWinningScreenObject->addComponent(*mWinningScreen);
	this->addGameObject(*mWinningScreenObject);

	mLosingPartsScreenObject = new engine::GameObject("losing_parts", std::make_pair(0, 0));
	mLosingPartsScreenObject->mObjectState = engine::ObjectState::DISABLED;
	mLosingPartsScreen = new engine::BackgroundComponent(*mLosingPartsScreenObject, "general_images/tela_derrota.png");
	mLosingPartsScreenObject->addComponent(*mLosingPartsScreen);
	this->addGameObject(*mLosingPartsScreenObject);

	mLosingDeathScreenObject = new engine::GameObject("losing_death", std::make_pair(0, 0));
	mLosingDeathScreenObject->mObjectState = engine::ObjectState::DISABLED;
	mLosingDeathScreen = new engine::BackgroundComponent(*mLosingDeathScreenObject, "general_images/tela_morte.png");
	mLosingDeathScreenObject->addComponent(*mLosingDeathScreen);
	this->addGameObject(*mLosingDeathScreenObject);

	mArrow = new engine::GameObject("arrow", std::make_pair(0, 0));
	mArrow->mObjectState = engine::ObjectState::DISABLED;
	mArrowImage = new engine::ImageComponent(*mArrow, "general_images/arrow.png", 1);
	mArrow->addComponent(*mArrowImage);
	this->addGameObject(*mArrow);
}

//function that adds level one parents
void LevelOne::addLevelParents() {
	DEBUG("adding level parents."); //technique 29
	mLevelOne->mParentList.push_back(mObstacleCar1);
	mLevelOne->mParentList.push_back(mObstacleAerial1);
	mLevelOne->mParentList.push_back(mObstacleBox01);
	mLevelOne->mParentList.push_back(mSpike1);
	mLevelOne->mParentList.push_back(mPart1);
	mLevelOne->mParentList.push_back(mObstacleAerial2);
	mLevelOne->mParentList.push_back(mPart1_1);
	mLevelOne->mParentList.push_back(mObstacleAerial3);
	mLevelOne->mParentList.push_back(mPart2);
	mLevelOne->mParentList.push_back(mObstacleBox1);
	mLevelOne->mParentList.push_back(mObstacleBox2);
	mLevelOne->mParentList.push_back(mObstacleAerial4);
	mLevelOne->mParentList.push_back(mObstacleBox21);
	mLevelOne->mParentList.push_back(mPart3);
	mLevelOne->mParentList.push_back(mObstacleCar2);
	mLevelOne->mParentList.push_back(mPart4);
	mLevelOne->mParentList.push_back(mObstacleAerial5);
	mLevelOne->mParentList.push_back(mPart41);
	mLevelOne->mParentList.push_back(mObstacleAerial6);
	mLevelOne->mParentList.push_back(mPart5);
	mLevelOne->mParentList.push_back(mObstacleBox3);
	mLevelOne->mParentList.push_back(mObstacleRock1);
	mLevelOne->mParentList.push_back(mPart6);
	mLevelOne->mParentList.push_back(mObstacleAerial7);
	mLevelOne->mParentList.push_back(mObstacleRock2);
	mLevelOne->mParentList.push_back(mPart7);
	mLevelOne->mParentList.push_back(mObstacleAerial8);
	mLevelOne->mParentList.push_back(mPart7_1);
	mLevelOne->mParentList.push_back(mObstacleAerial9);
	mLevelOne->mParentList.push_back(mPart8);
	mLevelOne->mParentList.push_back(mPart9);
	mLevelOne->mParentList.push_back(mObstacleAerial10);
	mLevelOne->mParentList.push_back(mPart10);
	mLevelOne->mParentList.push_back(mObstacleCar3);
	mLevelOne->mParentList.push_back(mPart11);
	mLevelOne->mParentList.push_back(mObstacleAerial11);
	mLevelOne->mParentList.push_back(mPart12);
	mLevelOne->mParentList.push_back(mObstacleAerial12);
	mLevelOne->mParentList.push_back(mPart13);
	mLevelOne->mParentList.push_back(mPart14);
	mLevelOne->mParentList.push_back(mPart15);
	mLevelOne->mParentList.push_back(mPart16);
	mLevelOne->mParentList.push_back(mObstacleAerial13);
	mLevelOne->mParentList.push_back(mSpike2);
	mLevelOne->mParentList.push_back(mObstacleBox4);
	mLevelOne->mParentList.push_back(mSpike3);
	mLevelOne->mParentList.push_back(mObstacleBox5);
	mLevelOne->mParentList.push_back(mSpike4);
	mLevelOne->mParentList.push_back(mObstacleBox6);
	mLevelOne->mParentList.push_back(mObstacleAerial14);
	mLevelOne->mParentList.push_back(mObstacleBox7);
	mLevelOne->mParentList.push_back(mObstacleAerial15);
	mLevelOne->mParentList.push_back(mPart17);
	mLevelOne->mParentList.push_back(mObstacleRock3);
	mLevelOne->mParentList.push_back(mObstacleBox8);
	mLevelOne->mParentList.push_back(mPart18);
	mLevelOne->mParentList.push_back(mObstacleAerial16);
	mLevelOne->mParentList.push_back(mObstacleRock4);
	mLevelOne->mParentList.push_back(mObstacleRock5);
	mLevelOne->mParentList.push_back(mObstacleAerial17);
	mLevelOne->mParentList.push_back(mObstacleBox9);
	mLevelOne->mParentList.push_back(mObstacleBox10);
	mLevelOne->mParentList.push_back(mObstacleAerial18);
	mLevelOne->mParentList.push_back(mPart19);
	mLevelOne->mParentList.push_back(mObstacleAerial19);
	mLevelOne->mParentList.push_back(mObstacleRock6);
	mLevelOne->mParentList.push_back(mObstacleRock7);
	mLevelOne->mParentList.push_back(mObstacleRock8);
	mLevelOne->mParentList.push_back(mObstacleCar4);
	mLevelOne->mParentList.push_back(mPart20);
	mLevelOne->mParentList.push_back(mObstacleCar5);
	mLevelOne->mParentList.push_back(mObstacleAerial20);
	mLevelOne->mParentList.push_back(mObstacleBox11);
	mLevelOne->mParentList.push_back(mSpike5);
	mLevelOne->mParentList.push_back(mPart21);
	mLevelOne->mParentList.push_back(mObstacleAerial21);
	mLevelOne->mParentList.push_back(mObstacleRock9);
	mLevelOne->mParentList.push_back(mObstacleAerial22);
	mLevelOne->mParentList.push_back(mPart22);

	mLevelOne->mParentList.push_back(mWinningScreenObject);
	mLevelOne->mParentList.push_back(mLosingPartsScreenObject);
	mLevelOne->mParentList.push_back(mLosingDeathScreenObject);
	mLevelOne->mParentList.push_back(mArrow);

	mLevelOne->mParentList.push_back(mPlayer);
	mLevelOne->mParentList.push_back(mGround);
}

void LevelOne::errorLog(std::string file){ // technique 32
    std::ofstream outfile;
    outfile.open("../errorLog.txt", std::ofstream::out | std::ofstream::app);
    time_t now = time(0);
  	std::string dt = ctime(&now);
    std::string message = "===============\n";
  	message += "Function: " + file + "\n";
    message += "Date: " + dt + "\n";

    switch(errorCode) {
        case FunctionStatusLevelOne::DIVIBYZERO:
            message += "Error: division by zero\n";
            break;
        case FunctionStatusLevelOne::EMPTYSTRING:
            message += "empty String\n";
            break;
        case FunctionStatusLevelOne::NULLPOINTER:
            message += "null pointer\n";
            break;
    		case FunctionStatusLevelOne::WRONGTYPE:
            message += "wrong type\n";
            break;
        default:
            message = "";
      			break;
    }
    outfile << message;
    outfile.close();
}
