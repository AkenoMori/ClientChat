#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <limits>
#pragma warning(disable: 4996)

SOCKET Connection;

void ClientHandler() {
    char msg[256];
    char log[256];
    while (true) {
        recv(Connection, log, sizeof(log), 0);
        recv(Connection, msg, sizeof(msg), 0);
        std::cout << msg << ":" << log << std::endl;
    }
}
void regist() {
    char log1[256];
    char pass[256];
    std::string login_check = "login.txt";
    std::string password_check = "password.txt";
    std::fstream login;
    std::fstream password;
    login.open(login_check, std::fstream::in | std::fstream::out | std::fstream::app);
    password.open(password_check, std::fstream::in | std::fstream::out | std::fstream::app);
    if (!login.is_open() || !password.is_open()) {
        std::cout << "Ошибка открытия файла." << std::endl;
    }
    else {
        std::cout << "Регистрация|Введите логин:" << std::endl;
        std::cin >> log1;
        login << log1 << std::endl;
        login.close();
        std::cout << "Регистрация|Введите пароль:" << std::endl;
        std::cin >> pass;
        password << pass << std::endl;
        password.close();

        send(Connection, log1, sizeof(log1), 0);
    }
}
int chat() {
    char msg1[256];
    std::cin.ignore();
    while (true) {
        std::cout << "Введите сообщение:" << std::endl;
        //std::cin >> msg1;
        std::cin.getline(msg1, sizeof(msg1));
        

        //std::cin.ignore();
        send(Connection, msg1, sizeof(msg1), 0);
    }
}



void login() {
    char log1[256];
    char pass[256];
    std::string login_check = "login.txt";
    std::string password_check = "password.txt";
    std::fstream login;
    std::fstream password;
    std::string log2, pass2;
    login.open(login_check, std::fstream::in | std::fstream::out | std::fstream::app);
    password.open(password_check, std::fstream::in | std::fstream::out | std::fstream::app);
    if (!login.is_open() || !password.is_open()) {
        std::cout << "Ошибка открытия файла." << std::endl;
    }
    else {
        while (!login.eof())
        {
            login >> log2;
        }
        while (!password.eof())
        {
            password >> pass2;
        }
        std::cout << "Авторизация|Введите логин:" << std::endl;
        std::cin >> log1;
        std::cout << "Авторизация|Введите пароль:" << std::endl;
        std::cin >> pass;
        send(Connection, log1, sizeof(log1), 0);
        if (log1 != log2 && pass != pass2) {
            std::cout << "Логин или пароль введены неверно!" << std::endl;
            system("pause");
        }
        else
            std::cout << "С возвращением! " << log1 << std::endl;
            
       
    }

}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "Error: failed connect to server.\n";
        return 1;
    }
    std::cout << "Connected!\n";

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);
    int select;
    std::cout << "1 - Авторизация | 2 - Регистрация" << std::endl;
    std::cin >> select;
  

    if (select == 1)
        login();
    else if (select == 2)
        regist();
    else {
        std::cout << "Ошибка ввода:Выберите 1 или 2" << std::endl;
        system("pause");
    }
    chat();

    return 0;
}