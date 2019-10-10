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
| test1.md (L)  | b73dcdcfc11d992357ee9919451f179c  |
| test2.md (p) | 15354a2feca5dda278e5dd0dc4ab443c  |

2. Užduotis: du failai su visiškai skirtingais tekstais (virš 10000 simbolių)

| Failai  | Output |
| ------------- | ------------- |
| test3.md (99999 simbolių) | f069e02a3b02edc58ab5c7e2fa75de6d  |
| test4.md (~100000 simbolių)  | 9a295f331cd05bde290c760f96a3c77d  |

3. Užduotis: failai skiriasi tik vienu simboiu

| Inputas  | Output |
| ------------- | ------------- |
| test5.md (paprastas tekstas) | fa62e5fd916af2c4b57ebc82f9ea563e |
| test6.md (tekste pakeista paskutinė raidė)  | 09d68f4dcf9df6225b4b5a2b8ef224d4  |

4. Užduotis: tuščias failas

| Inputas  | Output |
| ------------- | ------------- |
| test7.md  | 0fe4f2cafe4f1ec7e935a6a680dedafa  |

#### 2 dalis

Ištirkite Jūsų sukurtos hash funkcijos efektyvumą: tuo tikslu suhash'uokite kiekvieną eilutę iš konstitucija.txt failo.

| Bandymas  | Laikas |
| ------------- | ------------- |
| 1  | 0.006505 s |
| 2  | 0.0065179 s  |
| 3  | 0.0071385 s |

#### 3 dalis

Susigeneruoti bent 100 000 atsitiktinių simbolių eilučių (string'ų) porų ir patikrinti hashu pasikartojimų

| Bandymas  | Hashu pasikartojimas |
| ------------- | ------------- |
| 1  | Nesutapusiu hashu skaicius: 100000 is 100000 |
| 2  | Nesutapusiu hashu skaicius: 100000 is 100000  |
| 3  | Nesutapusiu hashu skaicius: 100000 is 100000 |