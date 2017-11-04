/* Copyright 1994 H.Ogasawara (COR.) */

#include	<stdio.h>
#include	<stdlib.h>
#include	"reg.h"

#define		MAXLEN		1024
#define		MAXLAB		1024
#define		HEXCH(ch)	(((ch)>'9' ? (ch)-7 : (ch)) & 0xf)
#define		ISHEX(ch)	(((ch)>='0'&&(ch)<='9')||\
				((ch)>='A'&&(ch)<='F')||\
				((ch)>='a'&&(ch)<='f'))
#define		ISSPC(ch)	(((ch)&&(ch)<=' ')||(ch)==',')

static loadhex();

unsigned short
atoh( ptr )
char	*ptr;
{
	unsigned short	i= 0;
	if( *ptr == '$' || *ptr == '&' )
		ptr++;
	for(; ISHEX(*ptr) ; ptr++ ){
		i<<= 4;
		i+=  HEXCH(*ptr);
	}
	return	i;
}

static unsigned char *
getword( str, ptr )
unsigned char	*str, *ptr;
{
	unsigned int	c= 0;
	for(; ISSPC(*ptr) ; ptr++ );
	if( *ptr == '"' || *ptr == '\'' )
		c= *str++= *ptr++;
	for(; *ptr && ((!c&&!ISSPC(*ptr))||(c&&c!=*ptr)) ; *str++= *ptr++ );
	*str= '\0';
	if( c && c == *ptr )
		ptr++;
	return	ptr;
}

typedef struct {
	char	name[16];
	unsigned short	addr;		/* 18 byte */
} T_LV;

static int	lp;

static void
ladd( name, adr, lvp )
char	*name;
unsigned short	adr;
T_LV	*lvp;
{
	strncpy( lvp[lp].name, name, 16 );
	lvp[lp++].addr= adr;
}

static unsigned short
lsearch( name, lvp )
char	*name;
T_LV	*lvp;
{
	int	i;
	for( i= 0 ; i< lp ; i++ )
		if( !strcmp( lvp[i].name, name ) )
			return	lvp[i].addr;
	return	0;
}

static void
lprint( lvp )
T_LV	*lvp;
{
	int	i;
	for( i= 0 ; i< lp ; i++ )
		printf( "%-16s %04x\n", lvp[i].name, lvp[i].addr );
}

static
path1( rp, fp, lvp, path )
T_REG	*rp;
FILE	*fp;
T_LV	*lvp;
{
	unsigned char	*lc= rp->mem,
			buf[MAXLEN],
			cmd[MAXLEN],
			*ptr;
	fseek( fp, 0, 0 );
	for(; fgets( buf, MAXLEN, fp );){
		for( ptr= buf ; ISSPC(*ptr) ; ptr++ );
		if( !*ptr || *ptr == '#' || *ptr == ';' )
			continue;
		for(; (ptr= getword( cmd, ptr )) && *cmd ;){
			unsigned char	*p;
			unsigned short	i, l;
			if( *cmd == ';' || *ptr == '#' )
				break;
			switch( *cmd ){
			case '.':
				if( !strncmp( cmd, ".addr:", 6 ) ){
					lc= rp->mem+atoh( cmd+6 );
				}else if( !strncmp( cmd, ".exec:", 6 ) ){
					rp->pc= atoh( cmd+6 );
				}else if( !strncmp( cmd, ".equ:", 5 ) ){
					if( !path )
						lvp[lp-1].addr= atoh( cmd+5 );
				}else if( !strncmp( cmd, ".include:", 9 ) ){
					if( !path )
						loadhex( rp, cmd+9, lvp, 1 );
				}else if( !strncmp( cmd, ".qinclude:", 10 ) ){
					if( !path )
						loadhex( rp, cmd+10, lvp, 0 );
				}else{
					printf( "command '%s' error\n", cmd );
				}
				break;
			case '"':
			case '\'':
				for( p= cmd+1 ; *p ; *lc++= *p++ );
				break;
			default:
				for( p= cmd ; *p && p[1] ; p+= 2 )
					*lc++= (HEXCH(*p)<<4)+(HEXCH(p[1]));
				break;
			case ':':
				if( !path )
					ladd( cmd+1, lc-rp->mem, lvp );
				break;
			case '@':
				i= lc-rp->mem;
				l= lsearch( cmd+1, lvp );
				*lc++= i < l ? l-i : i-l;
				break;
			case '!':
			case 'L':
				*lc++= lsearch( cmd+1, lvp );
				break;
			case 'H':
				*lc++= lsearch( cmd+1, lvp )>>8;
				break;
			case '*':
				l= lsearch( cmd+1, lvp );
				*lc++= l>>8;
				*lc++= l;
				break;
			case '_':
				l= lsearch( cmd+1, lvp )+0xe000;
				*lc++= l>>8;
				*lc++= l;
				break;
			}
		}
	}
}

static
loadhex( rp, file, lvp, path )
T_REG	*rp;
char	*file;
T_LV	*lvp;
{
	FILE	*fp;
	if( fp= fopen( file, "r" ) ){
		path1( rp, fp, lvp, 0 );
		if( path )
			path1( rp, fp, lvp, 1 );
		fclose( fp );
		return	1;
	}
	return	0;
}

loadhexfile( rp, err, file )
T_REG	*rp;
char	*file;
{
	T_LV	*lvp;
	if( lvp= malloc(sizeof(T_LV)*MAXLAB) ){
		lp= 0;
		if( loadhex( rp, file, lvp, 1 ) ){
			if( rp->trace & 8 )
				lprint( lvp );
			if( err )
				printf( "load '%s'\n", file );
		}else if( err ){
			printf( "'%s' open error\n", file );
			exit( 1 );
		}
		free( lvp );
	}else{
		puts( "malloc error" );
		exit( 1 );
	}
}

