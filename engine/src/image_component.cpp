/**
* @file image_component.cpp
* @brief Purpose: Contains the components of image fo the game.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* Notice: TheAzo, TheAzoTeam
* https://github.com/TecProg2018-2/Azo
*
* This file implements the main game component its declaration and state.
*/
#include "image_component.hpp"
#include "game.hpp"

using namespace engine;

ImageComponent::ImageComponent() {}

ImageComponent::~ImageComponent() {}

ImageComponent::ImageComponent(
	GameObject &gameObject,
	std::string imagePath,
	double zoomFactor
) {
	//This function paragraph creates the image component according
	//to the received gameObject
	DEBUG("Calling ImageComponent::ImageComponent");
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");
	ASSERT(imagePath != "", "ImageComponent::ImageComponent, imagePath is empty.");
	ASSERT(zoomFactor < 100.0, "zoomFactor cant be bigger than 100.");
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->zoomFactor = zoomFactor;
}

ImageComponent::ImageComponent(
	GameObject &gameObject,
	std::string imagePath,
	double zoomFactor,
	std::pair<double, double> positionRelativeToObject
) {
	//This function paragraph creates the image component according
	//to the received gameObject, but relating it to the relative
	//position of the object
	DEBUG("Calling ImageComponent::ImageComponent");
	ASSERT(&gameObject != NULL, "The gameObject can't be null.");
	ASSERT(imagePath != "", "ImageComponent::ImageComponent, imagePath is empty.");
	ASSERT(zoomFactor < 100.0, "zoomFactor cant be bigger than 100.");
	ASSERT(positionRelativeToObject.first >= 0.0, "The relative position must be bigger than zero.");
	ASSERT(positionRelativeToObject.second >= 0.0, "The relative position must be bigger than zero.");
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->zoomFactor = zoomFactor;
	mPositionRelativeToObject = positionRelativeToObject;
}

void ImageComponent::init() {
	DEBUG("Calling ImageComponent::init");

	//Check AssetsManager to see if image is already loaded.
	auto assetsImage = Game::instance.getAssetsManager().LoadImage(imagePath);
	ASSERT(
		assetsImage != NULL,
		"ImageComponent::init, The assetsImage can't be null."
	);

	imageTexture = assetsImage->texture;

	componentWidth = assetsImage->width * zoomFactor;
	componentHeight = assetsImage->height * zoomFactor;

	gameObject->mSize.first = componentWidth;
	gameObject->mSize.second = componentHeight;


	//initiating canvas quad.
	//This function paragraph initiates the canvasQuad values
	//according to the current and relative position of the object
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		componentWidth,
		componentHeight
	};


	//This function paragraph generates the renderQuad with
	//the current component and its informations
	renderQuad = {0, 0, componentWidth, componentHeight};
}


void ImageComponent::draw() {
	//This function paragraph is responsible for drawing the image component
	//DEBUG("Calling ImageComponent::draw");
	updateQuad();
	SDL_RenderCopy(
		Game::instance.sdlElements.getCanvas(),
		imageTexture,
		&renderQuad,
		&canvasQuad
	);
}

void ImageComponent::updateQuad() {
	//Updating canvas quad.
	//This function paragraph updates the canvasQuad values
	//according to the current and relative position of the object
	//DEBUG("Calling ImageComponent::updateQuad");
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + mPositionRelativeToObject.first),
		(int)(gameObject->mCurrentPosition.second + mPositionRelativeToObject.second),
		componentWidth,
		componentHeight
	};
}
