/*
Willkommen zum ersten Aufgabenblatt vom Programmierkurs.

Diese Datei enthält Aufgabenstellungen als Kommentare, sowie Bereiche in denen die Lösungen implementiert werden können.
Nachdem Sie in einem Terminal mittels des `cd` Befehls in das Verzeichnis gewechselt sind, in dem diese Datei liegt,
können Sie mit folgendem Befehl ihre Lösungen überprüfen:
cc -std=c11 -g -Wall 01ex_test.c -o 01ex_test.o -lm && ./01ex_test.o

Mehr Details dazu gibt es in der ersten Aufgabenstellung, außerdem wird dieses System ausführlich im ersten Tutorium vorgestellt.

Auf diesem Blatt geht es unter anderem um:
- Variablendeklarationen (`int variable_name = expression;`)
- Variablenzuweisungen (`variable_name = expression;`)
- Arithmetische Ausdrücke (+, -, *, /, %)
- Vergleichsausdrücke (==, !=, <, <=, >, >=)
- if Abfragen
- while und for Schleifen
*/

/*
Um ein automatisch überprüfbares Aufgabenblatt bereitzustellen, müssen wir einige Aspekte der
C Programmiersprache verwenden, die Sie noch nicht durch die Vorlesung kennen.
Daher werden wir explizit mit Kommentaren markieren, welche Teile der Datei Sie verändern sollen.
Allen anderen Code in der Datei, wie z.B. die folgenden vier Zeilen, können Sie ignorieren.
*/
#include <stdio.h>

int simple_assignment(int a, int b) {
    int result = 0;
    /*
    Aufgabe 1a:
    Haben Sie die vorgehenden Zeilen ignoriert? Sehr schön!

    Hier beginnt nun die erste Aufgabe. In allen Aufgaben markieren wir den Teil, in dem Sie Code einfügen sollen,
    mithilfe zweier Kommentare: "BEGIN CHANGES" und "END CHANGES". Als erste Aufgabe, sollen Sie schlicht
    die Codezeile `result = a + b;` zwischen diesen beiden Kommentaren einfügen, und dann weiterlesen.
    */
    /* BEGIN CHANGES */
    result = a * b;
    /* END CHANGES */
    /*
    Die Codezeile, die Sie eingefügt haben, weist der Variable `result` die Summe der beiden Variablen `a` und `b` zu.
    Die Initialisierung dieser Variablen haben wir für Sie übernommen. Warum der Aufwand? Weil wir diesen Code
    automatisch überprüfen können. Dazu müssen Sie in einem Terminal den `cd` Befehl benutzen, bis Sie
    in dem Verzeichnis sind, in dem auch diese Datei liegt.
    Dort können Sie den Befehl `cc -std=c11 -g -Wall 01ex_test.c -o 01ex_test.o -lm && ./01ex_test.o`
    ausführen (ohne die "`" Zeichen). Die Ausgabe sollte eine Liste der Aufgaben sein, zusammen mit Hinweisen dazu, dass
    die Aufgaben noch nicht richtig gelöst wurden. Falls Sie keine solche Ausgabe bekommen, können und sollten Sie beim
    betreuten Arbeiten oder im Forum Hilfe suchen.

    Die Konsolenausgabe kann etwas unübersichtlich sein. Der folgende Befehl führt ausschließlich die Tests für
    _diese_ Aufgabe durch: `cc -std=c11 -g -Wall 01ex_test.c -o 01ex_test.o -lm && ./01ex_test.o simple_assignment`.
    Lesen Sie die Ausgabe von diesem Befehl durch. Denn tatsächlich müssen Sie in dieser Aufgabe nicht
    die Summe von `a` und `b` berechnen, sondern etwas anderes. Die Testausgabe verrät Ihnen, was genau.
    Ja, wir zwingen Sie gerade dazu, das Testsystem zum Laufen zu bringen und die Ausgabe zu lesen.
    Denn mit den Tests und deren Fehlermeldungen werden Sie sich den ganzen Programmierkurs über beschäftigen.

    Wenn Sie den Anweisungen der Testausgabe gefolgt sind, sollten Sie einen grünen, fröhlichen Smiley
    als Ausgabe erhalten. Dann haben Sie die erste Aufgabe erfolgreich gelöst, und Sie können weiterlesen.
    Vergessen Sie nicht, wieder die Tests für _alle_ Aufgaben auszuführen.
    */

    /*
    Jetzt folgt wieder Code, den Sie ignorieren können. Lesen Sie im Folgenden einfach nur die Kommentare, fügen Sie
    ihre Lösungen zwischen den CHANGES-Kommentaren ein, _überprüfen Sie ihre Lösungen im Terminal_, und ignorieren
    Sie alles andere.
    */
    return result;
}

