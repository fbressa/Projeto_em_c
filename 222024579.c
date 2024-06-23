/******************************************************************************
Aluno(a): FIlipe Bressanelli
Matrícula: 222024579
Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/
#include <stdio.h>
#include "222024579.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>


int main()
{
    //declaração de variaveis importantes 
    int opcao;
    
   
    charset();
    setlocale(LC_CTYPE,".UTF8");
    

    while(opcao !=9)

    { 
        
           //menu de opcao
         printf("   ** MENU **\n");
         printf("1) Consultar minusina cadastrada\n");
         printf("2) Consultar consumidor cadastrado\n");
         printf("3) Listar as minusinas cadastradas\n");
         printf("4) Listar as miniusinas em operacao por ordem decrescente de capacidade de geracao de energia\n");
         printf("5) Listar as RAs por ordem decrescente de quantidade de miniusinas\n");
         printf("6) Listar as RAs por ordem crescente de numero de contratos\n");
         printf("7) Listar as RAs por ordem decrescente de capacidade de geracao\n");
         printf("8) Listar as RAs por ordem decrescente de percentual de energia disponivel\n");
         printf("9) Sair do programa\n\n");
         

        //escolha da opcao
        printf("Digite a sua opcao: ");
        while (scanf("%d", &opcao) != 1)
        {
            int o;
            while((o = getchar()) != '\n' && o != EOF);
            printf("Erro de processamento, Digite novamente: \n");
        } 
        

         //execucao da escolha do usuario
         
        if (opcao == 1)
        {
            consultar_miniusinas();
        }
        else if(opcao ==2)
        {
            Consultar_consumidores();
        }

        else if(opcao == 3)
        {
            Listar_miniusinas();
        }

         else if(opcao == 4)
        {
            Listar_MiniUsinas_Dec();
        }

        else if(opcao == 5)
        {
            Listar_RA_dec_min();
        }

        else if (opcao == 6)
        {
            Listar_ra_cr_cont();
        }
        
        else if (opcao == 7)
        {
            Listar_RA_dec_gera();
        }
        
        else if (opcao == 8)
        {
            Listar_RA__dec_perc();
        }

        else if(opcao<=0 || opcao>9)
        {
            printf("Essa opcao nao existe\n\n");
        }

    }

    return 0;
}