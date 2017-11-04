/* Copyright 1994 H.Ogasawara (COR.) */

#include	<stdio.h>
#include	<stdlib.h>
#include	"reg.h"

#define		MEMSIZE		(64*1024)

T_REG	reg;
unsigned short	atoh();

loadimage( rp, loadadr, file, err )
T_REG	*rp;
unsigned short	loadadr;
char	*file;
{
	FILE	*fp;
	if( fp= fopen( file, "rb" ) ){
		int	size= fread( rp->mem+loadadr, 1, MEMSIZE, fp );
		if( err )
			printf( "load %04x-%d bytes\n", loadadr, size );
		fclose( fp );
		return	size;
	}else if( err ){
		printf( "'%s' open error\n", file );
		exit( 1 );
	}
}

bigendian_check()
{
	int	i= 1;
	if( *((char*)(&i)) == 1 ){
#ifdef BIGENDIAN
		puts( "compile missing. you need -DLITTLEENDIAN option" );
		exit( 1 );
#else
	}else{
		puts( "compile missing. you need -DBIGENDIAN option" );
		exit( 1 );
#endif
	}
}

static void
usage()
{
	puts( "\
usage: oldsce [-e<execadr>] [-h <hexfile>] [-l<loadadr>] [-t<l>] [<corefile>]\
" );
	exit( 1 );
}

main( argc, argv )
char	**argv;
{
	unsigned short	loadadr= 0x2000;
	puts( "oldsce - sc61860 emurator v1.10 1994 by H.Ogasawara (COR.)" );
	bigendian_check();
	memset( &reg, 0, sizeof(T_REG) );
	reg.pc= 0;
#ifdef HUMAN
	sbrk( 64*1024 );
#endif
#ifdef UNIX
	srand( getpid() );
#endif
	if( !(reg.mem= malloc( MEMSIZE )) ){
		puts( "memory error" );
		exit( 1 );
	}
	loadhexfile( &reg, 0, "sysinit" );
	for(; --argc ;){
		if( **++argv == '-' ){
			switch( (*argv)[1] ){
			case 'e':
				reg.pc= atoh( *argv+2 );
				break;
			case 'l':
				loadadr= atoh( *argv+2 );
				break;
			case 'h':
				if( (*argv)[2] )
					loadhexfile( &reg, 1, *argv+2 );
				else if( argc >= 2 ){
					loadhexfile( &reg, 1, *++argv );
					argc--;
				}else
					usage();
				break;
			case 't':
				reg.trace= atoh( *argv+2 )|1;
				break;
			default:
				usage();
			}
		}else
			loadimage( &reg, loadadr, *argv, 1 );
	}
	run_sce( &reg );
	free( reg.mem );
	exit( 0 );
}

