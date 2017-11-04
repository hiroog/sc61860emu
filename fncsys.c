/* Copyright 1994 Hiroyuki Ogasawara (COR.) */

#include	<stdio.h>
#include	"reg.h"

saveimage( rp, addr, len, file )
T_REG	*rp;
char	*file;
unsigned	addr, len;
{
	FILE	*fp;
	if( fp= fopen( file, "wb" ) ){
		if( fwrite( rp->mem+addr, 1, len, fp ) != len )
			puts( "write error" );
		fclose( fp );
	}
}

savehexfile( rp, addr, len, file )
T_REG	*rp;
char	*file;
unsigned	addr, len;
{
	FILE	*fp;
	if( fp= fopen( file, "w" ) ){
		unsigned char	i;
		unsigned char	*ptr= rp->mem+addr;
		fprintf( fp, "# %04X byte\n.addr:%04X\n", len, addr );
		for( i= 0 ; len-- ; i++ ){
			fprintf( fp, "%02X", *ptr++ );
			putc( (i&15) == 15 ? '\n': ' ', fp );
		}
		fclose( fp );
	}
}

exec_fncsys( rp, fncp )
T_REG		*rp;
unsigned char	*fncp;
{
	unsigned int	addr, length;
	extern void	bst_push();
	switch( *fncp ){
	case 0x00:
		return	1;
	case 0x01:
		if( IsFile( fncp+4 ) ){
			addr= (fncp[2]<<8)+(fncp[3]);
			loadimage( rp, addr, fncp+4, 0 );
			return	1;
		}
		return	2;
	case 0x02:
		if( IsFile( fncp+2 ) ){
			loadhexfile( rp, 0, fncp+2 );
			return	1;
		}
		return	2;
	case 0x03:
		addr=   (fncp[2]<<8)+(fncp[3]);
		length= (fncp[4]<<8)+(fncp[5]);
		saveimage( rp, addr, length, fncp+6 );
		return	1;
	case 0x04:
		addr=   (fncp[2]<<8)+(fncp[3]);
		length= (fncp[4]<<8)+(fncp[5]);
		savehexfile( rp, addr, length, fncp+6 );
		return	1;
	case 0x05:
		LsFile( bst_push );
		return	0;
	case 0x06:
		length= FileSize( fncp+2 );
		bst_push( length>>8 );
		bst_push( length & 255 );
		return	1;
	case 0x07:
		return	rand()>>3;
	}
	return	2;
}

