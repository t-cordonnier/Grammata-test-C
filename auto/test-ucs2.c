#include "../char8.c"
#include "../char16.c"

/** Sélection des algorithmes **/
#define ELIMINE_PONCTUATIONS 1
#define COMPARATEUR fr_compare_sans_casse

char8 majchar8(char8 ch) { return ch; } /* non utilisé */


void latin1_to_utf16 (char8 *src, char16 *dest, int limit) {
	while (limit && *src) {
		*dest = *src;
		dest++; limit--;
	}
	*dest = 0;
}

char16 majchar16 (char16 ch) {
	if (ch >= 0x61 && ch <= 0x7A) return ch - 0x20;
	if (ch >= 0xE0 && ch <= 0xF6) return ch - 0x20;
	if (ch >= 0xF8 && ch <= 0xFE) return ch - 0x20;
	return ch;
}

char16 sans_accent (char16  ch) {
	if (ch < 0x80) return ch;
	switch (ch) {
		case 0xe0 /* 'à' */: case 0xe2 /* 'â' */: return 0x0061 /* 'a' */;
		case 0xc0 /* 'À' */: case 0xc2 /* 'Â' */: return 0x0041 /* 'A' */;
		case 0xe7 /* 'ç' */: return 0x0063 /* 'c' */;
		case 0xc7 /* 'Ç' */: return 0x0043 /* 'C' */;
		case 0xe9 /* 'é' */: case 0xe8 /* 'è' */: case 0xeb /* 'ë' */: case 0xea /* 'ê' */: return 0x0065 /* 'e' */;
		case 0xc9 /* 'É' */: case 0xc8 /* 'È' */: case 0xca /* 'Ê' */: case 0xcb /* 'Ë' */: return 0x0045 /* 'E' */;
		case 0xee /* 'î' */: case 0xef /* 'ï' */: return 0x0069 /* 'i' */;
		case 0xce /* 'Î' */: case 0xcf /* 'Ï' */: return 0x0049 /* 'I' */;
		case 0xf4 /* 'ô' */: case 0xf6 /* 'ö' */: return 0x006F /* 'o' */;
		case 0xd4 /* 'Ô' */: case 0xd6 /* 'Ö' */: return 0x004F /* 'O' */;
		case 0xf9 /* 'ù' */: case 0xfb /* 'û' */: case 0xfc /* 'ü' */: return 0x0075 /* 'u' */;
		case 0xd9 /* 'Ù' */: case 0xdb /* 'Û' */: case 0xdc /* 'Ü' */: return 0x0055 /* 'U' */;
		default: return ch;
	}
}

int len16 (char16 *st) {
	int c = 0; while (*st) { c++; st++; } return c;
}

void copy16 (char16 *dest, char16 *src) {
	while (*src) { *dest = *src; dest++; src++; } 
}

int cmp16 (char16* ch1, char16* ch2) {
	while ((*ch1) && (*ch2)) {
		if (*ch1 > *ch2) return -1;
		else if (*ch1 < *ch2) return 1;
		ch1++; ch2++;
	}
	if (*ch1) return -1;
	if (*ch2) return +1;	
}

int fr_compare (char16 *st1, char16 *st2) {
	char16 maj1 [len16(st1) + 1], maj2 [len16(st2) + 1];
	int res;
	copy16(maj1,st1); majstring16 (maj1); copy16(maj2,st2); majstring16 (maj2);
	res = fr_compare1 (maj1, maj2); if (res != 0) return res;
	res = fr_compare2 (maj1, maj2); if (res != 0) return res;
	return cmp16 (st1, st2);
}

int fr_compare_sans_casse (char16 *st1, char16 *st2) {
	int res = fr_compare1 (st1, st2);
	if (res != 0) return res;
	return fr_compare2 (st1, st2);
	//return fr_compare1 (st1, st2) || fr_compare2 (st1, st2);
}

int fr_compare1 (char16 *st1, char16 *st2) {
	while (*st1) {
#ifdef ELIMINE_PONCTUATIONS
		while ((*st1) && (*st1 < 0x40)) st1++; // ignorer les ponctuations
		while ((*st2) && (*st2 < 0x40)) st2++; // ignorer les ponctuations 
#endif
		if (! *st2) return -1; if (! *st1) return +1;
		char16 ch1 = sans_accent(*st1), ch2 = sans_accent(*st2);
		if (ch1 > ch2) return -1;
		else if (ch1 < ch2) return +1;
		/* else */ st1++; st2++;
	}
	if (*st2 > 0) return 1; /* else */ return 0;
}

int fr_compare2 (char16 *st1, char16 *st2) {
	char16 *cp1 = st1 + len16(st1), *cp2 = st2 + len16 (st2);
	char16 ch1, ch2;
	while (cp1 >= st1) {
		ch1 = *cp1; ch2 = *cp2;
		if (ch1 > 0x80) {
			if (ch2 > 0x80) return -1;
			else if (ch2 < ch1) return -1;
			else if (ch2 > ch1) return 1;
		}
		else if (ch2 > 0x80) return 1;
		cp1--; cp2--;
	}
	return 0;
}


int main (int argc, char **argv) {
	int i;
	string8* liste8 = charge("../data/fr.la3.txt");
	string16* liste16 = to_liste16 (liste8, latin1_to_utf16);
	collator16 compare = COMPARATEUR; 

	// ecrire_liste(); printf ("\n------------------------\n");
	testUpper16(liste16);
	testCollate16(liste8, liste16, compare);

	for (i = 0; i < 10000; i++) { free (liste8[i]); free (liste16[i]); }
	free (liste8); free (liste16);

	exit (0);
}


