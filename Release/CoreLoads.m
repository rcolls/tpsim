fid = fopen('CoreLoads.txt');
SingleCell = textscan(fid,'%s','delimiter','\n');
AllText = SingleCell{1};
t = [];
coredata = [];
thisStep = [];
rowNo = 1;
while rowNo <= size(AllText,1)
   tokens = strsplit(AllText{rowNo});
   if strcmp(tokens{1},'//') || strcmp(tokens{1},'')
   elseif tokens{1} == 't'
       t = [t;str2double(tokens{2})];
       if size(t,1) > 1
            coreData(:,:,size(t,1)-1) = thisStep;
            thisStep = [];
       end
   else
       thisStep = [thisStep; str2num(AllText{rowNo})];
   end
   rowNo = rowNo + 1;
end
coreData(:,:,size(t,1)) = thisStep;
