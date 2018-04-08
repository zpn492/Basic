# Standard funktioner <br />
> Rentetilskrivning <br />
> Akkumuleretværdi <br />
> Nutidsværdi <br />
> Dødsintensitet <br />
> <br /> <br />

> Akkumuleretværdi <br />
På en bankbog indsættes 10.000 kr., der forrentes med 8 procent p.a. Såfremt de tilskrevne renter og det indskudte beløb ikke hæves, der der efter 10 år så 21.589,25 kt. på kontoen, idet 10.000 * 1,08^10 = 21.589,25. <br />
```
double k0 = liv1::accumulated(liv1::NORMAL, 10000, 0.08, 10);
``` <br /> <br />


> Nutidsværdi <br />
Hansen ønskre at købe en ny bil om 5 år. BIlen skønnes at koste 150.000 om 5 år. Hvor stort et beløb skal Hansen idag sætte ind på en konto, der giver 8 pct. p.a., hvis der om 5 år skal stå 150.000 kr. på kontoen? Der skal stå 150.000 * 1,08^(-5) = 102.087,48 kr. <br />
```
double k0 = liv1::retrospective(liv1::NORMAL, 150000, 0.08, 5);
``` <br /> <br />