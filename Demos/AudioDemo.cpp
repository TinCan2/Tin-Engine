#include "Audio.hpp"
#include "GameManager.hpp"
#include "KeyboardManager.hpp"

using namespace Tin;

int main(int argc, char* argv[]) {
	GameManager* gameManager = GameManager::Instantiate();

	gameManager->Initialize("Audio Demo", 640, 480);

	Audio arp(TIN_DEMO_LOCATION "Audio/arpegio.wav", false);
	Audio music1(TIN_DEMO_LOCATION "Audio/Valazonturenkur.mp3", true);
	Audio music2(TIN_DEMO_LOCATION "Audio/Mini Game 1 music.mp3", true);

	music1.Play();
	music2.Play();

	while(!gameManager->IsQuitting()) {
		gameManager->Handle();
		gameManager->Update();
		if (KeyboardManager::GetCurrentManager()->KeyPressed("Z")) arp.Play();
		gameManager->Render();
	}

	gameManager->Terminate();

	GameManager::Destroy();
	return 0;
}