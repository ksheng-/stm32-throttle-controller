function stm32_make_rtw_hook(hookMethod,modelName,rtwroot,templateMakefile,buildOpts,buildArgs) %#ok
% stm32MAKERTWHOOK supports build process
%
% $ stm32_make_rtw_hook.m 2014-04-11 dlange $
%

% ERT_MAKE_RTW_HOOK - This is the standard ERT hook file for the RTW build
% process (make_rtw), and implements automatic configuration of the
% models configuration parameters.  When the buildArgs option is specified
% as 'optimized_fixed_point=1' or 'optimized_floating_point=1', the model
% is configured automatically for optimized code generation.
%
% This hook file (i.e., file that implements various RTW callbacks) is
% called by RTW for system target file ert.tlc.  The file leverages
% strategic points of the RTW process.  A brief synopsis of the callback
% API is as follows:
%
% ert_make_rtw_hook(hookMethod, modelName, rtwroot, templateMakefile,
%                   buildOpts, buildArgs)
%
% hookMethod:
%   Specifies the stage of the RTW build process.  Possible values are
%   entry, before_tlc, after_tlc, before_make, after_make and exit, etc.
%
% modelName:
%   Name of model.  Valid for all stages.
%
% rtwroot:
%   Reserved.
%
% templateMakefile:
%   Name of template makefile.  Valid for stages 'before_make' and 'exit'.
%
% buildOpts:
%   Valid for stages 'before_make' and 'exit', a MATLAB structure
%   containing fields
%
%   modules:
%     Char array specifying list of generated C files: model.c, model_data.c,
%     etc.
%
%   codeFormat:
%     Char array containing code format: 'RealTime', 'RealTimeMalloc',
%     'Embedded-C', and 'S-Function'
%
%   noninlinedSFcns:
%     Cell array specifying list of non-inlined S-Functions.
%
%   compilerEnvVal:
%     String specifying compiler environment variable value, e.g.,
%     D:\Applications\Microsoft Visual
%
% buildArgs:
%   Char array containing the argument to make_rtw.  When pressing the build
%   button through the Configuration Parameter Dialog, buildArgs is taken
%   verbatim from whatever follows make_rtw in the make command edit field.
%   From MATLAB, it's whatever is passed into make_rtw.  For example, its
%   'optimized_fixed_point=1' for make_rtw('optimized_fixed_point=1').
%
%   This file implements these buildArgs:
%     optimized_fixed_point=1
%     optimized_floating_point=1
%
% You are encouraged to add other configuration options, and extend the
% various callbacks to fully integrate ERT into your environment.

% Copyright 1996-2006 The MathWorks, Inc.
% $Revision: 1.1.6.7 $ $Date: 2006/10/10 02:35:48 $

disp(['### Real-Time Workshop build procedure for method: ''' hookMethod]);

disp(['### modelName: ''' modelName]);
disp(['### gcs: ''' gcs]);
disp(['### bdroot: ''' bdroot]);

%Global variable to know if we download appli or not. Do not download
%reference, only top model
global downloadTopModel;

