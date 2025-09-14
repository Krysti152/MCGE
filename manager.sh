#!/bin/bash

echo "-----MeowCat Game Engine Manager-----"
echo "Name of the new project:"
read p_name
p_path="/home/krystian/MCGE_projects/"$p_name/

cp -r /etc/MCGE/default_proj/ $p_path

echo "-----Successfully created new project-----"
