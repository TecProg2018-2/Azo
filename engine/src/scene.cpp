/**
 * @file scene.cpp
 * @brief Purpose: Contains all the methods from the Scene class.
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
 */
#include "scene.hpp"

using namespace engine;

Scene::Scene() {}

/*
 *@brief Contructor for the scene
 *
 * initializes the SceneName attribute
 */
Scene::Scene(std::string sceneName) {
	this->sceneName = sceneName;
}

/*
 *@brief Method to initialize the gameObjectMap
 *
 *Initializes every key in the gameObjectMap
 */
void Scene::init(){

	for (auto eachKey : mKeyList) {
		gameObjectMap[eachKey]->init();
	}
}

/*
 *@brief Method to shutdown all game objects
 *
 *passes every object in the gameObjectMap to the shutdown method
 */
void Scene::shutdown() {

	for (auto eachKey : mKeyList) {
		gameObjectMap[eachKey]->shutdown();
	}

	deleteKeyList();
}

/*
 *@brief Method to delete the key list
 */
void Scene::deleteKeyList() {
	mKeyList.erase(mKeyList.begin(), mKeyList.end());
}

/*
 *@brief Method to draw scene on screen
 *
 *Passes every gameObjectin the gameObjectMap to the draw() method
 */
void Scene::draw() {

	for (auto eachKey : mKeyList) {
		if(gameObjectMap[eachKey]->mObjectState == ObjectState::ENABLED) {
			gameObjectMap[eachKey]->draw();
		} else {
			//Nothing to do
		}
	}
}

/*
 *@brief Methos to update the code of the scene
 *
 *Passes every element of the gameObjectMap to the updateCode() method.
 */
void Scene::updateCode(){

	for(auto eachKey : mKeyList){
		if (gameObjectMap[eachKey]->mObjectState == ObjectState::ENABLED){
			gameObjectMap[eachKey]->updateCode();
		} else {
			//Nothing to do
		}
	}
}

/*
 *@brief Method to restart scene.
 *
 *@returns "void".
 */
void Scene::restart(){}

/*
 *@brief Method to add a new game object
 *
 *adds a new game object in the gameObjectMap
 */
void Scene::addGameObject(GameObject &gameObject){

	auto gameObjectName = gameObject.mName;

	if (gameObjectMap.find(gameObjectName) != gameObjectMap.end()){
		ERROR("Game object already exists!");
	} else {
		//Nothing to do
	}

	gameObjectMap[gameObjectName] = &gameObject;
	mKeyList.push_back(gameObjectName);
}

/*
 *@brief Method to retrieve a gameObject
 *
 *returns a gameObject
 */
GameObject & Scene::getGameObject(std::string &gameObjectName){

	if (gameObjectMap.find(gameObjectName) == gameObjectMap.end()){
		ERROR("Game object doesn't exist!");
	} else {
		//Nothing to do
	}

	return *gameObjectMap[gameObjectName];
}

/*
 *@method to remove a gameObject
 *
 *Removes a gameObject from the gameObjectMap
 */
void Scene::removeGameObject(std::string &gameObjectName){

	if (gameObjectMap.find(gameObjectName) == gameObjectMap.end()){
		ERROR("Game object doesn't exist!");
	} else {
		//Nothing to do
	}

	gameObjectMap.erase(gameObjectName);
	mKeyList.remove(gameObjectName);
}
