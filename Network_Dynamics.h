#ifndef NETWORK_DYNAMICS_H
#define NETWORK_DYNAMICS_H

#include "com.h"
#include "Network.h"

class Network_Dynamics{
	public:
		Network now;
		Network next;
		int t;
		Network_Dynamics(const Network now): now(now), t(0) { std::cout<<"dynamics"<<std::endl;};
		void step();
		void run(int T);
};

#endif
