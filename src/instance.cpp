#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */
#include "instance.h"

using namespace std;


Instance::Instance(unsigned features) {
	this->features = features;
	
	this->keywords = new string[features];
	this->ids = new unsigned[features];
	this->scores = new float[features];
}

unsigned Instance::getNumberOfFeatures() const {
	return this->features;
}

Instance::Instance(const Instance& original) {
	this->fileName = original.getFileName();
	this->category = original.getCategory();
	this->features = original.getNumberOfFeatures();

	this->keywords = new string[original.getNumberOfFeatures()];
	this->ids = new unsigned[original.getNumberOfFeatures()];
	this->scores = new float[original.getNumberOfFeatures()];

	for (int i=0; i<original.getNumberOfFeatures(); i++) {
		this->setFeature(i, original.getFeature(i), original.getFeatureID(i), original.getScore(i));
	}
}

// Destructor
Instance::~Instance() {

}

void Instance::setCategory(bool category) {
	this->category = category;
}

bool Instance::getCategory() const {
	return this->category;
}

void Instance::setFileName(const string& fileName) {
	this->fileName = fileName;
}

string Instance::getFileName() const {
	return this->fileName;
}

void Instance::setFeature(unsigned i, const string& feature, unsigned featureID, float score) {
	this->ids[i] = featureID;
	this->scores[i] = score;
	
	this->keywords[i] = feature;
}

string Instance::getFeature(unsigned i) const {
	return keywords[i];
}

unsigned Instance::getFeatureID(unsigned i) const {
	return ids[i];
}

float Instance::getScore(unsigned i) const {
	return scores[i];
}

Instance& Instance::operator=(const Instance& right) {
	this->fileName = right.getFileName();
	this->category = right.getCategory();
	this->features = right.getNumberOfFeatures();

	this->keywords = new string[right.getNumberOfFeatures()];
	this->ids = new unsigned[right.getNumberOfFeatures()];
	this->scores = new float[right.getNumberOfFeatures()];

	for (int i=0; i<right.getNumberOfFeatures(); i++) {
		this->setFeature(i, right.getFeature(i), right.getFeatureID(i), right.getScore(i));
	}

    return *this;  // Return a reference to myself.
}

ostream& operator<<(ostream& out, const Instance& inst) {
	if (inst.getCategory())  // if the category is spam
		out << "< message file = \"" << inst.getFileName() << "\" category = \"spam\" features = " << inst.getNumberOfFeatures() << "\" >\n";
	else  // if the category is ham
		out << "< message file = \"" << inst.getFileName() << "\" category = \"ham\" features = " << inst.getNumberOfFeatures() << "\" >\n";

	for (int i=0; i<inst.getNumberOfFeatures(); i++) {
		out << "< feature token = \"" << inst.getFeature(i) << "\" id = \"" << inst.getFeatureID(i) << "\" tfidf = " << inst.getScore(i) << "\" >\n";
	}

	out << "</ message >\n";

    return out;
}

istream& operator>>(istream& in, Instance& inst) {

	string token;
	
	in >> token;  // <
	in >> token;  // message
	in >> token;  // file
	in >> token;  // =

	string fileName;
	in >> fileName;
	fileName.erase( 0, 1 );  // erase the first quote "
    fileName.erase( fileName.size() - 1 ); // erase the last quote "
	// cout << "fileName: " << fileName << "\n";

	in >> token;  // category
	in >> token;  // =

	string category;
	in >> category;
	category.erase( 0, 1 );  // erase the first quote "
    category.erase( category.size() - 1 ); // erase the last quote "
	// cout << "category: " << category << "\n";

	in >> token;  // features
	in >> token;  // =

	string features;
	in >> features;
	features.erase( 0, 1 );  // erase the first quote "
    features.erase( features.size() - 1 ); // erase the last quote "
	unsigned m = stoi(features);
	// cout << "m: " << m << "\n";

	in >> token;  // >

	inst.features = m;

	inst.setFileName(fileName);
	if (category == "spam")
		inst.setCategory(true);
	else if (category == "ham")
		inst.setCategory(false);

	inst.keywords = new string[inst.getNumberOfFeatures()];
	inst.ids = new unsigned[inst.getNumberOfFeatures()];
	inst.scores = new float[inst.getNumberOfFeatures()];

	for (int i=0; i<inst.getNumberOfFeatures(); i++) {
		in >> token;  // <
		in >> token;  // feature
		in >> token;  // token
		in >> token;  // =

		string keyword;
		in >> keyword;
		keyword.erase( 0, 1 );  // erase the first quote "
    	keyword.erase( keyword.size() - 1 ); // erase the last quote "
		// cout << "keyword: " << keyword << "\n";

		in >> token;  // id
		in >> token;  // =
		
		string id_string;
		in >> id_string;
		id_string.erase( 0, 1 );  // erase the first quote "
    	id_string.erase( id_string.size() - 1 ); // erase the last quote "
		unsigned id = stoi(id_string);
		// cout << "id: " << id << "\n";

		in >> token;  // tfidf
		in >> token;  // =

		string tfidf_string;
		in >> tfidf_string;
		tfidf_string.erase( 0, 1 );  // erase the first quote "
    	tfidf_string.erase( tfidf_string.size() - 1 ); // erase the last quote "
		float tfidf = stof(tfidf_string);
		// cout << "tfidf: " << tfidf << "\n";

		in >> token;  // />

		inst.setFeature(i, keyword, id, tfidf);

	}

	in >> token;  // </
	in >> token;  // message
	in >> token;  // >

	return in;
}
