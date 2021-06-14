typedef unsigned int char32;
typedef char32 *string32;
typedef int (*collator32) (char32 *, char32 *);
typedef void (*converter) (char8 *src, char32 *dest, int limit);


char32 majchar32(char32 ch);

void majstring32 (char32* string) {
	while (*string) { *string = majchar32(*string); string++; }
}


void trie_liste32 (collator32 coll, string32 liste32[], string8 liste8[]) {
	int i, j;

	for (i = 0; i < 10000; i++)
		for (j = i + 1; j < 10000; j++)
			if ((*coll) (liste32[i], liste32[j]) > 0) {
				string32 mem32 = liste32[i];
				liste32[i] = liste32[j];
				liste32[j] = mem32;
				
				string8 mem8 = liste8[i];
				liste8[i] = liste8[j];
				liste8[j] = mem8;
			}
}

string32* to_liste32 (string8 liste8[], converter conv) {
	int i; string32* res = (string32*) malloc (10000 * sizeof(string32));
	for (i = 0; i < 10000; i++) {
		res[i] = (string32) malloc (100 * sizeof (char32));
		(*conv) (liste8[i], res[i], 100);
	}
	return res;
}

void copy32 (char32 *dest, char32 *src);

double testUpper32 (string32 liste[]) {
	struct timespec begin, end; double diff;

	// ecrire_liste(); printf ("\n------------------------\n");
	clock_gettime(CLOCK_REALTIME, &begin);
	int i,j; char32 *test = (char32*) malloc(sizeof(char32) * 100); 
	for (j = 10000; j > 0; j--) for (i = 0; i < 10000; i++) { copy32(test,liste[i]); majstring32 (test); }
	clock_gettime(CLOCK_REALTIME, &end);
	printf ("Durée testUpper32 : %0.9f\n", diff = difftimespec (&begin, &end));

	return diff;
}


double testCollate32 (string8 liste8[], string32 liste32[], collator32 coll) {
	struct timespec begin, end; double diff;

	// ecrire_liste(); printf ("\n------------------------\n");
	clock_gettime(CLOCK_REALTIME, &begin);
	trie_liste32(coll, liste32, liste8);
	clock_gettime(CLOCK_REALTIME, &end);
	ecrire_liste(liste8); printf ("\n------------------------\n");
	printf ("Durée : %0.9f\n", diff = difftimespec (&begin, &end));

	return diff;
}
