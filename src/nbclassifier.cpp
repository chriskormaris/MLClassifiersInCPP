#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

#include "nbclassifier.h"
#include "instancepool.h"

using namespace std;


// Constructor
NaiveBayesClassifier::NaiveBayesClassifier() : Classifier() {

}

// Copy Constructor
NaiveBayesClassifier::NaiveBayesClassifier(const NaiveBayesClassifier& original) : Classifier(original) {
    
}

// Destructor
NaiveBayesClassifier::~NaiveBayesClassifier() {

}


// This is an implementation for the Naive Bayes classifier with tf-idf features,
// that is not scientifically proven to be correct. It is something that seemed to do the trick.
bool* NaiveBayesClassifier::classify(InstancePool trainingPool, InstancePool testPool) {
    unsigned Ntest = testPool.getNumberOfInstances();

    unsigned Ntrain = trainingPool.getNumberOfInstances();
    
    // sum_of_all_test_vector_scores_in_class:
    // sum of (tf-idf weights of the test feature vector for all the train documents having these tokens, belonging to that class) 

    // sum_of_all_train_scores_in_class: 
    // sum of (tf-idf weights of all the tokens belonging to that class, for the train documents)

    float sum_of_all_train_scores_in_spam_class = 0;
    float sum_of_all_train_scores_in_ham_class = 0;
    
    for (int i=0; i<Ntrain; i++) {
        Instance inst = trainingPool[i];
        bool label = inst.getCategory();
        for (int j=0; j<inst.getNumberOfFeatures(); j++) {
            int id = inst.getFeatureID(j);
            float score = inst.getScore(j);
            if (label)
                sum_of_all_train_scores_in_spam_class += score;
            else
                sum_of_all_train_scores_in_ham_class += score;
        }
    }

    bool* predicted_labels = new bool[Ntest];
    for (int i=0; i<Ntest; i++) {
        
        float sum_of_all_test_vector_scores_in_spam_class = 0;
        float sum_of_all_test_vector_scores_in_ham_class = 0;
        int j = 0;
        while (j < testPool[i].getNumberOfFeatures()) {
            int id = testPool[i].getFeatureID(j);
            float score = testPool[i].getScore(j);
            // cout << "j: " << j << ", id: " << id << "\n";

            for (int k=0; k<Ntrain; k++) {
                // cout << "k: " << k << "\n";
                int l = 0;
                int id2 = -1;
                while (l < trainingPool[k].getNumberOfFeatures() && id2 < id) {
                    id2 = trainingPool[k].getFeatureID(l);
                    // cout << "l: " << l << ", id2: " << id2 << "\n";
                    l++;
                }
                if (id == id2) {
                    // cout << "id == id2" << "\n";
                    // cout << "l: " << l << "\n";
                    if (trainingPool[k].getCategory()) {
                        sum_of_all_test_vector_scores_in_spam_class += score;
                    } else {
                        sum_of_all_test_vector_scores_in_ham_class += score;
                    }
                }
            }

            j++;
        }

        float prob_feature_vector_given_spam_class = sum_of_all_test_vector_scores_in_spam_class / sum_of_all_train_scores_in_spam_class;
        float prob_feature_vector_given_ham_class = sum_of_all_test_vector_scores_in_ham_class / sum_of_all_train_scores_in_ham_class;

        if (prob_feature_vector_given_spam_class >= prob_feature_vector_given_ham_class)
            predicted_labels[i] = true;
        else
            predicted_labels[i] = false;

        cout << "Naive-Bayes, i: " << i << ", filename: " << testPool[i].getFileName() 
            << ", predicted category: " << predicted_labels[i] << "\n";
    }
    
    cout << "\n";

    this->setNtest(Ntest);
    // this->setPredictedLabels(predicted_labels);

    return predicted_labels;
}

NaiveBayesClassifier& NaiveBayesClassifier::operator=(const NaiveBayesClassifier& right) {
    return *this;
}
