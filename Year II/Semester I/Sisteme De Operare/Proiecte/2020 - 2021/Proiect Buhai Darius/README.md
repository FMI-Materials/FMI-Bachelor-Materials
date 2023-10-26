# DiskAnalyzer

Creati un daemon care analizeaza spatiul utilizat pe un dispozitiv de stocare incepand de la o cale data, si construiti un program utilitar care permite folosirea acestei functionalitati din linia de comanda.
Daemonul trebuie sa analizeze spatiul ocupat recursiv, pentru fiecare director continut, indiferent de adancime.

Utilitarul la linia de comanda se va numi ”da” si trebuie sa expuna urmatoarele functionalitati: 
- [x] Crearea unui job de analiza, pornind de la un director parinte si o prioritate data
    - [x] prioritatile pot fi de la 1 la 3 si indica ordinea analizei in raport cu celelate joburi (1-low, 2-normal, 3-high)
    - [x] un job de analiza pentru un director care este deja parte dintr-un job de analiza, nu trebuie sa creeze task-uri suplimentare
- [x] Anularea / stergerea unui job de analiza
- [x] Intreruperea si restartarea (pause/resume) unui job de analiza
- [x] Interogarea starii unui job de analiza (preparing, in progress, done)

```
   Usage: da [OPTION]... [DIR]...
   Analyze the space occupied by the directory at [DIR]
      -a, --add           analyze a new directory path for disk usage
      -p, --priority   set priority for the new analysis (works only with -a argument)
      -S, --suspend <id>  suspend task with <id>
      -R, --resume <id>  resume task with <id>
      -r, --remove <id>  remove the analysis with the given <id>
      -i, --info <id>  print status about the analysis with <id> (pending, progress, d
      -l, --list   list all analysis tasks, with their ID and the corresponding root p
      -p, --print <id>  print analysis report for those tasks that are "done"
```

Exemplu de folosire:
```
  $> da -a /home/user/my_repo -p 3
  Created analysis task with ID ’2’ for ’/home/user/my_repo’ and priority ’high’.

  $> da -l
  ID  PRI Path  Done Status            Details
  2 *** /home/user/my_repo  45% in progress       2306 files, 11 dirs

  $> da -l
  6
  ID  PRI Path  Done Status            Details
     2 *** /home/user/my_repo  75% in progress       3201 files, 15 dirs
     
  $> da -p 2
     Path  Usage  Size Amount
     /home/user/my_repo 100%   100MB  #########################################
     |
     |-/repo1/ 31.3%  31.3MB #############
     |-/repo1/binaries/ 15.3%  15.3MB ######
     |-/repo1/src/ 5.7%   5.7MB ##
     |-/repo1/releases/ 9.0%   9.0MB  ####
     |
     |-/repo2/ 52.5%  52.5MB #####################
     |-/repo2/binaries/ 45.4%  45.4MB ##################
     |-/repo2/src/ 5.4%   5.4MB ##
     |-/repo2/releases/ 2.2%   2.2MB #
     |
     |-/repo3/ 17.2%  17.2MB ########
     [...]
     
  $> da -a /home/user/my_repo/repo2
  Directory ’home/user/my_repo/repo2’ is already included in analysis with ID ’2’
  
  $> da -r 2
  Removed analysis task with ID ’2’, status ’done’ for ’/home/user/my_repo’
  
  $> da -p 2
  No existing analysis for task ID ’2’
```
