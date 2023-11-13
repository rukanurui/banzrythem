#include "ScoreManager.h"

void ScoreManager::Update()
{
	float error = 10.0f;
	//“ñ‚Â‚Æ‚à‹²‚ñ‚Å‚¢‚Ä
	if (SandPoint == 2)
	{
		//Œë·Œ—“à‚È‚ç
		if ((IngredientsRotation.z <= BunsDownRotation.z + error && IngredientsRotation.z >= BunsDownRotation.z - error)&&
			(IngredientsRotation.z <= BunsUpRotation.z + error && IngredientsRotation.z >= BunsUpRotation.z - error))
		{
			Score += 1;
		}
	}

	SandPoint = 0;
}
