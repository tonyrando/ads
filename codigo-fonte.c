#include<stdio.h>
#include<conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PASSWORD "1"
#define USER "u"

int erro = 0;
char str[100];
char entrada[50];

char nome[50];
char telefone[50] = "Nao Informado";
char endereco[150];
char nasc[50];
int idade;
char email[50] = "Nao Informado";
char dataDiagnostico[50];
char cpf[50];
char cep[50];
char comorbidadeDeclaradas[500];
int comorbidadesA = 0;

int dats(char* data[]);
int login();
void mascara(char *frase, char formato[], int caracteres);
void Arquivo();

void Nome();
void CPF();
void DataDiagnostico();
void Nascimento();
void Telefone();
void Email();
void Endereco();
void Comorbidades();

void Cadastrar();
void ExibeDados();
void LimpaDados();

int main(){
	int k = 0;
	if(!login()) return 0;

	do{
		Cadastrar();

		system("CLS");
		fflush(stdin);
		printf("Entrar com Outro paciente?[s/n]:\t");

		switch(getch()){
			case 's':
				system("CLS");
				k = 1;
				LimpaDados();
				break;
			case 'n':
				system("CLS");
				break;
			default:
				system("CLS");
				puts("Opcao invalida!\a");
				system("pause");
				break;
		}
	}while(k);
}

void Cadastrar(){
	Nome();
	CPF();
	Endereco();
	DataDiagnostico();
	Nascimento();
	Telefone();
	Email();
	Comorbidades();
	ExibeDados();
	if(idade >= 65 || comorbidadesA) Arquivo();
	printf("\n\n\n");
	system("pause");
}

void Arquivo(){
	FILE *pont_arq;
	char palavra[20];

	pont_arq = fopen("arquivo.txt", "w");
	if(pont_arq == NULL) printf("Erro na abertura do arquivo!");
	fprintf(pont_arq, "CEP: %s; Idade: %i", cep, idade);
	fclose(pont_arq);
	printf("\n\n\nDados gravados com sucesso!");
}


void LimpaDados(){
	idade = 0;

	memset(&str, 0, 100);
	memset(&entrada, 0, 50);
	memset(&nome, 0, 50);
	memset(&dataDiagnostico, 0, 50);
	memset(&nasc, 0, 50);
	memset(&cpf, 0, 50);
	memset(&cep, 0, 50);
	memset(&comorbidadeDeclaradas, 0, 28);
	memset(&endereco, 0, 150);
	
	strcpy(telefone, "Nao Informado");
	strcpy(email, "Nao Informado");
}

void ExibeDados(){
	printf("\nNome: %s", nome);
	printf("\nCPF: %s", cpf);
	printf("\nTelefone: %s", telefone);
	printf("\nEmail: %s", email);
	printf("\nEndereco: %s", endereco);
	printf("\nData de Nascimento [Idade]: %s [%i Anos]", nasc, idade);
	printf("\nData do Diagnostico: %s", dataDiagnostico);
	printf("\nComorbidades: %s", comorbidadeDeclaradas);
	return;
}

void Nome(){
	fflush(stdin);
	printf("Entre com o Nome do paciente:\t");
	gets(nome);
	system("cls");
	return;
}

void CPF(){
	char t[100];
	erro = 0;

	do{
		if(erro){
			printf("CPF Invalido!\n\n");
	    	system("pause");
			system("cls");
		}
		fflush(stdin);
		printf("Entre com o CPF do paciente:\t");
		gets(cpf);
		system("cls");
		mascara(cpf, "###.###.###-##", 11);
		strcpy(cpf, str);
	} while(erro);
	
	return;
}

void mascara(char *frase, char formato[], int caracteres){
	erro = 0;
	char aux[100];
    int i = 0;
    
    if(strlen(frase) == caracteres){    
	    while(*frase){
			if(formato[i] != '#') aux[i] = formato[i];
			else aux[i] = *frase++;
			i++;
		}
		strcpy(str, aux);
	} else erro = 1;
}

