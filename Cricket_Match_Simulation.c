// Program to simulate a match of cricket between two teams
// Match should start after a toss 
// there are two differnet teams
// different teams have same number of players
// firstly a process is performed to toss
// then the toss winnig team will choose to bating or balling
// Now as team choose the match start and the target should build through the randomized number
// Now the when first team will play the target is build and then the second team will play
// Now three overs of other team and they also make some target
// Then the both targets of both teams will be compared and the winnig team will congrats
// If the score of both team is same then the program should play a super over
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
// BALLSINOVER can be changed to change the length of over
#define BALLSINOVER 6
// TOTALOVERS can be changed to change the total over of the match
#define TOTALOVERS 5
// TOTALBALLS will change with change in over or change in balls in over and calculated as TOTALOVERS * BALLSINOVER
#define TOTALBALLS 30
void getScorePerBall(int[] , int over,int *players);
void calculateScorePerOver(int[], int[],int overs);
int calculateTarget(int[], int overs);
void displayArray(int[], int size);
int toss();
int toBatorBall(int a);
void displayGradually(char a[], float sec);
int main()
{
	// srand function is used to randamize numbers with respect to the time
	srand(time(0));
	// Declaration of variables
	int targetStar11Team, targetGorillaTeam, overs, tossWinningTeam;
	int decisionForBattingOrBalling, flagForNextTeamToPlay, flagForSuperOver, noOfPlayersInTeam;
	int playersGorillaTeam, playersStar11Team;
	int scorePerBallTeam1[TOTALBALLS], scorePerBallTeam2[TOTALBALLS], scorePerOverTeam1[TOTALBALLS], scorePerOverTeam2[TOTALOVERS];
	overs = targetStar11Team = targetGorillaTeam = 0;
	flagForNextTeamToPlay = 3;
	flagForSuperOver = 0;
	/// <Variables Explanation>
	///		targetStar11Team and targetGorillaTeam is used to store the total score of both teams
	///		overs variable is used to take an input of total over of the match
	///		tossWinningTeam will store 1 if the toss is won by Star11 and 2 if the toss winning team is Gorilla 
	///		decisionForBattingOrBalling variable will store 1 if the team decided to batting first and 0 if toss winning team decide for balling first
	///		flagForNextTeamToPlay will store 1 if the next team is Star11 and 2 if the next team to play from the batting side is Gorilla
	///		flagForSuperOver is used to check if the match goes to super over if the flag is 1 then it should start the super over other wise the super over will not be played
	///		noOfPlayersInTeam is used to get an input from the user for the total number of player in team
	///		playersGorillaTeam variable is used to  store and manipulate the number of players in Gorilla Team
	///		playersSta
	/// \r11Team variable is used to store and manipulate the number of player in Star11 team
	///		scorePerBallTeam1[TOTALBALLS] array will be used to store the score of every ball played by team1 means Star11 team
	///		scorePerBallTeam2[TOTALBALLS] array will be used to store the score of every ball played by team2 means Gorilla team
	///		scorePerOverTeam1[TOTALBALLS] array will store the total score of each over by team star11
	///		scorePerOverTeam2[TOTALOVERS] array will store the total score of each over by Gorilla Team
	/// </Variables Explanation>
	
	// Graphics Work

	/*
	unsigned char b, f;

	for (b = 0; b < 16; b++)
	{
		for (f = 0; f < 16; f++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), b << 4 | f);
			printf("%.2X", b << 4 | f);
		}
		printf("\n");
	}
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	printf("\n");
	/*
	FOREGROUND_GREEN |
	FOREGROUND_INTENSITY |
	BACKGROUND_RED
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	// This statement will colorize the text over console to green
	printf("\n\n\t\t\t");
	displayGradually("|-----------  WellCome to The Cricket Match  -----------|",2);
	printf("\n\n\n\t\t\t");
	// underlying statement will print that there will be two teams in this match
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	// This statement will print names of both teams in red color
	displayGradually("There will be two teams in this match as below : ", 3);
	printf("\n\n\t\t\t");
	displayGradually("1 . Star11 Team", 1);
	printf("\t\t");
	displayGradually("2 . Gorilla Team", 1);
	printf("\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x07);
	// underlying statement will print loading in white color
	printf("Loading");
	displayGradually(" . . . . . . . . . .", 5);
	printf("\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	// This loop will get a value for total number of overs in match and validate it until the condition is true
	do
	{	
		printf("Please decide and Enter Number of overs of Match (0<overs<%d) : ",TOTALOVERS);
		scanf("%d", &overs);
		getchar();
		if (overs <= 0 || overs >= TOTALOVERS)
		{
			printf("Invalid Input ! ");
		}
	} while (overs <= 0 || overs >= TOTALOVERS);
	printf("\n");
	//	This do-while loop will take total number of players each team have and validates until the entered players are outside the 2 and 10 
	do
	{
		printf("Enter the Number of Players (2 <= Players <= 5) : ");
		scanf("%d", &noOfPlayersInTeam);
		getchar();
		if (noOfPlayersInTeam < 2 || noOfPlayersInTeam >= 5)
			printf("Invalid Input ! ");
	} while (noOfPlayersInTeam < 2 || noOfPlayersInTeam >= 5);
	playersGorillaTeam = playersStar11Team = noOfPlayersInTeam;
	printf("\n");
	// This loop will simply iterate until the one team win and iterate if the match goes to super over
	do
	{
		tossWinningTeam = toss();
		decisionForBattingOrBalling = toBatorBall(tossWinningTeam);
		// This for loop will print the match is started between the teams
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("\n\n\t\t\t");
		displayGradually("<|>-----------------  Match Started  -----------------<|>", 3);
		printf("\n\n\n");
		// Taking input from user and assigning radom scores
		// These condition will check which team will play first on batting side and which team player after the other team
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Red color
		if (tossWinningTeam == 2)
		{
			if (decisionForBattingOrBalling == 1)
			{
				displayGradually("Gorilla Team is Playing from Batting Side !",2);
				printf("\n");
				flagForNextTeamToPlay = 2;
				getScorePerBall(scorePerBallTeam2, overs , &playersStar11Team);
				calculateScorePerOver(scorePerOverTeam2, scorePerBallTeam2, overs);
				targetGorillaTeam = calculateTarget(scorePerOverTeam2, overs);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n\t|--------The total score of Gorilla Team is : %d--------|\n", targetGorillaTeam);
			}
			else
			{
				displayGradually("Star11 Team is Playing from Batting Side !",2);
				printf("\n");
				flagForNextTeamToPlay = 1;
				getScorePerBall(scorePerBallTeam1, overs , &playersGorillaTeam);
				calculateScorePerOver(scorePerOverTeam1, scorePerBallTeam1, overs);
				targetStar11Team = calculateTarget(scorePerOverTeam1, overs);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n\t|--------The total score of Star11 Team is : %d--------|\n", targetStar11Team);

			}
		}
		else
		{
			if (decisionForBattingOrBalling == 1)
			{
				displayGradually("Star11 Team is Playing from Batting Side !",2);
				printf("\n");
				flagForNextTeamToPlay = 1;
				getScorePerBall(scorePerBallTeam1, overs, &playersStar11Team);
				calculateScorePerOver(scorePerOverTeam1, scorePerBallTeam1, overs);
				targetStar11Team = calculateTarget(scorePerOverTeam1, overs);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n\t|--------The total score of Star11 Team is : %d--------|\n", targetStar11Team);

			}
			else
			{
				displayGradually("Gorilla Team is Playing from Batting Side !", 2);
				printf("\n");
				flagForNextTeamToPlay = 2;
				getScorePerBall(scorePerBallTeam2, overs, &playersGorillaTeam);
				calculateScorePerOver(scorePerOverTeam2, scorePerBallTeam2, overs);
				targetGorillaTeam = calculateTarget(scorePerOverTeam2, overs);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("\n\n\t|--------The total score of Gorilla Team is : %d--------|\n", targetGorillaTeam);

			}
		}
		// this if-else structure will decide which team has to play from Batting side according to flagForNextTeamToPlay variables
		if (flagForNextTeamToPlay == 1)
		{
			printf("\n\n");
			displayGradually("Now the Gorrila Team have to play from Batting side ! Gorilla Team ! ",3.5);
			getScorePerBall(scorePerBallTeam2, overs, &playersGorillaTeam);
			calculateScorePerOver(scorePerOverTeam2, scorePerBallTeam2, overs);
			targetGorillaTeam = calculateTarget(scorePerOverTeam2, overs);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n\t|--------The total score of Gorilla Team is : %d--------|\n", targetGorillaTeam);

		}
		else
		{
			printf("\n\n");
			displayGradually("Now the Star11 Team have to Play from Batting side ! Star11 Team ! ",3.5);
			getScorePerBall(scorePerBallTeam1, overs, &playersStar11Team);
			calculateScorePerOver(scorePerOverTeam1, scorePerBallTeam1, overs);
			targetStar11Team = calculateTarget(scorePerOverTeam1, overs);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("\n\n\t|--------The total score of Star11 Team is : %d--------|\n", targetStar11Team);

		}
		// under lying statements will calculate and display score of each team in each overs and on each ball using function
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Red color
		printf("\n");
		displayGradually("Score per Ball in each Over by Star11 Team.", 2);
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // White color
		displayArray(scorePerBallTeam1, BALLSINOVER * overs);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Red color
		printf("\n");
		displayGradually("Score per Ball in each over by Gorilla Team.", 2);
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // White color
		displayArray(scorePerBallTeam2, BALLSINOVER * overs);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Red color 
		printf("\n");
		displayGradually("Score per Over by Star11 Team.", 2);
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // White color
		displayArray(scorePerOverTeam1, overs);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Red color
		printf("\n");
		displayGradually("Score per Over by Gorilla Team.", 2);
		printf("\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // White color
		displayArray(scorePerOverTeam2, overs);
		// These statements will calculate total scores of teams and display them
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // Green color
		printf("\n\nTotal Score of Star11 : %d runs\nGorilla Team scored : %d runs\n", targetStar11Team, targetGorillaTeam);
		printf("\n\n");
		// Congratulation the team with more scores and start super over if the score of both teams are same
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); // Red color
		if (targetStar11Team > targetGorillaTeam)
		{
			printf("Congratulations to the Team Star11.\n");
			printf("Star11 team win by %d runs and %d wikets.\n", targetStar11Team - targetGorillaTeam, playersStar11Team);
			flagForSuperOver = 0;
		}
		else if (targetGorillaTeam > targetStar11Team)
		{
			printf("Congratulations to the Gorilla Team.\n");
			printf("Gorilla Team win by %d runs and %d wikets.\n", targetGorillaTeam - targetStar11Team, playersGorillaTeam);
			flagForSuperOver = 0;
		}
		else
		{
			printf("Both teams have same Scores.\tThe match is moved to the Super Over !\n\n\n\n\n");
			Sleep(1000);
			flagForSuperOver = 1;
			overs = 1;
			printf("\t\t\t\tSUPER OVER ! \n\n\n");
		}
	} while (flagForSuperOver == 1);

	return 0;

}
/// <summary>
/// This function will randomize score of each ball according to the given number of over
/// if the score are in between 1 and 6 it will display different statements like six for 6 runs and panelity runs for 5 runs
/// if the score is 7 it will declare out which may be run out or catch out or a clean bold according to the situation
/// panelity runs 5 assignment to any team chances are only 4% to 5%
/// </summary>
/// <param name="scorePerBall">This array will be used to store the randomized runs on each ball</param>
/// <param name="overs">This will be used to store number of overs which will be used to evaluate the total number of balls</param>
/// <param name="players">This will be used to check the players of team if the total players are declared out then function will stop taking numbers</param>
void getScorePerBall(int scorePerBall[] , int overs,int *players)
{

	getchar();
	int ballCounter = 1;
	for (int i = 0; i < (overs * BALLSINOVER); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); // Blue color
		printf("\nPress Enter key to play Ball %d : ", ballCounter);
		getchar();
		scorePerBall[i] = rand() % 8 ;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		if (scorePerBall[i] == 0)
		{
			printf("\nA great Ball by the Baller !\n\n\t\t\t\\");
			displayGradually("--------Dot Ball.--------/", 1);
			printf("\n\n");
		}
		else if (scorePerBall[i] == 1)
		{
			printf("\n\t\t\t\\");
			displayGradually("-------Single run.-------/", 1);
			printf("\n\n");
		}
		else if (scorePerBall[i] <= 3)
		{
			printf("\nFielder is passing the ball.");
			displayGradually("......", 1);
			printf("\n\n");
			printf("\t\t\t\\-------Its %d runs.-------/\n\n",scorePerBall[i]);
		}
		else if (scorePerBall[i] == 4)
		{
			printf("\nA Boundary by the Batsman !\n\n");
			printf("\t\t\t\\");
			displayGradually("-------Four runs !-------/", 1);
			printf("\n\n");
		}
		else if (scorePerBall[i] == 6)
		{
			printf("\nO Wonderful shot by the Batsman !\n\n");
			printf("\t\t\t\\");
			displayGradually("-------Six Scores !-------/", 1);
			printf("\n\n");
		}
		else if (scorePerBall[i] == 7)
		{
			*players--;
			printf("\nOh ! Bad Luck of Batsman ! ");
			int out = rand() % 4;
			if (out == 0)
			{
				printf(" Bowled !\n\n\t\t\t\\");
				displayGradually("------Its 0 Runs !------/", 1);
				printf("\n\n");
				scorePerBall[i] = 0;
			}
			else if (out == 1)
			{
				printf("\n\nThe fielder is passing the Ball.");
				displayGradually(".......", 1);
				printf("\n\nIts a run out !\n\n");
				if (rand() % 2 == 0)
				{
					scorePerBall[i] = 1;
					printf("\t\t\t\\");
					displayGradually("--------Single run on this Ball.-------/", 1);
					printf("\n\n");
				}
				else
				{
					scorePerBall[i] = 2;
					printf("\t\t\t\\");
					displayGradually("-------Double runs on this Ball.-------/", 1);
					printf("\n\n");
				}
			}
			else
			{
				scorePerBall[i] = 0;
				if(rand()%2 == 1)
				{
					printf("\n\nThe wonderful catch by the fielder !");
				}
				else
				{
					printf("\n\nThe wonderful catch by the keeper !");
				}
				printf("\n\n\t\t\t\\");
				displayGradually("--------No run on this ball.--------/", 1);
				printf("\n\n");
			}
		}
		else
		{
			if (rand() % 3 == 0)
			{
				printf("\nOh ! Its bad Luck of the Baller !\n\n\t\t\t\\");
				displayGradually("-------Its 5 runs with wide and four.-------/", 1);
				printf("\n\n");
			}
			else
			{
				printf("\nFielder is passing the ball.");
				displayGradually("........", 1);
				printf("\n\n\t\t\t\\");
				displayGradually("------Its 2 runs.------/", 1);
				printf("\n\n");
				scorePerBall[i] = 2;
			}
		}
		if (ballCounter == 6)
		{
			ballCounter = 0;
		}
		ballCounter++;
		if (*players == 0)
		{	
			printf("\n\n");
			displayGradually("All Team Out ! ", 3);
			printf("\n\n");
			break;
		}
	}
}
/// <summary>
/// This function will be used to calculate the score of each over of each team according to the given score of that team 
/// </summary>
/// <param name="totalPerOver">This will be used to store the score calculated for each over</param>
/// <param name="scorePerBall">This will be used to check the scores on each ball</param>
/// <param name="overs">overs will be used to manipulate the total number of overs and total number of balls</param>
void calculateScorePerOver(int totalPerOver[],int scorePerBall[], int overs)
{
	int sumScore = 0 ;
	for (int i = 0; i < overs ; i++)
	{
		sumScore = 0;
		for (int j = i * BALLSINOVER; j < (BALLSINOVER * (i + 1)); j++)
		{
			sumScore = sumScore + scorePerBall[j];
		}
		totalPerOver[i] = sumScore;
	}
}
/// <summary>
/// This function will be used to calculate the total score of each team in the match
/// </summary>
/// <param name="totalPerOver">this will provide the data of the scores of each over</param>
/// <param name="overs">overs will be used to manipulate the total over given</param>
/// <returns>This function will return the calculated total score of the team</returns>
int calculateTarget(int totalPerOver[], int overs)
{
	int target = 0;
	for (int i = 0; i < overs; i++)
	{
		target = target + totalPerOver[i];
	}
	return target;
}
/// <summary>
/// This function will only display each element of array passed to it
/// </summary>
/// <param name="array">Array passed by the user</param>
/// <param name="size">size of the array which declare how many elements to display</param>
void displayArray(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("\t%d",array[i]);
	}
}
/// <summary>
/// This function will get the winning team and get an input from winnig team to Batting first or Balling first
/// </summary>
/// <param name="a">this parameter will pass the 1 if the winnig team is Star11 and pass 2 If the winning team is Gorilla Team</param>
/// <returns>Return 1 if the team selected for batting first and 0 if the team selected for balling first</returns>
int toBatorBall(int a)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	int choice = 3;
	if (a == 2)
		printf("Gorilla Team ! ");
	else
		printf("Star11 Team ! ");
	do
	{
		printf("Enter 1 for Bating first or 0 for Balling First : ");
		scanf("%d", &choice);
		if (choice != 0 && choice != 1)
			printf("Invalid Input ! ");
	} while (choice != 0 && choice != 1);
	printf("\n");
	if (a == 2)
	{
		if (choice == 1)
			printf("\t\t\tGorilla Team Selected for Batting First.\n");
		else
			printf("\t\t\tGorilla Team Selected for Balling First.\n");
	}
	else
	{
		if (choice == 1)
			printf("\t\t\tStar11 Team Selected for Batting First.\n");
		else
			printf("\t\t\tStar11 Team Selected for Balling First.\n");
	}
	printf("\n\n");
	return choice;
}
/// <summary>
/// This function will take an input from the team leader in form of head or tail and perform a toss
/// </summary>
/// <returns>Return 1 if the toss Winning team is star11 and return 2 if the toss winning team is Gorilla Team</returns>
int toss()
{
	int choice = 2 , temp = 2;
	do
	{
		printf("Please enter 1 for head and 0 for tail : ");
		scanf("%d", &choice);
		if (choice != 1 && choice != 0)
			printf("Invalid Input ! ");
	} while (choice != 1 && choice != 0);
	temp = rand() % 2;
	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("\t\t\t");
	if (temp == choice)
	{
		displayGradually("Gorilla team win the toss.",2);
		printf("\n\n");
		return 2;
	}
	else
	{
		displayGradually("Star11 team win the toss.",2);
		printf("\n\n");
		return 1;
	}
}
/// <summary>
/// This function will be used to display any given character array in the given seconds
/// </summary>
/// <param name="a">This is character array passed to Display</param>
/// <param name="sec">Given time in seconds in which user want to display the given character array</param>
void displayGradually(char a[], float sec)
{
	int count = 0;
	while (a[count] != 0)
	{
		count++;
	}
	for (int i = 0; i < count; i++)
	{
		Sleep((sec * 1000.0) / count);
		printf("%c", a[i]);
	}
}