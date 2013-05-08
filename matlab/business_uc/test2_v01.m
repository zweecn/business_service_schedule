function [ output_args ] = test2_v01( t,revenueIgnore,revenueRandom,revenueMinCost,revenueMaxProfit,costIgnore,costRandom,costMinCost,costMaxProfit,profitIgnore,profitRandom,profitMinCost,profitMaxProfit )
% Draw test2

subplot(1,3,1);
plot(t, revenueIgnore, 'k:v', t, revenueRandom, 'r-*', t, revenueMinCost, 'b-s',  t, revenueMaxProfit, 'mo-');
% title('Revenue');
xlabel('time');
ylabel('Revenue($)');
% legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)');
% legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)', 'Location','NorthWestOutside');
legend('Ignore', 'Random', 'min(cost)', 'max(profit)', 'Location','NorthWest');
 
subplot(1,3,2);
plot(t, costIgnore, 'k:v', t, costRandom, 'r-*', t, costMinCost, 'b-s', t, costMaxProfit, 'mo-');
% title('Cost');
xlabel('time');
ylabel('Cost($)');
% legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)');
legend('Ignore', 'Random', 'min(cost)', 'max(profit)', 'Location','NorthWest');

subplot(1,3,3);
plot(t, profitIgnore, 'k:v', t, profitRandom, 'r-*', t, profitMinCost, 'b-s', t, profitMaxProfit, 'mo-');
% title('Profit');
xlabel('time');
ylabel('Profit($)');
% legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)');
legend('Ignore', 'Random', 'min(cost)', 'max(profit)', 'Location','NorthWest');