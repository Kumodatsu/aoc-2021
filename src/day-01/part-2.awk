BEGIN { if (w < 1) w = 1 }
{ a[NR] = $1 }
NR >= w { s = 0; for (i = 0; i < w; i++) s += a[NR - i]; print s }
