#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout, rand_r */

#include "baselineclassifier.h"
#include "instancepool.h"

using namespace std;

// Constructor
BaselineClassifier::BaselineClassifier() : Classifier() {

}

// Copy Constructor
BaselineClassifier::BaselineClassifier(const BaselineClassifier& original) : Classifier(original) {
    this->setStrategy(original.getStrategy());
    this->setSeed(original.getSeed());
}

// Destructor
BaselineClassifier::~BaselineClassifier() {

}

void BaselineClassifier::setStrategy(string strategy) {
    this->strategy = strategy;
}

string BaselineClassifier::getStrategy() const {
    return this->strategy;
}

void BaselineClassifier::setSeed(unsigned seed) {
    this->seed = seed;
}

unsigned BaselineClassifier::getSeed() const {
    return this->seed;
}

bool* BaselineClassifier::classify(InstancePool trainingPool, InstancePool testPool) {
    unsigned Ntest = testPool.getNumberOfInstances();

    unsigned Ntrain = trainingPool.getNumberOfInstances();
    unsigned positive_counter = 0;
    unsigned negative_counter = 0;
    for (int i=0; i<Ntrain; i++) {
        bool label = trainingPool[i].getCategory();
        if (label)
            positive_counter++;
    }
    negative_counter = Ntrain - positive_counter;

    // cout << "strategy: " << this->getStrategy() << "\n";
    
    bool* predicted_labels = new bool[Ntest];

    if (this->getStrategy() == "most_frequent") {
        bool most_frequent;
        if (positive_counter >= negative_counter)
            most_frequent = true;
        for (int i=0; i<Ntest; i++) {        
            predicted_labels[i] = most_frequent;
        }
    } else if (this->getStrategy() == "random") {
        for (int i=0; i<Ntest; i++) {         
            unsigned random_number = rand_r(&this->seed) % 2;
            // cout << "random_number: " << random_number << "\n";
            if (random_number == 1)
                predicted_labels[i] = true;
            else
                predicted_labels[i] = false;
        }
    }

    this->setNtest(Ntest);
    // this->setPredictedLabels(predicted_labels);

    return predicted_labels;
}

BaselineClassifier& BaselineClassifier::operator=(const BaselineClassifier& right) {
    this->setStrategy(right.getStrategy());
    this->setSeed(right.getSeed());

    return *this;
}
