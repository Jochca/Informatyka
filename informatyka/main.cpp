#include <iostream>

#include <mysql.h>

#include <mysqld_error.h>

#include <windows.h>

#include <stdio.h>

using namespace std;

char HOST[] = "localhost";
char USER[] = "root";
char PASS[] = "\0";

void slow_print(const std::string & str, int delay_time) {
  for (size_t i = 0; i != str.size(); ++i) {
    cout << str[i];
    Sleep(delay_time);
  }
}

int main(int argc, char ** argv) {

  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

  MYSQL * obj;
  MYSQL_RES * res;
  MYSQL_ROW row;

  string Name;
  string Email;
  string Password;
  string ID;

  bool ProgramIsOpened = true;
  int answer;

  char * consult;
  char * sentence;
  string sentence_aux;

  slow_print("Connecting to database...", 30);
  cout << endl << endl;
  Sleep(500);

  if (!(obj = mysql_init(0))) {
    cout << "ERROR: UNKNOWN_ERROR" << endl;
  } else {
    if (!mysql_real_connect(obj, HOST, USER, PASS, "informatyka", 3306, NULL, 0)) {
      cout << "ERROR: Could not connect to database" << endl;
      cout << mysql_error(obj) << endl;
    } else {
      SetConsoleTextAttribute(h, 10);
      slow_print("Connection succesfull!", 30);
      for (int i = 0; i < 4; i++) {
        cout << endl;
        Sleep(200);
      }
      system("cls");

      for (;;) {

        SetConsoleTextAttribute(h, 15);
        slow_print("Authorization", 20);
        cout << endl << endl;
        SetConsoleTextAttribute(h, 7);
        slow_print("Login: ", 20);
        cin >> Name;
        cout << endl;
        SetConsoleTextAttribute(h, 7);
        slow_print("Password: ", 20);
        cin >> Password;

        system("cls");

        for (int i = 0; i < 4; i++) {
          cout << endl;
          Sleep(200);
        }

        string sql = "SELECT * FROM `users` WHERE `name` = '" + Name + "' AND `password` = '" + Password + "'";

        mysql_query(obj, sql.c_str());
        res = mysql_store_result(obj);

        if (!mysql_fetch_row(res)) {

          SetConsoleTextAttribute(h, 12);
          slow_print("Access Denied", 30);
          Sleep(200);
          system("cls");

          SetConsoleTextAttribute(h, 15);

          continue;
        }

        SetConsoleTextAttribute(h, 10);
        slow_print("Access Granted", 30);
        Sleep(200);
        system("cls");

        SetConsoleTextAttribute(h, 15);

        break;
      }

      for (;;) {
        mysql_query(obj, "SELECT * FROM users");

        res = mysql_store_result(obj);
        int num_fields = mysql_num_fields(res);

        while ((row = mysql_fetch_row(res))) {
          if (row[0] != NULL) {
            cout << row[0] << ".   ";
            cout << "Name: " << row[1] << "   ";
            cout << "Password: " << row[2] << "   ";
            cout << "Email: " << row[3] << endl;
          } else
            cout << "NULL" << endl;
        }

        int choice;
        cout << endl << "1. Add new    2. Delete    3. Update" << endl;
        cin >> choice;

        if (choice == 1) {
          slow_print("Name: ", 30);
          cin >> Name;
          slow_print("Email: ", 30);
          cin >> Email;
          slow_print("Password: ", 30);
          cin >> Password;

          string sql = "INSERT INTO `users` (`ID`, `name`, `email`, `password`) VALUES (NULL, '" + Name + "', '" + Email + "', '" + Password + "')";

          mysql_query(obj, sql.c_str());

          system("cls");
        } else if (choice == 2) {
          slow_print("Insert id of element you want to delete: ", 10);
          cin >> ID;

          string sql = "DELETE FROM `users` WHERE `ID` = " + ID;

          mysql_query(obj, sql.c_str());

          system("cls");
        } else if (choice == 3) {
          slow_print("Insert id of element you want to update: ", 10);
          cin >> ID;
          slow_print("Name: ", 30);
          cin >> Name;
          slow_print("Email: ", 30);
          cin >> Email;
          slow_print("Password: ", 30);
          cin >> Password;

          string sql = "UPDATE `users` SET `name` = '" + Name + "', `email` = '" + Email + "', `password` = '" + Password + "' WHERE `users`.`ID` = " + ID + ";";

          mysql_query(obj, sql.c_str());

          system("cls");
        }
      }
    }
  }

  return 0;

}
