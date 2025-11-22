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

includes='-I F:/VulkanSDK/1.4.321.1/Include'
links='-L F:/VulkanSDK/1.4.321.1/Lib'
libs='-luser32 -lvulkan-1'
warnings='-Wno-writable-strings -Wno-format-security'

echo -e "${yellow}Building...${reset}"

clang++ src/main.cpp src/platform/win32_window.cpp -o game.exe $warnings $includes $links $libs
status=$?

if [[ $status -eq 0 ]]; then
    echo -e "${green}Build done!${reset}"
else
    echo -e "${red}Build failed!${reset}"
fi