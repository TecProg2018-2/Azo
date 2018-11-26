/**
     * @file menu_code.hpp
	 * @brief Purpose: Declaration of the MenuCode class
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#ifndef MENU_CODE
#define MENU_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	/**
	 * @brief Class for possible button types.
	 * 
	 * Enum class used to differentiate buttons inside the menu.
	 */ 
	enum class ButtonType {
		START_BUTTON,
		EXIT_BUTTON,
		SOUND_BUTTON
	};
	/**
	 * @brief Class for possible errors types.
	 * 
	 * Enum class used to differentiate errors inside the menu.
	 */ 
	enum class FunctionStatus {
		DIVIBYZERO,
		NULLPOINTER,
		EMPTYSTRING,
		WRONGTYPE,
		SUCCESS,
	};

	/** 
		 * @brief A Hitbox class.
		 * MenuCode class
		 *
		 * A more elaborate class description.
		 * Class responsible for creating the Menu features
		 */
	class MenuCode : public engine::CodeComponent {
		private:
			engine::AudioController *mAudioController; // Variable responsible for audio control
			engine::AnimationController *mAnimationController; // Variable responsible for animation control
			ButtonType mCurrentButton = ButtonType::START_BUTTON; // Variable referring to the current button
			FunctionStatus errorCode = FunctionStatus::SUCCESS;

		public:
			MenuCode(engine::GameObject *gameObject);

		private:
			void findAudioController();
			void findAnimationController();
			void changeOption();
			void updateCode();
			void errorLog(std::string file);
	};
}

#endif
