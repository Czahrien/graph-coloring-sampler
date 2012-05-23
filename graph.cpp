/**
 * File: graph.cpp
 * Author: Benjamin Mayes <bdm8233@rit.edu> Tony Bentancur <amb8241@rit.edu>
 * Description: A simple undirected graph class.
 *
 */

#include <cassert>
#include <iostream>
#include <set>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "graph.h"
#define OMIT_OUTPUT

// O(1)
graph::graph() : _n(0), _amatrix(), _colors() {}

// O(N)
graph::graph(unsigned int n) : _n(n), _amatrix(n,std::vector<int>(n,0)), _colors(n,0) {}

// O(1)
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

// O(1)
int graph::has_edge(unsigned int u, unsigned int v, unsigned int i) {
    assert( u < _n && v < _n);
    // if either of these are the case the edge is not in the subgraph
    // being considered.
    if(v < i && u < i) {
        return edge_entry(u,v);
    } else {
        return 0;
    }
}

// O(1)
unsigned int graph::get_vertices() {
    return _n;
}

// O(1)
unsigned int graph::get_color(unsigned int v) {
    assert(v < _n);
    return _colors[v];
}

// O(N)
std::vector<unsigned int> graph::get_colors() {
    return _colors;
}

// O(N^2)
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

// O(N)
void graph::remove_edges(unsigned int v) {
    assert(v < _n);
    for( unsigned int i = 0u; i < _n; ++i ) {
        edge_entry(i,v) = 0u;
    }
}

// O(1)
void graph::remove_edge(unsigned int u, unsigned int v) {
    assert(u < _n && v < _n);
    edge_entry(u,v) = 0;
}

// O(1)
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
        while( !set_color_verify(i,c++,i+1) ) ; // O(N)
    }
}
// average O(n^2)
void graph::markov_step(unsigned int q, unsigned int i) {
    assert(valid_coloring(i));
    unsigned int v = rand() % _n;
    set_color(v, get_rand_valid_color(v,q,i));
}
// average O(nlog(n))
unsigned int graph::get_rand_valid_color(unsigned int v, unsigned int q, unsigned int i) {
    std::set<unsigned int> invalid_colors;

    if(i > _n)
        i = _n;
    
    for(unsigned int j = 0; j < i; j++){
        if(has_edge(v,j,i)){
            invalid_colors.insert(get_color(j));
        }
    }
    
    unsigned int color;
    //average O(q / (q - delta))
    do{
        color = rand() % q;
    }
    while(invalid_colors.find(color) != invalid_colors.end() );

    return color;
}

// average O(n^4/eps^2)
long double graph::sample(unsigned int q, long double epsilon) {
	generate_arbitrary_coloring();
    unsigned int delta = 0;
    for( unsigned int i = 0; i < _n; ++i ) {
        unsigned int ndelta = 0;
        for( unsigned int j = 0; j < _n; ++j ) {
            ndelta += static_cast<unsigned int>(has_edge(i,j));
        }
        delta = delta < ndelta ? ndelta : delta;
    }
#ifndef OMIT_OUTPUT
    std::cout << "Given graph has delta = " << delta << " colors." << std::endl;
    if( q < 2*delta) std::cout << "Warning: q (" << q << ") < 2*delta. Sample may be inaccurate." <<std::endl;
#endif
    unsigned int steps;
    if( 2*delta >= q ) {
        std::cout << "# of colors < 2*delta. Mixing and termination of sampler not guaranteed." << std::endl;
        // some large number of steps just to "try" to mix the chain.
        steps = q*_n*_n/epsilon;
    } else {
        steps = static_cast<unsigned int>(static_cast<long double>((q*_n)/(q-2*delta)*log(_n/epsilon)));
    }
#ifndef OMIT_OUTPUT
    std::cout << "Mixing Markov chain by running for " << steps << " steps" << std::endl; 
#endif
    unsigned int start = time(NULL);
	for(unsigned int i = 0; i < steps; i++){
		markov_step(q,_n);
	}
#ifndef OMIT_OUTPUT
    std::cout << "Markov chain mixed in " <<  time(NULL) - start << "s" << std::endl;
    std::cout << "Random coloring: <";
    for( unsigned int i = 0; i < _n; ++i ) {
        std::cout << _colors[i];
        if(i != _n - 1) {
            std::cout << ",";
        } else {
            std::cout << ">" << std::endl;
        }
    }
#endif
    unsigned int samples = static_cast<unsigned int> (ceil ( (75*_n) / (epsilon*epsilon) ));
	long double ln_samples = log (samples);
    long double rho_product = 0;
#ifndef OMIT_OUTPUT
    std::cout << "Starting sampling..." << std::endl;
#endif
    for(unsigned int i = _n - 1; i > 0; i--){ // O(n*n^3/eps^2)
        unsigned int count = 0;
		for(unsigned int s = 1; s < samples; s++){ // O(n^2*n/eps^2)
			markov_step(q,i); // run a step of the markov chain on graph G_i
            assert(valid_coloring(i));
			if(valid_coloring(i+1)){ // increment the count if the coloring is valid on G_{i+1}
                count++;
            }
		}
        // calculate the logarithm of rho_i
        long double rho_i =  (log(count) - ln_samples); 
#ifndef OMIT_OUTPUT
        std::cout << "rho_" << i << "=>" << exp(log(count)-ln_samples) << std::endl;
#endif
        // "multiply" in the rho term to the product.
        rho_product += rho_i;
	}
    // "multiply" out the q^n term
    rho_product += _n*log(q);
	return exp (rho_product);
}
