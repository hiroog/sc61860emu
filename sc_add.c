/* Copyright 1994 H.Ogasawara (COR.) */

#include	"reg.h"

#define	ACZSET(n,op) (rp->c=(n)+(op)>=0x100,rp->z=((n)+=(op))==0)
#define	SCZSET(n,op) (rp->c=(n)<(op),rp->z=((n)-=(op))==0)
#define	CCZSET(n,op) (rp->c=(n)<(op),rp->z=((n)==(op)))

/* 44 (P)+=A */
f_adm( rp )
T_REG	*rp;
{
	ACZSET( REGMP(), REGA );
}

/* 45 (P)-=A */
f_sbm( rp )
T_REG	*rp;
{
	SCZSET( REGMP(), REGA );
}

/* 70 (P)+=op */
f_adim( rp )
T_REG	*rp;
{
	ACZSET( REGMP(), OP );
}

/* 71 (P)-=op */
f_sbim( rp )
T_REG	*rp;
{
	SCZSET( REGMP(), OP );
}

/* 74 A+=op */
f_adia( rp )
T_REG	*rp;
{
	ACZSET( REGA, OP );
}

/* 75 A-=op */
f_sbia( rp )
T_REG	*rp;
{
	SCZSET( REGA, OP );
}

/* c4 (P)+=(A+C) */
f_adcm( rp )
T_REG	*rp;
{
	unsigned char	tmp= REGA+rp->c;
	ACZSET( REGMP(), tmp );
}

/* c5 (P)-=(A+C) */
f_sbcm( rp )
T_REG	*rp;
{
	unsigned char	tmp= REGA+rp->c;
	SCZSET( REGMP(), tmp );
}

/* 14 (P)2+=BA */
f_adb( rp )
T_REG	*rp;
{
	unsigned short	tmp= (RM(REGP+1)<<8)+RM(REGP);
	SWAPBA();
	rp->c= (unsigned long)(tmp+REGBA) >= 0x10000;
	rp->z= (tmp+= REGBA) == 0;
	SWAPBA();
	RM(REGP)= tmp & 0xff;
	RM(REGP+1)= tmp>>8;
	REGP++;
}

/* 15 (P)2-=BA */
f_sbb( rp )
T_REG	*rp;
{
	unsigned short	tmp= (RM(REGP+1)<<8)+RM(REGP);
	SWAPBA();
	rp->c= tmp < REGBA;
	rp->z= (tmp-= REGBA) == 0;
	SWAPBA();
	RM(REGP)= tmp & 0xff;
	RM(REGP+1)= tmp>>8;
	REGP++;
}

/* 60 (P)&=op */
f_anim( rp )
T_REG	*rp;
{
	ZSET( REGMP()&=OP );
}

/* 61 (P)|=op */
f_orim( rp )
T_REG	*rp;
{
	ZSET( REGMP()|=OP );
}

/* 64 A&=op */
f_ania( rp )
T_REG	*rp;
{
	ZSET( REGA&=OP );
}

/* 65 A|=op */
f_oria( rp )
T_REG	*rp;
{
	ZSET( REGA|=OP );
}

/* 46 (P)&=A */
f_anma( rp )
T_REG	*rp;
{
	ZSET( REGMP()&=REGA );
}

/* 47 (P)|=A */
f_orma( rp )
T_REG	*rp;
{
	ZSET( REGMP()|=REGA );
}

/* d4 (DP)&=op */
f_anid( rp )
T_REG	*rp;
{
	ZSET( MEM(rp->dp)&=OP );
	RM(rp->r-1)= MEM(rp->dp);
}

/* d5 (DP)|=op */
f_orid( rp )
T_REG	*rp;
{
	ZSET( MEM(rp->dp)|=OP );
	RM(rp->r-1)= MEM(rp->dp);
}

/* 62 A&op */
f_tsim( rp )
T_REG	*rp;
{
	ZSET( REGMP()&OP );
}

/* 63 A-op */
f_cpim( rp )
T_REG	*rp;
{
	CCZSET( REGMP(), OP );
}

/* 66 A&op */
f_tsia( rp )
T_REG	*rp;
{
	ZSET( REGA&OP );
}

/* 67 A-op */
f_cpia( rp )
T_REG	*rp;
{
	CCZSET( REGA, OP );
}

/* c6 (P)&A */
f_tsma( rp )
T_REG	*rp;
{
	ZSET( REGMP()&REGA );
}

/* c7 (P)-A */
f_cpma( rp )
T_REG	*rp;
{
	CCZSET( REGMP(), REGA );
}

/* d6 (P)&op */
f_tsid( rp )
T_REG	*rp;
{
	ZSET( MEM(rp->dp)&OP );
	RM(rp->r-1)= MEM(rp->dp);
}

/* d7 (P)-op */
f_cpid( rp )
T_REG	*rp;
{
/*	CCZSET( MEM(rp->dp), OP );*/
	rp->z= 1;
	RM(rp->r-1)= MEM(rp->dp);
}

