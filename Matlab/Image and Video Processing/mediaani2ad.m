function [suodatettu]=mediaani2ad(kuva,Smax)
% mediaani2ad Adaptiivinen mediaanisuodin kokoa.
%       [suodatettu] = mediaani2ad(kuva, Smax) palauttaa
%       adaptiivisella mediaanisuodattimellasuodatetun kuvan kuva.
%       Kuvan ympärille lisätään suodatuksen yhteydessä nollia, jotta kuvan
%       koko säilyy. Palautettu kuva ei sisällä enää nollia. Suodatuksessa
%       suodattimen koko on vähintään 3 x 3 ja suurimmillaan Smax.

% Lisätään nollat
nollilla=zeros(size(kuva,1)+(Smax-1), size(kuva,2)+(Smax-1));
suodatettu=zeros(size(nollilla));

for x=1:size(kuva,1)
    for y=1:size(kuva,2)
        nollilla(x+(floor(Smax/2)),y+(floor(Smax/2)))=kuva(x,y);
    end
end

s = floor(Smax/2);
% Suodatus
for i=s+1:size(kuva,1)+s
    for j=s+1:size(kuva,2)+s
        for m=3:2:Smax
            n = m;
            suodin=nollilla(i-floor(m/2):i+floor(m/2),j-floor(m/2):j+floor(m/2));
            suodin2 = sort(reshape(suodin, 1, size(suodin, 1)*size(suodin, 1)));
            zmin = min(suodin2);
            zmax = max(suodin2);
            zmed = suodin2((m*n+1)/2);

            if ((zmed - zmin) > 0) & ((zmed - zmax) < 0)
                [rows,colums] = size(suodin);

                zxy = suodin(ceil(rows/2),ceil(colums/2));

                if ((zxy - zmin) > 0) & ((zxy - zmax) < 0)
                    value = zxy;
                    break
                else
                    value = zmed;
                    break
                end
            else
                if (m + 2 <= Smax) || (n + 2 <= Smax)
                    continue
                else
                    value = zmed;
                    break
                end
            end
        end
        suodatettu(i,j) = value;                  
    end
end

% Poistetaan lisätyt nollat
suodatettu = uint8(suodatettu(s+1:end-s,s+1:end-s));
             
      
end

