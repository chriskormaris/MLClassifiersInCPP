#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */
// #include <algorithm>

#include "math.h"

#include "knnclassifier.h"
#include "instancepool.h"

using namespace std;


// Constructor
KNNClassifier::KNNClassifier() : Classifier() {

}

// Copy Constructor
KNNClassifier::KNNClassifier(const KNNClassifier& original) : Classifier(original) {
    this->setK(original.getK());
    this->setMetric(original.getMetric());
}

// Destructor
KNNClassifier::~KNNClassifier() {

}

void KNNClassifier::setK(unsigned k) {
    this->k = k;
}

unsigned KNNClassifier::getK() const {
    return this->k;
}

void KNNClassifier::setMetric(string metric) {
    this->metric = metric;
}

string KNNClassifier::getMetric() const {
    return this->metric;
}

bool* KNNClassifier::classify(InstancePool trainingPool, InstancePool testPool) {
    unsigned Ntrain = trainingPool.getNumberOfInstances();
    // cout << "Ntrain: " << Ntrain << "\n";
    unsigned Ntest = testPool.getNumberOfInstances();
    // cout << "k: " << this->getK() << "\n";

    bool* predicted_labels = new bool[Ntest];
    
    bool test_true_labels[Ntest];
    for (int i=0; i<Ntest; i++) {
        test_true_labels[i] = testPool[i].getCategory();
    }

    // Perform kNN with Euclidean distances.
    for (int i=0; i<Ntest; i++) {
        // cout << "i: " << i << ", filename: " << testPool[i].getFileName() << "\n";
        
        float distances[Ntrain];

        for (int j=0; j<Ntrain; j++) {
            // cout << "j: " << j << "\n";

            // find the euclidean distance between the two tfidf vectors
            if (this->getMetric() == "euclidean_distances") {
                distances[j] = get_euclidean_distance(testPool[i], trainingPool[j], testPool.getFeatures().size());
                // cout << "distances[" << j << "]: " << distances[j] << "\n";
            }

            // find the cosine similarities between the two tfidf vectors
            if (this->getMetric() == "cosine_similarity") {
                distances[j] = get_cosine_similarity(testPool[i], trainingPool[j], testPool.getFeatures().size());
                // cout << "distances[" << j << "]: " << distances[j] << "\n";
            }
        }

        bool* sorted_train_labels = new bool[Ntrain];
        for (int j=0; j<Ntrain; j++) {
            sorted_train_labels[j] = trainingPool[j].getCategory();
        }

        // Run bubblesort on 2 arrays simultaneously.
        // We have two cases:
        // 1) Sort in ascending order if using euclidean distances.
        // The smaller the euclidean distance, the better.
        // 2) Sort in descending order if using cosine similarity.
        // The bigger the cosine similarity, the better.
        for (int ii=0; ii<Ntrain; ii++) {
            for (int jj=1; jj<Ntrain-ii; jj++) {
                bool order;
                if (this->getMetric() == "euclidean_distances")
                    // sort in ascending order
                    order = distances[jj-1] > distances[jj];
                else if (this->getMetric() == "cosine_similarity")
                    // sort in descending order
                    order = distances[jj-1] < distances[jj];
                if (order) {
                    float temp1 = distances[jj-1];
                    distances[jj-1]  = distances[jj];
                    distances[jj] = temp1;

                    bool temp2 = sorted_train_labels[jj-1];
                    sorted_train_labels[jj-1]  = sorted_train_labels[jj];
                    sorted_train_labels[jj] = temp2;
                }
            }
        }

        // Get the category of the top 
        unsigned spam_votes = 0;
        unsigned ham_votes = 0;
        for (int j=0; j<this->getK(); j++) {
            // cout << "distances[" << j << "]: " << distances[j] 
            //    << ", sorted_train_labels[" << j << "]: " << sorted_train_labels[j] << "\n";
            if (sorted_train_labels[j])
                spam_votes += 1;
            else
                ham_votes += 1;
        }
        
        if (spam_votes > ham_votes) {
            predicted_labels[i] = true;
        } else if (spam_votes < ham_votes) {
            predicted_labels[i] = false;
        } else {
            predicted_labels[i] = sorted_train_labels[0];
        }

        cout << "i: " << i << ", filename: " << testPool[i].getFileName() 
            << ", predicted category: " << predicted_labels[i] << "\n";

    }

    cout << "\n";

    this->setNtest(Ntest);
    // this->setPredictedLabels(predicted_labels);

    return predicted_labels;
}


