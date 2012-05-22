/**
 * File: graph.h
 * Author: Benjamin Mayes <bdm8233@rit.edu> Tony Bentancur <amb8241@rit.edu>
 * Description: A simple undirected graph class.
 */

#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>

/**
 * A simple undirected graph class.
 */
class graph {
    public:
        /**
         * Constructs a graph with no vertices.
         */
        graph();
        /**
         * Constructs a graph with n vertices.
         *
         * @param n     The number of vertices in the new graph.
         */
        graph(unsigned int n);
    private:
        /**
         * Obtains the reference to the entry for the edge (u,v) and (v,u).
         *
         * Since this graph is undirected (u,v)=(v,u). This function merely
         * returns a reference to the cell at (min(u,v),max(u,v)) in the
         * adjacency matrix. As a result the matrix will be as follows:
         *
         * -XXXXXXXXX   0 <- always 0
         * 0-XXXXXXXX   - <- always 0 (diagonal)
         * 00-XXXXXXX   X <- 0 or 1
         * 000-XXXXXX
         * 0000-XXXXX
         * 00000-XXXX
         * 000000-XXX
         * 0000000-XX
         * 00000000-X
         * 000000000-
         *
         * @param u     One vertex in the edge.
         * @param v     The other vertex in the edge.
         * @return      A reference to cell (min(u,v),max(u,v)) in the adjacency
         *  matrix.
         */
        int& edge_entry(unsigned int u, unsigned int v);
    public:
        /**
         * Determines if (u,v) is an edge in the graph.
         *
         * @param u     One vertex of the edge.
         * @param v     The other vertex of the edge.
         * @param i     The subgraph we are considering. Default value of _n
         *              means that this function behaves as if it was simply
         *              checking the adjacency matrix normally.
         *              Default value of -1 just means that the max integer
         *              will be used which is desirable.
         * @return      true if the edge is present, false otherwise.
         */
        int has_edge(unsigned int u, unsigned int v,unsigned int i=-1);
        /**
         * Obtains the number of vertices in the graph.
         *
         * @return  The number of vertices in the graph.
         */
        unsigned int get_vertices();
        /**
         * Obtains the color of vertex v.
         *
         * @return  The color of vertex v.
         */
        unsigned int get_color(unsigned int v);
        /**
         * Obtains the colors for all vertices in the graph.
         *
         * @return  The color of all vertices in the graph.
         */
        std::vector<unsigned int> get_colors();
        /**
         * Determines if the graph is colored validly.
         *
         * @return  true if the graph is colored validly, false otherwise.
         */
        int valid_coloring(unsigned int i = -1);
        /**
         * Generates an arbitrary random coloring as an initial step to the
         * coloring Markov Chain.
         */
        void generate_arbitrary_coloring();
    public:
        /**
         * Removes all edges incident to vertex v.
         *
         * @param v     The vertex to remove edges from.
         */
        void remove_edges(unsigned int v);
        /**
         * Removes edge (u,v) if it exists.
         *
         * @param u     One vertex of the edge.
         * @param v     The other vertex of the edge.
         */
        void remove_edge(unsigned int u, unsigned int v);
        /**
         * Adds edge (u,v) to the graph.
         *
         * @param u     One vertex of the edge.
         * @param v     The other vertex of the edge.
         */
        void add_edge(unsigned int u, unsigned int v);
        /**
         * Sets the color of vertex v to c. This does not check for validity.
         *
         * @param v     The vertex to color.
         * @param c     The color.
         */
        void set_color(unsigned int v, unsigned int c);
        /**
         * Sets the color of vertex v to c if c is a valid color for v.
         * Otherwise the graph is not modified. If this function succeeds
         * it returns 1, otherwise it returns 0.
         *
         * @param v     The vertex to color.
         * @param c     The color.
         * @param i     The subgraph to verify against.
         * @return      1 if success, 0 if failure.
         */
        int set_color_verify(unsigned int v, unsigned int c, unsigned int i = -1);
        /**
         * Sets the colors of all vertices to the given vector of colors.
         * 
         * @param v     A vector containing at least n colors.
         */
        void set_colors(std::vector<unsigned int> v);
        /**
         * Performs the Markov Chain step. That is it chooses a random vertex
         * and recolors that vertex a random valid color.
         *
         * @param q     The number of colors in the graph
         * @param i     The subgraph we are considering. Default value of _n
         *              means that this function behaves as if it was simply
         *              checking the adjacency matrix normally.
         *              Default value of -1 just means that the max integer
         *              will be used which is desirable.
         */
        void markov_step(unsigned int q, unsigned int i);
        /**
         * Gets a randomly generated valid color for vertex v.
         *
         * @param v     The vertex to find a find color on.
         * @param q     The number of colors.
         * @param i     The subgraph we are considering. Default value of _n
         *              means that this function behaves as if it was simply
         *              checking the adjacency matrix normally.
         *              Default value of -1 just means that the max integer
         *              will be used which is desirable.
         */
        unsigned int get_rand_valid_color(unsigned int v, unsigned int q, unsigned int i = -1);
    private:
        /**
         * The number of vertices in the graph.
         */
        unsigned int _n;
        /**
         * The adjacency matrix.
         * Invariants: One entry per edge at _amatrix[min(u,v)][max(u,v)]
         *             Matrix is MxN, M=N, M and N >= _n
         */
        std::vector< std::vector<int> > _amatrix;

        /**
         * The color assignments for the graph.
         * Invariant: _colors.size() >= _n
         */
        std::vector<unsigned int> _colors;
};
#endif
