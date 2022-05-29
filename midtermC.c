#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#define ll long long
#define max(a,b) a>b ? a : b
#define min(a,b) a<b ? a : b
#define MAX_GROUP 8
#define MAX_NAME 20
#define MAX_TEAM 4

typedef struct group_s{
    char GroupID;
    char TeamName[MAX_TEAM][MAX_NAME];
    unsigned int Points[4];
    int Goals[4];
} grouped;

typedef struct location_s{
    int i;
    int j;
} location;

struct group_s AllPointers[MAX_GROUP];
int N = 0;

int isNValid(int n){
    if ((n >= 1) && (N + n <= 8)) return 1;
    printf("INVALID INPUT\n");
    return 0;
}
int isGroupIDValid(int i){
    if (AllPointers[i].GroupID >= 'A' && AllPointers[i].GroupID <= 'Z')
        for (int count = 0; count < N; count++)
            if ((count != i) && (AllPointers[i].GroupID == AllPointers[count].GroupID))
                break;
            else
                if (count + 1 == N) return 1;
    printf("INVALID INPUT\n");
    return 0;
}
location findname(char *teamname){
    // Output -1 to i and j if not found
    location loc;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < MAX_TEAM; j++) {
            if (strcmp(teamname, AllPointers[i].TeamName[j]) == 0){
                loc.i = i;
                loc.j = j;
                return loc;
            }
        }
    }
    loc.i = -1;
    loc.j = -1;
    return loc;
}
int isTeamValid(int i, int j, char *teamname, int point){
    location loc;
    loc = findname(teamname);
    if (loc.i == -1){
        if (point >= 0){
            strcpy(AllPointers[i].TeamName[j], teamname);
            AllPointers[i].Points[j] = point;
            return 1;
        }
    }
    printf("INVALID INPUT\n");
    return 0;
}
void func1() {
    // Add team
    if (N == 8){
        printf("ALL 8 GROUPS");
        return;
    }
    int n = 0;
    char teamname[MAX_NAME];
    int point = 0;
    do{
        // Input n (to add to the total)
        printf("Input number of groups: ");
        scanf(" %d", &n);
        // Check validity 1
    }while(!isNValid(n));
    N += n;
    for (int i = 0; i < N; i++){
        do{
            // Input GroupID
            printf("GroupID: ");
            scanf(" %c", &AllPointers[i].GroupID);
            // Check validity 2
        } while (!isGroupIDValid(i));
        for (int j = 0; j < MAX_TEAM; j++){
            do{
                // Input Team stuffs
                printf("Team #%d name, points, goal diff: ", j+1);
                scanf(" %s", teamname);
                scanf(" %d", &point);
                scanf(" %d", &AllPointers[i].Goals[j]);
                // Check validity 3 4
            }while (!isTeamValid(i, j, teamname, point));
        }
    }
    return;
}

void func2(){
    // Print team
    for (int i = 0; i < N; i++){
        printf("Group %c\n", AllPointers[i].GroupID);
        printf("%-20s%-10s%-20s\n", "Team", "Point", "Goal Difference");
        for (int j = 0; j < MAX_TEAM; j++){
            printf("%-20s%-10u%-20d\n", 
                AllPointers[i].TeamName[j], 
                AllPointers[i].Points[j], 
                AllPointers[i].Goals[j]);
        }
    } 
}

void printTeamInfo(int i, int j){
    printf("%s, Group %c, %u Point, %d Goal difference\n",
        AllPointers[i].TeamName[j],
        AllPointers[i].GroupID, 
        AllPointers[i].Points[j], 
        AllPointers[i].Goals[j]);
}
void func3(){
    // Find team
    location loc;
    char teamname[MAX_NAME];
    printf("Input: ");
    scanf(" %s", teamname);
    loc = findname(teamname);
    printf("Result: ");
    if (loc.i != -1)
        printTeamInfo(loc.i, loc.j);
    else
        printf("No result\n");
}

