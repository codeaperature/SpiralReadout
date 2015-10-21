//
//  SpiralReadout
//
//  Created by Stephan Warren on 10/21/15.
//  Copyright © 2015 Stephan Warren. All rights reserved.
//
/*
 https://www.codeeval.com/open_challenges/57/
 
 
 Spiral Printing
 Challenge Description:
 
 Write a program to print a 2D array (n x m) in spiral order (clockwise)
 Input sample:
 
 Your program should accept as its first argument a path to a filename. The input file contains several lines. Each line is one test case. Each line contains three items (semicolon delimited). The first is 'n'(rows), the second is 'm'(columns) and the third is a single space separated list of characters/numbers in row major order. E.g.
 
 3;3;1 2 3 4 5 6 7 8 9
 
 Output sample:
 
 Print out the matrix in clockwise fashion, one per line, space delimited. E.g.
 
 1 2 3 6 9 8 7 4 5
  
 
 */



#include <string.h> // printf()
#include <stdio.h>  // printf()
#include <stdlib.h> // atoi()
//using namespace std;

int main(int argc, const char *argv[])
{
    int ii, i, n, m;
    char * ptr;
    FILE *file = fopen(argv[1], "r");
    char line[1024];
    
    // table of directions to move as struct
    typedef struct { int x; int y; } directions_t;
    const directions_t delta[4] = {
        { 1,  0}, // right
        { 0,  1}, // down
        {-1,  0}, // left
        { 0, -1}  // up
    };
    // loop over file
    while (fgets(line, 1024, file)) {
        //		printf("%s\n", line);
        
        if(*(line + strlen(line) - 1) == '\n') {
            *(line + strlen(line) - 1) = '\0';
            //			printf("found\n");
        }
        
        // get the row & col dims
        i = 0;
        while(line[++i] != ';');
        *(ptr = line + i) = '\0';
        n = atoi(line);
        while(line[++i] != ';');
        line[i++] = '\0';
        m = atoi(ptr+1);
        //		printf("rows = %d, cols = %d\n", n, m);
        
        // allocate matrix
        // int** matrix = (int**) malloc(m * sizeof(int*));
        // for(int j = 0; j < m; j++)
        // matrix[j] = (int*) malloc(n * sizeof(int));
        char *** matrix = (char ***) malloc(m * sizeof(char **));
        for(ii = 0; ii < m; ii++)
            matrix[ii] = (char **) malloc(n * sizeof(char *));
        
        // parse line & fill matrix
        ptr = strtok(line + i, " ");
        i = ii = 0;
        while(ptr != NULL) {
            matrix[i][ii] = ptr;
            //			printf(">%s<, strlen = %d\n", ptr , strlen(ptr));
            if(++i >= m) {
                i = 0;
                ii++;
            }
            ptr = strtok(NULL, " ");
        }
        // spiral
        int x = -1; // need to init location before first position (-1,0)
        int y = 0;
        int phase = 0; // (0 = right, 1 = down, 2 = left, 3 = up)
        int moveunitsn = n; // move this many cells in current direction
        int moveunitsm = m; // move this many cells in current direction
        
        i = 1;
        strcpy(line, " ");
        ptr = &line[1];
        
        ii = n * m;
        
        while(i <= ii) {
            moveunitsn -= (phase & 1); // decrement horizontal travel size if going down or up
            moveunitsm -= (phase & 1); // decrement vertical travel size if going down or up
            int moveunits = (phase & 1) ? moveunitsn : moveunitsm;
            for(int j = 0; j < moveunits; j++) {
                //				printf("%d, %d - %d\n", i, j, matrix[x += delta[phase].x][y += delta[phase].y]);
                //				printf("%s%d", ptr, matrix[x += delta[phase].x][y += delta[phase].y]);
                printf("%s%s", ptr, matrix[x += delta[phase].x][y += delta[phase].y]);
                i++;
                ptr = line;
            }
            phase = (++phase) & 3;
        }
        printf ("\n");
        /*		
         for(int y = 0; y < n; y++) {
         for(int x = 0; x < m; x++) {
         //				printf("%d%s", matrix[x][y], ((x != (m - 1)) ? ", ":"\n"));
         }
         }
         */
        for(i = 0; i < m; i++) 
            free(matrix[i]);
        free(matrix); 
    }
    return 0;
}

