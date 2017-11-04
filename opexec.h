/* Copyright 1994 H.Ogasawara (COR.) */

#define	l1B	1
#define	l2B	2
#define	l3B	3
#define	l4B	4
#define lnB	0xff

#define	tLD	0
#define	tEX	1
#define	tINC	2
#define	tDEC	3
#define	tLDX	4
#define	tADD	5
#define	tAND	6
#define	tTS	7
#define	tCP	8
#define	tFLG	9
#define	tSFT	10
#define	tNOP	11
#define	tJR	12
#define	tJP	13
#define	tST	14
#define	tMV	15
#define	tLP	16
#define	tCAL	17
#define	tPORT	18
#define	tCASE	19
#define	tERR	31

typedef struct {
	unsigned short	opcode,
			length,
			type;
	int		(*exec)();
	char		*mnem;
} T_OPTBL;

extern T_OPTBL	opt[];

