# Flocking system
For my project I decided to pursue a simple Craig-Reynolds Flocking System using the 
NGL library to render the data. This system consists of three main rules which are
cohesion, separation and aggregation. 

## Class structure
The classes for this project are separated into 2 classes as follows: The Boids and 
Flocking classes. The general system behaviour of all the boids is contained within 
the Flocking class, whereas specific attributes per boid within the overall flock
is implemented into the Boids classes.

## Flocking Rules:
When all 3 flocking rules are simulated in conjunction, a simple Craig Reynolds 
flocking system behvaiour starts to exist.

### Cohesion
This rule controls the behaviour of boids that approach a neighbourhood of another 
boid. A cohesive or attractive force binds to boids that are very close together
from different neighbourhoods.

### Separation
A second separation force exists to repel certain boids that attract to close to
each other from different boid neighbourhoods.

### Aggregation


 
 
