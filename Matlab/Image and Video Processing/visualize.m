function [frames, N, frameformat] = visualize(framepath)
% visualize Visualisoi kuvat kahdella tapaa, subplotina ja toinen toisensa
%           perään vaihtuvana nauhana.
% [frames, N, frameformat] = visualize(framepath) Lukee tiedoston framepath
% ja tekee kansion, joka sisältää kuvat tiedostosta. Visualisoi kuvat 
% kahdella tapaa. Palauttaa kuvat solutaulukossa frames, solutaulukon koon 
% N ja kuvaformaatin frameformat.

load('formats.mat')
contents = dir(framepath);

% Poistetaan kansiosta tyhjät ei kuvat
k = 1;
for i=1:max(size(contents)) 
    str = contents(i).name;
    if (strcmp(str,'.')==0)&&(strcmp(str,'..')==0)
        str = (framepath + "/" + str);
        frames{k} = imread(str);
        k = k + 1;
    end 
end

N = max(size(frames));

% Kuvan koko ja määritellään formaatti
[r, c, d] = size(frames{1});
for k=1:max(size(formats))
    vertsize = formats(k).verticalsize;
    if (r == vertsize) 
        frameformat = formats(k).name;
    end
end


figure(1)
% Jos kuvia pariton määrä
if (mod(N, 2) == 1)
    row = ceil(N/3);
    column = 3;
% Jos kuvia parillinen määrä
else 
    row = ceil(N/6);
    column = 6;
end

for i=1:N
    subplot(row, column, i)
    imshow(frames{i})
end

figure(2)
posvec=[50 150 1024 768];
figure('Color',[0.5 0.5 0.5],'Position',posvec) 
rgbframe=frames{1}; 
imagehandle=image(rgbframe);
axis equal; axis off;
for index=2 : max(size(frames))
    rgbframe=frames{index}; % cell-type variable 
    set(imagehandle,'Cdata',rgbframe); drawnow; 
    pause(0.1)
end
    

end

