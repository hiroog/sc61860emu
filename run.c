/* Copyright 1994 H.Ogasawara (COR.) */

#include	"reg.h"
#include	"opexec.h"

run_sce( rp )
T_REG	*rp;
{
	for(;;){
		unsigned char	opcode= MEM(rp->pc);
		T_OPTBL		*cp= opt+opcode;

		if( rp->trace ){
			unsigned char	opr[20];
			int		i;
			if( (rp->trace & 4) || rp->pc >= 0x2000 ){
				switch( cp->length ){
				case l2B:
					sprintf( opr, "%02x", MEM(rp->pc+1) );
					break;
				case l3B:
					sprintf( opr, "%02x%02x", MEM(rp->pc+1), MEM(rp->pc+2) );
					break;
				case l4B:
					sprintf( opr, "%02x %02x%02x", MEM(rp->pc+1), MEM(rp->pc+2), MEM(rp->pc+3) );
					break;
				default:
					*opr= '\0';
				}
				printf( "%04x: %02x %-7s(%d) p:%02x q:%02x r:%02x dp:%04x f:%d%d %s\n",
						rp->pc, opcode, opr, cp->length,
						rp->p, rp->q, rp->r, rp->dp, rp->c, rp->z,
						cp->mnem );
				if( rp->trace & 2 ){
					for( i= 0 ; i< 0x5f ; i++ )
						printf( "%02x ", RM(i) );
					putchar( '\n' );
				}
			}
		}

		if( cp->length != lnB )
			rp->pc+= cp->length;
		(*cp->exec)( rp );
	}
}
