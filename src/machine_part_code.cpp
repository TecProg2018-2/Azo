#include "machine_part_code.hpp"
#include "obstacle.hpp"

using namespace Azo;

MachinePartCode::MachinePartCode(Obstacle *machinePart) {
	mMachinePart = machinePart;
	findAudioController();
}

MachinePartCode::~MachinePartCode() {}

void MachinePartCode::shutDown(){
	if (mAudioController != NULL) {
		mAudioController = NULL;
	}
}

void MachinePartCode::findAudioController() {
	mAudioController = (mMachinePart->getAudioController(typeid(engine::AudioController)));
}

void MachinePartCode::updateCode() {
	switch(mMachinePart->mMachinePartState) {
		case MachinePartState::COLLECTED:
			mAudioController->PlayAudio("coleta");

			mMachinePart->mMachinePartState = MachinePartState::FINISHED;
			break;
		case MachinePartState::FINISHED:
			mMachinePart->mObjectState = engine::ObjectState::DISABLED;
		default:
			break;
	}
}
