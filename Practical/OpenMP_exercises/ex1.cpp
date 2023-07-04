#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <time.h>
#include <cstdlib>

using namespace std;

#define SYSTEMTIME clock_t


void constructMatrixes(int m_ar, int m_br, double *pha, double *phb) {
    for(int i = 0; i < m_ar; i++)
		for(int j = 0; j < m_ar; j++)
			pha[i*m_ar + j] = (double)1.0;

	for(int i = 0; i < m_br; i++)
		for(int j = 0; j < m_br; j++)
			phb[i * m_br + j] = (double)(i + 1);
}

void displayMatrixResult(int m_ar, int m_br, double *phc) {
    int num_elems = min(10, m_ar * m_br), curr_elem = 0, line = 0, col = 0;
	cout << "\nResult matrix (phc): " << endl;
	while (curr_elem < num_elems) {
		if (col == m_ar) {
			col = 0;
			line++;
			cout << endl;
		}
		cout << phc[line * m_br + col] << " ";
		col++;
		curr_elem++;
	} 
	cout << endl << endl;
}

void OnMult(int m_ar, int m_br)  {

	SYSTEMTIME Time1, Time2;

	char st[100];
	double temp;
	int i, j, k;

	double *pha, *phb, *phc;



    pha = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phb = (double *)malloc((m_ar * m_ar) * sizeof(double));
	phc = (double *)malloc((m_ar * m_ar) * sizeof(double));

	constructMatrixes(m_ar, m_br, pha, phb);

    Time1 = clock();

	// Loops  through the result matrix phc
	for(i=0; i<m_ar; i++) {
		for( j=0; j<m_br; j++) {
			// Element (i, j) of phc -> calcules of 2 lines of the matrix
			temp = 0;
			for( k=0; k<m_ar; k++) {
				temp += pha[i*m_ar+k] * phb[k*m_br+j];
			}
			phc[i*m_ar+j]=temp;
		}
	}

    Time2 = clock();
	sprintf(st, "Time: %3.3f seconds\n", (double)(Time2 - Time1) / CLOCKS_PER_SEC);
	cout << st;

	displayMatrixResult(m_ar, m_br, phc);

    free(pha);
    free(phb);
    free(phc);

}


int main (int argc, char *argv[]) {
	int lin, col;

	int validDimension = false;
	printf("Dimensions: lins=cols ? ");
	while (!validDimension) {
		cin >> lin;
		if (lin >= 0) {
			validDimension = true;
			col = lin;
		} else {
			cout << "Invalid dimension! Please try again (dimension >= 0): ";
		}
	}

	OnMult(lin, lin);

}