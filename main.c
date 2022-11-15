#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void database(char nome[50], char sobrenome[50], char idade[3]);

void main(void)
{
    char nome[50];
    char sobrenome[50];
    char idade[3];
    printf("Cadastre seu usuario\n");
    printf("\nDigite seu nome\n");
    fgets(nome, sizeof(nome), stdin);
    printf("Digite seu sobrenome\n");
    fgets(sobrenome, sizeof(sobrenome), stdin);
    printf("Digite sua idade\n");
    fgets(idade, sizeof(idade), stdin);
    database(nome, sobrenome, idade);
}

void database(char nome[50], char sobrenome[50], char idade[3])
{
  MYSQL *conn = mysql_init(NULL);

  if (mysql_real_connect(conn, "localhost", "root", "Vasco123@",
          NULL, 0, NULL, 0) == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(conn));
      mysql_close(conn);
      exit(1);
  }


  if (mysql_query(conn, "USE USUARIO"))
  {
      fprintf(stderr, "%s\n", mysql_error(conn));
      mysql_close(conn);
      exit(1);
  }

  char sql_statement[2048];

  //char nome[20] = "JOKO";

  sprintf(sql_statement, "INSERT INTO USUARIOS(nome, sobrenome, idade) VALUES('%s','%s','%s')", nome, sobrenome, idade);

  if (mysql_query(conn, sql_statement))
  {
      fprintf(stderr, "%s\n", mysql_error(conn));
      mysql_close(conn);
      exit(1);
  } else {printf("\nCadastrado com sucesso\n");}

  mysql_close(conn);
  exit(0);
}
