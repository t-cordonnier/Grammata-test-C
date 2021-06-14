#include "../char8.c"
#include "../char32.c"

/** S�lection des algorithmes **/
#define ELIMINE_PONCTUATIONS 1
#define COMPARATEUR fr_compare

char8 majchar8(char8 ch) { return ch; } /* non utilis� */


void latin1_to_utf32 (char8 *src, char32 *dest, int limit) {
	while (limit && *src) {
		*dest = *src;
		dest++; limit--;
	}
	*dest = 0;
}

char32 majchar32 (char32 ch) {
	if (ch >= 0x61 && ch <= 0x7A) return ch - 0x20;
	if (ch >= 0xE0 && ch <= 0xF6) return ch - 0x20;
	if (ch >= 0xF8 && ch <= 0xFE) return ch - 0x20;
	return ch;
}

char32 sans_accent (char32  ch) {
	switch (ch) {
		case 0xe0 /* '�' */: case 0xe2 /* '�' */: return 0x0061 /* 'a' */;
		case 0xc0 /* '�' */: case 0xc2 /* '�' */: return 0x0041 /* 'A' */;
		case 0xe7 /* '�' */: return 0x0063 /* 'c' */;
		case 0xc7 /* '�' */: return 0x0043 /* 'C' */;
		case 0xe9 /* '�' */: case 0xe8 /* '�' */: case 0xeb /* '�' */: case 0xea /* '�' */: return 0x0065 /* 'e' */;
		case 0xc9 /* '�' */: case 0xc8 /* '�' */: case 0xca /* '�' */: case 0xcb /* '�' */: return 0x0045 /* 'E' */;
		case 0xee /* '�' */: case 0xef /* '�' */: return 0x0069 /* 'i' */;
		case 0xce /* '�' */: case 0xcf /* '�' */: return 0x0049 /* 'I' */;
		case 0xf4 /* '�' */: case 0xf6 /* '�' */: return 0x006F /* 'o' */;
		case 0xd4 /* '�' */: case 0xd6 /* '�' */: return 0x004F /* 'O' */;
		case 0xf9 /* '�' */: case 0xfb /* '�' */: case 0xfc /* '�' */: return 0x0075 /* 'u' */;
		case 0xd9 /* '�' */: case 0xdb /* '�' */: case 0xdc /* '�' */: return 0x0055 /* 'U' */;
		default: return ch;
	}
}

int len32 (char32 *st) {
	int c = 0; while (*st) { c++; st++; } return c;
}

void copy32 (char32 *dest, char32 *src) {
	while (*src) { *dest = *src; dest++; src++; } 
}

int cmp32 (char32* ch1, char32* ch2) {
	while ((*ch1) && (*ch2)) {
		if (*ch1 > *ch2) return -1;
		else if (*ch1 < *ch2) return 1;
		ch1++; ch2++;
	}
	if (*ch1) return -1;
	if (*ch2) return +1;	
}

int fr_compare (char32 *st1, char32 *st2) {
	char32 maj1 [len32(st1) + 1], maj2 [len32(st2) + 1];
	int res;
	copy32(maj1,st1); majstring32 (maj1); copy32(maj2,st2); majstring32 (maj2);
	res = fr_compare1 (maj1, maj2); if (res != 0) return res;
	res = fr_compare2 (maj1, maj2); if (res != 0) return res;
	return cmp32 (st1, st2);
}

int fr_compare_sans_casse (char32 *st1, char32 *st2) {
	int res = fr_compare1 (st1, st2);
	if (res != 0) return res;
	return fr_compare2 (st1, st2);
	//return fr_compare1 (st1, st2) || fr_compare2 (st1, st2);
}

int fr_compare1 (char32 *st1, char32 *st2) {
	while (*st1) {
#ifdef ELIMINE_PONCTUATIONS
		while ((*st1) && (*st1 < 0x40)) st1++; // ignorer les ponctuations
		while ((*st2) && (*st2 < 0x40)) st2++; // ignorer les ponctuations 
#endif
		if (! *st2) return -1; if (! *st1) return +1;
		char32 ch1 = sans_accent(*st1), ch2 = sans_accent(*st2);
		if (ch1 > ch2) return -1;
		else if (ch1 < ch2) return +1;
		/* else */ st1++; st2++;
	}
	if (*st2 > 0) return 1; /* else */ return 0;
}

int fr_compare2 (char32 *st1, char32 *st2) {
	char32 *cp1 = st1 + len32(st1), *cp2 = st2 + len32 (st2);
	char32 ch1, ch2;
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
	string32* liste32 = to_liste32 (liste8, latin1_to_utf32);
	collator32 compare = COMPARATEUR; 

	// ecrire_liste(); printf ("\n------------------------\n");
	testUpper32(liste32);
	testCollate32(liste8, liste32, compare);

	for (i = 0; i < 10000; i++) { free (liste8[i]); free (liste32[i]); }
	free (liste8); free (liste32);

	exit (0);
}


