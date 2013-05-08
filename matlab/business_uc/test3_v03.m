function [ output_args ] = test3( x, actions, profit, wtpX, wtpActions, wtpProfit, delayX, delayActions, delayProfit, kX, kActions, kProfits )
% Business UC test3

figure(1);

subplot(2, 2, 1);
name = {'', 'A1', 'A3', 'A5', 'A4', ''};
b = bar(x, actions);
ch = get(b, 'children');
axis([-0.1, 1.6, 0, 4]);
set(gca, 'YTickLabel', name);
% xlabel('UnitRCancelCost / UnitRPrice');
xlabel('ȡ���⳥/��׼����(��λ��)');
ylabel('��������');
title('(a)','position',[0.75 -1.0]);

subplot(2, 2, 3);
plot(x, profit, 'r-o', 'MarkerSize', 5);
% xlabel('UnitRCancelCost / UnitRPrice');
% ylabel('Profit');
xlabel('ȡ���⳥/��׼����(��λ��)');
ylabel('����');
axis([-0.1, 1.6, min(profit) - 100, max(profit) + 100]);
title('(b)','position',[0.75 1246]);

subplot(2, 2, 2);
name = {'', 'A1', 'A3', 'A5', 'A4', ''};
b = bar(wtpX, wtpActions);
ch = get(b, 'children');
axis([-0.1, 1.6, 0, 4]);
set(gca, 'YTickLabel', name);
% xlabel('extra WTP / UnitRCancelCost');
xlabel('����WTP/ȡ���⳥(��λ��)');
ylabel('��������');
title('(c)','position',[0.75 -1.0]);

subplot(2, 2, 4);
plot(wtpX, wtpProfit, 'r-o', 'MarkerSize', 5);
% xlabel('extra WTP / UnitRCancelCost');
% ylabel('Profit');
xlabel('����WTP/ȡ���⳥(��λ��)');
ylabel('����');
axis([-0.1, 1.6, min(wtpProfit) - 100, max(wtpProfit) + 100]);
title('(d)','position',[0.75 -420]);


figure(2);

subplot(2, 2, 1);
name = {'', 'A1', 'A6', 'A8', ''};
b = bar(delayX, delayActions);
ch = get(b, 'children');
axis([-0.1, 1.1, 0, 4]);
set(gca, 'YTickLabel', name);
% xlabel('UnitTimeDelayCost / UnitDelayCost');
xlabel('�ӳٲ���/�����Ƴٲ���(��λ��)');
ylabel('��������');
title('(a)','position',[0.5 -1.0]);

subplot(2, 2, 3);
plot(delayX, delayProfit, 'r-o', 'MarkerSize', 5);
% xlabel('UnitTimeDelayCost / UnitDelayCost');
% ylabel('Profit');
xlabel('�ӳٲ���/�����Ƴٲ���(��λ��)');
ylabel('����');
axis([-0.1, 1.1, min(delayProfit) - 500, max(delayProfit) + 500]);
title('(b)','position',[0.5 -6720]);

subplot(2, 2, 2);
name = {'', 'A1', 'A6', 'A8', ''};
b = bar(kX, kActions);
ch = get(b, 'children');
axis([-0.1, 3.1, 0, 4]);
set(gca, 'YTickLabel', name);
% xlabel('k');
xlabel('k(ϵ��)');
ylabel('��������');
title('(c)','position',[1.5 -1.0]);

subplot(2, 2, 4);
plot(kX, kProfits, 'r-o', 'MarkerSize', 5);
% xlabel('k');
% ylabel('Profit');
xlabel('k(ϵ��)');
ylabel('����');
axis([-0.1, 3.1, min(kProfits) - 500, max(kProfits) + 500]);
title('(d)','position',[1.5 -8400]);

