#!/bin/bash

make fclean --quiet
make --quiet

valgrind  --track-origins=yes ./philo 4 420 42 24