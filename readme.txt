
********************
Implementation Notes
********************

- `main()` calls to Allocator class, which encapsulates Staff, Student, and Project classes - coordinates all operations.                  
- `std::unordered_map` for lookup of staff, projects, and students by ID.
- `std::map` for allocations to maintain automatic sorting by student_id for output.
- `std::vector` for subject areas and project preferences.

The DEBUG macro (in DEBUG.h) is disabled (`DEBUG = 0`) for submission to ensure clean output,
but can be enables by `DEBUG = 1`. Used to aid debugging/development. This is what `DEBUG_PRINT` is.

************************************
Additional Functionality Implemented
************************************

Extensions to the basic allocation algorithm provided in the brief include:

1. Randomised Multi-Iteration Optimisation
   Implemented the suggested improvement from the coursework brief.
   The algorithm executes 1000 (`NUM_ITERATIONS`) iterations, each with a randomised ordering of students and staff members using `std::shuffle`,
   then selects the highest-scoring legal allocation from all attempts. 
   This produces better allocations than a single greedy interation,espeically for larger datapools where the order 
   of processing has large impact on the final result.

2. Enhanced Unallocated Student Allocation (Phase 1.5)
   Unallocated students are assigned to projects in two sub-phases to maximise the total score before assigning supervisors:

   Phase 1.5a - Maxmising Supervisor Scores: 
               Students who are still unallocated are assigned to projects proposed by their supervisors.
               This maximises supervisor scores (+4) and ensures a project allocation for the students.

   Phase 1.5b - Gurantee All Allocations:
               Any students *still* without a project are then assigned to any available project- no matter the propser.
               This is the final action to take place to ensure every student recieves an allocation- even if they have no stated preferences or their preferences were unavailable.

   This enhancement ensures the allocation meets the requirement that all students receive exactly one project, whilst strategically maximising the overall score.

3. Validation and Score-Based Selection
The algorithm validates each student allocation, rejecting any with a score of -1 to ensure all students are assigned supervisors.
Across 1000 iterations, the maximum score is monitored. The process returns the best legal and stable allocation, guaranteeing all constraints are satisfied while maximising the overall score.

