

#include "image_component.hpp"
#include "game.hpp"

using namespace engine;

ImageComponent::ImageComponent(){}

ImageComponent::~ImageComponent(){}

ImageComponent::ImageComponent(GameObject &gameObject, std::string imagePath, double zoomFactor){
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->zoomFactor = zoomFactor;
}

ImageComponent::ImageComponent(GameObject &gameObject,
			       std::string imagePath,
			       double zoomFactor,
			       std::pair<double, double> position_relative_to_object){
	this->gameObject = &gameObject;
	this->imagePath = imagePath;
	this->zoomFactor = zoomFactor;
	m_position_relative_to_object = position_relative_to_object;
}

void ImageComponent::init(){
	// Check AssetsManager to see if image is already loaded.
	auto assets_image = Game::instance.GetAssetsManager().LoadImage(imagePath);

	imageTexture = assets_image->texture;

	componentWidth = assets_image->width * zoomFactor;
	componentHeight = assets_image->height * zoomFactor;

	gameObject->mSize.first = componentWidth;
	gameObject->mSize.second = componentHeight;

	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + m_position_relative_to_object.first),
		(int)(gameObject->mCurrentPosition.second + m_position_relative_to_object.second),
		componentWidth,
		componentHeight
	};

	renderQuad = {0, 0, componentWidth, componentHeight};

}


void ImageComponent::draw(){
	updateQuad();
	SDL_RenderCopy(
		Game::instance.sdl_elements.getCanvas(),
		imageTexture,
		&renderQuad,
		&canvasQuad
		);
}

void ImageComponent::updateQuad(){
	canvasQuad = {
		(int)(gameObject->mCurrentPosition.first + m_position_relative_to_object.first),
		(int)(gameObject->mCurrentPosition.second + m_position_relative_to_object.second),
		componentWidth,
		componentHeight
	};
}
