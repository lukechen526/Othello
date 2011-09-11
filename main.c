/*Written in 2004*/

#include <stdio.h>
#include <stdlib.h>
#define PASS 9999
#define BLACK 1
#define WHITE -1
#define BLANK 0
#define READ 0
#define WRITE 1

struct board

{
	int cells[8][8];
	int score_black;
	int score_white;
	int turn;
};
struct move 
{
	int x;
	int y;	
};

int position_evaluater(struct board board_evaluate);
void board_io(struct board* board, int option);
int drawboard(struct board* board_draw);
int test_direction(struct board*board_check,int x,int y,int direction);
int test_legalmove(struct board *board_check, int x,int y);
int legalmove_available(struct board*board_check1);
int beststrategy_entry(struct board *currentboard, struct move *bestmove, int depth);
int beststrategy_search(struct board board_cache, int depth);
void update(struct board* board_destiny, struct board* board_source, int x, int y);
int badmoves(struct board board_evaluate, int i, int j); 
struct move move_cache;

int main(int argc, char*arg[])
{
  /*declaration*/
    int player,i,j;
	struct board masterboard;
    int masterboard_board[8][8];
	struct move the_move;
    int passcounter=0; 
	int legalmovemade=0;
  /*end of declaration*/




/*initialization*/

	masterboard.score_black=2;
	masterboard.score_white=2;
	masterboard.turn=BLACK;
	
	for(i=0; i<8; i++)
	{
		for (j=0;j<8;j++)
		{
			masterboard.cells[i][j]=0;
		}
		
	}


	masterboard.cells[3][3]=WHITE;
	masterboard.cells[4][3]=BLACK;
	masterboard.cells[3][4]=BLACK;
	masterboard.cells[4][4]=WHITE;
	
	masterboard.turn=BLACK;
	/*end of initialization*/
	
	printf("Das Panzer by Luke Chen, at Mathcamp 2004\n\n"); /*credit*/ 
	printf("CPU vs Player (1) or Player vs Player (2)");/*choose between the type of game*/
	
	scanf("%d",&player);



	if(player==3)
	{
		masterboard.score_black=0;
		masterboard.score_white=0;
		board_io(&masterboard,READ);
		player=0;
		
	}
	else if(player==4)
	{
	    masterboard.score_black=0;
		masterboard.score_white=0;
		board_io(&masterboard,0);
		player=1;
	
	}


/*the interaction between man and comp*/
	drawboard(&masterboard);
	if(player==1)
	{ 
    	printf("CPU goes first(1) or Man goes first(2)?\n"); 
    	scanf("%d",&player); 
    	
    	if(player==2)
    	{   
    		player=1;
        	goto HERE;
        	
    	}
    }    
	while(((masterboard.score_black+masterboard.score_white)!=64)&&(masterboard.score_black!=0)&&(masterboard.score_white!=0)&&(passcounter<2)) 
	/*if the board is not full and no one has been completely destroyed */
	{   
	passcounter=0; 
    legalmovemade=0;
 	/*the player can make a move only if there are available cells for legal moves*/

	/* BLACK's control*/	

	if(player==2)
	{
  		masterboard.turn=BLACK;
		if(legalmove_available(&masterboard)==1)
		{

			printf("This is Black's turn.\n\n");



while(legalmovemade!=1)
{  /*this part will loop untill the player makes a legal move*/
printf("Please type in the coordinate of the desired cell\n"); /*the player's move*/
scanf("%d %d", &(the_move.x),&(the_move.y));/*get the coordinate*/
if(test_legalmove(&masterboard,the_move.x, the_move.y)==1){  /*test if it is a legal move*/
update(&masterboard,&masterboard,the_move.x,the_move.y);
legalmovemade=1;

}

else {

	printf("This move is not a legal move\n");
	 /*if not a legal move, tell the player*/
    legalmovemade=0;}}}

else {printf("You cannot make any legal move, pass.\n");
      passcounter+=1; 
}
drawboard(&masterboard);
}

else if ((player==1)||(player==0)){  /*When the player chooses to compete against the AI*/

printf("This is CPU's turn\n\n");
if(legalmove_available(&masterboard)==1)
{   beststrategy_entry(&masterboard,&the_move,6);
  /*the computer, or black, moves first*/
	update(&masterboard,&masterboard,the_move.x,the_move.y);
	printf("The move is %d  %d\n",the_move.x,the_move.y);
  drawboard(&masterboard);}
else
	{printf("CPU passes\n");
	passcounter+=1;
    drawboard(&masterboard);/*computer passes*/
   }
/*endd of BLACK's control*/
HERE:
     
legalmovemade=0;
 masterboard.turn=WHITE;

if(player!=0){/*when it is not AI vs AI mode*/

if(legalmove_available(&masterboard)==1){ /*the player can make a move only if there are available cells for legal moves*/

	   printf("This is White's turn.\n\n");
while(legalmovemade!=1)
{  /*this part will loop untill the player makes a legal move*/

printf("Please type in the coordinate of the desired cell\n"); /*the player's move*/

scanf("%d %d", &(the_move.x),&(the_move.y));/*get the coordinate*/

if(test_legalmove(&masterboard,the_move.x,the_move.y)==1){  /*test if it is a legal move*/


update(&masterboard,&masterboard,the_move.x,the_move.y);
legalmovemade=1;
drawboard(&masterboard);
}

else {

	printf("This move is not a legal move\n");
	 /*if not a legal move, tell the player*/
    legalmovemade=0;
	}}}

else {
     masterboard.turn=BLACK;
	printf("You cannot make any legal move, pass.\n");
    passcounter+=1; }
 }
/*end of AI vs man*/

else
/* AI vs AI mode*/
{ masterboard.turn=WHITE;
  printf("This is CPU WHITE's turn\n\n");
if(beststrategy_entry(&masterboard,&the_move,3)!=PASS){     /*the computer, or black, moves first*/
	update(&masterboard,&masterboard,the_move.x,the_move.y);
    printf("The move is %d  %d\n",the_move.x,the_move.y);
     drawboard(&masterboard);
}
else
	{	printf("CPU WHITE passes\n");
	    passcounter+=1; 
		drawboard(&masterboard);/*computer passes*/}}
/*end of AI vs AI*/
board_io(&masterboard,WRITE);
}}
/*decide who wins the game*/
if(masterboard.score_black>masterboard.score_white){
	printf("CPU wins\n");
	}
else if(masterboard.score_black<masterboard.score_white){
	printf("Congratulation, You have won the game.\n");
	}

else{printf("It is a tie.\n");
    }

  getchar(); 
/*end of this part*/
  return 0;}





