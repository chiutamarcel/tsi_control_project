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