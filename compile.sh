#!/bin/bash

make fclean 
make 

# valgrind  --track-origins=yes ./philo 5 800 200 200 5

./philo 5 800 200 200 5