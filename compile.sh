mkdir -p bin

g++ src/helper_functions.cpp src/construct_data.cpp -o bin/construct_data.o
g++ src/instance.cpp src/instancepool.cpp src/classifier.cpp src/knnclassifier.cpp src/classifierevaluator.cpp src/Main.cpp -o bin/Main.o 
