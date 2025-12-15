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