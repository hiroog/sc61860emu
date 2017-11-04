#!/usr/local/bin/jperl
while(<>){
	if( /^(f_[0-9A-Za-z_]*)/ ){
		chop;
		printf( "extern int $1();\n" );
	}
}
