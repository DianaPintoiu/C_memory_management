___________________________TEMA 1 IOCLA: MOMENTE DISPERATE____________________

Durata : 24 de ore
Dificultate: peste medie (zic)
Titlu : Foarte bun, au fost niste momente disperate


_______________________________IMPLEMENTARE_____________________________________

MAIN:
	Am alocat data_structure-ul dinamic, iar linia pe care o citesc de la tastatura
la fel. Am implementat un while care o sa mearga mereu pana la comanda exit
unde va iesi din while si se va incheia programul (cu ajutorul unui break).
Se citeste prima linie si se va lua primul cuvant din citesc, acestea fiind 
comparat cu insert/insert_at/delete_at/find print/exit.
	Daca primul cuvant este insert, atunci am o variabila len, initial 0,
care va creste odata cu adaugarea in vectorul data din structura structura 
(data_structure). Se va trece cu strtok la urmatorul cuvant care este tipul bacnotelor,
si acesta va fi memorat in structura structura->head->type. Se va aloca memorie 
vectorului data din structura (len) si se va copia cu memcopy primul cuvant din linie,
aka numele celui care da dedicatie. Dupa, in functie de ce tip a fost memorat, (1 ,
2 sau 3) se va defini ca un tip de date de diferiti octeti . Pentru tipul 1
bacnota 1 si bacnota 2, sunt definite cu int8_t , adica un octet. Caracterul citit va 
fi schimbat in int cu atoi si apoi memorat in vectorul data din structura cu memmove si 
len (length- ul) care trebuie, adica 2. La fel si pentru bacnota 2 (bac2). Pentru tipul 2
bacnota 1 si bacnota 2, sunt definite cu int16_t , adica un octet. Caracterul citit va 
fi schimbat in int cu atoi si apoi memorat in vectorul data din structura cu memmove si 
len (length- ul) care trebuie, adica 2. Pentru bacnota 2 (bac2), cu int32_t.
Pentru tipul 3 bacnota 1 si bacnota 2, sunt definite cu int8_t , adica un octet. 
Caracterul citit va  fi schimbat in int cu atoi si apoi memorat in vectorul data
din structura cu memmove si len (length- ul) care trebuie, adica 2. 
La fel si pentru bacnota 2 (bac2). La final se va citi ultimul cuvant , la fel ca primul,
bagata in vectorul data si marit len cu cat trebuie. 
La final se va apela functia add_last -add_last(void **arr, int *len, data_structure *data)
care adauga in vectorul arr toate aceste detalii
dar in alt format(vorbim cand ajungem sa discutam de acea functie), apoi se va elibera 
memoria alocata (din structura/vectorul data din structura).
	Daca primul cuvant este insert_at o sa  fie aceeasi implemetare ca la insert 
in afara de un caracter inainte care zice pe ce pozitie vom insera aceste date. 
Se va transforma in int cu atoi si apoi la final cand se apeleaza functia, va fi si 
acest index ca parametru -add_at(void **arr, int *len, data_structure *data, int index).
	Daca primul cuvant e delete_at atunci va mai avea dupa un caracter care va fi 
indexul unde va trebui sters elementul de pe acea pozitie. Indexul va fi transformat
in int cu atoi, apoi se va apela functia de delete (delete_at(&arr, &len_arr, index);).
	Daca primul cuvant e find atunci va mai avea un caracter care va fi indexul
unde va afisa elementul de pe acea pozitie(daca exista element pe acea pozitie ).
Se va apela cu find(arr, len_arr, index); .
	Daca primul cuvant e print atunci se va apela functia de print.
	Daca primul cuvant e exit, atunci e singurul cuvant si doar se va elibera 
memoria din structura din vectorul arr care memora toate elementele si din vectorul
ce citeste fiecare linie, iar apoi se iese din while.




_________________________FUNCTIA ADD_LAST________________________________

	Daca len(care este lungimea elementelor din vector ,  initial 0) este 0 
atunci se aloca length-ul vectorului care trebuie introdus plus 5 pentru tip.
Altfel se va parcurge putin ciudat vectorul data(mie imi place si am ceva pt 
terminatori de sir, am reusit intr-un final sa implementez si sa mearga ,dar pain). 
Asadar, variabila parcurgeri, initial 0, variabila terminator ;) , initial 0
Se vor adauga elemente cat timp parcurgerile sunt mai mici decat len array-ului arr, 
adica vreau sa stiu pe ce pozitie o sa inserez noul meu element. De aceea am un 
element_length, initial 0(la inceputul functiei), care va creste cu cat parcurg 
vectorul arr. Voi memora prima data in variabila char tip, tipul fiecarui element 
(e o micunealta secreta pentru mai tarziu) . Daca aceasta memorare voi creste
element_length cu 5 , iar terminatorul meu il initializez cu 0. Voi parcurge vect arr
cat timp nu gasesc terminator si voi adauga la element_length cate 1 ( adica + 1). 
Daca arr a ajuns la terminatorul cuvantului ( mai precis al primului nume) se va 
opri while-ul  (terminator = -1;). Dupa aceea,a daca tipul pe care l-am memorat la
inceput este 1, element_length se va aduna cu 2, daca este egal cu 2, se va aduna cu 
6 , iar daca este egal cu 3, se va aduna cu 8 (pt cati biti trebuie sa lasi pt memorie).
Again, aceeasi idee la al doilea cuvant cu terminatorul. La final dupa ce se 
parcurge un element intreg parcurgeri va creste. Dupa ce se termina while-ul, se va
realoca memoria cu cat trebuie, adica cu element_length si len - ul nou care trebuie
introdus plus 5 pentru tip. Se va adauga cu memmove la arr + element_length prima data 
tipul , iar element_length va creste cu 1. Apoi la fel pentru len-ul datei si va creste 
cu 4. La final se adauga in memoria arr-ului data ul din data , iar len-ul array-ului
arr creste cu unul deoarece s-a adaugat un element nou.



