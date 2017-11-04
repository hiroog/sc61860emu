/* Copyright 1994 H.Ogasawara (COR.) */

#include	"reg.h"

/* 34 push */
f_push( rp )
T_REG	*rp;
{
	RM(--rp->r)= REGA;
}

/* 5b pop */
f_pop( rp )
T_REG	*rp;
{
	REGA= RM(rp->r++);
}

/* 78 call */
f_call( rp )
T_REG	*rp;
{
	RM(--rp->r)= rp->pc>>8;
	RM(--rp->r)= rp->pc&255;
	rp->pc= OPWD;
}

/* e0..ff cal */
f_cal( rp )
T_REG	*rp;
{
	RM(--rp->r)= rp->pc>>8;
	RM(--rp->r)= rp->pc&255;
	rp->pc= ((MEM(rp->pc-2)&0x1f)<<8)+OP;
}

/* 37 ret */
f_ret( rp )
T_REG	*rp;
{
	rp->pc= (RM(rp->r+1)<<8)+ RM(rp->r);
	rp->r+= 2;
}

/* d8 (R)=00 */
f_reave( rp )
T_REG	*rp;
{
	RM(rp->r)= 0;
}

/* 2f loop */
f_loop( rp )
T_REG	*rp;
{
	if( RM(rp->r) == 0 ){
		RM(rp->r++)--;
		rp->c= 1;
		rp->z= 0;
	}else{
		rp->z= --RM(rp->r) == 0;
		rp->c= 0;
		rp->pc-= OP+1;
	}
}

/* 7a set */
f_set( rp )
T_REG	*rp;
{
	rp->flag= MEM(rp->pc-3);	/* count */
	RM(--rp->r)= MEM(rp->pc-2);
	RM(--rp->r)= MEM(rp->pc-1);
}

