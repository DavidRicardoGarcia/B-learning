% En este script se genera una grafica en R3 que permite relacionar
% cada harmonico en el tiempo como curva parametrica en un eje y en
% otro eje la amplitud  en el dominio de la frecuencia.


% En la primera parte del script se hace el calculo
% de los harmonicos de la señal y sus correspondiente fases.

% en la segunda parte se grafica la señal original, los armonicos
% en el dominio del tiempo y de la frecuencia y la respuesta
% en fase en R3 como curvas parametricas.

%%%%>>>>>

% se crea la variable de tiempo como variable simbolica
% para poder graficar usando la funcion ezplot directamente.
% y ademas poder hacer calculos simbolicos
disp('declarando variables simbolicas...')
syms t n;

w_f = 60*2*pi; % frecuencia angular fundamental.

N = 10; % numero de armonicos deseados
ft = sign(sin(t*w_f)); % senal periodica que se desea descomponer
T_2 = (2*pi/(2*w_f));

disp('calculando componentes en funcion de n...')
C_n = (w_f/(2*pi))*int( ft*exp(-1i*w_f*n*t), t, -T_2, T_2);

H = vpa(subs(C_n, 1:1:N), 4); % se evalua la funcion para obtener un vector
% con las componentes compljeas

time_interval = [0, 2*pi/w_f]; %  intervalo de tiempo en que se graficaran los armonicos

Harm_v = sym.empty([1,0]); % se crea vector vacio de funciones symbolicas
% cada funcino simbolica es una funcion

% en cada iteracion se construye un harmonico y se guarda en vector
for x=1:1:N
    Harm_v(x) = 2*abs(H(x))*cos(x*w_f*t+angle(H(x)));
end

% se pone (t*0) para que interprete 0 como funcion y(t)=0 y 
% no como double y marca error
fplot3(t, 1+(t*0), Harm_v(1), time_interval); %  se grafica primer armonico
hold on; % se mantiene, para poder dibujar las otras curvas en el mismo plot
for x=2:1:N
    fplot3(t, x+(t*0), Harm_v(x), time_interval);
end

% se grafica la suma de los armonicos, es decir, Una aproximacion 
% truncada de la señal original. (recuerdese que la señal original 
% solo se obtiene al realizar la suma infinita)
fplot3(t, (t*0), sum(Harm_v), time_interval);
fplot3(t, -1+(t*0), ft, time_interval);

%grid off; % se quitan las cuaddriculas

% se grafica el expectro y la fase sobre un eje diferente
stem3(zeros(1, N), 1:1:N, 2*vpa(abs(H), 4));
stem3(ones(1, N)*2*pi/w_f, 1:1:N, 2*vpa(angle(H), 4));
