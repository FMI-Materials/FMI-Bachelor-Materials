# Ai Chess
## Chess game, that uses stockfish

### Dependencies:
 - For graphics:
   - SFML (https://www.sfml-dev.org/)
 - Stockfish for linux:
   - python 3.6+ (with python3 alias)
   - python-chess (pip install python-chess)
   
### How does the computer play?
There are 2 game modes when competing against the computer. One of them uses stockfish, which is one of the best machine learning chess engines, and was connected using python. The other one was implemented by us and described below.

### About our game engine
Even though our game engine does not use any related machine learning algorithm, the computer moves the pieces based on a selection algorithm (greedy) as follow:

 - Searches for the best piece that can be remove
 - Searches the best peace under attack that can be moved
 - Searches the position that can lead to check
 - Based on an evaluation scheme (determined for each piece, based on the position where that piece should be on the table)
 - Moves to a random position

### Requirements
* [x] Graphic interface (**SFML**) 
* [x] RTTI (**dynamic_cast and static_cast**)
* [x] Abstract Classes (**in pieces**)
* [x] Operators (***12***)
* [x] Heap Memory Allocation (**in pieces**)
* [x] Exceptions (**catch in table.cpp, throw in brain.cpp**)
* [x] STL (**vectors**)
* [x] Lambda expressions (**rules.cpp Rules::getFuturePawn()**)
* [x] Templates (**materials.h**)
* [x] Smart pointers (**unique_pointer<>** + de adaugat inca unul)
* [x] Design patterns (maxim 4: Factory, Template Method, Singleton, Null Object)
* [x] Features of C++17/20 (***constexpr, consteval, constinit, fold expressions, init statement for if/switch, etc***) (**brain.cpp -> isOkToMove()**)

***More details here: https://darius.buhai.ro/project.php?p=ai_chess***


***Created by Darius Buhai, Ciorica Vlad and Ioan Savu Daniel. All rights reserved***
