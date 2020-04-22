clear
mkdir -p bin
g++ src/helper_functions.cpp src/construct_dataset.cpp -o bin/construct_dataset.o
g++ src/instance.cpp src/instancepool.cpp src/classifier.cpp \
	src/knnclassifier.cpp src/nbclassifier.cpp src/baselineclassifier.cpp src/classifierevaluator.cpp \
	src/Main.cpp -o bin/Main.o 