void func4(){
    // Input match result
    location loc_1;
    location loc_2;
    char team_1[MAX_NAME];
    char team_2[MAX_NAME];
    int goal_1 = 0, goal_2 = 0;
    while(1){
        printf("Input match result: ");
        scanf(" %s %s %d %d", team_1, team_2, &goal_1, &goal_2);
        loc_1 = findname(team_1);
        loc_2 = findname(team_2);

        // Check validity
        if ((loc_1.i != -1) && (loc_2.i != -1) 
            && (goal_1 >= 0) && (goal_2 >= 0)){
            if (loc_1.i == loc_2.i){
                // Calculate points
                AllPointers[loc_1.i].Goals[loc_1.j] += (goal_1 - goal_2);
                AllPointers[loc_2.i].Goals[loc_2.j] += (goal_2 - goal_1);
                if (goal_1 > goal_2) 
                    AllPointers[loc_1.i].Points[loc_1.j] += 3;
                else if (goal_1 < goal_2)   
                    AllPointers[loc_2.i].Points[loc_2.j] += 3;
                else{
                    AllPointers[loc_1.i].Points[loc_1.j] += 1;
                    AllPointers[loc_2.i].Points[loc_2.j] += 1;
                }
                printf("\n");
                printTeamInfo(loc_1.i, loc_1.j);
                printTeamInfo(loc_2.i, loc_2.j);
                break;
            } else{
                printf("Different group\n");
                break;
            }
        } else{
            printf("INVALID INPUT\n");
            break;
        }
    }
}


int compareMyTeam(const int i, const int a, const int b){
    if (AllPointers[i].Points[a] > AllPointers[i].Points[b]) 
        return 1;
    if (AllPointers[i].Points[a] < AllPointers[i].Points[b]) 
        return -1;

    if (AllPointers[i].Goals[a] > AllPointers[i].Goals[b]) 
        return 1;
    if (AllPointers[i].Goals[a] < AllPointers[i].Goals[b]) 
        return -1;

    return -strcmp(AllPointers[i].TeamName[a], AllPointers[i].TeamName[b]);
}
void swapMyTeam(const int i, const int a, const int b){
    char tmp_TeamName[MAX_NAME];
    unsigned int tmp_Points;
    int tmp_Goals;

    tmp_Points = AllPointers[i].Points[a];
    AllPointers[i].Points[a] = AllPointers[i].Points[b];
    AllPointers[i].Points[b] = tmp_Points;

    tmp_Goals = AllPointers[i].Goals[a];
    AllPointers[i].Goals[a] = AllPointers[i].Goals[b];
    AllPointers[i].Goals[b] = tmp_Goals;

    strcpy(tmp_TeamName, AllPointers[i].TeamName[a]);
    strcpy(AllPointers[i].TeamName[a], AllPointers[i].TeamName[b]);
    strcpy(AllPointers[i].TeamName[b], tmp_TeamName);
}
void func5(){
    // Sort points
    for (int i = 0; i < N; i++)
        // For all groups
        for (int k = 0; k < MAX_TEAM-1; k++)
            // Teams
            for (int j = 0; j < MAX_TEAM-k-1; j++)
                if (compareMyTeam(i, j, j+1) < 0)
                    swapMyTeam(i, j, j+1);
    func2();
}

int main(){
    int option;
    while(1){
        printf("\n");
        printf("1. Add groups\n");
        printf("2. Print groups\n");
        printf("3. Find team\n");
        printf("4. Update team\n");
        printf("5. Sort team\n");
        printf("6. Exit\n");
        printf("Enter 1-6: ");
        scanf(" %d", &option);

        switch(option){
            case 1:
                func1();
                break;
            case 2:
                func2();
                break;
            case 3:
                func3();
                break;
            case 4:
                func4();
                break;
            case 5:
                func5();
                break;
            case 6:
                return 0;
                break;
            default:
                printf("INVALID INPUT\n");
                break;
        }
    }
}