#!/bin/bash

make fclean
make

clear

valgrind  --leak-check=full --track-origins=yes ./philo 2 800 200 200 2