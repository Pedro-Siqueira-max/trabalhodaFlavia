#include <iostream>
#include <string.h>

struct reg
{
	char nome[20];
	char tel[20];
	char email[20];
	char cor[20];
	char modelo[20];
	char marca[20];
	char status;
};

int tamanho(FILE *);
void cadastrar(FILE *);
void consultar(FILE *);
void gerar_arq(FILE *);
void excluir(FILE *);

int main()
{

	int op;
	FILE *arq;

	if ((arq = fopen("dados.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados.dat", "wb+")) == NULL)
		{
			printf("\nFalha ao abrir o arquivo!\n");
			system("pause");
		}
	}

	do
	{
		system("CLS");
		printf("\n========== AGENDA DA CONCESSIONARIA ==========");
		printf("\n1.Cadastrar\n");
		printf("\n2.Consultar\n");
		printf("\n3.Gerar arquivo\n");
		printf("\n4.excluir arquivo\n");
		printf("\n5.Sair\n");
		printf("============Contatos: %d=\n", tamanho(arq));
		printf("Opcao: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1:
			cadastrar(arq);
			break;
		case 2:
			consultar(arq);
			break;
		case 3:
			gerar_arq(arq);
			break;
		case 4:
			excluir(arq);
			break;
		case 5: fclose(arq);
		} 
	} while (op != 4);
}

void cadastrar(FILE *arq)
{ 
	reg contato; 
	char confirma;

	fflush(stdin);
	printf("Cadastrando novo registro: \n");
	printf("\nNumero do registro: %d\n", tamanho(arq) +1);
	printf("Nome do Comprador............: ");
	gets(contato.nome);
	printf("Telefone do Comprador.........:");
	gets(contato.tel);
	printf("e-mail do Comprador...........:");
	gets(contato.email);
	printf("Cor do veiculo................:");
	gets(contato.cor);
	printf("Modelo do veiculo.............:");
	gets(contato.modelo);
	printf("Marca do Veiculo..............:");
	gets(contato.marca);
	printf("\nConfirma <s/n>:");
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\n gravando ....\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&contato, sizeof(reg), 1, arq);

	}
}

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}

void consultar(FILE *arq)
{
reg contato;
int nr;
printf("\nConsulta pelo codigo\n");
printf("\nInforme o Codigo...:");
scanf("%d",&nr);
if ( (nr<=tamanho(arq)) && (nr>0) )
{
fseek(arq,(nr-1)*sizeof(reg),SEEK_SET);
fread(&contato,sizeof(reg),1,arq);
printf("\nNome do Comprador......:%s",contato.nome);
printf("\nTelefone do Comprador..:%s",contato.tel);
printf("\ne-mail do Comprador....:%s",contato.email);
printf("\nModelo do Veiculo......:%s",contato.modelo);
printf("\nCor do Veiculo.........:%s",contato.cor);
printf("\nMarca do Veiculo.......:%s\n",contato.marca);
}
else
{
printf("\nNumero de registro invalido!\n");
}
system("pause");
}
void gerar_arq(FILE *arq)
{
	char nomeArq[20];
	printf("Informe o nome do arquivo: ");
	scanf("%s",&nomeArq);
	strcat(nomeArq,".txt");
	
	FILE *arqtxt = fopen(nomeArq,"w");
	
	if (!arqtxt)
	{
		printf("\nNão foi possível criar este arquivo!\n");
		system("pause");
		
	}
	
	fprintf(arqtxt,"Marca       Modelo      Cor");
	fprintf(arqtxt,"================================\n");
	
	int nr;
	
	reg cadastro;
	
	for(nr = 0; nr < tamanho(arq); nr++)
	{
		fseek(arq,nr * sizeof(reg),SEEK_SET);
		fread(&cadastro,sizeof(reg),1,arq);
		fprintf(arqtxt,"%-10s %-10s %-10s",cadastro.marca,cadastro.modelo,cadastro.cor);
		
	}
	fprintf(arqtxt,"\n====================================");
	fclose(arqtxt);
}

void excluir(FILE*arq)
{
	reg contato;
	char confirma;
	int nr;

	printf("\nInforme o codigo do registro para excluir\n");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\nNome do Comprador......:%s",contato.nome);
			printf("\nTelefone do Comprador..:%s",contato.tel);
			printf("\ne-mail do Comprador....:%s",contato.email);
			printf("\nModelo do Veiculo......:%s",contato.modelo);
			printf("\nCor do Veiculo.........:%s",contato.cor);
			printf("\nMarca do Veiculo.......:%s\n",contato.marca);
			printf("\nConfirma a exclusao: <s/n>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nexcluindo...\n\n");
				fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
				contato.status = '*';
				fwrite(&contato, sizeof(reg), 1, arq);
			}
		}
	else
		printf("Registro inexistente! \n");
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}


