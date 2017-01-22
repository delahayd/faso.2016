#!/usr/bin/perl
print "Content-type: text/html\n\n";
system "./temperature";
print "<HTML>";
print "<BODY>";
print "<P>Bonjour</P>";
print "<a href='http://www.jamesterrien.fr/controller/Controller_Page_Dashboard.php'> Continuer </a>";
print "</BODY>";
print "</HTML>";
