// Trabalho de Manutencao - triagem do pronto socorro
// versao antiga
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
using namespace std;

int x;
char p[50];

int calc(int a,double b,double c,char d)
{
    x=0;
    // coracao
    if(a>=51&&a<=90) x=x+0;
    else if(a>=41&&a<=130) x=x+1;
    else x=x+3;
    // sat
    if(b>=96) x+=0;
    else
      if(b>=92) x+=1;
      else x+=3;
    // temp
    if (c >= 36.1 && c <= 38.0) {
        x = x + 0;
    } else {
        if (c >= 35.1 && c <= 39.0) {
            x = x + 1;
        } else {
            x = x + 3;
        }
    }
    if(d=='n'||d=='N') return 1;
    if(x>=6) return 1;
    else {
        if(x>=4) return 2;
        else {
            if(x>=2) return 3;
            else {
                if(x>=1) return 4;
                else return 5;
            }
        }
    }
}

int main(){
int op=1;
int fc;
double sat,temp;
char resp;
int r; // risco
    while(op==1)
    {
        printf("\n===== TRIAGEM =====\n");
        printf("Nome do doente: ");
        scanf(" %49[^\n]",p);
        printf("Frequencia cardiaca (bpm): ");scanf("%d",&fc);
        printf("Saturacao (%%): ");scanf("%lf",&sat);
        printf("Temperatura (C): ");scanf("%lf",&temp);
        printf("Paciente consciente? (s/n): ");scanf(" %c",&resp);

        if(fc>0&&fc<=300){
            if(sat>0&&sat<=100){
                if(temp>=25&&temp<=45){
                    if(resp=='s'||resp=='S'||resp=='n'||resp=='N'){
                        r=calc(fc,sat,temp,resp);
                        // mostra o nivel
                        if(r==1){ printf("Pessoa: %s\n",p); printf("Cor: VERMELHO - emergencia - atendimento imediato (pontos: %d)\n",x); }
                        else if(r==2){ printf("Pessoa: %s\n",p); printf("Cor: LARANJA - muito urgente - esperar no maximo 10 min (pontos: %d)\n",x); }
                        else if(r==3){ printf("Pessoa: %s\n",p); printf("Cor: AMARELO - urgente - esperar no maximo 60 min (pontos: %d)\n",x); }
                        else if(r==4){ printf("Pessoa: %s\n",p); printf("Cor: VERDE - pouco urgente - esperar no maximo 120 min (pontos: %d)\n",x); }
                        else { printf("Pessoa: %s\n",p); printf("Cor: AZUL - nao urgente - esperar no maximo 240 min (pontos: %d)\n",x); }
                    }
                    else printf("Erro: resposta invalida\n");
                }
                else printf("Erro: temperatura invalida\n");
            }
            else printf("Erro: saturacao invalida\n");
        }
        else printf("Erro: frequencia invalida\n");

        printf("\nClassificar outro? (1 - sim / 0 - nao): ");
        scanf("%d",&op);
    }
    printf("Fim do programa\n");
    return 0;
}
