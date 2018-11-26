/**
     * @file menu.hpp
	 * @brief Purpose: Menu class declaration
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#ifndef MENU
#define MENU

#include "scene.hpp"
#include "menu_code.hpp"
#include "audio_controller.hpp"

namespace Azo {
	/**  
		 * @brief A Hitbox class.
		 * Menu class
		 *
		 * A more elaborate class description.
		 * Class responsible for creating the ' menu '
		 */
	class Menu : public engine::Scene {
		private:
			engine::GameObject *mMenu; // Miscellaneous comment

			engine::AnimationController *mAnimationController;

			engine::Animation *mStartButton; // Variable referring to the Start button
			engine::Animation *mExitButton; // Variable referring to the output button
			engine::Animation *mSoundEnabledButton; // Variable referring to the Activate sound button
			engine::Animation *mSoundDisabledButton; // Variable referring to the Activate sound button

			engine::Animation *mArrowStart; // Variable referring to start arrow
			engine::Animation *mArrowExit; // Variable referring to output arrow
			engine::Animation *mArrowSound; // Variable referring to sound

			std::vector<engine::Sprite *> mStartButtonSprites;
			std::vector<engine::Sprite *> mExitButtonSprites;
			std::vector<engine::Sprite *> mSoundEnabledButtonSprites;
			std::vector<engine::Sprite *> mSoundDisabledButtonSprites;

			std::vector<engine::Sprite *> mArrowSprites;

			engine::BackgroundComponent *mBackground;
			MenuCode *mCode;
			engine::AudioController *mAudioController;
			engine::AudioComponent *mMenuTheme; // Variable referring to the menu
		
		public:
			Menu();
			Menu(std::string name);
			void restart();
			void shutdown();

		private:
			void createGameObjects();
			void createMenuComponents();
			void generateButtonsAnimation();

	};
}

#endif
