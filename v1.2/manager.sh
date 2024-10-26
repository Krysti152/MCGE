#!/bin/bash

echo "-----MeowCat Game Engine Manager-----"
echo "Name of the new project:"
read PROJECT_NAME
mkdir /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME
cp -n presets/blank.cpp /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME/main.cpp
cp -n presets/pref.ini /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME/pref.ini
mkdir /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME/assets
mkdir /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME/assets/sprites
mkdir /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME/assets/fonts
mkdir /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME/assets/sounds
mkdir /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME/assets/scripts

cp -n presets/script.hpp /run/media/krystian/Pliki/Komputery/Programowanie/cpp/MCGE_projects/$PROJECT_NAME/assets/scripts/example_script.hpp
echo "-----Successfully created new project-----"
