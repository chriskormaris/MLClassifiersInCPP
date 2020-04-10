#include <iostream>			/* printf */
#include <string>
#include <vector>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */
#include <fstream>			/* ifstream, ofstream */

#include "instancepool.h"
#include "instance.h"

using namespace std;


// Constructor
InstancePool::InstancePool() {
	
	ifstream keywords_file("keywords-filenames/keywords.txt");
	string keywords_text((istreambuf_iterator<char>(keywords_file)), istreambuf_iterator<char>());

	unsigned i = 0;
	stringstream ss(keywords_text);
	string keyword;
	while( ss >> keyword ) {
		this->features.push_back(keyword);
		this->featureIDs.push_back(i);
		++i;
	}

}

// Copy Constructor
InstancePool::InstancePool(const InstancePool& original) {
	this->messagecollection = original.messagecollection;
	this->features = original.getFeatures();
	this->featureIDs = original.getFeaturesIDs();
}

// Destructor
InstancePool::~InstancePool() {

}

unsigned InstancePool::getNumberOfInstances() const {
	return this->messagecollection.size();
}

const Instance& InstancePool::operator[](unsigned index) const {
	return this->messagecollection[index];
}

vector<string> InstancePool::getFeatures() const {
	return this->features;
}

vector<unsigned> InstancePool::getFeaturesIDs() const {
	return this->featureIDs;
}

InstancePool& InstancePool::operator=(const InstancePool& right) {
	this->messagecollection = right.messagecollection;
	this->features = right.getFeatures();
	this->featureIDs = right.getFeaturesIDs();

    return *this;  // Return a reference to myself.
}

istream& operator>>(istream& in, InstancePool& ip) {
	ip.messagecollection.clear();

	string token;
	in >> token;  // <
	in >> token;  // messagecollection
	in >> token;  // messages
	in >> token;  // =

	string number_of_instances;
	in >> number_of_instances;
  	number_of_instances.erase( 0, 1 );  // erase the first quote "
	number_of_instances.erase( number_of_instances.size() - 1 ); // erase the last quote "
	unsigned N = stoi(number_of_instances);

	// cout << "N: " << N << "\n";

	in >> token;  // >

	for (int i=0; i<N; i++) {
		Instance inst;
		in >> inst;
		ip.messagecollection.push_back(inst);
	}

	in >> token;  // </
	in >> token;  // messagecollection
	in >> token;  // >

	// cout << "token: " << token << "\n";

	return in;
}

ostream& operator<<(ostream& out, InstancePool& ip) {
	out << "< messagecollection messages = \"" << ip.getNumberOfInstances() << "\" >\n";
	for (int i=0; i<ip.getNumberOfInstances(); i++) {
		Instance inst = ip.messagecollection[i];
		out << inst;
	}
	out << "</ messagecollection >\n";

    return out;
}
