#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

#include "knnclassifier.h"
#include "nbclassifier.h"
#include "baselineclassifier.h"
#include "instancepool.h"
#include "classifierevaluator.h"

using namespace std;


// Constructor
ClassifierEvaluator::ClassifierEvaluator() {

}


ClassifierEvaluator::ClassifierEvaluator(KNNClassifier kNN, InstancePool trainingPool, InstancePool testPool) {
    this->classifier = &kNN;
    // this->trainingPool = trainingPool;
    // this->testPool = testPool;

    bool* predicted_labels = kNN.classify(trainingPool, testPool);

    unsigned Ntest = testPool.getNumberOfInstances();
    bool test_true_labels[Ntest];
    for (int i=0; i<Ntest; i++) {
        test_true_labels[i] = testPool[i].getCategory();
    }
    calculateMetrics(predicted_labels, test_true_labels);
}

ClassifierEvaluator::ClassifierEvaluator(NaiveBayesClassifier nb, InstancePool trainingPool, InstancePool testPool) {
    this->classifier = &nb;
    // this->trainingPool = trainingPool;
    // this->testPool = testPool;
    
    bool* predicted_labels = nb.classify(trainingPool, testPool);

    unsigned Ntest = testPool.getNumberOfInstances();
    bool test_true_labels[Ntest];
    for (int i=0; i<Ntest; i++) {
        test_true_labels[i] = testPool[i].getCategory();
    }
    calculateMetrics(predicted_labels, test_true_labels);
}

ClassifierEvaluator::ClassifierEvaluator(BaselineClassifier base, InstancePool trainingPool, InstancePool testPool) {
    this->classifier = &base;
    // this->trainingPool = trainingPool;
    // this->testPool = testPool;
    
    bool* predicted_labels = base.classify(trainingPool, testPool);

    unsigned Ntest = testPool.getNumberOfInstances();
    bool test_true_labels[Ntest];
    for (int i=0; i<Ntest; i++) {
        test_true_labels[i] = testPool[i].getCategory();
    }
    calculateMetrics(predicted_labels, test_true_labels);
}


// Copy Constructor
ClassifierEvaluator::ClassifierEvaluator(const ClassifierEvaluator& original) {

}

// Destructor
ClassifierEvaluator::~ClassifierEvaluator() {

}

void ClassifierEvaluator::setAccuracy(float accuracy) {
    this->accuracy = accuracy;
}

void ClassifierEvaluator::setPrecision(float precision) {
    this->precision = precision;
}

void ClassifierEvaluator::setRecall(float recall) {
    this->recall = recall;
}

float ClassifierEvaluator::getAccuracy() const {
    return this->accuracy;
}

float ClassifierEvaluator::getPrecision() const {
    return this->precision;
}

float ClassifierEvaluator::getRecall() const {
    return this->recall;
}

void ClassifierEvaluator::calculateMetrics(bool* predicted_labels, bool* test_true_labels) {
    unsigned Ntest = this->classifier->getNtest();
    cout << "Ntest: " << Ntest << "\n";
    
    // Calculate accuracy and other metrics.
    unsigned wrong_counter = 0;
    
    unsigned true_positives = 0;
    unsigned false_positives = 0;
    unsigned true_negatives = 0;
    unsigned false_negatives = 0;

    for (int i=0; i<Ntest; i++) {
        if (predicted_labels[i] == test_true_labels[i] && test_true_labels[i]) {
            true_positives++;
        } else if (predicted_labels[i] != test_true_labels[i] && test_true_labels[i]) {
            false_positives++;
            wrong_counter++;
        } else if (predicted_labels[i] == test_true_labels[i] && !test_true_labels[i]) {
            true_negatives++;
        } else if (predicted_labels[i] != test_true_labels[i] && !test_true_labels[i]) {
            false_negatives++;
            wrong_counter++;
        }
    }

    cout << "wrong counter: " << wrong_counter << "\n";

    cout << "true positives: " << true_positives << "\n";
    cout << "false positives: " << false_positives << "\n";
    cout << "true negatives: " << true_negatives << "\n";
    cout << "false negatives: " << false_negatives << "\n";

    float accuracy = (float) (Ntest - wrong_counter) / (float) Ntest;
    this->setAccuracy(accuracy);
    // cout << "accuracy: " << accuracy << "\n";

    float precision = (float) true_positives / (float) (true_positives + false_positives);
    this->setPrecision(precision);
    // cout << "precision: " << precision << "\n";

    float recall = (float) true_positives / (float) (true_positives + false_negatives);
    this->setRecall(recall);
    // cout << "recall: " << recall << "\n";

    // float f1_score = (float) (2 * precision * recall) / (precision + recall);
    // cout << "f1-score: " << f1_score << "\n";

}
