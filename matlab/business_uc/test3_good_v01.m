clear all;
cd E:\Dev\MATLAB7\work\business_uc;x = [0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 1.1 1.2 1.3 1.4 1.5];
actions = [3 3 3 3 3 2 2 2 2 2 2 2 2 2 2 2];
profit = [1957 1857 1757 1658 1557 1515 1515 1515 1515 1515 1515 1515 1515 1515 1515 1515];
wtpX = [0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 1.1 1.2 1.3 1.4 1.5];
wtpActions = [1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 2];
wtpProfit = [0 0 0 0 0 15 114 214 315 415 515 615 714 815 914 1015];
delayX = [0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1];
delayActions = [1 1 3 3 3 3 3 3 3 3 3];
delayProfit = [0 -4000 -4749 -4749 -4749 -4749 -4749 -4749 -4749 -4749 -4749];
kX = [0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2 2.1 2.2 2.3 2.4 2.5 2.6 2.7 2.8 2.9 3];
kActions = [1 1 1 1 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 2 2 2 2 2 2 2 2 2];
kProfits = [0 -1100 -2300 -3500 -4029 -4149 -4266 -4386 -4509 -4629 -4749 -4869 -4986 -5109 -5226 -5349 -5469 -5586 -5709 -5826 -5949 -6069 -6078 -6078 -6078 -6078 -6078 -6078 -6078 -6078 -6078];
test3(x, actions, profit, wtpX, wtpActions, wtpProfit, delayX, delayActions, delayProfit, kX, kActions, kProfits);