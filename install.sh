sudo dscl . -delete /Groups/_ued
sudo dscl . -delete /Users/_ued
sudo rm -rf /Users/_ued

sudo dscl . -create /Groups/_ued
sudo dscl . -create /Groups/_ued PrimaryGroupID 4343

sudo dscl . -create /Users/_ued UniqueID 4343
sudo dscl . -create /Users/_ued PrimaryGroupID 4343
sudo dscl . -create /Users/_ued UserShell /bin/bash
sudo dscl . -create /Users/_ued NFSHomeDirectory /Users/_ued

sudo mkdir /Users/_ued
sudo chown _ued:_ued /Users/_ued

#sudo sed -i '' 's/%admin/#%admin/g' /etc/sudoers;
#echo '%admin		ALL = (ALL) NOPASSWD:ALL' | sudo tee -a  /etc/sudoers
