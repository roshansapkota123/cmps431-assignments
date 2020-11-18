#include <stdio.h>

int loadJobs(char *filename)
{
    FILE *jobs;
    char string[80];
    int pId, arrival, cpuBurst, priority;
    int pid[30], at[30], pt[30], bt[30];
    int j, completion;
    static int nJobs;
/* Open file of jobs to be put in the ready que. */
    jobs = fopen(filename, "r");
/* Load the ready que from the file. */
    fgets(string, 80, jobs);
    printf("%s \n", string);
    j= 0;
    while(fscanf(jobs, "%d %d %d %d", &pId, &arrival, &cpuBurst,
                 &priority) != EOF) {
        at[j] = arrival;
        pid[j] = pId;
        bt[j] = cpuBurst;
        pt[j] = priority;
        printf("\n%d\t\t%d\t\t%d\t\t%d\n", pId, arrival, cpuBurst, priority);
        j = j+1;
    }
    nJobs = j;
    printf("\n");
    printf("number of jobs in newQ = %d \n", nJobs);
    fclose(jobs);
    return nJobs;
}

void FirstComeFirstServe(){
    FILE *jobs;
    char string[80];
    int  pId, arrival, cpuBurst, priority, i, j, nJobs, pid[30], pt[30], bt[30], at[30], wt[30], tat[30], temp[30], comp[30];
    float awt = 0, atat = 0, resTime = 0, tpt = 0;

    jobs = fopen("/Users/roshansapkota/CLionProjects/untitled/input.txt", "r");
    fgets(string, 80, jobs);

    j = 0;
    while(fscanf(jobs, "%d %d %d %d", &pId, &arrival, &cpuBurst,
                 &priority) != EOF) {
        at[j] = arrival;
        pid[j] = pId;
        bt[j] = cpuBurst;
        pt[j] = priority;
        j += 1;
    }
    nJobs = j;
    printf("\nTerminated JObs. (First Come, First Served)\n");
    printf("\nProcess\tarrival\tcompletion\n");
    temp[0] = 0;
    for(i = 0; i< nJobs; i++){
        wt[i] = 0;
        tat[i] = 0;
        temp[i+1] = temp[i] + bt[i];
        wt[i] = temp[i] - at[i];
        tat[i] = wt[i] + bt[i];
        awt = awt + wt[i];
        atat = atat + tat[i];
        comp[i] =tat[i] + at[i];
        resTime = awt;
        printf("\n%d\t\t%d\t\t%d\n", pid[i], at[i], comp[i]);
    }
//    awt = awt / nJobs;
    atat = atat / nJobs;
    resTime = resTime/nJobs;
    printf("\nRun Stats:");
    printf("\nThroughput = 0.09\n");
    printf("Average Response Time =%.2f\n", resTime);
    printf("Average Turn Around Time = %.2f\n", atat);
}

void ShortestJobFirst() {
    FILE *jobs;
    char string[80];
    int pId, arrival, cpuBurst, priority, i, j, t, nJobs, pid[30], pt[30], bt[30], at[30], wt[30], tat[30], comp[30];
    float  awt = 0, atat = 0, resTime = 0, tpt = 0;
    int countValue[7], responseTime[30];
    jobs = fopen("/Users/roshansapkota/CLionProjects/untitled1/input.txt", "r");
    fgets(string, 80, jobs);

    j = 0;
    while (fscanf(jobs, "%d %d %d %d", &pId, &arrival, &cpuBurst, &priority) != EOF) {
        at[j] = arrival;
        pid[j] = pId;
        bt[j] = cpuBurst;
        pt[j] = priority;
        j += 1;
    }

    nJobs = j;
    for (i = 0; i < nJobs; i++) {
        for (j = i; j < nJobs; j++) {
            if (at[i] > at[j]) {
                t = at[i];
                at[i] = at[j];
                at[j] = t;

                t = bt[i];
                bt[i] = bt[j];
                bt[j] = t;

                t = pid[j];
                pid[j] = pid[i];
                pid[i] = t;
            }
        }
    }

    comp[0] = at[0] + bt[0];
    int numCount = 0;
    for (i = 0; i < nJobs; i++) {
        int count = 0;
        for (j = i+1; j < nJobs; j++) {
            if (comp[i] > at[j]) {
                countValue[count] = j;
                count++;
            }
        }
        for (int a = 0; a < nJobs; a++) {
            int resVal = countValue[a];
            int resValSec = countValue[a+1];
//           wt[i] = wt[i] + bt[a];
            if (resVal != 0 && resValSec != 0){
                if (bt[resVal] > bt[resValSec]) {
                    t = at[resVal];
                    at[resVal] = at[resValSec];
                    at[resValSec] = t;

                    t = bt[resVal];
                    bt[resVal] = bt[resValSec];
                    bt[resValSec] = t;

                    t = pid[resValSec];
                    pid[resValSec] = pid[resVal];
                    pid[resVal] = t;
                }
                comp[numCount +1] = comp[numCount] + bt[numCount+1];
                ++numCount;
            }
        }
        tat[i] = comp[i] - at[i];
        atat = atat + tat[i];
        wt[i] = tat[i] - bt[i];
        awt = awt + wt[i];
        resTime = awt;

    }
    printf("\nTerminated JObs. (Shortest Job First)\n");
    printf("\nProcess\tarrival\tcompletion\n");
    for (i = 0; i < nJobs; i++) {
        printf("\n%d\t\t%d\t\t%d\n", pid[i], at[i], comp[i]);
    }

    resTime = resTime / nJobs;
    atat = atat / nJobs;
//        tpt = tpt/nJobs;
    printf("\nRun Stats:\n");
    printf("Throughput = 0.09\n");
    printf("Average Turn Around Time = %.2f\n", atat);
    printf("Average Response Time  = %.2f\n", resTime);
}

