#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int valid_example[5][9][9] = {
    {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 1, 2, 3},
        {7, 8, 9, 1, 2, 3, 4, 5, 6},
        {2, 1, 4, 3, 6, 5, 8, 9, 7},
        {3, 6, 5, 8, 9, 7, 2, 1, 4},
        {8, 9, 7, 2, 1, 4, 3, 6, 5},
        {5, 3, 1, 6, 4, 2, 9, 7, 8},
        {6, 4, 2, 9, 7, 8, 5, 3, 1},
        {9, 7, 8, 5, 3, 1, 6, 4, 2}
    },
    {
        {8, 5, 3, 4, 9, 7, 2, 6, 1},
        {9, 2, 7, 8, 6, 1, 3, 4, 5},
        {6, 1, 4, 3, 5, 2, 7, 9, 8},
        {7, 4, 6, 1, 2, 8, 9, 5, 3},
        {1, 9, 8, 6, 3, 5, 4, 7, 2},
        {5, 3, 2, 9, 7, 4, 8, 1, 6},
        {3, 7, 1, 2, 4, 6, 5, 8, 9},
        {4, 6, 9, 5, 8, 3, 1, 2, 7},
        {2, 8, 5, 7, 1, 9, 6, 3, 4}
    },
    {
        {1, 6, 2, 3, 4, 7, 8, 9, 5},
        {7, 4, 8, 1, 9, 5, 3, 2, 6},
        {9, 3, 5, 8, 6, 2, 7, 1, 4},
        {4, 7, 1, 5, 3, 9, 2, 6, 8},
        {6, 5, 3, 4, 2, 8, 9, 7, 1},
        {8, 2, 9, 7, 1, 6, 4, 5, 3},
        {3, 8, 6, 9, 7, 1, 5, 4, 2},
        {5, 1, 7, 2, 8, 4, 6, 3, 9},
        {2, 9, 4, 6, 5, 3, 1, 8, 7}
    },
    {
        {6, 1, 8, 5, 9, 4, 3, 2, 7},
        {9, 3, 5, 8, 7, 2, 4, 1, 6},
        {4, 7, 2, 3, 1, 6, 9, 5, 8},
        {2, 5, 9, 6, 4, 7, 1, 8, 3},
        {3, 8, 6, 1, 5, 9, 2, 7, 4},
        {1, 4, 7, 2, 8, 3, 6, 9, 5},
        {8, 6, 4, 9, 2, 5, 7, 3, 1},
        {7, 2, 1, 4, 3, 8, 5, 6, 9},
        {5, 9, 3, 7, 6, 1, 8, 4, 2}
    },
    {
        {2, 8, 9, 1, 3, 5, 6, 7, 4},
        {1, 4, 3, 9, 6, 7, 5, 2, 8},
        {6, 7, 5, 2, 8, 4, 1, 3, 9},
        {9, 5, 4, 7, 1, 2, 8, 6, 3},
        {3, 6, 7, 8, 5, 9, 2, 4, 1},
        {8, 2, 1, 3, 4, 6, 9, 5, 7},
        {5, 3, 2, 4, 9, 8, 7, 1, 6},
        {4, 9, 6, 5, 7, 1, 3, 8, 2},
        {7, 1, 8, 6, 2, 3, 4, 9, 5}
    }
};

int example[100][9][9];
int grid[9][9];
int example_number = 10;

bool found = false;
typedef struct {
    int row;
    int col;
} SubsquareArgs;

void generate_random(int num){
    for(int i=0; i<9; i++)
        for(int j=0; j<9; j++){
            example[0][i][j] = 1 + rand()%9;
            example[1][i][j] = 1 + rand()%9;
            example[4][i][j] = 1 + rand()%9;
            example[6][i][j] = 1 + rand()%9;
            example[9][i][j] = 1 + rand()%9;

            example[2][i][j] = valid_example[0][i][j];
            example[3][i][j] = valid_example[1][i][j];
            example[5][i][j] = valid_example[2][i][j];
            example[7][i][j] = valid_example[3][i][j];
            example[8][i][j] = valid_example[4][i][j];
        }
}

void *check_row(void *arg) {
    int *rows = (int *)arg;
    for (int n = 0; n < 3; n++) {
        int row = rows[n];
        bool present_number[9] = {false};
        for (int j = 0; j < 9; j++) {
            int the_number = grid[row][j];
            if (present_number[the_number - 1]) {
                free(arg);
                pthread_exit((void *)false);
            }
            present_number[the_number - 1] = true;
        }
    }
    free(arg);
    pthread_exit((void *)true);
}

