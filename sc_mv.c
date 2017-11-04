/* 1994/02/06 Hiroyuki Ogasawara (COR.) */

#include	"reg.h"

/* 08 [(P)=(Q)]i */
f_mvw( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ; RM(rp->p++)= RM(rp->q++) );
}

/* 09 [(P)<>(Q)]i */
f_exw( rp )
T_REG	*rp;
{
	int	i= REGI;
	unsigned char	wk;
	for(; i-- >= 0 ; wk=RM(rp->q),RM(rp->q++)=RM(rp->p),RM(rp->p++)=wk );
}

/* 0a [(P)=(Q)]j */
f_mvb( rp )
T_REG	*rp;
{
	int	i= REGJ;
	for(; i-- >= 0 ; RM(rp->p++)= RM(rp->q++) );
}

/* 0b [(P)<>(Q)]i */
f_exb( rp )
T_REG	*rp;
{
	int	i= REGJ;
	unsigned char	wk;
	for(; i-- >= 0 ; wk=RM(rp->q),RM(rp->q++)=RM(rp->p),RM(rp->p++)=wk );
}

/* 18 [(P)=(DP)]i */
f_mvwd( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ; RM(rp->p++)= MEM(rp->dp++) );
	rp->dp--;
}

/* 19 [(P)<>(DP)]i */
f_exwd( rp )
T_REG	*rp;
{
	int	i= REGI;
	unsigned char	wk;
	for(; i-- >= 0 ;wk=RM(rp->p),RM(rp->p++)=MEM(rp->dp),MEM(rp->dp++)=wk);
	rp->dp--;
}

/* 1a [(P)=(DP)]j */
f_mvbd( rp )
T_REG	*rp;
{
	int	i= REGJ;
	for(; i-- >= 0 ; RM(rp->p++)= MEM(rp->dp++) );
	rp->dp--;
}

/* 1b [(P)<>(DP)]i */
f_exbd( rp )
T_REG	*rp;
{
	int	i= REGJ;
	unsigned char	wk;
	for(; i-- >= 0 ;wk=RM(rp->p),RM(rp->p++)=MEM(rp->dp),MEM(rp->dp++)=wk);
	rp->dp--;
}

/* 1e [(P)=A]i */
f_film( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ; RM(rp->p++)= REGA );
}

/* 1f [(DP)=A]i */
f_fild( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ; MEM(rp->dp++)= REGA );
	rp->dp--;
}

/* 35 [(P)=(BA)]i */
f_data( rp )
T_REG	*rp;
{
	int	i= REGI;
	unsigned short	pc;
	RM(rp->r-1)= rp->pc>>8;
	RM(rp->r-2)= rp->pc&255;
	SWAPBA();
	for( pc= REGBA ; i-- >= 0 ; RM(rp->p++)= MEM(pc++) );
	SWAPBA();
}

/* d3 [(BA)=(P)]i ? */
f_write( rp )
T_REG	*rp;
{
#if 0
	int	i= REGI;
	unsigned short	pc;
	RM(rp->r-1)= rp->pc>>8;
	RM(rp->r-2)= rp->pc&255;
	SWAPBA();
	for( pc= REGBA ; i-- >= 0 ; MEM(pc++)= RM(rp->p++) );
	SWAPBA();
#endif
}



/*** Caution ! not imprement ***/

/* 0c [(P)+=A]i */
f_adn( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ;){
	}
}

/* 0d [(P)-=A]i */
f_sbn( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ;){
	}
}

/* 0e [(P)+=(Q)]i */
f_adw( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ;){
	}
}

/* 0f [(P)-=(Q)]i */
f_sbw( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ;){
	}
}

/* 1c [(P)>>=4]i */
f_srw( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ;);
}

/* 1d [(P)<<=4]i */
f_slw( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ;);
}

/* 4f []i */
f_ipxl( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ;);
}

/* 6f []i */
f_ipxh( rp )
T_REG	*rp;
{
	int	i= REGI;
	for(; i-- >= 0 ;);
}

