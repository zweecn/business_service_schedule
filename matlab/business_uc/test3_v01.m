function [ output_args ] = test3_v01( x, actions, profit, wtpX, wtpActions, wtpProfit, delayX, delayActions, delayProfit, kX, kActions, kProfits )
% Business UC test3

figure(1);

subplot(2, 2, 1);
name = {'', 'A1', 'A3', 'A5', 'A4', ''};
% xname = {'0', '0.2', '0.4', '0.6', '0.8', '1', '1.2', '1.4', '1.6', '1.8', '2'};
b = bar(x, actions);
ch = get(b, 'children');
axis([-0.1, 1.6, 0, 4]);
set(gca, 'YTickLabel', name);
% set(gca, 'XTickLabel', xname);
xlabel('UnitRCancelCost / UnitRPrice');
% title('(a)');
title('(a)','position',[0.75 -1.0]);

subplot(2, 2, 3);
plot(x, profit, 'r-o', 'MarkerSize', 5);
xlabel('UnitRCancelCost / UnitRPrice');
ylabel('Profit');
% xlim([-0.1 1.6])
axis([-0.1, 1.6, min(profit) - 100, max(profit) + 100]);
%title('(d)');
title('(b)','position',[0.75 1250]);

subplot(2, 2, 2);
name = {'', 'A1', 'A3', 'A5', 'A4', ''};
% xname = {'0', '0.2', '0.4', '0.6', '0.8', '1', '1.2', '1.4', '1.6', '1.8', '2'};
b = bar(wtpX, wtpActions);
ch = get(b, 'children');
axis([-0.1, 1.6, 0, 4]);
set(gca, 'YTickLabel', name);
% set(gca, 'XTickLabel', xname);
xlabel('extra WTP / UnitRCancelCost');
% title('(b)');
title('(c)','position',[0.75 -1.0]);

subplot(2, 2, 4);
plot(wtpX, wtpProfit, 'r-o', 'MarkerSize', 5);
xlabel('extra WTP / UnitRCancelCost');
ylabel('Profit');
% axis([-0.1, 1.6, ma - 10, mi + 10]);
% xlim([-0.1 1.6])
axis([-0.1, 1.6, min(wtpProfit) - 100, max(wtpProfit) + 100]);
% title('(e)');
title('(d)','position',[0.75 -420]);


figure(2);

subplot(2, 2, 1);
name = {'', 'A1', 'A6', 'A8', ''};
% xname = {'0', '0.2', '0.4', '0.6', '0.8', '1', '1.2', '1.4', '1.6', '1.8', '2'};
b = bar(delayX, delayActions);
ch = get(b, 'children');
axis([-0.1, 1.1, 0, 4]);
set(gca, 'YTickLabel', name);
% set(gca, 'XTickLabel', xname);
xlabel('UnitTimeDelayCost / UnitDelayCost');
% title('(c)');
title('(a)','position',[0.5 -1.0]);

subplot(2, 2, 3);
plot(delayX, delayProfit, 'r-o', 'MarkerSize', 5);
xlabel('UnitTimeDelayCost / UnitDelayCost');
ylabel('Profit');
% axis([-0.1, 1.6, ma - 10, mi + 10]);
% xlim([-0.1 1.6])
axis([-0.1, 1.1, min(delayProfit) - 500, max(delayProfit) + 500]);
% title('(f)');
title('(b)','position',[0.5 -6720]);

subplot(2, 2, 2);
name = {'', 'A1', 'A6', 'A8', ''};
% xname = {'0', '0.2', '0.4', '0.6', '0.8', '1', '1.2', '1.4', '1.6', '1.8', '2'};
b = bar(kX, kActions);
ch = get(b, 'children');
axis([-0.1, 3.1, 0, 4]);
set(gca, 'YTickLabel', name);
% set(gca, 'XTickLabel', xname);
xlabel('k');
% title('(c)');
title('(c)','position',[1.5 -1.0]);

subplot(2, 2, 4);
plot(kX, kProfits, 'r-o', 'MarkerSize', 5);
xlabel('k');
ylabel('Profit');
% axis([-0.1, 1.6, ma - 10, mi + 10]);
% xlim([-0.1 1.6])
axis([-0.1, 3.1, min(kProfits) - 500, max(kProfits) + 500]);
% title('(j)');
title('(d)','position',[1.5 -8800]);

% plot(x0, a0, 'r-*', x1, a1, 'b-o');
% xlabel('Punishment / Total Price');
% ylabel('Action');
% legend('Markov', 'Greedy');
% axis([0, 2 , 0, 6]);
% text(0, 2, 'Stop')
% text(0, 3, 'Retry')
% text(0, 4, 'Substitute')
% text(0, 5, 'Re-composite')
% subplot(2, 1, 2);
% plot(x0, r0, 'r-*', x1, r1, 'b-o');
% xlabel('Punishment / Total Price');
% ylabel('Reward');
% legend('Markov', 'Greedy');

