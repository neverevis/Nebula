#!/bin/bash

#set text colors
black='\e[30m'
red='\e[31m'
green='\e[32m'
yellow='\e[33m'
blue='\e[34m'
magenta='\e[35m'
cyan='\e[36m'
white='\e[37m'
reset='\e[0m'

#activate glob to search for subdirectories
shopt -s globstar

includes='-Iexternal -Isrc'
links=''
libs='-luser32 -lopengl32 -lgdi32'
warnings='-Wno-writable-strings -Wno-format-security'

echo -e "${yellow}Building...${reset}"

clang++ src/**/*.cpp -o game.exe $warnings $includes $links $libs
status=$?

if [[ $status -eq 0 ]]; then
    echo -e "${green}Build done!${reset}"
else
    echo -e "${red}Build failed!${reset}"
fi