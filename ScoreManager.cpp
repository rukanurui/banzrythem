#include "ScoreManager.h"

void ScoreManager::Update()
{
	SandWitch = false;
	//“ñ‚Â‚Æ‚à‹²‚ñ‚Å‚¢‚Ä
	if (UpSandPoint == true && UnderSandPoint == true)
	{
		//‹ïŞ•Ê
		if (SandType == 1)
		{
			Score += 1;
		}
		SandWitch = true;
	}
}
