/**
* @file invisible_block.cpp
* @brief Purpose: Contains the InvisibleBlock class methods.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#include "invisible_block.hpp"

using namespace Azo;

InvisibleBlock::~InvisibleBlock(){}

/**
* @brief Constructor for InvisibleBlock class.
*
* Used for initializing class variables.
* @param name InvisibleBlock name.
* @param positionRelativeToParent Pair of doubles relative to position(range > 0).
* @param size Pair of doubles relative to size(range > 0).
*/
InvisibleBlock::InvisibleBlock(
	std::string name,
	std::pair<double, double> positionRelativeToParent,
	std::pair<double, double> size
) {
	DEBUG("Creating Blocks");

	mName = name;
	ASSERT(mName != "", "name can't be empty.");
	mPositionRelativeToParent = positionRelativeToParent;
	mSize = size;

	// 2.0f is used on the snippets below to halve the size while maintaining float type result.
	mHalfSize.first = mSize.first / 2.0f;
	mHalfSize.second = mSize.second / 2.0f;

	mCenter = mHalfSize; // Center is equal to the mHalfSize pair.

	// Initializing new ImageComponent with default invisible block image.
	mImage = new engine::ImageComponent(
		*this,
		"backgrounds/test_invisible_1.png",
		1
	);
	this->addComponent(*mImage);
	ASSERT(mImage != NULL, "mImage, ImageComponent can't be empty");
}

/**
* @brief Destructor class for InvisibleBlock.
*
* Used for shutting down ImageComponent so as to free memory when closing the game.
*/
void InvisibleBlock::shutdown() {
	DEBUG("Shutting down images");
	mImage->shutdown();
	mImage = NULL;
}
