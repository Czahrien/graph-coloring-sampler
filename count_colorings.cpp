#include <iostream>
#include <fstream>
#include "graph.h"
using namespace std;

int main(int argc, char** argv) {
    istream * in = &cin;
    filebuf fb;
    if( argc == 2 ) {
        fb.open( argv[1], ifstream::in );
        if( !fb.is_open() ) { 
            cerr << "Invalid filename: " << argv[1];
            return 1;
        } else {
            in = new istream(&fb);
        }
    } 

    int n, m, ncolors;
    *in >> n;
    *in >> m;
    *in >> ncolors;
    graph g(n);

    for( int i = 0; i < m; ++i ) {
        int e1, e2;
        *in >> e1 >> e2;
        g.add_edge(e1,e2);
    }
    

    vector<unsigned int> colors(n,0);
    long count = 0;
    long prod = 1;
    for( int i = 0; i < n; ++i ) {
        prod *= ncolors;
    }
    for( int i = 0; i < prod; ++i ) {
        int tmp = i;
        for( int j = 0; j < n; ++j ) {
            int v = tmp % ncolors;
            colors[j] = v;
            tmp /= ncolors;
        }
        g.set_colors(colors);
        count += g.valid_coloring();
    }
    cout << count << endl;
}