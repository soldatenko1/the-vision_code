#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string encrypt(string input_text, string key)//функция шифрования 
{
    string output_text = "";//создание пустой строки
    // определяем длину ключа и длину текста для шифрования
    int key_length = key.length();
    int text_length = input_text.length();
    for (int i = 0; i < text_length; i++)
    {
        if (input_text[i] == ' ')//если в введенном тексте есть пробел, то добавляем пробел в зашифрованный текст 
        {
            output_text += ' ';
            continue;
        }
        int text_letter_position = input_text[i] - 'a';// определение позиции i-го символа входного текста в алфавите
        if (input_text[i] == ',') //если в введенном тексте есть запятая, то добавляем её в зашифрованный текст
        {
            text_letter_position = 26; // задание позиции для запятой
        }
        int key_letter_position = key[i % key_length] - 'a';// определение позиции i-го символа ключа в алфавите, при этом ключ повторяется с начала, если длина текста превышает длину ключа
        int encrypted_letter_position = (text_letter_position + key_letter_position) % 27;// вычисление позиции зашифрованного символа в алфавите
        char encrypted_letter;
        if (encrypted_letter_position == 26)
        {
            encrypted_letter = ','; // задаем символ для позиции запятой
        }
        else
        {
            encrypted_letter = encrypted_letter_position + 'a';// преобразование позиции зашифрованного символа в символ и добавление его в выходную строку
        }
        output_text += encrypted_letter;//добавление зашифрованный текст в строку
    }
    return output_text;
}

string decrypt(string input_text, string key)//функция дешифрования 
{
    string output_text = "";
    int key_length = key.length();
    int text_length = input_text.length();
    for (int i = 0; i < text_length; i++)
    {
        if (input_text[i] == ' ')//если в введенном тексте есть пробел, то добавляем пробел в зашифрованный текст 
        {
            output_text += ' ';
            continue;
        }
        int text_letter_position = input_text[i] - 'a';
        if (input_text[i] == ',')
        {
            text_letter_position = 26; // задаем позицию для запятой
        }
        int key_letter_position = key[i % key_length] - 'a';
        int decrypted_letter_position = (text_letter_position - key_letter_position + 27) % 27;
        char decrypted_letter;
        if (decrypted_letter_position == 26)
        {
            decrypted_letter = ','; // задаем символ для позиции запятой
        }
        else
        {
            decrypted_letter = decrypted_letter_position + 'a';
        }
        output_text += decrypted_letter;
    }
    return output_text;
}

int main()
{
    int mode, mode_1;

    string input_text;
    string output_text;
    string key;

    cout << "Select the operating mode of the program: " << endl;
    cout << "1 - encryption" << endl;
    cout << "2 - decryption" << endl;
    cin >> mode;

    cout << "Select the information input/output mode: " << endl;
    cout << "1 - input/output to the console" << endl;
    cout << "2 - input/output to a file" << endl;
    cin >> mode_1;
    if (mode_1 == 2)
    {
        string input_filename;
        string output_filename;

        cout << "Enter the name of the input file: ";
        cin >> input_filename;
        cout << "Enter the name of the output file: ";
        cin >> output_filename;

        ifstream input_file(input_filename);
        ofstream output_file(output_filename);
        if (mode == 1)
        {
            cout << "Enter the encryption key: ";
            cin >> key;
            string line;
            while (getline(input_file, line))
            {
                output_file << encrypt(line, key) << endl;
            }
        }
        else
        {
            cout << "Enter the decryption key: ";
            cin >> key;
            string line;
            while (getline(input_file, line))
            {
                output_file << decrypt(line, key) << endl;
            }

        }
        input_file.close();
        output_file.close();
    }
    else
    {
        if (mode == 1)
        {
            cout << "Enter the encryption key: ";
            cin >> key;
            cout << "Enter the encryption text: ";
            getline(cin, input_text);
            getline(cin, input_text);
            output_text = encrypt(input_text, key);
            cout << "Encrypted text: " << output_text << endl;
        }
        else
        {
            cout << "Enter the decryption key: ";
            cin >> key;
            cout << "Enter the decryption text: ";
            getline(cin, input_text);
            getline(cin, input_text);
            output_text = decrypt(input_text, key);
            cout << "Decrypted text: " << output_text << endl;
        }
    }
    return 0;
}