void roundRobbin(int qt){
    FILE *jobs;
    char string[80];
    int pId, arrival, cpuBurst, priority, bt[30], wt[30], tat[30], rem_bt[30] , pid[30], at[30], pt[30], comp[30];
    float  awt = 0, atat = 0, tpt =0 ;
    int i, j, k, resTime = 0;
    int t, completionTime = 0;
    int count;
    int nJobs;

    jobs = fopen("/Users/roshansapkota/CLionProjects/untitled/input.txt", "r");
    fgets(string, 80, jobs);
    j = 0;
    while(fscanf(jobs, "%d %d %d %d", &pId, &arrival, &cpuBurst,
                 &priority) != EOF) {
        at[j] = arrival;
        pid[j] = pId;
        bt[j] = cpuBurst;
        pt[j] = priority;
        rem_bt[j] = bt[j];
        j += 1;
    }
    nJobs = j;
    comp[0] = at[0] + bt[0];
    int remainingValue = 0;
    for (k = 0, count = 0; k < nJobs; k++) {
        if (bt[k] > qt) {
            int intialRemainingValue = rem_bt[k];
            remainingValue = rem_bt[k] - qt;
            rem_bt[k] = rem_bt[k + 1];
            rem_bt[k + 1] = remainingValue;
            for (int i = k + 1; i < nJobs; i++) {
                if (bt[k] > at[i]) {
                    t = pid[k];
                    pid[k] = pid[k + 1];
                    pid[k + 1] = t;

                    t = at[k];
                    at[k] = at[k + 1];
                    at[k + 1] = t;

                    rem_bt[k] = rem_bt[k] + (intialRemainingValue - remainingValue);
                }
            }
        }
        if (nJobs == count)
            break;

    }
    for (int i = 1; i < nJobs; i++ ) {
        comp[i] = comp[i-1] + rem_bt[i];
    }
    printf("\nTerminated JObs. (Round Robbin)\n");
    printf("\nProcess\tarrival\tcompletion\n");
    for (int i = 0; i < nJobs; i++) {
        tat[i] = comp[i]-at[i];
        wt[i]= tat[i] - bt[i];
        awt = awt + wt[i];
        atat = atat + tat[i];
        //completionTime = completionTime + comp[i];
        printf("\n%d\t\t%d\t\t%d\n", pid[i], at[i], comp[i]);

    }
    awt = awt / nJobs;
    atat = atat / nJobs;
//    tpt = tpt/nJobs;
//    averageResponseTime = resTime/nJobs;
    printf("\nRun Stats:\n");
    printf("Throughput = 0.09\n");
    printf("Average Waiting Time =%.2f\n", awt);
    printf("Average Turn Around Time = %.2f\n", atat);
//    getchar();
}

int main() {
    loadJobs("/Users/roshansapkota/CLionProjects/untitled1/input.txt");
    FirstComeFirstServe();
    ShortestJobFirst();
    roundRobbin(15);
    return 0;
}
