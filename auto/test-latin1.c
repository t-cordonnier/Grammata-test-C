/** S�lection des algorithmes **/
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
		case 0xe0 /* '�' */: case 0xe2 /* '�' */: return 'a';
		case 0xc0 /* '�' */: case 0xc2 /* '�' */: return 'A';
		case 0xe7 /* '�' */: return 'c';
		case 0xc7 /* '�' */: return 'C';
		case 0xe9 /* '�' */: case 0xe8 /* '�' */: case 0xeb /* '�' */: case 0xea /* '�' */: return 'e';
		case 0xc9 /* '�' */: case 0xc8 /* '�' */: case 0xca /* '�' */: case 0xcb /* '�' */: return 'E';
		case 0xee /* '�' */: case 0xef /* '�' */: return 'i';
		case 0xce /* '�' */: case 0xcf /* '�' */: return 'I';
		case 0xf4 /* '�' */: case 0xf6 /* '�' */: return 'o';
		case 0xd4 /* '�' */: case 0xd6 /* '�' */: return 'O';
		case 0xf9 /* '�' */: case 0xfb /* '�' */: case 0xfc /* '�' */: return 'u';
		case 0xd9 /* '�' */: case 0xdb /* '�' */: case 0xdc /* '�' */: return 'U';
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


