/**
 * File: graph.h
 * Author: Benjamin Mayes <bdm8233@rit.edu>
 * Description: A simple undirected graph class.
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
class graph {
    public:
        graph();
        graph(unsigned int n);
    private:
        int& edge_entry(unsigned int u, unsigned int v);
    public:
        int has_edge(unsigned int u, unsigned int v);
        unsigned int get_vertices();
        unsigned int get_color(unsigned int v);
        std::vector<unsigned int> get_colors();
        int valid_coloring();
    public:
        void remove_edges(unsigned int v);
        void remove_edge(unsigned int u, unsigned int v);
        void add_edge(unsigned int u, unsigned int v);
        void set_vertices(unsigned int n);
        void set_color(unsigned int v, unsigned int c);
        void set_colors(std::vector<unsigned int> v);
    private:
        unsigned int _n;
        std::vector< std::vector<int> > _amatrix;
        // adj. matrix invariant:
        // Only one entry per edge, entry will be in index _amatrix[min(u,v)][max(u,v)]
        std::vector<unsigned int> _colors;
};
#endif
