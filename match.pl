#!/usr/bin/perl
use strict;
use warnings;

sub print_usage
{
    print "Usage: match.pl <filename>\n";
}

# Check that we have exactly one argument (the file name)
if ( $#ARGV != 0 )
{
    print_usage ();
}

my $is_debug=0;
if ( $0 =~ m/match.pl/ )
{
    $is_debug=1;
}

my $in_filename=$ARGV[0];
$in_filename =~ m/([a-zA-Z0-9]*)(_{0,})-([a-zA-Z0-9]+)\.([a-zA-Z0-9]+)/;

# This is to aid debugging : when run as rename/.rename, do not take debug actions
# described in this if clause 
# FIXME: Reverse this condition, so that debug code runs _unless_ the name
#        is rename or .rename
if ( $is_debug )
{
#   DEBUG code goes here ...
    print $1 . "\n";
    print $2 . "\n";
    print $3 . "\n";
    print $4 . "\n";
}

if ((defined $1) && (defined $4))
{
    print "$1.$4";
}
