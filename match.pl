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

my $in_filename=$ARGV[0];
$in_filename =~ m/([a-zA-Z0-9]+)_{0,}-([a-zA-Z0-9]+)\.([a-zA-Z0-9]+)/;
print "$1.$3";
