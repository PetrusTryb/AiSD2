# AiSD2
# ![dramaturgy-vtuber](https://user-images.githubusercontent.com/8248412/236293311-b37361ac-404e-4596-9a4c-c72b6fe4a7c8.gif) Jak dojadę?
## Treść zadania projektowego:
<div id="content">
<div id="problemtext"><div id="content"><h3>autor:/author:<br>Krzysztof Ocetkiewicz</h3></div>
<div id="problemtext">Dana jest prostokątna mapa podzielona na kwadraty. Każde pole mapy może być puste (nieprzejezdne), być fragmentem drogi (przejezdnej w każdą stronę) lub miastem (przejezdnym tak jak droga). Nazwa każdego z miast jest podana na mapie i każda litera zajmuje jedno pole (pole z literą jest nieprzejezdne). Przebycie jednego pola zajmuje minutę. Poruszać się możemy tylko pomiędzy polami sąsiadującymi bokami.
Dodatkowo wybrane miasta połączone są jednokierunkowymi połączeniami lotniczymi.
<br>
Nazwa miasta będzie sąsiadowała (bokiem lub rogiem) z miastem pierwszą lub ostatnią literą. Nazwa będzie jednoznacznie przypisana do miasta. Pole przed i za nazwą miasta (o ile będzie takie pole) nie pojawi się cyfra lub litera. </div>
<b>Uwagi implementacyjne:</b>
<ul>
<li>Nie można używać klasy string ani kontenerów z biblioteki STL.</li>
<li>Można używać elementów języka C++ takich jak klasy, referencje, itp.</li>
<li>Można zaimplementować własną klasę string.</li>
<li>Czytelność kodu jest ważna, a komentarze (które są oczywiście dozwolone) niekoniecznie ją zapewniają.</li>
<li>Smartpointer'y z biblioteki standardowej są zabronione, ale nadal można zaimplementować własną klasę inteligentnych wskaźników.</li>
<li>Proszę pamiętać o odzyskiwaniu pamięci podczas usuwania elementów implementowanych struktur danych.</li>
</ul>
------------------------------------------------------------------------------------------------------------------------
<div id="problemtext">A rectangular map divided into squares is given. Each field on the map can be empty (impassable), be part of a road (passable in both directions), or be a city (passable like a road). The name of each city is given on the map, and each letter occupies one field (the field with the letter is impassable). Moving through one field takes one minute. We can only move between fields adjacent by sides. Additionally, selected cities are connected by one-way air connections. The name of a city will be adjacent (by side or corner) to the city with the first or last letter of the name.
<br>
The name will be unambiguously assigned to the city. There will be no number or letter before or after the name of the city (if there is such a field).</div>

<b>Implementation notes:</b>
<ul>
<li>Standard string class and other standard library containers cannot be used.</li>
<li>You can use C++ elements such as classes, references, etc. </li>
<li>One can implement their own string class.</li>
<li>Code readability is important, and comments (which are of course allowed) do not necessarily ensure it.</li>
<li>Smartpointers from standard library are forbidden, but you can still implement your own smartpointer class.</li>
<li>Please remember to free memory when deleting elements of the implemented data structures.</li>
</ul>

