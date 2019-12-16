#include "Network.h"

Network::Network(std::map<node_id,std::vector<node_id> > adjs){
	this->size=adjs.size();
	this->adjs=adjs;
	for(auto& [node_id,adj]: adjs){
		Node node(node_id);
		assert(node.get_id()==node_id);
		node.set_adjacent(adjs.at(node_id));
		(this->nodes)[node_id]=node;
//		(this->nodes)[node_id].cout_id();
//		node.cout_id();
	}
}

void Network::set_parameter(std::map<node_id,double> transmission_power,std::map<node_id,int> infectious_period){
	for(auto&& [node_id,node]: this->nodes){
		node.set_transmission_power(transmission_power.at(node_id));
		node.set_infectious_period(infectious_period.at(node_id));
	}
}

void Network::set_state(std::map<node_id,int> state){
	for(auto&& [node_id,node]: this->nodes){
		node.set_state(state.at(node_id));
	}
}

void Network::set_adjacent(std::map<node_id,std::vector<node_id> > adjs){
	this->adjs=adjs;
	for(auto&& [node_id,node]: this->nodes){
		node.set_adjacent(adjs.at(node_id));
	}
}

std::map<node_id,int> Network::get_state() const {
	std::map<node_id,int> state;
	for(const auto& [node_id,node]: this->nodes){
		state[node_id]=node.get_state();
	}
	return state;
}

std::map<node_id,std::vector<node_id> > Network::get_adjacent() const {
	std::map<node_id,std::vector<node_id> > adjacent;
	for(const auto& [node_id,node]: this->nodes){
		adjacent[node_id]=node.get_adjacent();
	}
	return adjacent;
}

void Network::cout_id() const {
	std::cout<<"id of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_id();
	}
}

void Network::cout_state(bool require_id) const {
	std::cout<<"state of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_state(require_id);
	}
	std::cout<<std::endl;
}

void Network::cout_adjacent() const {
	std::cout<<"adjacent nodes of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_adjacent();
	}
}

void Network::cout_transmission_power() const {
	std::cout<<"transmission power of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_transmission_power();		
	}
}

void Network::cout_infectious_period() const {
	std::cout<<"infectious period of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_infectious_period();
	}
}

int Network::count_Susceptible() const {
	int s=0;
	for(const auto& [node_id,node]: this->nodes){
		if(node.get_state()==0){
			s++;
		}
	}
	return s;
}

std::map<int,int> Network::count_Infected() const {
	std::map<int,int> i;
	for(const auto& [node_id,node]: this->nodes){
		if(node.get_state()>0){
			i[node.get_state()]+=1;
		}
	}
	return i;
}

int Network::count_Recovered() const {
	int r=0;
	for(const auto& [node_id,node]: this->nodes){
		if(node.get_state()==-1){
			r++;
		}
	}
	return r;
}

std::map<int,int> Network::degree_dist() const {
	std::map<int,int> degree_dist;
	for(const auto& [node_id,node]: this->nodes){
		degree_dist[node.get_adjacent().size()]+=1;
	}
	return degree_dist;
}
