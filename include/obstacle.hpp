#ifndef OBSTACLE
#define OBSTACLE

#include "game_object.hpp"
#include "invisible_block.hpp"
#include "machine_part_code.hpp"

namespace Azo {

	// Add new obstacle Types here.
	enum class ObstacleType {
		GROUND,
		WESTERN_BOX,
		WESTERN_RAISED_BOX,
		WESTERN_CAR,
		WESTERN_ROCK,
		WESTERN_SPIKE,
		MACHINE_PART,
		WESTERN_POST
	};

	enum class MachinePartState {
		COLLECTED,
		NON_COLLECTED,
		NON_MACHINE,
		FINISHED,
	};

	class Obstacle : public engine::GameObject {
		public:
			std::pair<double, double> mPositionRelativeToParent;
			std::list<InvisibleBlock *> mBlockList;
			ObstacleType mObstacleType;
			MachinePartState mMachinePartState = MachinePartState::NON_MACHINE;
		private:
			engine::ImageComponent *mObstacleImage = NULL;

			engine::AudioController *mAudioController = NULL;

			engine::Animation *mTurning = NULL;

			engine::AudioComponent *mCollected = NULL;

			std::vector<engine::Sprite *> mTurningAnimationSprites;

			MachinePartCode *mMachinePartCode = NULL;
		public:
			Obstacle();
			virtual ~Obstacle();
			Obstacle(std::string name, std::pair<double, double> positionRelativeToParent, ObstacleType obstacleType);
			void shutDown();
			inline std::string getClassName(){
				return "obstacle";
			}
		private:
			void createComponents();
			void createBlocks();
			void generateTurningAnimation();

	};
}

#endif
