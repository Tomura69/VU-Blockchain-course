# VU-Blockchain-course

## v0.1

### Hash'avimo funkcijos idėja
  * Idėja labai paprasta, inputo simbolius pasiversti skaičiais ir juos sudėti. Taip gaunamas unikalus skaičius, kuris priskirtas tam
  inputui. Tada tas skaičius modifikuojamas ir išgaunamas vektorius, kuris saugo skaičius (49, 100, 57, 97). Tie skaičiai
  yra paverčiami į `char` simbolius ir taip išgaunama hash'as.
  * skaičius [48, 57]
  * raidė [97, 102]

### Programos naudojimas
Naudoti programą yra labai paprasta:
  * Atsisiųsti visus failus
  * Atsidaryti `command line`
  * Įveskite žodį `make`
  * Toliau vykdykite instrukcijas koncolėje
  
### Analizė:
#### 1 dalis

1. Užduotis: du failai su vienu skirtingu simboliu

| Failai  | Output |
| ------------- | ------------- |
| test1.md (L)  | 974b67120f56b50378fd126a974b671  |
| test2.md (p) | 6a56f2012d1f7867b340759b6a56f20  |

2. Užduotis: du failai su visiškai skirtingais tekstais (virš 10000 simbolių)

| Failai  | Output |
| ------------- | ------------- |
| test3.md (99999 simbolių) | fb19d527100423fb6756a867fb19d52  |
| test4.md (~100000 simbolių)  | b957043b7687f1d2102f65a6b957043  |

3. Užduotis: failai skiriasi tik vienu simboiu

| Inputas  | Output |
| ------------- | ------------- |
| test5.md (paprastas tekstas) | 576609e1752f7377f8009dfb49c5f560 |
| test6.md (tekste pakeista paskutinė raidė)  | 61f70b501649a2d8356f27b761f70b5  |

4. Užduotis: tuščias failas

| Inputas  | Output |
| ------------- | ------------- |
| test7.md  | 7d3404c72540ec76f4b0146844c1e58a  |

#### 2 dalis

Ištirkite Jūsų sukurtos hash funkcijos efektyvumą: tuo tikslu suhash'uokite kiekvieną eilutę iš konstitucija.txt failo.

| Bandymas  | Laikas |
| ------------- | ------------- |
| 1  | 0.006505 s |
| 2  | 0.0065179 s  |
| 3  | 0.0071385 s |