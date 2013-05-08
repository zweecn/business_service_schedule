clear all;
cd E:\Dev\MATLAB7\work\business_uc;
t = [2 4 8 12 18 22 24 27 31 33 35 37 41 43 45 52];
revenueIgnore = [0 0 0 0 0 0 0 0 0 0 500 500 500 500 500 1000];
revenueRandom = [0 0 0 6000 6000 6000 14000 14000 14000 14000 14500 23500 31500 41500 41500 42000];
revenueMinCost = [0 0 0 0 0 0 0 0 0 0 500 500 500 500 500 1000];
revenueMaxProfit = [0 0 0 6000 6000 6000 14000 23000 23000 23000 23500 32500 40500 50500 50500 51000];
costIgnore = [6078 7828 9906 9906 13966 13966 13966 13966 11965 12065 13065 13065 13065 13065 11064 12064];
costRandom = [6078 7828 7908 9393 13453 13453 18202 18202 20280 29323 30323 33489 38238 40252 38251 39251];
costMinCost = [6078 7661 5660 5660 9720 9720 9720 9720 7719 7819 8819 8819 8819 8819 6818 7818];
costMaxProfit = [6078 7661 5660 6113 10173 10173 14922 18088 16087 16287 17287 20453 25202 26785 24784 25784];
profitIgnore = [-6078 -7828 -9906 -9906 -13966 -13966 -13966 -13966 -11965 -12065 -12565 -12565 -12565 -12565 -10564 -11064];
profitRandom = [-6078 -7828 -7908 -3393 -7453 -7453 -4202 -4202 -6280 -15323 -15823 -9989 -6738 1248 3249 2749];
profitMinCost = [-6078 -7661 -5660 -5660 -9720 -9720 -9720 -9720 -7719 -7819 -8319 -8319 -8319 -8319 -6318 -6818];
profitMaxProfit = [-6078 -7661 -5660 -113 -4173 -4173 -922 4912 6913 6713 6213 12047 15298 23715 25716 25216];
test2( t,revenueIgnore,revenueRandom,revenueMinCost,revenueMaxProfit,costIgnore,costRandom,costMinCost,costMaxProfit,profitIgnore,profitRandom,profitMinCost,profitMaxProfit );