int nested_expressions(int x, int y) {
    int result = 0;
    /*
    Aufgabe 1b:
    Weisen Sie der Variable `result` den Wert `(x - y)^2` (das Quadrat der Differenz zwischen `x` und `y`) zu.
    Dazu können Sie entweder einen großen Ausdruckverwenden, oder aber Sie speichern ein Zwischenergebnis in einer
    selbstdefinierten Variable ab. Probieren Sie gerne beides.
    */
    /* BEGIN CHANGES */
    result = (x - y) * (x - y);

    /* END CHANGES */
    return result;
}

int rotation(int a, int b, int c) {
    /*
    Aufgabe 2a:
    Weisen Sie der Variable `a` den ursprünglichen Wert der Variable `b` zu, der Variable `b` den ursprünglichen Wert
    der Variable `c` zu, und der Variable `c` den ursprünglichen Wert der Variable `a` zu.
    Z.B. sollte bei der anfänglichen Variablenbelegung `a = 0, b = 3, c = 7` am Ende
    die Belegung `a = 3, b = 7, c = 0` sein.
    */
    /* BEGIN CHANGES */
    int temp = a;
    a = b;
    b = c;
    c = temp;
    /* END CHANGES */
    return a + (b * 256) + (c * 256 * 256); /* Ja, diese Zeile mag überraschend sein. Einfach ignorieren :-) */
}

int while_loop(int n) {
    int result = 1;
    /*
    Aufgabe 3a:
    Weisen Sie der Variable `result` das Produkt aller natürlichen Zahlen zwischen `1` und `n` (inklusive) zu.
    Benutzen Sie eine _while-Schleife_, um das Produkt zu berechnen.
    `n` ist nie kleiner als `1`.
    */
    /* BEGIN CHANGES */
    while (n > 0) {
        result *= n;
        n -= 1;
    }

    /* END CHANGES */
    return result;
}

int for_loop(int n) {
    int result = 1;
    /*
    Aufgabe 3b:
    Weisen Sie der Variable `result` das Produkt aller natürlichen Zahlen zwischen `1` und `n` (inklusive) zu.
    Benutzen Sie eine _for-Schleife_, um das Produkt zu berechnen.
    `n` ist nie kleiner als `1`.
    */
    /* BEGIN CHANGES */
    for (int f = 1; f <= n; f++)
      result *= f;

    /* END CHANGES */
    return result;
}

int ones_place(int n) {
    int result = 0;
    /*
    Aufgabe 4a:
    Die *Einerstelle* einer natürlichen Zahl ist ihre letzte Dezimalstelle.
    Z.B. ist die Einerstelle von 543210 die 0, und die Einerstelle von 7 ist die 7.
    Weisen Sie der Variable `result` die Einerstelle von `n` zu.
    Tipp: der `%` Operator sollte vermutlich in der Lösung auftauchen.
    */
    /* BEGIN CHANGES */
    result = n % 10;
    /* END CHANGES */
    return result;
}

