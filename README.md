## This is a C implementation of the popular M-Questions Game. 
The M-Questions game will get information about what questions to ask, the items, and the answer to each
question for each item, from a database file that is formatted similarly to a CSV file. working directory. Here is
one example of a file that the program will be expected to read in:
```
10
does it have 4 legs?,does it have wheels?,does it have a motor?,does it have fur?
car,0,1,1,0
fox,1,0,0,1
elephant,1,0,0,0
trailer,0,1,0,0
tarantula,0,0,0,1
mirror,0,0,0,0
work bench,1,1,0,0
standing desk,1,1,1,0
bear,1,0,0,1
lion,1,0,0,1
```
* The first line should be a number, which tells the program how many total items this file has in it. In the
example above, there are 10 total items: car, fox, elephant, trailer, tarantula, mirror, work bench,
standing desk, bear, lion.

* The second line will have a comma-separated list of the questions that this file has information about. In
the example above, there are four questions.

* From the third line on, each line will have information about one item in a comma-separated list. The
first element will be the name of the item. For example, the item car is on line 3. Following this is a
comma separated list of 1s and 0s. A 1 corresponds to a “yes” answer to a question, and a 0
corresponds to “no”. For example, for the car row, the numbers are 0,1,1,0. This means that the answer
to the first and fourth questions from row 2 are “no” and the answer to the second and third questions
from row 2 are “yes”. This makes sense, because a card does NOT have 4 legs and does NOT have
fur, but it DOES have four wheels and it DOES have a motor.

The database file should be provided as the first command-line argument to the program. For example, if the
contents of that file were stored in a file named ```small.mq``` then you should run the game with this file like so:
```
$ ./game small.mq
```
