#!/bin/bash
cp get_next_line.c get_next_line_bonus.c
cp get_next_line.h get_next_line_bonus.h
cp get_next_line_utils.c get_next_line_utils_bonus.c
sed -i '' 's/get_next_line.h/get_next_line_bonus.h/g' get_next_line_bonus.c get_next_line_utils_bonus.c