#include "ScoreManager.h"

void ScoreManager::Update()
{
	//具材別

	//二つとも挟んでいて
	if (SandPoint == 2)
	{

		if (SandType == 1)
		{
			Score += 1;
		}
	}

	SandPoint = 0;
}
