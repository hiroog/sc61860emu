/* 1994/02/16 Hiroyuki Ogasawara (COR.) */

#include	"reg.h"

/* d0 c=z=1 */
f_sc( rp )
T_REG	*rp;
{
	rp->c= rp->z= 1;
}

/* d1 c=0,z=1 */
f_rc( rp )
T_REG	*rp;
{
	rp->c= 0, rp->z= 1;
}

/* 77 z=0 */
f_rz( rp )
T_REG	*rp;
{
	rp->z= 0;
}

/* d2 A>>=1 */
f_sr( rp )
T_REG	*rp;
{
	unsigned short	flag= rp->c ? 128 : 0;
	rp->c= REGA & 1;
	REGA>>= 1;
	REGA|= flag;
}

/* 5a A<<=1 */
f_sl( rp )
T_REG	*rp;
{
	unsigned short	flag= rp->c ? 1 : 0;
	rp->c= (REGA & 128) != 0;
	REGA<<= 1;
	REGA|= flag;
}

/* 58 Al<=>Ah */
f_swp( rp )
T_REG	*rp;
{
	REGA= (REGA<<4)+(REGA>>4);
}

/* 4d nop */
f_nop( rp )
{
}

/* ce nopt */
f_nopt( rp )
{
}

/* 4e wait */
f_wait( rp )
{
}

/* 80..bf lp */
f_lp( rp )
T_REG	*rp;
{
	REGP= MEM(rp->pc-1) & 0x3f;
}
