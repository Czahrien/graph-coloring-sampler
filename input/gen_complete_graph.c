/**
 * File: gen_complete_graph.c
 * Author: Benjamin Mayes
 * Description: Generates an input file for a complete graph with n vertices and k colors.
 *
 * usage: ./gen_complete_graph (# of vertices) (# of colors)
 */

#include <stdio.h>

int main(int argc, char** argv ) {
    if( argc != 3 ) {
        fprintf(stderr, "usage: %s n q\n", argv[0] );
        return 1;
    }
    int i,j;
    int n;
    int q;
    if( !(sscanf(argv[1],"%d",&n) && sscanf(argv[2],"%d",&q)) ) {
        fprintf(stderr, "error: Invalid value for n or q!\n" );
        return 1;
    }
    if( !(n > 0 && q > 0) ) {
        fprintf(stderr, "error: Values for n and q must be positive!\n" );
        return 1;
    }

    char outputfile[64];
    sprintf(outputfile,"k%dq%d.in",n,q);
    FILE* out = fopen(outputfile, "w");
    fprintf(out,"%d\n%d\n%d\n",n,n*(n-1)/2,q);
    for(i = 0; i < n; ++i) {
        for(j = i + 1; j < n; ++j) {
            fprintf(out,"%d %d\n", i, j );
        }
    }
    fclose(out);
    return 0;
}
