#!/bin/bash

make fclean
make bonus

clear

# valgrind  --leak-check=full --track-origins=yes ./philo 5 800 200 200 5

./philo_bonus 5 800 200 200 7