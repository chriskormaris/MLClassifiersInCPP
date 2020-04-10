#ifndef _CLASSIFIEREVALUATOR_H_
#define _CLASSIFIEREVALUATOR_H_

#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

#include "classifier.h"
#include "knnclassifier.h"
#include "instancepool.h"

using namespace std;

class ClassifierEvaluator {
    
    private:
        float accuracy = 0;
        float precision = 0;
        float recall = 0;

        Classifier *classifier;
        // InstancePool trainingPool;
        // InstancePool testPool;

    public:
        // Constructor
        ClassifierEvaluator();

        ClassifierEvaluator(KNNClassifier kNN, InstancePool trainingPool, InstancePool testPool);
		
        // Copy Constructor
        ClassifierEvaluator(const ClassifierEvaluator& original);

        // Destructor
        ~ClassifierEvaluator();

        void setAccuracy(float accuracy);

        void setPrecision(float precision);

        void setRecall(float recall);

        float getAccuracy() const;

        float getPrecision() const;

        float getRecall() const;

        void calculateMetrics(bool* predicted_labels, bool* test_true_labels);

};

#endif
