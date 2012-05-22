#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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
    vector<long double> v;
    for( int i = 0; i < 7; ++i ) {
        long double approx = g.sample(ncolors,0.1);
        v.push_back(approx);
        cout << "Run " << i << ":"<< approx << endl;
    }
    sort(v.begin(), v.end());
    cout << "Median of 7: " << v[3] << endl;
}
