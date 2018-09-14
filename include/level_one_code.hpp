#ifndef LEVEL_ONE_CODE
#define LEVEL_ONE_CODE

#include "code_component.hpp"
#include "player.hpp"
#include "obstacle.hpp"
#include "audio_controller.hpp"

namespace Azo {
	class LevelOneCode : public engine::CodeComponent {
		private:
			Player *mPlayer;
			std::list<Obstacle *> mObstacleList;
			engine::AudioController *mAudioController;
			engine::GameObject *mLosingParts;
			engine::GameObject *mLosingDeath;
			engine::GameObject *mWinningScreen;
			engine::GameObject *mArrow;

			double mWaitingTime = 0.0f;
			int mCurrentOption = 1;
		public:
			LevelOneCode(engine::GameObject &gameObject);
			void shutDown();
		private:
			void findAudioController();
			void updateCode();
			void changeOption();
			void chooseOption();
			void updateObstaclePosition();
			void getParents();
			bool hasGround(double *groundY);
			bool hasCeiling(double *groundY);
			bool hasWallOnRight(double *wallX);
			bool hasWallOnLeft(double *wallX);
			void updatePhysics();

	};
}

#endif
