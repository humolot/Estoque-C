// @Humolot - Gianck 
// Projeto Estoque em C 
// ------ // ----------
#include<iostream>
#include<cstring>
using namespace std;
struct dados
{
    char nome[20],local[20],cod[20];
    
};
dados d;
//declarando ponteiro de arquivo
FILE *p;
char esc;
int cont = 0;
int aux=0;
int salto = 0;
int saltorRemocao=0;
double totalLavagens;
int i=0;
int nao=0;
int aux1=0;
bool valueFound=false;
void cadastro();
void listar();
void pesquisar();
void alterar();
void excluir();
int main()
{
    int op;
   
    
    p = fopen("cadastro.txt","rb+");// tenta abrir o arquivo
    if(p==NULL)
    {
        p = fopen("cadastro.txt","wb+");
        if(p==NULL)
        {
            cout << "Impossivel abrir arquivo!";
            exit(1);
        }
    }
    if(p!=NULL)
    {
        do
	{
		do
		{
          system("cls");    
		  system("color f0");
          cout<<"\t\t|************************************************|"<<endl;
          cout<<"\t\t|*                                              *|"<<endl;
          cout<<"\t\t|*              SEJAM BEM VINDOS!               *|"<<endl;
          cout<<"\t\t|*                                              *|"<<endl;      
          cout<<"\t\t|*              SISTEMA DE ESTOQUE              *|"<<endl;
          cout<<"\t\t|*                                              *|"<<endl;
          cout<<"\t\t|*---------------------Menu---------------------*|"<<endl;
          cout<<"\t\t|*                                              *|"<<endl;
          cout<<"\t\t|*          1 - Cadastrar Produto(s)            *|"<<endl;
          cout<<"\t\t|*          2 - Listar Produto(s)               *|"<<endl;
          cout<<"\t\t|*          3 - Pesquisar Produto(s)            *|"<<endl; 
          cout<<"\t\t|*          4 - Alterar Produto(s)              *|"<<endl;       
          cout<<"\t\t|*          5 - Excluir Produto(s)              *|"<<endl;            
          cout<<"\t\t|*          6 - Sair                            *|"<<endl;
          cout<<"\t\t|*                                              *|"<<endl;
          cout<<"\t\t|************************************************|"<<endl;
          cout<<endl;
          cout<<"\t\t               Opcao Escolhida: "; cin>>op;
		
		}while(op<1 || op>6);
		
		
		
		
		
            switch(op)
            {
                case 1: cadastro();
                        break;
                        
                case 2: listar();
                        break;
              
              
                case 3: pesquisar();
                        break;
                        
                case 4: alterar();
                        break;
                          
                case 5: excluir();
                        break;  
                                 
                case 6: system("exit");
                        break;
            }// fim switch
            nao=0;
        }while(op!=6);
    }
}
void alterar()
{
     
     system("cls");   
     cout<<endl<<endl;
     cout<<"\tALTERACAO DE PRODUTO"<<endl<<endl;
     fseek(p,0,SEEK_SET);
     fread(&cont,sizeof(cont),1,p);
     char codigo[20];
     cin.ignore();
     cout << "Entre com o codigo do produto a ser pesquisado:";
     cin.getline(codigo,20);
     for( i=0;i<cont;i++)
     {
          salto = sizeof(d)*i + sizeof(cont);
          fseek(p,salto,SEEK_SET);
          fread(&d,sizeof(d),1,p);
          if(strcmp(codigo,d.cod)==0) 
          {
                                      system("cls");          
                                      cout<<endl;
                                      cin.ignore(); 
                                      cout<<"Novo nome do produto:"; cin.getline(d.nome,20);
                                      cout<<"Novo localizacao do produto:";  cin.getline(d.local,20);
                                      cout<<"Novo codigo do produto:";  cin.getline(d.cod,20);
                                      nao=1;
          }
          salto = sizeof(d)*i + sizeof(cont);
          fseek(p,salto,SEEK_SET);
          fwrite(&d,sizeof(d),1,p);
     }
     if(nao==0)
     {
               cout<<"Produto nao encontrado"<<endl;
               system("PAUSE");
     }
}
void excluir()
{
     system("cls");          
     cout<<endl;
     fseek(p,0,SEEK_SET);
     fread(&cont,sizeof(cont),1,p);
     char codigo[20];
     cin.ignore();
     cout<<"\tEXCLUSAO DE PRODUTOS"<<endl<<endl;
     cout << "Entre com o codigo do produto a ser pesquisado:";
     cin.getline(codigo,20);
     dados carro1; 
     valueFound = false;
     for( i=0;i<cont;i++)
     {
          salto = sizeof(d)*i + sizeof(cont);
          fseek(p,salto,SEEK_SET);
          fread(&d,sizeof(d),1,p);
          if(strcmp(codigo,d.cod)==0)
          {
                                     valueFound =true;
                                     aux =i;
                                     nao=1;
          }
     }
     if ((aux== (cont-1)& valueFound)){
     cont = cont - 1;      
     fseek(p,0,SEEK_SET);
     fwrite(&cont,sizeof(cont),1,p);            
     }else if (valueFound)
     {
           for( i=aux;i<cont-1;i++)
           {
                salto = sizeof(d)*i + sizeof(cont);
                fseek(p,salto,SEEK_SET);
                fread(&d,sizeof(d),1,p);
                salto = sizeof(d)*(i+1) + sizeof(cont);
                fseek(p,salto,SEEK_SET);
                fread(&carro1,sizeof(d),1,p);
                strcpy(d.cod, carro1.cod);
                strcpy(d.nome, carro1.nome);
                strcpy(d.local, carro1.local);
                salto = sizeof(d)*i + sizeof(cont);
                fseek(p,salto,SEEK_SET);
                fwrite(&d,sizeof(d),1,p);
                fseek(p,0,SEEK_SET);
                aux1=i+1;
                fwrite(&aux1,sizeof(aux1),1,p);
           }
                        cont=aux1;
     }
      if(nao==0)
     {
                cout<<endl<<"Erro na Exclusao"<<endl<<endl;
                system("PAUSE");
     }else
     {
          cout<<endl<<endl<<"Exclusao com sucesso!"<<endl<<endl;
          system("PAUSE");
     }
     
}
void pesquisar()
{
     system("cls");          
     cout<<endl;
     cout<<"\tPESQUISA DE PRODUTO"<<endl<<endl;
     fseek(p,0,SEEK_SET);
     fread(&cont,sizeof(cont),1,p);
     char codigo[20];
     cin.ignore();
     cout << "Entre com o codigo do produto a ser pesquisado:";
     cin.getline(codigo,20);
     for( i=0;i<cont;i++)
     {
          salto = sizeof(d)*i + sizeof(cont);
          fseek(p,salto,SEEK_SET);
          fread(&d,sizeof(d),1,p);
          if(strcmp(codigo,d.cod)==0) 
          {
                                      cout<<endl<<"Nome do produto: "<< d.nome<<endl;
                                      cout<<"Localizacao do produto: " <<d.local<<endl;
                                      cout<<"Codigo do produto: " << d.cod<<endl<<endl;  
                                      nao=1;
          }
     }
     if(nao==0)
     {
               cout<<endl<<endl<<"Produto nao encontrado!"<<endl<<endl;
     }
     system("PAUSE");
                       
}
     
