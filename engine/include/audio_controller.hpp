/**
 * @file audio_controller.hpp
 * @brief Purpose: Contains the AudioController class declaration
 *
 * GPL v3.0 License
 * Copyright (c) 2017 Azo
 *
 * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
 */
#ifndef AUDIO_CONTROLLER_HPP
#define AUDIO_CONTROLLER_HPP

#include "audio_component.hpp"
#include "log.h"

#include <map>
#include <iostream>

namespace engine {

	/*
	 *@brief Audio contoller class to control in game audio.
	 *
	 *Used to control the behavior defined by the AudioComponent
	 */
	class AudioController : public AudioComponent {

		private:
			std::map <std::string, AudioComponent *> audioMap;

		public:
			AudioController();
			virtual ~AudioController();
			AudioController(GameObject &gameObject);
			void addAudio(std::string audioName, AudioComponent &audio);
			void playAudio(std::string audioName);
			void stopAudio(std::string audioName);
			void pauseAudio(std::string audioName);
			void stopAllAudios();
			AudioState getAudioState(std::string audioName);
			void init();
			void shutdown();
			void updateCode();

	};

}

#endif
