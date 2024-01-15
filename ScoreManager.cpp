#include "ScoreManager.h"

void ScoreManager::Update()
{
	SandWitch = false;
	//ìÒÇ¬Ç∆Ç‡ã≤ÇÒÇ≈Ç¢Çƒ
	if (UpSandPoint == true && UnderSandPoint == true)
	{
		//ãÔçﬁï 
		if (SandType == 1)
		{
			Score += 2;
			type = 2;

			if (perfect == true)
			{
				type = 1;
			}
		}
		else if (SandType == 2)
		{
			Score += 1;
			type = 2;

			if (perfect == true)
			{
				type = 1;
			}
		}
		else if (SandType == 3)
		{
			Score += 1;
			type = 2;

			if (perfect == true)
			{
				type = 1;
			}
		}
		else if (SandType == 4)
		{
			Score += 1;
			type = 2;

			if (perfect == true)
			{
				type = 1;
			}
		}
		else if (SandType == 5)
		{
			Score += 1;
			type = 2;

			if (perfect == true)
			{
				type = 1;
			}
		}
		else if (SandType == 6)
		{
			Score -= 1;
			type = 3;
		}
		SandWitch = true;
		combo += 1;
		comoboflag = true;
		
	}
	else
	{
		combo = 0;
	}
}
