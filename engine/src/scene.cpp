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
#include <ctime>
#include <fstream>
#include <iostream>

using namespace engine;

Scene::Scene() {}

/*
 *@brief Contructor for the scene
 *
 * initializes the SceneName attribute
 */
Scene::Scene(std::string sceneName) {
	DEBUG("Creating Scene " << sceneName);
	this->sceneName = sceneName;
}

/*
 *@brief Method to initialize the gameObjectMap
 *
 *Initializes every key in the gameObjectMap
 */
void Scene::init(){
	DEBUG("Init Scene " << sceneName);
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
	DEBUG("Shutdown Scene " << sceneName)
	for (auto eachKey : mKeyList) {
		gameObjectMap[eachKey]->shutdown();
	}

	deleteKeyList();
}

/*
 *@brief Method to delete the key list
 */
void Scene::deleteKeyList() {
	DEBUG("Deleting key list");
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
	DEBUG("Adding game object" << gameObjectName);

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
	DEBUG("Getting game object" << gameObjectName);
	if (gameObjectMap.find(gameObjectName) == gameObjectMap.end()){
		errorLog(ErrorTypeScene::NULL_POINTER, "Scene::removeGameObject");
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
	DEBUG("Remove game object" << gameObjectName);
	if (gameObjectMap.find(gameObjectName) == gameObjectMap.end()){
		errorLog(ErrorTypeScene::NULL_POINTER, "Scene::removeGameObject");
		ERROR("Game object doesn't exist!");
	} else {
		//Nothing to do
	}

	gameObjectMap.erase(gameObjectName);
	mKeyList.remove(gameObjectName);
}


/*
 *@brief Method to log error messages.
 *
 * Writes a file with error message, function containing error and time.
 */
void Scene::errorLog(ErrorTypeScene code, std::string file){
    std::ofstream outfile;
    outfile.open("../errorLog.txt", std::ofstream::out | std::ofstream::app);
    time_t now = time(0);
    std::string dt = ctime(&now); //convert to string
	outfile << "Function: " + file << std::endl;
    outfile << "Date: " + dt << std::endl;

    switch(code) {
        case ErrorTypeScene::DIVI_BY_ZERO:
            outfile << "Error: division by zero" << std::endl;
            break;
        case ErrorTypeScene::EMPTY_STRING:
            outfile << "Error: empty String" << std::endl;
            break;
        case ErrorTypeScene::NULL_POINTER:
            outfile << "Error: null pointer" << std::endl;
            break;
        case ErrorTypeScene::WRONG_TYPE:
            outfile << "Error: wrong type" << std::endl;
			break;
		default:
			outfile << "Error: no matching file" << std::endl;
    }
    outfile << "===============" << std::endl;
    outfile.close();
}
