#include "char8.c"

#if (MODE == 8)

#define CHARn char8
#define LENGTHn(string) strlen(string)
#define STRCOPY(dest,src) strcpy(dest,src)
#define MAJSTRING(string) majstring8(string)
#define COMPARE(string1,string2) strcmp(string1,string2)

#elif (MODE == 16)

#include "char16.c"

#define CHARn char16
#define LENGTHn(string) len16(string)
#define STRCOPY(dest,src) copy16(dest,src)
#define MAJSTRING(string) majstring16(string)
#define COMPARE(string1,string2) cmp16(string1,string2)

#elif (MODE == 32)

#include "char32.c"

#define CHARn char32
#define LENGTHn(string) len32(string)
#define STRCOPY(dest,src) copy32(dest,src)
#define MAJSTRING(string) majstring32(string)
#define COMPARE(string1,string2) cmp32(string1,string2)

#endif

	//return fr_compare1 (MAJSTRING(st1), MAJSTRING(st2)) || fr_compare2 (MAJSTRING(st1), MAJSTRING(st2)) || strcmp(st1, st2);
int fr_compare (CHARn *st1, CHARn *st2) {
	CHARn maj1 [LENGTHn(st1) + 1], maj2 [LENGTHn(st2) + 1];
	int res;
	STRCOPY(maj1,st1); MAJSTRING (maj1); STRCOPY(maj2,st2); MAJSTRING (maj2);
	res = fr_compare1 (maj1, maj2); if (res != 0) return res;
	res = fr_compare2 (maj1, maj2); if (res != 0) return res;
	return COMPARE (st1, st2);
}

	//return fr_compare1 (st1, st2) || fr_compare2 (st1, st2) || strcmp(st1, st2);
int fr_compare_sans_casse (CHARn *st1, CHARn *st2) {
	int res;
	res = fr_compare1 (st1, st2); if (res != 0) return res;
	res = fr_compare2 (st1, st2); if (res != 0) return res;
	return COMPARE (st1, st2);
}

#ifdef PROTO_sans_accents
PROTO_sans_accents;
#endif

int fr_compare1 (CHARn *st1, CHARn *st2) {
	while (*st1) {
#ifdef ELIMINE_PONCTUATIONS
		ELIMINE_PONCTUATIONS(st1);
		ELIMINE_PONCTUATIONS(st2);
#endif
		if (! *st2) return -1; if (! *st1) return +1;
		CHARn ch1 = SANS_ACCENTS(*st1), ch2 = SANS_ACCENTS(*st2);
		if (ch1 > ch2) return -1;
		if (ch1 < ch2) return +1;
		st1++; st2++;
	}
	if (*st2 > 0) return 1; /* else */ return 0;
}

#define END(st) st + LENGTHn(st)

int fr_compare2 (CHARn *st1, CHARn *st2) {
	CHARn *cp1 = END(st1), *cp2 = END(st2);
	CHARn ch1, ch2;
	while (cp1 >= st1) {
		if (*cp1 > *cp2) return 1;
		if (*cp1 < *cp2) return -1;
		cp1 --; cp2 --;
	}
	return 0;
}



