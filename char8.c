typedef unsigned char char8;
typedef char8 *string8;
typedef int (*collator8) (char8 *, char8 *);


char8 majchar8(char8 ch);

void majstring8 (char8* string) {
	while (*string) { *string = majchar8(*string); string++; }
}



void trie_liste8 (collator8 coll, string8 liste[]) {
	int i, j;

	for (i = 0; i < 10000; i++)
		for (j = i + 1; j < 10000; j++)
			if ((*coll) (liste[i], liste[j]) > 0) {
				string8 mem = liste[i];
				liste[i] = liste[j];
				liste[j] = mem;
			}
}

#include <stdio.h>

void ecrire_liste(string8 liste[]) {
	int i;

	for (i = 0; i < 10000; i++)
		printf ("%s", liste[i]);
}

#include <time.h>

double difftimespec(struct timespec *begin, struct timespec *end) {
	double res = end->tv_sec + end->tv_nsec / 1E9;
	res -= begin->tv_sec + begin->tv_nsec / 1E9;
	return res;
}

string8* charge (const char* entree) {
	FILE *f; int i,j; 
	string8* liste = (string8*) malloc(10000 * sizeof(string8));
	f = fopen (entree, "r");
	for (i = 0; i < 10000; i++) {
		liste[i] = (char8 *) malloc(100 * sizeof(char8));
		for (j = 0; j < 100; j++) liste[i][j] = 0;
		fgets (liste[i], 80, f);
		//printf ("lu : %s\n", liste[i]);
	}
	close (f); printf ("Lecture terminée.\n");
	return liste;
}

double testUpper8 (string8 liste[]) {
	struct timespec begin, end; double diff;

	// ecrire_liste(); printf ("\n------------------------\n");
	clock_gettime(CLOCK_REALTIME, &begin);
	int i,j; char8 test[100]; for (j = 10000; j > 0; j--) for (i = 0; i < 10000; i++) { strcpy(test,liste[i]); majstring8 (test); }
	clock_gettime(CLOCK_REALTIME, &end);
	printf ("Durée testUpper8 : %0.9f\n", diff = difftimespec (&begin, &end));

	return diff;
}

double testCollate8 (string8 liste[], collator8 coll) {
	struct timespec begin, end; double diff;

	// ecrire_liste(); printf ("\n------------------------\n");
	clock_gettime(CLOCK_REALTIME, &begin);
	trie_liste8(coll, liste);
	clock_gettime(CLOCK_REALTIME, &end);
	ecrire_liste(liste); printf ("\n------------------------\n");
	printf ("Durée testCollate8 : %0.9f\n", diff = difftimespec (&begin, &end));

	return diff;
}
