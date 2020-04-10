#ifndef _INSTANCE_H
#define _INSTANCE_H

#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

using namespace std;

class Instance {

	private:
		string fileName;
		bool category;
		unsigned features;

		string* keywords;
		unsigned* ids;
		float* scores;

	public:
		// Constructor
		Instance(unsigned features = 0);

		unsigned getNumberOfFeatures() const;

		// Copy Constructor
		Instance(const Instance& original);

		// Destructor
		~Instance();

		void setCategory(bool category);

		bool getCategory() const;

		void setFileName(const string& fileName);

		string getFileName() const;

		void setFeature(unsigned i, const string& feature, unsigned featureID, float score);

		string getFeature(unsigned i) const;

		unsigned getFeatureID(unsigned i) const;

		float getScore(unsigned i) const;

		Instance& operator=(const Instance& right);

		friend ostream& operator<<(ostream& out, const Instance& inst);

		friend istream& operator>>(istream& in, Instance& inst);

};

#endif
