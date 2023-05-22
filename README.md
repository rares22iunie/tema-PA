Pentru cerinta 1 am creat 4 structuri, tip player. tip player list, team care include si player list si team list.
Totul este facut pe functii care se explica prin nume :>. Spatiile uneori au fost o problema.
Pentru cerinta 2 aflu cea mai aproape putere a lui 2, dupa care in functie caut minimul, tin minte pozitia anterioara minimului, si "prevMin->next = minPointsTeam->next;"
Pentru cerinta 3 mai adaug 2 structuri teamQueue si teamStack, pun din teamlist in queue la inceput dupa joc meciurile, sterg ce se afla in losers, si pun ceea ce este in winners in queue, cand numarul echipelor ramase este 8, adaug cele 8 intr o lista auxiliara winner8, am grija sa dau free la tot ce folosesc sa nu ramana in memorie
Pentru cerinta 4 mai adaug o structura Bst, creez bstul, am grija la spatii, grija mare, eliberez memoria :>
Pentru cerinta 5 sortez cu un mergesort cele 8 echipe ramase, creez avlul, si toate functiile necesare, si apoi intr o functie incepand de la nivelul de jos (0), recursiv o apelez pana ajung la nivelul 2, cand afisez, am grija si la memorie

Solutia am incercat sa fie cat mai modulara, functiile cat mai mici, iar mainul la fel cat mai mic

Dificultati ar fi spatiile ciudat alese :>>
**la testul 15 se intampla ceva ciudat, deoarece la winners of round 1, tot ce este spre exemplu 6.225 se rotunjeste la 6.23, dar in cazul membrului elixir junior, acestea este 6.625 si in rezolvare apare ca 6.62, e singuru care se rotunjeste in jos, si de aceea imi si da failed

Am descoperit ca un program in c poate avea aproape 900 de linii :>>