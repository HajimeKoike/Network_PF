#include "Particles.h"

Particles::Particles(int size,Network forecast): size(size),id_list(forecast.get_id()){
	for(particle_id id=0;id<this->size;id++){
		this->forecast[id]=forecast;
		this->forecast_weight[id]=1.0/this->size;
	}
}

Particles::Particles(std::map<int,Network> forecast,std::map<int,double> weight): size(weight.size()),forecast(forecast),forecast_weight(weight){
}

void Particles::cout_likelihood() const {
	std::cout<<"likelihood"<<std::endl;
	for(const auto& [id,l]: this->likelihood){
		std::cout<<l<<" ";
	}
	std::cout<<std::endl;
}

void Particles::cout_weight() const {
	std::cout<<"weight"<<std::endl;
	for(const auto& [id,weight]: this->forecast_weight){
		std::cout<<weight<<" ";
	}
	std::cout<<std::endl;
}

void Particles::cout_state() const {
	for(const auto& [id,network]: this->forecast){
		network.cout_state();
	}
	std::cout<<std::endl;
}	

void Particles::normalize(std::map<int,double>& mp){
	double sum=std::accumulate(mp.begin(),mp.end(),0.0,[](double acc, std::pair<int,double> p){ return (acc+p.second); });
	for(auto&& [integer,element]: mp){
		element=element/sum;
	}
}

void Particles::calc_likelihood(const std::map<node_id,Node> y){
	std::map<particle_id,double> l;//size=m
	std::map<particle_id,double> d_net;//size=m
	for(const auto& [id,network] : this->forecast){
		std::map<particle_id,double> d;//size=obs_dim
		for(const auto& [obs_node_id,obs_node]: y){
			double dtmp=double(obs_node.get_state()-network.nodes.at(obs_node_id).get_state());
//			std::cout<<"dtmp "<<dtmp<<std::endl;
			d[obs_node_id]=-0.5*dtmp*dtmp;
		}
		d_net[id]=std::accumulate(d.begin(),d.end(),0.0,[](double acc, std::pair<particle_id,double> p){ return (acc+p.second); });	
		std::cout<<d_net[id]<<std::endl;
		d.clear();
	}
	double dmax=std::max_element(d_net.begin(),d_net.end(),[](std::pair<int,double> p1,std::pair<int,double> p2){ return p1.second<p2.second; })->second;
	std::cout<<"dmax "<<dmax<<std::endl;
	for(const auto& [id,network]: this->forecast){
		d_net[id]-=dmax;
		l[id]=std::exp(d_net[id]);
	}
	normalize(l);
	this->likelihood=l;
}

void Particles::calc_analysis_weight(){
	for(auto&& [id,weight]: this->forecast_weight){
		this->analysis_weight[id]=this->likelihood[id]*weight;
	}
	normalize(this->analysis_weight);
}

void Particles::update(const std::map<node_id,Node> y){
	calc_likelihood(y);
	cout_likelihood();
	calc_analysis_weight();
/*	bool condition=true;
	if(condition){
		resample();
	}else{
		this->analysis=this->forecast;
	}
	this->forecast=this->anaysis;
*/	this->forecast_weight=this->analysis_weight;
	cout_weight();
	this->t=this->t+1;
	this->likelihood.clear();
//	this->analysis.clear();
	this->analysis_weight.clear();
}


double Particles::Neff(){
	double neff_inv=std::accumulate(this->analysis_weight.begin(),this->analysis_weight.end(),0.0,[](double acc,std::pair<particle_id,double> pair){ return acc+pair.second*pair.second; });
	return 1.0/neff_inv;
}

/*
void Particles::resample(){
	//based on my previous code. EDITED BY HAJIME KOIKE on 1st Dec.2019
	std::partial_sum(this->analysis_weight.begin(),this->analysis_weight.end(),std::map<int,double> cumulative_w.begin(),[](std::pair<int,double> p1,std::pair<int,double> p2){ return std::make_pair(p2.first,p1.second+p2.second); });
	double ind=0.0;
	for(particle_id id=0;id<this->size;id++){
		ind+=1.0/this->size;
		
		this->analysis[id]=this->forecast[];
		this->analysis_weight[id]=1.0/this->size;
	}
}
*/

Network Particles::get_analysis() const{
	std::map<node_id,Node> nodes;
	for(auto node_id: this->id_list){
		Node node(node_id);
		double state=0.0;
		double transmission_power=0.0;
		int infectious_period;
		for(particle_id id=0;id<this->size;id++){
			state+=this->forecast.at(id).nodes.at(node_id).get_state()*this->forecast_weight.at(id);
//			transmission_power+=this->analysis.at(id).nodes[node_id].get_transmission_power()*this->analysis_weight.at(id);		
		}
		node.set_state(state);
		node.set_transmission_power(0.3);
		node.set_infectious_period(10);//adopt majority
		nodes[node_id]=node;
	}
	Network analysis(nodes);
	return analysis;
}

