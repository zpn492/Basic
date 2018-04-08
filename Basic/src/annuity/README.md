# Standard funktioner <br />
> Akkumuleretværdi <br />
> Nutidsværdi <br />
> Rentetilskrivning <br />
> Dødsintensitet <br />
<br />

> Akkumuleretværdi <br />
```c++
// På en bankbog indsættes 10.000 kr., der forrentes med 8 procent p.a. 
// Såfremt de tilskrevne renter og det indskudte beløb ikke hæves, 
// der der efter 10 år så 21.589,25 kt. på kontoen, idet 10.000 * 1,08^10 = 21.589,25.

double k0 = liv1::accumulated(liv1::NORMAL, 10000, 0.08, 10);
``` 


> Nutidsværdi <br />
```c++
// Hansen ønskre at købe en ny bil om 5 år. Bilen skønnes at koste 150.000 om 5 år. 
// Hvor stort et beløb skal Hansen idag sætte ind på en konto, der giver 8 pct. p.a., 
// hvis der om 5 år skal stå 150.000 kr. på kontoen? Der skal stå 150.000 * 1,08^(-5) = 102.087,48 kr.

double k0 = liv1::retrospective(liv1::NORMAL, 150000, 0.08, 5);
``` 

> Rentetilskrivning <br /> 
```c++
// Ènkelt beløb, der forrentes til en statisk rente til 8 ptc., over 10 år. 

double Enkelt_betaling = liv1::interest(liv1::RETROSPECTIVE, liv1::NORMAL, 0.08, 10);
```

```c++
// Løbende indbetaling(bagudbetalt) af et statisk beløb. 
// Èn indbetaling indsættes på tidspunkt t og forrentes (n-t+1) gange, 
// hvor n svarer til antal indbetalte år, her er det 10 år. <br />
// Den sidste indbetaling kommer på tidspunkt n og forrentes ikke.

double Kontinuerlig_Betaling_Bagudbetalt = liv1::interest(liv1::RETROSPECTIVE, liv1::AFTERWARD, 0.08, 10);
```

```c++
// Løbende indbetaling(forudbetalt) af et statisk beløb. 
// Èn indbetaling indsættes på tidspunkt t og forrentes (n-t) gange, 
// hvor n svarer til antal indbetalte år, her er det 10 år. <br />
// Den sidste indbetaling kommer på tidspunkt n-1 og forrentes frem til n.

double Kontinuerlig_Betaling_Forudbetalt = liv1::interest(liv1::RETROSPECTIVE, liv1::FORWARD, 0.08, 10);
```

Anvendelse af rentetilskrivning foregår ved at kalde liv1::accumulated eller liv1::retrospective, hvori der angives rentetilskrivningsmetode, beløb, rente og termin.
