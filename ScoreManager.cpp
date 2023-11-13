#include "ScoreManager.h"

void ScoreManager::Update()
{
	float error = 10.0f;
	//二つとも挟んでいて
	if (SandPoint == 2)
	{
		//誤差圏内なら
		if ((IngredientsRotation.z <= BunsDownRotation.z + error && IngredientsRotation.z >= BunsDownRotation.z - error)&&
			(IngredientsRotation.z <= BunsUpRotation.z + error && IngredientsRotation.z >= BunsUpRotation.z - error))
		{
			Score += 1;
		}
	}

	SandPoint = 0;
}
