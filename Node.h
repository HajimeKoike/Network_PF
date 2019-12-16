#ifndef NODE_H
#define NODE_H

#include "com.h"

class Node{
	private:
		node_id id;//identification number of node
		int state;
		int t;
		double transmission_power;
		int infectious_period;
		std::vector<node_id> adj;//adj={id1,id2,...,idn} not an adjacent matrix!! 

	public:
		Node(){;}
		Node(node_id id): id(id),state(0),t(0) { ; }
		Node(const Node& node): id(node.id),state(node.state),t(node.t),transmission_power(node.transmission_power),infectious_period(node.infectious_period),adj(node.adj) { 
//			std::cout<<"copy const"<<std::endl; 
		};
		~Node(){;}
		Node& operator=(const Node& node) { 
//			std::cout<<"operator = "<<std::endl; 
			if(this==&node){
				return *this;
			}else{
				this->id = node.get_id();
				this->state = node.get_state();
				this->t = node.get_t();
				this->transmission_power = node.get_transmission_power();
				this->infectious_period = node.get_infectious_period();
				this->adj = node.get_adjacent();	
				return *this;
			}
		}


		void set_state(const int state);
		void set_transmission_power(const double transmission_power);
		void set_infectious_period(const int infectious_period);
		void set_adjacent(const std::vector<node_id> adj);

		node_id get_id() const;
		int get_state() const;
		int get_t() const { return this->t; }
		double get_transmission_power() const;
		int get_infectious_period() const;
		std::vector<node_id> get_adjacent() const;

		void cout_id() const;
		void cout_state(bool require_id=true) const;
		void cout_adjacent() const;
		void cout_transmission_power() const;
		void cout_infectious_period() const;

		void get_infected();
		void step();
};
#endif
