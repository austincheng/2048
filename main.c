#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int gen_2_or_4()
{
   int x;

   x=rand()%5+1;

   if (x==1) {
      return 2;
   } else {
      return 1;
   }
}

int main()
{
   /* Creating the board array */
   int board[12][12];

   /* These variables will be used when a 2 or 4 needs to be generrated */
   int gennum, gennum2;

   /* These variables will be used to represent the dimensions in the array */
   int sw, sx, sy, sz;
   int w, x, y, z;

   /* This will be used for asking the user to enter a move or input */
   char input;

   /* This will be used to test if the game is over */
   bool gameover;

   /* These will be used to represent the placeholders and will be used to preoject the array */
   char*p2[12];
   p2[0]="-";
   p2[1]="2";
   p2[2]="4";
   p2[3]="8";
   p2[4]="16";
   p2[5]="32";
   p2[6]="64";
   p2[7]="128";
   p2[8]="256";
   p2[9]="512";
   p2[10]="1024";
   p2[11]="2048";

   /* Seeding the random number generator */
   srand(time(NULL));

   /* Showing instructions for the game */
   printf("Use the WASD Keyboard\n");
   printf("W-Up\n");
   printf("A-Left\n");
   printf("S-Down\n");
   printf("D-Right\n");

   /* Filling all values with -1 */
   for (x=0; x<12; x++) {
      for (y=0; y<12; y++) {
         board[x][y]=-1;
      }
   }

   /* Filling the actual board to be empty */
   for (x=4; x<8; x++) {
      for (y=4; y<8; y++) {
         board[x][y]=0;
      }
   }

   /* Generating a 2 or 4 to be placed on the starting board */
   gennum=gen_2_or_4();
   
   /* Generating a random spot to place the number */
   sx=rand()%4+4;
   sy=rand()%4+4;

   /* Placing the value in its spot */
   board[sx][sy]=gennum;

   /* Same process but with a second value */
   gennum2=gen_2_or_4();
   sw=rand()%4+4;
   sz=rand()%4+4;

   /* Checking if the two starting values are placed in the same spot */
   while (sx==sw && sy==sz) {
      sw=rand()%4+4;
      sz=rand()%4+4;
   }

   /* Placing the value in its spot */
   board[sw][sz]=gennum2; 

   /* Printing the starting board */
   for (x=4; x<8; x++) {
      for (y=4; y<8; y++) {
         printf("%s\t", p2[board[x][y]]);
      }
      printf("\n");
   }

   for (;;) {
      do
      {
         /* Taking in an input */
         scanf("%c", &input);

         /* Checking if the input is acceptable */
         if (input!='w' &&  input!='W' && input!='a' && input!='A' && input!='s' && input!='S' && input!='d' && input!='D') {
            printf("Please enter a correct input : W, A, S, or D: ");
         }

         /* Clearing the buffer for the input */
         while (getchar() != '\n') {} ;
      } while (input!='w' && input!='W' && input!='a' && input!='A' && input!='s' && input!='S' && input!='d' && input!='D');
      if (input=='w' || input=='W') {
         for (x=5; x<8; x++) {
            for (y=4; y<8; y++) {

               /* Checking if the spot on the board has a value */
               if (board[x][y]!=0) {

                  /* Checking if spots above have values */
                  if (board[x-3][y]==0) {
                     board[x-3][y]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x-2][y]==0) {
                     board[x-2][y]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x-1][y]==0) {
                     board[x-1][y]=board[x][y];
                     board[x][y]=0;
                  }
               }
            }
         }

         /* Combining Values that are the same */
         for (x=4; x<7; x++) {
            for (y=4; y<8; y++) {
               if (board[x][y]==board[x+1][y] && board[x][y]!=0) {
                  board[x][y]=board[x][y]+1;
                  board[x+1][y]=0;
               }
            }
         }

         /* Moving everything up to fill empty spaces */
         for (y=4; y<8; y++) {
            for (x=5; x<8; x++) {
               if (board[x][y]!=0) {
                  if (board[x-3][y]==0) {
                     board[x-3][y]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x-2][y]==0) {
                     board[x-2][y]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x-1][y]==0) {
                     board[x-1][y]=board[x][y];
                     board[x][y]=0;
                  }
               }
            }
         }

         /* Creating a random spot to place the random number */
         if (board[4][4]==0 || board[4][5]==0 || board[4][6]==0 || board[4][7]==0 || board[5][4]==0 || board[5][5]==0 || board[5][6]==0 || board[5][7]==0 || board[6][4]==0 || board[6][5]==0 || board[6][6]==0 || board[6][7]==0 || board[7][4]==0 || board[7][5]==0 || board[7][6]==0 || board[7][7]==0) {
            w=rand()%4+4;
            z=rand()%4+4;
            
            /* Checking if the random spot already has a value */
            while (board[w][z]!=0) {
               w=rand()%4+4;
               z=rand()%4+4;
            }

            /* Generating a random number and placing it in it's spot */
            gennum=gen_2_or_4();
            board[w][z]=gennum;
         }

         printf("\n\n\n");

         /* Printing the new board */
         for (x=4; x<8; x++) {
            for (y=4; y<8; y++) {
               printf("%s\t", p2[board[x][y]]);
            }
            printf("\n");
         }
      } else if (input=='a' || input=='A') {
         for (y=5; y<8; y++) {
            for (x=4; x<8; x++) {
               if (board[x][y]!=0) {
                  if (board[x][y-3]==0) {
                     board[x][y-3]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x][y-2]==0) {
                     board[x][y-2]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x][y-1]==0) {
                     board[x][y-1]=board[x][y];
                     board[x][y]=0;
                  }
               }
            }
         }

         for (y=4; y<7; y++) {
            for (x=4; x<8; x++) {
               if (board[x][y]==board[x][y+1] && board[x][y]!=0) {
                  board[x][y]=board[x][y]+1;
                  board[x][y+1]=0;
               }
            }
         }

         for (x=4; x<8; x++) {
            for (y=5; y<8; y++) {
               if (board[x][y]!=0) {
                  if (board[x][y-3]==0) {
                     board[x][y-3]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x][y-2]==0) {
                     board[x][y-2]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x][y-1]==0) {
                     board[x][y-1]=board[x][y];
                     board[x][y]=0;
                  }
               }
            }
         }
         if (board[4][4]==0 || board[4][5]==0 || board[4][6]==0 || board[4][7]==0 || board[5][4]==0 || board[5][5]==0 || board[5][6]==0 || board[5][7]==0 || board[6][4]==0 || board[6][5]==0 || board[6][6]==0 || board[6][7]==0 || board[7][4]==0 || board[7][5]==0 || board[7][6]==0 || board[7][7]==0) {
            w=rand()%4+4;
            z=rand()%4+4;

            while (board[w][z]!=0) {
               w=rand()%4+4;
               z=rand()%4+4;
            }
         
            gennum=gen_2_or_4();
            board[w][z]=gennum;
         }

         printf("\n\n\n");
       
         for (x=4; x<8; x++) {
            for (y=4; y<8; y++) {
               printf("%s\t", p2[board[x][y]]);
            }
            printf("\n");
         }
      } else if (input=='s' || input=='S') {
         for (x=6; x>3; x--) {
            for (y=4; y<8; y++) {
               if (board[x][y]!=0) {
                  if (board[x+3][y]==0) {
                     board[x+3][y]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x+2][y]==0) {
                     board[x+2][y]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x+1][y]==0) {
                     board[x+1][y]=board[x][y];
                     board[x][y]=0;
                  }
               }
            }
         }

         for (x=7; x>4; x--) {
            for (y=4; y<8; y++) {
               if (board[x][y]==board[x-1][y] && board[x][y]!=0) {
                  board[x][y]=board[x][y]+1;
                  board[x-1][y]=0;
               }
            }
         }

         for (y=4; y<8; y++) {
            for (x=6; x>3; x--) {
               if (board[x][y]!=0) {
                  if (board[x+3][y]==0) {
                     board[x+3][y]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x+2][y]==0) {
                     board[x+2][y]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x+1][y]==0) {
                     board[x+1][y]=board[x][y];
                     board[x][y]=0;
                  }
               }
            }
         }
         if (board[4][4]==0 || board[4][5]==0 || board[4][6]==0 || board[4][7]==0 || board[5][4]==0 || board[5][5]==0 || board[5][6]==0 || board[5][7]==0 || board[6][4]==0 || board[6][5]==0 || board[6][6]==0 || board[6][7]==0 || board[7][4]==0 || board[7][5]==0 || board[7][6]==0 || board[7][7]==0) {
            w=rand()%4+4;
            z=rand()%4+4;

            while (board[w][z]!=0) {
               w=rand()%4+4;
               z=rand()%4+4;
            }
         
            gennum=gen_2_or_4();
            board[w][z]=gennum;
         }

         printf("\n\n\n");
       
         for (x=4; x<8; x++) {
            for (y=4; y<8; y++) {
               printf("%s\t", p2[board[x][y]]);
            }
            printf("\n");
         }
      } else if (input=='d' || input=='D') {
         for (y=6; y>3; y--) {
            for (x=4; x<8; x++) {
               if (board[x][y]!=0) {
                  if (board[x][y+3]==0) {
                     board[x][y+3]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x][y+2]==0) {
                     board[x][y+2]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x][y+1]==0) {
                     board[x][y+1]=board[x][y];
                     board[x][y]=0;
                  }
               }
            }
         }

         for (y=7; y>4; y--) {
            for (x=4; x<8; x++) {
               if (board[x][y]==board[x][y-1] && board[x][y]!=0) {
                  board[x][y]=board[x][y]+1; 
                  board[x][y-1]=0;
               }
            }
         }

         for (x=4; x<8; x++) {
            for (y=6; y>3; y--) {
               if (board[x][y]!=0) {
                  if (board[x][y+3]==0) {
                     board[x][y+3]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x][y+2]==0) {
                     board[x][y+2]=board[x][y];
                     board[x][y]=0;
                  } else if (board[x][y+1]==0) {
                     board[x][y+1]=board[x][y];
                     board[x][y]=0;
                  }
               }
            }
         }
         if (board[4][4]==0 || board[4][5]==0 || board[4][6]==0 || board[4][7]==0 || board[5][4]==0 || board[5][5]==0 || board[5][6]==0 || board[5][7]==0 || board[6][4]==0 || board[6][5]==0 || board[6][6]==0 || board[6][7]==0 || board[7][4]==0 || board[7][5]==0 || board[7][6]==0 || board[7][7]==0) {
            w=rand()%4+4;
            z=rand()%4+4;

            while (board[w][z]!=0) {
               w=rand()%4+4;
               z=rand()%4+4;
            }
         
            gennum=gen_2_or_4();
            board[w][z]=gennum;
         }

         printf("\n\n\n");
       
         for (x=4; x<8; x++) {
            for (y=4; y<8; y++) {
               printf("%s\t", p2[board[x][y]]);
            }
            printf("\n");
         }
      }

      /* Setting gameover to be true and will be false if conditions below are reached */
      gameover=true;

      /* Checking if all the boxes are filled up and if adjacent squares aren't the same (Game is then over) */
      for (x=4; x<8; x++) {
         for (y=4; y<8; y++) {
            if (board[x][y]==board[x][y+1] && board[x][y]!=0) {
               gameover=false;
               break;
            } else if (board[x][y]==board[x+1][y] && board[x][y]!=0) {
               gameover=false;
               break;
            } else if (board[x][y]==0) {
               gameover=false;
               break;
            }
         }
         if (! gameover) {
            break;
         }
      }

      if (gameover) {
         printf("Game Over\n");
         exit(0);
      }
   }

   return 0;
}