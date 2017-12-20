#include <stdio.h>
#include <stdlib.h>
FILE *openf(char *name,char *mode);
void readF(FILE *fin,int *r,int *c,int ***matr,int ***matc);
void showmat(int **mat,int n);
int **alloc2d(int r,int c);
int place_r(int **nonogram,int **matr,int **matc,int r,int c,int level);
int check(int **nonogram,int **matr,int **matc,int r,int c);
void display(int **nonogram, int r,int c, FILE *fp);
int main(int argc,char *argv[])
{
    FILE *fpin,*fpout;
    int r,c;
    int **matr;
    int **matc;
    int **nonogram;
    if(argc!=3)
    {
        printf("error in C.L arguments.");
        exit(0);
    }
    fpin=openf(argv[1],"r");
    fpout=openf(argv[2],"w");
    readF(fpin,&r,&c,&matr,&matc);
    showmat(matr,r);
    showmat(matc,c);
    nonogram=alloc2d(r,c);
    if(place_r(nonogram,matr,matc,r,c,0)==1)
    {
        display(nonogram,r,c,fpout);
    }
    return 0;
}

FILE *openf(char *name,char *mode)
{
    FILE *fp;
    fp=fopen(name,mode);
    if(fp==NULL)
    {
        printf("error in opening file.");
        exit(0);
    }
    return fp;
}
void readF(FILE *fin,int *r,int *c,int ***matr,int ***matc)
{
    int i,j,n;
    int **rmat;
    int **cmat;
    fscanf(fin,"%d",r);
    rmat=(int **)malloc((*r)*sizeof(int *));
    if(rmat==NULL)
    {
        printf("memory error");
        exit(0);
    }
    for(i=0; i<*r; i++)
    {
        fscanf(fin,"%d",&n);
        rmat[i]=(int *)malloc((n+1)*sizeof(int));
        if(rmat[i]==NULL)
        {
            printf("memory error");
            exit(0);
        }
        rmat[i][0]=n;
        for(j=1; j<=n; j++)
        {
            fscanf(fin,"%d",&rmat[i][j]);
        }

    }
    *matr=rmat;

    fscanf(fin,"%d",c);
    cmat=(int **)malloc((*c)*sizeof(int *));
    if(cmat==NULL)
    {
        printf("error");
        exit(0);
    }
    for(i=0; i<*c; i++)
    {
        fscanf(fin,"%d",&n);
        cmat[i]=(int *)malloc((n+1)*sizeof(int));
        if(cmat[i]==NULL)
        {
            printf("error");
            exit(0);
        }
        cmat[i][0]=n;
        for(j=1; j<=n; j++)
        {
            fscanf(fin,"%d",&cmat[i][j]);
        }

    }
    *matc=cmat;
    return;

}
void showmat(int **mat,int n)
{
    int r,c;
    printf("%d \n",n);
    for(r=0; r<n; r++)
    {
        for(c=0; c<=mat[r][0]; c++)
        {
            printf("%d ",mat[r][c]);
        }
        printf("\n");
    }
    return;
}
int **alloc2d(int r,int c)
{
    int **mat;
    int i,j;
    mat=(int **)malloc(r*sizeof(int *));
    if(mat==NULL)
    {
        printf("Error");
        exit(0);
    }
    for(i=0; i<r; i++)
    {
        mat[i]=(int *)malloc(c*sizeof(int));
        if(mat[i]==NULL)
        {
            printf("Error");
            exit(0);
        }
    }
    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
            mat[i][j]=0;
        }
    }
    return mat;
}
int place_r(int **nonogram,int **matr,int **matc,int r,int c,int level)
{
    int col,row;
    if(level==(r*c))
    {
        return (check(nonogram,matr,matc,r,c));
    }
    row=level/r;
    col=level%c;
    nonogram[row][col]=0;
    if(place_r(nonogram,matr,matc,r,c,level+1)==1)
    {
        return 1;
    }
    nonogram[row][col]=1;
    if(place_r(nonogram,matr,matc,r,c,level+1)==1)
    {
        return 1;
    }
    return 0;
}
int check(int **nonogram,int **matr,int **matc,int r,int c)
{
    int i,j,n,l;

    //row
    for(i=0; i<r; i++){
        n=0;
        l=0;
        for(j=0; j<c; j++){
            if(nonogram[i][j]==1){
                l++;
                if(l==1)
                    n++;
                }else{
                if(l!=0){
                    if(n>matr[i][0] || l!=matr[i][n]){
                        return 0;
                    }else{
                    l=0;
                }
            }
        }
    }
    if(n!=matr[i][0]) return 0;
    if(l!=0 && l!=matr[i][n]) return 0;
}
    //col check
    for(j=0; j<c; j++){
        n=0;
        l=0;
        for(i=0; i<r; i++){
            if(nonogram[i][j]==1){
                l++;
                if(l==1)
                    n++;
                }else{
                if(l!=0){
                    if(n>matc[j][0] || l!=matc[j][n]){
                        return 0;
                    }else{
                    l=0;
                }
            }
        }
    }
    if(n!=matc[j][0]) return 0;
    if(l!=0 && l!=matc[j][n]) return 0;
}

    return 1;
}
void display(int **nonogram, int r,int c, FILE *fp)
{
    int i,j;
    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++)
        {
            fprintf(fp,"%d",nonogram[i][j]);
        }
        fprintf(fp,"\n");
    }
    return;
}
