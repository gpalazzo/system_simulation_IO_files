#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *pont_login, *pont_cadastro, *pont_calcIMC;
void Login (char resposta);
void Menu ();
void CadastroPaciente ();
void CalculoIMC ();
void MostraPacientes ();
int Contar ();
void MostraIMC ();
void MostraDiabeticos ();
char resposta;

struct dados {
	char nome_paciente[30], data_nasc[10], sexo;
	float glicemia, colesterol, peso, altura, imc;
};

struct dados dados_pacientes;

main () {
	
	printf("**********************************************\n");
	printf("Bem-vindo ao Sistema da Clinica de Nutrologia\n");
	printf("**********************************************\n\n");

	if ((pont_login = fopen ("Login.txt", "r")) == NULL) {	
		printf("Pelo que vi, voce ainda nao possui cadastro. Voce sera redirecionado para faze-lo.\n");
		system("pause");
		fclose(pont_login);
		resposta = 'N';
		Login (resposta);
	}
		
	else {
		resposta = 'S';
		Login (resposta);
	}
}

void Login (char resposta) {
	char usuario_cadastro[30], usuario_informado[30], nome[30];
	int senha_cadastro, senha_informada, opcao;

	if (resposta == 'S') {
		
		pont_login = fopen ("Login.txt", "r");
		
		printf("\nInforme seu nome de usuario: \n");
		fflush(stdin);
		gets(usuario_informado);

		printf("Informe sua senha (apenas numeros): \n");
		scanf("%d", &senha_informada);

		while (fscanf(pont_login, "%s %d", usuario_cadastro, &senha_cadastro) != EOF) {

			if ((strcmp(usuario_cadastro, usuario_informado) == 0) && (senha_cadastro == senha_informada)) {
				printf("Login efetuado com sucesso\n\nVoce sera redirecionado para o Menu\n\n");
				system("pause");
				fclose(pont_login);
				system("cls");
				Menu ();
			}
			
			else {
				
				printf("\nUsuario e/ou Senha invalidos.\nDeseja inseri-lo novamente?\n");
				printf("1 - Sim\n");
				printf("2 - Nao / Sair do Sistema\n");
				scanf("%d", &opcao);
				
				switch (opcao) {
					
					case 1: {
						resposta = 'S';
						Login (resposta);
					}
					
					case 2: exit(0);
					
					default: {
						printf("Resposta invalida.\n");
						resposta = 'S';
						Login (resposta);
					}
				}
			}
		}
	}

	else {
		pont_login = fopen ("Login.txt", "w");

		printf("\nInforme seu nome: \n");
		fflush(stdin);
		gets(nome);

		printf("\nOla, bem-vindo %s. Estamos na tela de cadastro.\n\n", nome);

		printf("Informe um nome de usuario: \n");
		fflush(stdin);
		gets(usuario_cadastro);

		printf("Informe uma senha (apenas numeros): \n");
		scanf("%d", &senha_cadastro);

		fprintf(pont_login, "%s %d", usuario_cadastro, senha_cadastro);

		printf("Cadastro efetuado com sucesso. Agora iremos para a tela de login.\n\n");
		system("pause");
		fclose (pont_login);
		resposta = 'S';
		Login (resposta);
	}
}

void Menu () {

	int opcao;
	system ("cls");

	printf("*****************\n");
	printf("Bem-vindo ao Menu\n");
	printf("*****************\n\n");
	printf("1 - Cadastrar Paciente\n");
	printf("2 - Gerar Valor do IMC\n");
	printf("3 - Mostrar Pacientes Cadastrados\n");
	printf("4 - Mostrar Resultados do IMC\n");
	printf("5 - Mostrar Pacientes Diabeticos\n");
	printf("6 - Sair do Sistema\n\n");
	printf("Qual opcao voce deseja?\n");
	scanf("%d", &opcao);
	
	switch (opcao) {
		
		case 1: {
			CadastroPaciente ();
			Menu ();
		}

		case 2: {
			CalculoIMC ();
			Menu ();
		}
		
		case 3: {
			MostraPacientes ();
			Menu ();
		}

		case 4: {
			MostraIMC ();
			Menu ();
		}

		case 5: {
			MostraDiabeticos ();
			Menu ();
		}

		case 6: exit(0);

		default: {

			printf("Resposta invalida.\nVoce sera redirecionado para o Menu\n");
			system ("pause");
			Menu ();
		}
	}
}

