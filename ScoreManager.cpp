#include "ScoreManager.h"

void ScoreManager::Update()
{
	//��ޕ�

	//��Ƃ�����ł���
	if (SandPoint == 2)
	{

		if (SandType == 1)
		{
			Score += 1;
		}
	}

	SandPoint = 0;
}