int drawboard(struct board* board_draw)
{    int q;int p;
   
	for(q=7;q>=0;q--){
		printf("%d",q);
	  for(p=0;p<8;p++){


		  switch(board_draw->cells[p][q])
		  {

			  case BLACK:
				 printf("|O");
				 break;
			  case WHITE:
				  printf("|X");
				  break;
			  case BLANK:
				   printf("| ");
				   break;

				}
			}

            printf("|");
			printf("\n");
		}
		printf("  0 1 2 3 4 5 6 7\n");
		printf("Black:%d    White:%d\n",board_draw->score_black, board_draw->score_white);
        return 0;}

int test_direction(struct board *board_check, int x,int y,int direction)
{

/*test if there is any cell with the opposite color around the desired cell*/
    int i=2;
	int k=0;

    int turn=board_check->turn;
	int invturn=-1*turn;

if(board_check->cells[x][y]==BLANK){

switch(direction){

case 1:
	 if( (x-1>=0)&&(y-1>=0)){
    i=2;
if((board_check->cells[x-1][y-1]== invturn)){

		  while( (x-i>=0)&&(y-i>=0)){
			  if(board_check->cells[x-i][y-i]!=invturn){
			  break;
			} i+=1;  }
           	if((x-i>=0)&&(y-i>=0)){
 if(board_check->cells[x-i][y-i]==turn)
 	  {k= 1;}}}
	}
break;
/*================================================*/
case 2:
 if((y-1>=0)){
         i=2;
if((board_check->cells[x][y-1]== invturn)){
		  while( y-i>=0){
			  if(board_check->cells[x][y-i]!=invturn){
			  break;
			}
  i+=1;  }
if(y-i>=0){
 if(board_check->cells[x][y-i]==turn)
  {k= 1;}}}
}
break;
/*====================================================*/
case 3:
	 if( (x+1<8)&&(y-1>=0)){
       i=2;
if((board_check->cells[x+1][y-1]== invturn)){
	  while( (x+i<8)&&(y-i>=0)){
			  if(board_check->cells[x+i][y-i]!=invturn){
			  break;
			}
               i+=1;  }
			if((x+i<8)&&(y-i>=0)){
			  if(board_check->cells[x+i][y-i]==turn)
			  {k= 1;}}	}}
break;
/*========================================================*/ 
case 4:
	 if( x-1>=0){
       i=2;
if((board_check->cells[x-1][y]== invturn)){
while(x-i>=0){
if(board_check->cells[x-i][y]!=invturn){
			 break;}

    i+=1;  }
if(x-i>=0){
 if(board_check->cells[x-i][y]==turn)
 {k= 1;}}}}
break;
/*==============================================================*/
case 5:
	 if(x+1<8){
       i=2;

if((board_check->cells[x+1][y]== invturn)){
		  while(x+i<8){
			  if(board_check->cells[x+i][y]!=invturn){
			  break;
			}
               i+=1;  }
			if(x+i<8){
			  if(board_check->cells[x+i][y]==turn)
			  {k= 1;}}	}	}
break;
/*==============================================================*/
case 6:
	 if( (x-1>=0)&&(y+1<8)){
         i=2;
if((board_check->cells[x-1][y+1]== invturn)){
		  while( (x-i>=0)&&(y+i<8)){
			  if(board_check->cells[x-i][y+i]!=invturn){
			  break;
			} i+=1;  }
			if((x-i>=0)&&(y+i<8)){
			  if(board_check->cells[x-i][y+i]==turn)
			  {k= 1;}}}
					}
break;
/*===============================================================*/
case 7:
if(y+1<8){i=2;
if((board_check->cells[x][y+1]== invturn)){
while( y+i<8){if(board_check->cells[x][y+i]!=invturn){break;}  i+=1;  }
			if(y+i<8){
			  if(board_check->cells[x][y+i]==turn)
			  {k= 1;}}}}
break;
/*=================================================================*/
case 8:
 if( (x+1<8)&&(y+1<8)){i=2;
if((board_check->cells[x+1][y+1]== invturn)){
while( (x+i<8)&&(y+i<8)){if(board_check->cells[x+i][y+i]!=invturn){break;}

i+=1;  }
if((x+i<8)&&(y+i<8)){if(board_check->cells[x+i][y+i]==turn)
 {k= 1;}
}}}break;

}}
return k;
}