void CadastroPaciente () {

	pont_cadastro = fopen ("Cadastro_Pacientes.txt", "a");

	do {
		
		system("cls");
		strcpy (dados_pacientes.nome_paciente, "                              ");
		strcpy (dados_pacientes.data_nasc, "          ");
		
		printf("\nInforme o nome do paciente: \n");
		fflush(stdin);
		gets(dados_pacientes.nome_paciente);

		printf("Informe sua data de nascimento: <dd/mm/aaaa>\n");
		fflush(stdin);
		gets(dados_pacientes.data_nasc);

		printf("Informe o valor da sua glicemia: \n");
		scanf("%f", &dados_pacientes.glicemia);

		printf("Informe o valor do seu colesterol: \n");
		scanf("%f", &dados_pacientes.colesterol);

		printf("Informe seu peso em kg: \n");
		scanf("%f", &dados_pacientes.peso);

		printf("Informe sua altura em m: \n");
		scanf("%f", &dados_pacientes.altura);
		
		printf("Informe seu sexo: <M/F>\n");
		dados_pacientes.sexo = getche();

		dados_pacientes.imc = dados_pacientes.peso / (dados_pacientes.altura * dados_pacientes.altura);

		fwrite (&dados_pacientes, sizeof(dados_pacientes), 1, pont_cadastro);

		printf("\nDeseja cadastrar outro paciente? <s/n>\n");
		resposta = getche();
	} while (toupper(resposta) == 'S');
	
	fclose(pont_cadastro);
}

void CalculoIMC () {

	if ((pont_cadastro = fopen ("Cadastro_Pacientes.txt", "r")) == NULL) {

		printf("Erro ao abrir arquivo de Pacientes Cadastrados.\n");
		printf("Voce deseja cadastrar algum paciente? <s/n>\n");
		resposta = getche();

		if (toupper(resposta) == 'S') {
			CadastroPaciente ();
		}

		else {
			printf("Voce sera redirecionado para o Menu\n");
			system ("pause");
			Menu ();
		}
	}

	pont_calcIMC = fopen ("CalculoIMC.txt", "w");
	
	while ((fread(&dados_pacientes, sizeof(dados_pacientes), 1, pont_cadastro)) == 1) {
		fprintf(pont_calcIMC, "%s %f\n", dados_pacientes.nome_paciente, dados_pacientes.imc);
	}

	fclose (pont_cadastro);
	fclose (pont_calcIMC);
	printf ("Os calculos de IMC foram realizados com sucesso.\nVoce sera redirecionado para o Menu\n");
	system ("pause");
}

void MostraPacientes () {

	if ((pont_cadastro = fopen ("Cadastro_Pacientes.txt", "r")) == NULL) {

		printf("Erro ao abrir arquivo de Pacientes Cadastrados.\n");
		printf("Voce deseja cadastrar algum paciente? <s/n>\n");
		resposta = getche();

		if (toupper(resposta) == 'S') {
			CadastroPaciente ();
		}

		else {
			printf("Voce sera redirecionado para o Menu\n");
			system ("pause");
			Menu ();
		}
	}

	else {

		while (fread(&dados_pacientes, sizeof (dados_pacientes), 1, pont_cadastro) == 1) {
			
			printf("\nNome do Paciente: %s\nData de Nascimento: %s\nValor Glicemia: %.2f\nValor Colesterol: %.2f\nPeso: %.2f\nAltura: %.2f\nSexo: %c\n", dados_pacientes.nome_paciente, dados_pacientes.data_nasc, dados_pacientes.glicemia, dados_pacientes.colesterol, dados_pacientes.peso, dados_pacientes.altura, dados_pacientes.sexo);
		}
	}
	
	fclose (pont_cadastro);
	system("pause");
	printf("\n\nVoce sera redirecionado para o Menu\n");
	system("pause");
}

