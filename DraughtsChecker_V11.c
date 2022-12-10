/*
Project Name: Draught Checkers Game
programming Language: C Language
Project Done By : 
    1. Karthick Srinivas S, Reg. No:
    2. Deepak Kumar,        Reg. No:
    3. Bala,                Reg. No:
    4. Kavin T              Reg. No

Purpose of the Program: Two player checkers board game.  
*/

//Standard Includes of C Library
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

/*
Function Module High Level Documentation
----------------------------------------
    1. student_intro : Display the initial screen of the game and students developed.
    2. rules_of_the_game: Display the rules and control details of the game.
    3. start_condition: Input the game choices - Start Game, Display History and Exit Game. Return the selection to main function.
    4. display_game_history: Displays the game played details stored in the gamelog.txt log file in tabular format
    5. logfile_generation: Creates new log file if the log file not present at the game directory. Also creates the game number control text file.
    6. get_player_details: Take input of the players from the user.
    7. initilize_board: Initialize the initial board setup. Player 1 will have checker marked 'O' and Player 2 will have the checkers marked 'X'. 
    8. print_player_details: After initial board display or update board display, refresh the game status - Checkers holding by player, King checkers holding by player and Active player.
    9. validate_source_input: validate the input provided by user for checker selection and validates the postion holds the players checker and not blank.
    10. validate_target_input: validate the move or capture requested and make sure the requested action is feasible. if not feasible raise alert return for input.
    11. move_checker: Moves the checker from the initial position to target postion inputed by the users and update the position details stored variables.
    12. update_board: Refresh the board with revised positions and status of the check after each action.
    13. capture_checker: Captures the opponent checker and update the checker count variables and checker position control file.
    14. check_more capture: After a successful capture, check for the feasibility of one more capture for the active player. If feasible player continues or switch player initiated.
    15. check_for_king_position: After every move the postion of the checker is validated. if it reached the last row the checker is converted into a King checker. King check is displayed with suffix 'K'.
    16. check_kingchecker: Called by other function modules to validate the checker worked upon is a king checker or normal checker. Returns Y- If the checker is King. 
    17. ascii_to_number: The board is designed as alphabets reference for x-axis and numerical for y-axis. Converting alphabet reference to number value to use the array position. 
*/

void student_intro();
void rules_of_the_game();
char start_condition();
void display_game_history();
void logfile_generation();
void generate_game_number(int *game_number);
void get_player_details(char player1_name[], char player2_name[]);
void initialize_board(int board[10][10], int player1_cheker_position[], int player2_cheker_position[],char player1_name[], char player2_name[],int game_number);
void print_player_details(char player1_name[], char player2_name[], int active_player, int player1_checkers, int player2_checkers, int player1_kingchekers, int player_kingchekers);
int validate_source_input(char si1, char si2, int board[10][10], int active_player);
int validate_target_input(char ti1, char ti2, char ti3, char si1, char si2, int board[10][10], int active_player, char helper_tmp, int player1_kingchekers, int player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[]);
void move_checker(int active_player, int player1_chekers, int player2_chekers,int player1_cheker_position[], int player2_cheker_position[], char si1, char si2, char ti2, char ti3, char helper_tmp, int *new_position, int player1_kingchekers, int player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[]);
void update_board(int board[10][10], int player1_cheker_position[], int player2_cheker_position[],char player1_name[], char player2_name[], int player1_kingchekers, int player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[], int game_number);
void capture_checker(int player1_cheker_position[], int player2_cheker_position[], char ti2, char ti3, int active_player, int *player1_checkers, int *player2_chekers, int *player1_kingchekers, int *player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[]);
char check_more_capture(int new_position, int active_player, int board[10][10], int player1_kingchekers, int player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[]);
void check_for_king_posiion(int new_position, int active_player, int player1_kingcheker_position[], int player2_kingcheker_position[],int *player1_kingchekers, int *player2_kingchekers );
char check_kingchecker(int active_player, int player1_kingchekers, int player2_kingchekers, int player1_kingcheker_position[], int player2_kingcheker_position[], int checker_position);
int ascii_to_number(char input);

