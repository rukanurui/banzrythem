#include "ScoreManager.h"

void ScoreManager::Update()
{
	SandWitch = false;
	//二つとも挟んでいて
	if (UpSandPoint == true && UnderSandPoint == true)
	{
		//具材別
		if (SandType == 1)
		{
			Score += 1;
		}
		SandWitch = true;
	}
}
