/* Copyright 1994 H.Ogasawara (COR.) */

#include	"reg.h"

#define	ICZSET(n)	((n)++,rp->z= rp->c= ((n)==0))
#define	DCZSET(n)	((n)--,rp->z= ((n)==0),rp->c= ((n)==255))

/* 00 I=op */
f_lii( rp )
T_REG	*rp;
{
	REGI= OP;
}

/* 01 J=op */
f_lij( rp )
T_REG	*rp;
{
	REGJ= OP;
}

/* 02 A=op */
f_lia( rp )
T_REG	*rp;
{
	REGA= OP;
}

/* 03 B=op */
f_lib( rp )
T_REG	*rp;
{
	REGB= OP;
}

/* 04 DP=++X */
f_ix( rp )
T_REG	*rp;
{
	SWAPX();
	rp->dp= ++REGX;
	SWAPX();
}

/* 05 DP=--X */
f_dx( rp )
T_REG	*rp;
{
	SWAPX();
	rp->dp= --REGX;
	SWAPX();
}

/* 06 DP=++Y */
f_iy( rp )
T_REG	*rp;
{
	SWAPY();
	rp->dp= ++REGY;
	SWAPY();
}

/* 07 DP=--Y */
f_dy( rp )
T_REG	*rp;
{
	SWAPY();
	rp->dp= --REGY;
	SWAPY();
}



/* 10 DP=op */
f_lidp( rp )
T_REG	*rp;
{
	rp->dp= OPWD;
}

/* 11 DPL=op */
f_lidl( rp )
T_REG	*rp;
{
	rp->dp= (rp->dp & 0xff00) + OP;
}

/* 12 P=op */
f_lip( rp )
T_REG	*rp;
{
	rp->p= OP & 0x7f;
}

/* 13 Q=op */
f_liq( rp )
T_REG	*rp;
{
	rp->q= OP & 0x7f;
}

/* 20 A=P */
f_ldp( rp )
T_REG	*rp;
{
	REGA= rp->p;
}

/* 21 A=Q */
f_ldq( rp )
T_REG	*rp;
{
	REGA= rp->q;
}

/* 22 A=R */
f_ldr( rp )
T_REG	*rp;
{
	REGA= rp->r;
}

/* 23 A=0 */
f_clra( rp )
T_REG	*rp;
{
	REGA= 0;
}

/* 24 A=(DP=++X) */
f_ixl( rp )
T_REG	*rp;
{
	SWAPX();
	REGA= MEM(rp->dp= ++REGX);
	SWAPX();
}

/* 25 A=(DP=--X) */
f_dxl( rp )
T_REG	*rp;
{
	SWAPX();
	REGA= MEM(rp->dp= --REGX);
	SWAPX();
}

/* 26 (DP=++Y)=A */
f_iys( rp )
T_REG	*rp;
{
	SWAPY();
	MEM(rp->dp= ++REGY)= REGA;
	SWAPY();
}

/* 27 (DP=--Y)=A */
f_dys( rp )
T_REG	*rp;
{
	SWAPY();
	MEM(rp->dp= --REGY)= REGA;
	SWAPY();
}


/* 30 P=A */
f_stp( rp )
T_REG	*rp;
{
	rp->p= REGA & 0x7f;
}

/* 31 Q=A */
f_stq( rp )
T_REG	*rp;
{
	rp->q= REGA & 0x7f;
}

/* 32 R=A */
f_str( rp )
T_REG	*rp;
{
	rp->r= REGA & 0x7f;
}

/* 40 I++ */
f_inci( rp )
T_REG	*rp;
{
	ICZSET( REGI );
	REGQ= 0x00;
}

/* 41 I-- */
f_deci( rp )
T_REG	*rp;
{
	DCZSET( REGI );
	REGQ= 0x00;
}

/* 42 A++ */
f_inca( rp )
T_REG	*rp;
{
	ICZSET( REGA );
	REGQ= 0x02;
}

/* 43 A-- */
f_deca( rp )
T_REG	*rp;
{
	DCZSET( REGA );
	REGQ= 0x02;
}

/* 48 K++ */
f_inck( rp )
T_REG	*rp;
{
	ICZSET( REGK );
	REGQ= 0x08;
}

/* 49 K-- */
f_deck( rp )
T_REG	*rp;
{
	DCZSET( REGK );
	REGQ= 0x08;
}

/* 4a M++ */
f_incm( rp )
T_REG	*rp;
{
	ICZSET( REGM );
	REGQ= 0x0a;
}

/* 4b M-- */
f_decm( rp )
T_REG	*rp;
{
	DCZSET( REGM );
	REGQ= 0x0a;
}

/* 50 P++ */
f_incp( rp )
T_REG	*rp;
{
	REGP++;
	REGP &= 0x7f;
}

/* 51 P-- */
f_decp( rp )
T_REG	*rp;
{
	REGP--;
	REGP &= 0x7f;
}

/* 52 (DP)=A */
f_std( rp )
T_REG	*rp;
{
	MEM(rp->dp)= REGA;
}

/* 53 (DP)=(P) */
f_mvdm( rp )
T_REG	*rp;
{
	MEM(rp->dp)= REGMP();
}

/* 54 (P)=(PC) */
f_readm( rp )
T_REG	*rp;
{
	REGMP()= MEM(rp->pc);
}

/* 55 (P)=(DP) */
f_mvmd( rp )
T_REG	*rp;
{
	REGMP()= MEM(rp->dp);
}

/* 56 A=(PC) */
f_read( rp )
T_REG	*rp;
{
	REGA= MEM(rp->pc);
}

/* 57 A=(DP) */
f_ldd( rp )
T_REG	*rp;
{
	REGA= MEM(rp->dp);
}

/* 59 A=(P) */
f_ldm( rp )
T_REG	*rp;
{
	REGA= REGMP();
}

/* c0 J++ */
f_incj( rp )
T_REG	*rp;
{
	ICZSET( REGJ );
	REGQ= 0x01;
}

/* c1 J-- */
f_decj( rp )
T_REG	*rp;
{
	DCZSET( REGJ );
	REGQ= 0x01;
}

/* c2 B++ */
f_incb( rp )
T_REG	*rp;
{
	ICZSET( REGB );
	REGQ= 0x03;
}

/* c3 J-- */
f_decb( rp )
T_REG	*rp;
{
	DCZSET( REGB );
	REGQ= 0x03;
}

/* c8 L++ */
f_incl( rp )
T_REG	*rp;
{
	ICZSET( REGL );
	REGQ= 0x09;
}

/* c9 L-- */
f_decl( rp )
T_REG	*rp;
{
	DCZSET( REGL );
	REGQ= 0x09;
}

/* ca N++ */
f_incn( rp )
T_REG	*rp;
{
	ICZSET( REGN );
	REGQ= 0x0b;
}

/* cb N-- */
f_decn( rp )
T_REG	*rp;
{
	DCZSET( REGN );
	REGQ= 0x0b;
}

/* da A<=>B */
f_exab( rp )
T_REG	*rp;
{
	unsigned char	wk= REGA;
	REGA= REGB;
	REGB= wk;
}

/* da A<=>(P) */
f_exam( rp )
T_REG	*rp;
{
	unsigned char	wk= REGMP();
	REGMP()= REGA;
	REGA= wk;
}

