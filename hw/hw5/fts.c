// 2015112525
// Lee Joon-Byeong

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// structure for coordinate
struct LOC{
    int x;
    int y;
};

// distance between two struct
float dist(struct LOC A, struct LOC B){
    float k= sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
    return k;
}

// total distance from (0,0) to (100,100)
float tdist(struct LOC *A, int num){
    float distv=0,distd;
    int i;
    for(i=0;i<num-1;i++){
        distd=dist(A[i],A[i+1]);
        distv+=distd;
    }
    return distv;
}

// insert coordinate in final route
void c_insert(struct LOC *A, struct LOC B, int num){
    int ii=1;
    struct LOC min_a;
        for(int i=1;i<num;i++){
            if(A[i].x<B.x){
                ii=i+1;
            }
            else if(A[i].x==B.x && A[i].y<B.y){
                ii=i+1;
            }
        }
        for(int i=num+1;i>ii;i--){
            A[i]=A[i-1];
        }
        A[ii]=B;
}

int main(){
    int num, i, j, temp;
    float distv, distd;
    fscanf(stdin,"%d",&num);
    struct LOC *city=malloc(sizeof(struct LOC)*num); // input coordinate
    struct LOC *min=malloc(sizeof(struct LOC)*num); // temp struct
    struct LOC *fin=malloc(sizeof(struct LOC)*num);// final route

    for(i=0;i<num;i++){
        fscanf(stdin,"%d",&city[i].x);
        fscanf(stdin,"%d",&city[i].y);
    }

    // sort by x & y
    for(i=0;i<num-1;i++){
        for(j=i+1;j<num;j++){
            if(city[i].x>city[j].x){
                temp=city[i].x;
                city[i].x=city[j].x;
                city[j].x=temp;

                temp=city[i].y;
                city[i].y=city[j].y;
                city[j].y=temp;
            }
            else if(city[i].x==city[j].x && city[i].y>city[j].y){
                temp=city[i].x;
                city[i].x=city[j].x;
                city[j].x=temp;

                temp=city[i].y;
                city[i].y=city[j].y;
                city[j].y=temp;
            }
        }
    }

    printf("===========================================\n");
    printf("===========================================\n");

    // put start & end point
    min[0]=city[0];
    min[1]=city[num-1];
    fin[0]=city[0];
    fin[1]=city[num-1];
    float incm,td1=0,td2=0;
    int ii;

/////////////////////////////////////////////////////////////////////////////////////
// fts.pdf
/////////////////////////////////////////////////////////////////////////////////////
    for(j=1;j<num-1;j++){
        incm=9999; // increment
        // find minimum increment
        for(i=1;i<num-1;i++){
            if(incm>dist(city[0],city[i])+dist(city[i],city[num-1])){
                incm=dist(city[0],city[i])+dist(city[i],city[num-1]);
                ii=i;
            }
        }
        c_insert(min,city[ii],j);
        city[ii].x=1000; // put 1000 to make increment big
        city[ii].y=1000;

        td2=td1;
        td1=tdist(min,j);

        // print
        if(td1>1500 && td2<1500){
            printf("1500 %.2f\n",td2);
            for(i=0;i<j+1;i++){
                printf("%d %d  ", fin[i].x,fin[i].y);
            }
            printf("\n\n");
        }
        else if(td1>1100 && td2<1100){
            printf("1100 %.2f\n",td2);
            for(i=0;i<j+1;i++){
                printf("%d %d  ", fin[i].x,fin[i].y);
            }
            printf("\n\n");
        }
        else if(td1>700 && td2<700){
            printf("700 %.2f\n",td2);
            for(i=0;i<j+1;i++){
                printf("%d %d  ", fin[i].x,fin[i].y);
            }
            printf("\n\n");
        }
        else if(td1>300 && td2<300){
            printf("300 %.2f\n",td2);
            for(i=0;i<j+1;i++){
                printf("%d %d  ", fin[i].x,fin[i].y);
            }
            printf("\n\n");
        }

        for(i=1;i<j+2;i++){
            fin[i]=min[i];
        }
    }

    free(city);
    free(min);
    free(fin);
    return 0;
}
