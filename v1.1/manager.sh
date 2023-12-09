#!/bin/bash

echo "-----MeowCat Game Engine Manager-----"
echo "Name of the new project:"
read PROJECT_NAME
mkdir ~/MCGE_projects/$PROJECT_NAME
cp -n presets/blank.cpp ~/MCGE_projects/$PROJECT_NAME/main.cpp
cp -n presets/pref.ini ~/MCGE_projects/$PROJECT_NAME/pref.ini
mkdir ~/MCGE_projects/$PROJECT_NAME/assets
mkdir ~/MCGE_projects/$PROJECT_NAME/assets/sprites
mkdir ~/MCGE_projects/$PROJECT_NAME/assets/sprites/anim
mkdir ~/MCGE_projects/$PROJECT_NAME/assets/sprites/tileset
mkdir ~/MCGE_projects/$PROJECT_NAME/assets/fonts
mkdir ~/MCGE_projects/$PROJECT_NAME/assets/sounds
mkdir ~/MCGE_projects/$PROJECT_NAME/assets/scripts
cp -n presets/script.hpp ~/MCGE_projects/$PROJECT_NAME/assets/scripts/example_script.hpp
echo "-----Successfully created new project-----"
