/**
 * File: graph.cpp
 * Author: Benjamin Mayes <bdm8233@rit.edu>
 * Description: A simple undirected graph class.
 */

#include <cassert>
#include <iostream>
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
int graph::has_edge(unsigned int u, unsigned int v, unsigned int i) {
    assert( u < _n && v < _n);
    // if either of these are the case the edge is not in the subgraph
    // being considered.
    std::cout << v << " " << u << " " << i << std::endl;
    if(v < i && u < i) {
        std::cout << "lt i" << std::endl;
        return edge_entry(u,v);
    } else {
        std::cout << "gte i" << std::endl;
        return 0;
    }
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

int graph::valid_coloring(unsigned int i) {
    if( i > _n) i = _n;
    for( unsigned int k = 0; k < i; ++k ) {
        unsigned int c = _colors[k];
        for( unsigned int j = k; j < i; ++j ) 
            if(_amatrix[k][j]) {
                if( c == _colors[j] ) {
                    return false;
                }
            }
    }
    return true;
}

void graph::remove_edges(unsigned int v) {
    assert(v < _n);
    for( unsigned int i = 0u; i < _n; ++i ) {
        edge_entry(i,v) = 0u;
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

// O(1)
void graph::set_color(unsigned int v, unsigned int c) {
    assert(v < _n);
    _colors[v] = c;
}

// O(N)
int graph::set_color_verify(unsigned int v, unsigned int c, unsigned int i) {
    assert(v < _n);
    if( i > _n ) i = _n;
    for(unsigned int j = 0; j < i; ++j) { // O(N)
        if(has_edge(v,j,i)) { 
            if(c == _colors[j]) {
                return 0;
            }
        }
    }
    _colors[v] = c;
    return 1;
}

// O(1)
void graph::set_colors(std::vector<unsigned int> v) {
    assert(v.size() >= _n);
    _colors = v;
}

// O(N^2)
void graph::generate_arbitrary_coloring() {
    // first vertex's color should be 0
    _colors[0] = 0;

    // for the remaining vertices color based on only the
    // previously colored vertices
    for( unsigned int i = 1; i < _n; ++i ) { // O(N^2)
        unsigned int c = 0;
        // c will never have to be a value greater than delta+1. 
        // Additionally if we consider only the first i+1 vertices we are able
        // to efficiently arrive at a valid coloring in O(N*(N+1)/2) steps as
        // opposed to O(N^2) which is slightly more efficient.
        while( !set_color_verify(i,c++,i+1)); // O(N)
    }
    //std::cout << c - 1 << std::endl;   
}
