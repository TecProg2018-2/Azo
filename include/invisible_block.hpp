/**
* @file invisible_block.hpp
* @brief Purpose: Contains the InvisibleBlock class declaration.
*
* GPL v3.0 License
* Copyright (c) 2017 Azo
*
* https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
*/
#ifndef INVISIBLE_BLOCK
#define INVISIBLE_BLOCK

#include "game_object.hpp"

namespace Azo {
	/**
	* @brief A collision class with invisible blocks.
	*
	* A class for collision calculation using invisible blocks as parameters.
	*/
	class InvisibleBlock : public engine::GameObject {
	public:
		std::pair<double, double> mPositionRelativeToParent;
		InvisibleBlock();
		virtual ~InvisibleBlock();
		InvisibleBlock(
			std::string name,
			std::pair<double, double> positionRelativeToParent,
			std::pair<double, double> size
		);
		void shutdown();
		/**
		* @brief Method for class name.
		*
		* Inline method for returning the class' name.
		*/
		inline std::string getClassName() {
			return "InvisibleBlock";
		}

	private:
		engine::ImageComponent *mImage;
		
	};
}

#endif
