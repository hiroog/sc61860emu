/* 1997/04/02 Hiroyuki Ogasawara (COR.) */

#include	<stdio.h>
#ifndef _SWIN32
#include	<sys/file.h>
#endif
#include	<sys/types.h>
#ifdef UNIX
# include	<sys/dir.h>
#endif
#ifdef HUMAN
# include	<doslib.h>
#endif
#if _SWIN32
# ifndef	F_OK
#  define	F_OK	0
# endif
#endif

GetChar()
{
	return	getchar();
}

PutChar( c )
{
	putchar( c );
	fflush( stdout );
}

IsFile( file )
char	*file;
{
	return	!access( file, F_OK );
}

LsFile( fnc )
void	(*fnc)();
{
#ifdef HUMAN
	struct FILBUF	dp;
	if( FILES( &dp, "*.*", 0x2f ) >= 0 ){
		do{
			char	*p= dp.name;
			for(; *p ; (*fnc)( *p++ ) );
			(*fnc)( '\n' );
		}while( NFILES( &dp ) >= 0 );
	}
	(*fnc)( '\0' );
#endif
#ifdef UNIX
	DIR	*dp;
	if( dp= opendir( "." ) ){
		struct direct	*dir;
		while( dir= readdir( dp ) ){
			char	*p= dir->d_name;
			for(; *p ; (*fnc)( *p++ ) );
			(*fnc)( '\n' );
		}
		closedir( dp );
	}
	(*fnc)( '\0' );
#endif
#ifdef _SWIN32
	puts( "W32”Å‚Í–¢ŽÀ‘•" );
	(*fnc)( '\0' );
#endif
}

FileSize( file )
char	*file;
{
	FILE	*fp;
	int	size= 0;
	if( fp= fopen( file, "rb" ) ){
		fseek( fp, 0, 2 );
		size= ftell( fp );
		fclose( fp );
	}
	return	size;
}
