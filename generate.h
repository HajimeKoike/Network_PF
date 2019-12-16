#ifndef GENERATE_H
#define GENERATE_H

#include "com.h"

void ba(int size,int new_add,std::map<int,std::vector<int> >& adjs);
void complete(int size,std::map<int,std::vector<int> >& adjs);
void er(int size, double p,std::vector<std::pair<int,int> >& edges);
void ws(int size,int mean_degree,double beta,std::map<int,std::vector<int> >& adjs);
void edge_to_adj(std::vector<std::pair<int,int> > edges,std::map<int,std::vector<int> >& adjs,bool directed=false);
void adj_to_edge(std::map<int,std::vector<int> > adjs,std::vector<std::pair<int,int> >& edges);
void symmetrize(std::map<int,std::vector<int> >& adjs);
void adjs_to_adj(std::map<int,std::vector<int> > adjs, std::vector<std::vector<int> >& adj);
void adj_to_adjs(std::vector<std::vector<int> > adj,std::map<int,std::vector<int> >& adjs);
void simplify(std::vector<std::pair<int,int> >& edges);
void cout_edges(std::vector<std::pair<int,int> > edges);
void cout_adjs(std::map<int,std::vector<int> > adjs);
std::map<int,int> degree_dist(std::map<int,std::vector<int> > adjs);

#endif
