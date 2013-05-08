function [ output_args ] = test3_1( x, actions, profit, ignore, resAdd, resTrans, forkNext)
% Business UC test3

subplot(2, 1, 1);
name = {'', 'IGNORE', 'RESOURCE_ADD_PLAN', 'RESOURCE_TRANS_PLAN', 'FORK_NEXT_PERIOD', ''};
% xname = {'0', '0.2', '0.4', '0.6', '0.8', '1', '1.2', '1.4', '1.6', '1.8', '2'};
b = bar(x, actions);
ch = get(b, 'children');
axis([-0.1, 1.6, 0, 4]);
set(gca, 'YTickLabel', name);
% set(gca, 'XTickLabel', xname);
xlabel('UnitRCancelCost / UnitRPrice');

subplot(2, 1, 2);
plot(x, profit, 'r-o', x, ignore, 'k-*', x, resAdd, 'b-+', x, resTrans, 'g-^', x, forkNext, 'c-x', 'MarkerSize', 5);
xlabel('UnitRCancelCost / UnitRPrice');
ylabel('Profit');
[ma, mi] = max(profit);
% axis([-0.1, 1.6, ma - 10, mi + 10]);
xlim([-0.1 1.6])

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