Przykłady:/Examples:<br>
<br>
<b>Tak może być</b>:/<b>This can be</b>:
<pre>*GDANSK....OPOLE....RUMIA
...*GDYNIA......*....*...
*SOPOT.............*....*
...PUCK*.*KRAKOW.REDA.HEL
</pre>
<b>Tak nie będzie</b>:/<b>This is incorrect</b>:
<pre>**GDANSK..........OPOLE.
..........*GDYNIA*......
*SOPOTHEL...............
........*..REDA.*PUCK*..
</pre>
<br>
<b>Z A można dotrzeć do B</b>:/<b>It is possible to arrive from point A to B</b>:
<pre>..................
A*####...#####*B..
.....#.C.#........
.....##*##........
</pre>
<pre>......
.A**B.
......
</pre>
<br>
<b>Z A nie można dotrzeć do B</b>:/<b>It is not possible to arrive from point A to B</b>:
<pre>....##*B
A*##....
</pre>
<pre>....##*B
A*#*C...
</pre>
<pre>....*....
A*##C##*B
</pre>
<!--
<h3>Etap 1</h3>
Program powinien poprawnie odpowiadać na zapytania.
<h3>Etap 2</h3>
Należy zaimplementować algorytm Dijkstry wykorzystując każdą ze struktur do przechowywania etykiet wierzchołków:
<ul>
<li>tablicę</li>
<li>kopiec binarny</li>
</ul>
i zbadać czasy wykonania dla losowych grafów małych, średnich i dużych (np. <i>n</i>=10, 100, 1000, 10000, 100000 wierzchołków), rzadkich (liczba krawędzi kilkukrotnie większa od liczby wierzchołków), przeciętnych (liczba krawędzi rzędu <i>n</i>log<i>n</i> czy <i>n</i>log<sup><font size="-3">2</font></sup><i>n</i>) i gęstych (liczba krawędzi bliska maksymalnej, rzędu 0.2-0.5 * <i>n</i><sup><font size="-3">2</font></sup>). Wyniki i wnioski z przeprowadzonych testów należy zawrzeć w sprawozdaniu i przedstawić je na zajęciach.
-->
<h3>Wejście:/Input:</h3>
W pierwszej linii wejścia pojawią się wymiary mapy: szerokość <i>w</i> i wysokość <i>h</i>. W następnych <i>h</i> liniach (każda po <i>w</i> znaków) podany będzie opis mapy. Każdy znak opisu to kropka (.) oznaczająca puste pole, krzyżyk (#) reprezentujący drogę, gwiazdka (*) symbolizujący miasto lub litera bądź cyfra, będąca częścią nazwy miasta.<br>
W kolejnej linii pojawi się jedna liczba <i>k</i> – liczba połączeń lotniczych. Następne <i>k</i> linii to opis połączeń w postaci <i>źródło</i> <i>cel</i> <i>czas</i>, gdzie <i>źródło</i> to nazwa miasta startowego, <i>cel</i> to nazwa miasta docelowego a <i>czas</i> jest czasem przelotu w minutach.
W kolejnej linii pojawi się jedna liczba <i>q</i> będąca liczbą zapytań. Każde zapytanie
pojawi się w osobnej linii i będzie miało format: <i>źródło</i> <i>cel</i> <i>typ</i>. Jest to zapytanie o najkrótszy czas przejazdu od miasta <i>źródło</i> do miasta <i>cel</i>. Typ równy zero oznacza zapytanie tylko o czas. Gdy zapytanie ma typ równy jeden, należy także podać trasę przejazdu.<br>
------------------------------------------------------------------------------------------------------------------------
<br>
The first line of input will contain the dimensions of the map: width w and height h. The next h lines (each containing w characters) will describe the map. Each character in the description is a dot (.) representing an empty field, a cross (#) representing a road, an asterisk (*) representing a city, or a letter or number that is part of the city name.<br>
The next line will contain a single integer k - the number of flight connections. The next k lines will describe the connections in the format source destination time, where source is the name of the starting city, destination is the name of the destination city, and time is the flight time in minutes.
The next line will contain a single integer q - the number of queries.
Each query will appear on a separate line and will have the format source destination type.
This is a query for the shortest travel time from the source city to the destination city.
If the type is zero, the query is only for the time. If the type is one, the route should also be provided.

<h3>Wyjście:/Output:</h3>
Na wyjściu należy wypisać dla każdego zapytania jedną linię. Na początku linii powinna pojawić się liczba, będąca najkrótszym czasem podróży pomiędzy miastami. Jeżeli zapytanie ma typ równy jeden, należy także wypisać, po spacji, wszystkie miasta pośrednie (bez startowego i końcowego) w kolejności ich odwiedzania.<br>
------------------------------------------------------------------------------------------------------------------------
<br>
For each query, output one line. At the beginning of the line should be the number representing the shortest travel time between the cities. If the query has a type of one, all intermediate cities (excluding the starting and ending cities) should also be listed in the order they were visited, separated by spaces.

<h3>Testy:</h3>
<a href="http://stos.eti.pg.gda.pl/~goluch/testy/mapa.zip">Tutaj</a><br>
Opis testów:<br>
1 - przykład<br>
2 - minimalny<br>
3 - poprawność czytania etykiet<br>
4 - poprawność<br>
5 - prosty test na kracie<br>
6 - mały wachlarz<br>
7 - mała ścieżka<br>
8 - mały graf pełny<br>
9 - duża mapa, mało miast<br>
10 - duża mapa, mało miast<br>
11 - wachlarz, implementacja z tablicą raczej nie zmieści się w czasie<br>
12 - spirala, rekurencja implementacja przeszukiwania przepełni stos<br>
13 - długa ścieżka, implementacja z tablicą raczej nie zmieści się w czasie<br>
14 - dużo krawędzi<!--, implementacja z kopcem raczej nie zmieści się w czasie--><br>
<!--<b>Uwaga:</b> program nie musi zaliczyć wszystkich testów (w zależności od implementacji
może nie zmieścić się w czasie w testach (11 i 13) lub (14) ), ale wszystkie pozostałe
(1-10, 12) poprawne rozwiązanie powinno przechodzić.<br/>
W przypadku wyniku "błąd wewnętrzny" albo jest to przekroczenie limitu czasu, albo wygenerowanie za dużego wyjścia (rzędu 500MB). Błąd wewnętrzny w jednym teście nie wpływa
na pozostałe testy.-->

<h3>Tests:</h3>
<a href="http://stos.eti.pg.gda.pl/~goluch/testy/mapa.zip">Here</a><br>
Opis testów:<br>
1 - example<br>
2 - minimum<br>
3 - label reading correctness<br>
4 - correctness<br>
5 - simple test on a grid<br>
6 - small fan<br>
7 - small path<br>
8 - small complete graph<br>
9 - large map, few cities<br>
10 - large map, few cities<br>
11 - fan, array implementation may not fit in time<br>
12 - spiral, recursion implementation of search overflows the stack<br>
13 - long path, array implementation may not fit in time<br>
14 - many edges<!--, implementacja z kopcem raczej nie zmieści się w czasie--><br>

<h3>Przykład:/Example:</h3>
<pre><b>Wejście:/Input:</b>
20 20
.........GDANSK.....
........*...........
........#...........
........#...........
*##################.
#SZCZECIN.........#.
#.................#.
##................#.
.############*#####.
.#...WARSZAWA.......
.#..................
.#############......
.#...........#......
.#..WROCLAW.##......
.#..*.......*.......
.####.......#KIELCE.
......*##.#########.
.OPOLE..#.*.......#.
........#.KRAKOW..#.
........###########.
0
3
KIELCE KRAKOW 0
KRAKOW GDANSK 0
KRAKOW GDANSK 1

<b>Wyjście:/Output:</b>
5
40
40 KIELCE SZCZECIN

</pre></div></div>
