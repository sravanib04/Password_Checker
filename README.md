# Password_Checker
Prompts the user to enter a new password until all the seven rules for a password are met

## What it does
There are seven rules that need to be met for a password to be accepted. These rules are the following:
1: The password must contain at least eight characters
2: The password must contain at least one uppercase letter
3: The password must contain at least one lowercase letter
4: The password must contain at least one number
5: The password must contain at least one of these given special characters: @, !, #, ^, &, *, or $
6: The password should not be previously leaked. The list of leaked passwords is contained in alleged-gmail-passwords file
7: The password cannot consist of an English word. The list of 5 letter english words are in words_5 file

## How I programmed it
I programmed this password checker in C++ with my knowledge of in built C++ functions, recursion, vectors, and for and while loops

## Challenges I ran into
The text files: alleged-gmail-passwords and words_5 were very long. So, I first had to learn how to open these files, read through each line, and store them into a vector.

## Accomplishments that I am proud of
I did not know how to open a file and read through each line of it before, but after this program, I learned something that is an elementary step in the Computer Science field.

## What I learned
I learned the importance of programming especially when there are files that contain thousands of rows that contain information to read through, which is tedious if we were to do it manually.
