#include "ScoreManager.h"

void ScoreManager::Update()
{
	//‹ïŞ•Ê

	//“ñ‚Â‚Æ‚à‹²‚ñ‚Å‚¢‚Ä
	if (SandPoint == 2)
	{

		if (SandType == 1)
		{
			Score += 1;
		}
	}

	SandPoint = 0;
}
