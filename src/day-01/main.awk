BEGIN { n = 0; p = -log(0); if (w < 1) w = 1 }
{ a[NR] = $1 }
NR >= w { s = 0; for (i = 0; i < w; i++) s += a[NR - i]; if (s > p) n++; p = s }
END { print n }
