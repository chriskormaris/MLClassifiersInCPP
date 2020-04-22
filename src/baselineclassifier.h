#ifndef _BASELINECLASSIFIER_H_
#define _BASELINECLASSIFIER_H_

#include <iostream>			/* printf */
#include <string>
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */

#include "classifier.h"
#include "instancepool.h"

using namespace std;

class BaselineClassifier : public Classifier {
    
    private:
        string strategy = "most_frequent";
        // string strategy = "random";
        unsigned seed = 0;

    public:
        // Constructor
        BaselineClassifier();

        // Copy Constructor
        BaselineClassifier(const BaselineClassifier& original);

        // Destructor
        virtual ~BaselineClassifier();

        void setStrategy(string strategy);

        string getStrategy() const;

        void setSeed(unsigned seed);

        unsigned getSeed() const;
        
        virtual bool* classify(InstancePool trainingPool, InstancePool testPool);
        
        virtual BaselineClassifier& operator=(const BaselineClassifier& base);

};

#endif
