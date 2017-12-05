#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define radius 39.

int main(int argc, char *argv[]) {
  char chNum;
  DIR *dir;
  struct dirent *dp;
  char path[64] = "./2017output/";
  char file_path[64];
  char date[16];
  char work[64];
  char *pw = work;
  char hour[3], min[3], sec[3];

  long count;
  double dur_time, speed, distance;
  int  duration, dur_high;

  double fhour, fmin, fsec, ftime;

  FILE *fp;
  char s[128];

  if (argc <= 2) {
    printf("./concat3-LJ chNum date \n");
    return -1;
  } else {
    chNum = 0x40+atoi(argv[1]);
    strcpy(date, "kash_");
    strcat(date, argv[2]);
  }
  // printf( "%c\n", chNum);

  count = 0;
  dur_time = 0.;
  speed = 0.;
  distance = 0.;

  dir = opendir(path);
  for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){
    if (strchr(dp->d_name, chNum) > 0) {
      // printf("%s\n",dp->d_name);

      strcpy(file_path, path);
      strcat(file_path, dp->d_name);

      // detect time infromation

      strcpy(work, dp->d_name);
      
      pw = strtok(work, "_");
      pw = strtok(NULL, "_");
      pw = strtok(NULL, ".");

      //      printf("%s\n", pw);
      strcpy(work, pw);
      pw = work;
      memcpy(hour, pw, 2); hour[2] = 0; fhour = atof(hour);
      memcpy(min, pw+2, 2); min[2] = 0; fmin = atof(min);
      memcpy(sec, pw+4, 2); sec[2] = 0; fsec = atof(sec);
      //      printf("%10.3lf, %10.3lf, %10.3lf\n", fhour, fmin, fsec);

      // selected data file  by date
      
      if (strstr(file_path, date) != NULL) {
//	 printf("path: %s\n", file_path);

	fp = fopen( file_path, "r");
	while (fgets(s, 128, fp) != NULL) {
	  if (strstr(s, "time") == NULL) {
	    //	  printf("%s", s);

	    count = count + 1;
	    pw = strtok(s, ",");
	    //	    ftime = fhour*3600. + fmin*60. + fsec + atof(pw);
	    ftime = atof(pw); 
	    pw = strtok(NULL, ",");
	    pw = strtok(NULL, ",");
	    duration = atoi(pw);
	    pw = strtok(NULL, ",");
	    dur_high = atoi(pw);
	    pw = strtok(NULL, ",");
	    dur_time = atof(pw);
	    pw = strtok(NULL, ",");
	    speed = atof(pw);
	    distance = (double)count * 2. * 3.14159 * radius / 1000.;

	    printf("%14.8lf, %ld, %5d, %5d, %10.4lf, %10.4lf, %10.4lf\n", ftime, count, duration, dur_high, dur_time, speed, distance);
	  }
	}
      }
      fclose(fp);
    }
  }

  closedir(dir);
  
  return 0;
}
