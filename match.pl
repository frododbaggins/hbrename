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
if ( !($0 =~ m/rename/) )
{
    $is_debug=1;
}

my $in_filename=$ARGV[0];
my $sanity_regex = '(\w+)(-{1,})(\w+)\.([a-zA-Z0-9]+)';

$in_filename =~ m/$sanity_regex/;

# This is to aid debugging : when run as rename/.rename, do not take debug actions
# described in this if clause 
if ( $is_debug )
{
#   DEBUG code goes here ...

}

# Sanity TC
if ($1 && $4)
{
    print "$1.$4";
}
