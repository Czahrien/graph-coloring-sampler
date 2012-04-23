/**
 * File: graph.cpp
 * Author: Benjamin Mayes <bdm8233@rit.edu>
 * Description: A simple undirected graph class.
 */

#include <cassert>
#include "graph.h"

graph::graph() : _n(0), _amatrix(), _colors() {}
graph::graph(unsigned int n) : _n(n), _amatrix(n,std::vector<int>(n,0)), _colors(n,0) {}

int& graph::edge_entry(unsigned int u, unsigned int v) {
    //assuming u and v are checked...
    if( u > v ) {
        // swap u and v
        u = u^v; // u' = u^v, v' = v
        v = v^u; // u' = u^v, v' = v^u^v = u
        u = u^v; // u' = u^v^u = v, v' = u
    }
    return (_amatrix[u][v]);
}
int graph::has_edge(unsigned int u, unsigned int v) {
    assert( u < _n && v < _n );
    unsigned int ret;
    return edge_entry(u,v);
}

unsigned int graph::get_vertices() {
    return _n;
}

unsigned int graph::get_color(unsigned int v) {
    assert(v < _n);
    return _colors[v];
}

std::vector<unsigned int> graph::get_colors() {
    return _colors;
}

int graph::valid_coloring() {
    for( unsigned int i = 0; i < _n; ++i ) {
        int c1 = _colors[i];
        for( unsigned int j = i; j < _n; ++j ) 
            if(_amatrix[i][j]) {
                if( i == _colors[j] ) {
                    return false;
                }
            }
    }
    return true;
}

void graph::remove_edges(unsigned int v) {
    assert(v < _n);
    for( int i = 0; i < _n; ++i ) {
        edge_entry(i,v) = 0;
    }
}

void graph::remove_edge(unsigned int u, unsigned int v) {
    assert(u < _n && v < _n);
    edge_entry(u,v) = 0;
}

void graph::add_edge(unsigned int u, unsigned int v) {
    assert(u < _n && v < _n);
    edge_entry(u,v) = 1;
}

void graph::set_vertices(unsigned int n) {
    return; //TODO: Implement me
}

void graph::set_color(unsigned int v, unsigned int c) {
    assert(v < _n);
    _colors[v] = c;
}

void graph::set_colors(std::vector<unsigned int> v) {
    assert(v.size() >= _n);
    _colors = v;
}
