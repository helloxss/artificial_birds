#ifndef BIRD_OPTIMIZER_H__
#define BIRD_OPTIMIZER_H__

#include "btBulletDynamicsCommon.h"
#include "BigBirdLocalParams.h"
#include "../proto/proto.pb.h"
#include "BigBird.h"
#include "BigFeather.h"
#include "time.h"

class BirdOptimizer {
public:
	BirdOptimizer(btDynamicsWorld* ownerWorld, int numBirds);
	~BirdOptimizer();
	void pretick(btScalar dt);
	void spawnBigBird(const btVector3& startOffset);
	void removeBigBird();
	btVector3 getBirdPosition() { 
		if (m_bigbird)
			return m_bigbird->getPosition();
		return btVector3(0,0,0);
	}
protected:
	void fillWithRandomNumbers(proto::BigBirdConstructionData* info, int numPoints);
	//void spawnBigBird(const btVector3& startOffset);
	//void removeBird();
	void perturbBestResult(const proto::BigBirdConstructionData& bestCPG, proto::BigBirdConstructionData* info);
	void evaluateCurrentGenerationBirds();

private:
	btDynamicsWorld* m_ownerWorld;
	BigBird* m_bigbird;
	btScalar m_time;  // keep track of time.
	btAlignedObjectArray<proto::TrajectoryData*> m_birdTrajectoryData;
	proto::TrajectoryData* m_currentTrajectoryData;
	btAlignedObjectArray<proto::BigBirdConstructionData*> m_birdInfos;
	proto::BigBirdConstructionData* m_birdData;
	BigBirdLocalParams* m_birdLocalParam;
	proto::BigBirdConstructionData* m_currentBestInfo;
	int m_numBirdsPerGeneration;
	int m_numGeneration;
	int m_giveBirdThisId;
};

#endif