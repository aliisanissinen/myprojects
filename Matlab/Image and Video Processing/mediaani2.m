function [suodatettu] = mediaani2(kuva,m,n)

% mediaani2 Mediaanisuodin kokoa m x n.
%       [suodatettu] = mediaani2(kuva, m, n) palauttaa
%       mediaanisuodattimella m x n suodatetun kuvan kuva.
%       Kuvan ympärille lisätään suodatuksen yhteydessä nollia, jotta kuvan
%       koko säilyy. Palautettu kuva ei sisällä enää nollia. Suodatuksessa
%       oletetaan että suodattimen m ja n ovat parittomia lukuja.

% Lisätään nollat
nollilla=zeros(size(kuva,1)+(m-1), size(kuva,2)+(n-1));
suodatettu=zeros(size(kuva));

for x=1:size(kuva,1)
    for y=1:size(kuva,2)
        nollilla(x+(floor(m/2)),y+(floor(n/2)))=kuva(x,y);
    end
end

% Suodatus
for i=1:size(nollilla,1)-(m-1)
    for j=1:size(nollilla,2)-(n-1)
        suodin=zeros(m*n,1);
        k=1;
        for x=1:m
            for y=1:n
                suodin(k)=nollilla(i+x-1,j+y-1);
                k=k+1;
            end
        end
        % Järjestetään ja etsitään mediaani
        mediaani=sort(suodin);
        suodatettu(i,j)=mediaani((m*n+1)/2);
       
    end
end

end