// Finds the euclidean distance between the two tfidf vectors.
// N is the total number of features.
float KNNClassifier::get_euclidean_distance(Instance inst1, Instance inst2, unsigned N) {
    float euclidean_distance = 0;
    float sum = 0;
    unsigned m = 0;
    unsigned r = 0;
    // cout << "N: " << N << "\n";
    for (int i=0; i<N; i++) {
        // cout << "i: " << i << ", m: " << m << ", r: " << r << "\n";
        unsigned id1 = inst1.getFeatureID(m);
        unsigned id2 = inst2.getFeatureID(r);
        // cout << "id1: " << id1 << ", id2: " << id2 << "\n";
        if (i == id1 && i == id2) {
            sum += pow(inst1.getScore(m) - inst2.getScore(r), 2);
            if (m < inst1.getNumberOfFeatures() - 1)
                m += 1;
            if (r < inst2.getNumberOfFeatures() - 1)
                r += 1;
        } else {
            if (i == id1)
                sum += pow(inst1.getScore(m) - 1, 2);
            else if (i == id2)
                sum += pow(1 - inst2.getScore(r), 2);
            else if (i != id1 && i != id2)
                sum += 1;

            if (id1 < i && id2 < i) {
                if (m < inst1.getNumberOfFeatures() - 1)
                    m += 1;
                if (r < inst2.getNumberOfFeatures() - 1)
                    r += 1;
            } else if (id1 < i) {
                if (m < inst1.getNumberOfFeatures() - 1)
                    m += 1;
            } else if (id2 < i) {
                if (r < inst2.getNumberOfFeatures() - 1)
                    r += 1;
            }

        }
        
        // cout << "i: " << i << ", m: " << m << ", r: " << r << "\n";
    }
    // cout << "sum: " << sum << "\n";
    euclidean_distance = sqrt(sum);
    return euclidean_distance;
}


// Finds the cosine similarity between the two tfidf vectors.
// N is the total number of features.
float KNNClassifier::get_cosine_similarity(Instance inst1, Instance inst2, unsigned N) {
    float cosine_similarity = 0;
    float sum = 0;
    float norm_inst1 = 0;
    float norm_inst2 = 0;
    unsigned m = 0;
    unsigned r = 0;
    // cout << "N: " << N << "\n";
    for (int i=0; i<N; i++) {
        // cout << "i: " << i << ", m: " << m << ", r: " << r << "\n";
        unsigned id1 = inst1.getFeatureID(m);
        unsigned id2 = inst2.getFeatureID(r);
        // cout << "id1: " << id1 << ", id2: " << id2 << "\n";
        if (i == id1 && i == id2) {
            sum += inst1.getScore(m) * inst2.getScore(r);
            if (m < inst1.getNumberOfFeatures() - 1)
                m += 1;
            if (r < inst2.getNumberOfFeatures() - 1)
                r += 1;
        } else {

            if (id1 < i && id2 < i) {
                if (m < inst1.getNumberOfFeatures() - 1)
                    m += 1;
                if (r < inst2.getNumberOfFeatures() - 1)
                    r += 1;
            } else if (id1 < i) {
                if (m < inst1.getNumberOfFeatures() - 1)
                    m += 1;
            } else if (id2 < i) {
                if (r < inst2.getNumberOfFeatures() - 1)
                    r += 1;
            }

        }

        // Calculate the euclidean norms (norm 2) of each vector.
        if (i == id1)
            norm_inst1 += pow(inst1.getScore(m), 2);
        if (i == id2)
            norm_inst2 += pow(inst2.getScore(r), 2);
        
        // cout << "i: " << i << ", m: " << m << ", r: " << r << "\n";
    }
    // cout << "sum: " << sum << "\n";
    norm_inst1 = sqrt(norm_inst1);
    norm_inst2 = sqrt(norm_inst2);
    cosine_similarity = sum / (norm_inst1 + norm_inst2);
    return cosine_similarity;
}


KNNClassifier& KNNClassifier::operator=(const KNNClassifier& right) {
    this->setK(right.getK());
    this->setMetric(right.getMetric());

    return *this;
}