void Endereco(){
	int tentativa = 1;
	
	printf("Entre com o Endereco do paciente:\nNome da Rua:\t");
	fflush(stdin);
	gets(entrada);
	strcpy(endereco, entrada);
	
	printf("Numero da Residencia:\t");
	fflush(stdin);
	gets(entrada);
	if(strcmp(entrada, "") == 0) strcat(endereco, ", S/N");
	else strcat(strcat(endereco, ", "), entrada);
	
	printf("Complemento:\t");
	fflush(stdin);
	gets(entrada);
	if(!(strcmp(entrada, "") == 0)) strcat(strcat(strcat(endereco, " ("), entrada), ")");
	
	printf("Bairro:\t");
	fflush(stdin);
	gets(entrada);
	strcat(strcat(endereco, " - "), entrada);
	
	printf("Cidade:\t");
	fflush(stdin);
	gets(entrada);
	strcat(strcat(endereco, ", "), entrada);
	
	printf("UF:\t");
	fflush(stdin);
	gets(entrada);
	strcat(strcat(endereco, "/"), entrada);
	
	printf("CEP:\t");
	fflush(stdin);
	gets(cep);
	strcat(strcat(endereco, " - CEP: "), cep);
	
	system("cls");
}

void DataDiagnostico(){	
    time_t agora;
    char datahora[100];

    agora = time(NULL);
    strftime(datahora, sizeof(datahora), "%d/%m/%Y", localtime(&agora));
	strcpy(dataDiagnostico, datahora);
}

void Nascimento(){
	int dd, mm, yy;
	int dd1, mm1, yy1;

	char** str_split( char* str, char delim, int* numSplits ){
	    char** ret;
	    int retLen;
	    char* c;

	    if((str == NULL) || (delim == '\0')){
	        ret = NULL;
	        retLen = -1;
	    } else {
	        retLen = 0;
	        c = str;

	        do{
	            if(*c == delim) retLen++;
				c++;
	        } while (*c != '\0');

	        ret = malloc((retLen + 1) * sizeof(*ret));
	        ret[retLen] = NULL;

	        c = str;
	        retLen = 1;
	        ret[0] = str;

	        do{
	            if (*c == delim){
	                ret[retLen++] = &c[1];
	                *c = '\0';
	            }
	            c++;
	        } while (*c != '\0');
	    }
	    if (numSplits != NULL) *numSplits = retLen;
	    return ret;
	}

	int verificarNumero(char *entrada) {
		int i;
		for (i = 0; entrada[i] != '\0'; i++)if(entrada[i] != '/' && !isdigit(entrada[i])) return 0;
		return 1;
	}

	int ValidaData(char data[9]){
		char* strCpy;
	    char** split;
	    int num;
	    int i;

	    strCpy = malloc(strlen(data) * sizeof(*strCpy));
	    strcpy(strCpy, data);
	    split = str_split(strCpy, '/', &num);

	    dd = atoi(split[0]);
	    mm = atoi(split[1]);
	    yy = atoi(split[2]);

	    if (yy >= 1900 && yy <= 9999) {
	        if (mm >= 1 && mm <= 12) {
	            if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12)) return 1;
	            else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11)) return 1;
	            else if ((dd >= 1 && dd <= 28) && (mm == 2)) return 1;
	            else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0))) return 1;
	            else printf("Data Incorreta: Dia Invalido.\n");
	        } else printf("Data Incorreta: Mes Invalido.\n");
	    } else printf("Data Incorreta: Ano Invalido.\n");
	    return 0;
	}

	void CalculaIdade(){
		dd1 = dd;
		mm1 = mm;
		yy1 = yy;

		ValidaData(dataDiagnostico);

		idade = yy - yy1;
		if(mm1 >= mm && dd1 >= dd) idade++;
	}

	fflush(stdin);
	printf("Entre com o Data do Nascimento do paciente [Dia/Mes/Ano]:\t");
	gets(nasc);
	if(!verificarNumero(nasc)) printf("Data Incorreta");
	if(ValidaData(nasc)) CalculaIdade();
	system("cls");
}

