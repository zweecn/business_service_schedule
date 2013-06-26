#!/bin/bash

# Author: Vincent

node_count="bs_nodecount.conf"
node_size=`cat $node_count`
max_unit=5
ins_size=5
req_qlevel_size=$(($ins_size * 2))
min_amount=$(($req_qlevel_size * $max_unit))
max_amount=$(($min_amount * 3 / 2))
min_price=10
max_price=100

res_conf="./bs_resource.conf"
temp="./temp"

mkdir $temp

echo "[Resource = (Period, ResType, TotalQLevel, Price)]" > $res_conf
column_size=4
echo $node_size'	'$column_size >> $res_conf


make_res()
{
	perid=$1
	seed=$((`date +%s` + $1))

	echo $node_size | awk '{
		srand("'$seed'");
		for (i = 0; i < $1; i++) {
			print "'$perid'";
		}
	}' > ${temp}/p

	echo $node_size | awk '{
		srand("'$seed'" + 1);
		for (i = 0; i < $1; i++) {
			print i "\t" rand();
		}
	}' | sort -k2 | cut -f1 > ${temp}/resType

	echo $node_size | awk '{
		srand("'$seed'" + 2);
		for (i = 0; i < $1; i++) {
			print int(rand() * "'$max_amount'") + "'$min_amount'";
		}
	}'> ${temp}/t

	echo $node_size | awk '{
		srand("'$seed'" + 3);
		for (i = 0; i < $1; i++) {
			print int(rand() * "'$max_price'") + "'$min_price'";
		}
	}'> ${temp}/price


	paste ${temp}/p ${temp}/resType ${temp}/t ${temp}/price  > $2

}

make_res 0 ${temp}/res1
make_res 1 ${temp}/res2

cat ${temp}/res1 ${temp}/res2 >> $res_conf


rm -rf $temp

sz -be $res_conf
sz -be $node_count
