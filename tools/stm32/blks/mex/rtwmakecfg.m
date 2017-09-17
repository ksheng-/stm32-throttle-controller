function makeInfo = rtwmakecfg() 
% RTWMAKECFG Add include and source directories to RTW make files. 
% makeInfo = RTWMAKECFG returns a structured array containing following fields:

% makeInfo.includePath - cell array containing additional include 
% directories. Those directories will be 
% expanded into include instructions of rtw 
% generated make files.
% makeInfo.sourcePath - cell array containing additional source 
% directories. Those directories will be 
% expanded into rules of rtw generated make 
% files.
% makeInfo.library - structure containing additional runtime library 
%names and module objects. This information 
% will be expanded into rules of rtw generated make 
% files.
% ... .library(1).Name - name of runtime library 
% ... .library(1).Modules - cell array containing source file 
% names for the runtime library 
% ... .library(2).Name 
% ... .library(2).Modules 
% ...
% This RTWMAKECFG file must be located in the same directory as the related 
% S-function MEX-DLL(s). If one or more S-functions of the directory are referenced 
% by a model Real-Time Workshop will evaluate RTWMAKECFG to obtain the additional 
% include and source directories.
% To examine more RTWMAKECFG files in your installation issue at the MATLAB prompt: 
% >> which RTWMAKECFG -all
% Issue a message. 
seperatorLine = char(ones(1,70) * '~');
fprintf('\n'); 
fprintf('%s\n', seperatorLine); 
% RPMODIF fprintf(' %s\n', which(mfilename)); 
fprintf(' Adding source and include directories to make process.\n')

stm32RootPath =  getpref('STM32', 'stm32RootPath');
fprintf('STM32 package install path: %s\n', stm32RootPath); 

%Add path depending on toolchain selection for startup file
%stm32f3ToolChain =  getpref('STM32F30x', 'stm32f3ToolChain');
%Default is IAR path
%stm32f3StartupFilepath =  fullfile(stm32RootPath,'\lib\CMSIS\Device\ST\STM32F30x\Source\Templates\iar'); 

%switch stm32f3ToolChain
%	case 'IAR'
%		stm32f3StartupFilepath =  fullfile(stm32RootPath,'\lib\CMSIS\Device\ST\STM32F30x\Source\Templates\iar');
%	case 'KEIL'
%		stm32f3StartupFilepath =  fullfile(stm32RootPath,'\lib\CMSIS\Device\ST\STM32F30x\Source\Templates\arm');	
%	case 'ATOLLIC'
%		stm32f3StartupFilepath =  fullfile(stm32RootPath,'\lib\CMSIS\Device\ST\STM32F30x\Source\Templates\TrueSTUDIO');
%end


% Setting up the return structure with 
% - source directories: 
% C:\Projects\SFunctions\Sources 
makeInfo.sourcePath = { ... 
    fullfile(stm32RootPath,'\addSrc\src') ...
   };
%	stm32f3StartupFilepath ...
%     fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\BasicMathFunctions') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\CommonTables') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\ComplexMathFunctions') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\ControllerFunctions') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\FastMathFunctions') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\FilteringFunctions') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\MatrixFunctions') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\StatisticsFunctions') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\SupportFunctions') ...
%    fullfile(stm32RootPath,'\lib\CMSIS\DSP_Lib\Source\TransformFunctions') ...
%    };

% - include directories 
% C:\Projects\SFunctions\Headers 
makeInfo.includePath = { ... 
     fullfile(stm32RootPath,'\addSrc\inc') ...
 %   fullfile(stm32RootPath,'\lib\CMSIS\Device\ST\STM32F30x\Include')  ... 
 %   fullfile(stm32RootPath,'\lib\CMSIS\Include') ...
 %   fullfile(stm32RootPath,'\lib\STM32F30x_StdPeriph_Driver\inc') ...
 %    fullfile(stm32RootPath,'\src') ...    
 %   fullfile(stm32RootPath,'\lib\CMSIS\Include') ...    
    };
% Display contents. 
fprintf(' - additional source directories:\n'); 
fprintf(' %s\n', makeInfo.sourcePath{:}); 
fprintf(' - additional include directories:\n'); 
fprintf(' %s\n', makeInfo.includePath{:}); 
fprintf('%s\n', seperatorLine);
% [EOF] rtwmakecfg.m