switch hookMethod
	case 'error'
		% Called if an error occurs anywhere during the build.  If no error occurs
		% during the build, then this hook will not be called.  Valid arguments
		% at this stage are hookMethod and modelName. This enables cleaning up
		% any static or global data used by this hook file.
		disp(['### Real-Time Workshop build procedure for model: ''' modelName...
			''' aborted due to an error.']);
		
	case 'entry'
        %Do not download by default. See before_tlc case
        downloadTopModel = 0;
		% Called at start of code generation process (before anything happens.)
		% Valid arguments at this stage are hookMethod, modelName, and buildArgs.
		fprintf('\n### Starting Real-Time Workshop build procedure for model: %s\n',modelName);

        %Verify that product has been installed (ie: Added to Matlab path)
		Stm32RootPath  = updatePrefs('get','stm32RootPath');    
		%If path has not been added to preferences. Product has not been installed		
        if(isempty(Stm32RootPath))
			h = errordlg('Add STM32 toolkit repository to Matlab default path.','STM32');	    
			close(h);
			clear h
			error('Product has not been installed. ie:Not in Matlab path')
        end

        %Set environement variable to know windows version 32/64 bits      
        ext = mexext;
        if (isempty(getenv('MATLAB_WIN_VER')))
            switch ext
            	case 'mexw32'
                    setenv('MATLAB_WIN_VER','win32');
                case 'mexw64'
                    setenv('MATLAB_WIN_VER','win64');                
            end
        end
        clear ext 
        disp(['### Windows version:',getenv('MATLAB_WIN_VER')]);
        %Obtain the model's active configuration set.
        cset = getActiveConfigSet(modelName);
        
		%If path of product is not good. Certainly example has been copied from system where product has not been installed
		%at same location.
		ProductInfo = what(Stm32RootPath);		
        if (isempty(ProductInfo))            
            toolChain = cset.get_param('ToolChain');
            DownloadApplication = cset.get_param('DownloadApplication');
            cset.set_param('SystemTargetFile', 'ert.tlc');   % System target file
            switchTarget(cset,'ert.tlc',[]);
            pause(1);
            switchTarget(cset,'stm32.tlc',[]);
            cset.set_param('ToolChain', toolChain);
            cset.set_param('DownloadApplication', DownloadApplication);
            clear toolChain 
            clear DownloadApplication
			h = warndlg(sprintf('Configuration parameters>code Generation>STM32 Options>Installed path is not valid.\nPossible raison: Model has been copied from system where product was not installed at same location.\nSolution: Set Configuration parameters>code Generation>System target file to ert.tlc and click OK button. Then select stm32.tlc again, click OK button and verify that Installed path is STM32 repository installation path on your system.\nThen save the model.')...
            ,modelName,'modal');
            uiwait(h); 
			clear h               		
        end
		clear Stm32RootPath ProductInfo
			
		SIL_PIL = cset.get_param ('SimulationMode');
		fprintf('### Model connectivity is: %s\n',SIL_PIL);
		if (strfind(SIL_PIL,'processor-in-the-loop'))
            %reset configuration parameters 'external mode'
            cset.set_param ('ExtMode','off');                        
			%PIL requested mode
			updatePrefs('set','stm32PilMode',1);
            set_param(modelName, 'CreateSILPILBlock','PIL');
			pause(1);
			fprintf('### Create verification block: PIL\n');
        elseif (strfind(SIL_PIL,'external'))
			%External mode requested
			updatePrefs('set','stm32PilMode',2);
    		cset.set_param ('CreateSILPILBlock','None');
			fprintf('### Create verification block: None (External mode)\n');
            extModeParameters = cset.get_param ('ExtModeMexArgs');
            %Set configuration parameters to external mode
            cset.set_param ('ExtMode','on');            
            %default com parameters
            verbose = '0'; comPort = '1'; baudRate = '115200'; timeOut = '10';
            params = regexp(extModeParameters,'[, ]*','split');
            if(~isempty(params))
                v = 0;
                c = 0;
                b = 0;
                t = 0;
                [~,nbParams] = size(params);
                for k = 1:nbParams
                    if (~isempty(params{1,k}))
                        if(v == 0)
                            verbose = params{1,k};
                            v = 1;
                        elseif(c == 0)
                            comPort = params{1,k};
                            c = 1;
                        elseif(b == 0)
                            baudRate = params{1,k};
                            b = 1;
                        elseif(t == 0)
                            timeOut = params{1,k};
                            t = 1;
                        end                        
                    end
                end
            end
            [comPort,baudRate,timeOut] = getExtCOM(comPort, baudRate,timeOut);
            extModeParameters = char([verbose,',',comPort,',',baudRate,',',timeOut]);
            cset.set_param ('ExtModeMexArgs',extModeParameters);
            fprintf('### External mode parameters: %s\n',extModeParameters);
            setpref('STM32','COMSpeed',baudRate);
            %Tunable parameters
            cset.set_param ('DefaultParameterBehavior','Tunable');
        else
            %reset configuration parameters 'external mode'
            cset.set_param ('ExtMode','off');   
            %Inlined function
            cset.set_param ('DefaultParameterBehavior','Inlined');
			%NORMAL/SIL (Not PIL) requested mode
			updatePrefs('set','stm32PilMode',0);
			if (strfind(SIL_PIL,'Software-in-the-loop'))
				%SIL requested mode
				cset.set_param ('CreateSILPILBlock','SIL');
				cset.set_param('GenerateErtSFunction','on');
				fprintf('### Create verification block: SIL\n');
			else
				%other requested mode
				cset.set_param ('CreateSILPILBlock','None');
				fprintf('### Create verification block: None\n');
			end
		end
		clear cset SIL_PIL
       
			
	case 'before_tlc'
		% Called just prior to invoking TLC Compiler (actual code generation.)
		% Valid arguments at this stage are hookMethod, modelName, and
		% buildArgs
		fprintf('### before_tlc\n');
        % Download for topModel only, not for referenced model!
        % Check if this is a referenced model
        mdlRefTargetType = get_param(modelName,'ModelReferenceTargetType');
        isNotModelRefTarget = strcmp(mdlRefTargetType, 'NONE'); % NONE, SIM, or RTW
        if isNotModelRefTarget
            % code that is specific to the top model
            downloadTopModel = 1;
            %MCU selection
            %STM32MCU_selection(modelName);            
        else
            % code that is specific to the referenced model
            downloadTopModel = 0;
        end        
        clear isNotModelRefTarget mdlRefTargetType
 		
	case 'after_tlc'
		% Called just after to invoking TLC Compiler (actual code generation.)
		% Valid arguments at this stage are hookMethod, modelName, and
		% buildArgs
		fprintf('### after_tlc\n');
		
	case 'before_makefilebuilder_make'
		% Called after code generation is complete for PIL processing
		% All arguments are valid at this stage.
		fprintf('### before_makefilebuilder_make\n');
	
	case 'before_make'
		% Called after code generation is complete, and just prior to kicking
		% off make process (assuming code generation only is not selected.)  All
		% arguments are valid at this stage.
        fprintf('\n### Code Format : %s\n',buildOpts.codeFormat);
               		
		%Add makefile token to know when model ref is built if it is for PIL or not
        SIMULATION_MODE_RP = 'NO_PIL'; %#ok
		SIL_PIL = updatePrefs('get','stm32PilMode');
        if (isequal(SIL_PIL,1))
            SIMULATION_MODE_RP = 'PIL'; %#ok
        end
		clear SIL_PIL               	
		 		
	case 'after_make'
		% Called after make process is complete. All arguments are valid at
		% this stage.
	
	case 'exit'
		% Called at the end of the RTW build process.  All arguments are valid
		% at this stage.

		disp(['### Successful completion of Real-Time Workshop build ',...
			'procedure for model: ', modelName]);
				
		% In case the user enabled the checkbox 'Download Application' the
		% project is opened and the application gets downloaded:
        % When PIL request, Launcher do that.
		PilReq = updatePrefs('get','stm32PilMode');
        if (strcmp(get_param(modelName,'DownloadApplication'),'on') && ...
			strcmp(get_param(modelName,'GenCodeOnly'),'off') && ...
            (isequal(PilReq,0) ||  isequal(PilReq,2)) && ...
            downloadTopModel == 1)           
         if (isequal(PilReq,0)) 
            %PIL mode 
            %Get current repository (should be CodeGeneration)
            currentPath = pwd;                        
            hexGeneratedFilePath = which ('buildInfo.mat');
            [pathstr, ~, ~] = fileparts(hexGeneratedFilePath);
            pathstr = strrep(pathstr,'/','\');
            %Get project info from build information
            load([pathstr,'\buildInfo.mat']);
            %Extract files name and path information from build
            listCfiles = getFullFileList(buildInfo,'source'); 
                      
            %Get ioc file path and name.
            %It is the created project path.
            try
                ioc_path = ioc_getIocPath();
                [ioc_filePath,ioc_fileName,ioc_fileExt] = fileparts(ioc_path);
                ioc_file = [ioc_fileName,ioc_fileExt];
            catch
                h = errordlg('Please load an STM32 configuration file using STM32_Config model.','STM32 CONFIGURATION');	    
                close(h);
                clear h
                error('STM32 configuration not done.')
            end
            disp('### Copy generated files to STM32CubeMX working repository.');
            listPath = getIncludePaths(buildInfo,'true');
            listHfiles = getFullFileList(buildInfo,'include'); 
            Srcpath = fullfile(ioc_filePath,[modelName,'/Src']);
            Incpath = fullfile(ioc_filePath,[modelName,'/Inc']);
            mkdir(Srcpath);
            mkdir(Incpath);
            %Also build dir Src and Inc beside ioc file to copy main into
            %Src
            SrcCubepath = fullfile(ioc_filePath,'/Src');
            IncCubepath = fullfile(ioc_filePath,'/Inc');
            mkdir(SrcCubepath);
            mkdir(IncCubepath);

            %.mlproject file creation in same repository as ioc file.
            mlprojectName = fullfile(ioc_filePath,'/.mlproject');
            try
                mlproject = fopen(mlprojectName, 'w');
                fprintf(mlproject,'[ProjectFiles]\n');                   
                %All include files will be copied to IncPath
                fprintf(mlproject,'HeaderPath=%s;',Incpath);                   
 %           for index = listPath                
 %               pathName = strrep(index,'\','/');
 %               fprintf(mlproject,'%s;',char(pathName));                                  
 %           end           
                %Process c files : copy to src and Add to project!
                fprintf(mlproject,'\nSourceFiles=');                               
            
                %Process C files
                %All c files are copied to Srcpath except main.c
                for index = listCfiles
                    [pathFile, nameFile, extFile] = fileparts(char(index));
                    if(isempty(pathFile))
                        [pathFile, nameFile, extFile] = fileparts(which(char(index)));
                        pathFile = strrep(pathFile,'/','\');
                        prjSrcFile = fullfile(pathFile,index);
                    else
                        pathFile = strrep(pathFile,'/','\');
                        prjSrcFile = index;                    
                    end                
                    if(strcmp(extFile,'.c')&& isequal(strcmp(nameFile,'rt_main'),0))
                        if(isequal(strcmp(nameFile,'main'),0))
                            copyfile(char(prjSrcFile),[Srcpath,'\',nameFile,extFile],'f');
                            fprintf(mlproject,'%s/%s%s;',Srcpath,char(nameFile),char(extFile));                          
                         elseif(strcmp(nameFile,'main') && strcmp(pathstr,pathFile))
                            %main.c is copied into Src if it doesn't exist or overwriteMain preference is set to 1
							overwriteMain = updatePrefs('get','overwriteMain');
							mainExist = exist([SrcCubepath,'\',nameFile,extFile],'file');
							if(mainExist == 0)
								%main.c doesn't exist ---> copy it
								copyfile(char(prjSrcFile),[SrcCubepath,'\',nameFile,extFile],'f');							
							elseif(overwriteMain == 1)
								%overwriteMain preference is set ---> overwrite main.c
								copyfile(char(prjSrcFile),[SrcCubepath,'\',nameFile,extFile],'f');
							elseif(overwriteMain == 0)
								disp(['### overwriteMain preference is 0. Simulink will not provide main.c file. (no overwritten) ',...
								'Enter updatePrefs(', '''' , 'set', ''',', '''', 'overwriteMain', ''',', '1); ' ... 
								'in MATLAB command window to enable use of main.c file coming from Simulink.']);
							elseif(isempty(overwriteMain))
								updatePrefs('set','overwriteMain',1);
								h = warndlg(sprintf('%s\\main.c\nwill be overwritten.\nIf you have modified it and do not want to use Simulink provided one.\nYou must save it before to click OK.\nEnter updatePrefs(''set'' , ''overwriteMain'' , 0); in MATLAB command window to disable use of main.c file coming from Simulink.',SrcCubepath)...
								,modelName,'modal');
								uiwait(h); 
								clear h
								overwriteMain = updatePrefs('get','overwriteMain');
								if(overwriteMain == 1)
									%overwriteMain preference is set ---> overwrite main.c
									copyfile(char(prjSrcFile),[SrcCubepath,'\',nameFile,extFile],'f');
								end
							end          							
                        end
                    end
                end
    
                %Define section
                fprintf(mlproject,'\n[Others]\n');                   
                fprintf(mlproject,'Define=MEM_UNIT_BYTES;ARM_MATH_CM4;MemUnit_T:uint8_T;\n');                   
                %Close files description project file
                fclose(mlproject);
            catch
                error(['Can not create file : '...
                        mlprojectName ]);
            end

            openProject = updatePrefs('get','openProject');
            if(isempty(openProject))
                updatePrefs('set','openProject',1);
            end
            
            STM32CubeVersion = updatePrefs('get','stm32CubeMxVersion');
            %FROM STM32CubeMx Version 4.04
            if(STM32CubeVersion >= 4.04)
                %.script file creation in same repository as ioc file.
                scriptName = fullfile(ioc_filePath,'/.script');
                try
                    script = fopen(scriptName, 'w');                
                    %fprintf(script,'project path %s\n',ioc_filePath);                
                    fprintf(script,'config load "%s"\n',ioc_path);
                    if(openProject == 0)
                        fprintf(script,'project generate\n');
                    else
                        fprintf(script,'project generate ui\n');
                    end
                    fprintf(script,'exit wait\n');                
                    %Close script file
                    fclose(script);
                catch
                    error(['Can not create file : '...
                            scriptName ]);
                end
            end
            
            %Process H files : Copy to Incpath
%RPMODIF START
            %Copy .h file included in _sharedutils repository
            for index = listPath                
                pathName = strrep(index,'\','/');                
                if(~isempty(strfind(char(pathName), '_sharedutils')))
                    foundPath = regexp(char(pathName),'_sharedutils','split');
                    file2copy = fullfile(char(foundPath(1)),'_sharedutils','*.h');
                    copyfile(char(file2copy),char(Incpath),'f'); 
                    break;                    
                end
            end                       
%RPMODIF END      
            %Copy .h included files
            for index = listHfiles
                [pathFile, nameFile, extFile] = fileparts(char(index));
                if(isempty(pathFile))
                    if(exist(fullfile(char(Incpath),char(index)),'file') == 0)
                        %Files not already copied
                        for pathIndex = listPath
                            fileH2Found = fullfile(char(pathIndex),char(index));
                            if(exist(fileH2Found,'file') == 2)
                               copyfile(fileH2Found,[Incpath,'\',char(index)],'f'); 
                               break;
                            end
                        end
                    end
                else
                    copyfile(char(index),[Incpath,'\',nameFile,extFile],'f'); 
                end                                
            end
%RPMODIF            ioc_usedFile = fullfile(ioc_filePath,ioc_file);

            
            %Parse .ioc init file to add project manager info            
%RPMODIF            disp(['### Parse STM32CubeMX ioc configuration file:' ioc_usedFile]);
%RPMODIF            ioc_info = ioc_parse(ioc_usedFile);

            disp(['### Parse STM32CubeMX ioc configuration file:' ioc_path]);
            ioc_info = ioc_parse(ioc_path);
            [~,nbInfo] = size(ioc_info);
            ProjectFileName = ioc_getInfo(ioc_info,'ProjectManager','ProjectFileName','');
            if(isempty(ProjectFileName))
                nbInfo = nbInfo + 1;
                ioc_info(nbInfo).name = 'ProjectManager';
                ioc_info(nbInfo).field{1} = 'ProjectFileName';
                ioc_info(nbInfo).value = ioc_file;
                ioc_info(nbInfo).nbField = 1;
            else
                ProjectFileName.value = ioc_file;
            end
            ProjectName = ioc_getInfo(ioc_info,'ProjectManager','ProjectName','');
            if(isempty(ProjectName))
                nbInfo = nbInfo + 1;
                ioc_info(nbInfo).name = 'ProjectManager';
                ioc_info(nbInfo).field{1} = 'ProjectName';
                ioc_info(nbInfo).value = modelName;
                ioc_info(nbInfo).nbField = 1;
            else
                ProjectName.value = modelName;
            end
            %Write ioc configuration file including project info
%RPMODIF            ioc_write(ioc_usedFile,ioc_info);
            ioc_write(ioc_path,ioc_info);
                                                       
            %Start CubeMx
			disp('### Open STM32CubeMX for configuration and project code generation.');
            try        
                stm32CubeMxPath = getSTM32CubeMxPath();    
            catch ME         
                %Error STM32CubeMX path not found
                throw(ME);    
            end             
            commandString = char(fullfile(stm32CubeMxPath, 'STM32CubeMX.exe'));
            commandString = [ '"' commandString '"' ];
            STM32CubeVersion = updatePrefs('get','stm32CubeMxVersion');
            %FROM STM32CubeMx Version 4.04           
            if(STM32CubeVersion >= 4.04)
                argString = sprintf(' -q "%s"',scriptName);
            else
                argString = sprintf('"%s"', ioc_path);
            end
            
            disp(['Start command: ' commandString ' ' argString]);
            
            %Command string to start blocking CubeMx
            str = ['java -jar ', [commandString,' ',argString]];                    
            
            %Command string to start non blocking CubeMx
            %str = [commandString,' ',argString]; 
              
              
            %Start IDE
			[status, result] = system(str); %#ok
            
            %Go back to current path
            cd(currentPath);
            clear currentPath ;
			if status == 0 % success
				disp('### Downloaded command successfully fired.');
			end
			clear Stm32RootPath toolChainSel toolPath            
         elseif (isequal(PilReq,2))
            %%%%%%%%%%%%%% EXTERNAL MODE %%%%%%%%%%%%%%%%%%%% 
            %Get current repository (should be CodeGeneration)
            currentPath = pwd;                        
            hexGeneratedFilePath = which ('buildInfo.mat');
            [pathstr, ~, ~] = fileparts(hexGeneratedFilePath);
            pathstr = strrep(pathstr,'/','\');
            %Get project info from build information
            load([pathstr,'\buildInfo.mat']);
                      
            %Get ioc file path and name.
            %It is the created project path.
            try
                ioc_path = ioc_getIocPath();
                [ioc_filePath,ioc_fileName,ioc_fileExt] = fileparts(ioc_path);
                %STM32CubeMx not opened by default
                updatePrefs('set','hideIDE',1); 
                if(isempty(ioc_fileExt))
                    disp(['### WARNING: No IOC file selected for model: ', modelName ]);                    
                    ioc_file = [modelName,'.ioc'];
                    %Create ioc file beside model file
                    [ioc_filePath,~,~] = fileparts(which(bdroot));
                    ioc_path = fullfile(ioc_filePath,ioc_file);
                    %test if ioc file has already been created
                    if(exist(ioc_path,'file')~= 2)   
                        %Create ioc file
                        %with all necessary parameters 
                        %-Select STM32
                        %-Select USART + Rx + Tx for external mode
                        %-toolChain selection
                        extModeIocUsartUpdate('',ioc_path,modelName);
                    else
                        %Use ioc created file
                        %Select USART + Rx + Tx from ioc created file
                        getUsartExtModeFromIoc(ioc_path,modelName);               
                    end
                else
                    ioc_file = [ioc_fileName,'_extMode',ioc_fileExt];
                    ioc_ext_mode_path = fullfile(ioc_filePath,ioc_file);
                    if(exist(ioc_ext_mode_path,'file') ~= 2)                   
                       copyfile(char(ioc_path),char(ioc_ext_mode_path),'f');                        
                    end
                    %Select USART + Rx + Tx for external mode from ioc or from STM32 capabilities
                    getUsartExtModeFromIoc(ioc_ext_mode_path,modelName);
                    ioc_path = ioc_ext_mode_path;
                end                
            catch ME
                throw(ME);
            end
            %Create RTIOSTREAM for External Mode
            %Include path 
            stm32f3RootPath = getpref('STM32','stm32RootPath');
            rtiostream_src_path = fullfile(stm32f3RootPath,'ext','stm32SerialRtiostream');
            %Add rtiostream files to buid information
            buildInfo.addIncludePaths(rtiostream_src_path);
            buildInfo.addSourcePaths(rtiostream_src_path);                      
            buildInfo.addSourceFiles('STM32SerialRtiostream.c',rtiostream_src_path);
            buildInfo.addIncludeFiles('STM32SerialRtiostream.h',rtiostream_src_path);
            %Add path to MATLAB needed files                     
            path2Add1=fullfile(matlabroot,'/extern/include'); 
            %buildInfo.addIncludePaths(path2Add);
            path2Add2=fullfile(matlabroot,'/simulink/include');
            %buildInfo.addIncludePaths(path2Add);
            path2Add3=fullfile(matlabroot,'/rtw/c/src');
            %buildInfo.addIncludePaths(path2Add);
            path2Add4=fullfile(matlabroot,'/rtw/c/src/ext_mode/common');
            %buildInfo.addIncludePaths(path2Add);
            path2Add5=fullfile(matlabroot,'/rtw/c/ert');
            %buildInfo.addIncludePaths(path2Add);
            path2Add6=fullfile(matlabroot,'/toolbox/coder/rtiostream/src/utils');
            %buildInfo.addIncludePaths(path2Add);
            path2Add7=fullfile(matlabroot,'/rtw/c/src/ext_mode/serial');            
            %buildInfo.addIncludePaths(path2Add);  
%            IncExtModePath = ['"',path2Add1,'";','"',path2Add2,'";','"',path2Add3,'";','"',path2Add4,'";','"',path2Add5,'";','"',path2Add6,'";','"',path2Add7,'";'];
            IncExtModePath = [path2Add1,';',path2Add2,';',path2Add3,';',path2Add4,';',path2Add5,';',path2Add6,';',path2Add7,';'];
            %Extract source files name and path information from build
            listCfiles = getFullFileList(buildInfo,'source'); 
            disp('### Copy generated files into STM32CubeMX working repository.');
            %Create SRC and INC repository
            listPath = getIncludePaths(buildInfo,'true');
            listHfiles = getFullFileList(buildInfo,'include'); 
            Srcpath = fullfile(ioc_filePath,[modelName,'/Src']);
            Incpath = fullfile(ioc_filePath,[modelName,'/Inc']);
            mkdir(Srcpath);
            mkdir(Incpath);
            %Also build dir Src and Inc beside ioc file to copy main into
            %Src
            SrcCubepath = fullfile(ioc_filePath,'/Src');
            IncCubepath = fullfile(ioc_filePath,'/Inc');
            mkdir(SrcCubepath);
            mkdir(IncCubepath);                        
            
            % Build .h file with choosen USART parameters. 
            rtiostreamConfigFile = fullfile(Incpath,'STM32SerialRtiostream_Config.h');
            fid = fopen(rtiostreamConfigFile,'w');
            fprintf(fid,'/*\n * File: STM32FSerialRtiostream_Config.h\n *\n * Code generated for Simulink model :%s\n *\n',modelName);
            fprintf(fid,' * PIL USART File configuration\n *\n *\n *\n * * ******************************************************************************\n');
            fprintf(fid,'* * attention\n');
            fprintf(fid,'* *\n');
            fprintf(fid,'* * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS\n');
            fprintf(fid,'* * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE\n');
            fprintf(fid,'* * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY\n');
            fprintf(fid,'* * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING\n');
            fprintf(fid,'* * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE\n');
            fprintf(fid,'* * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.\n');
            fprintf(fid,'* *\n');
            fprintf(fid,'* ******************************************************************************\n*/\n\n');
            fprintf(fid,'#ifndef RTW_HEADER_STM32SerialRtiostream_Config_h_\n');
            fprintf(fid,'#define RTW_HEADER_STM32SerialRtiostream_Config_h_\n');
            %Get parameters
            PIL_USARTName = char(getpref('STM32','PIL_USARTName'));
            STM32Fam = lower(char(getpref('STM32','STM32Fam')));
            usartNum = regexp(PIL_USARTName,'[1-9]','match');
            usartNum = [usartNum{1,:}];            
            fprintf(fid,'#include "%sxx_hal.h"\n',STM32Fam);
            fprintf(fid,'extern UART_HandleTypeDef huart%s;\n',usartNum);
            fprintf(fid,'#define EXT_MODE_USART_HANDLE\t (&huart%s)\n',usartNum);
            fprintf(fid,'#endif\n');
            fprintf(fid,'\n/* File trailer for Real-Time Workshop generated code.\n*\n* [EOF] STM32SerialRtiostream_Config.h\n*/\n');        
            fclose(fid);
                                   

            %.mlproject file creation in same repository as ioc file.
            %to give files and path and defines to STM32CubeMX
            mlprojectName = fullfile(ioc_filePath,'/.mlproject');
            try
                mlproject = fopen(mlprojectName, 'w');
                fprintf(mlproject,'[ProjectFiles]\n');                   
                %All include files will be copied to IncPath
                fprintf(mlproject,'HeaderPath=%s;%s',Incpath,IncExtModePath);                   
                %Process c files : copy to src and Add to project!
                fprintf(mlproject,'\nSourceFiles=');                               
                %Process C files
                %All c files are copied to Srcpath except main.c
                for index = listCfiles
                    [pathFile, nameFile, extFile] = fileparts(char(index));
                    if(isempty(pathFile))
                        [pathFile, nameFile, extFile] = fileparts(which(char(index)));
                        pathFile = strrep(pathFile,'/','\');
                        prjSrcFile = fullfile(pathFile,index);
                    else
                        pathFile = strrep(pathFile,'/','\');
                        prjSrcFile = index;                    
                    end                
                    if(strcmp(extFile,'.c')&& isequal(strcmp(nameFile,'rt_main'),0))
                        if(isequal(strcmp(nameFile,'main'),0))
                            copyfile(char(prjSrcFile),[Srcpath,'\',nameFile,extFile],'f');
                            fprintf(mlproject,'%s/%s%s;',Srcpath,char(nameFile),char(extFile));                          
                         elseif(strcmp(nameFile,'main') && strcmp(pathstr,pathFile))
                            %main.c is copied into Src if it doesn't exist or overwriteMain preference is set to 1
							overwriteMain = updatePrefs('get','overwriteMain');
							mainExist = exist([SrcCubepath,'\',nameFile,extFile],'file');
							if(mainExist == 0)
								%main.c doesn't exist ---> copy it
								copyfile(char(prjSrcFile),[SrcCubepath,'\',nameFile,extFile],'f');							
							elseif(overwriteMain == 1)
								%overwriteMain preference is set ---> overwrite main.c
								copyfile(char(prjSrcFile),[SrcCubepath,'\',nameFile,extFile],'f');
							elseif(overwriteMain == 0)
								disp(['### overwriteMain preference is 0. Simulink will not provide main.c file. (no overwritten) ',...
								'Enter updatePrefs(', '''' , 'set', ''',', '''', 'overwriteMain', ''',', '1); ' ... 
								'in MATLAB command window to enable use of main.c file coming from Simulink.']);
							elseif(isempty(overwriteMain))
								updatePrefs('set','overwriteMain',1);
								h = warndlg(sprintf('%s\\main.c\nwill be overwritten.\nIf you have modified it and do not want to use Simulink provided one.\nYou must save it before to click OK.\nEnter updatePrefs(''set'' , ''overwriteMain'' , 0); in MATLAB command window to disable use of main.c file coming from Simulink.',SrcCubepath)...
								,modelName,'modal');
								uiwait(h); 
								clear h
								overwriteMain = updatePrefs('get','overwriteMain');
								if(overwriteMain == 1)
									%overwriteMain preference is set ---> overwrite main.c
									copyfile(char(prjSrcFile),[SrcCubepath,'\',nameFile,extFile],'f');
								end
							end          							
                        end
                    end
                end
                %Add to sources files for External Mode only
                prjSrcFile=fullfile(matlabroot,'/rtw/c/src/ext_mode/serial/ext_serial_pkt.c');
                [~, nameFile, extFile] = fileparts(prjSrcFile);
                copyfile(char(prjSrcFile),[Srcpath,'\',nameFile,extFile],'f');
                fprintf(mlproject,'%s/%s%s;',Srcpath,char(nameFile),char(extFile));                          

                prjSrcFile=fullfile(matlabroot,'/rtw/c/src/ext_mode/serial/rtiostream_serial_interface.c');
                [~, nameFile, extFile] = fileparts(prjSrcFile);
                copyfile(char(prjSrcFile),[Srcpath,'\',nameFile,extFile],'f');
                fprintf(mlproject,'%s/%s%s;',Srcpath,char(nameFile),char(extFile));                          
                
                prjSrcFile=fullfile(matlabroot,'/rtw/c/src/ext_mode/serial/ext_svr_serial_transport.c');
                [~, nameFile, extFile] = fileparts(prjSrcFile);
                copyfile(char(prjSrcFile),[Srcpath,'\',nameFile,extFile],'f');
                fprintf(mlproject,'%s/%s%s;',Srcpath,char(nameFile),char(extFile));                          

                %Define section
                fprintf(mlproject,'\n[Others]\n');                   
                fprintf(mlproject,'Define=MEM_UNIT_BYTES;ARM_MATH_CM4;MemUnit_T:uint8_T;EXT_MODE:1;EXTMODE_DISABLEPRINTF;EXTMODE_DISABLETESTING;EXTMODE_DISABLE_ARGS_PROCESSING:1\n');                   
                %Close files description project file
                fclose(mlproject);
            catch
                error(['Can not create file : '...
                        mlprojectName ]);
            end

            openProject = updatePrefs('get','openProject');
            if(isempty(openProject))
                updatePrefs('set','openProject',1);
            end
            STM32CubeVersion = updatePrefs('get','stm32CubeMxVersion');
            %FROM STM32CubeMx Version 4.14
            if(STM32CubeVersion >= 4.14)
                %.script file creation in same repository as ioc file.
                %File command for STM32CubeMX
                scriptName = fullfile(ioc_filePath,'/.script');
                try                   
                    script = fopen(scriptName, 'w');                
                    %fprintf(script,'project path %s\n',ioc_filePath);                
                    fprintf(script,'config load "%s"\n',ioc_path);
                    %Set project name
                    fprintf(script,'project name %s\n',modelName);
                    %Set toolchain name
                    toolChainName = char(updatePrefs('get','toolChainName'));
                    toolChainVersion = char(strtrim(updatePrefs('get','toolChainVersion')));
                    if(strcmp(toolChainName,'Other'))
                        fprintf(script,'project toolchain %s\n',toolChainVersion);
                    elseif isempty(toolChainVersion)
                        fprintf(script,'project toolchain %s\n',toolChainName);
                    else                        
                        fprintf(script,'project toolchain %s\n',['"',toolChainName,' ',toolChainVersion,'"']);
                    end
                    %%RP_MODIF fprintf(script,'project toolchainLocation Projects\n');
                    fprintf(script,'project toolchainLocation \n');
                    %Sysclock src is PLL
                    %%RP_MODIF fprintf(script,'clock set SysClkSource 2\n');
                    %PLL src is HSI
                    %%RP_MODIF fprintf(script,'clock set PLLSource 0\n');
                    %RPMODIF SET APB DIVIDER
                    %%RP_MODIF fprintf(script,'clock set APB1CLKDivider 4\n');
                    %%RP_MODIF fprintf(script,'clock set APB2CLKDivider 2\n');               
                    %Get MCU frequency value
                    ticksPerSecond = str2double(char(getpref('STM32','ticksPerSecond')));        
                    %set frequency value
                    fprintf(script,'clock set hclk %d\n',ticksPerSecond / 1e6);
                    %RP_MODIF Set HeapSize for test
                    heapSizeDec = updatePrefs('get','heapSize');
                    fprintf(script,'project set heapsize 0x%x\n',heapSizeDec);
                    if(openProject == 0)
                        disp('### Open Project popup window will not appear. Set openProject preference to 1 if you want to see it.');
                        fprintf(script,'project generate\n');
                    else
                        disp('### Open Project popup window will appear. Set openProject preference to 0 if you do not want to see it.');
                        fprintf(script,'project generate ui\n');
                    end
                    fprintf(script,'exit wait\n');                
                    %Close script file
                    fclose(script);                                                                                            
                catch
                    error(['Can not create file : '...
                            scriptName ]);
                end
            else
                error('STM32CubeMX version not supported for External Mode. Update STM32CubeMX.');
            end
            
            %Process H files : Copy to Incpath
            %Copy .h file included in _sharedutils repository
            for index = listPath                
                pathName = strrep(index,'\','/');                
                if(~isempty(strfind(char(pathName), '_sharedutils')))
                    foundPath = regexp(char(pathName),'_sharedutils','split');
                    file2copy = fullfile(char(foundPath(1)),'_sharedutils','*.h');
                    copyfile(char(file2copy),char(Incpath),'f'); 
                    break;                    
                end
            end                       
            %Copy .h included files
            for index = listHfiles
                [pathFile, nameFile, extFile] = fileparts(char(index));
                if(isempty(pathFile))
                    if(exist(fullfile(char(Incpath),char(index)),'file') == 0)
                        %Files not already copied
                        for pathIndex = listPath
                            fileH2Found = fullfile(char(pathIndex),char(index));
                            if(exist(fileH2Found,'file') == 2)
                               copyfile(fileH2Found,[Incpath,'\',char(index)],'f'); 
                               break;
                            end
                        end
                    end
                else
                    copyfile(char(index),[Incpath,'\',nameFile,extFile],'f'); 
                end                                
            end            
            disp(['### Parse STM32CubeMX ioc configuration file:' ioc_path]);
            ioc_info = ioc_parse(ioc_path);
            [~,nbInfo] = size(ioc_info);
            ProjectFileName = ioc_getInfo(ioc_info,'ProjectManager','ProjectFileName','');
            if(isempty(ProjectFileName))
                nbInfo = nbInfo + 1;
                ioc_info(nbInfo).name = 'ProjectManager';
                ioc_info(nbInfo).field{1} = 'ProjectFileName';
                ioc_info(nbInfo).value = ioc_file;
                ioc_info(nbInfo).nbField = 1;
            else
                ProjectFileName.value = ioc_file;
            end
            ProjectName = ioc_getInfo(ioc_info,'ProjectManager','ProjectName','');
            if(isempty(ProjectName))
                nbInfo = nbInfo + 1;
                ioc_info(nbInfo).name = 'ProjectManager';
                ioc_info(nbInfo).field{1} = 'ProjectName';
                ioc_info(nbInfo).value = modelName;
                ioc_info(nbInfo).nbField = 1;
            else
                ProjectName.value = modelName;
            end
            %Write ioc configuration file including project info
            ioc_write(ioc_path,ioc_info);
                                                       
            %Start CubeMx
			disp('### Open STM32CubeMX for configuration and project code generation.');
            try        
                stm32CubeMxPath = getSTM32CubeMxPath();    
            catch ME         
                %Error STM32CubeMX path not found
                throw(ME);    
            end             
            commandString = char(fullfile(stm32CubeMxPath, 'STM32CubeMX.exe'));
            commandString = [ '"' commandString '"' ];
            STM32CubeVersion = updatePrefs('get','stm32CubeMxVersion');
            hideIDE = updatePrefs('get','hideIDE');
            %FROM STM32CubeMx Version 4.04
            % and STM32CubeMX IDE not opened
            if(STM32CubeVersion >= 4.04 && hideIDE)
                argString = sprintf(' -q "%s"',scriptName);
            else
                argString = sprintf('"%s"', ioc_path);
            end            
            disp(['Start command: ' commandString ' ' argString]);            
            %Command string to start blocking CubeMx
            str = ['java -jar ', [commandString,' ',argString]];                                
            %Command string to start non blocking CubeMx
            %str = [commandString,' ',argString];                             
            %Start IDE
			[status, result] = system(str); %#ok            
            %Go back to current path
            cd(currentPath);
            clear currentPath ;
			if status == 0 % success
				disp('### External mode downloaded command successfully fired.');
			end
			clear Stm32RootPath toolChainSel toolPath
         end         
        end
end
