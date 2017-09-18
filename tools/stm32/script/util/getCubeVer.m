function CubeVer = getCubeVer()
 try     
     script = fopen('.getVersionScript', 'w');                
     fprintf(script,'get version\n');
     fprintf(script,'exit wait\n');                
     %Close script file
     fclose(script);
     %Call STM32CubeMX to get its version
     stm32CubeMxPath = getSTM32CubeMxPath();
     commandString = char(fullfile(stm32CubeMxPath, 'STM32CubeMX.exe '));
     commandString = ['java -jar "' commandString '"', ' -q .getVersionScript' ];
     [status, result] = system(commandString); %#ok 
     foundVer = regexp(result,'get version','split');
     ver = regexp(foundVer{2},'OK','split');
     version = regexp(ver{1},'\.','split');
     verH = str2num(char(version(1)));%#ok
     verL = str2num(char(version(2)));%#ok
     CubeVer = str2num(strcat(num2str(verH,'%02d'),'.',num2str(verL,'%02d')));%#ok
     if isempty(CubeVer)
         CubeVer = 0;
     end
 catch
     CubeVer = 0;  
 end
end
