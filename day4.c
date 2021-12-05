#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NBOARDS 100
#define NBINGO 100 
#define ROW(n) (0x1f << 5*n)
#define COL(n) (0x1084210 >> n)

struct Board {
    int nums[25];
    int mask; 
};

bool is_bingo(struct Board *b){
    for (int j=0; j<5; ++j){ 
        if ( ((*b).mask & ROW(j)) == ROW(j) ) return true;
        if ( ((*b).mask & COL(j)) == COL(j) ) return true;
    }
    return false;
}

void print(struct Board *b){ 
    for (int i=0; i<25; ++i){
        printf("%d ", (*b).nums[i]);
        if (i%5 == 4) printf("\n");
    }
    printf("\n");

    for (int i=0; i<25; ++i){
        printf("%d ", ((*b).mask >> i )&1);
        if (i%5 == 4) printf("\n");
    }
    printf("\n");
}

int score(struct Board *b){
    int score = 0;
    for (int i=0; i<25; ++i){
        if ( !( ((*b).mask >> i)&1 ) ){ 
            score += (*b).nums[i];
        }
    }
    return score;
}

int solve1(struct Board bd[], int bingo[]){
    for (int i=0; i<NBINGO; ++i){
        for (int j=0; j<NBOARDS; ++j){
            for (int n=0; n<25; ++n){
                if (bd[j].nums[n] == bingo[i]) 
                    bd[j].mask |= (1<<n);
            }

            if ( is_bingo(&bd[j]) ){
                printf("BINGO!!!\n");
                print(&bd[j]);
                return bingo[i] * score(&bd[j]);
            }
        }
    }
    return -1;
}

int solve2(struct Board bd[], int bingo[]){
    bool won[NBOARDS];
    int n_won = 0;
    for (int i=0; i<NBOARDS; ++i){
        won[i] == false;
    }

    int last = -1;
    for (int i=0; i<NBINGO; ++i){
        if (n_won == NBOARDS) return last;

        for (int j=0; j<NBOARDS; ++j){
            if (won[j]) continue;
            for (int n=0; n<25; ++n){
                if (bd[j].nums[n] == bingo[i]) 
                    bd[j].mask |= (1<<n);
            }

            if ( is_bingo(&bd[j]) ){
                won[j] = true;
                n_won++;
                last = bingo[i] * score(&bd[j]);
            }
        }
    }
    return last;
}

int main(){
    FILE *fp;
    fp = fopen("input4.txt","r");
    if (fp == NULL) 
        return 1;

    int bingo[NBINGO];
    for (int i=0; i<NBINGO; ++i)
        fscanf(fp, "%d,", &bingo[i]);

    struct Board boards[NBOARDS];
    for (int i=0; i<NBOARDS; ++i){ 
        boards[i].mask = 0;
        for (int j=0; j<5; ++j){
            for (int k=0; k<5; ++k)
                fscanf(fp, "%d", &boards[i].nums[5*j+k]);
        }
    }
    fclose(fp);

    int res = solve2(boards, bingo);
    printf("%d\n",res);
    return 0;
}
