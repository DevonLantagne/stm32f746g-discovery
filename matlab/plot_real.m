%% plot_real.m
% This function is used to read a binary file containing 
% 128 (or bufferLength) float32 values and plot them. 
% The filename is passed as an argument to the function.
%
% To create this binary file, run your buffer program in debug mode
% and use the GDB "dump binary memory" command.

function plot_real(filename, bufferLength)

    arguments
        filename (1,:) char
        bufferLength (1,1) {mustBePositive} = 128
    end

fid = fopen(filename, 'rb');
data = fread(fid, bufferLength, 'float32');
fclose(fid);

figure;
plot(data);
title('Samples from %s', filename);
xlabel('Sample');
ylabel('Value');

end