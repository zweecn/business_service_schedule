#!/bin/bash

# Author: Vincent

node_count="bs_nodecount.conf"
node_size=`cat $node_count`
max_unit=5

# 0.7
seq_p=7

node_conf="./bs_snode.conf"
temp="./temp"

mkdir $temp

echo "[SNode=(SID, ResType, UnitReqQLevel, ConcurrencyType)]" > $node_conf
column_size=4

echo $node_size'	'$column_size >> $node_conf

seed=`date +%s`

echo $node_size | awk '{
	srand("'$seed'");
	for (i = 0; i < $1; i++) {
		print i "\t" rand();
	}
}' | sort -k2 | cut -f1 > ${temp}/sid


echo $node_size | awk '{
	srand("'$seed'" + 1);
	for (i = 0; i < $1; i++) {
		print i "\t" rand();
	}
}' | sort -k2 | cut -f1 > ${temp}/resType

echo $node_size | awk '{
	srand("'$seed'" + 2);
	for (i = 0; i < $1; i++) {
		print int(rand() * "'$max_unit'") + 1;
	}
}'> ${temp}/unit

echo $node_size | awk '{
	srand("'$seed'" + 3);
	for (i = 0; i < $1; i++) {
		if (rand() * 10 <= "'$seq_p'") {
			print 0;
		} else {
			print 1;
		}
		
	}
}'> ${temp}/con

paste ${temp}/sid ${temp}/resType ${temp}/unit ${temp}/con | sort -k1 >> $node_conf


rm -rf $temp

sz -be $node_conf
sz -be $node_count 

