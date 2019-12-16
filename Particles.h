#ifndef PARTICLES_H
#define PARTICLES_H

#include "com.h"
#include "Node.h"
#include "Network.h"

class Particles{
	public:
		int size;
		std::list<node_id> node_ids;
		std::map<particle_id,Network> forecast;
		int t;

		Particles(int size, Network forecast);
		Particles(std::map<particle_id,Network> forecast,std::map<particle_id,double> forecast_weight);

		std::map<particle_id,double> get_weight() const { return this->forecast_weight;};
		void cout_likelihood() const;
		void cout_weight() const;
		void cout_state() const;

		void update(std::map<node_id,Node> y);
		double Neff();
/*		void resample(bool condition);
*/
	private:
		std::map<particle_id,Network*> analysis;
		std::map<particle_id,double> forecast_weight;
		std::map<particle_id,double> likelihood;
		std::map<particle_id,double> analysis_weight;
		void normalize(std::map<particle_id,double>& mp);
		void calc_likelihood(const std::map<node_id,Node> y);
		void calc_analysis_weight();
	
};
#endif
