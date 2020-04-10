#include <iostream>			/* cout */
#include <fstream>			/* ifstream, ofstream */
// #include <sstream>		/* stringstream */
#include <string>
#include <vector>
// #include <stdio.h>		/* printf */
// #include <cstdio>		/* printf */#include <string>
#include <vector>
#include <iostream>			/* printf */
#include <sstream>			/* stringstream */
#include <stdlib.h>			/* cin, cout */
#include <algorithm>    	/* find */
#include <string.h>			/* strtok, strlen */
// #include <bits/stdc++.h>	/* cout, vector, strtok, strlen, find */
#include <math.h>       	/* log */

#include "helper_functions.h"

using namespace std;


int main (int argc, char* argv[]) {
	
	ifstream fin;

	// keywords.txt to string array
	fin.open("keywords-filenames/keywords.txt");
	unsigned keywordsSize = 0;
	string unused;
	while (getline(fin, unused))
	   ++keywordsSize;
	printf("keywords size: %d\n", keywordsSize);
	fin.clear();
	fin.seekg(0, ios::beg);

	string keywords[keywordsSize];

	unsigned i = 0;
	while (i < keywordsSize && getline(fin, keywords[i])){
		// cout << "keywords[" << i << "]: " << keywords[i] << "\n";
		++i;
	}
	fin.close();
	
	/******************************************************************/
	/* GET TRAINING DATA */
		
	// ling_filenames.txt to string array
	fin.open("keywords-filenames/ling_filenames.txt");
	unsigned lingSize = 0;
	while (getline(fin, unused)) {
	   	lingSize++;
	}
	printf("training ling files size: %d\n", lingSize);

	fin.clear();
	fin.seekg(0, ios::beg);

	string ling_filenames[lingSize];
	string ling_files[lingSize];

	i = 0;
	while (i < lingSize && getline(fin, ling_filenames[i])) {
		ifstream temp_fin(ling_filenames[i]);
		string content( (istreambuf_iterator<char>(temp_fin) ), (istreambuf_iterator<char>()    ) );
		ling_files[i] = content;
		temp_fin.close();

		++i;
	}
	fin.close();


	// spam_filenames.txt to string array
	fin.open("keywords-filenames/spam_filenames.txt");
	unsigned spamSize = 0;
	while (getline(fin, unused))
	   ++spamSize;
	printf("training spam files size: %d\n", spamSize);
	fin.clear();
	fin.seekg(0, ios::beg);

	string spam_filenames[spamSize];
	string spam_files[spamSize];

	i = 0;
	while (i < spamSize && getline(fin, spam_filenames[i])) {
		ifstream temp_fin(spam_filenames[i]);
		string content( (istreambuf_iterator<char>(temp_fin) ), (istreambuf_iterator<char>()    ) );
		spam_files[i] = content;
		temp_fin.close();

		++i;
	}
	fin.close();

	unsigned Ntrain = lingSize + spamSize;

	// Construct the document frequency of each keyword.
	int df[keywordsSize];
	for (i=0; i<keywordsSize; i++) {
		df[i] = 0;
	}
	
	cout << "\n";
	
	construct_document_frequency(ling_files, lingSize, keywords, keywordsSize, df);
	construct_document_frequency(spam_files, spamSize, keywords, keywordsSize, df);
	
	/*
	for (i=0; i<keywordsSize; i++) {
		cout << keywords[i] << ": " << df[i] << "\n";
	}
	*/
	
	ofstream fout("training_data.txt");

	fout << "< messagecollection messages = \"" << Ntrain << "\" >\n";

	cout << "Writing to file...";
	get_tf_idf_scores("spam", spam_filenames, spam_files, spamSize, keywords, keywordsSize, Ntrain, df, fout);
	get_tf_idf_scores("ham", ling_filenames, ling_files, lingSize, keywords, keywordsSize, Ntrain, df, fout);
	cout << "[DONE]\n";

	fout << "</ messagecollection >\n";
	
	fout.close();
	
	cout << "**********************\n";
	
	/******************************************************************/
	
	/* GET TEST DATA */
	
	// test_ling_filenames.txt to string array
	fin.open("keywords-filenames/test_ling_filenames.txt");
	unsigned testLingSize = 0;
	while (getline(fin, unused)) {
	   	testLingSize++;
	}
	printf("test ling files size: %d\n", testLingSize);

	fin.clear();
	fin.seekg(0, ios::beg);

	string test_ling_filenames[testLingSize];
	string test_ling_files[testLingSize];

	i = 0;
	while (i < testLingSize && getline(fin, test_ling_filenames[i])) {
		ifstream temp_fin(test_ling_filenames[i]);
		string content( (istreambuf_iterator<char>(temp_fin) ), (istreambuf_iterator<char>()    ) );
		test_ling_files[i] = content;
		temp_fin.close();

		++i;
	}
	fin.close();

	// test_spam_filenames.txt to string array
	fin.open("keywords-filenames/test_spam_filenames.txt");
	unsigned testSpamSize = 0;
	while (getline(fin, unused))
	   ++testSpamSize;
	printf("test spam files size: %d\n", testSpamSize);
	fin.clear();
	fin.seekg(0, ios::beg);

	string test_spam_filenames[testSpamSize];
	string test_spam_files[testSpamSize];

	i = 0;
	while (i < testSpamSize && getline(fin, test_spam_filenames[i])) {
		ifstream temp_fin(test_spam_filenames[i]);
		string content( (istreambuf_iterator<char>(temp_fin) ), (istreambuf_iterator<char>()    ) );
		test_spam_files[i] = content;
		temp_fin.close();

		++i;
	}
	fin.close();

	unsigned Ntest = testLingSize + testSpamSize;

	// Construct the document frequency of each keyword.
	df[keywordsSize];
	for (i=0; i<keywordsSize; i++) {
		df[i] = 0;
	}
	
	cout << "\n";
	
	construct_document_frequency(test_ling_files, testLingSize, keywords, keywordsSize, df);
	construct_document_frequency(test_spam_files, testSpamSize, keywords, keywordsSize, df);
	
	/*
	for (i=0; i<keywordsSize; i++) {
		cout << keywords[i] << ": " << df[i] << "\n";
	}
	*/
	
	fout.open("test_data.txt");

	fout << "< messagecollection messages = \"" << Ntest << "\" >\n";

	cout << "Writing to file...";
	get_tf_idf_scores("spam", test_spam_filenames, test_spam_files, testSpamSize, keywords, keywordsSize, Ntest, df, fout);
	get_tf_idf_scores("ham", test_ling_filenames, test_ling_files, testLingSize, keywords, keywordsSize, Ntest, df, fout);
	cout << "[DONE]\n";
	
	fout << "</ messagecollection >\n";
	
	fout.close();
	
	/******************************************************************/

	return 0;

}
