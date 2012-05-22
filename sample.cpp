#include <iostream>
#include <fstream>
#include <vector>
#include "graph.h"

using namespace std;

int main(int argc, char** argv) {
    istream * is = &cin;
    filebuf fb;
    if( argc == 2 ) {
        fb.open( argv[1], ifstream::in );
        if( !fb.is_open() ) { 
            cerr << "Invalid filename: " << argv[1] << "\n";
            return 1;
        } else {
            is = new istream(&fb);
        }
    } 

    istream& in(*is);
    int n, m, ncolors;
    in >> n;
    in >> m;
    in >> ncolors;
    graph g(n);

    for( int i = 0; i < m; ++i ) {
        int e1, e2;
        in >> e1 >> e2;
        g.add_edge(e1,e2);
    }
    long double approx = g.sample(ncolors,0.1);
    cout << approx << endl;
}
