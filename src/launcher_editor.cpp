#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

#define MAX_LAUNCHER_LENGTH 7
#define LAUNCHER_ADDRESS 0x200F3C

void seekLauncher(std::fstream &gameRaw) {
	gameRaw.seekp(LAUNCHER_ADDRESS);
}

void updateLauncher(std::fstream &gameRaw, std::string newLauncher) {

	int launcherChars = newLauncher.size();
	int emptyLauncherChars = MAX_LAUNCHER_LENGTH - launcherChars;

	std::cout << "Attempting to update Game.exe launcher to " << newLauncher << std::endl;

	seekLauncher(gameRaw);
	gameRaw.write(newLauncher.c_str(), newLauncher.size());

	// Empty all of the values that are beyond the new launcher's length but are part of the launcher's space
	std::string emptyString("");
	for (int i = 0; i < emptyLauncherChars; i++) {
		gameRaw.seekp(LAUNCHER_ADDRESS + launcherChars + i);
		gameRaw.write(emptyString.c_str(), 1);
	}

}

std::string getLauncher(std::fstream &gameRaw) {

	seekLauncher(gameRaw);

	char* buffer = new char[MAX_LAUNCHER_LENGTH];
	gameRaw.read(buffer, MAX_LAUNCHER_LENGTH);
	std::string currentLauncher(buffer);

	return currentLauncher;

}

void printLauncher(std::fstream &gameRaw) {

	std::string launcher = getLauncher(gameRaw);
	std::cout << "Current launcher is " << launcher << std::endl;

}

std::string requestNewLauncher() {

	std::string newLauncher;

	while (newLauncher.size() == 0 || newLauncher.size() > MAX_LAUNCHER_LENGTH) {
		std::cout << "Enter the new launcher for the game (maximum length is 7 characters)" << std::endl;
			
		std::cin >> newLauncher;
	}

	return newLauncher;

}

bool openGameRaw(std::string gamePath, std::fstream &file) {

	bool opened = false;

	file = std::fstream ( gamePath.c_str(), std::ios::binary | std::ios::in | std::ios::out );

	if (file) {
		opened = true;
	}

	return opened;

}

std::string getGamePath() {

	std::string fileName;

	std::cout << "Please enter the relative path of Game.exe" << std::endl;

	std::cin >> fileName;

	return fileName;
}


int main(int argc, char* argv[])
{
	
	std::string gamePath;
	std::fstream gameFile;
	while (!openGameRaw(gamePath, gameFile)) {
		gamePath = getGamePath();
	}

	printLauncher(gameFile);
	std::string newLauncher = requestNewLauncher();
	updateLauncher(gameFile, newLauncher);
	printLauncher(gameFile);

	std::cout << "Update completed" << std::endl;

	gameFile.close();

	return 0;
}