#include "../char8.c"
#include "../char32.c"

/** Sélection des algorithmes **/
#define ELIMINE_PONCTUATIONS 1
#define COMPARATEUR fr_compare

char8 majchar8(char8 ch) { return ch; } /* non utilisé */

void grammata_8_to_32 (char8 *src, char32 *dest, int limit) {
	while (limit && *src) {
		*dest = 0x201AE000; /* 100D7 << 13 */
		*dest += *src << 6;
		src++;
		if (*src > 0x80) {
			*dest += (*src & 0x7F);
			src++;
		}
		dest++; limit--;
	}
	*dest = 0;
}

char32 majchar32 (char32 ch) {
	/* gta8: if (ch & 0xE0 == 0x60) return ch & 0xDF; */
	if ((ch & 0x3800) == 0x1800) return ch & 0xFFFFF7FF;
	return ch;
}

int len32 (char32 *st) {
	int c = 0; while (*st & 0x1FFF) { c++; st++; } return c;
}

void copy32 (char32 *dest, char32 *src) {
	while (*src & 0x1FFF) { *dest = *src; dest++; src++; } 
}

int cmp32 (char32* ch1, char32* ch2) {
	while ((*ch1 & 0x1FFF) && (*ch2 & 0x1FFF)) {
		if (*ch1 > *ch2) return -1;
		else if (*ch1 < *ch2) return 1;
		ch1++; ch2++;
	}
	if (*ch1 & 0x1FFF) return -1;
	if (*ch2 & 0x1FFF) return +1;	
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
		while ((*st1) && ((*st1 & 0x3000) != 0x1000)) st1++; // ignorer les accents et ponctuations : (*st1 < 0x40) || (*st1 > 0x80)
		while ((*st2) && ((*st2 & 0x3000) != 0x1000)) st2++; // ignorer les accents et ponctuations : (*st2 < 0x40) || (*st2 > 0x80)
#endif
		if (! *st2) return -1; if (! *st1) return +1;
		char32 ch1 = *st1 & 0x1FC0, ch2 = *st2 & 0x1FC0;  // 0x7F << 6;
		if (ch1 < ch2) return -1;
		if (ch1 > ch2) return 1;
		st1++; st2++;
	}
	if (*st2) return 1; /* else */ return 0;
}

int fr_compare2 (char32 *st1, char32 *st2) {
	char32 *cp1 = st1, *cp2 = st2;
	while (*cp1) cp1++; while (*cp2) cp2++;
	while (cp1 >= st1) {
		if (*cp1 > *cp2) return 1;
		if (*cp1 < *cp2) return -1;
		cp1 --; cp2 --;
	}
	return 0;
}


int main (int argc, char **argv) {
	int i;
	string8* liste8 = charge("../data/fr.gta8.txt");
	string32* liste32 = to_liste32 (liste8, grammata_8_to_32);
	collator32 compare = COMPARATEUR; 

	// ecrire_liste(); printf ("\n------------------------\n");
	testCollate32(liste8, liste32, compare);
	testUpper32(liste32);

	for (i = 0; i < 10000; i++) { free (liste8[i]); free (liste32[i]); }
	free (liste8); free (liste32);

	exit (0);
}


