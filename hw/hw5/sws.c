// 2015112525
// Lee Joon-Byeong


#include <stdio.h>
// difference of two input
int abs(int a, int b){
    if(a-b>=0) return a-b;
    else return b-a;
}

int main(){
    int h, w, index, i,tmp, j, diff=1000, d=0;
    fscanf(stdin,"%d %d",&h,&w);

// make 2nd dimension arr for input
    int **arr = malloc(sizeof(int *) * (h+2));
    for(i=0; i<h+2; i++){
        arr[i]=malloc(sizeof(int) * w+1);
    }
    int *path= malloc(sizeof(int)*(h+2));
    int *path1= malloc(sizeof(int)*(h+2));
    int *path2= malloc(sizeof(int)*(h+2));

    index=w/2;
    for(i=0;i<h+2;i++){
        for(j=0;j<w+1;j++){
            fscanf(stdin,"%d",&arr[i][j]);
            if(arr[i][j]<0){
                break;
            }
        }
    }

    for(i=1;i<h+2;i++){
        for(j=1;j<w+1;j++){
            for(int k=j+1;k<w+1;k++){
                if(arr[i][k]<0) break;
                else if(arr[i][j]>arr[i][k]){
                    tmp=arr[i][j];
                    arr[i][j]=arr[i][k];
                    arr[i][k]=tmp;
                }
            }
            if(arr[i][j]<0){
                break;
            }
        }
    }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

    //  when first plate's slit num < index
    printf("\n");
    int temp;
    diff=1000;
    j=1;
    while(1){
        if(diff>abs(index,arr[1][j])){
            diff=abs(index,arr[1][j]);
            temp=arr[1][j];
        }
        j++;
        if(temp<index && arr[1][j]>index){
            break;
        }
        if(arr[1][j]<0){
            break;
        }
    }
    d+=diff;
    path1[1]=temp;
    index=temp;
    // under second plate
    for(i=2;i<h+1;i++){
        diff=1000;
        for(j=1;j<w+1;j++){
            if(arr[i][j]<0){
                break;
            }
            else if(diff>abs(index,arr[i][j])){
                diff=abs(index,arr[i][j]);
                temp=arr[i][j];
            }
        }
        d+=abs(index,temp);
        index=temp;
        path1[i]=temp;
    }
    path1[0]=d;

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

    //  when first plate's slit num > index
    diff=1000;
    index=w/2;
    j=1;
    d=0;
    while(1){
        if(diff>abs(index,arr[1][j])){
            diff=abs(index,arr[1][j]);
            temp=arr[1][j];
        }
        j++;
        if(temp>index){
            break;
        }
        if(arr[1][j]<0){
            break;
        }
    }
    path2[1]=temp;
    index=temp;
    d+=diff;

    //under second plate
    for(i=2;i<h+1;i++){
        diff=1000;
        for(j=1;j<w+1;j++){
            if(arr[i][j]<0){
                break;
            }
            else if(diff>abs(index,arr[i][j])){
                diff=abs(index,arr[i][j]);
                temp=arr[i][j];
            }
        }
        d+=abs(index,temp);
        index=temp;
        path2[i]=temp;
    }
    path2[0]=d;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// print
    if(path1[1]>path2[1]){
        path=path2;
    }
    else{
        path=path1;
    }

    for(i=0;i<h+1;i++){
        printf("%d ",path[i]);
    }

    free(arr);
    free(path);
    free(path1);
    free(path2);

    return 0;
}
