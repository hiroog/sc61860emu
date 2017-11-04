/* Copyright 1994 H.Ogasawara (COR.) */

#include	"reg.h"

/* 28 jrnzp */
f_jrnzp( rp )
T_REG	*rp;
{
	if( !rp->z ){
		rp->pc+= OP-1;
		RM(rp->r-1)= rp->pc;
	}
}

/* 29 jrnzm */
f_jrnzm( rp )
T_REG	*rp;
{
	if( !rp->z ){
		rp->pc-= OP+1;
		RM(rp->r-1)= rp->pc;
	}
}

/* 2a jrncp */
f_jrncp( rp )
T_REG	*rp;
{
	if( !rp->c ){
		rp->pc+= OP-1;
		RM(rp->r-1)= rp->pc;
	}
}

/* 2b jrncm */
f_jrncm( rp )
T_REG	*rp;
{
	if( !rp->c ){
		rp->pc-= OP+1;
		RM(rp->r-1)= rp->pc;
	}
}

/* 2c jrp */
f_jrp( rp )
T_REG	*rp;
{
	rp->pc+= OP-1;
	RM(rp->r-1)= rp->pc;
}

/* 2d jrm */
f_jrm( rp )
T_REG	*rp;
{
	rp->pc-= OP+1;
	RM(rp->r-1)= rp->pc;
}

/* 38 jrzp */
f_jrzp( rp )
T_REG	*rp;
{
	if( rp->z ){
		rp->pc+= OP-1;
		RM(rp->r-1)= rp->pc;
	}
}

/* 39 jrzm */
f_jrzm( rp )
T_REG	*rp;
{
	if( rp->z ){
		rp->pc-= OP+1;
		RM(rp->r-1)= rp->pc;
	}
}

/* 3a jrcp */
f_jrcp( rp )
T_REG	*rp;
{
	if( rp->c ){
		rp->pc+= OP-1;
		RM(rp->r-1)= rp->pc;
	}
}

/* 3b jrcm */
f_jrcm( rp )
T_REG	*rp;
{
	if( rp->c ){
		rp->pc-= OP+1;
		RM(rp->r-1)= rp->pc;
	}
}

/* 7c jpnz */
f_jpnz( rp )
T_REG	*rp;
{
	if( !rp->z )
		rp->pc= OPWD;
}

/* 7d jpnc */
f_jpnc( rp )
T_REG	*rp;
{
	if( !rp->c )
		rp->pc= OPWD;
}

/* 7e jpz */
f_jpz( rp )
T_REG	*rp;
{
	if( rp->z )
		rp->pc= OPWD;
}

/* 7f jpc */
f_jpc( rp )
T_REG	*rp;
{
	if( rp->c )
		rp->pc= OPWD;
}

/* 79 jp */
f_jp( rp )
T_REG	*rp;
{
	rp->pc= OPWD;
}

/* 69 jp */
f_case( rp )
T_REG	*rp;
{
	int	f= rp->flag;
	for( rp->pc++ ; f-- >= 0 ; rp->pc+= 3 ){
		if( MEM(rp->pc) == REGA ){
			rp->pc= (MEM(rp->pc+1)<<8)+MEM(rp->pc+2);
			return;
		}
	}
	rp->pc= (MEM(rp->pc)<<8)+MEM(rp->pc+1);
}
