#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TH_LEVEL   0.5
#define SF         1000.
#define radius     39.
//#define radius     40.
#define MIN_DT     3
#define MIN_DH     3
#define MAX_DH     20
#define MIN_PD     50
#define MAX_PD     300

int main(int argc, char *argv[]) {
    int    i, ret, flag, period, chNum, numFile, periodHigh;
    long   ln, count, lnAll, countAll;
    int    skipLN[10];
    FILE   *fp[10], *fr;
    char   getstr1[256], getstr2[256];
    float  periodT, speed, adval0, adval1;
    double dist, distAll;
    char   *p1, *p2;
    double time1, start_time;
    int    f_start = 0;

    if (argc <= 3) {
        printf("./dA3-LJnew ch# data_file1 skip_line1 data_file2 skip_line2 ... \n");
        return -1;
    } else {
        chNum = atoi(argv[1]);
        for( i = 0; i < (argc-2)/2; i++ ) {
            fr = fopen(argv[2*i+2], "r");
            if (fr == NULL) {
	        printf("Error data file\n");
	        return -1;
            }
            skipLN[i] = atoi(argv[2*i+3]);
            fclose(fr);
        }
    }
    numFile = i;

    lnAll = 0; countAll = 0;
    time1 = 0.;
    printf("time(s), count, duration, dur_high, dur_time(sec), speed(m/h), distance(m)\n"); 
    for (i = 0; i < numFile; i++) {
        ln = 0;
        flag = 0;
        fr = fopen(argv[2*i+2], "r");
        while ((ret = fscanf(fr, "%s", getstr1)) != EOF){

  	    // pickup A/D value

 	     ln++;
	     if (ln <= (long)skipLN[i]) continue;

	     p1 = strtok(getstr1,",");
	     time1 = (double)atof(p1);
	     if (f_start == 0) {
	         start_time = time1;
		 adval0 = 0;
		 f_start = 1;
	     }

	     p1 = strtok(NULL,",");
	     if (chNum == 1) {
	         adval1 = atof(p1);
	     } else {
	         p1 = strtok(NULL,",");
	         if (chNum == 2) {
	             adval1 = atof(p1);
	         } else {
	             p1 = strtok(NULL,",");
	             if (chNum == 3) {
	                 adval1 = atof(p1);
	             } else {
	                 p1 = strtok(NULL, "\n");
	                 adval1 = atof(p1);
	             }
	         }
	     }

	     //	     if (adval1 >= TH_LEVEL) printf("%14.8lf, %5.3f\n", time1, adval1);
	     if (flag == 0 && adval0 < TH_LEVEL  && adval1 >= TH_LEVEL) {
	        period = 1;
	        periodHigh = 1;
	        flag = 1;
	        periodHigh++;
	        period++;
	     } else if (flag == 1 && adval0 < TH_LEVEL && adval1 >= TH_LEVEL ) {
	        countAll++;
		periodT = (float)period/SF;
	        dist = 2. * 3.14159 * radius / 1000.;
	        distAll = (float)countAll * 2. * 3.14159 * radius / 1000.;
	        speed = 2. * 3.14259 * radius / 1000. / periodT * 3600.;
		printf("%14.8lf, %ld, %d, %d, %f, %f, %lf\n", 
		       time1, countAll, period, periodHigh, periodT, speed, distAll);
		period = 1;
		periodHigh = 1;
		flag = 1;
	     } else {
	        period++;
 	        if (adval1 >= TH_LEVEL) { 
		   periodHigh++; 
		}
	     }

	     adval0 = adval1;
        }
        fclose(fr);
    }
    //    printf("%lf, %ld, , , , %lf\n", time, countAll, distAll);

  return 0;
}