int main()
{

/* 
Brief Explanation of the Variables
-----------------------------------
    1. FILE - File point for reading and writing the log file
    2. board - 2-Dimention array, holds the details of the checkers details
    3. player1_name and player2_name: Name of the players, input taken from the user.
    4. player1_cheker_position and player2_cheker_poition: Stores the current position of the checker in the board for player 1 and player 2. Once captured the postion is marked as blank space ascii code 32.
    5. player1_chekers and player2_chekers: Holds the count of active checkers of player 1 and player 2.
    6. source_input: Character array for storing the checker selection
    7. target_input: Character array for stoing the action step (Move or Capture) and target position.
    8. flag: Control variable for the program loop.
    9. si1, si2: Source input data split into individual coordinate elements. si1 stores the x-axis details and si2 stores the y-axis details.
    10. ti1, ti2, ti3: Variable target_input split and stored. ti1 stores the action detail - Move or Capture (m or c). ti2 and ti3 stores the x-axis and y-axis of the target position or opponent's checker postion.
    11. helper_tmp: Temporary variable used to pass the action Move or Capture during the function call.
    12. has_onemore: Stores the return value of the function check_more_capture. If Return value is Y - Player has option to capture more, N - No option to capture more. Player switch happens.
    13. sc: Initial Game selection - 49 - Play Game, 50-Display History log, 51- Exit game
    14. new_postion: Stores the check postion moved after capture. Used to check the feasibility free position during capture and move operation.
    15. active_player: Stores the current active player, value changes during switch of the player after each operation. Value 1-Player 1, 2-Player 2
    16. game_number: Stores the game number generated, the same is used to store in the game log and board display.
    17. rc_valudate: Function module return code storage
    18. i,j: Loop control variables. 
*/

    FILE *fpin, *fpout;
    int board[10][10];
    char player1_name[30], player2_name[30];
    int player1_cheker_position[12]={11,13,15,17,22,24,26,28,31,33,35,37};
    int player2_cheker_position[12]={62,64,66,68,71,73,75,77,82,84,86,88};
    int player1_kingcheker_position[12], player2_kingcheker_position[12];
    int player1_chekers=12, player2_chekers=12, player1_kingchekers=0, player2_kingchekers=0;
    char source_input[3], target_input[3], flag='T', si1, si2, ti1, ti2, ti3, helper_tmp, has_onemore='N', sc;
    int new_position, active_player= 1, game_number, rc_validate, i, j;

    // Steps 1: Display the Student Details in Welcome Screen
    student_intro();
    system("cls");
        
    // Steps 2: Take User Input for Play / History View / Exit
    sc = start_condition();

    // If User Input is to Exit
    if (sc == 51) 
    {
        printf("Exiting the Game...\n");
        return 0;
    }

    // If User Input is to View Game History
    if (sc == 50) 
    {
        printf("Showing the Previous Game Played History\n");
        display_game_history();
        return 0;
    }

    // If User Input is to Play the Game 
    if (sc == 49)
    {   
        // Step 3: Initiate the Game - Generate Game Number, Collect Player Details, Initialize the Checker Board
        rules_of_the_game();
        logfile_generation();
        generate_game_number(&game_number);
        get_player_details(player1_name, player2_name);
        initialize_board(board, player1_cheker_position, player2_cheker_position,player1_name, player2_name, game_number);

        //Step 4: Game Logic
        while (flag=='T')
        {
            // Function call to pring the player statistics - Number of checkers of normal and king and active player.
            print_player_details(player1_name, player2_name, active_player, player1_chekers, player2_chekers, player1_kingchekers, player2_kingchekers);

            if (player1_chekers==0)
            {
                if((fpin = fopen("Gamelog.txt","a+")) == NULL) printf("\nERRROR - Cannot open file\n");
                fprintf(fpin,"%d,%s,%s,%s,\n",game_number,player1_name,player2_name, player2_name);
                fclose(fpin);
                printf("\n**** C O N G R A G U L A T I O N S ****\n");
                printf("Player 1's all checkers captured, GAME Over !\n");
                printf("Player 2, Won the Game\n");

                break;
            }

            if (player2_chekers==0)
            {
                if((fpin = fopen("Gamelog.txt","a+")) == NULL) printf("\nERRROR - Cannot open file\n");
                fprintf(fpin,"%d,%s,%s,%s,\n",game_number,player1_name,player2_name, player1_name);
                fclose(fpin);
                printf("\n**** C O N G R A G U L A T I O N S ****\n");
                printf("Player 2's all checkers captured, GAME Over !\n");
                printf("Player 1, Won the Game\n");
                break;
            }

            // Get the source checker input and validate
            while(flag =='T')
            {
                printf("\nChoose the Checker to Move (ex. a3)\n");
                printf("To Exit Game - 'eg' or 'EG'\n");
                printf("Enter Your Selection co-ordinates :");
                scanf("%[^\n]%*c", source_input);
                si1=source_input[0];
                si2=source_input[1];

                if(((si1 =='E') & (si2=='G')) | ((si1 =='e') & (si2=='g')))
                {
                    if((fpin = fopen("Gamelog.txt","a+")) == NULL) printf("\nERRROR - Cannot open file\n");
                    if (active_player == 1 ) 
                    {
                        printf("\n**** C O N G R A G U L A T I O N S ****\n");
                        printf("Player 1 Ended the Game - GAME Over !\n");
                        printf("Player 2, Won the Game\n");

                        fprintf(fpin,"%d,%s,%s,%s,\n",game_number,player1_name,player2_name, player2_name);
                    }
                    else 
                    {
                        printf("\n**** C O N G R A G U L A T I O N S ****\n");
                        printf("Player 2 Ended the Game - GAME Over !\n");
                        printf("Player 1, Won the Game\n");
                        fprintf(fpin,"%d,%s,%s,%s,\n",game_number,player1_name,player2_name, player1_name);
                    }
                    fclose(fpin);
                    flag='E';
                    break;
                }
                
                // Validate the source input for the correctness.
                rc_validate = validate_source_input(si1, si2, board, active_player);
                
                if(rc_validate==1) 
                {
                    printf("Input Validation Completed, Moving to Next Step\n");
                    break;
                }
            }

            // Get the target checker input and validate
            while(flag == 'T')
            {
                printf("\nAction (M)ove or (C)apture\n");
                printf("To Move - Action+Co-ordinates(ex. mb4)\n");
                printf("To Capture - Action+Co-ordinates of opponent player's Checker (ex. cb4)\n");
                printf("To Reset and Go to previous step - 'rst' or 'RST'\n");
                printf("Enter the Action & Coordinates without space:");
                scanf("%[^\n]%*c", target_input);
                ti1=target_input[0];
                ti2=target_input[1];
                ti3=target_input[2];

                if (strlen(target_input) < 3)
                {
                    printf("Enter details of Action (M/C), followed by target postion to move.\n");
                    continue;
                }
                          
                if (((ti1 == 'R') & (ti2=='S')&(ti3=='T')) | ((ti1 == 'r') & (ti2=='s')&(ti3=='t')))
                {
                    printf("Reseting the input, going back to source selection.\n");
                    flag='T';
                    break;
                }

                // Sequence of function modules executed for move operation
                if((ti1 =='M') | (ti1=='m'))
                {
                    helper_tmp ='M';
                    rc_validate = validate_target_input(ti1, ti2, ti3, si1, si2, board, active_player, helper_tmp,  player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position);
                    if(rc_validate == 0)
                    {
                        continue;
                    }
                    if (rc_validate == 1)
                    {                                
                        printf("Validation Successful..Initating Movement of Checker\n");
                        move_checker(active_player, player1_chekers, player2_chekers, player1_cheker_position, player2_cheker_position, si1, si2, ti2, ti3, helper_tmp, &new_position, player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position);
                        check_for_king_posiion(new_position, active_player, player1_kingcheker_position, player2_kingcheker_position, &player1_kingchekers, &player2_kingchekers);
                        update_board(board, player1_cheker_position, player2_cheker_position,player1_name, player2_name, player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position, game_number);
                        if (active_player == 1) active_player=2;
                        else active_player=1;
                        break;
                    }
                }
                // Sequence of function modules executed for Capture operation
                else if((ti1 =='C') | (ti1=='c'))
                {
                    helper_tmp='C';
                    rc_validate = validate_target_input(ti1, ti2, ti3, si1, si2, board, active_player,helper_tmp, player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position);
                    if(rc_validate == 0)
                    {
                        continue;
                    }
                    if (rc_validate == 1)
                    {                                
                        printf("Validation Successful..Initating Capture of opponent Checker\n");
                        capture_checker(player1_cheker_position, player2_cheker_position, ti2, ti3, active_player, &player1_chekers, &player2_chekers, &player1_kingchekers, &player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position);
                        move_checker(active_player, player1_chekers, player2_chekers, player1_cheker_position, player2_cheker_position, si1, si2, ti2, ti3, helper_tmp, &new_position, player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position);
                        check_for_king_posiion(new_position, active_player, player1_kingcheker_position, player2_kingcheker_position, &player1_kingchekers, &player2_kingchekers);
                        has_onemore='N';
                        has_onemore =  check_more_capture(new_position, active_player, board, player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position);
                        update_board(board, player1_cheker_position, player2_cheker_position,player1_name, player2_name, player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position, game_number);
                        if ((active_player == 1) & (has_onemore=='Y')) 
                        {
                            active_player=1;
                            break;
                        }
                        if ((active_player == 1) & (has_onemore=='N'))
                        {
                            active_player=2;
                            break;
                        }
                        if ((active_player == 2) & (has_onemore=='Y'))
                        {
                            active_player=2;
                            break;
                        }
                        if ((active_player == 2) & (has_onemore=='N')) 
                        {
                            active_player=1;
                            break;
                        }
                    }


                }
                break;

            }
            if (flag == 'T') continue;
            else  break;
        }
        }
    return 0;
}

