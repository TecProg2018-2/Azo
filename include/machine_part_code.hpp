	#ifndef MACHINE_PART_CODE
#define MACHINE_PART_CODE

#include "code_component.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class Obstacle;

	class MachinePartCode : public engine::CodeComponent {
		private:
			Obstacle *mMachinePart;
			engine::AudioController *mAudioController;
		public:
			MachinePartCode(Obstacle *machinePart);
			virtual ~MachinePartCode();
			void shutDown();
		private:
			void updateCode();
			void findAudioController();
	};
}
#endif
