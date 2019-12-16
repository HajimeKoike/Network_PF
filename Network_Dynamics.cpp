#include "Network_Dynamics.h"

void Network_Dynamics::step(){

	//state & parameter update
	std::cout<<"start"<<std::endl;
	for(auto&& [node_id, node]: (this->now).nodes){
		//state update
//		std::cout<<"accessed node"<<std::endl;
		if(node.get_state()==0){
//			std::cout<<"accessed state of node"<<std::endl;
//			node.cout_adjacent();
			for(const auto& nbd_id: node.get_adjacent()){
//			std::cout<<"accessed adjacent of node"<<std::endl;
				if((this->now).nodes.at(nbd_id).get_state()>0){
//				std::cout<<"accessed state of adjacent of node"<<std::endl;
					std::random_device rd;
					std::mt19937 mt(rd());
					std::uniform_real_distribution<double> u(0.0,1.0);
					double rand=u(mt);
					if(rand<(this->now).nodes.at(nbd_id).get_transmission_power()){
						node.get_infected();
						std::cout<<"infected "<<node.get_id()<<"by "<<nbd_id<<std::endl;
					}
				}
			}
		}else if(node.get_state()>0){
			node.step();
		}else{
			;
		}
		(this->next).nodes[node_id]=node;
		//parameter update
	}
//	(this->next) = (this->now).nodes;
	//structure update
	(this->next).set_adjacent((this->now).get_adjacent());
	(this->next).size=(this->now).get_size();

	this->now=this->next;
	this->t=this->t+1;	

	std::cout<<"next clear"<<std::endl;
	(this->next).nodes.clear();
	std::cout<<"done"<<std::endl;
}	

void Network_Dynamics::run(int T){
	for(int t=0;t<T;t++){
		step();
	}
}
