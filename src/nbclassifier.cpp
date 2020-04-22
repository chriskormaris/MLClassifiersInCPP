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


// See this: https://stackoverflow.com/questions/37405617/how-to-use-tf-idf-with-naive-bayes
bool* NaiveBayesClassifier::classify(InstancePool trainingPool, InstancePool testPool) {
    unsigned Ntest = testPool.getNumberOfInstances();

    unsigned Ntrain = trainingPool.getNumberOfInstances();

    // word_count_in_class:
    // sum of (tf-idf_weights of the word for all the documents belonging to that class) 
    // Basically replacing the counts with the tf-idf weights of the same word calculated for every document within that class.

    // total_words_in_class: 
    // sum of (tf-idf weights of all the words belonging to that class)

    float total_words_in_spam_class = 0;
    float total_words_in_ham_class = 0;

    for (int i=0; i<Ntrain; i++) {
        Instance inst = trainingPool[i];
        bool label = inst.getCategory();
        for (int j=0; j<inst.getNumberOfFeatures(); j++) {
            int id = inst.getFeatureID(j);
            float score = inst.getScore(j);
            if (label)
                total_words_in_spam_class += score;
            else
                total_words_in_ham_class += score;
        }
    }

    bool* predicted_labels = new bool[Ntest];
    for (int i=0; i<Ntest; i++) {
        
        float jth_word_count_in_spam_class = 0;
        float jth_word_count_in_ham_class = 0;
        int j = 0;
        while (j < testPool[i].getNumberOfFeatures()) {
            int id = testPool[i].getFeatureID(j);
            // cout << "j: " << j << ", id: " << id << "\n";

            for (int k=0; k<Ntrain; k++) {
                // cout << "k: " << k << "\n";
                int l = 0;
                int id2 = -1;
                while (l < testPool[k].getNumberOfFeatures() && id2 < id) {
                    id2 = trainingPool[k].getFeatureID(l);
                    // cout << "l: " << l << ", id2: " << id2 << "\n";
                    l++;
                }
                if (id == id2) {
                    // cout << "id == id2" << "\n";
                    // cout << "l: " << l << "\n";
                    if (trainingPool[k].getCategory()) {
                        jth_word_count_in_spam_class += trainingPool[k].getScore(l-1);
                    } else {
                        jth_word_count_in_ham_class += trainingPool[k].getScore(l-1);
                    }
                }
            }

            j++;
        }

        float p_jth_word_given_spam_class = jth_word_count_in_spam_class / total_words_in_spam_class;
        float p_jth_word_given_ham_class = jth_word_count_in_ham_class / total_words_in_ham_class;

        if (p_jth_word_given_spam_class >= p_jth_word_given_ham_class)
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
