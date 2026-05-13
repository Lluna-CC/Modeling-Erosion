# Project Steps

## Algorithm Improvement

### Parallelization

We can parallelize multiple things in the code, like graph update and traversal, but in the context of the algorithm we can try to parallelize the path traversal.

The main 2 problems for that are:
 1. What if two paths go through the same link at the same time (we need some coordination)
 2. What happens after one part is broken and separeted from the rest
 - Additionally we have to be careful with the link updates, as two paths might not go through the same link at the same time but at differnt times, so the link would be damaged by the previous path

Main tasks to do in this regard are:

- [ ] Plan how to solve both problems
- [ ] Plan what to use for parallelism (which library)
- [ ] Should we allow water fusing if two paths intersect (?) 
### Divergent Paths

Water can flow in multiple directions, and the water path can be divided into two sub-paths (we can make use of parallelism here), I think the appropiate thing would be to only allow two subpaths to generate and avoid water diverging with low ammounts of water, as water paths scale exponentially we should put a *linit* on the number of paths generated

Main tasks to plan:

- [ ] Plan paramters that regulate splitting, trying yo avoid exponantial explosion

### Physically based elements

We can improve the simulation by adding some physically based elements to the algorithm. Some things that we could add:

- Crack expansion
- Unloading
- Take stress of the whole sysytem into account
- We can use other modles (mass-spring?, DEM?) as inspiration

Main tasks to plan:  

- [ ] Decide which things, exactly are we going to implement

## Visualization


The main problem of visualization is that rendering the inside cells would be really costly, so we might to edit some things for that

### Link visuzlization

We can separet the cells and render a link (as an octogonal prism) between neighbors, we can modify the color and the size of the link to encode different variables

### Path visualization

We can show the faces that the water traversses so we can visualize the paths.

The main problem of that would be rendering the interior cells.

## General Improvements

### Better sampling

The largest models are extremly big and we can not work with them with our current method, we should design a method to reduce the number of Voronoi Cells generated, specially for bigger models. 

The main problem would be to ensure some accuracy of the modeling while sampling less points.

### Resolution levels

We can edit the model as we keep erosioing parts, but as we can not have the full model loaded, that means that we will have to stop the execution at some moment to start computing the voronoi decomposition again.

### Parallelization

There are multiple parts of the code that can be easily parallelized.

Also, the algorithm could run in a different process than the rendering, as currently the applications stops for a while until the algorithm ends.

Maybe we can also make use of compute shaders for some things.

### General efficiency improvements

We have to revise all code to improve the efficiency, there might be some things to improve.

### Code cleaning and UI improvements

There is a huge part of the code that is not being used (and the UI) We should clean all code at the end

## Report

### Introduction

### Background

### Previous Work

### Method

### Implementation

### Results

### Conclusions