/*================================================================*/
int test_legalmove(struct board* board_check,int x,int y)
{int k=0;

if((test_direction(board_check,x,y,1)==1)||(test_direction(board_check,x,y,2)==1)||(test_direction(board_check,x,y,3)==1)||
(test_direction(board_check,x,y,4)==1)||(test_direction(board_check,x,y,5)==1)||(test_direction(board_check,x,y,6)==1)||
(test_direction(board_check,x,y,7)==1)||(test_direction(board_check,x,y,8)==1))
   {k=1;}
	return k;
}
/*==============================================================*/
int legalmove_available(struct board* board_check1)

{

   int k=0;int m; int n; 
	for(m=0;m<8;m++){
		for (n=0;n<8;n++){
			
			if(test_legalmove(board_check1,m,n)==1)
				{k=1;}}}
return k;
}
int beststrategy_entry(struct board* currentboard, struct move* bestmove, int depth)

{  struct board board_cache;int value=PASS;int current=-99999; 
   int m=0; int n=0; 
   for(m=0;m<8;m++){

	for(n=0;n<8;n++){
if(currentboard->cells[m][n]==BLANK){
  if(test_legalmove(currentboard,m,n)==1) {      
update(&board_cache,currentboard, m,n);
 value=beststrategy_search(board_cache,depth-1);
printf("Good move= %d  %d  ",m,n); 
printf("The value=%d\n",value);
if(value>current){
current=value; bestmove->x=m; bestmove->y=n;}}}

}}
return value; /*If none of possible moves are legal, then beststrategy_entry will pass back PASS*/
}
/*================================================================*/
int beststrategy_search(struct board board_cache2,int depth){
   int p; int q; 
   
   int k=0;struct board board_cache3;
     int value=PASS;
	int current=-99999;

     
	if(depth>0){
for(p=0;p<8;p++){
  	for(q=0;q<8;q++){
if(board_cache2.cells[p][q]==BLANK){
                
if(test_legalmove(&board_cache2,p,q)==1){
    
   
    
 update(&board_cache3,&board_cache2,p,q);
  value=beststrategy_search(board_cache3,depth-1);
  if((board_cache2.turn*value)>current){    /*find the largest outcome, B-W if current player is B, -(B-W) if current player is W*/
	
	current=board_cache2.turn*value;
	
 if(value!=PASS){k= value;}
     
     }
} }

}}

/*if some moves are legal, in which case value!=PASS*/

 /*if all the moves are illegal, in which case value remains 65*/
if(value==PASS) {update(&board_cache3,&board_cache2,-1,-1); /*current player pass, update the board without making any change except give the control to the other player*/
value=beststrategy_search(board_cache3,depth-1);
 k=value;
}
}
if(depth==0){k=position_evaluater(board_cache2);}


return k;}
/*================================================================*/
void update(struct board* board_destiny, struct board* board_source, int x,int y){
int i=0;  int turn=board_source->turn; int invturn=(-1*turn); int score=0;

int m,n; 
if(board_destiny!=board_source){
			  for(m=0; m<8;m++){
				  for ( n=0;n<8;n++){
                       board_destiny->cells[m][n]=board_source->cells[m][n]; }}
                    } /*copy the board to destiny if it is not the same board*/

/*reverse the color in all eight directions*/
/*=================================================================*/
if(test_direction(board_source,x,y,1)==1){
i=1;
while( (x-i>=0)&&(y-i>=0)){
if(board_source->cells[x-i][y-i]!=invturn){
		break;}
board_destiny->cells[x-i][y-i]=turn;
score+=1;
i+=1;
}}
/*=================================================*/
if(test_direction(board_source,x,y,2)==1){
	i=1;
while(y-i>=0){

	if(board_source->cells[x][y-i]!=invturn){
		break;}

board_destiny->cells[x][y-i]=turn;
score+=1;
i+=1;}}
/*=================================================*/
if(test_direction(board_source,x,y,3)==1){
i=1;
while((x+i<8)&&(y-i>=0)){
if(board_source->cells[x+i][y-i]!=invturn){break;}
board_destiny->cells[x+i][y-i]=turn;
score+=1;
i+=1;
}}
/*=====================================================*/
if(test_direction(board_source,x,y,4)==1){i=1;
while(x-i>=0){if(board_source->cells[x-i][y]!=invturn){break;}
board_destiny->cells[x-i][y]=turn;
score+=1;
i+=1;}}
/*======================================================*/
if(test_direction(board_source,x,y,5)==1){
   i=1; while(x+i<8){if(board_source->cells[x+i][y]!=invturn){break;}
board_destiny->cells[x+i][y]=turn;
score+=1;
i+=1;}}
/*=========================================================*/
if(test_direction(board_source,x,y,6)==1){i=1;
while((x-i>=0)&&(y+i<8)){
if(board_source->cells[x-i][y+i]!=invturn){break;}board_destiny->cells[x-i][y+i]=turn;
score+=1;
i+=1;}}
if(test_direction(board_source,x,y,7)==1){i=1;
while(y+i<8){if(board_source->cells[x][y+i]!=invturn){break;}
board_destiny->cells[x][y+i]=turn;
score+=1;
i+=1;}}
/*=========================================================*/
if(test_direction(board_source,x,y,8)==1){i=1;
while((x+i<8)&&(y+i<8)){if(board_source->cells[x+i][y+i]!=invturn){break;}
board_destiny->cells[x+i][y+i]=turn;
score+=1;
i+=1;
}}

board_destiny->turn=-1*turn;
/*update score*/
if(turn==BLACK){
	board_destiny->score_black=board_source->score_black+score+1;
	board_destiny->score_white=board_source->score_white-score;}
	else if(turn==WHITE){
	board_destiny->score_black=board_source->score_black-score;
	board_destiny->score_white=board_source->score_white+score+1;}
	
board_destiny->cells[x][y]=turn;}
/*=============================================================*/
void board_io(struct board *board, int option){
     char readstring[65];int m,n; FILE*file; int i,j; 
	switch(option){
	case 0:
        file=fopen("game.dat","r+");
		fgets(&readstring[0],65,file);
		 for(m=0;m<8;m++){
            for(n=0;n<8;n++){
            
              switch(readstring[n+8*m]){
 case 'O':
board->cells[m][n]=1;
board->score_black+=1;
break;
/*=================================================*/
case 'X':
    board->cells[m][n]=-1;
    board->score_white+=1;
 break;
 case ' ':
board->cells[m][n]=0;
 break;}}}
 break;
case WRITE:
file=fopen("game.dat","w+");
 for(i=0;i<8;i++){
for(j=0;j<8;j++){

switch(board->cells[i][j]){
    case BLACK: fputc('O',file); break;
    case WHITE:fputc('X',file);break;
    case BLANK:fputc(' ',file);break;}}}
    break;}
fclose(file);}
/*===================================================*/
int position_evaluater(struct board board_evaluate){ 
	int i,j; int bw=0; int ww=0;  
	
	for(i=0;i<8;i++){
     for(j=0;j<8;j++){
         
        
             
             /*Caculate the weighed score for B and W*/ 
                       
  /*  corners   */
if( ((i==0)&&(j==0))||((i==0)&&(j==7))||((i==7)&&(j==0))||((i==7)&&(j==7)))
             
     { if(board_evaluate.cells[i][j]==BLACK)
           {bw+=25;}
     else if(board_evaluate.cells[i][j]==WHITE)
     {ww+=25; } }
/*  positions right next to the corner are disadvantageous */           
if( ((i==0)&&(j==1))||((i==1)&&(j==0))||((i==0)&&(j==6))||((i==1)&&(j==7))||((i==6)&&(j==0))||((i==7)&&(j==1))||((i==7)&&(j==6))||((i==6)&&(j==7))||((i==1)&&(j==1))||((i==6)&&(j==1))||((i==1)&&(j==6))||((i==6)&&(j==6)))
{

  if(board_evaluate.cells[i][j]==BLACK)
           {bw-=5;}
       else if(board_evaluate.cells[i][j]==WHITE){ww-=5; }



}
/*===============edges========================*/
else if((i==0)||(i==7)||(j==0)||(j==7))
   
   { if(board_evaluate.cells[i][j]==BLACK)
          {bw+=6;
          if((((board_evaluate.cells[i][j+1]==WHITE)&&(board_evaluate.cells[i][j-1]==BLANK))||((board_evaluate.cells[i][j-1]==WHITE)&&(board_evaluate.cells[i][j+1]==BLANK)))&&((i==0)||(i==7))){
              bw-=9;}
           else if((((board_evaluate.cells[i+1][j]==WHITE)&&(board_evaluate.cells[i-1][j]==BLANK))||((board_evaluate.cells[i-1][j]==WHITE)&&(board_evaluate.cells[i+1][j]==BLANK)))&&((j==0)||(j==7))){
              bw-=9;}   } /*a position on the edge is disadvantageous if there is an opponent piece next to it*/ 
    
     
       else if (board_evaluate.cells[i][j]==WHITE)
     {ww+=6; 
     if((((board_evaluate.cells[i][j+1]==BLACK)&&(board_evaluate.cells[i][j-1]==BLANK))||((board_evaluate.cells[i][j-1]==BLACK)&&(board_evaluate.cells[i][j+1]==BLANK)))&&((i==0)||(i==7))){
              ww-=9;}
          else if((((board_evaluate.cells[i+1][j]==BLACK)&&(board_evaluate.cells[i-1][j]==BLANK))||((board_evaluate.cells[i-1][j]==BLACK)&&(board_evaluate.cells[i+1][j]==BLANK)))&&((j==0)||(j==7))){
              ww-=9;}   
     
          }   
          
                       }                                                 
  
 /*======================== all other spaces==================*/  
 else
 { if(board_evaluate.cells[i][j]==BLACK)
     {bw+=1;}
     else if(board_evaluate.cells[i][j]==WHITE){ww+=1; }}
             
     }
     
     }
	
	
      
	return (bw-ww);}


