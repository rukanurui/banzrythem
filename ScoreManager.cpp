#include "ScoreManager.h"

void ScoreManager::Update()
{
	float error = 10.0f;
	//��Ƃ�����ł���
	if (SandPoint == 2)
	{
		//�덷�����Ȃ�
		if ((IngredientsRotation.z <= BunsDownRotation.z + error && IngredientsRotation.z >= BunsDownRotation.z - error)&&
			(IngredientsRotation.z <= BunsUpRotation.z + error && IngredientsRotation.z >= BunsUpRotation.z - error))
		{
			Score += 1;
		}
	}

	SandPoint = 0;
}