% 不作为策略(Ignore Strategy):							
% Time	EventType	EventDetail	ActionType	ActionDetail	Revenue	Cost	Profit
% 2	E6:SERVICE_EXEC_FAILED	[Event: Time:2 Type:SERVICE_EXEC_FAILED_E6 Ins:1 SNode:0]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 1) (FreeRes: type:1 Amt:6 type:6 Amt:15 type:3 Amt:3 type:4 Amt:15 type:7 Amt:3 type:2 Amt:9 type:0 Amt:9)NeedAddRes:0 Amt:80 Revenue:0 Cost:6078 Profit:-6078]	0	6078	-6078
% 4	E5:SERVICE_EXEC_DELAY	[Event: Time:4 Type:SERVICE_EXEC_DELAY_E5 Ins:3 SNode:0 TimeDelay:5]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:1750 Profit:-1750]	0	7828	-7828
% 8	E6:SERVICE_EXEC_FAILED	[Event: Time:8 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:1]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes: type:6 Amt:5 type:3 Amt:1 type:4 Amt:5 type:7 Amt:1 type:2 Amt:3 type:0 Amt:3)NeedAddRes:196608 Amt:17170480 Revenue:0 Cost:2078 Profit:-2078]	0	9906	-9906
% 12	E2:REQUIREMENT_ADD	[Event: Time:12 Type:REQUIREMENT_ADD_E2 Ins:2 ReqVLevel:1 extraWTP:5000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	9906	-9906
% 18	E6:SERVICE_EXEC_FAILED	[Event: Time:18 Type:SERVICE_EXEC_FAILED_E6 Ins:4 SNode:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 4) (FreeRes: type:4 Amt:10 type:7 Amt:2 type:2 Amt:6 type:0 Amt:6)NeedAddRes:40 Amt:13238318 Revenue:0 Cost:4060 Profit:-4060]	0	13966	-13966
% 22	E4:RESOURCE_REDUCE	[Event: Time:22 Type:RESOURCE_REDUCE_E4 ResType:3 Amt:126]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	13966	-13966
% 24	E2:REQUIREMENT_ADD	[Event: Time:24 Type:REQUIREMENT_ADD_E2 Ins:4 ReqVLevel:3 extraWTP:5000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	13966	-13966
% 27	E2:REQUIREMENT_ADD	[Event: Time:27 Type:REQUIREMENT_ADD_E2 Ins:3 ReqVLevel:2 extraWTP:7000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	13966	-13966
% 31	E6:SERVICE_EXEC_FAILED	[Event: Time:31 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:4]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:56 Amt:13238314 Revenue:0 Cost:-2001 Profit:2001]	0	11965	-11965
% 33	E5:SERVICE_EXEC_DELAY	[Event: Time:33 Type:SERVICE_EXEC_DELAY_E5 Ins:2 SNode:4 TimeDelay:2]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:100 Profit:-100]	0	12065	-12065
% 35	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:35 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	500	13065	-12565
% 37	E2:REQUIREMENT_ADD	[Event: Time:37 Type:REQUIREMENT_ADD_E2 Ins:4 ReqVLevel:2 extraWTP:7000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	13065	-12565
% 41	E3:REQUIREMENT_NEW	[Event: Time:41 Type:REQUIREMENT_NEW_E3 Ins:2 Req:[Requirement:10 Qlevel:3 ExpPeriod:0 wtp:5000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	13065	-12565
% 43	E2:REQUIREMENT_ADD	[Event: Time:43 Type:REQUIREMENT_ADD_E2 Ins:3 ReqVLevel:1 extraWTP:9000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	13065	-12565
% 45	E6:SERVICE_EXEC_FAILED	[Event: Time:45 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:7]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:196608 Amt:38141988 Revenue:0 Cost:-2001 Profit:2001]	500	11064	-10564
% 52	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:52 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	1000	12064	-11064
% 随机策略(Random Strategy):							
% Time	EventType	EventDetail	ActionType	ActionDetail	Revenue	Cost	Profit
% 2	E6:SERVICE_EXEC_FAILED	[Event: Time:2 Type:SERVICE_EXEC_FAILED_E6 Ins:1 SNode:0]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 1) (FreeRes: type:1 Amt:6 type:6 Amt:15 type:3 Amt:3 type:4 Amt:15 type:7 Amt:3 type:2 Amt:9 type:0 Amt:9)NeedAddRes:214191592 Amt:5 Revenue:0 Cost:6078 Profit:-6078]	0	6078	-6078
% 4	E5:SERVICE_EXEC_DELAY	[Event: Time:4 Type:SERVICE_EXEC_DELAY_E5 Ins:3 SNode:0 TimeDelay:5]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:1750 Profit:-1750]	0	7828	-7828
% 8	E6:SERVICE_EXEC_FAILED	[Event: Time:8 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:1]	A9:RETRY_SERVICE	[Action:0 Type:RETRY_SERVICE Ins:3 SNode:1 Revenue:0 Cost:80 Profit:-80]	0	7908	-7908
% 12	E2:REQUIREMENT_ADD	[Event: Time:12 Type:REQUIREMENT_ADD_E2 Ins:2 ReqVLevel:1 extraWTP:5000]	A3:RESOURCE_ADD_PLAN	[Action:0 Type:RESOURCE_ADD_PLAN Res:5 Amt:2 Res:1 Amt:2 Res:6 Amt:5 Res:3 Amt:1 Res:4 Amt:5 Res:7 Amt:1 Res:2 Amt:3 Res:0 Amt:3  Revenue:6000 Cost:1485 Profit:4515]	6000	9393	-3393
% 18	E6:SERVICE_EXEC_FAILED	[Event: Time:18 Type:SERVICE_EXEC_FAILED_E6 Ins:4 SNode:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 4) (FreeRes: type:4 Amt:10 type:7 Amt:2 type:2 Amt:6 type:0 Amt:6)NeedAddRes:40 Amt:34209822 Revenue:0 Cost:4060 Profit:-4060]	6000	13453	-7453
% 22	E4:RESOURCE_REDUCE	[Event: Time:22 Type:RESOURCE_REDUCE_E4 ResType:3 Amt:126]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	6000	13453	-7453
% 24	E2:REQUIREMENT_ADD	[Event: Time:24 Type:REQUIREMENT_ADD_E2 Ins:4 ReqVLevel:3 extraWTP:5000]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:4 NextReq:[Requirement:10 Qlevel:3 ExpPeriod:1 wtp:5000] (FreeRes:) Revenue:8000 Cost:4749 Profit:3251]	14000	18202	-4202
% 27	E2:REQUIREMENT_ADD	[Event: Time:27 Type:REQUIREMENT_ADD_E2 Ins:3 ReqVLevel:2 extraWTP:7000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	14000	18202	-4202
% 31	E6:SERVICE_EXEC_FAILED	[Event: Time:31 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:4]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes: type:0 Amt:3)NeedAddRes:56 Amt:34209818 Revenue:0 Cost:2078 Profit:-2078]	14000	20280	-6280
% 33	E5:SERVICE_EXEC_DELAY	[Event: Time:33 Type:SERVICE_EXEC_DELAY_E5 Ins:2 SNode:4 TimeDelay:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 2) (FreeRes:)NeedAddRes:2671176 Amt:4371003 Revenue:0 Cost:9043 Profit:-9043]	14000	29323	-15323
% 35	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:35 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	14500	30323	-15823
% 37	E2:REQUIREMENT_ADD	[Event: Time:37 Type:REQUIREMENT_ADD_E2 Ins:4 ReqVLevel:2 extraWTP:7000]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:4 NextReq:[Requirement:11 Qlevel:2 ExpPeriod:1 wtp:7000] (FreeRes:) Revenue:9000 Cost:3166 Profit:5834]	23500	33489	-9989
% 41	E3:REQUIREMENT_NEW	[Event: Time:41 Type:REQUIREMENT_NEW_E3 Ins:2 Req:[Requirement:10 Qlevel:3 ExpPeriod:0 wtp:5000]]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:2 NextReq:[Requirement:12 Qlevel:3 ExpPeriod:1 wtp:5000] (FreeRes:) Revenue:8000 Cost:4749 Profit:3251]	31500	38238	-6738
% 43	E2:REQUIREMENT_ADD	[Event: Time:43 Type:REQUIREMENT_ADD_E2 Ins:3 ReqVLevel:1 extraWTP:9000]	A5:RESOURCE_TRANS_PLAN	[Action:0 Type:RESOURCE_TRANS_PLAN Ins:0 QLevel:3 Ins:1 QLevel:-1 Ins:2 QLevel:-1  Revenue:10000 Cost:2014 Profit:7986]	41500	40252	1248
% 45	E6:SERVICE_EXEC_FAILED	[Event: Time:45 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:7]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:1 Amt:59113492 Revenue:0 Cost:-2001 Profit:2001]	41500	38251	3249
% 52	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:52 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	42000	39251	2749
% 最小成本策略(MinCost Strategy):						
% Time	EventType	EventDetail	ActionType	ActionDetail	Revenue	Cost	Profit
% 2	E6:SERVICE_EXEC_FAILED	[Event: Time:2 Type:SERVICE_EXEC_FAILED_E6 Ins:1 SNode:0]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 1) (FreeRes: type:1 Amt:6 type:6 Amt:15 type:3 Amt:3 type:4 Amt:15 type:7 Amt:3 type:2 Amt:9 type:0 Amt:9)NeedAddRes:214191592 Amt:5 Revenue:0 Cost:6078 Profit:-6078]	0	6078	-6078
% 4	E5:SERVICE_EXEC_DELAY	[Event: Time:4 Type:SERVICE_EXEC_DELAY_E5 Ins:3 SNode:0 TimeDelay:5]	A8:DELAY_TO_NEXT_PEROID	[Action:0 Type:DELAY_TO_NEXT_PEROID Ins:3 NextReq:[Requirement:10 Qlevel:1 ExpPeriod:1 wtp:78]) (FreeRes: type:6 Amt:5 type:3 Amt:1 type:4 Amt:5 type:7 Amt:1 type:2 Amt:3 type:0 Amt:3) Revenue:0 Cost:1583 Profit:-1583]	0	7661	-7661
% 8	E6:SERVICE_EXEC_FAILED	[Event: Time:8 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:1]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:2 Amt:27656208 Revenue:0 Cost:-2001 Profit:2001]	0	5660	-5660
% 12	E2:REQUIREMENT_ADD	[Event: Time:12 Type:REQUIREMENT_ADD_E2 Ins:2 ReqVLevel:1 extraWTP:5000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	5660	-5660
% 18	E6:SERVICE_EXEC_FAILED	[Event: Time:18 Type:SERVICE_EXEC_FAILED_E6 Ins:4 SNode:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 4) (FreeRes: type:4 Amt:10 type:7 Amt:2 type:2 Amt:6 type:0 Amt:6)NeedAddRes:40 Amt:46006286 Revenue:0 Cost:4060 Profit:-4060]	0	9720	-9720
% 22	E4:RESOURCE_REDUCE	[Event: Time:22 Type:RESOURCE_REDUCE_E4 ResType:3 Amt:126]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	9720	-9720
% 24	E2:REQUIREMENT_ADD	[Event: Time:24 Type:REQUIREMENT_ADD_E2 Ins:4 ReqVLevel:3 extraWTP:5000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	9720	-9720
% 27	E2:REQUIREMENT_ADD	[Event: Time:27 Type:REQUIREMENT_ADD_E2 Ins:3 ReqVLevel:2 extraWTP:7000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	0	9720	-9720
% 31	E6:SERVICE_EXEC_FAILED	[Event: Time:31 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:4]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:56 Amt:46006282 Revenue:0 Cost:-2001 Profit:2001]	0	7719	-7719
% 33	E5:SERVICE_EXEC_DELAY	[Event: Time:33 Type:SERVICE_EXEC_DELAY_E5 Ins:2 SNode:4 TimeDelay:2]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:100 Profit:-100]	0	7819	-7819
% 35	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:35 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	500	8819	-8319
% 37	E2:REQUIREMENT_ADD	[Event: Time:37 Type:REQUIREMENT_ADD_E2 Ins:4 ReqVLevel:2 extraWTP:7000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	8819	-8319
% 41	E3:REQUIREMENT_NEW	[Event: Time:41 Type:REQUIREMENT_NEW_E3 Ins:2 Req:[Requirement:10 Qlevel:3 ExpPeriod:0 wtp:5000]]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	8819	-8319
% 43	E2:REQUIREMENT_ADD	[Event: Time:43 Type:REQUIREMENT_ADD_E2 Ins:3 ReqVLevel:1 extraWTP:9000]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	500	8819	-8319
% 45	E6:SERVICE_EXEC_FAILED	[Event: Time:45 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:7]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:196608 Amt:63045636 Revenue:0 Cost:-2001 Profit:2001]	500	6818	-6318
% 52	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:52 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	1000	7818	-6818
% 最大利润策略(MaxProfit Strategy):						
% Time	EventType	EventDetail	ActionType	ActionDetail	Revenue	Cost	Profit
% 2	E6:SERVICE_EXEC_FAILED	[Event: Time:2 Type:SERVICE_EXEC_FAILED_E6 Ins:1 SNode:0]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 1) (FreeRes: type:1 Amt:6 type:6 Amt:15 type:3 Amt:3 type:4 Amt:15 type:7 Amt:3 type:2 Amt:9 type:0 Amt:9)NeedAddRes:214191592 Amt:5 Revenue:0 Cost:6078 Profit:-6078]	0	6078	-6078
% 4	E5:SERVICE_EXEC_DELAY	[Event: Time:4 Type:SERVICE_EXEC_DELAY_E5 Ins:3 SNode:0 TimeDelay:5]	A8:DELAY_TO_NEXT_PEROID	[Action:0 Type:DELAY_TO_NEXT_PEROID Ins:3 NextReq:[Requirement:10 Qlevel:1 ExpPeriod:1 wtp:78]) (FreeRes: type:6 Amt:5 type:3 Amt:1 type:4 Amt:5 type:7 Amt:1 type:2 Amt:3 type:0 Amt:3) Revenue:0 Cost:1583 Profit:-1583]	0	7661	-7661
% 8	E6:SERVICE_EXEC_FAILED	[Event: Time:8 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:1]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:2 Amt:-65536 Revenue:0 Cost:-2001 Profit:2001]	0	5660	-5660
% 12	E2:REQUIREMENT_ADD	[Event: Time:12 Type:REQUIREMENT_ADD_E2 Ins:2 ReqVLevel:1 extraWTP:5000]	A5:RESOURCE_TRANS_PLAN	[Action:0 Type:RESOURCE_TRANS_PLAN Ins:1 QLevel:-1 Ins:3 QLevel:-1 Res:5 Amt:6 Res:1 Amt:6 Res:6 Amt:15 Res:3 Amt:3 Res:4 Amt:15 Res:7 Amt:3 Res:2 Amt:9 Res:0 Amt:9  Revenue:6000 Cost:453 Profit:5547]	6000	6113	-113
% 18	E6:SERVICE_EXEC_FAILED	[Event: Time:18 Type:SERVICE_EXEC_FAILED_E6 Ins:4 SNode:2]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 4) (FreeRes: type:4 Amt:10 type:7 Amt:2 type:2 Amt:6 type:0 Amt:6)NeedAddRes:40 Amt:2752561 Revenue:0 Cost:4060 Profit:-4060]	6000	10173	-4173
% 22	E4:RESOURCE_REDUCE	[Event: Time:22 Type:RESOURCE_REDUCE_E4 ResType:3 Amt:126]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:0 Profit:0]	6000	10173	-4173
% 24	E2:REQUIREMENT_ADD	[Event: Time:24 Type:REQUIREMENT_ADD_E2 Ins:4 ReqVLevel:3 extraWTP:5000]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:4 NextReq:[Requirement:10 Qlevel:3 ExpPeriod:1 wtp:5000] (FreeRes:) Revenue:8000 Cost:4749 Profit:3251]	14000	14922	-922
% 27	E2:REQUIREMENT_ADD	[Event: Time:27 Type:REQUIREMENT_ADD_E2 Ins:3 ReqVLevel:2 extraWTP:7000]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:3 NextReq:[Requirement:11 Qlevel:2 ExpPeriod:1 wtp:7000] (FreeRes:) Revenue:9000 Cost:3166 Profit:5834]	23000	18088	4912
% 31	E6:SERVICE_EXEC_FAILED	[Event: Time:31 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:4]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:56 Amt:2752557 Revenue:0 Cost:-2001 Profit:2001]	23000	16087	6913
% 33	E5:SERVICE_EXEC_DELAY	[Event: Time:33 Type:SERVICE_EXEC_DELAY_E5 Ins:2 SNode:4 TimeDelay:2]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:0 Cost:200 Profit:-200]	23000	16287	6713
% 35	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:35 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	23500	17287	6213
% 37	E2:REQUIREMENT_ADD	[Event: Time:37 Type:REQUIREMENT_ADD_E2 Ins:4 ReqVLevel:2 extraWTP:7000]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:4 NextReq:[Requirement:12 Qlevel:2 ExpPeriod:1 wtp:7000] (FreeRes:) Revenue:9000 Cost:3166 Profit:5834]	32500	20453	12047
% 41	E3:REQUIREMENT_NEW	[Event: Time:41 Type:REQUIREMENT_NEW_E3 Ins:2 Req:[Requirement:10 Qlevel:3 ExpPeriod:0 wtp:5000]]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:2 NextReq:[Requirement:13 Qlevel:3 ExpPeriod:1 wtp:5000] (FreeRes:) Revenue:8000 Cost:4749 Profit:3251]	40500	25202	15298
% 43	E2:REQUIREMENT_ADD	[Event: Time:43 Type:REQUIREMENT_ADD_E2 Ins:3 ReqVLevel:1 extraWTP:9000]	A4:FORK_NEXT_PERIOD	[Action:0 Type:FORK_NEXT_PERIOD Ins:3 NextReq:[Requirement:14 Qlevel:1 ExpPeriod:1 wtp:9000] (FreeRes:) Revenue:10000 Cost:1583 Profit:8417]	50500	26785	23715
% 45	E6:SERVICE_EXEC_FAILED	[Event: Time:45 Type:SERVICE_EXEC_FAILED_E6 Ins:3 SNode:7]	A6:CANCEL_INSTANCE	[Action:0 Type:CANCEL_INSTANCE (CancelIns: 3) (FreeRes:)NeedAddRes:3 Amt:17170471 Revenue:0 Cost:-2001 Profit:2001]	50500	24784	25716
% 52	E1:REQUIREMENT_CANCEL_REDUCE	[Event: Time:52 Type:REQUIREMENT_CANCEL_REDUCE_E1 Ins:4 ReqVLevel:1]	A1:IGNORE	[Action:0 Type:IGNORE Revenue:500 Cost:1000 Profit:-500]	51000	25784	25216
