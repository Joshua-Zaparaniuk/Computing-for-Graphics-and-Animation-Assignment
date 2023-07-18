# Flocking System
This is a simple flocking system written using the NGL library, inspired by Craig-Reynolds flocking
behaviour. It depicts flocking behaviour of boids using 3 simple rules, cohesion, separation and
aggregation

## Class implementation
The way this class was implemented was by creating a flocking class, which handles the implementation
of system rules. Independent boid controls are implemented within a separate class Boids. Calculations
on a boid basis are implemented within the Boids class, whereas system calculations such as neighbour
groups and boid neighbour behaviours inherit some of their functionality from the Boids class.

## Flocking Rules

### Cohesion
This rule applies to boids from different neighbourhoods that approach a close proximity to one another.
In these use cases, the boids have an attraction to their neighbourhood pairs, which is also the first
rule of cohesion or attraction between neighbouring Boids.

### Separation
This is a force that repels neighbouring Boids from one another. It counteracts the Cohesion rule as it
pushes neighbouring Boids apart from one another.

### Aggregation
