#define MSG_TYPE 1

struct persinfo
{
  char nev[40];
  char neptun[7];
};

struct persmsg
{
  long mtype;
  struct persinfo data;
};
