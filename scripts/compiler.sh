#!/bin/bash

echo -e "\033[32mWhat file:\n"

read path

echo $path

g++ $path -o exe



./exe
