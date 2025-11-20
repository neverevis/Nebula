#!/bin/bash

black='\e[30m'
red='\e[31m'
green='\e[32m'
yellow='\e[33m'
blue='\e[34m'
magenta='\e[35m'
cyan='\e[36m'
white='\e[37m'
reset='\e[0m'

libs=-luser32
warnings=-Wno-writable-strings

echo -e "${yellow}Building...${reset}"

clang++ src/main.cpp -o game.exe $libs $warnings
status=$?

if [[ $status -eq 0 ]]; then
    echo -e "${green}Build done!${reset}"
else
    echo -e "${red}Build failed!${reset}"
fi