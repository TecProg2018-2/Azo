/**
* @file background_component.cpp
* @brief Purpose: Contains the components of the background images.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main game component its declaration and state.
*/
#include "background_component.hpp"
#include "game_object.hpp"
#include "game.hpp"
#include "sdl.hpp"

using namespace engine;

const int COMPONENT_X = 0;
const int COMPONENT_Y = 0;

BackgroundComponent::BackgroundComponent(){}

BackgroundComponent::BackgroundComponent(std::string imagePath){
	this->imagePath = imagePath;
	this->componentState = State::ENABLED;
}

BackgroundComponent::BackgroundComponent(
	GameObject & gameObject, std::string imagePath
){
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->componentState = State::ENABLED;
}

BackgroundComponent::~BackgroundComponent(){}

void BackgroundComponent::init(){
	//DEBUG("BackgroundComponent::init method.");
	auto assetsImage = Game::instance.getAssetsManager().LoadImage(imagePath);

	imageTexture = assetsImage->texture;
	componentWidth = assetsImage->width;
	componentHeight = assetsImage->height;

	renderQuad = {COMPONENT_X, COMPONENT_Y, componentWidth, componentHeight};
}

void BackgroundComponent::shutdown(){
	// Terminate Texture
	imageTexture = NULL;
}

void BackgroundComponent::draw(){
	//DEBUG("BackgroundComponent::draw method.");
	SDL_RenderCopy(
		Game::instance.sdlElements.getCanvas(),
		imageTexture,
		&renderQuad,
		NULL
	);
}
