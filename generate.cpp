#include "com.h"
#include "generate.h"

template<typename Container>
bool exist_in(const Container& c,const typename Container::value_type& v){
	return (c.end() != std::find(c.begin(),c.end(),v) );
}

void ba(int size,int new_add,std::map<int,std::vector<int> >& adjs){
	if(adjs.empty()){
		std::cerr<<"empty graph "<<std::endl; std::exit(1);
	}
	while(adjs.size()<size){
		std::cout<<adjs.size()<<std::endl;
		int m0=adjs.size();
		std::vector<int> new_adj;//id=adj.size()=m0

		int sum=0;
		for(int k=0;k<adjs.size();k++){
			sum+=adjs[k].size();
		}	

		std::vector<double> p(adjs.size());
		for(int k=0;k<adjs.size();k++){
			p[k]=double(adjs[k].size())/double(sum);
		}	
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> u(0.0,1.0);


		for(int m=0;m<new_add;m++){
			double rand=u(mt);
			int k=0;
			std::vector<double>::iterator itr=p.begin();
			for(itr=p.begin();itr!=p.end();++itr){
					rand-=*itr;
					if(rand<=0){
						break;
					}
					k++;
			}
			adjs[k].push_back(m0);
			new_adj.push_back(k);

			p[k]=0.0;	
		}
		p.clear();
		adjs[m0]=new_adj;
	}
}

void complete(int size,std::map<int,std::vector<int> >& adjs){
	for(int i=0;i<size;i++){
		std::vector<int>  adj;//id=i
		for(int j=0;j<i;j++){
			adj.push_back(j);
		}
		for(int j=i+1;j<size;j++){
			adj.push_back(j);
		}

		adjs[i]=adj;
	}
}

void er(int size, double p,std::vector<std::pair<int,int> >& edges){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> u(0.0,1.0);

	for(int i=0;i<size;i++){
		for(int j=0;j<i;j++){
			if(u(mt)<p){
				std::pair<int,int> edge;
				edge.first=i;
				edge.second=j;
				edges.push_back(edge);
			}
		}
		for(int j=i+1;j<size;j++){
			if(u(mt)<p){
				std::pair<int,int> edge;
				edge.first=i;
				edge.second=j;
				edges.push_back(edge);
			}
		}
	}
}

void ws(int size,int mean_degree,double beta,std::map<int,std::vector<int> >& adjs){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> u(0.0,1.0);
	//construct regular ring lattice
	for(int i=0;i<size;i++){
		std::vector<int> adj;//adj[i]
		for(int j=i-int(mean_degree/2);j<i;j++){
			int j_mod_size=j;
			if(j<0){
				j_mod_size+=size;
			}
			adj.push_back(j_mod_size);
		}
		for(int j=i+1;j<=i+int(mean_degree/2);j++){
			int j_mod_size=j;
			if(j>=size){
				j_mod_size-=size;
			}
			adj.push_back(j_mod_size);
		}
		adjs[i]=adj;
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<adjs.at(i).size();j++){
			double rand;
			int rewire;
			rand=u(mt);
			if(rand<beta){
				do{
					rewire=int(u(mt)*size);
				}while(rewire==i);
				if(!exist_in(adjs.at(i),rewire)){
					int k=adjs.at(i)[j];
					adjs.at(i)[j]=rewire;
					auto itr=std::find(adjs.at(k).begin(),adjs.at(k).end(),i);
					//int index=std::distance(adj[k].begin(),itr);
					adjs.at(k).erase(itr);
					adjs.at(rewire).push_back(i);
				}
			}
		}
	}

}
/*
void ws(int size,int mean_degree,double beta,std::vector<std::pair<int,int> >& edges){
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> u(0.0,1.0);
	//construct regular ring lattice
	for(int i=0;i<size;i++){
		for(int j=i-int(mean_degree/2);j<i;j++){
			std::pair<int,int> edge;
			int j_mod_size=j;
			if(j<0){
				j_mod_size+=size;
			}
			edge.first=i;
			edge.second=j_mod_size;
			edges.push_back(edge);
		}
		for(int j=i+1;j<=i+int(mean_degree/2);j++){
			std::pair<int,int> edge;
			int j_mod_size=j;
			if(j>=size){
				j_mod_size-=size;
			}
			edge.first=i;
			edge.second=j_mod_size;
			edges.push_back(edge);
		}
	}

	for(auto edge: edges){
		if(u(mt)<beta){
			int random=int(u(mt)*size);
			edge.second=random;
		}
	}
}
*/
//edge list/adjacency list converter

void edge_to_adj(std::vector<std::pair<int,int> > edges,std::map<int,std::vector<int> >& adjs,bool directed){
	for(auto edge: edges){
		adjs[edge.first].push_back(edge.second);	
		if(directed==false){
			adjs[edge.second].push_back(edge.first);
		}
	}
}

void adj_to_edge(std::map<int,std::vector<int> > adjs,std::vector<std::pair<int,int> >& edges){
	for(auto adj: adjs){
		for(auto itr=adj.second.begin();itr!=adj.second.end();itr++){
			std::pair<int,int> pair;
			pair.first=adj.first;
			pair.second=*itr;
			edges.push_back(pair);
		}
	}	
}


//symmetric list for undirected graph
void symmetrize(std::map<int,std::vector<int> >& adjs){
	for(int i=0;i<adjs.size();i++){
		for(int j=0;j<adjs.at(i).size();j++){
			int k=adjs.at(i)[j];
			if(!exist_in(adjs.at(k),i)){
				adjs[k].push_back(i);
			}
		}
	}
}

void adjs_to_adj(std::map<int,std::vector<int> > adjs, std::vector<std::vector<int> >& adj){
	std::vector<std::vector<int> > adj0(adjs.size());
	for(auto node=adjs.begin();node!=adjs.end();++node){
		adj0[node->first]=node->second;
	}
	adj=adj0;
}

void adj_to_adjs(std::vector<std::vector<int> > adj,std::map<int,std::vector<int> >& adjs){
	for(int i=0;i<adj.size();i++){
		adjs[i]=adj[i];
	}
}

void simplify(std::vector<std::pair<int,int> >& edges){
	std::vector<std::pair<int,int> > edges_simplified;
	std::vector<std::pair<int,int> >::iterator itr;
	for(itr=edges.begin();itr!=edges.end();++itr){
		std::pair<int,int> pair;
		if(itr->first==itr->second || (edges_simplified.end() != std::find(edges_simplified.begin(),edges_simplified.end(),*itr)) ){
			continue;
		}
		pair.first=itr->first;
		pair.second=itr->second;
		edges_simplified.push_back(pair);
	}
	edges.clear();
	edges=edges_simplified;
}

void cout_edges(std::vector<std::pair<int,int> > edges){
	for(auto edge: edges){
		std::cout<<edge.first<<" "<<edge.second<<std::endl;
	}
}

void cout_adjs(std::map<int,std::vector<int> > adjs){
	for(auto itr=adjs.begin();itr!=adjs.end();itr++){
		std::cout<<itr->first<<" ";
		for(auto nbd: itr->second){
			std::cout<<nbd<<" ";
		}
		std::cout<<std::endl;
	}
}

std::map<int,int> degree_dist(std::map<int,std::vector<int> > adjs){
	std::map<int,int> degree_dist;
	for(auto node: adjs){
		degree_dist[node.second.size()]+=1;
	}
	return degree_dist;
}
