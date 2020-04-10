#ifndef _CLASSIFIER_H_
#define _CLASSIFIER_H_

#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

#include "instancepool.h"

using namespace std;

class Classifier {

    private:
        unsigned Ntest;
        // bool* predicted_labels;

    public:
        // Constructor
        Classifier();

        // Copy Constructor
        Classifier(const Classifier& original);

        // Destructor
        virtual ~Classifier();

        void setNtest(unsigned Ntest);

        unsigned getNtest() const;
        
        // void setPredictedLabels(bool* predicted_labels);

        // bool* getPredictedLabels() const;

        virtual bool* classify(InstancePool trainingPool, InstancePool testPool);

        virtual Classifier& operator=(const Classifier& clf);
        
};

#endif
