# robot4ws_navigation
So far, autonomous navigation within a SLAM scenario has been implemented.

## Installation
Install ros navigation stack by executing:

```
sudo apt-get update
sudo apt-get install ros-melodic-navigation
```
## Usage

### Autonomous Navigation and SLAM
Launch a SLAM node publishing a map, for example:
```
roslaunch robot4ws_slam archimede_cartographer_3dslam.launch
```

Therefore, launch the navigation package:
```
roslaunch robot4ws_navigation archimede_move_base.launch
```

An rviz gui will appear. You can set there navigation goals and waypoints within the global map.