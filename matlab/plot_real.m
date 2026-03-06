function plot_real(filename, opts)
%PLOT_REAL Plot samples from a raw binary memory dump.
%
%   PLOT_REAL(FILENAME, NameValuePairs) reads values from the binary file
%   specified by FILENAME and plots them. Default assumes the data is in
%   32-bit floating-point format (float32) and little-endian byte order.
%   You can change the input format with the 'inputType' optional argument.
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
%   NameValuePairs:
%       'inputType'   Data type of the values in the binary file (default float32). Can also be
%                     int8, int16, int32, int64, uint8, uint16, uint32, or uint64.
%       'machineFmt'  Machine format of the values in the binary file (default little endian).
%
%   Example
%   -------
%       plot_real('buffer.bin'); % Reads float32 data from buffer.bin
%       plot_real('buffer.bin', 'inputType', 'int16'); % Reads int16 data from buffer.bin
%

    arguments
        filename {mustBeTextScalar}
        opts.inputType {mustBeMember(opts.inputType, {...
            'float32',...
            'int8','int16','int32','int64',...
            'uint8','uint16','uint32','uint64'})} = 'float32'
        opts.machineFmt {mustBeMember(opts.machineFmt, {'ieee-le','ieee-be'})} = 'ieee-le'
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
    data = fread(fid, 'precision', [opts.inputType '=>double'], 'machinefmt', opts.machineFmt);

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