#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int N, iteration;
int dead_astro_count = 0; int dead_imp_count = 0;
int astro_count, imp_count;
enum game_status {Defeat, Victory, Continue};
enum game_status g_stat;

struct Impostor {
  bool is_alive;
  int x, y;
};

struct Astronaut {
  bool is_alive;
  int x, y;
};

struct People {
  struct Astronaut * astronauts;
  struct Impostor * impostors;
};


int distance(int x1, int y1 , int x2, int y2){
/* calculates distance between two cells. Do not use sqrt for simplicity. */
	int x_dif = x1-x2;
	int y_dif = y1-y2;
	
return (x_dif * x_dif + y_dif * y_dif);
}




struct People * read_from_file(const char *filename){



	FILE *input = fopen(filename, "r");
	
	
	const unsigned MAX_LENGTH = 256;
	char lines [6][256];
	int index = 0;
	
	
	while(!feof(input) && !ferror(input)) {
       /* we open the first input file and read accordingly */
	if ( fgets(lines[index],MAX_LENGTH,input) != NULL ) {
	index++;		
}
	}
	fclose(input);

        /* we use the stored lines to get the information */
	astro_count = atoi(lines[0]);
	imp_count = atoi(lines[1]);	
	N = atoi(lines[2]);
	iteration = atoi(lines[3]);

	/* we get the coordinations of astronauts and impostors */
	char astro_coord [50];     strcpy(astro_coord,lines[4]);
	char impostor_coord [50];  strcpy(impostor_coord, lines[5]);
	
	char *coordinate;
    	char *astro_loc[astro_count];
    	int i = 0;
    
	/* we seperate the strings using strtok, & is not needed */
    	coordinate = strtok(astro_coord, " &");
    	while(coordinate != NULL)
    	{
        astro_loc[i] = coordinate;
        coordinate = strtok(NULL, " &");
        i++;
    }
        /* we do the same procedure again for imp coordinations */
	char *coordinates2;
	char *impo_loc[imp_count];
	int k = 0;
	coordinates2 = strtok(impostor_coord," &");
	while(coordinates2 != NULL)
	{
	impo_loc[k] = coordinates2;
	coordinates2 = strtok(NULL," &");
	k++;
    }	

	/* using dynamic memory to store people, astronauts and impostors list we will work on */
	struct Impostor * impostors = malloc(imp_count * sizeof(struct Impostor)); 
	struct Astronaut * astronauts =  malloc ((astro_count) * sizeof(struct Astronaut));
	struct People *people =  malloc(sizeof(struct People));


	/* initializing the astronauts with the astro_loc location string */
	for(int ast = 0; ast < astro_count ; ast++){
	astronauts[ast].is_alive = true;
	char* x_str = strtok(astro_loc[ast], ",");
    	char* y_str = strtok(NULL, ",");
    	astronauts[ast].x = atoi(x_str);
    	astronauts[ast].y = atoi(y_str);
}
        /* creating impostors the same way we initialized astronauts */
	for (int imp = 0; imp < imp_count ; imp++) {
	impostors[imp].is_alive = true;
	char * x_str = strtok(impo_loc[imp], ",");
	char* y_str = strtok(NULL, ",");
	impostors[imp].x = atoi(x_str);
        impostors[imp].y = atoi(y_str);
}
/* we initialize the impo and astro lists to the struct people */
people->astronauts = astronauts;
people->impostors = impostors;


return people;

}
void move_astronauts(struct Astronaut * astronauts){

/* for every alive astronaut we move them to the ER */
 for (int i = 0; i<astro_count; i++){
    if (astronauts[i].is_alive) {
        if (astronauts[i].y != N) { // first vertically, then horizantally
   astronauts[i].y = (N > astronauts[i].y) ? astronauts[i].y +1 : astronauts[i].y - 1; 	   
 }     
	else if  (astronauts[i].y == N && astronauts[i].x != N) {
   	
   astronauts[i].x = (N > astronauts[i].x) ? astronauts[i].x + 1 : astronauts[i].x-1;
   
   } 
    }
 }
}

