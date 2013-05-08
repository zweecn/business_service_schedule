% ======================================================================
% DateTime: 2013.05.08 16:47:45
% MatlabCmd:
clear all;
cd E:\Dev\MATLAB7\work\business_uc;
t = [2 6 10 14 19 21 26 29 31 33 35 37 39 41 43 45];
revenueIgnore = [0 0 0 500 500 500 500 500 500 500 1000 1000 1500 1500 1500 1500];
revenueRandom = [0 10000 10000 10500 10500 10500 10500 10500 10500 18500 19000 19000 19500 19500 19500 19500];
revenueMinCost = [0 0 0 500 500 500 500 500 500 500 1000 1000 1500 1500 1500 1500];
revenueMaxProfit = [0 10000 10000 10500 10500 20500 20500 20500 20500 28500 29000 34000 34500 34500 34500 34500];
costIgnore = [0 0 2078 3078 5121 5121 6975 4974 4974 4974 5974 5974 6974 6974 6974 13052];
costRandom = [0 6332 6412 7412 9455 9455 9455 11533 11533 11533 12533 12533 13533 13533 13533 19611];
costMinCost = [0 0 80 1080 3123 3123 2100 99 99 99 1099 1099 2099 2099 2099 8177];
costMaxProfit = [0 6332 6412 7412 9455 11038 11038 13116 13116 13116 14116 15699 16699 16699 16699 22777];
profitIgnore = [0 0 -2078 -2578 -4621 -4621 -6475 -4474 -4474 -4474 -4974 -4974 -5474 -5474 -5474 -11552];
profitRandom = [0 3668 3588 3088 1045 1045 1045 -1033 -1033 6967 6467 6467 5967 5967 5967 -111];
profitMinCost = [0 0 -80 -580 -2623 -2623 -1600 401 401 401 -99 -99 -599 -599 -599 -6677];
profitMaxProfit = [0 3668 3588 3088 1045 9462 9462 7384 7384 15384 14884 18301 17801 17801 17801 11723];
test2( t,revenueIgnore,revenueRandom,revenueMinCost,revenueMaxProfit,costIgnore,costRandom,costMinCost,costMaxProfit,profitIgnore,profitRandom,profitMinCost,profitMaxProfit );
% Log:
% Test2:
% 不作为策略(Ignore Strategy):
% Time	EventType	EventDetail	ActionType	ActionDetail	Revenue	Cost	Profit
% 2	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:2 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:1 ReqVLevel:0]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	0	0
% 6	E3:REQUIREMENT_NEW	[Event: Time:6 Type:REQUIREMENT_NEW_E3 Ins:1 Req:[Requirement:10 Qlevel:4 ExpPeriod:0 wtp:6000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	0	0
% 10	E6:SERVICE_EXEC_FAILED	[Event: Time:10 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:1]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes: type:6 Amt:5 type:3 Amt:1 type:4 Amt:5 type:7 Amt:1 type:2 Amt:3 type:0 Amt:3)NeedAddRes:11403264 Amt:4063280 Revenue:0 Cost:2078 Profit:-2078]	0	2078	-2078
% 14	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:14 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	500	3078	-2578
% 19	E6:SERVICE_EXEC_FAILED	[Event: Time:19 Type:SERVICE_EXEC_FAILED_E6 Ins:2 SNode:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 2) (FreeRes: type:4 Amt:5 type:7 Amt:1 type:2 Amt:3 type:0 Amt:3)NeedAddRes:40 Amt:7995438 Revenue:0 Cost:2043 Profit:-2043]	500	5121	-4621
% 21	E3:REQUIREMENT_NEW	[Event: Time:21 Type:REQUIREMENT_NEW_E3 Ins:4 Req:[Requirement:11 Qlevel:1 ExpPeriod:0 wtp:9000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	5121	-4621
% 26	E4:RESOURCE_REDUCE	[Event: Time:26 Type:RESOURCE_REDUCE_E4 ResType:1 Amt:4]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 0 2 3) (FreeRes:)NeedAddRes:1 Amt:-2 Revenue:0 Cost:1854 Profit:-1854]	500	6975	-6475
% 29	E6:SERVICE_EXEC_FAILED	[Event: Time:29 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:3]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:1 Amt:11927595 Revenue:0 Cost:-2001 Profit:2001]	500	4974	-4474
% 31	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:31 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:0]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	4974	-4474
% 33	E3:REQUIREMENT_NEW	[Event: Time:33 Type:REQUIREMENT_NEW_E3 Ins:4 Req:[Requirement:12 Qlevel:0 ExpPeriod:0 wtp:8000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	4974	-4474
% 35	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:35 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	1000	5974	-4974
% 37	E2:REQUIREMENT_ADD	[Event: Time:37 Type:REQUIREMENT_ADD_E2 Ins:0 ReqVLevel:1 extraWTP:4000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	1000	5974	-4974
% 39	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:39 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	1500	6974	-5474
% 41	E4:RESOURCE_REDUCE	[Event: Time:41 Type:RESOURCE_REDUCE_E4 ResType:7 Amt:14]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	1500	6974	-5474
% 43	E4:RESOURCE_REDUCE	[Event: Time:43 Type:RESOURCE_REDUCE_E4 ResType:0 Amt:38]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	1500	6974	-5474
% 45	E6:SERVICE_EXEC_FAILED	[Event: Time:45 Type:SERVICE_EXEC_FAILED_E6 Ins:1 SNode:7]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 1) (FreeRes:)NeedAddRes:1 Amt:25034787 Revenue:0 Cost:6078 Profit:-6078]	1500	13052	-11552
% 随机策略(Random Strategy):
% Time	EventType	EventDetail	ActionType	ActionDetail	Revenue	Cost	Profit
% 2	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:2 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:1 ReqVLevel:0]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	0	0
% 6	E3:REQUIREMENT_NEW	[Event: Time:6 Type:REQUIREMENT_NEW_E3 Ins:1 Req:[Requirement:10 Qlevel:4 ExpPeriod:0 wtp:6000]]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:1 NextReq:[Requirement:10 Qlevel:4 ExpPeriod:1 wtp:6000] (FreeRes: type:1 Amt:6 type:6 Amt:15 type:3 Amt:3 type:4 Amt:15 type:7 Amt:3 type:2 Amt:9 type:0 Amt:9) Revenue:10000 Cost:6332 Profit:3668]	10000	6332	3668
% 10	E6:SERVICE_EXEC_FAILED	[Event: Time:10 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:1]	A9:RETRY_SERVICE	[Action:0 Type:RETRY_SERVICE Ins:3 SNode:1 Revenue:0 Cost:80 Profit:-80]	10000	6412	3588
% 14	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:14 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	10500	7412	3088
% 19	E6:SERVICE_EXEC_FAILED	[Event: Time:19 Type:SERVICE_EXEC_FAILED_E6 Ins:2 SNode:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 2) (FreeRes: type:4 Amt:5 type:7 Amt:1 type:2 Amt:3 type:0 Amt:3)NeedAddRes:40 Amt:6684702 Revenue:0 Cost:2043 Profit:-2043]	10500	9455	1045
% 21	E3:REQUIREMENT_NEW	[Event: Time:21 Type:REQUIREMENT_NEW_E3 Ins:4 Req:[Requirement:11 Qlevel:1 ExpPeriod:0 wtp:9000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	10500	9455	1045
% 26	E4:RESOURCE_REDUCE	[Event: Time:26 Type:RESOURCE_REDUCE_E4 ResType:1 Amt:4]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	10500	9455	1045
% 29	E6:SERVICE_EXEC_FAILED	[Event: Time:29 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:3]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes: type:0 Amt:3)NeedAddRes:1 Amt:35520539 Revenue:0 Cost:2078 Profit:-2078]	10500	11533	-1033
% 31	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:31 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:0]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	10500	11533	-1033
% 33	E3:REQUIREMENT_NEW	[Event: Time:33 Type:REQUIREMENT_NEW_E3 Ins:4 Req:[Requirement:12 Qlevel:0 ExpPeriod:0 wtp:8000]]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:4 NextReq:[Requirement:11 Qlevel:0 ExpPeriod:1 wtp:8000] (FreeRes:) Revenue:8000 Cost:0 Profit:8000]	18500	11533	6967
% 35	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:35 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	19000	12533	6467
% 37	E2:REQUIREMENT_ADD	[Event: Time:37 Type:REQUIREMENT_ADD_E2 Ins:0 ReqVLevel:1 extraWTP:4000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	19000	12533	6467
% 39	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:39 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	19500	13533	5967
% 41	E4:RESOURCE_REDUCE	[Event: Time:41 Type:RESOURCE_REDUCE_E4 ResType:7 Amt:14]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	19500	13533	5967
% 43	E4:RESOURCE_REDUCE	[Event: Time:43 Type:RESOURCE_REDUCE_E4 ResType:0 Amt:38]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	19500	13533	5967
% 45	E6:SERVICE_EXEC_FAILED	[Event: Time:45 Type:SERVICE_EXEC_FAILED_E6 Ins:1 SNode:7]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 1) (FreeRes:)NeedAddRes:1 Amt:42074131 Revenue:0 Cost:6078 Profit:-6078]	19500	19611	-111
% 最小成本策略(MinCost Strategy):
% Time	EventType	EventDetail	ActionType	ActionDetail	Revenue	Cost	Profit
% 2	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:2 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:1 ReqVLevel:0]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	0	0
% 6	E3:REQUIREMENT_NEW	[Event: Time:6 Type:REQUIREMENT_NEW_E3 Ins:1 Req:[Requirement:10 Qlevel:4 ExpPeriod:0 wtp:6000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	0	0
% 10	E6:SERVICE_EXEC_FAILED	[Event: Time:10 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:1]	A9:RETRY_SERVICE	[Action:0 Type:RETRY_SERVICE Ins:3 SNode:1 Revenue:0 Cost:80 Profit:-80]	0	80	-80
% 14	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:14 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	500	1080	-580
% 19	E6:SERVICE_EXEC_FAILED	[Event: Time:19 Type:SERVICE_EXEC_FAILED_E6 Ins:2 SNode:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 2) (FreeRes: type:4 Amt:5 type:7 Amt:1 type:2 Amt:3 type:0 Amt:3)NeedAddRes:40 Amt:43384846 Revenue:0 Cost:2043 Profit:-2043]	500	3123	-2623
% 21	E3:REQUIREMENT_NEW	[Event: Time:21 Type:REQUIREMENT_NEW_E3 Ins:4 Req:[Requirement:11 Qlevel:1 ExpPeriod:0 wtp:9000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	3123	-2623
% 26	E4:RESOURCE_REDUCE	[Event: Time:26 Type:RESOURCE_REDUCE_E4 ResType:1 Amt:4]	A7:CANCEL_DELAY_NEXT_PEROID	[Action:0 Type:CANCEL_DELAY_NEXT_PEROID (CancelIns: 2 3) (FreeOrNeedRes:)NeedAddRes:1 Amt:2 Revenue:0 Cost:-1023 Profit:1023]	500	2100	-1600
% 29	E6:SERVICE_EXEC_FAILED	[Event: Time:29 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:3]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:1 Amt:56492043 Revenue:0 Cost:-2001 Profit:2001]	500	99	401
% 31	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:31 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:0]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	99	401
% 33	E3:REQUIREMENT_NEW	[Event: Time:33 Type:REQUIREMENT_NEW_E3 Ins:4 Req:[Requirement:12 Qlevel:0 ExpPeriod:0 wtp:8000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	99	401
% 35	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:35 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	1000	1099	-99
% 37	E2:REQUIREMENT_ADD	[Event: Time:37 Type:REQUIREMENT_ADD_E2 Ins:0 ReqVLevel:1 extraWTP:4000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	1000	1099	-99
% 39	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:39 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	1500	2099	-599
% 41	E4:RESOURCE_REDUCE	[Event: Time:41 Type:RESOURCE_REDUCE_E4 ResType:7 Amt:14]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	1500	2099	-599
% 43	E4:RESOURCE_REDUCE	[Event: Time:43 Type:RESOURCE_REDUCE_E4 ResType:0 Amt:38]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	1500	2099	-599
% 45	E6:SERVICE_EXEC_FAILED	[Event: Time:45 Type:SERVICE_EXEC_FAILED_E6 Ins:1 SNode:7]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 1) (FreeRes:)NeedAddRes:1 Amt:65667075 Revenue:0 Cost:6078 Profit:-6078]	1500	8177	-6677
% 最大利润策略(MaxProfit Strategy):
% Time	EventType	EventDetail	ActionType	ActionDetail	Revenue	Cost	Profit
% 2	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:2 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:1 ReqVLevel:0]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	0	0
% 6	E3:REQUIREMENT_NEW	[Event: Time:6 Type:REQUIREMENT_NEW_E3 Ins:1 Req:[Requirement:10 Qlevel:4 ExpPeriod:0 wtp:6000]]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:1 NextReq:[Requirement:10 Qlevel:4 ExpPeriod:1 wtp:6000] (FreeRes: type:1 Amt:6 type:6 Amt:15 type:3 Amt:3 type:4 Amt:15 type:7 Amt:3 type:2 Amt:9 type:0 Amt:9) Revenue:10000 Cost:6332 Profit:3668]	10000	6332	3668
% 10	E6:SERVICE_EXEC_FAILED	[Event: Time:10 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:1]	A9:RETRY_SERVICE	[Action:0 Type:RETRY_SERVICE Ins:3 SNode:1 Revenue:0 Cost:80 Profit:-80]	10000	6412	3588
% 14	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:14 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	10500	7412	3088
% 19	E6:SERVICE_EXEC_FAILED	[Event: Time:19 Type:SERVICE_EXEC_FAILED_E6 Ins:2 SNode:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 2) (FreeRes: type:4 Amt:5 type:7 Amt:1 type:2 Amt:3 type:0 Amt:3)NeedAddRes:40 Amt:2752561 Revenue:0 Cost:2043 Profit:-2043]	10500	9455	1045
% 21	E3:REQUIREMENT_NEW	[Event: Time:21 Type:REQUIREMENT_NEW_E3 Ins:4 Req:[Requirement:11 Qlevel:1 ExpPeriod:0 wtp:9000]]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:4 NextReq:[Requirement:11 Qlevel:1 ExpPeriod:1 wtp:9000] (FreeRes: type:7 Amt:1 type:2 Amt:3 type:0 Amt:3) Revenue:10000 Cost:1583 Profit:8417]	20500	11038	9462
% 26	E4:RESOURCE_REDUCE	[Event: Time:26 Type:RESOURCE_REDUCE_E4 ResType:1 Amt:4]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	20500	11038	9462
% 29	E6:SERVICE_EXEC_FAILED	[Event: Time:29 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:3]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes: type:0 Amt:3)NeedAddRes:1 Amt:5373998 Revenue:0 Cost:2078 Profit:-2078]	20500	13116	7384
% 31	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:31 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:0]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	20500	13116	7384
% 33	E3:REQUIREMENT_NEW	[Event: Time:33 Type:REQUIREMENT_NEW_E3 Ins:4 Req:[Requirement:12 Qlevel:0 ExpPeriod:0 wtp:8000]]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:4 NextReq:[Requirement:12 Qlevel:0 ExpPeriod:1 wtp:8000] (FreeRes:) Revenue:8000 Cost:0 Profit:8000]	28500	13116	15384
% 35	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:35 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	29000	14116	14884
% 37	E2:REQUIREMENT_ADD	[Event: Time:37 Type:REQUIREMENT_ADD_E2 Ins:0 ReqVLevel:1 extraWTP:4000]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:0 NextReq:[Requirement:13 Qlevel:1 ExpPeriod:1 wtp:4000] (FreeRes:) Revenue:5000 Cost:1583 Profit:3417]	34000	15699	18301
% 39	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:39 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	34500	16699	17801
% 41	E4:RESOURCE_REDUCE	[Event: Time:41 Type:RESOURCE_REDUCE_E4 ResType:7 Amt:14]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	34500	16699	17801
% 43	E4:RESOURCE_REDUCE	[Event: Time:43 Type:RESOURCE_REDUCE_E4 ResType:0 Amt:38]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	34500	16699	17801
% 45	E6:SERVICE_EXEC_FAILED	[Event: Time:45 Type:SERVICE_EXEC_FAILED_E6 Ins:1 SNode:7]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 1) (FreeRes:)NeedAddRes:1 Amt:15859750 Revenue:0 Cost:6078 Profit:-6078]	34500	22777	11723
% ======================================================================
