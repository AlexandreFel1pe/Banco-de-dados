#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void database(char nome[50], int idade);

void main(void)
{
    char nome[50];
    char sobrenome[50];
    int idade;
    printf("Cadastre seu usuario\n");
    printf("\nDigite seu nome\n");
    fgets(nome, sizeof(nome), stdin);
    printf("Digite sua idade\n");
    scanf("%d", &idade);
    database(nome, idade);
}

void database(char nome[50], int idade)
{
    // DATABASE CONFIG
    MYSQL *conn;
      MYSQL_RES *res;
      MYSQL_RES *res2;
      MYSQL_ROW row;

      char *server = "localhost";
      char *user = "root";
      //set the password for mysql server here
      char *password = "Vasco123@"; /* set me first */
      char *database = "USUARIO";

      conn = mysql_init(NULL);

      /* Connect to database */
      if (!mysql_real_connect(conn, server,
            user, password, database, 0, NULL, 0)) {
          fprintf(stderr, "%s\n", mysql_error(conn));
          exit(1);
      }

      // MOSTRAR TABLES
      /* send SQL query */
      if (mysql_query(conn, "show tables")) {
          fprintf(stderr, "%s\n", mysql_error(conn));
          exit(1);
      }

      res = mysql_use_result(conn);

      /* output table name */
      printf("MySQL Tables in mysql database:\n");
      while ((row = mysql_fetch_row(res)) != NULL)
          printf("%s \n", row[0]);

      // INSERT QUERY

      char insert_nome[2000];

      sprintf(insert_nome, "insert into USUARIOS (NOME, IDADE) values ('%s', '%d')", nome, idade);
      if (mysql_query(conn, insert_nome)) {
          fprintf(stderr, "%s\n", mysql_error(conn));
          exit(1);
      }

      // SELECT QUERY

      /* send SQL query */
      if (mysql_query(conn, "select * from USUARIOS")) {
          fprintf(stderr, "%s\n", mysql_error(conn));
          exit(1);
      }

      res = mysql_use_result(conn);

      /* output SELECT */
      printf("MySQL Tables in mysql database:\n");
      while ((row = mysql_fetch_row(res)) != NULL)
          printf("%s""%s", row[0], row[1]);

      /* close connection */
      mysql_free_result(res);
      mysql_close(conn);
}
