#!/usr/bin/perl -w

use lib '../../tools/pdbgen';

require 'util.pl';

*write_file = \&Gimp::CodeGen::util::write_file;
*FILE_EXT   = \$Gimp::CodeGen::util::FILE_EXT;

$ignorefile = ".svnignore";

$outmk = "Makefile.am$FILE_EXT";
$outignore = "$ignorefile$FILE_EXT";
open MK, "> $outmk";
open IGNORE, "> $outignore";

require 'plugin-defs.pl';

$bins = ""; $opts = "";

foreach (sort keys %plugins) {
    $bins .= "\t";
    if (exists $plugins{$_}->{optional}) {
        my $makename = $_;
        $makename =~ s/-/_/g;
	$bins .= "\$(\U$makename\E)";
	$opts .= "\t$_ \\\n";
    }
    else {
	$bins .= $_;
    }
    $bins .= " \\\n";
}

$extra = "";
foreach (@extra) { $extra .= "\t$_\t\\\n" }
if ($extra) {
    $extra =~ s/\t\\\n$//s;
    $extra = "\t\\\n$extra";
}

foreach ($bins, $opts) { s/ \\\n$//s }

print MK <<EOT;


## ---------------------------------------------------------
## This file is autogenerated by mkgen.pl and plugin-defs.pl
## ---------------------------------------------------------

## Modify those two files instead of this one; for most
## plug-ins you should only need to modify plugin-defs.pl.


libgimp = \$(top_builddir)/libgimp/libgimp-\$(GIMP_API_VERSION).la
libgimpbase = \$(top_builddir)/libgimpbase/libgimpbase-\$(GIMP_API_VERSION).la
libgimpcolor = \$(top_builddir)/libgimpcolor/libgimpcolor-\$(GIMP_API_VERSION).la
libgimpconfig = \$(top_builddir)/libgimpconfig/libgimpconfig-\$(GIMP_API_VERSION).la
libgimpmath = \$(top_builddir)/libgimpmath/libgimpmath-\$(GIMP_API_VERSION).la
libgimpmodule = \$(top_builddir)/libgimpmodule/libgimpmodule-\$(GIMP_API_VERSION).la
libgimpui = \$(top_builddir)/libgimp/libgimpui-\$(GIMP_API_VERSION).la
libgimpwidgets = \$(top_builddir)/libgimpwidgets/libgimpwidgets-\$(GIMP_API_VERSION).la


if OS_WIN32
mwindows = -mwindows
endif

AM_LDFLAGS = \$(mwindows)

libexecdir = \$(gimpplugindir)/plug-ins

EXTRA_DIST = \\
	mkgen.pl	\\
	plugin-defs.pl$extra

INCLUDES = \\
	-I\$(top_srcdir)	\\
	\$(GTK_CFLAGS)	\\
	-I\$(includedir)

libexec_PROGRAMS = \\
$bins

EXTRA_PROGRAMS = \\
$opts

install-\%: \%
	\@\$(NORMAL_INSTALL)
	\$(mkinstalldirs) \$(DESTDIR)\$(libexecdir)
	\@p=\$<; p1=`echo \$\$p|sed 's/\$(EXEEXT)\$\$//'`; \\
	if test -f \$\$p \\
	   || test -f \$\$p1 \\
	; then \\
	  f=`echo "\$\$p1" | sed 's,^.*/,,;\$(transform);s/\$\$/\$(EXEEXT)/'`; \\
	  echo " \$(INSTALL_PROGRAM_ENV) \$(LIBTOOL) --mode=install \$(libexecPROGRAMS_INSTALL) \$\$p \$(DESTDIR)\$(libexecdir)/\$\$f"; \\
	  \$(INSTALL_PROGRAM_ENV) \$(LIBTOOL) --mode=install \$(libexecPROGRAMS_INSTALL) \$\$p \$(DESTDIR)\$(libexecdir)/\$\$f || exit 1; \\
	else :; fi
EOT

print IGNORE <<EOT;
Makefile
Makefile.in
.deps
.libs
EOT

foreach (sort keys %plugins) {
    my $makename = $_;
    my $MAKENAME;
    $makename =~ s/-/_/g;
    $MAKENAME = "\U$makename";

    my $libgimp = "";

    if (exists $plugins{$_}->{ui}) {
        $libgimp .= "\$(libgimpui)";
        $libgimp .= "\t\t\\\n\t\$(libgimpwidgets)";
	$libgimp .= "\t\\\n\t\$(libgimpmodule)";
	$libgimp .= "\t\\\n\t";
    }

    $libgimp .= "\$(libgimp)";
    $libgimp .= "\t\t\\\n\t\$(libgimpmath)";
    $libgimp .= "\t\t\\\n\t\$(libgimpconfig)";
    $libgimp .= "\t\\\n\t\$(libgimpcolor)";
    $libgimp .= "\t\t\\\n\t\$(libgimpbase)";

    my $glib;
    if (exists $plugins{$_}->{ui}) {
	$glib = "\$(GTK_LIBS)"
    } else {
	$glib = "\$(GLIB_LIBS)"
    }

    my $optlib = "";

    if (exists $plugins{$_}->{optional}) {
	if (exists $plugins{$_}->{libs}) {
		$optlib = "\n\t\$(" . $plugins{$_}->{libs} . ")\t\t\\";
	}
    }

    if (exists $plugins{$_}->{cflags}) {
	my $cflags = $plugins{$_}->{cflags};
	my $optflags = $cflags =~ /FLAGS/ ? $cflags : "$MAKENAME\E_CFLAGS";

	print MK <<EOT;

${makename}_CFLAGS = \$($optflags)
EOT
    }

    my $deplib = "\$(RT_LIBS)\t\t\\\n\t\$(INTLLIBS)";
    if (exists $plugins{$_}->{libdep}) {
	my @lib = split(/:/, $plugins{$_}->{libdep});
	foreach $lib (@lib) {
	    $deplib = "\$(\U$lib\E_LIBS)\t\t\\\n\t$deplib";
	}
    }

    print MK <<EOT;

${makename}_SOURCES = \\
	$_.c

${makename}_LDADD = \\
	$libgimp		\\
	$glib		\\$optlib
	$deplib
EOT

    print IGNORE "$_\n";
}

close MK;
close IGNORE;

&write_file($outmk);
&write_file($outignore);

system ("svn", "propset", "-F", $ignorefile, "svn:ignore", ".");
unlink $ignorefile;
