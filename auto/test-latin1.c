/** Sélection des algorithmes **/
#define ELIMINE_PONCTUATIONS(st) 	while ((*st) && !(*st & 0xC0)) st++; // ignorer les ponctuations : (*st < 0x40)
#define COMPARATEUR fr_compare
#define PROTO_sans_accents char8 sans_accents (char8 ch)
#define SANS_ACCENTS(ch) sans_accents(ch)

#define MODE 8
#include "../fr-compare.c"


char8 majchar8(char8 ch) {
	if (ch >= 0x61 && ch <= 0x7A) return ch - 0x20;
	if (ch >= 0xE0 && ch <= 0xF6) return ch - 0x20;
	if (ch >= 0xF8 && ch <= 0xFE) return ch - 0x20;
	return ch;
}

char8 sans_accents (char8 ch) {
	switch (ch) {
		case 0xe0 /* 'à' */: case 0xe2 /* 'â' */: return 'a';
		case 0xc0 /* 'À' */: case 0xc2 /* 'Â' */: return 'A';
		case 0xe7 /* 'ç' */: return 'c';
		case 0xc7 /* 'Ç' */: return 'C';
		case 0xe9 /* 'é' */: case 0xe8 /* 'è' */: case 0xeb /* 'ë' */: case 0xea /* 'ê' */: return 'e';
		case 0xc9 /* 'É' */: case 0xc8 /* 'È' */: case 0xca /* 'Ê' */: case 0xcb /* 'Ë' */: return 'E';
		case 0xee /* 'î' */: case 0xef /* 'ï' */: return 'i';
		case 0xce /* 'Î' */: case 0xcf /* 'Ï' */: return 'I';
		case 0xf4 /* 'ô' */: case 0xf6 /* 'ö' */: return 'o';
		case 0xd4 /* 'Ô' */: case 0xd6 /* 'Ö' */: return 'O';
		case 0xf9 /* 'ù' */: case 0xfb /* 'û' */: case 0xfc /* 'ü' */: return 'u';
		case 0xd9 /* 'Ù' */: case 0xdb /* 'Û' */: case 0xdc /* 'Ü' */: return 'U';
		default: return ch;
	}
}

int main (int argc, char **argv) {
	int i;
	string8* liste = charge("../data/fr.la3.txt");
	collator8 compare = COMPARATEUR; 
	
	testCollate8 (liste, compare);
	testUpper8 (liste);
	
	for (i = 0; i < 10000; i++) free (liste[i]);
	free (liste);

	exit (0);
}


