#!/bin/bash

# Author: Vincent

node_count="bs_nodecount.conf"
node_size=`cat $node_count`
max_unit=5
ins_size=5
req_size=$ins_size
req_qlevel_size=$(($ins_size * 2))
max_wtp=100

node_conf="./bs_snode.conf"
res_conf="./bs_resource.conf"
r_conf="./bs_requirement.conf"

temp="./temp"

mkdir $temp

echo "[R= (Customer, QLevel, ExpectedPeriod, WTP)]" > $r_conf
column_size=4
echo $(($req_size * 2))'	'$column_size >> $r_conf

seed=$RANDOM

echo $seed | awk ' BEGIN { 
	req_size = "'$req_size'";
	req_qlevel_size = "'$req_qlevel_size'";
	max_wtp = "'$max_wtp'";
	seed = "'$seed'";
	srand(seed);
} {

	for (i = 0; i < req_size; i++) {
		req[i] = 1;
	}
	for ( ;i < 10; i++) {
		seed += i;
		srand(seed);
		r = int(rand() * req_size);	
		req[r]++;
	}
	for (i = 0; i < req_size; i++) {
		seed += i;
		srand(seed);
		print i "\t" req[i] "\t" 0 "\t" int(rand() * max_wtp);
	}
	for (i = 0; i < req_size; i++) {
		seed += i;
		srand(seed);
		print i+req_size "\t" req[i] "\t" 1 "\t" int(rand() * max_wtp);
	}

}' >> $r_conf

rm -rf $temp

sz -be $r_conf

