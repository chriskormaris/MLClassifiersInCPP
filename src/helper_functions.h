#include <iostream>		/* printf, cin, cout */
#include <fstream>		/* ifstream, ofstream */
#include <sstream>		/* stringstream */
#include <string>
#include <vector>
#include <algorithm>    	/* find */
#include <string.h>		/* strtok, strlen */
#include <math.h>       	/* log */


using namespace std;


void construct_document_frequency(string documents[], unsigned documentsSize, string keywords[], unsigned keywordsSize, int df[]);

void get_tf_idf_scores(string category, string document_names[], string documents[], unsigned documentsSize, 
			string keywords[], unsigned keywordsSize, unsigned N, int df[], ofstream& fout);

vector<string> tokenize_document(string sdocument);
