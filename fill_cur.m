
%aporte mario para pintar el area de una curva y hacerla mas visible.
t=[0:.001:2*pi];
y=sin(t);
plot(t, y);
hold on
fill(t, y, 'r');