_________________________FUNCTIA ADD_AT_______________________________________

	Aici aveam cam aceeasi infrastructura ca la add_last,  dar avem un index deci
adaugam cand spune domnul index. Daca e mai mic decat 0 indexul, inseamna ca e gresit 
si dam return -1, altfel daca e mai mare decat length-ul , o sa il adaugam ultimul,
folosim functia de add_last . Altfel acum se incepe treaba. Se va face aceeasi parcurgere 
a vectorului arr , doar ca acum pana unde trebuie sa adaugam (adica pana la index) ,
iar element_length-u; acela va fi memorat in length_to_insert_at.
Dupa aceea se parcurge normal pana se termina elementele din vector.
Asadar la final o sa avem :
   ------- un element_length care este pana la finalul vectorului
   -------- un length_to_insert_at care este pana unde trebuie inserat noul element.
Se va realoca arr ul cu element_length + data->header->len + 5. 
Se va memora de la pozitia de dupa ce ar fi inserat elementul adica 
 length_to_insert_at + data->header->len + 5, vectorul de la pozitia de unde trebuie
 inserat, pentru a nu suprascrie peste vector. Apoi se va memora de la pozitia de 
unde trebuie inserat,prima data type-ul apoi len-ul si apoi data-ul . 
La final, va creste len-ul array-ului arr deoarece s a adaugat un element nou.  
 


__________________________FUNCTIA FIND________________________________________

	La aceasta functie se afiseaza la indexul index elementul sub o anumita
forma  
EXEMPLU CUM TREBUIE SA ARATE :
           Tipul 3
           Andrei pentru Teo
           100283912
           12312312

	Asadar, daca indexul este mai mic decat 0 sau mai mare decat nr de elemente din 
vector nu se va afisa nimic si se va iesi din functie. Altfel se va parcurge 
fiecare element din vector pana cand i-ul ca fi egal cu indexul si se va afisa 
elementul de pe acea pozitie. Pana cand se gaseste elementul de pe pozitia index,
se va parcurge cum s-a parcurs si in insert, si se va aduna la nr de elemente,
element_length. Cand se gaseste elementul ce trebuie afisat , se memoreaza tipul,
si se afiseaza sub aceasta forma " printf("Tipul %c\n", tip);  ", iar element_length
va creste cu 5. Dupa se parcurge numele primei persoane pana la terminatorul de nume,
se va afisa caracter cu caracter, iar element_length-ul creste. Dupa aceea 
se afiseaza cuvantul pentru. Dupa trebuie memorate bacnotele care pot fi de 3 tipuri,
tipul 1 (bac1 si bac2 amandoua de tip int8_t) , de tipul 2 (bac12 de tipul int16_t
 si bac22  de tipul int32_t ) si de tipul 3 (bac13 si bac23 amandoua de tipul int32_t).
Element_length va creste conform tipului . (Bacnotele se memoreaza cu memmove).
Dupa urmeaza urmatorul cuvant/nume care se parcurge si afiseaza la fel ca primul.
La final se afiseaza fiecare bacnota pe cate o coloana, bacnotele memorate in functie 
de ce tip sunt.




_________________________FUNCTIA DELETE_AT________________________________________

	Functia trebuia sa streag aelementul de pe un anumit index, iar daca indexul 
este mai mic decat 0, sau mai mare decat length ul array-ului , atunci se va 
returna -1. Altfel , se va parcurge la fel ca la add_at , iar dupa ce se parcurge
 pana la index length_to_be_deleted_at primeste element_length. Daca index+1 este 
egal cu len ul lui arr atunci este ultimul element si doar se realoca arr-ul cu
 element_length-ul pana la cel care trebuie sters. Altfel se va parcurge elementul
care trebuie sters, iar la final length_end_to_be_deleted primeste element_length .
Apoi se va parcurge vectorul pana la final , element_length fiind length-ul vectorului
inainte sa se stearga un element. Dupa se va muta memoria de unde trebuie sters
 elementul(length_to_be_deleted),de la cea de unde se termina elementul care 
trebuie sters (length_end_to_be_deleted) si se muta 
element_length - length_end_to_be_deleted elemente. Dupa aceea se realoca memoria 
fara elementul care trebuie sters. La final len-ul vectorului arr, adica cate elemente
sunt in vector, scade cu unul.




_____________________________FUNCTIA PRINT_________________________________________


	Aproape la fel ca functia de find, dar se vor afisa toate elementele care exista
in vector, nemaifiind nevoie de acel if.



_______________________________FINAL THOUGHTS_______________________________________




	A fost o tema destul de grea , iar faptul ca am primit un clarificari destul de
tarziu nu a ajutat. In final, sunt fericita ca am reusit sa o termin si ca "Momente 
Disperate"  m-a ajutat sa invat cum sa ma descurc cu gdb-ul. De asemenea, odata ce intelegi
ce se intampla si ce doreste cerinta de la tine e o tema care nu dureaza asa de mult. 
Frumos enuntul a facut toata aceasta experiente mai usor de strabatut. 


# C_memory_management
