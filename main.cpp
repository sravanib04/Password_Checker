/**------------------------------------------
    Password Checker
    Checks if all the seven requirements for a password are met and returns if
    the password is accepted or rejected
    System: Windows 11 & C++
    Author: Sravani Bhamidipaty
 ---------------------------------------------**/
#include <iostream> // Used for cin and cout
#include <string> // Used for string variables
#include <vector> // Used for compiling vectors
#include <fstream> // Used to read in information from files
using namespace std;

const string rule_msg_1 = "The selected password must be at least eight characters long.";
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";

//The binarySearch function takes in the leaked passwords file and checks if the input password contains a leaked password
//Input:
//  data: the leaked password file that is stored in a string vector
//  passwordLowerCase: password that is converted into all lower case letters 
//  low: the first element index of the file (0)
//  high: the last element index of the file
//Output:
//  Returns mid if the data value of the lower case password input is a leaked password
//  Returns 0 if the the lower case password input is not a leaked password
int binarySearch(vector <string> data, string& passwordLowerCase, int low, int high)
{
  int mid = 0; //Middle of the data set
  int returnValue = 0;
  while(low <= high)
  {
    mid = (low+high)/2; //Sets the middle value of the vector data. This keeps changing as we go through the vector and compare it with the password inputted
    if (data[mid] == passwordLowerCase)
    {
      returnValue = 1; 
      return mid; //The password is a leaked password, so we return mid
    }
    else if (data[mid] < passwordLowerCase) //Checks if the value of data at mid is greater than or less than the password in lower case inputted
    {
      low = mid + 1; //Increases low and then recaluculates mid to do the binary search again
    }
    else
    {
      high = mid - 1; //Decreases high and then recalculates mid to do the binary search again
    }
  }
  return returnValue; //Returns 0 if password inputted is not in the leaked password file
}
//The PasswordLeak function checks for rule 6: if the password inputted is a leaked password
//Input:
//  leaked_password_file: the leaked password file given
//  password: password that is inputted by the user
//Output:
//  Returns 1 if the password is a leaked password
//  Returns 0 if the password is not a leaked password
int PasswordLeak(string leaked_password_file, string password)
{
  ifstream leakedPasswordsFile; //Inputting the file stream data for the file leakedPasswordsFile
  vector <string> storeData;
  string storeDataElement;
  string passwordLowerCase;
  long long int leakedPasswordsFileSize;
  long long int returnValue;
  int low = 0;
  int passwordLeakChecker = 0;
  string modifiedString;
  leakedPasswordsFile.open("alleged-gmail-passwords.txt"); //Opens the file leakedPasswordFile
  if(!leakedPasswordsFile.is_open()) //If the file is not open, we print that we could not open the file
  {
    cout << "Could not open file alleged_gmail_passwords.txt." << endl;
  }
  else
  {
    //While the computer is not reading the end of the file, we get the line at the element the computer is reading and then if there are no punctuations or symbols then it added to the vector storeData, if not we remove the symbols and add it to the vector store data
    while(!leakedPasswordsFile.eof())
    {
      getline(leakedPasswordsFile, storeDataElement);
      for (int i = 0; i < storeDataElement.size(); i++)
      {
        if (ispunct(storeDataElement[i]) != 0)
        {
          continue;
        }
        else
        {
          modifiedString = modifiedString + storeDataElement[i];
        }
      }
      storeData.push_back(modifiedString);
      modifiedString = "";
    }
  } 
  //For the string password that starts at element 0 and continues until but not including password size, if the password at i is a letter or a number, then it is added to another string passwordLowerCase
  for(int i=0; i<password.size(); i++)
  {
    password.at(i) = tolower(password.at(i));
    if(isalpha(password.at(i)) || isdigit(password.at(i)))
    {
      passwordLowerCase.push_back(password.at(i));
    }
  }
  leakedPasswordsFileSize = storeData.size() - 1; //Gets the size of the vector, which is the same as the size of the leakedPasswordsFile
  returnValue = binarySearch(storeData, passwordLowerCase, low, leakedPasswordsFileSize); //Get the value that is returned from the binarySearch function if the returnValue is greater than or equal to 1 then the password inputted is a leaked password
  if(returnValue >= 1)
  {
    passwordLeakChecker = 1;
  }
  return passwordLeakChecker;
}
//The EnglishWords function checks for rule 7: if the password inputted contains an English word
////Input:
//  english_word_file: the english words file given
//  password: password that is inputted by the user
//Output:
//  Returns 1 if the password contains an English word
//  Returns 0 if the password does not contain an English word
int EnglishWords(string english_word_file, string password)
{
    ifstream englishWordsFile; //Inputting the file stream data for the file englishWordsFile
    vector <string> storeData;
    string storeDataElement;
    string passwordLowerCase;
    int englishWordChecker = 0;
    englishWordsFile.open("words_5.txt"); //Opens the file englishWordsFile
    if(!englishWordsFile.is_open())
    {
        cout << "Could not open file words_5.txt." << endl; //If the file is not open, we print that we could not open the file
    }
    else{
      //While the computer is not reading the end of the file, we get the line at the element the computer is reading and then we add it to the vector storeData
        while(!englishWordsFile.eof())
        {
            getline(englishWordsFile, storeDataElement);
            storeData.push_back(storeDataElement);
            storeDataElement = "";
        }
    }
    //For the string password that starts at element 0 and continues until but not including password size, if the password at i is a letter, then it is added to another string passwordLowerCase
    for(int i=0; i<password.size() - 1; i++)
    {
        password.at(i) = tolower(password.at(i));
        if(isalpha(password.at(i)))
        {
            passwordLowerCase.push_back(password.at(i));
        }
    }
    //For the storeData vector that starts at element 0 and continues until but not including storeData's size. If the storeData at i is equal to the lower case password then the password contains an english word
    for(int i = 0; i<storeData.size(); i++)
    {
        if(passwordLowerCase == storeData[i])
        {
            englishWordChecker = 1;
        }
    }
  return englishWordChecker;
}
//The run function checks all the rules from 1 to 5, calls rule 6 from the PasswordLeak function, and calls rule 7 from the EnglishWords function
//Input:
//  leaked_password_file: the leaked password file given
//  english_word_file: the english words file given
//Output:
//  None
void run(string leaked_password_file, string english_word_file)
{
  string password;
  bool passwordValidity = true;
  int countUpperCase = 0;
  int countLowerCase = 0;
  int countDigit = 0;
  int countSpecialCharacters = 0;
  cout << "Enter password: "; //Prompts the user to enter password
  cin >> password; //Reads in user input
  vector <char> specialCharacters = {'@','!', '#', '^','&','$'};
  bool rules1to5Checker = false;
  bool rule7Checker = false;
  int englishWordsCheck = 0;
  //If password is less than 8 characters then rule 1 fails, so rule 1 message is printed passwordValidity variable is set to false because it is later used to print if the password is accepted or rejected
  if(password.size() < 8)
  {
    cout << rule_msg_1 << endl;
    passwordValidity = false;
  }
  //A for loop to check through the user entered password and count if each of the conditions from rules 2 to 5 are found
  for(int i=0; i<password.size(); i++)
  {
    //If the password contains an upper case letter then countUpperCase increments by 1.
    if(isupper(password.at(i)))
    {
      countUpperCase++;
    }
    //If the password contains a lower case letter then countLowerCase increments by 1.
    else if(islower(password.at(i)))
    {
      countLowerCase++;
    }
    //If the password contains a number then countDigit increments by 1.
    if(isdigit(password.at(i)))
    {
      countDigit++;
    }
    //If the password contains any of the special characters that are declared in the vector special characters countSpecialCharacters increments by 1.
    for(int j=0; j<specialCharacters.size(); j++)
    {
      if(password.at(i) == specialCharacters.at(j))
      {
        countSpecialCharacters++;
      }
    }
  }
  //If password does not contain any upper case letters rule 2 fails, so rule 2 message is printed passwordValidity variable is set to false because it is later used to print if the password is accepted or rejected
  if(countUpperCase == 0)
  {
    cout << rule_msg_2 << endl;
    passwordValidity = false;
  }
  //If password does not contain any lower case letters rule 3 fails, so rule 3 message is printed passwordValidity variable is set to false because it is later used to print if the password is accepted or rejected
  if(countLowerCase == 0)
  {
    cout << rule_msg_3 << endl;
    passwordValidity = false;
  }
  //If password does not contain any numbers rule 4 fails, so rule 4 message is printed passwordValidity variable is set to false because it is later used to print if the password is accepted or rejected
  if(countDigit == 0)
  {
    cout << rule_msg_4 << endl;
    passwordValidity = false;
  }
  //If password does not contain any special characters rule 5 fails, so rule 5 message is printed passwordValidity variable is set to false because it is later used to print if the password is accepted or rejected
  if(countSpecialCharacters == 0)
  {
    cout << rule_msg_5 << endl;
    passwordValidity = false;
  }
  //Checks if all the statements from 1 to 5 are passed rules1to5Checker variable is set to true because it is later used to print if the password is accepted or rejected
  if(countUpperCase == 0 && countLowerCase == 0 && countDigit == 0 && countSpecialCharacters == 0)
  {
    rules1to5Checker = true;
  }
  //If passwordValidity still holds true then we check rule 6
  if(passwordValidity)   
  {    
    //If PasswordLeak function returns 1 then the user inputted password is leaked and rule message 6 is printed passwordValidity variable is set to false because it is later used to print if the password is accepted or rejected
    if(PasswordLeak(leaked_password_file, password) == 1)
    {
      cout << rule_msg_6 << endl;
      passwordValidity = false;
    }
    englishWordsCheck = EnglishWords(english_word_file, password);
    //If EnglishWordsCheck returned from the EnglishWords function returns 1 then the user inputted password contains an English word and rule message 7 is printed. rule7Checker stays false if the password contains an English word and set to true if the password does not contain an English word
    if(englishWordsCheck == 1)
    {
      cout << rule_msg_7 << endl;
    }
    else
    {
      rule7Checker = true;
    }
  }
  //If rules1to5Checker, passwordValidity, or rule7Checker is false then the password does not meet all the rules from 1 to 7 and the password is rejected
  if(rules1to5Checker || !passwordValidity ||!rule7Checker)
  {
    cout << "Password rejected!" << endl;
  }
  //Else all the rules from 1 to 7 are passed and the password is accepted
  else
  {
    cout << "Password accepted!" << endl;
  }
}
int main() {
    /** Change the address of the files appropriatly based on your local machine.
     * This main function will be replaced during testing. Do not add any line of code to the main function
     **/
    string leaked_password_file = "alleged-gmail-passwords.txt"; //change this based on the location of the file on your machine
    string english_word_file = "words_5.txt"; //change this based on the location of the file on your machine
    run(leaked_password_file, english_word_file);
    return 0;
}