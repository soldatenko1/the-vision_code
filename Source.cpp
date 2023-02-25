#include <iostream>
#include <fstream>
#include <string>

using namespace std;
string encrypt(string input_text, string key)//������� ���������� 
{
    string output_text = "";//�������� ������ ������
    // ���������� ����� ����� � ����� ������ ��� ����������
    int key_length = key.length();
    int text_length = input_text.length();
    for (int i = 0; i < text_length; i++)
    {
        if (input_text[i] == ' ')//���� � ��������� ������ ���� ������, �� ��������� ������ � ������������� ����� 
        {
            output_text += ' ';
            continue;
        }
        int text_letter_position = input_text[i] - 'a';// ����������� ������� i-�� ������� �������� ������ � ��������
        if (input_text[i] == ',') //���� � ��������� ������ ���� �������, �� ��������� � � ������������� �����
        {
            text_letter_position = 26; // ������� ������� ��� �������
        }
        int key_letter_position = key[i % key_length] - 'a';// ����������� ������� i-�� ������� ����� � ��������, ��� ���� ���� ����������� � ������, ���� ����� ������ ��������� ����� �����
        int encrypted_letter_position = (text_letter_position + key_letter_position) % 27;// ���������� ������� �������������� ������� � ��������
        char encrypted_letter;
        if (encrypted_letter_position == 26)
        {
            encrypted_letter = ','; // ������ ������ ��� ������� �������
        }
        else
        {
            encrypted_letter = encrypted_letter_position + 'a';// �������������� ������� �������������� ������� � ������ � ���������� ��� � �������� ������
        }
        output_text += encrypted_letter;//���������� ������������� ����� � ������
    }
    return output_text;
}

string decrypt(string input_text, string key)//������� ������������ 
{
    string output_text = "";
    int key_length = key.length();
    int text_length = input_text.length();
    for (int i = 0; i < text_length; i++)
    {
        if (input_text[i] == ' ')//���� � ��������� ������ ���� ������, �� ��������� ������ � ������������� ����� 
        {
            output_text += ' ';
            continue;
        }
        int text_letter_position = input_text[i] - 'a';
        if (input_text[i] == ',')
        {
            text_letter_position = 26; // ������ ������� ��� �������
        }
        int key_letter_position = key[i % key_length] - 'a';
        int decrypted_letter_position = (text_letter_position - key_letter_position + 27) % 27;
        char decrypted_letter;
        if (decrypted_letter_position == 26)
        {
            decrypted_letter = ','; // ������ ������ ��� ������� �������
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
