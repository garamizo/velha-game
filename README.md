# velha
Tic tac toe game against an invencible oponent

## Algorithm

*Evaluating moves.* Move is GOOD if leads to victory. Otherwise, BAD if oponent has a move that leads to his victory. Otherwise, UNKNOWN.

## How to play

Clone repository in catkin workspace and compile from source

```bash
cd ~/catkin_ws/src
git clone https://github.com/garamizo/velha.git
catkin_make --pkg velha
```

Execute with

```bash
rosrun velha play
```
