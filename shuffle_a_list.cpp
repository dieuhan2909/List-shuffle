#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void swap(int &n1,int &n2) {
	int temp = n1;
	n1 = n2;
	n2 = temp;
}

void partitionsort(int *b,int L,int R) {
	if(L>=R) return;
	int i = L + 1, j = R;
	while(i<=j)
	{
		while(b[i]<b[L]) i++;
		while(b[j]>b[L]) j--;
		if(i<j)
		{
			swap(b[i],b[j]);
			i++;
			j--;
		}
	}
	swap(b[L],b[j]);
	partitionsort(b,L,j-1);
	partitionsort(b,j+1,R);
}

void shufflelist(int *a,int n) {
	int i, j, k, bsize = 1, randomvalue;
	bool randomvaluechanged;
	int *b = (int*)malloc(n*sizeof(int));
	srand(time(NULL));
	a[0] = rand()%n;
	b[0] = a[0];
	for(i=1;i<n-1;i++) {
		randomvalue = rand()%n;
		randomvaluechanged = false;
		for(j=0;j<bsize;j++) {
			if(j==b[j]) {
				if(randomvalue==j) {
					randomvalue++;
					randomvaluechanged = true;
				}
			}
			else break;
		}
		if(!randomvaluechanged)
			for(j=bsize-1;j>=0;j--)  {
				if(j<b[j]) {
					if(randomvalue==b[j]) {
						if(b[j]==j-bsize+n) randomvalue--;
						else {
							k = j;
							while(randomvalue==b[k]) {
								randomvalue++;
								k++;
							}
							break;
						}
					}
				}
				else break;
			}
		a[i] = randomvalue;
		b[bsize] = randomvalue;
		partitionsort(b,0,bsize);
		bsize++;
	}
	for(i=0;i<bsize;i++) 
		if(b[i]>i) {
			a[n-1] = i;
			free(b);
			return;
		}
	if(i==bsize) a[n-1] = n - 1;
	free(b);
}

int main() {
	int i, n, *a;
	printf("Nhap vao so phan tu danh sach: ");
	scanf("%d",&n);
	a = (int*)malloc(n*sizeof(int));
	printf("Danh sach ban dau: ");
	for(i=0;i<n;i++) printf("%d ",i);
	shufflelist(a,n);
	printf("\nDanh sach sau khi tron: ");
	for(i=0;i<n;i++) printf("%d ",a[i]);
	free(a);
}