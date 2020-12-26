function [rgbkuva]=luekuva(fid, sijainti, korkeus, leveys)
% luekuva Muuttaa kuvat rgb kuviksi.
% [rgbkuva]=luekuva(fid, sijainti, korkeus, leveys) Muuttaa tiedoston fid
% rgb kuvaksi rgbkuva käyttäen apuna sijaintia sekä kuvan korkeutta ja 
% leveyttä.

keyword='FRAME';    %the frame tag to search for

%computing the segment length:
segmentlength = (korkeus*leveys*1.5)+length(keyword)+1;

%moving the pointer to correct location:
status=fseek(fid,sijainti,'bof');
%read the frame data
datavector=fread(fid,segmentlength-length(keyword)-1,'uint8');

%check that the length is correct:
length(datavector) + length(keyword) + 1;
%segmentlength

% reading the frame components from the datavector:
%where it starts	
aa=1;
bb=korkeus*leveys;
	
%reading the Y component
yy=datavector(aa:bb);

%where next component starts
cc=length(yy)+1;
dd=length(yy)+((korkeus/2)*(leveys/2));

%reading the Cb component
ccb=datavector(cc:dd);

%where the last component starts
ee=length(yy)+length(ccb)+1;
ff=length(yy)+length(ccb)+((korkeus/2)*(leveys/2));

%reading the Cr component
ccr=datavector(ee:ff);

% construct image:
Iyy = reshape(yy, [leveys, korkeus]);
Iyy = transpose(Iyy);

Iccb = transpose(reshape(ccb, [leveys/2, korkeus/2]));
Iccr = transpose(reshape(ccr, [leveys/2, korkeus/2]));

Iccb = imresize(Iccb, [korkeus, leveys]);
Iccr = imresize(Iccr, [korkeus, leveys]);

YCbCr = uint8(cat(3,Iyy,Iccb, Iccr));
rgbkuva = ycbcr2rgb(YCbCr);

end

