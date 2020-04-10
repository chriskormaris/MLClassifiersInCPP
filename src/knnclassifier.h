#ifndef _KNNCLASSIFIER_H_
#define _KNNCLASSIFIER_H_

#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

#include "classifier.h"
#include "instancepool.h"

using namespace std;

class KNNClassifier : public Classifier {

    private:
        unsigned k = 1;
        string metric = "euclidean";
    
    public:
        // Constructor
        KNNClassifier();

        // Copy Constructor
        KNNClassifier(const KNNClassifier& original);

        // Destructor
        virtual ~KNNClassifier();

        void setK(unsigned k);

        unsigned getK() const;

        void setMetric(string metric);

        string getMetric() const;

        virtual bool* classify(InstancePool trainingPool, InstancePool testPool);

        float get_euclidean_distance(Instance inst1, Instance inst2, unsigned N);

        float get_cosine_similarity(Instance inst1, Instance inst2, unsigned N);
        
        virtual KNNClassifier& operator=(const KNNClassifier& right);

};

#endif
