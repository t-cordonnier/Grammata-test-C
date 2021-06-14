typedef unsigned short char16;
typedef char16 *string16;
typedef int (*collator16) (char16 *, char16 *);
typedef void (*converter) (char8 *src, char16 *dest, int limit);


char16 majchar16(char16 ch);

void majstring16 (char16* string) {
	while (*string) { *string = majchar16(*string); string++; }
}


void trie_liste16 (collator16 coll, string16 liste16[], string8 liste8[]) {
	int i, j;

	for (i = 0; i < 10000; i++)
		for (j = i + 1; j < 10000; j++)
			if ((*coll) (liste16[i], liste16[j]) > 0) {
				string16 mem16 = liste16[i];
				liste16[i] = liste16[j];
				liste16[j] = mem16;
				
				string8 mem8 = liste8[i];
				liste8[i] = liste8[j];
				liste8[j] = mem8;
			}
}

string16* to_liste16 (string8 liste8[], converter conv) {
	int i; string16* res = (string16*) malloc (10000 * sizeof(string16));
	for (i = 0; i < 10000; i++) {
		res[i] = (string16) malloc (100 * sizeof (char16));
		(*conv) (liste8[i], res[i], 100);
	}
	return res;
}

void copy16 (char16 *dest, char16 *src);

double testUpper16 (string16 liste[]) {
	struct timespec begin, end; double diff;

	// ecrire_liste(); printf ("\n------------------------\n");
	clock_gettime(CLOCK_REALTIME, &begin);
	int i,j; char16 test[100]; for (j = 100; j > 0; j--) for (i = 0; i < 10000; i++) { copy16(test,liste[i]); majstring16 (test); }
	clock_gettime(CLOCK_REALTIME, &end);
	printf ("Durée testUpper16 : %0.9f\n", diff = difftimespec (&begin, &end));

	return diff;
}

double testCollate16 (string8 liste8[], string16 liste16[], collator16 coll) {
	struct timespec begin, end; double diff;

	// ecrire_liste(); printf ("\n------------------------\n");
	clock_gettime(CLOCK_REALTIME, &begin);
	trie_liste16(coll, liste16, liste8);
	clock_gettime(CLOCK_REALTIME, &end);
	ecrire_liste(liste8); printf ("\n------------------------\n");
	printf ("Durée testCollate16 : %0.9f\n", diff = difftimespec (&begin, &end));

	return diff;
}
