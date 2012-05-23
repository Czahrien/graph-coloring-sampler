/**
 * File: gen_graph.c
 * Author: Benjamin Mayes
 * Description: Generates an input file for a graph with n vertices and k colors with the probability for each edge .
 *
 * usage: ./gen_graph (# of vertices) (# of colors) (prob, default=1.0)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv ) {
    srand(time(NULL));
    if( argc != 3 && argc != 4 ) {
        fprintf(stderr, "usage: %s n q [p]\n", argv[0] );
        return 1;
    }
    unsigned int i,j;
    unsigned int n;
    unsigned int q;
    double prob = 1.0;
    if( !(sscanf(argv[1],"%d",&n) && sscanf(argv[2],"%d",&q)) ) {
        fprintf(stderr, "error: Invalid value for n or q!\n" );
        return 1;
    }
    int p_given = (argc == 4);
    if( p_given && !sscanf(argv[3],"%lf",&prob) ) {
        fprintf(stderr, "error: Invalid probability given - %s\n", argv[3]);
    }
    if( !(n > 0 && q > 0) ) {
        fprintf(stderr, "error: Values for n and q must be positive!\n" );
        return 1;
    }
    unsigned int m = 0;
    char edges[n*(n-1)/2][21]; //21 because 9*2 for integers + 1 for space + 1 for newline + 1 for null 
    char outputfile[64];
    sprintf(outputfile,"n%dq%dp%.2f.in",n,q,prob);
    FILE* out = fopen(outputfile, "w");
    for(i = 0; i < n; ++i) {
        for(j = i + 1; j < n; ++j) {
            if( !p_given || (double)rand()/RAND_MAX <= prob)
                sprintf(edges[m++],"%d %d\n", i, j );
        }
    }
    fprintf(out,"%d\n%d\n%d\n",n,m,q);
    for(i = 0; i < m; ++i ) {
        fprintf(out, "%s", edges[i]);
    }
    fclose(out);
    return 0;
}
