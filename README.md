# 3D Gravitational Simulation

This project simulates the gravitational interactions between planets in a 3D space using Newton's Law of Universal Gravitation. It calculates forces, accelerations, and updates positions of planets iteratively over time, allowing for real-time graphical visualization of the system.

## Features
- Simulate gravitational forces between multiple planets in a 3D environment.
- Real-time coordinate updates with adjustable time intervals.
- Randomized initial positions and masses for planets, with support for both positive and negative coordinates.
- Stars implementation, with an option to create a central star in the simulation.
- Modular code structure for maintainability and scalability.
- Graphical User Interface (GUI) for visualizing the system, powered by Raylib.
- Parallel processing of gravitational calculations using threads to speed up computation.
- Scalable number of threads to optimize performance for large numbers of planets.
- Adjustable constants for gravitational force and time steps.

## Technologies Used
- **C Programming Language**: Core logic implementation.
- **Standard Libraries**: `stdio.h`, `stdlib.h`, `math.h`, `time.h`.
- **Raylib**: GUI and graphical representation for the simulation.
- **Pthread**: Parallel calculations to enhance performance.
- **Threading**: Distribute the gravitational force calculation across multiple threads for efficient processing.
  
## Requirements
- A C compiler that supports the C99 standard or later.
- Raylib library for graphics rendering (can be installed via package managers or built from source).
- Pthread library (usually included in most Unix-like systems).

## Usage
Upon running the simulation, the user will be prompted to:
- Create a central star (optional).
- Specify the number of planets in the simulation.
- The planets will have random initial positions and masses, with coordinates ranging from -1000 to 1000.

During the simulation, gravitational forces are calculated and applied in real time, with each planet's position updated iteratively. The graphical window will show a 3D visualization of the planets and star, allowing the user to observe their motion.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
