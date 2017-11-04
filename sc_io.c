/* Copyright 1994 H.Ogasawara (COR.) */

#include	"reg.h"

/* ?? err */
f_err( rp )
T_REG	*rp;
{
	printf( "%04x : %02x unknown opcode error\n", rp->pc, MEM(rp->pc-1) );
	exit( 1 );
}

/* 4c ina */
f_ina( rp )
T_REG	*rp;
{
/*	REGA= 0x00;*/
	REGA= GetChar();		/* input I/O */
}

static unsigned char	stcbuf[1024*4],
			*stcp0= stcbuf,
			*stcp1= stcbuf;
bst_init()
{
	*(stcp0= stcp1= stcbuf)= 0;
}

bst_push( ch )
unsigned char	ch;
{
	*stcp0++= ch;
}

/* cc inb */
f_inb( rp )
T_REG	*rp;
{
	REGA= *stcp1++;
}

/* 5d outa */
f_outa( rp )
T_REG	*rp;
{
	PutChar( RM(0x5c) );		/* output I/O */
}

static unsigned char	fncbuf[256+2],
			*fncp= fncbuf,
			fnclen= 0;
/* dd outb */
f_outb( rp )
T_REG	*rp;
{
	*fncp++= RM(0x5d);
	if( fnclen == 255 ){
		if( !(fnclen= RM(0x5d) ) ){
			bst_init();
			bst_push( exec_fncsys( rp, fncp= fncbuf ) );
		}
	}else if( fnclen ){
		if( !--fnclen ){
			bst_init();
			bst_push( exec_fncsys( rp, fncp= fncbuf ) );
		}
	}else
		fnclen= 255;
}

/* df outc */
f_outc( rp )
T_REG	*rp;
{
	if( RM(0x5f) & 0x8 ){
		puts( "PowerOff..exit" );
		exit( 0 );
	}
}

/* 5f outf */
f_outf( rp )
T_REG	*rp;
{
}

/* 6b test */
f_test( rp )
T_REG	*rp;
{
	rp->z= 0;
}