void student_intro()
{
    int bs=32;
    int ruc=201;
    int luc=187;
    int llc=200;
    int rlc=188;
    int hl=205;
    int vl=186;
    int lp=204;
    int rp=185;
    int i,j;
    
    char student1[30]="Bala Satvik";
    char student2[30]="Deepak Kumar";
    char student3[30]="Kavin T";
    char student4[30]="Karthick Srinivas";
    system("cls");
    printf("\n");
    printf("%c",ruc);
    for (i=0; i<=80;i++) printf("%c",hl);
    printf("%c\n",luc);

    printf("%c",vl);
    for (i=0;i<=80;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=19;i++) printf("%c",bs);
    printf("D R A U G H T   C H E C K E R S   G A M E");
    for (i=0;i<=19;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=80;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",lp);
    for (i=0;i<=80;i++) printf("%c",hl);
    printf("%c\n",rp);

    printf("%c",vl);
    for (i=0;i<=80;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=80;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    printf("   Game Developed By:  %s", student1);
    for (i=0;i<=46;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=22;i++) printf("%c",bs);
    printf("%s",student2);
    for (i=0;i<=(80-23-strlen(student2));i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=22;i++) printf("%c",bs);
    printf("%s",student3);
    for (i=0;i<=(80-23-strlen(student3));i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=22;i++) printf("%c",bs);
    printf("%s",student4);
    for (i=0;i<=(80-23-strlen(student4));i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=80;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=80;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",vl);
    for (i=0;i<=80;i++) printf("%c",bs);
    printf("%c\n",vl);
    printf("%c",llc);
    for (i=0; i<=80;i++) printf("%c",hl);
    printf("%c\n",rlc);

    printf("\nPress Any Key to Continue....\n");
    getch();
}

void rules_of_the_game()
{
    system("cls");
    printf("\n");
    printf("R U L E S  O F  T H E  G A M E:\n");
    printf("--------------------------------\n");
    printf("01. Checker board is marked with alphabets from 'a' to 'h' in x-axis and '1' to '8' in y-axis. \n");
    printf("02. Player 1 will start the game first. Player have the checkers makerd 'O' and Player 2 have the checkers marked 'X'.\n");
    printf("03. Movement of the direction is restricted to forward direction from the player side by one diagonal position only.\n");
    printf("04. Reverse move is not possibe. Only King checker can move forward and backwards.\n"); 
    printf("05. Movement of checkers allowed only in the dark shaded checks. White spaces cannot be used. it is marked with dot (.) in the checker board.\n");
    printf("06. The checker becomes King Checker when it reached the last row in the opposite side.\n");
    printf("07. A player can have any number of King Checkers at the same time. King Checkers can move forward and backward. Still one position only.\n");
    printf("08. After every move player switch happens, unless there is a possibility to capure more for the same user during previous capture move.\n");
    printf("09. During capturing the opponent's checker, it is jump over and occupy the vaccant space after that in the same diagonal direction.\n");
    printf("10. Movement of the checker not possible if all adjacent spaces are occuipied.\n");
    printf("11. Game ends if all the checkers are captured of a player or all checkers movement are blocked for a player.\n");
    printf("\n");

    printf("Directions to Play:\n");
    printf("--------------------------------\n");
    printf("Step 1: Choosing a checker\n");
    printf("01. Chose the checker first. To do that, input the co-ordinate as shown in the board.\n");
    printf("02. For chosing a checker of the active player at the co-ordinate of 'c' in x-axis and '3' in y-axis, user should enter 'c3'.\n");
    printf("03. System will do the needful validation of the selection and accepts the selection and move to next step.\n");
    printf("04. If all the checkers are blocked and need to end the game, type code 'EG' or 'eg'.\n");
    printf("\n");
    printf("Step 2: Performing action of (M)ove or (C)apture\n");
    printf("For Move Action:\n");
    printf("01. For Performing Move, the code to be used is 'm' and For Performing Capture, the code to be used is 'c'.\n");
    printf("02. Input the destination co-ordinates sufix to the action code (m/c). For example to move to b3, user should enter 'mb3'\n");
    printf("\n");
    printf("For Capture Action:\n");
    printf("01. Input the co-ordinates of the opponent checker postion to capture with the capture code.\n");
    printf("02. To capture a checker at b3, enter 'cb3'. System will move it to the next available postion.\n");
    printf("03. System will validate the capture and move feasibility before initiating. If not possible error message shown to correct. \n");
    printf("04. After error step, to rest and go-back to initial step use code 'RST' or 'rst'. This will restart the steps from choosing the checker.\n");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n");
    printf("Press Any Key To Continue......\n");
    getch();
}

void logfile_generation()
{
    FILE *cfPtr1 = fopen("Gamelog.txt", "r");
    if(cfPtr1 == NULL)
    {
        FILE *cfPtw1 = fopen("Gamelog.txt", "w");
        fclose(cfPtw1);
    }

    FILE *cfPtr2 = fopen("GameCount.txt", "r");
    if(cfPtr2 == NULL)
    {
        FILE *cfPtw2 = fopen("GameCount.txt", "w");
        fprintf(cfPtw2,"%d,\n", 0);
        fclose(cfPtw2);
    }
    fclose(cfPtr2);
    fclose(cfPtr1);
}

void generate_game_number(int *game_number)
{
    FILE *cfPtr = fopen("GameCount.txt", "r");
    int count=0, i,j=0, cc=0, gn=0, nc=0;
    char g_number[4],ch;
    int len;
    char line[10];
    
    if(cfPtr == NULL) 
    {
        puts("The file can't be open");
    }

    while((!feof(cfPtr)))
    {
        memset(line,0, 10);
        memset(g_number,0, 4);

        fgets(line, sizeof(line), cfPtr); 
        len=strlen(line);
       
        if(len > 0) 
        {
            for (i=0;i<=len;i++)
            {
                ch=line[i];
                if (ch ==',') break;
                g_number[j]=ch;
                j=j+1;
            }
        }
        if (len ==0) break;

        nc = strlen(g_number);
        if (nc==1) gn = g_number[0]-'0';
        if (nc==2) gn = (g_number[0]-'0')*10 + (g_number[1]-'0');
        if (nc==3) gn = (g_number[0]-'0')*100 + (g_number[1]-'0')*10 + (g_number[2]-'0');

    }
    fclose(cfPtr);
    FILE *pfout = fopen("GameCount.txt", "w");
    fprintf(pfout,"%d,",gn+1);
    fclose(pfout);
    *game_number = gn+1;
}

void get_player_details(char player1_name[], char player2_name[])
{
    printf("\n");
    printf("Enter Player 1 Name:");
    scanf("%[^\n]%*c", player1_name);
    printf("\n");
    printf("Enter Player 2 Name:");
    scanf("%[^\n]%*c", player2_name);
}

char start_condition()
{   
    char selection;
    int hl=196,i;
    system("cls");
    printf("\n");
    printf("Select 1 to Start the Game\n");
    printf("Select 2 to View the Game Play History\n");
    printf("Select 3 To Exit the Game\n");
    printf("\n");
    printf("Enter Your Choice:");
    scanf("%[^\n]%*c", &selection);
    return selection;      
}

void display_game_history()
{
    FILE *cfPtr = fopen("Gamelog.txt", "r");
    int count=0, i,j=0, cc=0, gn=0, nc=0;
    char game_number[4], player1_name[30], player2_name[30], winner[30], ch;
    int len;
    int bs=32;
    int vl=179;
    int luc=218;
    int ruc=191;
    int hl=196;
    int tt=194;
    int lt=195;
    int rt=180;
    int pl=197;
    int llc=192;
    int rlc=217;
    int it=193;

    if(cfPtr == NULL) 
    {
        puts("The file can't be open");
    }

    char  line[300];
    
    printf("%c",luc);
    printf("%c%c%c%c%c%c%c",hl,hl,hl,hl,hl,hl,tt);
    for (i=0;i<=50;i++) printf("%c",hl);
    printf("%c",tt);
    for (i=0;i<=30;i++) printf("%c",hl);
    printf("%c\n",ruc);

    printf("%c",vl);
    printf("%cGame%c",bs,bs);
    printf("%c",vl);

    printf("%cPlayers Details",bs);
    for(i=0;i<=50-16;i++) printf("%c",bs);
    printf("%c",vl);


    printf("%cWinner Details",bs);
    for(i=0;i<=30-15;i++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",lt);
    printf("%c%c%c%c%c%c%c",hl,hl,hl,hl,hl,hl,pl);
    for (i=0;i<=50;i++) printf("%c",hl);
    printf("%c",pl);
    for (i=0;i<=30;i++) printf("%c",hl);
    printf("%c\n",rt);

    while((!feof(cfPtr)))
    {
        memset(line,0, 300);
        memset(game_number,0, 4);
        memset(player1_name,0, 30);
        memset(player2_name,0, 30);
        memset(winner,0, 30);
        count =0;
        cc =0;
        j=0;
        gn=0;
        fgets(line, sizeof(line), cfPtr); 
        len=strlen(line);
        if(len > 0) 
        {
            for (i=0;i<=len;i++)
            {
                ch=line[i];
                if (ch ==',')
                {   cc = cc+1;
                    count = count+1;
                    j=0;
                    continue;
                }
                
                if (cc==4) break;
                if (count==0) game_number[j]=ch;
                if (count==1) player1_name[j]=ch;
                if (count==2) player2_name[j]=ch;
                if (count==3) winner[j]=ch;
                j=j+1;
            }
        }
        if (len ==0) break;

        nc = strlen(game_number);
        if (nc==1) gn = game_number[0]-'0';
        if (nc==2) gn = (game_number[0]-'0')*10 + (game_number[1]-'0');
        if (nc==3) gn = (game_number[0]-'0')*100 + (game_number[1]-'0')*10 + (game_number[2]-'0');

        printf("%c",vl);
        printf("%c%3d%c%c%c",bs,gn,bs,bs,vl);
        printf("%c%s vs %s", bs,player1_name, player2_name);
        for (i=0; i<50-strlen(player1_name)-4-strlen(player2_name); i++) printf("%c",bs);
        printf("%c",vl);
        printf("%c%s",bs, winner);
        for (i=0; i<30-strlen(winner); i++) printf("%c",bs);
        printf("%c",vl);
        printf("\n");

    }
    printf("%c",llc);
    printf("%c%c%c%c%c%c%c",hl,hl,hl,hl,hl,hl,it);
    for (i=0;i<=50;i++) printf("%c",hl);
    printf("%c",it);
    for (i=0;i<=30;i++) printf("%c",hl);
    printf("%c\n",rlc);


    fclose(cfPtr);
}

char check_kingchecker(int active_player, int player1_kingchekers, int player2_kingchekers, int player1_kingcheker_position[], int player2_kingcheker_position[], int checker_position)
{
    char kc='N';
    int i;
    if (active_player==1)
    {
        for (i=0; i< player1_kingchekers; i++)
        {
            if (checker_position == player1_kingcheker_position[i]) kc='Y';

        }
    }
    if (active_player==2)
    {
        for (i=0; i< player2_kingchekers; i++)
        {
            if (checker_position == player2_kingcheker_position[i]) kc='Y';

        }
    }
    return kc;
}

void check_for_king_posiion(int new_position, int active_player, int player1_kingcheker_position[], int player2_kingcheker_position[],int *player1_kingchekers, int *player2_kingchekers)
{
    int x, kcnum;
    x = new_position /10;
    if ((active_player == 1) & (x == 8))
    {
        *player1_kingchekers = *player1_kingchekers +1;
        kcnum = *player1_kingchekers;
        player1_kingcheker_position[kcnum-1]=new_position;
    }

    if ((active_player == 2) & (x == 1))
    {
        *player2_kingchekers = *player2_kingchekers +1;
        kcnum = *player2_kingchekers;
        player2_kingcheker_position[kcnum-1]=new_position;
    }

}

char check_more_capture(int new_position, int active_player, int board[10][10], int player1_kingchekers, int player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[])
{
    int x1,x2, y1, y2, x3, y3, x4, y4, s1, s2, tmp,i;
    char rt1='N', rt2='N', rt3='N', rt4='N', kc='N', kc1='N';
    s1 = new_position /10;
    s2 = new_position %10;

    kc = check_kingchecker(active_player, player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position, new_position);
/*
    if (active_player==1)
    {
        for (i=0; i< player1_kingchekers; i++)
        {
            if (new_position == player1_kingcheker_position[i]) kc='Y';
        }
    }

    if (active_player==2)
    {
        for (i=0; i< player2_kingchekers; i++)
        {
            if (new_position == player2_kingcheker_position[i]) kc='Y';

        }
    }
 */
    if (active_player == 1)
    {
        if (kc=='N')
        {
            x1 = s1+1;
            x2 = s1+1;
            y1 = s2+1;
            y2 = s2-1;

            if (board[x1][y1]== 88)
            {
                tmp= board[x1+1][y1+1];
                if (tmp == 32)
                {
                    rt1='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt1='N';
                }

            }
            if (board[x2][y2]== 88)
            {
                tmp= board[x2+1][y2-1];
                if (tmp == 32)
                {
                    rt2='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt2='N';
                }
            }

        }
        
        if(kc=='Y')
        {
            x1 = s1+1;
            x2 = s1+1;
            y1 = s2+1;
            y2 = s2-1;
            x3 = s1-1;
            x4 = s1-1;
            y3 = s2+1;
            y4 = s2-1;
            
            if (board[x1][y1]== 88)
            {
                tmp= board[x1+1][y1+1];
                if (tmp == 32)
                {
                    rt1='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt1='N';
                }

            }
            if (board[x2][y2]== 88)
            {
                tmp= board[x2+1][y2-1];
                if (tmp == 32)
                {
                    rt2='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt2='N';
                }
            }
            if (board[x3][y3]== 88)
            {
                tmp= board[x3-1][y3+1];
                if (tmp == 32)
                {
                    rt2='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt2='N';
                }
            }

            if (board[x4][y4]== 88)
            {
                tmp= board[x4-1][y4-1];
                if (tmp == 32)
                {
                    rt2='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt2='N';
                }
            }


        }

        if ((rt1=='Y')|(rt2=='Y')|(rt3=='Y')|(rt4=='Y')) return 'Y';
        else return 'N';
    }

    if (active_player == 2)
    {

        if (kc == 'N')
        {
            x1 = s1-1;
            x2 = s1-1;
            y1 = s2+1;
            y2 = s2-1;

            if (board[x1][y1]== 79)
            {
                tmp= board[x1-1][y1+1];
                if (tmp == 32)
                {
                    rt1='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt1='N';
                }

            }
            if (board[x2][y2]== 79)
            {
                tmp= board[x2-1][y2-1];
                if (tmp == 32)
                {
                    rt2='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt2='N';
                }
            }
        }

        if (kc =='Y')
        {
            x1 = s1-1;
            x2 = s1-1;
            y1 = s2+1;
            y2 = s2-1;
            x3 = s1+1;
            x4 = s1+1;
            y3 = s2+1;
            y4 = s2-1;
            if (board[x1][y1]== 79)
            {
                tmp= board[x1-1][y1+1];
                if (tmp == 32)
                {
                    rt1='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt1='N';
                }

            }

            if (board[x2][y2]== 79)
            {
                tmp= board[x2-1][y2-1];
                if (tmp == 32)
                {
                    rt2='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt2='N';
                }
            }

            if (board[x3][y3]== 79)
            {
                tmp= board[x3+1][y3+1];
                if (tmp == 32)
                {
                    rt3='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt3='N';
                }
            }

            if (board[x4][y4]== 79)
            {
                tmp= board[x4+1][y4-1];
                if (tmp == 32)
                {
                    rt4='Y';
                }
                else
                {
                    printf("Move to Destination cell is not possible\n");
                    rt4='N';
                }
            }
        }
        if ((rt1=='Y')|(rt2=='Y')|(rt3=='Y')|(rt4=='Y')) return 'Y';
        else return 'N';
    }

    
}

void capture_checker(int player1_cheker_position[], int player2_cheker_position[], char ti2, char ti3, int active_player, int *player1_chekers, int *player2_chekers, int *player1_kingchekers, int *player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[])
{
    int x, y, i, pos;
    int temp[12];
    x = ti3 -'0';
    char kc='N';
    int p1_cheker = *player1_kingchekers;
    int p2_cheker = *player2_kingchekers;
    int temp_active_player;
    y = ascii_to_number(ti2);
    pos = (x * 10) + y;
    if (active_player == 1)
    {
        for (i=0; i<12; i++)
        {
            if (player2_cheker_position[i] == pos)  player2_cheker_position[i] = 32;
        }
        *player2_chekers = *player2_chekers -1;
        temp_active_player=2;        
        kc = check_kingchecker(temp_active_player, p1_cheker, p2_cheker, player1_kingcheker_position, player2_kingcheker_position, pos);
        if (kc=='Y')
        {
            for (i=0; i<*player2_kingchekers; i++)
            {
                if (player2_kingcheker_position[i] == pos)  player2_kingcheker_position[i]=0;
                *player2_kingchekers = *player2_kingchekers -1;
            }
        }
    }
    else if (active_player == 2)
    {
        for (i=0; i<12; i++)
        {
            if (player1_cheker_position[i] == pos) player1_cheker_position[i]=32;
        }
        *player1_chekers = *player1_chekers -1;
        temp_active_player=1;        
        kc = check_kingchecker(temp_active_player, p1_cheker, p2_cheker, player1_kingcheker_position, player2_kingcheker_position, pos);
        if (kc=='Y')
        {
            for (i=0; i<*player1_kingchekers; i++)
            {
                if (player1_kingcheker_position[i] == pos)  player1_kingcheker_position[i]=0;
                *player1_kingchekers = *player1_kingchekers -1;
            }
        }

    }
}

void move_checker(int active_player, int player1_chekers, int player2_chekers,int player1_cheker_position[], int player2_cheker_position[], char si1, char si2, char ti2, char ti3, char helper_tmp, int *new_position, int player1_kingchekers, int player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[])
{
    int x1, x2, y1, y2, i, old_pos, new_pos;
    char kc='N';
    x1 = si2 -'0';
    x2 = ti3 -'0';
    y1 = ascii_to_number(si1);
    y2 = ascii_to_number(ti2);
  
    old_pos = (x1 * 10) + y1;
    kc = check_kingchecker(active_player, player1_kingchekers, player2_kingchekers, player1_kingcheker_position, player2_kingcheker_position, old_pos);

    if ((helper_tmp == 'M')|(helper_tmp=='m'))
    {
        new_pos = (x2 * 10) + y2;
    }
    else if ((helper_tmp == 'C')|(helper_tmp=='c'))
    {
        if (kc=='N')
        {
            if (active_player==1)  x2 = x2 +1;
            if (active_player==2) x2 = x2-1;
            if (y1 > y2) y2 = y2-1;
            if (y1 < y2) y2 = y2+1;
            new_pos = ((x2) * 10) + y2;
        }

        if (kc=='Y')
        {
            if (active_player==1) 
            {
                if(x1 > x2) x2 = x2-1;
                else x2=x2-1;
                
                if (y1 > y2) y2 = y2-1;
                if (y1 < y2) y2 = y2+1;
            }

            if (active_player==2) 
            {
                if(x2 > x1) x2 = x2+1;
                else x2 = x2-1;
                
                if (y1 > y2) y2 = y2-1;
                if (y1 < y2) y2 = y2+1;
            }
            new_pos = ((x2) * 10) + y2;
        }

    }

    *new_position = new_pos;
    if (active_player == 1)
    {
        for (i=0; i<12; i++)
        {
            if (player1_cheker_position[i] == old_pos) player1_cheker_position[i]=new_pos;
        }

        for (i=0; i<player1_kingchekers; i++)
        {
            if (player1_kingcheker_position[i] == old_pos)  player1_kingcheker_position[i]=new_pos;
        }
    }
    else if (active_player == 2)
    {
        for (i=0; i<12; i++)
        {
            if (player2_cheker_position[i] == old_pos) player2_cheker_position[i]=new_pos;
        }
       
        for (i=0; i<player2_kingchekers; i++)
        {
            if (player2_kingcheker_position[i] == old_pos)  player2_kingcheker_position[i]=new_pos;
        }
    }
}

int validate_target_input(char ti1, char ti2, char ti3, char si1, char si2, int board[10][10], int active_player, char helper_tmp, int player1_kingchekers, int player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[])
{
    int i, x1, x2, y1, y2, checker, checker_position, rc=0;
    x1 = si2 -'0';
    x2 = ti3 -'0';
    char kc='N';
    
    y1 = ascii_to_number(si1);
    y2 = ascii_to_number(ti2);    

    checker_position = x1*10+y1;
    checker = board[x2][y2];

    if (((y2==1)|(y2==8)|(x2==1)|(x2==8)) & ((helper_tmp=='C')|(helper_tmp=='c')))
    {
        printf("\n!Alert.. You are trying to capture a checker on the border, Not Allowed Move\n");
        return 0;
    }

    if (active_player==1)
    {
        for (i=0; i< player1_kingchekers; i++)
        {
            if (checker_position == player1_kingcheker_position[i]) kc='Y';

        }
    }

    if (active_player==2)
    {
        for (i=0; i< player2_kingchekers; i++)
        {
            if (checker_position == player2_kingcheker_position[i]) kc='Y';

        }
    }

    if (active_player == 1)
    {
        // Check vertical Movement
        if ((x2 - x1) == 1)
        {
            // printf("You are moving one step ahead, accepted\n");
            rc = 1;
        }
        else if ((x2 - x1) < 1)
        {
            if (kc=='Y')
            {
                //printf("King Checker can move in reverse direction\n");
                rc=1;
            }
            if (kc =='N')
            {
                printf("\n!Alert..Only King Checker can move in reverse direction, Not Allowed Move\n");
                return 0;
            }
        }

        else if ((x2 - x1) > 1)
        {
            printf("\n!Alert..You are moving more than one step ahead, Not Allowed Move\n");
            return 0;
        }


        // Check Horizontal Movement
        if (abs(y2 - y1) == 1)
        {
            //printf("You are moving one step across , accepted\n");
            rc=1;
        }
        else if (abs(y2 - y1) == 0)
        {
            printf("\n!Alert.. Strigt movement of checker is not allowed, Not Allowed Move\n");
            return 0;
        }
        else if (abs(y2 - y1) > 1)
        {
            printf("\n!Alert.. More than single step move not allowed, Not Accepted Move\n");
            return 0;
        }
        else if (abs(y2 - y1) < 1)
        {
            printf("\n!Alert.. More than single step move not allowed, Not Accepted Move\n");
            return 0;
        }

        if (checker == 46)
        {
            printf("\n!Alert, WRONG SELECTION, Checkers can move only in Dark Shade positions, Not Accepted Move\n");
            return 0;
        }

        if (checker == 79)
        {
            printf("\n!Alert.. WRONG SELECTION, Position occupied by your own checker, Not Accepted Move.\n");
            return 0;
        }
        else if (checker == 88)
        {
            if ((helper_tmp == 'M')|(helper_tmp=='m'))
            {
                printf("\n!Alert.. WRONG SELECTION, Your choosen position have opponent checker, Use Capture option.\n");
                return 0;
            }
            if ((helper_tmp == 'C')|(helper_tmp=='c'))
            {
                printf("Your choosen position have opponent checker, Initating Capture.\n");
            }
            
        }

        // Check for Free postion after movement
        // Check for the horizontal direction movement to check free position
        // Movement towards lower size a -> h and down 1 -> 8
        if ((helper_tmp =='C')|(helper_tmp=='c'))
        {
            if (y2 > y1)
            {
                if (kc=='N')
                {
                    if (board[x2+1][y2+1] != 32)
                    {
                        printf("\n!Alert.. No free position available after capture..Not Allowed Move\n");
                        return 0;
                    }
                }
                if (kc=='Y')
                {
                    if (board[x2-1][y2+1] != 32)
                    {
                        // Reverse movement is allowed only for King Cheker, Hence X2-1
                        rc=1;
                    }
                }
            
            }

            // Movement towards lower size h -> a and down 1 -> 8
            if (y2 < y1)
            {
                if (kc=='N')
                {
                    if (board[x2+1][y2-1] != 32)
                    {
                        printf("\n!Alert.. No free position available after capture..Not Allowed Move\n");
                        return 0;
                    }
                }
    
                if (kc=='Y')
                {
                    if (board[x2-1][y2-1] != 32)
                    {
                        // Reverse movement is allowed only for King Cheker, Hence X2-1
                        rc=1;
                    }
                }

            }
        }

        if (checker == 32)        
        {
            printf("Selected postion is blank.\n");
            rc=1;
        }
        if (rc == 0) return 0;
        else return 1;
    }
    else if (active_player == 2)
    {
        // Check vertical Movement
        if ((x2 - x1) == -1)
        {
            //printf("You are moving one step ahead, accepted\n");
            rc = 1;
        }
        else if ((x2 - x1) < -1)
        {
            printf("\n!Alert..You are moving more than one step ahead, Not Allowed Move\n");
            return 0;
        }

        else if ((x2 - x1) > -1)
        {
            if (kc=='N')
            {
                printf("\n!Alert..Only King Checker can move in reverse direction, Not Allowed Move\n");
                return 0;
            }
            if (kc=='Y')
            {
                //printf("King Checker can move in reverse direction\n");
                rc=1;
            }
            
        }
        // Check Horizontal Movement
        if (abs(y2 - y1) == 1)
        {
            //printf("You are moving one step across , accepted\n");
            rc=1;
        }
        else if (abs(y2 - y1) == 0)
        {
            printf("\n!Alert.. Strigt movement of checker is not allowed, Not Allowed Move\n");
            return 0;
        }
        else if (abs(y2 - y1) > 1)
        {
            printf("\n!Alert.. More than single step move not allowed, Not Accepted Move\n");
            return 0;
        }
        else if (abs(y2 - y1) < 1)
        {
            printf("\n!Alert.. More than single step move not allowed, Not Accepted Move\n");
            return 0;
        }

        if (checker == 46)
        {
            printf("\n!Alert, WRONG SELECTION, Checkers can move only in Dark Shade positions, Not Accepted Move\n");
            return 0;
        }

        if (checker == 88)
        {
            printf("\n!Alert.. WRONG SELECTION, Position occupied by your own checker, Not Accepted Move.\n");
            return 0;
        }
        else if (checker == 79)
        {
            if ((helper_tmp == 'M')|(helper_tmp=='m'))
            {
                printf("\n!Alert, WRONG SELECTION, Your choosen position have opponent checker, Use Capture option.\n");
                return 0;
            }
            if ((helper_tmp == 'C')|(helper_tmp=='c'))
            {
                printf("Your choosen position have opponent checker, Initating Capture.\n");
            }
        }

        // Check for Free postion after movement
        // Check for the horizontal direction movement to check free position
        // Movement towards lower size a -> h and down 1 -> 8
        if ((helper_tmp=='C')|(helper_tmp=='c'))
        {
            if (y2 > y1)
            {
                if(kc=='N')
                {
                    if (board[x2-1][y2+1] != 32)
                    {
                        printf("\n!Alert.. No free position available after capture..Not Allowed Move\n");
                        return 0;
                    }
                }
                if(kc=='Y')
                {
                    if (board[x2-1][y2+1] != 32)
                    {
                        // Reverse movement is allowed only for King Cheker, Hence X2-1
                        rc=1;
                    }
                }
            }
            // Movement towards lower size h -> a and down 1 -> 8
            if (y2 < y1)
            {
                if (kc=='N')
                {
                    if (board[x2-1][y2-1] != 32)
                    {
                        printf("\n!Alert.. No free position available after capture..Not Allowed Move\n");
                        return 0;
                    }
                }
                if (kc=='Y')
                {
                    if (board[x2-1][y2-1] != 32)
                    {
                        // Reverse movement is allowed only for King Cheker, Hence X2-1 
                        rc=1;
                    }
                }

            }
        }

        if (checker == 32)        
        {
            printf("Selected postion is blank.\n");
            rc=1;
        }
        if (rc == 0) return 0;
        else return 1;
    }
}

int validate_source_input(char si1, char si2, int board[10][10], int active_player )
{
    int x, y, checker;
    x = si2 -'0';
    y = ascii_to_number(si1);
  
    checker = board[x][y];
    if ((active_player == 1) & (checker == 79))
    {
        printf("Player 1,You choose right checker\n");
        return 1;
    }
    else if ((active_player == 2) & (checker == 88))
    {
        printf("Player 2, You choose right checker\n");
        return 1;
    }

    else
    {
        if (checker == 46) printf("!Alert, WRONG SELECTION,  You choosen empty position in the board.\n");
        else printf("WRONG SELECTION !, You choosen opponents checker\n");
        return 0;
    }
}

void print_player_details(char player1_name[], char player2_name[], int active_player, int player1_checkers, int player2_checkers, int player1_kingcheckers, int player2_kingcheckers)
{
    int hl=196;
    int i;
    printf("\nCheckers Available:\n");
    printf("Player 1: Checkers:%3d,  King Checkers:%2d\n", player1_checkers, player1_kingcheckers);
    printf("Player 2: Checkers:%3d,  King Checkers:%2d\n", player2_checkers, player2_kingcheckers);
    for (i=0; i<=50; i++) printf("%c",hl);
    printf("\n");
    if (active_player ==1)  printf("Active Player: %s (%d)\n",player1_name,active_player);
    if (active_player ==2)  printf("Active Player: %s (%d)\n",player2_name,active_player);
    for (i=0; i<=50; i++) printf("%c",hl);
}

void initialize_board(int board[10][10], int player1_cheker_position[], int player2_cheker_position[],char player1_name[], char player2_name[], int game_number)
{
    int bs=32;
    int vl=179;
    int luc=218;
    int ruc=191;
    int hl=196;
    int tt=194;
    int lt=195;
    int rt=180;
    int pl=197;
    int llc=192;
    int rlc=217;
    int it=193;


    int data[]= {
    126, 97, 98, 99, 100, 101, 102, 103, 104, 126, 
    49, 48, 46, 48, 46, 48, 46, 48, 46, 49, 
    50, 46, 48, 46, 48, 46, 48, 46, 48, 50, 
    51, 48, 46, 48, 46, 48, 46, 48, 46, 51, 
    52, 46, 32, 46, 32, 46, 32, 46, 32, 52, 
    53, 32, 46, 32, 46, 32, 46, 32, 46, 53, 
    54, 46, 48, 46, 48, 46, 48, 46, 48, 54, 
    55, 48, 46, 48, 46, 48, 46, 48, 46, 55, 
    56, 46, 48, 46, 48, 46, 48, 46, 48, 56, 
    126, 97, 98, 99, 100, 101, 102, 103, 104, 126};
    int i, j, count, pos, x, y, ch;
    system("cls");
    count=0;
    for (i=0; i<10; i++)
    {
        for (j=0; j<10; j++)
        {
           board[i][j]= data[count];
           count++;
        }
    }

    for (i=0; i<12; i++)
    {
        pos = player1_cheker_position[i];
        x = pos/10;
        y= pos % 10;
        board[x][y]= 79;
    }

    for (i=0; i<12; i++)
    {
        pos = player2_cheker_position[i];
        x = pos/10;
        y= pos % 10;
        board[x][y]= 88;
    }

    //!Caution - Do not delete this assignment. This to mask the deleted checkers
    board[3][2]=46;
    
/// Printing of the board initial design
    printf("\n");
    printf("%c",luc);
    for(j=0;j<=48;j++) printf("%c",hl);
    printf("%c\n",ruc);

    printf("%c",vl);
    for(j=0;j<=10;j++) printf("%c",bs);
    printf("G A M E  N U M B E R : %3d",game_number);
    for(j=0;j<=(47-33-3);j++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",lt);
    for(j=0;j<=48;j++) printf("%c",hl);
    printf("%c\n",rt);

    printf("%c",vl);
    for(j=0;j<=5;j++) printf("%c",bs);
    printf("Player 1: %s [ O ]",player1_name);
    for(j=0;j<=(47-15-6-strlen(player1_name));j++) printf("%c",bs);
    printf("%c\n",vl);

    
    printf("%c",lt);
    for (i=0;i<9;i++) printf("%c%c%c%c%c",hl,hl,hl,hl,tt);
    printf("%c%c%c%c%c\n",hl,hl,hl,hl,rt);

    for (i=0; i<10; i++)
    {
        printf("%c",vl);
        for (j=0; j<10; j++)
        {
            if ((board[i][j]==79) | (board[i][j]==88))  printf("%c%c%c%c%c", bs,board[i][j],bs,bs,vl);
            else  printf("%c%c%c%c%c", bs,board[i][j],bs,bs,vl);
        }
        printf("\n");
        
        if (i<9)
        {
            printf("%c",lt);
            for (j=0;j<9;j++) printf("%c%c%c%c%c",hl,hl,hl,hl,pl);
            printf("%c%c%c%c%c\n",hl,hl,hl,hl,rt);
        }
        
        if (i==9)
        {
            printf("%c",lt);
            for (j=0;j<9;j++) printf("%c%c%c%c%c",hl,hl,hl,hl,it);
            printf("%c%c%c%c%c\n",hl,hl,hl,hl,rt);
        }
    }
    printf("%c",vl);
    for(j=0;j<=5;j++) printf("%c",bs);
    printf("Player 2: %s [ X ]",player2_name);
    for(j=0;j<=(47-15-6-strlen(player2_name));j++) printf("%c",bs);
    printf("%c\n",vl);
    
    printf("%c",llc);
    for(j=0;j<=48;j++) printf("%c",hl);
    printf("%c\n",rlc);

}

void update_board(int board[10][10], int player1_cheker_position[], int player2_cheker_position[],char player1_name[], char player2_name[],int player1_kingchekers, int player2_kingchekers,int player1_kingcheker_position[], int player2_kingcheker_position[], int game_number)
{

    int bs=32;
    int vl=179;
    int luc=218;
    int ruc=191;
    int hl=196;
    int tt=194;
    int lt=195;
    int rt=180;
    int pl=197;
    int llc=192;
    int rlc=217;
    int it=193;

    int data[]= {
    126, 97, 98, 99, 100, 101, 102, 103, 104, 126, 
    49, 32, 46, 32, 46, 32, 46, 32, 46, 49, 
    50, 46, 32, 46, 32, 46, 32, 46, 32, 50, 
    51, 32, 46, 32, 46, 32, 46, 32, 46, 51, 
    52, 46, 32, 46, 32, 46, 32, 46, 32, 52, 
    53, 32, 46, 32, 46, 32, 46, 32, 46, 53, 
    54, 46, 32, 46, 32, 46, 32, 46, 32, 54, 
    55, 32, 46, 32, 46, 32, 46, 32, 46, 55, 
    56, 46, 32, 46, 32, 46, 32, 46, 32, 56, 
    126, 97, 98, 99, 100, 101, 102, 103, 104, 126};
    int i, j, count, pos, x, y, ch;
    system("cls");
    count=0;
    for (i=0; i<10; i++)
    {
        for (j=0; j<10; j++)
        {
           board[i][j]= data[count];
           count++;
        }
    }

    for (i=0; i<12; i++)
    {
        pos = player1_cheker_position[i];
        x = pos/10;
        y= pos % 10;
        board[x][y]= 79;
    }

    for (i=0; i<12; i++)
    {
        pos = player2_cheker_position[i];
        x = pos/10;
        y= pos % 10;
        board[x][y]= 88;
    }

    if (player1_kingchekers >0)
    {
        for (i=0; i< player1_kingchekers; i++)
        {
            pos = player1_kingcheker_position[i];
            x = pos/10;
            y= pos % 10;
            board[x][y]= 65;
        }
    }

    if (player2_kingchekers >0)
    {
        for (i=0; i< player2_kingchekers; i++)
        {
            pos = player2_kingcheker_position[i];
            x = pos/10;
            y= pos % 10;
            board[x][y]= 90;
        }
    }

    //!Caution - Do not delete this assignment. This to mask the deleted checkers
    board[3][2]=46;

    /// Printing of the board updated layut
    printf("\n");
    printf("%c",luc);
    for(j=0;j<=48;j++) printf("%c",hl);
    printf("%c\n",ruc);

    printf("%c",vl);
    for(j=0;j<=10;j++) printf("%c",bs);
    printf("G A M E  N U M B E R : %3d",game_number);
    for(j=0;j<=(47-33-3);j++) printf("%c",bs);
    printf("%c\n",vl);

    printf("%c",lt);
    for(j=0;j<=48;j++) printf("%c",hl);
    printf("%c\n",rt);

    printf("%c",vl);
    for(j=0;j<=5;j++) printf("%c",bs);
    printf("Player 1: %s [ O ]",player1_name);
    for(j=0;j<=(47-15-6-strlen(player1_name));j++) printf("%c",bs);
    printf("%c\n",vl);

    
    printf("%c",lt);
    for (i=0;i<9;i++) printf("%c%c%c%c%c",hl,hl,hl,hl,tt);
    printf("%c%c%c%c%c\n",hl,hl,hl,hl,rt);

    for (i=0; i <10; i++)
    {
        printf("%c",vl);
        for (j=0; j<10; j++)
        {
            if (board[i][j]==79)
            {
                printf("%c%c%c%c%c", bs,board[i][j],bs,bs,vl);
            }
            else if(board[i][j]==65)
            {
                board[i][j]=79;
                printf("%c%cK%c%c", bs,board[i][j],bs,vl);

            }
            else if(board[i][j]==88)
            {
                printf("%c%c%c%c%c", bs,board[i][j],bs,bs,vl);
            }
            else if(board[i][j]==90)
            {
                board[i][j]=88;
                printf("%c%cK%c%c", bs,board[i][j],bs,vl);
            }
            else  printf("%c%c%c%c%c", bs,board[i][j],bs,bs,vl);

        }
        printf("\n");
        if (i<9)
        {
            printf("%c",lt);
            for (j=0;j<9;j++) printf("%c%c%c%c%c",hl,hl,hl,hl,pl);
            printf("%c%c%c%c%c\n",hl,hl,hl,hl,rt);
        }
        
        if (i==9)
        {
            printf("%c",lt);
            for (j=0;j<9;j++) printf("%c%c%c%c%c",hl,hl,hl,hl,it);
            printf("%c%c%c%c%c\n",hl,hl,hl,hl,rt);
        }

    }
    printf("%c",vl);
    for(j=0;j<=5;j++) printf("%c",bs);
    printf("Player 2: %s [ X ]",player2_name);
    for(j=0;j<=(47-15-6-strlen(player2_name));j++) printf("%c",bs);
    printf("%c\n",vl);
    
    printf("%c",llc);
    for(j=0;j<=48;j++) printf("%c",hl);
    printf("%c\n",rlc);
}

int ascii_to_number(char input)
{
    int y;
    char ch=input;

    if ((ch == 'a')|(ch=='A')) y = 1;
    if ((ch == 'b')|(ch=='B')) y = 2;
    if ((ch == 'c')|(ch=='C')) y = 3;
    if ((ch == 'd')|(ch=='D')) y = 4;
    if ((ch == 'e')|(ch=='E')) y = 5;
    if ((ch == 'f')|(ch=='F')) y = 6;
    if ((ch == 'g')|(ch=='G')) y = 7;
    if ((ch == 'h')|(ch=='H')) y = 8;
    return y;
}