void bonus_write_file(char *in_fname, struct People *people, int cur_iteration){


    char out_fname [50]; 
    /* we create the correct output file name using snprintf */
    snprintf(out_fname, sizeof(out_fname), "%.*s_out_%d_vis.txt", (int)strlen(in_fname) - 4, in_fname, cur_iteration);
    
    FILE *fp;
    /* write the file, create if does not exist, overwrite if it does. "w" does it all */
    fp = fopen(out_fname,"w");
    if (fp == NULL){
    printf("Something went wrong badly");
    }


    /* this part is for using ~ to enclose the lines. 8*N+6 comes from the length of the pixels, works for all dimensions. */
    char border[8*N+6];
    memset(border, '~', 8*N+6);
    border[8*N+5] = '\0';
    /* write the file using fprintf */
    fprintf(fp,"%s\n",border);

for (int p = 0; p < 2*N+1 ; p++) {
   char line [500] = "";	

for (int l = 0 ; l < 2*N +1 ; l ++) {
	char cell [7];
	strcpy(cell,"|   ");
	int to_put = 1;
   if (l==N && p == N) {
   /* adding the ER to the middle */
   cell[1] = 'E';   cell[2] = 'R';

   }

   else{
   /* putting alive astronauts to the 2D representation accordingly */
   for (int i = 0; i < astro_count ; i++) {
      if ( people->astronauts[i].x == l && people->astronauts[i].y == p && people->astronauts[i].is_alive == true) {
      
      cell[to_put] = 'A';
      to_put ++; 
      } 
   }
   /* putting alive impostors to the 2D representation accordingly */
   for (int k = 0; k < imp_count ; k ++) {
   
    if (people->impostors[k].x == l && people->impostors[k].y == p && people->impostors[k].is_alive == true) {
    
    cell[to_put] = 'I';
    to_put++;
    
    
    }
   }


   }

strcat(line,cell);

   }
/* adding the seperator | between cells, printing the lines */
strcat(line,"|");
fprintf(fp,"%s\n",line);
fprintf(fp,"%s\n",border);
}
fclose(fp);

}



void write_a_file(char * in_fname, struct People * people, int cur_iteration){
    
    char out_fname[50];
    /* we creat the output file name accordingly with snprintf */
    snprintf(out_fname, sizeof(out_fname), "%.*s_out_%d.txt", (int)strlen(in_fname) - 4, in_fname, cur_iteration); 
    
   /* using I/O to write the file */
    FILE *fp;
    fp = fopen(out_fname, "w");

    if (fp == NULL) {
        printf("Error opening file!\n");
    }


/* fprintf writes the file fit to the instruction format */
fprintf(fp,"%d\n",dead_imp_count );
fprintf(fp, "%d\n", imp_count-dead_imp_count);
fprintf(fp, "%d\n",dead_astro_count );
fprintf(fp, "%d\n", astro_count - dead_astro_count);

char * victory = "Victory";
char * defeat = "Defeat";
char * continu = "Continue";

char *p;
/* we use a char pointer named p to print the game status depending on the value of enum g_stat */
if (g_stat == Victory) {

p = victory;
}
else if (g_stat == Defeat) {
p = defeat;}
else { p = continu;    }

fprintf(fp,"%s\n",p);


char astro_result [256]= "";
/* we print the location and the is_alive of the astronauts */
for (int i = 0; i < astro_count; i++) {
        char temp[20];
    sprintf(temp, "%d, %d, %s", people->astronauts[i].x, people->astronauts[i].y, people->astronauts[i].is_alive ? "Alive" : "Dead");
    strcat(astro_result, temp);


    if (i != astro_count-1) {
        strcat(astro_result, " & ");
    }
}

fprintf(fp,"%s\n",astro_result);

/* we print the location and the is_alive of the impostors */
char imp_result[256] ="";
for (int k = 0; k < imp_count; k++){
    char tmp[20];
    sprintf(tmp, "%d, %d, %s", people->impostors[k].x, people->impostors[k].y, people->impostors[k].is_alive ? "Alive" : "Dead");
    strcat(imp_result,tmp);

    if (k != imp_count -1 ) {
    strcat(imp_result," & " );
    }

}
fprintf(fp,"%s\n",imp_result);

    // Close the file
    fclose(fp);

}

