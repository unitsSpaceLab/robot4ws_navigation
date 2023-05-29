# robot4ws_navigation
So far, autonomous navigation within a SLAM scenario on an uneven terrain has been implemented.

## Installation
Install ros navigation stack by executing:

```
sudo apt-get update
sudo apt-get install ros-melodic-navigation
```
## Usage

### Autonomous Navigation and SLAM
Launch the navigation package:
```
roslaunch robot4ws_navigation archimede_move_base.launch
```
It automatically launch 3D SLAM performed by cartographer and the navigation stack.

An rviz gui will appear. You can set there navigation goals and waypoints within the global map.

### Autonomous Exploration (TODO)