void cadastro()
{
     fseek(p,0,SEEK_SET);
     fread(&cont,sizeof(cont),1,p);
     do
     {
                                   system("cls");          
                                   cout<<endl;
                                   cout<<"\tCADASTRO DE PRODUTO"<<endl<<endl;
                                   cin.ignore();
                                   cout<<"Nome do produto:";  
                                   cin.getline(d.nome,20);
                                   cout<<"Localizacao do produto:";  
                                   cin.getline(d.local,20);
                                   cout<<"Codigo do produto:";  
                                   cin.getline(d.cod,20);
                                   salto = sizeof(d)*cont+sizeof(cont);
                                   fseek(p,salto,SEEK_SET);
                                   fwrite(&d,sizeof(d),1,p);
                                   fseek(p,0,SEEK_SET);
                                   cont++;
                                   fwrite(&cont,sizeof(cont),1,p);
                                   do
                                   {
                                                                  cout<<"Deseja cadastrar outro Produto (S/N)?: "; cin>>esc;
                                   }while ((toupper(esc)!='N')&&(toupper(esc)!='S'));
     }while(toupper(esc)!='N');
}
void listar()
{
     system("cls");          
     cout<<endl;
     cout<<"\tLISTA DE PRODUTOS"<<endl<<endl;
     fseek(p,0,SEEK_SET);
     fread(&cont,sizeof(cont),1,p);
     for( i=0; i<cont; i++) 
     {
          salto = sizeof(d)*i + sizeof(cont);
          fseek(p,salto,SEEK_SET);
          fread(&d,sizeof(d),1,p);
          cout<<endl<<"Nome do produto: "<< d.nome<<endl;
          cout<<"Localizacao do produto: " <<d.local<<endl;
          cout<<"Codigo do produto: " << d.cod<<endl<<endl<<endl;  
     }
     if(cont!=0)
     {
                cout << endl << endl << "Total de produtos " << i<<endl; 
     }
     system ("PAUSE");               
}