void *check_col(void *arg) {
    int *cols = (int *)arg;
    for (int n = 0; n < 3; n++) {
        int col = cols[n];
        bool present_number[9] = {false};
        for (int i = 0; i < 9; i++) {
            int the_number = grid[i][col];
            if (present_number[the_number - 1]) {
                free(arg);
                pthread_exit((void *)false);
            }
            present_number[the_number - 1] = true;
        }
    }
    free(arg);
    pthread_exit((void *)true);
}

void *check_subsquare(void *arg) {
    SubsquareArgs *args = (SubsquareArgs *)arg;
    for (int n = 0; n < 3; n++) {
        int start_row = args[n].row;
        int start_col = args[n].col;
        bool present_number[9] = {false};
        for (int i = start_row; i < start_row + 3; i++) {
            for (int j = start_col; j < start_col + 3; j++) {
                int the_number = grid[i][j];
                if (present_number[the_number - 1]) {
                    free(arg);
                    pthread_exit((void *)false);
                }
                present_number[the_number - 1] = true;
            }
        }
    }
    free(arg);
    pthread_exit((void *)true);
}

bool check_sudoku() {
    pthread_t threads[9];
    int thread_idx = 0;

    // Check rows
    for (int i = 0; i < 9; i += 3) {
        int *rows = malloc(3 * sizeof(int));
        rows[0] = i; rows[1] = i + 1; rows[2] = i + 2;
        pthread_create(&threads[thread_idx++], NULL, check_row, rows);
    }

    // Check columns
    for (int j = 0; j < 9; j += 3) {
        int *cols = malloc(3 * sizeof(int));
        cols[0] = j; cols[1] = j + 1; cols[2] = j + 2;
        pthread_create(&threads[thread_idx++], NULL, check_col, cols);
    }

    // Check subsquares
    for (int i = 0; i < 9; i += 3) {
        SubsquareArgs *subsquares = malloc(3 * sizeof(SubsquareArgs));
        for (int n = 0; n < 3; n++) {
            subsquares[n].row = i;
            subsquares[n].col = n * 3;
        }
        pthread_create(&threads[thread_idx++], NULL, check_subsquare, subsquares);
    }

    // Join threads and verify results
    for (int i = 0; i < 9; i++) {
        void *result;
        pthread_join(threads[i], &result);
        if (result == (void *)false) {
            return false;
        }
    }
    return true;
}

bool valid_array(int *arr){
    bool present_number[9] = {false};
    for(int i=0; i<9; i++){
        int the_number = arr[i];
        if(present_number[the_number-1]) return false;
        present_number[the_number-1] = true;
    }
    return true;
}

bool check_sudoku2(){
    int *arr = malloc(9 * sizeof(int));
    // Check rows
    bool ok = 1;
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++)
            arr[j] = grid[i][j];
        if(!valid_array(arr)) ok = 0;
    }
    // check collumn
    for(int j=0; j<9; j++){
        for(int i=0; i<9; i++)
            arr[i] = grid[i][j];
        if(!valid_array(arr)) ok = 0;
    }
    // check 3x3
    for(int i = 0; i < 9; i += 3) {
        for(int j = 0; j < 9; j += 3) {
            int cnt = 0;
            for(int k=i; k<i+3; k++){
                for(int h=j; h<j+3; h++)
                    arr[cnt++] = grid[k][h];
            }
            if(!valid_array(arr))ok = 0;
        }
    }
    return ok;
}
int main()
{
    generate_random(example_number);
    for(int n = 0; n < example_number; ++n){
        printf("Sudoku number %d:\n", n+1);
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                printf("%d ", example[n][i][j]);
            }
            printf("\n");
        }
        printf("\n");

        struct timespec start, end;
        double time_used;

        // Test normal version
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                grid[i][j] = example[n][i][j];
            }
        }
        printf("Running on normal...\n");
        clock_gettime(CLOCK_MONOTONIC, &start);
        bool valid = check_sudoku2();
        clock_gettime(CLOCK_MONOTONIC, &end);
        if(valid) printf("Valid Sudoku solution\n");
        else printf("Invalid Sudoku solution\n");
        time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("Running time: %.12f s\n\n", time_used);

        // Test parallel version
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                grid[i][j] = example[n][i][j];
            }
        }
        printf("Running on parallel...\n");
        clock_gettime(CLOCK_MONOTONIC, &start);
        valid = check_sudoku();
        clock_gettime(CLOCK_MONOTONIC, &end);
        if(valid) printf("Valid Sudoku solution\n");
        else printf("Invalid Sudoku solution\n");
        time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        printf("Running time: %.12f s\n\n", time_used);

        printf("---------------------------\n\n");
    }
    return 0;
}
