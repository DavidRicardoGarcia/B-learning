
Ts = 1e-4;
fmax = 1/Ts;

tx = 0:Ts:2;

y = sin(2*pi*32*tx)+2+cos(120*2*pi*tx);

N = length(tx);
N2 = floor(N/2);

H = fft(y);
A = abs(H);

A(1) = A(1)/N; 
A(2:end) = A(2:end)/N2;
 

dw = fmax/N;
w = (0:1:N-1)*dw;

plot(w, A);


figure;

syms t wf;

yt = sin(2*pi*32*t)+2+cos(120*2*pi*t);

Fx = fourier(yt, wf*2*pi);

fplot(Fx, [-1 200]);
