Metode de concurenta in Java - thread-safe
	- Producer - Consumer (sincronizarea se efectueaza prin intermediul structurii utilizate)
	- Reader - Writer
Pentru Reader-Writer, in general vreau sa respect urmatoarele:
- avem o zona partajata in care scriu/citesc
- avem un singur thread pentru writer la un moment dat
- permit ca Readerii sa fie in paralel, dam prioritate Readerilor fata de Writer
[https://pastebin.com/GjMimh54](https://pastebin.com/GjMimh54)
Modificati producerea de mesaje astfel incat un Producer sa produca mesaje citite dintr-un fisier.txt.

Modificati codul astfel incat - primim un path in care exista o ierarhie de foldere; - am mai multi produceri care lucreaza in paralel si citesc continutul fisierelor text pe care le gasesc in ierarhia de foldere; - am mai multi consumeri care aplica o modificare continutului text citit. orice modificare. cum vreti voi.

^ a fost data la examen\
\
[https://pastebin.com/j8SuNfp4](https://pastebin.com/j8SuNfp4)

```java
	Producer - (Consumer -> (Writer - Reader))
```
