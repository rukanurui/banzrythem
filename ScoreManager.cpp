#include "ScoreManager.h"

void ScoreManager::Update()
{
	SandWitch = false;
	//��Ƃ�����ł���
	if (UpSandPoint == true && UnderSandPoint == true)
	{
		//��ޕ�
		if (SandType == 1)
		{
			Score += 1;
		}
		SandWitch = true;
	}
}
