**README**

Astronauts have to kill every Impostor to win or reach the ER, which is at the middle of the NxN grid. Impostors can kill if an astronaut is adjacent to them, but if there is a witness to this murder the impostor will be killed too! Impostors have to kill every living Astronaut in order to win!

The user can decide the N where the map is an NxN grid, choose the locations of the stationery Impostors and the Astronauts that can move 1 block vertically or horizontally per step. 

Every astronauts/impostors' location and whether it is alive or dead will be outputted to the console for each step, there will also be visual representation after the round is played, a .txt file will be created and written for each step with a cool ASCII representation.


$ gcc -std=gnu99 -g among\_us.c -o main

- Suggested before every run.



Text files input_text_0.txt, input_text_1.txt .... input_text_3.txt are the arguments to be given to among\_us.c
Custom setups can be created using the Input format given below.

﻿**Example run**

./main input_text_3.txt

Every step of the game will be outputed to the terminal with alive & dead impostors and astronauts. Also text files with the name of input\_text\_X\_out\_Y\_vis.txt where X is the input file number and Y is the step name.



﻿**Input Format**

X (Astronaut count)

Y (Impostor count)

N (Dimension parameter)

S (Step count)

2,3 & ... & 3,7 (Astronaut coordinates)

3,5 & ... & 5,7 (Impostor coordinates)



﻿**Output Format**

#DeadImpostors (Dead impostors)

Y - #DeadImpostors (Alive impostors)

#DeadAstronauts (Dead astronauts)

X - #DeadAstronauts (Alive astronauts)

Victory (Status - One of {Defeat, Victory, Continue})

2, 3, Alive & ... & 3, 7, Dead (Astronaut status)

3, 5, Alive & ... & 5, 7, Alive (Impostor status)














