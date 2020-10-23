#ifndef NETWORK_H
#define NETWORK_H

#include "com.h"
#include "Node.h"

class Network{
	public:
		int size;
		std::map<node_id,Node> nodes;

		Network(){;};
		Network(std::map<node_id,Node> nodes) : nodes(nodes) { ; };
		Network(std::map<node_id,std::vector<node_id> > adjs);
		Network(const Network& net): size(net.size), nodes(net.nodes), adjs(net.adjs) {
//		std::cout<<"copy constructor Network"<<std::endl; 
		};
		Network& operator=(const Network& net){ 
//			std::cout<<"operator = Net"<<std::endl;
			if(this==&net){
				;
			}else{
				this->size=net.size;
				this->nodes=net.nodes;
				this->adjs=net.get_adjacent();
			}
			return *this;
		}
/*		Node operator[](node_id id) const { 
			return this->nodes.at(id);
		}//read
		Node operator[](node_id id){ 
			auto itr=nodes.find(id); 
			if(nodes.end()!=itr){
				Node node(itr->second); 
				std::cout<<"[] for exist node"<<std::endl;
				return node;
			}else{
				Node node(id); 
				std::cout<<"[] for new node"<<std::endl; 
				return node;
			}
		}//write
*/
		~Network(){;};

		void set_parameter(std::map<node_id,double> transmission_power,std::map<node_id,int> infectious_period);//set each node's quantities
		void set_state(std::map<node_id,int> state); //set all states;
		void set_adjacent(std::map<node_id,std::vector<node_id> > adjs);

		int get_size() const { return this->size; }
		std::list<node_id> get_id() const;
		std::map<node_id,int> get_state() const;
		std::map<node_id,std::vector<node_id> > get_adjacent() const;

		void cout_id() const;
		void cout_state(bool require_id=true) const;
		void cout_adjacent() const;
		void cout_transmission_power() const;
		void cout_infectious_period() const;

	private: 
		std::map<node_id,std::vector<node_id> > adjs;

		int count_Susceptible() const;
		std::map<int,int> count_Infected() const;
		int count_Recovered() const;
		std::map<int,int> degree_dist() const;
};
#endif
