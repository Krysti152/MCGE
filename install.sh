#!/bin/bash

echo "-----MeowCat Game Engine Installer-----"
echo "SFML 2.6.0 libraries are needed to working properly."
echo "V1.3"

sudo cp -R Libraries/ /usr/include/MCGE/
sudo mkdir /etc/MCGE/
sudo cp -R presets/default_proj/ /etc/MCGE/default_proj/
sudo cp manager.sh /usr/bin/MCGE-man


mkdir ~/MCGE_projects
echo "New projects created via MeowCat Game Engine Manager will be stored in ~/MCGE_projects."
echo "This is default directory for new projects created via MeowCat Game Engine Manager." > ~/MCGE_projects/readme.md
echo "-----MeowCat Game Engine was successfully installed-----"
