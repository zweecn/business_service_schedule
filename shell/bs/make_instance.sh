#!/bin/bash

# Author: Vincent

node_count="bs_nodecount.conf"
node_size=`cat $node_count`
max_unit=5
ins_size=5
req_size=$ins_size
req_qlevel_size=$(($ins_size * 2))
max_wtp=100

max_node_runtime=10

node_conf="./bs_snode.conf"
res_conf="./bs_resource.conf"
r_conf="./bs_requirement.conf"
ins_conf="./bs_instance.conf"

temp="./temp"

mkdir $temp

echo "[Instance = (InstanceID, RequirementID, SNodePlanList{(SID, StartTime, EndTime)})]" > $ins_conf
echo $ins_size >> $ins_conf

echo $ins_size | awk '{
	ins_size = "'$ins_size'";
	for (i = 0; i < ins_size; i++) {
		print i "\t" i;
	}
}' >> $ins_conf

column_size=4

seed=$RANDOM

echo "[SNodePlanList:SNodeID, ConcurrencyType, instance1.startTime->endTime, instance2.startTime->endTime...]" >> $ins_conf
echo $node_size >> $ins_conf

awk -F '\t' '{
	if (FILENAME == ARGV[1]) {
		if (NF == 4) {
			conType[$1] = $4;			
		}
	}

} END {
	seed = "'$seed'";
	srand(seed);
	ins_size = "'$ins_size'";
	max_node_runtime="'$max_node_runtime'";
	
	for (i = 0; i < length(conType); i++) {
		printf i "\t" conType[i];
		if (conType[i] == 0) {
			for (j = 0; j < ins_size; j++) {
				startTime[i][j] = endTime[i-1][j];
				endTime[i][j] = startTime[i][j] + int(rand() * max_node_runtime) + 1;
			}
		} else {
			for (j = 0; j < ins_size; j++) {
				if (maxEndTime < endTime[i-1][j]) {
					maxEndTime = endTime[i-1][j];
				}
			}
			publicStartTime = maxEndTime;
			publicEndTime =  publicStartTime + int(rand() * max_node_runtime) + 1;
			for (j = 0; j < ins_size; j++) {
				startTime[i][j] = publicStartTime;
				endTime[i][j] = publicEndTime;
			}
		}
		for (j = 0; j < ins_size; j++) {
			if (startTime[i][j] == "") {
				startTime[i][j] = 0;
			}
			printf "\t" startTime[i][j] "->" endTime[i][j];
		}
		printf "\n";
	}

}' $node_conf >> $ins_conf


rm -rf $temp

sz -be $ins_conf

