#ifndef __COMMAND_H__
#define __COMMAND_H__

enum Command {
    DoNothing = 0, 
    Left, Right, 
    Clockwise, Counterclockwise, 
	Down, Drop, 
    LevelUp, LevelDown,
    Restart,
    I, J, L, O, S, T, Z,
    Hint, 
    Random, NoRandom,
    Sequence
}; 

#endif 
