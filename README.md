UTF-8 String Analyzer (C)
Project Overview
This project is a command-line string analyzer written in C. It explores how computers store and process text using ASCII and UTF-8, where a character can occupy between one and four bytes. The program accepts a line of text and displays information about its encoding, including its byte length, Unicode code point count, and decimal code point values. It also demonstrates ASCII capitalization, Unicode-aware substring extraction, and basic emoji detection.
How the Code Works
The application is organized into small functions, each responsible for a specific text-processing operation:
- is_ascii() checks whether every byte in a string belongs to the ASCII range (0–127).
- capitalize_ascii() converts lowercase English letters to uppercase in place and returns the number of letters changed. Non-ASCII bytes are left unchanged.
- codepoint_size() examines the leading byte of a UTF-8 character to determine whether it uses one, two, three, or four bytes.
- utf8_strlen() moves through a string using those byte lengths to count code points instead of bytes.
- utf8_substring() copies a selected range of code points into a separate output buffer, preserving multibyte characters.
- codepoint_at() combines UTF-8 bytes using bitwise operations to calculate a character's numeric Unicode value.
- is_animal_emoji_at() checks decoded values against two predefined ranges of animal emoji.
- next_utf8_char() attempts to encode the Unicode value immediately after a selected code point.
The main() function collects user input with fgets(), calls these helpers, and prints the results in a readable format.
