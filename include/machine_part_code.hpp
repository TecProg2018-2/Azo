/**
     * @file machine_part_code.hpp
	 * @brief Purpose: Declaration of the MachinePartCode class
     *
     * GPL 3.0 License
     * Copyright (c) 2017 Azo
     *
     * https://github.com/TecProg2018-2/Azo/blob/master/LICENSE.md
     */
#ifndef MACHINE_PART_CODE
#define MACHINE_PART_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class Obstacle;

	/**
	     * @brief A Hitbox class.
	     * MachinePartCode class
		 *
	     * A more elaborate class description.
		 * Class responsible for the creation of the parts by which the player must
		 * collect to get to victory.
	     */
	class MachinePartCode : public engine::CodeComponent {
		private:
			Obstacle *mMachinePart; // Variable responsible for creating the existing parts on the map
			engine::AudioController *mAudioController; // Variable responsible for audio control
			
		public:
			virtual ~MachinePartCode();
			MachinePartCode(Obstacle *machinePart);
			void shutdown();
		
		private:
			void updateCode();
			void findAudioController();
	};
}
#endif
