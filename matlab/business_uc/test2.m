function [ output_args ] = test2( t,revenueIgnore,revenueRandom,revenueMinCost,revenueMaxProfit,costIgnore,costRandom,costMinCost,costMaxProfit,profitIgnore,profitRandom,profitMinCost,profitMaxProfit )
% Draw test2

subplot(1,3,1);
plot(t, revenueIgnore, 'k:v', t, revenueRandom, 'r-*', t, revenueMinCost, 'b-s',  t, revenueMaxProfit, 'mo-', 'MarkerSize', 5);
% title('Revenue');
xlabel('ʱ��');
ylabel('����($)');
% legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)');
% legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)', 'Location','NorthWestOutside');
legend('����Ϊ����', '�������', '��С�ɱ�����', '����������', 'Location','NorthWest');
 
subplot(1,3,2);
plot(t, costIgnore, 'k:v', t, costRandom, 'r-*', t, costMinCost, 'b-s', t, costMaxProfit, 'mo-', 'MarkerSize', 5);
% title('Cost');
xlabel('ʱ��');
ylabel('�ɱ�($)');
% legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)');
legend('����Ϊ����', '�������', '��С�ɱ�����', '����������', 'Location','NorthWest');

subplot(1,3,3);
plot(t, profitIgnore, 'k:v', t, profitRandom, 'r-*', t, profitMinCost, 'b-s', t, profitMaxProfit, 'mo-', 'MarkerSize', 5);
% title('Profit');
xlabel('ʱ��');
ylabel('����($)');
% legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)');
legend('����Ϊ����', '�������', '��С�ɱ�����', '����������', 'Location','NorthWest');