int Contar () {

	int numreg = 0;
	pont_cadastro = fopen ("Cadastro_Pacientes.txt", "r");

	while ((fread(&dados_pacientes, sizeof(dados_pacientes), 1, pont_cadastro)) == 1) {
		numreg++;
	}

	fclose (pont_cadastro);
	return numreg;
}

void MostraIMC () {

	int max = Contar ();
	int i = 0, j = 0;
	struct dados auxiliar;
	struct dados ordenacao[max];
	
	if ((pont_calcIMC = fopen ("CalculoIMC.txt", "r")) == NULL) {

		printf("Erro ao abrir arquivo de IMC.\n");
		printf("Voce deseja cadastrar algum paciente para calcular o IMC? <s/n>\n");
		resposta = getche();

		if (toupper(resposta) == 'S') {
			CadastroPaciente ();
		}

		else {
			printf("Voce sera redirecionado para o Menu\n");
			system ("pause");
			Menu ();
		}
	}

	else {
		
		while ((fscanf(pont_calcIMC, "%s %f", dados_pacientes.nome_paciente, &dados_pacientes.imc)) != EOF) {
			
			strcpy (ordenacao[i].nome_paciente, dados_pacientes.nome_paciente);
			ordenacao[i].imc = dados_pacientes.imc;

			i++;
		}

		for (i = 0; i < max; i++) {

			for (j = i+1; j < max; j++) {

				if (strcmp (ordenacao[i].nome_paciente, ordenacao[j].nome_paciente) > 0) {

					auxiliar = ordenacao[i];
					ordenacao[i] = ordenacao[j];
					ordenacao[j] = auxiliar;
				}
			}
		}
		
		for (i = 0; i < max; i++) {

			printf("Nome Paciente: %s\nValor IMC: %.2f\n\n", ordenacao[i].nome_paciente, ordenacao[i].imc);
		}
	}

	fclose (pont_calcIMC);
	system("pause");
	printf("Voce sera redirecionado para o Menu\n");
	system("pause");
}

void MostraDiabeticos () {
	
	int max = Contar ();

	if ((pont_cadastro = fopen ("Cadastro_Pacientes.txt", "r")) == NULL) {

		printf("Erro ao abrir arquivo de Pacientes Cadastrados.\n");
		printf("Voce deseja cadastrar algum paciente? <s/n>\n");
		resposta = getche();

		if (toupper(resposta) == 'S') {
			CadastroPaciente ();
		}

		else {
			printf("Voce sera redirecionado para o Menu\n");
			system ("pause");
			Menu ();
		}
	}

	else {

		int contador = 0, i = 0;
		struct dados diabeticos[max];
		
		while ((fread(&dados_pacientes, sizeof (dados_pacientes), 1, pont_cadastro)) == 1) {
			diabeticos[i] = dados_pacientes;

			if (diabeticos[i].glicemia > 120) {
				contador++;
			}

			i++;
		}

		if (contador == 0) {
			printf("Nao ha pacientes diabeticos.\n");
		}

		else {

			printf("Os pacientes diabeticos sao: \n");
			for (i = 0; i < max; i++) {

				if (diabeticos[i].glicemia > 120) {
					printf("%s\n", diabeticos[i].nome_paciente);
				}
			}
		}
	}

	fclose (pont_cadastro);
	system("pause");
	printf("\nVoce sera redirecionado para o Menu\n");
	system("pause");
}