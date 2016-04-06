#include "GameManager.h"

bool GameManager::update()
{
	bool ret = false;

	while (currentWaves != 5)
	{
		/*
		for (int i = 0; i < hazardCount; i++)
		{
			//timer
			yield return new WaitForSeconds(startWait);
			Vector3 spawnPosition = new Vector3(Random.Range(-spawnValue.x, spawnValue.x), spawnValue.y, spawnValue.z);
			Quaternion spawnRotation = Quaternion.identity;
			Instantiate(hazard, spawnPosition, spawnRotation);
			yield return new WaitForSeconds(spawnWait);
		}
		yield return new WaitForSeconds(waveWait);
		if (gameOver)
		{
			gameOverText.text = "Press 'R' to restart the game.";
			restart = true;
			break;
		}
		*/
	}

	return ret;
}