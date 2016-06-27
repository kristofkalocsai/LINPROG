# EA #6

## IPC Inter Process Comunication

+ pid
+ fork

- systemV IPC

    `sys/ipc.h` kozos header a csaladhoz
    - semafore
        - szemafor tombok
        - szemafor tomb tobb, mint szemafor halmaz:
            - egyszerre tobb szemafor muveletet kerhetunk
            - vagy mindet vegrehajtja vagy egyiket sem!
        - header: `sys/sem.h`
        - letrehozas: `int semget(key_t key, int nsems, int semflg);`
            - `semflg` (bites VAGY): `0, IPC_CREAT, IPC_EXCL`
        - torles: `semctl(semid, 0, IPC_RMID, 0);`

        - muveletek: lasd dian, 16. oldal
    - uzenetsor
    - shared mem
    - kezelo parancs: `ipcs`

    - eroforrasok kozosek, nem folyamathoz kotodnek:
        - torolni kell, ha mar nem hasznaljuk. manualis torles: `ipcrm`
        - egyedi azonositora van szukseg: `key_t ftok(const char *pathname, int proj_id)`

- signals
- pipe
- socket
