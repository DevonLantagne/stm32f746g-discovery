function plot_real(filename)
%PLOT_REAL Plot float32 samples from a raw binary memory dump.
%
%   PLOT_REAL(FILENAME) reads float32 values from the binary file
%   specified by FILENAME and plots them.
%
%   This function is intended for visualizing raw buffers dumped from
%   embedded memory using a debugger (e.g., GDB).
%
%   The binary file should be generated using a command similar to:
%       dump binary memory output.bin <start_addr> <end_addr>
%
%   Inputs
%   ------
%   FILENAME      Character vector or string scalar specifying the path
%                 to the binary file.
%
%   Example
%   -------
%       plot_real('buffer.bin');
%

    arguments
        filename {mustBeTextScalar}
    end

    % Open the .bin file
    fid = fopen(filename, 'rb');
    if fid == -1
        error('plot_real:FileOpenError', ...
            'Unable to open file: %s', filename);
    end

    % Define cleanup object to ensure file is closed even if an error occurs
    cleanupObj = onCleanup(@() fclose(fid));
    
    % Read Data and convert to double
    data = fread(fid, 'float32=>double');

    % Generate figure
    figure('visible', 'off');
    plot(data);
    title(...
        sprintf('Samples from %s', filename), ...
        'interpreter', 'none'); % Display filename in title without interpreting underscores
    xlabel('Sample');
    ylabel('Value');
    grid on;
    movegui(gcf, 'center');
    set(gcf, 'visible', 'on');

end