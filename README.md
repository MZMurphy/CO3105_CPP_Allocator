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
- I implemented the greedy algorithm given as an example, which is pretty basic.
- This basic algo would get stuck giving the first couple of students in the list their optimal allocations,
and the others would be left with bad allocs.
- This was fixed through one of the suggested optimisations. Running 1000 iterations of the allocation,
I used `std::shuffle` to randomise what order students and staff were processed. This meant the algo
could explore lots of different options, and use that to find the maximum score. 
- `perform_allocation` is split into three parts to meet all the requirements:
  1. Firstly it does the normal
  greedy pass where it matches students with their choices (in order of preference). 
  2. Leftover students are then
  assigned to any available project, starting with those proposed by supervisors (4 points), then whatever's available.
     - By assigning them in this order, we ensure the highest score possible, which is always our aim.
  3. The third part is supervisor assignments. Again we look at proposer, then subject area match, then anyone who needs a supervisor.

- Other than that I changed private member variable names to match style guides, added checks for if a file is missing,
- and fixed an issue with file parsing bc comments in txt files were being read as part of an ID