/* Copyright 1994 H.Ogasawara (COR.) */

#define	REGI	(rp->m.r.i)
#define	REGJ	(rp->m.r.j)
#define	REGA	(rp->m.r.a)
#define	REGB	(rp->m.r.b)
#define	REGK	(rp->m.r.k)
#define	REGL	(rp->m.r.l)
#define	REGM	(rp->m.r.m)
#define	REGN	(rp->m.r.n)
#define	REGBA	(rp->m.x.ba)
#define	REGX	(rp->m.x.x)
#define	REGY	(rp->m.x.y)
#define	REGXL	(rp->m.r.xl)
#define	REGXH	(rp->m.r.xh)
#define	REGYL	(rp->m.r.yl)
#define	REGYH	(rp->m.r.yh)
#define	REGP	(rp->p)
#define	REGQ	(rp->q)
#define	RM(a)	(rp->m.p[a])
#define	MEM(a)	(rp->mem[a])
#define	REGMP()	(rp->m.p[rp->p])

#ifdef LITTLEENDIAN
# ifdef BIGENDIAN
#  undef BIGENDIAN
# endif
#else
# ifndef BIGENDIAN
#  define BIGENDIAN
# endif
#endif

#ifdef BIGENDIAN
# define SWAPX()  {unsigned char wk=REGXL;REGXL=REGXH;REGXH=wk;}
# define SWAPY()  {unsigned char wk=REGYL;REGYL=REGYH;REGYH=wk;}
# define SWAPBA() {unsigned char wk=REGA;REGA=REGB;REGB=wk;}
#else
# define SWAPX()
# define SWAPY()
# define SWAPBA()
#endif

#define	ZSET(n)		(rp->z= ((n)==0))
#define	OPWD		((MEM(rp->pc-2)<<8)+MEM(rp->pc-1))
#define	OP		(MEM(rp->pc-1))

typedef struct {
	unsigned short	pc,
			dp,
			trace;
	unsigned char	p, q, r, flag, c, z;
	unsigned char	*mem;
	union {
		struct {
			unsigned char	i,j,a,b;
			unsigned char	xl,xh,yl,yh;
			unsigned char	k,l,m,n;
			}	r;
		struct {
			unsigned short	ji, ba, x, y, lk, nm;
		}		x;
		unsigned char	p[256];
	} m;
} T_REG;

