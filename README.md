Hey 

I haven't done any work I've just played aroud w/ the make and directory structure to try and make things easier for us when we do start.




- `main` is the entry point (GenAlloc).
- `Allocator` is the logic for the actual algortithm.
- `Staff`, `Student`, `Projects` are thier respective classes (that I think you wanted to divide the work into?)
- `makefile` builds GenAlloc.


### Make Comamnds!

```
make <-- compile and create GenAlloc!

make clean <-- everything fresh

./GenAlloc ./Test/staffExample.txt ./Test/projectExample.txt ./Test/studentExample.txt output.txt <-- running the program with the examples ive imported in from the question page
```


So far I've done:
- Accepting cmd-line input
- file parsing for `staff`, `projects`, `students`
- makefile 
- added `DEBUG` file (1 for on, 0 for off)
    - I've left this on for now (DEBUG_PRINT)
- All data is stored in a dictionary for you to work with! `unordered_map`


### Things to note & ideas
- Allocator is our gateway to the other classes/datastructures! 
    ``` 
                        -> Project
    main() -> allocator -> Staff
                        -> Student

    ```
    - I've left `perform_allocation()` in allocator.cpp. I have no idea what methods you need.
- Output to file not implemented- i can do that if you want. 
- `./Test/` add any test files you want and change `./genalloc` call to fit

### What's Changed (Draco)
- I implemented the greedy algorithm given as an example, and then improved it using one of the examples,
described as when you 'Repeat the above algorithm a number 
of times, each with a different random ordering of students / staff, and choose the best one.'
- The algo runs 1000 iterations, shuffling the order of students and staff each time
using `std::shuffle` (as seen in the cpp algorithm ref given in lectures)
- The algo runs a greedy assignment and the allocation is scored. If new score is higher,
it's saved as the new max. 
- Three phases in the algo: Student preference based assignment, then checks all students are assigned,
then assigns supervisor. Follows all specifications (I think)
- I also added some stuff to the file loading in case files are missing, also fixed an issue where # was read as an ID,
and changed private member variable names to match style requirements