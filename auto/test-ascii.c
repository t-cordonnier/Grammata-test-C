#include <ctype.h>
#include <stdio.h>
#include "../char8.c"


char8 majchar8(char8 ch) {
	if (ch >= 0x61 && ch <= 0x7A) return ch - 0x20;
	return ch;
}

void trie_liste (string8 liste[]) {
	int i, j;

}


int main (int argc, char **argv) {
	int i, j;
	string8* liste = charge("../data/fr.la3.txt");
	
	/* testCollate8 (liste, &compare); */
	{
		struct timespec begin, end; double diff;

		clock_gettime(CLOCK_REALTIME, &begin);
		/* trie_liste(liste); */
		for (i = 0; i < 10000; i++)
			for (j = i + 1; j < 10000; j++)
				if (strcmp (liste[i], liste[j]) > 0) {
					string8 mem = liste[i];
					liste[i] = liste[j];
					liste[j] = mem;
				}
		
		clock_gettime(CLOCK_REALTIME, &end);
		ecrire_liste(liste); printf ("\n------------------------\n");
		printf ("Durée testCollate : %0.9f\n", diff = difftimespec (&begin, &end));
	}
	/* testCollate8 (liste, &compare); */
	{
		struct timespec begin, end; double diff;

		clock_gettime(CLOCK_REALTIME, &begin);
		/* trie_liste(liste); */
		for (i = 0; i < 10000; i++)
			for (j = i + 1; j < 10000; j++)
				if (strcasecmp  (liste[i], liste[j]) > 0) {
					string8 mem = liste[i];
					liste[i] = liste[j];
					liste[j] = mem;
				}
		
		clock_gettime(CLOCK_REALTIME, &end);
		ecrire_liste(liste); printf ("\n------------------------\n");
		printf ("Durée testCollate - nocase : %0.9f\n", diff = difftimespec (&begin, &end));
	}
	/* testUpper8 (liste); */
	{
		struct timespec begin, end; double diff; char8 test[100]; char8 *ptr;

		clock_gettime(CLOCK_REALTIME, &begin);
		/* trie_liste(liste); */
		for (i = 0; i < 10000; i++)
			for (j = 10000; j > 0; j--) {
				strcpy(test,liste[i]); ptr = test; 
				while (*ptr) { *ptr = toupper(*ptr); ptr++; }
			}
		
		clock_gettime(CLOCK_REALTIME, &end);
		printf ("Durée testUpper : %0.9f\n", diff = difftimespec (&begin, &end));
	}
	
	for (i = 0; i < 10000; i++) free (liste[i]);
	free (liste);


	exit (0);
}


