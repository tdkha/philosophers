#!/bin/bash

make fclean
make

clear

# valgrind  --leak-check=full --track-origins=yes ./philo 5 800 200 200 5

./philo 5 800 200 200 5