Tema practica

22-06-2023

UPDATE:

- nu merge alocare dinamica pe placa, am testat si malloc si new si delete si tot

- cred ca merge static normal ( gen intr-o functie ), dar tre sa testez pt static member ( gen intr-o clasa )

UPDATE:

- cred ca merge si static member ( am facut o clasa test ), doar ca trebuie sa fie si declaratia si definitia in acelasi fisier => s-ar putea sa fie problema de la linkare?

UPDATE:

- am ales sa folosesc namespace-uri ca sa nu imi mai bat capul cu static members si singleton si etc.

- cred ca am terminat cu tsi-ul, am count1 si count2 care par a fi invers proportionali intre ei si se activeaza fiecare din directii opuse de pe touch slider => probabil ii pot folosi ca sa determin pozitia degetului

- ramane de activat led-ul in functie de count 1 si count 2

23-06-2023

- incerc sa transmit prin uart date catre calculator
- problema: tdre nu devine 0 ( adica buffer-ul transmitter-ului nu se descarca )
- imediat dupa ce activez transmitter-ul la initializare, tc spune ca transmitter-ul este busy ( transmite date, break etc. ), dar nici macar nu i-am dat sa transmita ceva, iar tdre e 0 ( buffer-ul de date e gol )

UPDATE:

- am descarcat exemplul din laboratorul cu uart si merge, acum incerc sa-l modific pentru a transmite ce vreau eu

- aparent trebuie neaparat sa pot scrie eu ceva in terminalul de putty, ca sa si primesc ceva inapoi

25-06-2023

- domnul Coca mi-a sugerat sa analizez output-ul pe care incerc sa-l trimit prin UART0 folosing un osciloscop numit Analog Discovery de la Digilent

- am conectat canalul 1 al osciloscopului la pinul PTA1 de la placa si am monitorizat un program care basculeaza in continuu pentru a testa osciloscopul

UPDATE:

- am schimbat iar handler-ul de la UART si acum transmite t in continuu ( probabil gresisem eu data trecuta )

UPDATE:

- daca raman cu main.cpp imi zice ca nu gaseste header file-ul Uart.h la linkare => o sa scriu doar in C de acum in colo

- am facut sa compileze cu succes ambele module impreuna

- acum trb sa incerc sa transmit ce citesc de la TSI in loc de characterul 'c' prin UART0 catre calculator si apoi sa dezvolt o aplicatie python care sa se foloseasca de acele citiri pentru a afisa ceva

26-06-2023

- cu ajutorul lui dragos am reusit sa leg cele 2 variabile ( UART_Output si TSI_readings ); se pare ca trebuia sa le declar externe si sa le dau valoarea in main

- am facut o aplicatie de python in care sa citesc ce se comunica serial pentru a putea vedea in hexa caracterele transmise de la placa la calculator

- deocamdata aplicatia nu este complet functionala

- daca vreau sa restartez aplicatia, trebuie sa scot si sa bag inca o data placa, altfel placa nu mai comunica dintr-un motiv sau altul ( nu mai da output nici pe putty ), chiar daca inchid conexiunea la final de script python

- daca incerc sa transmit ce se afla in variabila UART_Output, in aplicatia mea citesc doar 18 si nu se modifica indiferent de unde pun degetul pe placa, doar ca daca dau cu debug, pare sa se actualizeze cele 2 variabile ( UART_Output si TSI_readings )

UPDATE:

- problema pare sa fie de la faptul ca in UART_Transmit, data nu se actualizeaza ( ramane 0x12, adica 18 ), de ce?

UPDATE:

- daca dau debug si pun breakpoint in handler, se actualizeaza si valoarea si este si transmisa bine catre aplicatie, doar ca se transmite un singur caracter, dupa care trebuie sa restartez aplicatia python ca sa ajunga iar la breakpoint in handler

- daca fac variabilele volatile nu schimba cu nimic

27-06-2023

- am creeat o variabila de status pe care o schimb in mai multe while-uri ca sa vad unde se blocheaza programul

- am observat ca daca opresc debugger-ul in mijlocul transmisiunii ramane blocat in while-ul din scan() din modulul de TSI

- de asemenea aplicatia python pare sa tina tot ce se transmite intr-un buffer => o gramada de valori transmise deja => nu pot vedea defapt ce se transmite in realtime ( adica daca macar placa mai transmite in momentul de fata )
=> de aia inca primeam valori la consola, chiar daca placa era blocata in while in realitate. solutie: dau clear la buffere inainte sa mai citesc

- de ce ramane placa blocata pe scan? de ce nu se termina scan-ul? ( pentru ca daca rezolv asta rezolv si problema )

28-06-2023

- am decis sa incerc sa lucrez cu intreruperi si pentru TSI pentru a evita problemele legate de flag-ul EOSF, flag care pare sa fie setat pe 1 o instantanee => pot aparea probleme daca nu apuca while-ul sa vada acea valoare de 1 in acel moment precis

- handler-ul intreruperii de TSI0 pare sa se execute fara probleme, singurul lucru dubios este faptul ca in TSICNT se citeste mereu valoarea FFFF, dar macar acum scanarea pare sa se termine

- am pus niste conditii: 1. sa scaneze doar daca nu e deja o scanare in progres (GENCS.SCNIP == 0), 2. sa citeasca din TSICNT doar cand a terminat de scanat (GENCS.EOSF == 1). acum in TSICNT nu mai am FFFF, dar ramane la 12. observ ca dupa scanare, cand incerc sa citesc, tsichannel este setat la 0. parerea mea este ca citesc de pe canalul gresit sau ceva de genul, si ar trebui sa setez canalul in alta parte, nu in functia de scanare

- am rezolvat issue #3 : codul de TSI acum foloseste intreruperi si pare sa functioneze bine

- problema noua : acum TSI readings este actualizat in aplicatia python doar la fiecare reset cpu => probabil citesc doar prima valoarea transmisa si ramane asa

- am oprit programul in timpul executarii si uitandu-ma in registrul de TSI, am observat ca defapt se intampla acelasi lucru: flag-ul de SCNIP ( scan in progress ) ramane 1 => scanarea nu se termina => de aia nu se schimba valoarea in aplicatia python. doar prima scanare aduce un rezultat, dupa ramane blocat in scan

UPDATE:

- daca nu opresc programul, dar in schimb pun doar breakpoint-uri nu se intampla problema cu blocarea in scan => s-ar putea sa nu fie o problema reala, ci doar de la oprirea brusca a programului

UPDATE:

- daca transmit flagul scnip prin portul serial in loc de a transmite TSI_Readings, se transmite mereu 1 => scnip s-ar putea chiar sa fie blocat pe 1, dar in cazul asta n-ar fi trebuit sa mai intre in breakpoint....

29-06-2023

- daca pun cate un breakpoint la fiecare dintre cele 2 handlere, transmite scanip = 0 catre aplicatia python => merge cum ar fi trebuit sa mearga, doar daca ii pun breakpoint-uri

- am continuat cu dezovltarea aplicatiei python ca sa am totul pregatit in caz ca reusesc sa rezolv problema, si sa imi devotez tot restul timpului la rezolvarea problemei fara a pierde progres potential

- am terminat aplicatia python, care afiseaza o culoare din intreg spectrul, in functie de valoarea citita de la modulul TSI