void print_state(struct People * people){
/* all of this code is the same with write_a_file except we use printf instead of fprintf for a file */

printf("%d\n", dead_imp_count);
printf("%d\n",(imp_count - dead_imp_count));
printf("%d\n",dead_astro_count);
printf("%d\n",(astro_count-dead_astro_count));

char * victory = "Victory";
char * defeat = "Defeat";
char * continu = "Continue";

char *p;

if (g_stat == Victory) {

p = victory;
}
else if (g_stat == Defeat) {
p = defeat;}
else { p = continu;    }

printf("%s\n",p);

char astro_result [256]= "";

for (int i = 0; i < astro_count; i++) {
	char temp[20];
    sprintf(temp, "%d, %d, %s", people->astronauts[i].x, people->astronauts[i].y, people->astronauts[i].is_alive ? "Alive" : "Dead");
    strcat(astro_result, temp);

	
    if (i != astro_count-1) {
        strcat(astro_result, " & ");
    } 
}

printf("%s\n",astro_result);


char imp_result[256] ="";
for (int k = 0; k < imp_count; k++){
    char tmp[20];
    sprintf(tmp, "%d, %d, %s", people->impostors[k].x, people->impostors[k].y, people->impostors[k].is_alive ? "Alive" : "Dead");
    strcat(imp_result,tmp);

    if (k != imp_count -1 ) {
    strcat(imp_result," & " );
    }

}
printf("%s\n",imp_result);
printf("\n");

}





void next_state(struct People * people){
       /* we first move the astronauts using the function we wrote */
	move_astronauts(people->astronauts);

	/* going through every astronaut for every impostor */
	for (int i = 0; i < imp_count ; i++){
		for (int k = 0; k < astro_count; k++) {
		
        /* using pointers to point to the current astronaut and impostor, makes the code readability better */		
	struct Impostor  *curr_imp = &people->impostors[i];
	struct	Astronaut *curr_astro = &people->astronauts[k];
		
	        /* checking conditions for killing, witnesses, for only alive impostors and astronauts gets to do action obviously */
		if (distance(curr_imp->x, curr_imp->y,curr_astro->x,curr_astro->y  ) == 0 && curr_astro->is_alive && curr_imp->is_alive){
			int witn_exist = 0;
			for (int l = 0; l < astro_count; l++) {
			    if (people->astronauts[l].is_alive  && distance(curr_imp->x, curr_imp->y, people->astronauts[l].x, people->astronauts[l].y) == 1   ) {
			    
			    witn_exist= 1;
			    } 
			
			}
                        /* no witness, time to chop chop */
			if (witn_exist == 0){
			curr_astro->is_alive = false;
			dead_astro_count ++;
		        int look_ex = 0;
			
				for (int z= 0; z < astro_count; z++){
				
				if (people->astronauts[z].is_alive && distance(curr_imp->x,curr_imp->y, people->astronauts[z].x, people->astronauts[z].y  )== 2) {
					curr_imp->is_alive = false;
					dead_imp_count ++;
      }
     }						
    }		
   }
  }	
 }
}

void update_game_status(struct People * people){

/* conditions for game status, will be set false if any situation doesnt fit */
bool astro_all_dead =true; 
bool impo_all_dead = true;
bool all_astro_er = true;

for (int i = 0; i < astro_count; i++){
    
   if (people->astronauts[i].is_alive == true) {
     astro_all_dead = false;
   
   }  

   if (people->astronauts[i].is_alive == true) {
   if (people->astronauts[i].x != N || people->astronauts[i].y != N        ) {
   all_astro_er = false;
   }
 }
}

for (int k = 0; k < imp_count; k++){
if (people->impostors[k].is_alive == true) {
   
   impo_all_dead = false;
}
}

/* checking for all dead imp, all dead astro or all astro in ER, changing g_stat accordingly with the bool values we checked */
if (dead_imp_count == imp_count) {
	g_stat = Victory;
}
else if (astro_count == dead_astro_count) {
	g_stat = Defeat;
}
else if (all_astro_er == true && astro_all_dead == false) {

	g_stat = Victory;

}
else { g_stat = Continue;

}


}

int main(int argc, char **argv)
{
  int cur_iteration = 0;
  char * filename = argv[1];
  g_stat = Continue;

  struct People * people = read_from_file(filename);
/* printing the file name like it was done in the example output */
 printf("\nfilename: %s\n", filename); 
	
  print_state(people);
  write_a_file(filename, people, cur_iteration);
  bonus_write_file(filename,people,cur_iteration);
  for(cur_iteration = 1; cur_iteration < iteration; ++cur_iteration){

    /* calling the functions accordingly, playing the game, updating status and printing,writing the correct outputs */
    next_state(people);
    update_game_status(people);
    print_state(people);
    write_a_file(filename, people, cur_iteration);
    bonus_write_file(filename,people,cur_iteration);
    if(g_stat == Victory || g_stat == Defeat){
      break;
    }
  }

 // freeing the heap memory we used.
 free(people->astronauts);
 free(people->impostors);
 free(people); 
  
 return 0;
} 
