# Repository for Advent of Code 2023

This year I wanted to try using C++, since I haven't used it for a long time.

### Problems I encountered

- **Day 5**: I tried using _uint32\_t_ as the type to read the numbers to
  -> Some of the seeds were over the limit, making them all wrong since now values rolled over
  -> Used wrong function, namely ***stoi()***, to convert string to integer -> now all numbers were of type _int32\_t_, which made them wrong as well
  -> Converted to use _uint64\_t_ and ***stoll()***, finally got right answer. Figured, that just using _int\_64_ is enough and makes it easier, so used that in the end.

- **Day 8**: Part 2 was first problem that needed some assumptions that were never mentioned in the assignment.
    1. That the ghosts have a cycle and it's constant from the get-go.
    2. The cycle has every ghost visiting only one goal.
- After these assumptions the solution was rather simple to implement; just track every ghost until they first arrive at the goal and save the amount of steps it takes. Then calculate the least common multiplier of the cycles (I used the std::lcm).
