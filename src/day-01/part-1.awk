BEGIN { n = 0; p = -log(0) }
{ if ($1 > p) n++; p = $1 }
END { print n }
