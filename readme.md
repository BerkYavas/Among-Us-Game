**README**

$ gcc -std=gnu99 -g among\_us.c -o main

- Suggested before every run.



Text files input\_text\_0, input\_text\_1 .... input\_text\_3 are the arguments to be given to among\_us.c

Example run: 

./main input\_text\_0

Every step of the game will be outputed to the terminal with alive & dead impostors and astronauts. Also text files with the name of input\_text\_X\_out\_Y\_vis.txt where 

X is the input file number and Y is the step name.



Input Format

X (Astronaut count)

Y (Impostor count)

N (Dimension parameter)

S (Step count)

2,3 & ... & 3,7 (Astronaut coordinates)

3,5 & ... & 5,7 (Impostor coordinates)



Output Format

#DeadImpostors (Dead impostors)

Y - #DeadImpostors (Alive impostors)

#DeadAstronauts (Dead astronauts)

X - #DeadAstronauts (Alive astronauts)

Victory (Status - One of {Defeat, Victory, Continue})

2, 3, Alive & ... & 3, 7, Dead (Astronaut status)

3, 5, Alive & ... & 5, 7, Alive (Impostor status)














