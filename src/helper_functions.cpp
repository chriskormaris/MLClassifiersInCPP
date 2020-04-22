#include <iostream>		/* printf, cin, cout */
#include <fstream>		/* ifstream, ofstream */
#include <sstream>		/* stringstream */
#include <string>
#include <vector>
#include <algorithm>    	/* find */
#include <string.h>		/* strtok, strlen */
#include <math.h>       	/* log */

#include "helper_functions.h"

using namespace std;


void construct_document_frequency(string documents[], unsigned documentsSize, string keywords[], unsigned keywordsSize, int df[]) {
	
	for (int i=0; i<documentsSize; i++) {

		vector<string> tokens = tokenize_document(documents[i]);

		for (int j=0; j<keywordsSize; j++) {

			if (find(tokens.begin(), tokens.end(), keywords[j]) != tokens.end()) {
				df[j] += 1;
			}
			// cout << keywords[j] << ": " << df[j] << "\n";
			
			/*
			for (int k=0; k<tokens.size(); k++) {
				// cout << tokens[k] << "\n";
				// if (keywords[j] == tokens[k]) {
				if (keywords[j].compare(tokens[k])) {
					df[j] += 1;
					break;
				}
			}
			*/
		}

		// cout << "i: " << i << "\n";
	}

}


void get_tf_idf_scores(string category, string document_names[], string documents[], unsigned documentsSize, 
	string keywords[], unsigned keywordsSize, unsigned N, int df[], ofstream& fout) { 
    
	for (int i=0; i<documentsSize; i++) {
		vector<string> tokens = tokenize_document(documents[i]);

		// Calculate tfidf scores.
		float k[keywordsSize];
		float tfidf[keywordsSize];
		int m = 0;
		for (int j=0; j<keywordsSize; j++) {
			float k = 0;
			for (int l=0; l<tokens.size(); l++) {
				// cout << tokens[l] << "\n";
				// if (keywords[j] == tokens[l]) {
				if (keywords[j].compare(tokens[l]) == 0) {
					k += 1;
				}
			}
			// cout << "k: " << k << "\n";
			float tf = k / tokens.size();
			float idf = (log(1 + N) - log(1 + df[j]));
			tfidf[j] = tf * idf;
			// cout << "j: " << j  << ", " << keywords[j] << ", tf: " << tf 
			// 	<< ", idf: " << idf << ", tfidf: " << tfidf[j] << "\n";
			if (tf > 0) {
				m += 1;
				// cout << "m: " << m  << ", j: " << j  << ", " << keywords[j] << ": " << tfidf[j] << "\n";
			}
		}
		// cout << "m: " << m  << "\n";
		
		fout << "< message file = \"" << document_names[i] << "\" category = \"" << category << "\" features = \"" << m << "\" >\n";
		for (int j=0; j<keywordsSize; j++) {
			if (tfidf[j] > 0)
				fout << "< feature token = \"" << keywords[j] << "\" id = \"" << j << "\" tfidf = \"" << tfidf[j] << "\" />\n";
		}
		fout << "</ message >\n";
		
	}

}


vector<string> tokenize_document(string sdocument) {
	
	vector<string> tokens;

	const char delimiters[] = " ,;:\"\'\t\n";

	char document[sdocument.size() + 1];
	sdocument.copy(document, sdocument.size() + 1);
	document[sdocument.size()] = '\0';

	char* token = strtok(document, delimiters);
	while (token != NULL) {
		// convert token to lowercase			
		for(int j=0; j<strlen(token); j++)
			token[j] = tolower(token[j]);
		
		// cout << "token: " << token << "\n";
		tokens.push_back(token);
		token = strtok(NULL, delimiters);
	}

	/*
	// A 2nd implementation for the tokenization.
	// stringstream class ss
	stringstream ss(sdocument); 
	
	string intermediate;
	
	// Tokenizing w.r.t. space ' ' 
	while (getline(ss, intermediate, ' ')) { 
		// convert token to lowercase
		transform(intermediate.begin(), intermediate.end(), intermediate.begin(), [](unsigned char c){ return tolower(c); });
		// cout << token << "\n";
		tokens.push_back(intermediate);
	}
	*/

	return tokens;
}
