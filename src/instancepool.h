#ifndef _INSTANCEPOOL_H
#define _INSTANCEPOOL_H

#include <iostream>			/* printf */
#include <string>
#include <vector>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */
#include "instance.h"

using namespace std;


class InstancePool {

	private:
		vector<Instance> messagecollection;
		vector<string> features;
		vector<unsigned> featureIDs;
	
	public:
		// Constructor
		InstancePool();

		// Copy Constructor
		InstancePool(const InstancePool& original);
		
		// Destructor
		~InstancePool();

		unsigned getNumberOfInstances() const;

		const Instance& operator[](unsigned index) const;

		vector<string> getFeatures() const;

		vector<unsigned> getFeaturesIDs() const;

		InstancePool& operator=(const InstancePool& right);

		friend istream& operator>>(istream& in, InstancePool& ip);
		
		friend ostream& operator<<(ostream& out, InstancePool& ip);

};

#endif