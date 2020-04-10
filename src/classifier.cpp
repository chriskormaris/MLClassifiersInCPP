#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

#include "classifier.h"
#include "instancepool.h"

using namespace std;


// Constructor
Classifier::Classifier() {

}

// Copy Constructor
Classifier::Classifier(const Classifier& original) {

}

// Destructor
Classifier::~Classifier() {

}

void Classifier::setNtest(unsigned Ntest) {
    this->Ntest = Ntest;
}

unsigned Classifier::getNtest() const {
    return this->Ntest;
}

// The method setNtest() must always be called before this.
/*
void Classifier::setPredictedLabels(bool* predicted_labels) {
    this->predicted_labels = predicted_labels;
    for (int i=0; i<Ntest; i++) {
        this->predicted_labels[i] = predicted_labels[i];
    }
}

bool* Classifier::getPredictedLabels() const {
    return this->getPredictedLabels();
}
*/

bool* Classifier::classify(InstancePool trainingPool, InstancePool testPool) {
    unsigned Ntest = testPool.getNumberOfInstances();
    
    bool* predicted_labels = new bool[Ntest];
    for (int i=0; i<Ntest; i++) {
        predicted_labels[i] = true;
    }

    return predicted_labels;
}

Classifier& Classifier::operator=(const Classifier& clf) {
    return *this;
}