void Telefone(){
	int tentativa = 1;

	void ValidaTelefone(){
		int v = 0;

		do{
			system("CLS");
			fflush(stdin);
			printf("Entre com o Telefone:\t");
			gets(entrada);
			v = 0;

			switch(strlen(entrada)){
				case 11:
					mascara(entrada, "(##) #####-####", 11);
					break;
				case 12:
					memcpy(entrada, entrada+1,sizeof(entrada));
					mascara(entrada, "(##) #####-####", 11);
					break;
				case 10:
					mascara(entrada, "(##) ####-####", 10);
					break;
				case 8:
					mascara(entrada, "####-####  ", 8);
				case 9:
					mascara(entrada, "#####-####  ", 9);
					break;
				default:
					system("CLS");
					puts("Numero Incorreto");
					system("pause");
					v = 1;
					system("CLS");
					break;
			}
		}while(v);

		strcpy(telefone, str);
	}

	do{
		system("CLS");
		fflush(stdin);
		printf("Entrar com o Telefone do paciente?[s/n]:\t");

		switch(getch()){
			case 's':
				ValidaTelefone();
				tentativa = 0;
				break;
			case 'n':system("CLS");
				tentativa = 0;
				break;
			default:system("CLS");
				puts("Opcao invalida!\a");
				system("pause");
				break;
		}
	}while(tentativa);
}

void Email(){
	int ValidaEmail(){
	  int tam=strlen(email);
	  int arroba = 0, ponto = 0, antesPonto = 0, depoisPonto = 0, i;

	  for (i = 0; i < tam; i++) {
	    char c = email[i];
	    if(c == '@') {
	      if (arroba) return 0;
	      arroba = 1;
	      if (i < 3) return 0;
	    }
	    else if (arroba) {
	      if (ponto) depoisPonto++;
	      else if(c == '.') {
	        ponto = 1;
	        if (antesPonto < 3) return 0;
	      } else antesPonto++;
	    }
	  }
	
	  if (i == tam && depoisPonto > 1) {
	  	printf("Valido");
	  	return 1;
	  } else {
	  	printf("Invalido. \n\n");
	  	system("pause");
	  	return 0;
	  }
	}

	int tentativa = 1;
	char opcao;
	
	do{
		system("CLS");
		fflush(stdin);
		printf("Entrar com o E-mail do paciente?[s/n]:\t");

		switch(getch()){
			case 's':
				do{
					system("CLS");
					printf("Entre com o E-mail do paciente:\t");
					gets(email);
					system("cls");
				}while(!ValidaEmail());
				tentativa = 0;
				break;
			case 'n':system("CLS");
				tentativa = 0;
				break;
			default:system("CLS");
				puts("Opcao invalida!\a");
				getch();
				break;
		}
	}while(tentativa);
}

int login(){
	int tentativa = 0;
	char usuario[50];
	char senha[50];	
	
	while(tentativa < 3){
		tentativa++;
		printf("entre com seu usuario:\t");
		fflush(stdin);
		scanf("%s", &usuario);
		printf("entre com sua senha:\t");
		fflush(stdin);
		scanf("%s", &senha);
		
		if(strcmp(usuario, USER) == 0 && strcmp(senha, PASSWORD) == 0) {
			system("cls");
			printf("Conectado");
			fflush(stdin);
			getch();
			system("cls");
			return 1;	
		} else {
			system("cls");
			printf("Usuario ou senha Incorreto - Tentativa %i/3", tentativa);
			fflush(stdin);
			getch();
			system("cls");
			return 0;
		}
	};
}

