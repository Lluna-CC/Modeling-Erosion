# Project Steps

## Multi-Resolution

## Erosion Algorithm Improvements

### Adding forces


### Parallelization and diverging paths

**If we have time**

## General Improvements


### Parallelization

There are multiple parts of the code that can be easily parallelized.

Also, the algorithm could run in a different process than the rendering, as currently the applications stops for a while until the algorithm ends.

Maybe we can also make use of compute shaders for some things.

### General efficiency improvements

We have to revise all code to improve the efficiency, there might be some things to improve.

### Code cleaning and UI improvements

There is a huge part of the code that is not being used (and the UI) We should clean all code at the end

### Small improvements

- Dealing with core cells
- Adding more toys
- Solve the weird artifacts when removing cells and models
- Dealing with area 0 triangles

## Report