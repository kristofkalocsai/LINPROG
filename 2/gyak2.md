# LAB #2: 02.24 eloadas potlasa
## Fordito (GCC)
- GNU compiler collection

  parancssori forditoprogram, szamos parameterrel
  - tobbnyire csak keveset hasznalunk
  - **pkg-config** leegyszerusiti a dolgokat

param                  | meaning
:--------------------- | :------------------------------------------------------------------------
-o filename            | kimeneti allomany neve
-c                     | forditas, linkeles nelkul
-Ddefinition=x         | definition makrot x ertekure allitja
-Ifolder               | itt kell megadni a hivatkozott headereket
-Lfolder               | itt keresi a library allomanyokat
-llibrary              | linkeli a library nevu programkonyvtart
-static                | default dinamikus linkeles helyett a statikus programkonyvtarakat linkeli
-g, -gN, -ggdb, -ggdbN | leforditott allomanyt ellatja a hibakereseshez szukseges infokkal
-O, -ON                | optimalizacio (-O0 kikapcsolja, pl debughoz kikell!)
-Wall                  | osszes gyakran hasznalt warning megjelenik a kimeneten
### forditas pelda
 tobb forras eseten ```gcc -o program forras1.c forras2.c```
 **lasd diakon**

## Makefile
- automatizalt forditas
- dependency tree a muveletek kozott
- modositaskor csak a fanak megfelelo reszet jarja vegig
- nem csak forditasra jo, barmilyen parancsot keszithetunk
- vagy **Makefile** vagy **makefile** vagy **Makefile**

```makefile
# Makefile
objs = ...
args = ...

```
- explicit szabalyok lasd diak!

```makefile
target: prequisites; recipe
<TAB>recipe
<TAB>...
```
