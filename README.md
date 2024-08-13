# Check list

1.	When time_eat or time_sleep is larger than time_die -> the program should die.  ✅

-	Example: ./philo 5 800 2000 2000

2.	Mixed timestamp output on the terminal.  ✅

-	Solution

	a. Create another lock for printing purpose  ✅
	
	b. Lock and unlock when a whole thing is done.

3. Printf cannot work correctly if not flushed -> build simple write_msg function ✅

4. Inconsistency in meal eaten ✅

-	Solution :

	<1>	usleep after thinking

	<2> Let the philo sleep after hitting the must_eat thresold before exiting
