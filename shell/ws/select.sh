#!/bin/bash

# Author: Vincent

iconv -f gbk -t utf-8 history.log > his_utf8

#awk -F '\t' '{
#	print rand() "\t" $0;
#}' his_utf8 | sort -k1 -n | cut -f2- | head -n 20

awk -F '\t' 'BEGIN {
	cnt = 0;
}{
	cur = $4;
	if (cur != prev) {
		cnt++;
	}
	print cnt "\t" $0;
	prev = cur;
}' his_utf8 | sort -k1 -k6 -n | cut -f2- | awk -F '\t' '{
	cur = $4;
	res = index($3, "N");
	if (cur != prev && res == 0) {
		print;
	}
	prev = cur;
}' 

#| sort -k5 -n | head -n 20 | sort -k1 -n

#| awk -F '\t' '{
#	seed = "'$RANDOM'";
#}{
#	#srand(seed);
#	print rand() "\t" $0;
#}' | sort -k1 -n | cut -f2- | head -n 20 | sort -k1 -n

#awk '{
#	print int(rand() * 4);
#
#}' his_utf8
