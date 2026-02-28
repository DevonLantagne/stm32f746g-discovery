%% startup.m
% This is the MATLAB startup script. If a MATLAB terminal opens
% in the directory containing this file, it will automatically 
% execute this script.
%
% This script adds the "matlab_new" directory to the MATLAB path
% so users can easily call functions.

repoRoot = fileparts(mfilename('fullpath'));
matlabNewPath = fullfile(repoRoot, "matlab_new");
addpath(matlabNewPath)
