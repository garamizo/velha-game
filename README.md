# velha [![Build Status](https://travis-ci.com/garamizo/velha-game.svg?branch=travis)](https://travis-ci.com/garamizo/velha-game)
Tic tac toe game against an invencible oponent

## Algorithm

*Evaluating moves.* Move is GOOD if leads to victory. Otherwise, BAD if oponent has a move that leads to his victory. Otherwise, UNKNOWN.

## How to play

### Without ROS

Clone repository and compile source with cmake
```bash
git clone https://github.com/garamizo/velha-game.git
cd velha-game/velha
mkdir build
cd build
cmake ..
make
```

Run single player game with
```bash
./play
```

Use numerical keyboard to enter values.

### With ROS

Clone repository in catkin workspace and compile from source

```bash
cd ~/catkin_ws/src
git clone https://github.com/garamizo/velha.git
catkin_make --pkg velha && . devel/setup.bash
```

Run game server
```bash
rosrun velha_ros velha_server
```

And in two other windows, run player 1
```bash
rosrun velha_ros velha_player move:=move1
```

and player 2
```bash
rosrun velha_ros velha_player move:=move2
```

To enable expert mode hack, add `1234` as argument:
```bash
rosrun velha_ros velha_player 1234 move:=move2
```
