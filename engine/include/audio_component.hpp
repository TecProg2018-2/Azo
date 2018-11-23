/**
   * @file audio_component.hpp
   * @brief Purpose: Contains the AudioComponent class declaration.
   *
   * GPL v3.0 License
   * Copyright (c) 2017 Azo
   *
   * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md */
#ifndef AUDIO_COMPONENT_HPP
#define AUDIO_COMPONENT_HPP

#include <string>
#include "sdl2include.h"
#include "component.hpp"
#include "log.h"

namespace engine {

	/*
	 *@brief Class for possible Audio States
ra	 *Enum Class used to differentiate Audio States
	 *
	 */
	enum class AudioState {
		PLAYING,
		PAUSED,
		STOPPED
	};

	/*
	 *
	 *@brief AudioComponent class for in-game audio
	 *
	 *Used to define the behavior of audio in game
	 *
	 */
	class AudioComponent : public Component {
	private:
		std::string audioPath;
		bool isMusic;
		bool playOnStart;

		Mix_Music * music;
		Mix_Chunk * sound;

	public:
		AudioState audioState;
		AudioComponent();
		virtual ~AudioComponent();
		AudioComponent(GameObject &gameObject, std::string audioPath,
					   bool isMusic, bool playOnStart);
		void init();
		void shutdown();
		void updateCode();
		void play(int loops, int channel);
		void stop(int channel);
		void pause(int channel);

		inline bool getIsMusic() {
			return isMusic;
		}
	};

}

#endif