int tens_place(int n) {
    int result = 0;
    /*
    Aufgabe 4b:
    Die *Zehnerstelle* einer natürlichen Zahl ist ihre zweitletzte Dezimalstelle.
    Z.B. ist die Zehnerstelle von 1234 die 3, und die Zehnerstelle von 7 ist die 0.
    Weisen Sie der Variable `result` die Zehnerstelle von `n` zu.
    Tipp: der `/` Operator sollte vermutlich in der Lösung auftauchen.
    */
    /* BEGIN CHANGES */
    result = n % 100 / 10;
    /* END CHANGES */
    return result;
}

int fine_print1() {
    int result = 0;
    /*
    Aufgabe 5a:
    An diesem Punkt haben Sie hoffentlich viele der Testfälle zum Bestehen gebracht.
    Die Testfälle können aber nur ausgewählte Beispiele überprüfen, sie können nie sicherstellen, dass Sie die
    Aufgabe vollständig korrekt beantwortet haben.
    Insbesondere könnten Sie durch diverse if statements für alle Testfälle einfach die richtige Lösung direkt angeben,
    ohne auch nur die Aufgabenstellung zu lesen.

    Darum werden wir zur Benotung zusätzliche Testfälle auswerten, zu denen Sie keinen Zugang haben.
    Wir geben uns große Mühe, dass dies keine gemeinen Randfälle sind.
    Aber Punkte gibt es nicht für grüne Tests, sondern für korrektes Beantworten der Aufgabenstellung.
    Die Verantwortung dafür liegt bei Ihnen.
    Um uns zu bestätigen, das Sie dies gelesen und verstanden haben, weisen Sie
    der Variable `result` die Anzahl der Sätze in diesem Kommentar zu.
    */
    /* BEGIN CHANGES */
    result = 8;
    /* END CHANGES */
    return result;
}

int fine_print2() {
    int result = 0;
    /*
    Aufgabe 5b:
    Manche Aufgabenstellungen enthalten außerdem Aspekte, die nicht von den Tests abgedeckt werden können.
    Beispielsweise geben die Aufgaben 3a und 3b bestimmte Implementierungstechniken vor. Es ist möglich, solche Aufgaben nicht
    korrekt zu bearbeiten, aber die Tests trotzdem zum Bestehen zu bringen. Beispielsweise könnte man Aufgabe 3b mit einer while-Scheife lösen.
    Wenn wir eine solche "Lösung" bemerken, wird sie *mit null Punkten bewertet*.
    
    Um uns zu bestätigen, das Sie dies gelesen und verstanden haben, weisen Sie der Variable `result` die Anzahl
    der Buchstaben des Nomens in dem Satzteil *zwischen den Sternchen* im vorigen Absatz zu.
    */
    /* BEGIN CHANGES */
    result = 7;
    /* END CHANGES */
    return result;
}

int fine_print3() {
    int result = 0;
    /*
    Aufgabe 5c:
    Zu guter Letzt: die Tests zur Benotung werden auf unserem Server ausgeführt, nicht auf Ihrem Computer.
    Manche Teile der Sprache C sind maschinenabhängig, es kann also theoretisch passieren, dass auf unserem Server
    ein Test fehlschlägt, der auf Ihrer Maschine funktioniert hat. Wir geben uns große Mühe, dass das bei unseren
    Aufgaben nicht vorkommt. Aber im Zweifelsfalle liegt die Verantwortung bei Ihnen, dass Ihre Lösung auf allen
    Maschinen das Gleiche tut.

    Bevor sie die Aufgaben abgeben, werden Sie die Möglichkeit haben zu prüfen, ob unser Server die Abgaben akzeptiert.
    Falls Ihre Lösung lokal funktioniert aber nicht auf unserem Server, haben Sie dann noch genug Zeit, um beim
    betreuten Arbeiten Hilfe zu suchen.

    Schlussendlich zählt aber, ob der Server Ihre finale Abgabe akzeptiert oder nicht, selbst wenn es lokal bei Ihnen
    funktioniert.
    Um uns zu bestätigen, dass Sie das verstanden haben, weisen Sie der Variable `result` den Wert 6174 zu.
    */
    /* BEGIN CHANGES */
    result = 6174;
    /* END CHANGES */
    return result;
}





