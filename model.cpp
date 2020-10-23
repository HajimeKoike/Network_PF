#include "com.h"
#include "Node.h"
#include "Network.h"
#include "Network_Dynamics.h"
#include "generate.h"
#include "Particles.h"

int main(){
	std::map<node_id,std::vector<node_id> > adjs;
	std::vector<std::vector<node_id>  > adj{{1,2},{0,2},{0,1,3},{2}};

	adj_to_adjs(adj,adjs);

	adjs.clear();	
	int size=6;
	double p=0.3;
	int mean_degree=2;
	int new_add=2;
	std::vector<std::pair<int,int> > edges;
//	er(size,p,edges);
//	symmetrize(adjs);
//	complete(size,adjs);
//	ba(size,new_add,adjs);//automatically symmetrized
	std::cout<<"BEGIN CONSTRUCTION"<<std::endl;
	ws(size,mean_degree,p,adjs);//automatically symmetrized
	cout_adjs(adjs);

	Network network(adjs);
	std::cout<<"ADJ"<<std::endl;
	network.cout_adjacent();
	network.nodes[int(network.size/2)].get_infected();
	std::map<node_id,double> transmission_power;
	std::map<node_id,int> infectious_period;
	for(int k=0;k<adjs.size();k++){
		transmission_power[k]=0.3;
		infectious_period[k]=10;
	}
	network.set_parameter(transmission_power,infectious_period);
	network.cout_transmission_power();

	int Tend=10;
	Particles nets(50,network);
	std::cout<<"PREPARED PARTICLE"<<std::endl;
	Network_Dynamics networkdyn(network);
	std::map<node_id,Node> y;

	for(int t=0;t<Tend;t++){
		std::cout<<"TIMESTEP "<<t<<std::endl;
		std::cout<<"TRUE"<<std::endl;
		networkdyn.now.cout_state();
		networkdyn.step();
		if(!&(networkdyn.now)){
			std::cerr<<"dynamical system not working "<<std::endl;
			std::exit(1);
		}
		y.clear();
		for(int k=0;k<networkdyn.now.size;k+=1){
			Node obs(networkdyn.now.nodes[k]);
			y[k]=obs;
		}

		std::cout<<"PARTICLES"<<std::endl;
		for(auto&& [id,net]: nets.forecast){
			Network_Dynamics netdyn(net);
			netdyn.step();
			net=netdyn.now;
		}
		nets.update(y);
		Network anal=nets.get_analysis();
		anal.cout_state();
	}
		
	return 0;
}
