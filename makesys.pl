#!/usr/local/bin/jperl
### make syscall.hed
$sysinit="sysinit";
$syscall="syscall.hed";
$systbl="sysinit.tbl";
$systmp="metemp.tmp";
#
unless( open( fcall, "$syscall" ) ){
	print "open error\n";
	exit 1;
}
system( "oldsce -t8 -h $sysinit > $systmp" );
print "## 1994 by H.Ogasawara (COR.)\n";
while( <fcall> ){
	if( /^:/ ){
		@tline=split( ":| |\t" );
#		print $tline[1],"\n";
		unless( open( finit, "$systmp" ) ){
			print "systmp open error\n";
			exit 1;
		}
		while( <finit> ){
			@xline=split;
			if( $xline[0] eq $tline[1] ){
				print ":$tline[1]\t.equ:$xline[1]\n";
				last;
			}
		}
		close( finit );
	}
}
close( fcall );
unlink( $systmp );
