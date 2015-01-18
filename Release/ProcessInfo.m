fid = fopen('ProcessInfo.txt');
SingleCell = textscan(fid,'%s','delimiter','\n');
AllText = SingleCell{1};
processes = {};
thisStep = [];
procNo = 0;
rowNo = 1;
while rowNo <= size(AllText,1)
   tokens = strsplit(AllText{rowNo});
   if strcmp(tokens{1},'//') || strcmp(tokens{1},'')
   elseif strcmp(tokens{1},'Process')
       if procNo > 0
           processes{procNo} = thisStep;
           thisStep = [];
       end
       procNo = procNo + 1;
   else
       thisStep = [thisStep; str2double(tokens{1}),str2double(tokens{2})];
   end
   rowNo = rowNo + 1;
end
processes{procNo} = thisStep;