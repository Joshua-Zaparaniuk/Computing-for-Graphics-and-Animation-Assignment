# Flocking System
This is a simple flocking system written using the NGL library, inspired by Craig-Reynolds flocking
behaviour. It depicts flocking behaviour of boids using 3 simple rules, cohesion, separation and
alignment

## Class implementation
The way this class was implemented was by creating a flocking class, which handles the implementation
of system rules. Independent boid controls are implemented within a separate class Boids. Calculations
on a boid basis are implemented within the Boids class, whereas system calculations such as neighbour
groups and boid neighbour behaviours inherit some of their functionality from the Boids class.

### GUI class
Within the GUI mainwindow.cpp and header files, the implementations of the user interface are controlled
via function callbacks sent to the NGLScene class sets which directly sets the private member values 
responsible for the simulation.

### NGLScene class
This class controls the connections between user inputs and simulation values. Furthermore, screen
position and draw calls are actually implemented through this class by inheriting from the 
Flock class.

### Boid class
This class is essentially a holder of attribute values and getter and setter methods that are called
within the main Flocking class sets. The Flock class inherits and implements functionality upon
the attributes within this class.

## Flocking Rules

### Cohesion
When other boids are within a distance threshold to the boid in question, they attract towards the 
current boid. This is calculated by averaging the distance of every other boid and subtracting the
position of the current boid relative to the distance of every other boid. It was important to 
normalize the distance values, as this caused numerical instabilites in the calculations.

### Separation
This is a force that repels neighbouring Boids from one another. This rule operates not only a single
boids, but has to repel a boid in question based on the average position and velocity of any boid
that is within a distance away from the boid in question. Creating the behaviour of repulsion forces
in nature to give the system more chaotic motion.

### Alignment
Whenever the other boids are within a distance threshold to the current boid, they're velocities and
positions are averaged relative to the current boid. This is the alignment rule, which is similar to
when flocks migrate in nature and form very distinct follower patterns.

## References
John Macey, ParticleNGL code, sourced here: https://github.com/jmacey/ParticleNGL
Coding Train, Craig Reynolds implementation in java, sourced here: https://www.youtube.com/watch?v=mhjuuHl6qHM&list=PLgF_pcLMWjq8x9JbKCZyK4c0Uve32Obrl&index=2&t=1552s
Craig Reynolds, Boids background and update, sourced here: https://www.red3d.com/cwr/boids/
