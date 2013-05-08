function [ output_args ] = test2( t,revenueIgnore,revenueRandom,revenueMinCost,revenueMaxProfit )
% Draw test

plot(t, revenueIgnore, 'k-*', t, revenueRandom, 'r:+', t, revenueMinCost, 'b-.',  t, revenueMaxProfit, 'mo-');
title('Revenue');
xlabel('time');
ylabel('Money');
%legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)');
legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)', 'Location','NorthWestOutside');
%legend('Ignore', 'Random', 'max(-cost)', 'max(revenue-cost)', 'Location','NorthWest');
 
