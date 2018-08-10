function varargout = GUI(varargin)
% GUI MATLAB code for GUI.fig
%      GUI, by itself, creates a new GUI or raises the existing
%      singleton*.
%
%      H = GUI returns the handle to a new GUI or the handle to
%      the existing singleton*.
%
%      GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI.M with the given input arguments.
%
%      GUI('Property','Value',...) creates a new GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help GUI

% Last Modified by GUIDE v2.5 13-Jun-2018 17:22:26

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before GUI is made visible.
function GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to GUI (see VARARGIN)

% Choose default command line output for GUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


axes(handles.img);
imshow('img.png');


% --- Outputs from this function are returned to the command line.
function varargout = GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function TF_hi_Callback(hObject, eventdata, handles)
% hObject    handle to TF_hi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of TF_hi as text
%        str2double(get(hObject,'String')) returns contents of TF_hi as a double


% --- Executes during object creation, after setting all properties.
function TF_hi_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TF_hi (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function TF_lo_Callback(hObject, eventdata, handles)
% hObject    handle to TF_lo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of TF_lo as text
%        str2double(get(hObject,'String')) returns contents of TF_lo as a double


% --- Executes during object creation, after setting all properties.
function TF_lo_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TF_lo (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function TF_amp_Callback(hObject, eventdata, handles)
% hObject    handle to TF_amp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of TF_amp as text
%        str2double(get(hObject,'String')) returns contents of TF_amp as a double


% --- Executes during object creation, after setting all properties.
function TF_amp_CreateFcn(hObject, eventdata, handles)
% hObject    handle to TF_amp (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in update.
function update_Callback(hObject, eventdata, handles)
% hObject    handle to update (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

axes(handles.spectra)
cla reset;

% se leen los datos de los campos de texto con los datos de la forma de
% onda
at = str2num(get(handles.TF_hi, 'String'));
bt = str2num(get(handles.TF_lo, 'String'));
c = str2num(get(handles.TF_amp, 'String'));

syms t w;

% se arma el pulso aperiodico como funcion simbolica
y = c*(heaviside(t)-heaviside(t-at));

% se grafica el pulso aperiodico
axes(handles.single_p);
fplot(y, [-at/10 at+bt]);
ylim([0 c+c/10]);

% se calcula la transformada de fourier simbolica
Ft = 2*fourier(y, 2*pi*w);
Ftw = abs(Ft);
maxFtw = double(vpa(limit(Ftw, 0), 3));

axes(handles.spectra);
fplot(Ftw, [-2 200]);
hold on;
ylim([0 maxFtw + maxFtw/10]);

% se construye el tren de pulsos a partir del pulso aperiodico.

Ts = (at+bt)/500; % se calcula el tiempo de muestreo de acuerdo a las dimensiones de las señales
tx = 0:Ts:(at+bt);
Xa = double(vpa(subs(y, tx), 3));

Ncy = 20;

Xp = repmat(Xa, 1, Ncy);
txx = 0:Ts:Ts*(length(Xp)-1);

axes(handles.full_p);
plot(txx, Xp, 'red');


% se hace la transformada rapida para el caso periodico.
% el espectro discreto que se obtiene se grafica superpuesto a la grafica
% del espectro continuo.


fmax = 1/Ts; % frecuencia maxima hasta donde va la fft

fny = fmax/2;

N = length(Xp); % numero de muestras
 
N2 = floor(N/2); % mitad del numero de muestras. recordando nyquist,
% solo la mitad de la transformada es de utilidad es decir hasta fmax/2

Fh = fft(Xp); % transformada rapida de fourier

dw = fmax/N; % resolucion en frecuencia de la fft

w = (0:1:N2-1)*dw; % vector de frecuencia

Fpw = abs(Fh);
Fpw(1) = Fpw(1)/N2;
Fpw(2:end) = Fpw(2:end)/N2*(at+bt);

Fpwp = Fpw(1:N2);

[c index] = min(abs(w-200))

axes(handles.spectra);
plot(w(1:index), Fpwp(1:index), 'red');



% --- Executes on key press with focus on update and none of its controls.
function update_KeyPressFcn(hObject, eventdata, handles)
% hObject    handle to update (see GCBO)
% eventdata  structure with the following fields (see MATLAB.UI.CONTROL.UICONTROL)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)
















