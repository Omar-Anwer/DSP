%% Cleaning window
clear all;
close all;
clc;
%%
Fs = 1000;           % Sampling frequency (Hz)
Ts = 1/Fs;           % Sampling period (seconds)
signal_start = 0;
signal_end = 1-Ts;
t = signal_start : Ts : signal_end;
%%
f1 = 400;
w1 = 2 * pi * f1;
x = cos(w1 * t);
x_normalized = x/(max(abs(x)));
%%
%figure(1);
%grid on;
%plot(t,x);     % plot x(t)
title('Signal in Time Domain x(t)');
ylabel('Amplitude');
xlabel('Time (sec)');
%% Convolution
x = [2 4 6 4 2];
subplot(3, 1, 1), stem(x), title('X[n]')
h = [3 -1 2 1];
subplot(3, 1, 2), stem(h), title('H[n]')
y = conv(x, h);
subplot(3, 1, 3), stem(y), title('Y[n] = X[N] * H[N]')



%%
filename = 'Audio_of_Signal_x(t).wav';  %generate 2 sec audio file 
%audiowrite(filename, x_normalized, Fs);
%% Audio parameters
audio_Fs = 44100;                       % 44.1KHz
audio_nBits = 24;                       % n = 8-bits, 2^8 = 256 levels
audio_NumChannels = 2;                  % Sterio 2-channels
audio_record_duration = 3;              % time in seconds

audio_voice_record = audiorecorder(audio_Fs, audio_nBits, audio_NumChannels);
%% Recording audio
disp('Recording started!')
recordblocking(audio_voice_record, audio_record_duration);
disp('Recording stopped!')
%% Playing audio
play(audio_voice_record);
%% Store audio file
audio_filename = 'my_voice.mp3';
audio_data = getaudiodata(audio_voice_record);
plot(audio_data);
%audiowrite(audio_filename, )
%% Upsampling
audio_upsample_factor = 2;
audio_upsampled = upsample(audio_data, audio_upsample_factor);
plot(audio_upsampled);
disp('Playing upsampled version!')
soundsc(audio_upsampled, audio_Fs);
%% Downsampling
audio_downsample_factor = 2;
audio_downsampled = downsample(audio_data, audio_downsample_factor);
plot(audio_downsampled);
disp('Playing downsampled version!')
soundsc(audio_downsampled, audio_Fs);
