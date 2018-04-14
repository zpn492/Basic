# liv1 <br />
### Find reference til bogen 'Basic Life Insurance Mathematics af Ragnar Norberg', under annuity.hpp
> Akkumuleretværdi <br />
> Nutidsværdi <br />
> Rentetilskrivning <br />
> Dødsintensitet <br />
> Passiv <br />
> Opsparede beløb <br />
<br />

> Akkumuleretværdi <br />
```c++
// På en bankbog indsættes 10.000 kr., der forrentes med 8 procent p.a. 
// Såfremt de tilskrevne renter og det indskudte beløb ikke hæves, 
// vil der efter 10 år stå 21.589,25 kt. på kontoen, idet 10.000 * 1,08^10 = 21.589,25.

double k0 = liv1::accumulated(liv1::NORMAL, 10000, 0.08, 10);
``` 

> Nutidsværdi <br />
```c++
// Hansen ønsker at købe en ny bil om 5 år. Bilen skønnes at koste 150.000 om 5 år. 
// Hvor stort et beløb skal Hansen idag sætte ind på en konto, der giver 8 pct. p.a., 
// hvis der om 5 år skal stå 150.000 kr. på kontoen? Der skal stå 150.000 * 1,08^(-5) = 102.087,48 kr.

double kn = liv1::retrospective(liv1::NORMAL, 150000, 0.08, 5);
``` 

> Rentetilskrivning <br /> 
```c++
// Ènkelt beløb, der forrentes med en statisk rente til 8 ptc., og forrentes hvert år i 10 år. 

double Enkelt_Betaling = liv1::annuity(liv1::RETROSPECTIVE, liv1::NORMAL, 0.08, 10);
```
$K_0 = (1 + i)^(-n) * K_n$

```c++
// Løbende indbetaling(bagudbetalt) af et statisk beløb. 
// Èn indbetaling indsættes på tidspunkt t og forrentes (n-t+1) gange, 
// hvor n svarer til antal indbetalte år, her er det 10 år.
// Den sidste indbetaling kommer på tidspunkt n og forrentes ikke.

double Kontinuerlig_Betaling_Bagudbetalt = liv1::annuity(liv1::RETROSPECTIVE, liv1::AFTERWARD, 0.08, 10);
```
$K_0  = \frac{1-(1+i)^(-n)}{i}$

```c++
// Løbende indbetaling(forudbetalt) af et statisk beløb. 
// Èn indbetaling indsættes på tidspunkt t og forrentes (n-t) gange, 
// hvor n svarer til antal indbetalte år, her er det 10 år.
// Den sidste indbetaling kommer på tidspunkt n-1 og forrentes frem til n.

double Kontinuerlig_Betaling_Forudbetalt = liv1::annuity(liv1::RETROSPECTIVE, liv1::FORWARD, 0.08, 10);
```
$K_0  = (1+i)\frac{1-(1+i)^(-n)}{i}$

Anvendelse af rentetilskrivning foregår ved at kalde liv1::accumulated eller liv1::retrospective, hvori der angives rentetilskrivningsmetode, beløb, rente og termin.


> Dødsintensitet <br />
```c++
// Beregner på baggrund af Gompertz-Makeham parametre,
// hvor mange mænd der overlever til alder x

double Overlevende_Mænd = liv1::lx(x);

// Sandsynligheden for at være x år og overleve til alder x + n, 
// findes ved at se hvor mange der bliver x+n år, 
// divideret med hvor mange der bliver x år 

double npx = liv1::lx(x+t) / liv1::lx(x);

// Hansen er 30 år, hvor stor er sandsynligheden,
// for at han overlever, til han bliver 60 år?

double npx = liv1::npx(30, 30);

// Hvis Gompertz-Makeham ikke er tilstrækkelig, kan dødsintensiteten loades via en .csv
// formatet på .csv filen forventes at være semikolon separeret med følgende headers
// x;mu_x(float);f_x;l_x;d_x;q_x

liv1::MortalityTable mt("data/G82.csv);

Overlevende_Mænd = mt.lx(x);

npx = mt.npx(n, x);
```

> Passiv <br />
```c++
// Passiv er den betegnelse, der anvendes for kapitalværiden af 1 kr. forsikringsydelse

// En 30-årig mand ønsker at få udbetalt 1 kr., hvis han er i live 
// som 60-årig. Ved død før 60 år skal der ikke udbetales noget.

// Sandsynligheden for at man som 30-årig bliver 60 år.

double Bliver_60 = liv1::npx(30, 30);

// Hvad skal der lægges til side for at have 1 kr. efter 30 år, med 4,5 % rente p.a.?

double Startkapital = liv1::retrospective(liv1::NORMAL, 1, 0.045, 30);

// Vi kan nu beregne passivet, som sandsynligheden for at opnå udbetaling
// gange med en startkapitalen for at opnår 1 kr. med 4,5 % rente p.a. i 30 år.

double Passiv = Bliver_60 * Startkapital;

// Værdien kan også findes direkte via funktionen passiv.
// Denne funktion anvender diskontering.
double Passiv_Diskontering = liv1::passiv(1, 0.045, 30, 30);
```

> Opsparede beløb <br />
```c++
// En kunde på 30 år sparer 42.000 op om året, altså lige knap 3.500 om måneden.
// Opsparingen forrentes med 0,5 % p.a., vis udviklingen af depotet efter 5 år.
// Resultatet: 197.928,-

int t = 5;
double Depot_Værdi_Efter_5_År = 
    liv1::npx(30-t, 30+t) * liv1::accumulated(liv1::AFTERWARD, 42000, 0.05, t)
```