void Comorbidades(){
	char *comorbidades[28] = {0};
	int cadastro = 0;
	char opcao;

	void CalculaComorbidades(){
		strcpy(comorbidadeDeclaradas, "");
		int i;

		for (i= 0; i< 28; i++){
	    	if (comorbidades[i] != 0){
	    		if (strcmp(comorbidadeDeclaradas, "\n\t- ") == 0){
	    			strcat(comorbidadeDeclaradas, comorbidades[i]);
	    		} else {
	    			strcat(comorbidadeDeclaradas, "\n\t- ");
	    			strcat(comorbidadeDeclaradas, comorbidades[i]);
				}
			}
		}
	}

	void MenuOpcao2(){
		short int interromper = 0;

		while(!interromper) {
			CalculaComorbidades();
			puts("Comorbidades - Pneumopatias cronicas graves:");
			puts("\t1 : Hipertensao Arterial Resistente (HAR);");
			puts("\t2 : Hipertensao arterial estagio 3;");
			puts("\t3 : Hipertensao arterial estagios 1 e 2 com lesao em orgao-alvo;");
			puts("\n\nESC : Voltar.");
			printf("\n\nComorbidades Declaradas:%s", comorbidadeDeclaradas);

			switch(getch()) {
				case '1':
					system("CLS");
					comorbidades[2] = comorbidades[2] ? 0 : "Hipertensao Arterial Resistente (HAR)";
					break;
				case '2':
					system("CLS");
					comorbidades[3] = comorbidades[3] ? 0 : "Hipertensao arterial estagio 3";
					break;
				case '3':
					system("CLS");
					comorbidades[4] = comorbidades[4] ? 0 : "Hipertensao arterial estagios 1 e 2 com lesao em orgao-alvo";
					break;
				case 27:
					system("CLS");
					interromper=1;
					break;
				default:
				system("CLS");
					puts("Opcao invalida!\a");
					system("pause");
					break;
			}

			system("CLS");
		}
	}
	
	void MenuOpcao9(){
		short int interromper = 0;

		while(!interromper) {
			CalculaComorbidades();	
			puts("Comorbidades - Doencas Cardiovasculares:");
			puts("\t1 : Insuficiencia Cardiaca;");
			puts("\t2 : Cor-pulmonale e Hipertensao pulmonar;");
			puts("\t3 : Cardiopatia Hipertensiva;");
			puts("\t4 : Sindromes Coronarianas;");
			puts("\t5 : Valvopatias;");
			puts("\t6 : Miocardiopatias e Pericardiopatias;");
			puts("\t7 : Doencas da Aorta, dos Grandes Vasos e Fistulas arteriovenosas;");
			puts("\t8 : Arritmias cardiacas;");
			puts("\t9 : Cardiopatias congenitas no adulto;");
			puts("\t0 : Proteses valvares e Dispositivos cardiacos implantados;");
			puts("\n\nESC : Voltar.");
			printf("\n\nComorbidades Declaradas:%s", comorbidadeDeclaradas);

			switch(getch()) {
				case '1':
					system("CLS");
					comorbidades[11] = comorbidades[11] ? 0 : "Insuficiencia Cardiaca";
					break;
				case '2':
					system("CLS");
					comorbidades[12] = comorbidades[12] ? 0 : "Cor-pulmonale e Hipertensao pulmonar";
					break;
				case '3':
					system("CLS");
					comorbidades[13] = comorbidades[13] ? 0 : "Cardiopatia Hipertensiva";
					break;
				case '4':
					system("CLS");
					comorbidades[14] = comorbidades[14] ? 0 : "Sindromes Coronarianas";
					break;
				case '5':
					system("CLS");
					comorbidades[15] = comorbidades[15] ? 0 : "Valvopatias";
					break;
				case '6':
					system("CLS");
					comorbidades[16] = comorbidades[16] ? 0 : "Miocardiopatias e Pericardiopatias";
					break;
				case '7':
					system("CLS");
					comorbidades[17] = comorbidades[17] ? 0 : "Doencas da Aorta, dos Grandes Vasos e Fistulas arteriovenosas";
					break;
				case '8':
					system("CLS");
					comorbidades[18] = comorbidades[18] ? 0 : "Arritmias cardiacas";
					break;
				case '9':
					system("CLS");
					comorbidades[19] = comorbidades[19] ? 0 : "Cardiopatias congenitas no adulto";
					break;
				case '0':
					system("CLS");
					comorbidades[20] = comorbidades[20] ? 0 : "Proteses valvares e Dispositivos cardiacos implantados";
					break;
				case 27:
					system("CLS");
					interromper=1;
					break;
				default:
					system("CLS");
					puts("Opcao invalida!\a");
					system("pause");
					break;
			}

			system("CLS");
		}
	}

	void MenuOpcao0(){
		short int interromper=0;

		while(!interromper) {
			CalculaComorbidades();	
			puts("Comorbidades - Doencas neurologicas cronicas:");
			puts("\t1 : Acidente vascular cerebral isquemico ou hemorragico;");
			puts("\t2 : Ataque isquemico transitorio;");
			puts("\t3 : Demencia Vascular;");
			puts("\t4 : Doencas neurologicas que impactam na funcao respiratoria;");
			puts("\t5 : Paralisia Cerebral;");
			puts("\t6 : Esclerose Multipla;");
			puts("\t7 : Doencas hereditarias e degenerativas do sistema nervoso ou muscular;");
			puts("\t8 : Deficiencia neurologica grave;");
			puts("\n\nESC : Sair do programa.");
			printf("\n\nComorbidades Declaradas:%s", comorbidadeDeclaradas);

			switch(getch()) {
				case '1':
					system("CLS");
					comorbidades[21] = comorbidades[21] ? 0 : "Acidente vascular cerebral isquemico ou hemorragico";
					break;
				case '2':
					system("CLS");
					comorbidades[22] = comorbidades[22] ? 0 : "Ataque isquemico transitorio";
					break;
				case '3':
					system("CLS");
					comorbidades[23] = comorbidades[23] ? 0 : "Demencia Vascular";
					break;
				case '4':
					system("CLS");
					comorbidades[24] = comorbidades[24] ? 0 : "Doencas neurologicas que impactam na funcao respiratoria";
					break;
				case '5':
					system("CLS");
					comorbidades[25] = comorbidades[25] ? 0 : "Paralisia Cerebral";
					break;
				case '6':
					system("CLS");
					comorbidades[26] = comorbidades[26] ? 0 : "Esclerose Multipla";
					break;
				case '7':
					system("CLS");
					comorbidades[27] = comorbidades[27] ? 0 : "Doencas hereditarias e degenerativas do sistema nervoso ou muscular";
					break;
				case '8':
					system("CLS");
					comorbidades[28] = comorbidades[28] ? 0 : "Deficiencia neurologica grave";
					break;
				case 27:
					system("CLS");
					interromper=1;
					break;
				default:
					system("CLS");
					puts("Opcao invalida!\a");
					system("pause");
					break;
			}

			system("CLS");
		}
	}
	
	void MenuPrincipal(){
		short int interromper = 0;

		while(!interromper) {
			CalculaComorbidades();
			puts("Comorbidades:");
			puts("\t1 : Diabetes;");
			puts("\t2 : Pneumopatias cronicas graves ->");
			puts("\t3 : Doenca renal cronica;");
			puts("\t4 : Imunocomprometidos;");
			puts("\t5 : Hemoglobinopatias graves: doenca falciforme e talassemia maior;");
			puts("\t6 : Obesidade morbida;");
			puts("\t7 : Sindrome de Down;");
			puts("\t8 : Cirrose hepatica;");
			puts("\t9 : Doencas Cardiovasculares ->");
			puts("\t0 : Doencas neurologicas cronicas ->");
			puts("\n\nESC : Voltar.");
			printf("\n\nComorbidades Declaradas:%s", comorbidadeDeclaradas);

			switch(getch()) {
				case '1':
					system("CLS");
					comorbidades[1] = comorbidades[1] ? 0 : "Diabetes";
					break;
				case '2':
					system("CLS");
					MenuOpcao2();
					break;
				case '3':
					system("CLS");
					comorbidades[5] = comorbidades[5] ? 0 : "Doenca renal cronica";
					break;
				case '4':
					system("CLS");
					comorbidades[6] = comorbidades[6] ? 0 : "Imunocomprometidos";
					break;
				case '5':
					system("CLS");
					comorbidades[7] = comorbidades[7] ? 0 : "Hemoglobinopatias graves: doenca falciforme e talassemia maior";
					break;
				case '6':
					system("CLS");
					comorbidades[8] = comorbidades[8] ? 0 : "Obesidade morbida";
					break;
				case '7':
					system("CLS");
					comorbidades[9] = comorbidades[9] ? 0 : "Sindrome de Down";
					break;
				case '8':
					system("CLS");
					comorbidades[10] = comorbidades[10] ? 0 : "Cirrose hepatica";
					break;
				case '9':
					system("CLS");
					MenuOpcao9();
					break;
				case '0':
					system("CLS");
					MenuOpcao0();
					break;
				case 27:
					system("CLS");
					interromper=1;
					break;
				default:
					system("CLS");
					puts("Opcao invalida!\a");
					system("pause");
					break;
			}

			system("CLS");
		}	
	}

	do{
		system("CLS");
		fflush(stdin);
		printf("Entrar com Comorbidades do paciente?[s/n]:\t");

		switch(getch()){
			case 's':
				comorbidadesA = 1;
				system("CLS");
				MenuPrincipal();
				break;
			case 'n':
				system("CLS");
				comorbidades[0] = "Sem Comorbidades!\a";
				break;
			default:
				system("CLS");
				puts("Opcao invalida!\a");
				system("pause");
				break;
		}

		CalculaComorbidades();
	}while(cadastro);
}
