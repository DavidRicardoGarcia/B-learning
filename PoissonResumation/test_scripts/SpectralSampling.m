syms t w;

y = heaviside(t)-heaviside(t-0.1);
fplot(y, [-.1 .2]);

Ft = 2*fourier(y, 2*pi*w);

figure;

fplot(abs(Ft), [-2 200]);

hold on;


Ts = 1e-5;

fmax = 1/Ts; % frecuencia maxima hasta donde va la fft

k =.01;

tx = -.1:Ts:k; % vector de tiempo. muestreo a Ts

X = heaviside(tx) - heaviside(tx-.1);

Xw = repmat(X, 1, 50);

N = length(Xw); % numero de muestras
 
N2 = floor(N/2); % mitad del numero de muestras. recordando nyquist,
% solo la mitad de la transformada es de utilidad es decir hasta fmax/2

Fh = fft(Xw); % transformada rapida de fourier

dw = fmax/N; % resolucion en frecuencia de la fft

w = (0:1:N2-1)*dw; % vector de frecuencia

Fhw = abs(Fh);
Fhw(1) = Fhw(1)/N2;
Fhw(2:end) = Fhw(2:end)/N2*(k+.1);

plot(w(1:7000), Fhw(1:7000));

figure;
plot(Xw);

