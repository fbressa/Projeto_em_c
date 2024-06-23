/******************************************************************************
Aluno(a): FIlipe Bressanelli
Matrícula: 222024579
Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <locale.h>

//definições de tamanho usados no codigo 
#define TAM_MAX_CNPJ_CPF 20
#define TAM_MAX_NOME 100
#define TAM_MAX_CAPACIDADE 10
#define TAM_MAX_ID 5
#define TAM_MAX_STATUS 15
#define TAM_MAX_IDCONSUMIDOR 20
#define TAM_MAX_DATA 11
#define TAM_MAX_ENERGIA 8
#define TAM_MAX_RA 4
#define TAM_MAX_TAMANHO 20




//structs usadas para ler os arquivos usados no decorrer do codigo 
 struct miniusinas
{
    char cnpj[TAM_MAX_CNPJ_CPF];
    char nome[TAM_MAX_NOME];
    char capacidade[TAM_MAX_CAPACIDADE];
    char id[TAM_MAX_ID];
    char status[TAM_MAX_STATUS];

};

struct contratos
{
    char id_contratos[TAM_MAX_ID];
    char idconsumidores_contratos[TAM_MAX_IDCONSUMIDOR];
    char cnpj_contratos[TAM_MAX_CNPJ_CPF];
    char data_contratos[TAM_MAX_DATA];
    char energia_contratos[TAM_MAX_ENERGIA];
};

struct consumidores
{
      char cnpj_cpf_consumidor[TAM_MAX_CNPJ_CPF];
      char nome_consumidor[TAM_MAX_NOME];
      char RA_consumidor[TAM_MAX_RA];
};

struct ra
{
    char id[TAM_MAX_ID];
    char nome[TAM_MAX_NOME];
    char tamanho[TAM_MAX_TAMANHO];
    char disponivel[20];
    char gasta[20];
};



//funçoes usadas para validar cnpj e outra coisas
bool validarCNPJ(char* cnpj) 
{
    // Removendo caracteres não numéricos
    char cnpjNumerico[15];
    int j = 0;
    for (int i = 0; i < strlen(cnpj); i++) {
        // Verificará qual a natureza do caractere
        // Número ou não número
        if (isdigit(cnpj[i])) {         
            cnpjNumerico[j] = cnpj[i];
            j++;
        }
    }
    cnpjNumerico[j] = '\0';
    // Verificando o tamanho do CNPJ, apenas números
    // Não contando com o caractere NULL
    if (strlen(cnpjNumerico) != 14) {
        return false;
    }
    int digito1 = 0, digito2 = 0;
    int multiplicador1 = 5, multiplicador2 = 6;
    // Cálculo do primeiro dígito verificador
    for (int i = 0; i < 12; i++) {
        digito1 += (cnpjNumerico[i] - '0') * multiplicador1;
        // multiplicador1 = multiplicador1 - 1
        multiplicador1--;
        if (multiplicador1 < 2) {
            multiplicador1 = 9;
        }
    }
    digito1 = 11 - (digito1 % 11);
    if (digito1 >= 10) {
        digito1 = 0;
    }
    // Cálculo do segundo dígito verificador
    for (int i = 0; i < 13; i++) {
        digito2 += (cnpjNumerico[i] - '0') * multiplicador2;
        //multiplicador2 = multiplicador2 - 1
        multiplicador2--;
        if (multiplicador2 < 2) {
            multiplicador2 = 9;
        }
    }
    digito2 = 11 - (digito2 % 11);
    if (digito2 >= 10) {
        digito2 = 0;
    }
    // Verificação dos dígitos verificadores
    if ((cnpjNumerico[12] - '0') == digito1 && (cnpjNumerico[13] - '0') == digito2) 
    {
        return true;
    }
    return false;
    
}

bool validarCPF(const char* cpf) {
    // Remover caracteres não numéricos do CPF
    char cpfNumerico[12];
    int j = 0;
    for (int i = 0; i < strlen(cpf); i++) {
        if (isdigit(cpf[i])) {
            cpfNumerico[j++] = cpf[i];
        }
    }
    cpfNumerico[j] = '\0';

    // Verificar se o CPF possui 11 dígitos
    if (strlen(cpfNumerico) != 11) {
        return false;
    }

    // Verificar se todos os dígitos são iguais (caso especial)
    bool digitosIguais = true;
    for (int i = 1; i < 11; i++) {
        if (cpfNumerico[i] != cpfNumerico[0]) {
            digitosIguais = false;
            break;
        }
    }
    if (digitosIguais) {
        return false;
    }

    // Validar o primeiro dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpfNumerico[i] - '0') * (10 - i);
    }
    int digito1 = (soma * 10) % 11;
    if (digito1 == 10) {
        digito1 = 0;
    }
    if (digito1 != (cpfNumerico[9] - '0')) {
        return false;
    }

    // Validar o segundo dígito verificador
    soma = 0;
    for (int i = 0; i < 10; i++) {
        soma += (cpfNumerico[i] - '0') * (11 - i);
    }
    int digito2 = (soma * 10) % 11;
    if (digito2 == 10) {
        digito2 = 0;
    }
    if (digito2 != (cpfNumerico[10] - '0')) {
        return false;
    }

    return true;
}

void limpar_buffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// Função utilizada para limpar o terminal
void limpar_tela()
{
#if defined(linux) || defined(unix) || defined(APPLE)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}
// Função para o vs code printar em portugues com acento
void charset()
{
    #if defined(_WIN32) || defined(_WIN64)
    system("chcp 65001");
    #endif
}

// funçoes que serão usadas para consultar ou listar os arquivos

//função 1
void consultar_miniusinas()
{
    //declaração de variaveis
    FILE *arquivo_miniusina;
    FILE *arquivo_contratos;
    char cnpj_consultado [20];
    struct miniusinas cadastradas;
    int flag=0;
    struct contratos contratos_cadastrados;
    

    printf("Digite um cnpj: ");
    scanf("%s",cnpj_consultado);
    printf("\n");
   
    //verifica se o cnpj é valido e executa uma ação
    if (validarCNPJ(cnpj_consultado))
    {
        //abre o arquivo
        arquivo_miniusina=fopen("miniusinas.csv","r");
        if (arquivo_miniusina !=NULL)
        {
           //descarta a primeira linha
           char primeira_linha[1000];
           fscanf(arquivo_miniusina,"%[^\n]\n",primeira_linha);
            //inicia a leitura do aquivo
           while (!feof(arquivo_miniusina))
           {
            fscanf(arquivo_miniusina,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                cadastradas.cnpj,
                                cadastradas.nome,
                                cadastradas.capacidade,
                                cadastradas.id,
                                cadastradas.status);

             if (strcmp(cnpj_consultado,cadastradas.cnpj)==0)
             {
                printf("MINIUSINA\n");
                printf("CNPJ: %s\n",cadastradas.cnpj);
                printf("Nome: %s\n",cadastradas.nome);
                printf("Capacidade: %s\n",cadastradas.capacidade);
                printf("ID: %s\n",cadastradas.id);
                printf("Status: %s\n",cadastradas.status);
                printf("\n");
                flag=1;
             }
             
            
            
           }

           if (flag==0)
           {
               printf("O cnpj digitado nao consta no arquivo\n");
               printf("\n");
           }

           else if(flag==1)
           {
            arquivo_contratos=fopen("contratos.csv","r");

             if(arquivo_contratos!=NULL)
             {
                char primeiralinhac[100];
                fscanf(arquivo_contratos,"%[^\n]\n",primeiralinhac);

                while (!feof(arquivo_contratos))
                {
                    fscanf(arquivo_contratos,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                  contratos_cadastrados.id_contratos,
                                  contratos_cadastrados.idconsumidores_contratos,
                                  contratos_cadastrados.cnpj_contratos,
                                  contratos_cadastrados.data_contratos,
                                  contratos_cadastrados.energia_contratos);


                    if(strcmp(cnpj_consultado,contratos_cadastrados.cnpj_contratos)==0)
                    {
                            printf("CONTRATOS\n\n");
                            printf("ID: %s\n",contratos_cadastrados.id_contratos);
                            printf("ID CONSUMIDOR: %s\n",contratos_cadastrados.idconsumidores_contratos);
                            printf("CNPJ: %s\n",contratos_cadastrados.cnpj_contratos);
                            printf("DATA DE INICIO: %s\n",contratos_cadastrados.data_contratos);
                            printf("ENERGIA %s\n\n",contratos_cadastrados.energia_contratos);
                            
                            flag=2;
                    }
                }

                if (flag==1)
                {
                    printf("CONTRATOS\n");
                    printf("Nao foi encontrado nenhum contrato\n\n");
                }
                
            
                
             }
             else if(arquivo_contratos==NULL)
             {
                printf("Arquivo nao encontrado\n\n");
             }
           }
           
           
        }
        else if(arquivo_miniusina == NULL)
        {
           printf("Arquivo nao encontrado\n");
           printf("\n");
        }
        
         
    }
    else
    {
        printf("CNPJ invalido\n");
        printf("\n");
    }
    



}

//função 2
void Listar_miniusinas()
{
    FILE *arquivo_miniusinas;
    struct miniusinas listaminiusinas;

    arquivo_miniusinas = fopen("miniusinas.csv","r");

    if(arquivo_miniusinas != NULL)
    {
        char primeiralinha [100];
        fscanf(arquivo_miniusinas,"%[^\n]\n",primeiralinha);


        while (!feof(arquivo_miniusinas))
        {
             fscanf(arquivo_miniusinas,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                  listaminiusinas.cnpj,
                                  listaminiusinas.nome,
                                  listaminiusinas.capacidade,
                                  listaminiusinas.id,
                                  listaminiusinas.status);


            printf("CNPJ: %s\n",listaminiusinas.cnpj);
            printf("NOME: %s\n",listaminiusinas.nome);
            printf("CAPACIDADE: %s\n",listaminiusinas.capacidade);
            printf("ID: %s\n",listaminiusinas.id);
            printf("STATUS: %s\n",listaminiusinas.status);
            printf("\n");



        }
        

    }
    else if(arquivo_miniusinas == NULL)
    {
        printf("O arquivo de miniusinas nao existe\n");
        printf("\n");
    }
}

//função 3
void Consultar_consumidores()
{
    //variaveis 
    FILE *arquivo_consumidores;
    FILE *arquivo_contratos;
    char cnpj_cpf [20];
    int busca;
    struct consumidores cadastrados;
    struct contratos contratos_cadastrados;
    int encontrado = 0;
    int encontrado2=0;
   
    
    
    //escolha o modo de pesquisa que irá ser consultado
    printf("Modo de pesquisa\n");
    printf("1)CNPJ\n");
    printf("2)CPF\n");
    printf("Escolha a sua opcao: ");
    scanf("%d",&busca);
    
    //abre os arquivos
    arquivo_consumidores = fopen("consumidores.csv","r");
    arquivo_contratos=fopen("contratos.csv","r");
    if(busca ==1)
    {
        //caso seja escolhida a opção 1
        printf("Digite o cnpj: ");
        scanf("%s",cnpj_cpf);
        printf("\n");

        if(validarCNPJ(cnpj_cpf))
        {
            //caso o cnpj que o usuario digitou foi validado 
             
             if(arquivo_consumidores != NULL)
             {
                //abre arquivo
                 
                 while (!feof(arquivo_consumidores))
                 {
                    //leitura do arquivo e preenchimento da struct
                    fscanf(arquivo_consumidores,"%[^;];%[^;];%[^\n]\n",
                                     cadastrados.cnpj_cpf_consumidor,
                                     cadastrados.nome_consumidor,
                                     cadastrados.RA_consumidor);
                    //compara os parametros e executa uma ação caso sejam iguais
                    if(strcmp(cnpj_cpf,cadastrados.cnpj_cpf_consumidor)==0)
                    {
                        //O CNPJ foi encontrado
                        printf("CONSUMIDOR\n");
                        printf("CNPJ/CPF: %s\n",cadastrados.cnpj_cpf_consumidor);
                        printf("NOME: %s\n",cadastrados.nome_consumidor);
                        printf("RA: %s\n",cadastrados.RA_consumidor);
                        printf("\n");
                        encontrado =1;
                    }
                 }

                 if (encontrado==0)
                 {
                    //O cnpj nao foi encontrado 
                    printf("O cnpj digitado nao foi encontrado\n");
                    printf("\n");
                 }

                 else if(encontrado ==1)
                 {
                   
                     //Verifica os contratos
                    if(arquivo_contratos!=NULL)
                    {
                        //abre arquivo e descarta a primeira linha
                        char primeiralinhac[1000];
                        fscanf(arquivo_contratos,"%[^\n]\n",primeiralinhac);
                         while (!feof(arquivo_contratos))
                         {
                            //leitura de arquivo
                            fscanf(arquivo_contratos,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                               contratos_cadastrados.id_contratos,
                                               contratos_cadastrados.idconsumidores_contratos,
                                               contratos_cadastrados.cnpj_contratos,
                                               contratos_cadastrados.data_contratos,
                                               contratos_cadastrados.energia_contratos);
                            
                            if (strcmp(cnpj_cpf,contratos_cadastrados.idconsumidores_contratos)==0)
                            {
                                //contratos vinculados ao cnpj foram encontrados
                                printf("CONTRATOS\n");
                                printf("ID: %s\n",contratos_cadastrados.id_contratos);
                                printf("CONSUMIDOR: %s\n",contratos_cadastrados.idconsumidores_contratos);
                                printf("CNPJ: %s\n",contratos_cadastrados.cnpj_contratos);
                                printf("DATA DE INICIO: %s\n",contratos_cadastrados.data_contratos);
                                printf("ENERGIA CONTRATADA: %s\n",contratos_cadastrados.energia_contratos);
                                printf("\n");
                                encontrado =2;
                            }
                            
                         }

                         if (encontrado == 1)
                         {
                            //o consumidor não possui contratos 
                            printf("O consumidor consultado nao possui contratos\n");
                            printf("\n");
                         }
                        
                         
                    }

                    
                    else if (arquivo_contratos==NULL)
                    {
                        //o arquivo de contratos não foi encontrado
                        printf("Arquivo nao encontrado\n");
                        printf("\n");
        
                    }
                    
                 }
                 
             }
             else if(arquivo_consumidores == NULL)
             {
                //arquivo de consumidores não foi encontrado 
                printf("Arquivo nao encontrado\n");
                printf("\n");
             }
        }
        else
        {
            //o cnpj é inválido
            printf("CNPJ invalido\n");
            printf("\n");
        }

         
        
            
        

    }

    else if(busca == 2)
    {
        //o usuario escolheu a opcao 2
        printf("Digite o cpf: ");
        scanf("%s",cnpj_cpf);
        printf("\n");

        if (validarCPF(cnpj_cpf))
        {
            //o cpf foi validado
            

            if (arquivo_consumidores!=NULL)
            {
                //abre arquivo 
                while (!feof(arquivo_consumidores))
                {
                    //leitura do arquivo
                    fscanf(arquivo_consumidores,"%[^;];%[^;];%[^\n]\n",
                                   cadastrados.cnpj_cpf_consumidor,
                                   cadastrados.nome_consumidor,
                                   cadastrados.RA_consumidor);
                    if (strcmp(cnpj_cpf,cadastrados.cnpj_cpf_consumidor)==0)
                    {
                        //o cpf foi encontrado no arquivo 
                        printf("CONSUMIDOR\n");
                        printf("CNPJ/CPF: %s\n",cadastrados.cnpj_cpf_consumidor);
                        printf("NOME: %s\n",cadastrados.nome_consumidor);
                        printf("RA: %s\n",cadastrados.RA_consumidor);
                        printf("\n");
                        encontrado2=1;
                        
                    }
                    
                }

                if (encontrado2==0)
                {
                    //o cpf não foi encontrado 
                    printf("Consumidor nao encontrado\n");
                    printf("\n");
                }

                else if (encontrado2==1)
                {
                    
                    //cpf encontrado
                    //busca para ver se possui contratos vinculados 
                    if (arquivo_contratos!=NULL)
                    {
                        //abre arquivo e descarta a primeira linha
                        char primeiralinha[1000];
                        fscanf(arquivo_contratos,"%[^\n]\n",primeiralinha);
                        while (!feof(arquivo_contratos))
                        {
                            //leitura de arquivo 
                            fscanf(arquivo_contratos,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                              contratos_cadastrados.id_contratos,
                                              contratos_cadastrados.idconsumidores_contratos,
                                              contratos_cadastrados.cnpj_contratos,
                                              contratos_cadastrados.data_contratos,
                                              contratos_cadastrados.energia_contratos);
                           
                            if (strcmp(cnpj_cpf,contratos_cadastrados.idconsumidores_contratos)==0)
                            {
                                //o cpf foi encontrado no arquivo de contrato 
                               printf("CONTRATO\n");
                               printf("ID: %s\n",contratos_cadastrados.id_contratos);
                               printf("CONSUMIDOR: %s\n",contratos_cadastrados.idconsumidores_contratos);
                               printf("CNPJ: %s\n",contratos_cadastrados.cnpj_contratos);
                               printf("DATA DE INICIO: %s\n",contratos_cadastrados.data_contratos);
                               printf("ENERGIA CONTRATADA: %s\n",contratos_cadastrados.energia_contratos);
                               printf("\n");
                               encontrado2=2;
                            }
                            
                        }

                        if(encontrado2==1)
                        {
                            //o consumidor nao possui contratos 
                            printf("O consumidor nao possui contratos\n");
                            printf("\n");
                        }
                        
                    }
                    else if (arquivo_contratos==NULL)
                    {
                        //arquivo de contrato não foi encontrado
                        printf("Arquivo de contratos nao encontrado\n");
                        printf("\n");
                    }
                    
                    
                }
                
                
                
            }
            else if (arquivo_consumidores==NULL)
            {
               //arquivo de consumidores não foi encontrado
               printf("Arquivo de consumidores nao encontrado\n");
               printf("\n");
            }
            
            
        }
        else
        {
            //cpf consultado não é valido 
            printf("CPF invalido\n");
            printf("\n");
        }
        
    }
     //fechamento dos arquivos
    fclose(arquivo_consumidores);
    fclose(arquivo_contratos);
    
    
}

//função 4
void Listar_MiniUsinas_Dec() 
{
    struct miniusinas miniusinas_dec[11]; 
    
    // abertura e declaração da variavel de arquivo
    FILE *arquivo_miniusinas = fopen("miniusinas.csv", "r");
    
    if (arquivo_miniusinas != NULL) 
    {
        // apaga a primeira linha
        char primeiralinha[100];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeiralinha);
        int i = 0; 

        while (!feof(arquivo_miniusinas)) 
        {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                   miniusinas_dec[i].cnpj,
                   miniusinas_dec[i].nome,
                   miniusinas_dec[i].capacidade,
                   miniusinas_dec[i].id,
                   miniusinas_dec[i].status);
            i++;
        }

        fclose(arquivo_miniusinas);
        // iniciação do vetor ordenado percorre de 0 a 10
        for (int i = 0; i < 10; i++) 
        {
           
            for (int j = i; j < 10; j++) 
            {         //função atof converte string para double
                if (atof(miniusinas_dec[i].capacidade) > atof(miniusinas_dec[j].capacidade)) 
                {   // variavel de verificação
                    struct miniusinas flag = miniusinas_dec[i];
                    miniusinas_dec[i] = miniusinas_dec[j]; 
                    miniusinas_dec[j] = flag;
                }
            }
        }
        // verifica se no processo existe alguma numero menor que o anterior e troca de lugar
        for (int i = 9; i >= 0; i--) 
        {
            printf("CNPJ: %s\n", miniusinas_dec[i].cnpj);
            printf("NOME: %s\n", miniusinas_dec[i].nome);
            printf("CAPACIDADE: %s\n", miniusinas_dec[i].capacidade);
            printf("ID: %s\n", miniusinas_dec[i].id);
            printf("STATUS: %s\n", miniusinas_dec[i].status);
            printf("\n");
        }
    } 
    else 
    {
        printf("Erro ao abrir o arquivo.\n");
    }
    //fechamento do arquivo
    fclose(arquivo_miniusinas);
}

//função 5
void Listar_RA_dec_min() 
{
    FILE *arquivo_ra;
    struct ra ra_arquivo[34];
    arquivo_ra=fopen("ra.csv","r");
    if (arquivo_ra!=NULL)
    {
        //descarta a primeira linha
        char primeira[1000];
        fscanf(arquivo_ra,"%[^\n]\n",primeira);
        //ler o arquivo
        int i=0;
        while (!feof(arquivo_ra))
        {
            fscanf(arquivo_ra,"%[^;];%[^\n]\n",
                            ra_arquivo[i].id,
                            ra_arquivo[i].nome);
            
            strcpy(ra_arquivo[i].tamanho,"0");
            i++;        
        }

        FILE *arquivo_miniusina;
        struct miniusinas miniusina_arquivo[11];
        arquivo_miniusina=fopen("miniusinas.csv","r");
        if (arquivo_miniusina!=NULL)
        {
            //descarta a primeira linha
            char primeiralinha[1000];
            fscanf(arquivo_miniusina, "%[^\n]\n",primeiralinha);
            //ler o arquivo
            int j = 0;
            while (!feof(arquivo_miniusina))
            {
                //lendo o arquivo
                fscanf(arquivo_miniusina,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                        miniusina_arquivo[j].cnpj,
                        miniusina_arquivo[j].nome,
                        miniusina_arquivo[j].capacidade,
                        miniusina_arquivo[j].id,
                        miniusina_arquivo[j].status);
                for (int i = 0; i < 33; i++)
                {
                    //for que sera reponsavel por atribuir a quantidade de miniuisinas que um ra possui
                    if (strcmp(ra_arquivo[i].id,miniusina_arquivo[j].id) == 0)
                    {
                        //o ra foi encontrado no arquivo de miniusinas
                        //funçao q transforma um char em um int
                        int cont = atoi(ra_arquivo[i].tamanho);
                        ///o contador ira somar mais 1 pq achou a ra
                        cont++;
                        ///o valor da variavel tamanho ira atualizar de acordo com o contador 
                        sprintf(ra_arquivo[i].tamanho,"%d", cont);
                    }
                    
                }
    
            }

            for (int i=0; i<32; i++)
            {
               for (int  j=i+1; j<33;j++)
               {
                    int numero1=atoi(ra_arquivo[i].tamanho);
                    int numero2=atoi(ra_arquivo[j].tamanho);

                    if (numero1 < numero2)
                    {
                       struct ra auxiliar=ra_arquivo[i];
                       ra_arquivo[i]=ra_arquivo[j];
                       ra_arquivo[j]=auxiliar;
                       
                    }
                    
               }
               
            }


            for (int i=0; i<33; i++)
            {
                printf("ID:%s\n",ra_arquivo[i].id);
                printf("Nome: %s\n",ra_arquivo[i].nome);
                printf("miniusinas: %s\n",ra_arquivo[i].tamanho);
                printf("\n");
            }
            
            


            


        }
        else if (arquivo_miniusina==NULL)
        {
           printf("Arquivo de miniusina nao foi aberto\n");
        }
        
        
        
    }
    else if (arquivo_ra==NULL)
    {
        printf("Arquivo de ra nao foi aberto\n");
    }
    
    fclose(arquivo_ra);
}

//função 6 falta comentar a abertura do arquivo de usina
void Listar_ra_cr_cont()
{
    //são declaradas variaveis que serão usadas para abrir e ler o arquivo de ra
    FILE *arquivo_ra;
    struct ra ra_arquivo[34];
    arquivo_ra = fopen("ra.csv","r");
    if(arquivo_ra!=NULL)
    {
       //abre o arquivo e descarta a primeira linha
        char primeira[1000];
        fscanf(arquivo_ra,"%[^\n]\n",primeira);
        //le o arquivo de ra's e o preenche
        int i=0;
        while (!feof(arquivo_ra))
        {
            fscanf(arquivo_ra,"%[^;];%[^\n]\n",
                            ra_arquivo[i].id,
                            ra_arquivo[i].nome);
            
            strcpy(ra_arquivo[i].tamanho,"0");
            i++;        
        }
       FILE *arquivo_minisuina;
       struct miniusinas miniusinas_arquivo[11];
       arquivo_minisuina=fopen("miniusinas.csv","r");
       if (arquivo_minisuina!=NULL)
       {
          //abre o arquivo e descarta a primeira linha
          char primeiralinha2[1000];
          fscanf(arquivo_minisuina,"%[^\n]\n",primeiralinha2);
          //le o arquivo e preenche a struct
          int i=0;
          while (!feof(arquivo_minisuina))
          {
             fscanf(arquivo_minisuina,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                    miniusinas_arquivo[i].cnpj,
                                    miniusinas_arquivo[i].nome,
                                    miniusinas_arquivo[i].capacidade,
                                    miniusinas_arquivo[i].id,
                                    miniusinas_arquivo[i].status);
            i++;
          }
          FILE *arquivo_contrato;
          struct contratos contratos_arquivo[8];
          arquivo_contrato=fopen("contratos.csv","r");
          if (arquivo_contrato!=NULL)
          {
            //abre o arquivo e descarta a primeira linha
            char primeiralinha3[100];
            fscanf(arquivo_contrato,"%[^\n]\n",primeiralinha3);
            //le o arquivo e preenche a struct
            int i=0;
            while (!feof(arquivo_contrato))
            {
                fscanf(arquivo_contrato,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                        contratos_arquivo[i].id_contratos,
                                        contratos_arquivo[i].idconsumidores_contratos,
                                        contratos_arquivo[i].cnpj_contratos,
                                        contratos_arquivo[i].data_contratos,
                                        contratos_arquivo[i].energia_contratos);
                
                for (int j=0; j<33; j++)
                {
                    for (int w=0; w<11;w++)
                    {
                        if(strcmp(ra_arquivo[j].id,miniusinas_arquivo[w].id)==0)
                        {
                            if (strcmp(miniusinas_arquivo[w].cnpj,contratos_arquivo[i].cnpj_contratos)==0)
                            {
                                int cont = atoi(ra_arquivo[j].tamanho);
                                cont++;
                                sprintf(ra_arquivo[j].tamanho,"%d",cont);
                            }
                            
                        }
                    }
                    
                }
                i++; 
            }
            //for para ordenar a struct 
           for (int i=0; i<32; i++)
           {
              //variavel i para controlar a posiçao de comparação
              for (int j=i+1; j<33; j++)
              {
                //variavel j para contolar a posiçao de comparação ao anteirior
                //transformar int em char
                 int comp1=atoi(ra_arquivo[i].tamanho);
                 int comp2=atoi(ra_arquivo[j].tamanho);
                 if (comp1 < comp2)
                 {
                    //os numeros foram comparados
                    //se o valor da posiçao i for menor do que j as posiçoes sao trocadas 
                    //struct auxiliar para a troca
                    struct ra auxiliar=ra_arquivo[i];
                    ra_arquivo[i]=ra_arquivo[j];
                    ra_arquivo[j]=auxiliar;                   
                 }             
              }
            }
        
           //funcao para listar a quantidade de ra na hora de imprimir 
           int ordenando=0;
           for (int i=32; i>=0;i--)
           {
               //for que ira pecorrer em ordem crescente e printar o resultado
               printf("%d: id:%s nome:%s - %s contratos\n",ordenando+1,ra_arquivo[i].id,ra_arquivo[i].nome,ra_arquivo[i].tamanho);
               printf("\n");
               ordenando++;
           } 
          }
          else if (arquivo_contrato==NULL)
          {
              printf("arquivo de contratos nao encontrado\n");
              printf("\n");
          }
               
       }
       else if (arquivo_minisuina==NULL)
       {
          //o arquivo de contrato nao foi aberto 
          printf("Arquivo de miniusinas nao encontrado\n");
          printf("\n");
       }   
       fclose(arquivo_minisuina);
    }
    else if (arquivo_ra==NULL)
    {
        //o arquivo de ra nao foi aberto 
        printf("Arquivo de ra nao encontrado\n");
        printf("\n");
    }
    fclose(arquivo_ra);
}

//função 7
void Listar_RA_dec_gera()
{
    FILE *arquivo_ra;
    struct ra ra_arquivo[33];

    arquivo_ra = fopen("ra.csv", "r");

    if (arquivo_ra != NULL)
    {
        //descarta a primeira linha
        char primeiralinha[100];
        fscanf(arquivo_ra, "%[^\n]\n", primeiralinha);

        int i = 0;
        while (!feof(arquivo_ra))
        {   
            //leitura do arquivo e preenchimento da struct
            fscanf(arquivo_ra, "%[^;];%[^\n]\n",
                   ra_arquivo[i].id,
                   ra_arquivo[i].nome);
            strcpy(ra_arquivo[i].tamanho, "0"); //Define a quantidade de miniusinas como "0" para cada RA lida

            i++; //incremento para ler a próxima linha do arquivo
        }
    }

    FILE *arquivo_miniusinas;
    struct miniusinas mini_arquivo[10];

    arquivo_miniusinas = fopen("miniusinas.csv", "r");

    if (arquivo_miniusinas != NULL)
    {
        char primeiralinha[100];
        fscanf(arquivo_miniusinas, "%[^\n]\n", primeiralinha);
        int i = 0;
        while (!feof(arquivo_miniusinas))
        {
            fscanf(arquivo_miniusinas, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                   mini_arquivo[i].cnpj,
                   mini_arquivo[i].nome,
                   mini_arquivo[i].capacidade,
                   mini_arquivo[i].id,
                   mini_arquivo[i].status);

            for (int j = 0; j < 33; j++) // Loop para percorrer cada RA
            {                            // Verifica se o ID da miniusina corresponde ao IDda RA
                if (strcmp(mini_arquivo[i].id, ra_arquivo[j].id) == 0)
                {
                    double numero = atof(ra_arquivo[j].tamanho);
                    numero += atof(mini_arquivo[i].capacidade);
                    sprintf(ra_arquivo[j].tamanho, "%.2lf", numero);//printa na string
                    break;
                }
            }
            i++;
        }
    }
    // Ordenação das RAs por quantidade de miniusinas em ordem decrescente
    for (int i = 0; i < 32; i++)
    {
        for (int j = i + 1; j < 33; j++)
        {
            // qtd_i e qtd_j são obtidos convertendo as quantidades de miniusinas para double usando atof
            float qtd_i = atof(ra_arquivo[i].tamanho);
            float qtd_j = atof(ra_arquivo[j].tamanho);

            // Compara as quantidades de miniusinas entre duas RAs
            if (qtd_i < qtd_j)
            {
                //troca as posições para a ordem decrescente
                struct ra auxiliar = ra_arquivo[i];
                ra_arquivo[i] = ra_arquivo[j];
                ra_arquivo[j] = auxiliar;
            }
        }
    }

    printf("RAs por ordem decrescente de quantidade de miniusinas:\n\n");
    for (int i = 0; i < 33; i++)
    {
        printf("%d %s - %.2f kWh de capacidade\n", i + 1, ra_arquivo[i].nome, atof(ra_arquivo[i].tamanho));
        printf("\n");
    }

    fclose(arquivo_ra);
    fclose(arquivo_miniusinas);
}

//função 8
void Listar_RA__dec_perc()
{
    //Abre o arquivo
    FILE *arquivo_ra;
    struct ra ra_cadastradas[34];
    arquivo_ra = fopen("ra.csv","r");
    if (arquivo_ra!=NULL)
    {
        //descarta a primeira linha
        char primeiralinha[1000];
        fscanf(arquivo_ra,"%[^\n]\n",primeiralinha);
        //int para pecorrer pela struct
        int i=0;
        while (!feof(arquivo_ra))
        {
            //le o arquivo e preenche as variaveis
           fscanf(arquivo_ra,"%[^;];%[^\n]\n",
                    ra_cadastradas[i].id,
                    ra_cadastradas[i].nome);

            strcpy(ra_cadastradas[i].tamanho,"0");
            strcpy(ra_cadastradas[i].gasta,"0");          //inicializa variaveis com "0" para evitar lixo de memoria
            strcpy(ra_cadastradas[i].disponivel,"0");
            i++;
        }
        //Abre o arquivo
        FILE *arquivo_miniusina;
        struct miniusinas miniusinas_cadastradas[11];
        arquivo_miniusina=fopen("miniusinas.csv","r");
        if (arquivo_miniusina!=NULL)
        {
            //arquivo miniusinas aberto
            //primeira linha descartada
            char primeiralinha2[100];
            fscanf(arquivo_miniusina,"%[^\n]\n",primeiralinha2);
            //int para pecorrer pela struct
            int k=0;
            while (!feof(arquivo_miniusina))
            {
                //le o arquivo e preenche as variaveis
                fscanf(arquivo_miniusina,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                miniusinas_cadastradas[k].cnpj,
                                miniusinas_cadastradas[k].nome,
                                miniusinas_cadastradas[k].capacidade,
                                miniusinas_cadastradas[k].id,
                                miniusinas_cadastradas[k].status);
                //for para por somar a capacidade total de uma ra 
                for (int i=0; i<33; i++)
                {

                    if (strcmp(ra_cadastradas[i].id,miniusinas_cadastradas[k].id)==0)
                    {
                        //caso o id da ra for igual ao da miniusina, a capacidade ira somar 
                        //o contador atribui o valor da variavel tamanho
                        int contador=atoi(ra_cadastradas[i].tamanho);
                        //o contador soma com a capacidade da miniusina
                        contador+=atoi(miniusinas_cadastradas[k].capacidade);
                        //a variavel tamanho é atualizada com o novo valor 
                        sprintf(ra_cadastradas[i].tamanho,"%d",contador);
                    }            
                }
                k++;
            }
            //declaradas variveis para abrir o arquivo contratos
            FILE *arquivo_contratos;
            struct contratos contratos_cadastrados[8];
            arquivo_contratos=fopen("contratos.csv","r");
            if (arquivo_contratos!=NULL)
            {
                //arquivo de contratos aberto
                //primeira linha descartada
                char primeiralinha3[1000];
                fscanf(arquivo_contratos,"%[^\n]\n",primeiralinha3);
                //int que sera responsavel por pecorrer pela struct
                int j=0;
                while (!feof(arquivo_contratos))
                {
                    //arquivo de contratos esta sendo lido e as variaveis preechidas
                    fscanf(arquivo_contratos,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n",
                                        contratos_cadastrados[j].id_contratos,
                                        contratos_cadastrados[j].idconsumidores_contratos,
                                        contratos_cadastrados[j].cnpj_contratos,
                                        contratos_cadastrados[j].data_contratos,
                                        contratos_cadastrados[j].energia_contratos);
                    //for que sera responsavel por somar a quantidade de energia contratada por ra 
                    for (int i=0; i<33; i++)
                    {
                        //a variavel i ira pecorrer pela struct de ra 
                        for (int k=0; k<11; k++)
                        {
                            //a variavel k ira pecorrer pela struct de miniusinas
                            if (strcmp(ra_cadastradas[i].id,miniusinas_cadastradas[k].id)==0)
                            {
                                //caso o id da ra foi encontrado no arquivo de miniusinas
                                if (strcmp(miniusinas_cadastradas[k].cnpj,contratos_cadastrados[j].cnpj_contratos)==0)
                                {
                                    //foi encontrados os contratos associados aos cnpj das miniusinas associadas a ra 
                                    //gasto ira receber o valor da varivel gasta
                                    int gasto=atoi(ra_cadastradas[i].gasta);
                                    //gasto ira somar a quantidade de energia contratada
                                    gasto +=atoi(contratos_cadastrados[j].energia_contratos);
                                    //a variavel gasta atualizada
                                    sprintf(ra_cadastradas[i].gasta,"%d",gasto);
                                }                                
                            }                    
                        }                  
                    }
                    j++;          
                }
                //for que ira calcular a porcentagem 
                for (int i=0; i<33; i++)
                {
                    if (!strcmp(ra_cadastradas[i].tamanho,"0"))
                    {
                        //Desconsidera as variaveis que nao tem capacidade
                        continue;
                    }
                    //função que calcula a porcentagem 
                    float porcentagem = atoi(ra_cadastradas[i].gasta);
                    porcentagem=(porcentagem*100.0)/atoi(ra_cadastradas[i].tamanho);
                    sprintf(ra_cadastradas[i].disponivel,"%.2f",100-porcentagem);       
                }
                //for para ordenar em ordem decrescente 
                for (int i=0; i<32; i++)
                {
                    if (!strcmp(ra_cadastradas[i].tamanho,"0"))
                    {
                        //Ras sem capacidades são desconsideradas 
                        continue;
                    } 
                    for (int j=i+1; j<33; j++)
                    {
                        if (!strcmp(ra_cadastradas[j].tamanho,"0"))
                        {
                            //Ras sem capacidades são desconsideradas 
                            continue;
                        }   
                        int comparar1 =atoi(ra_cadastradas[i].disponivel);
                        int comparar2=atoi(ra_cadastradas[j].disponivel);
                        if (comparar1 < comparar2)
                        {
                            //troca as posições para ordem decrescente
                            struct ra auxiliar=ra_cadastradas[i];
                            ra_cadastradas[i]=ra_cadastradas[j];
                            ra_cadastradas[j]=auxiliar;
                        }                    
                    }            
                }
                //for para printar o resultado
                for (int i=0; i<33; i++)
                {
                    if (!strcmp(ra_cadastradas[i].tamanho,"0"))
                    {
                        continue;
                    }
                        printf("ID da RA: %s\n",ra_cadastradas[i].id);
                        printf("Nome da RA: %s\n",ra_cadastradas[i].nome);
                        printf("Percentual de energia disponivel: %s %%\n",ra_cadastradas[i].disponivel);
                        printf("\n");             
                }     
            }
            else if (arquivo_contratos==NULL)
            {
                printf("Arquivo de contratos nao encontrado\n");
                printf("\n");
            }      
        }
        else if (arquivo_miniusina==NULL)
        {
            printf("Arquivo de miniusinas nao encontrado\n");
            printf("\n");
        }     
    }
    else if (arquivo_ra==NULL)
    {
        printf("Arquivo de ra nao encontrado\n");
        printf("\n");
    }    
}
