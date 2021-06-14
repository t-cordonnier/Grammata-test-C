/** Sélection des algorithmes **/
#define ELIMINE_PONCTUATIONS(st)	while ((*st) && ((*st & 0xC0) != 0x40)) st++; // ignorer les accents et ponctuations : (*st1 < 0x40) || (*st1 > 0x80)
#define COMPARATEUR fr_compare

#define SANS_ACCENTS(ch) ch


#define MODE 8
#include "../fr-compare.c"


char8 majchar8(char8 ch) {
	if (ch & 0xE0 == 0x60) return ch & 0xDF;
	return ch;
}

int main (int argc, char **argv) {
	int i;
	string8* liste = charge("../data/fr.gta8.txt");
	collator8 compare = COMPARATEUR; 
	
	testCollate8 (liste, compare);
	testUpper8 (liste);

	for (i = 0; i < 10000; i++) free (liste[i]);
	free (liste);

	exit (0);
}


