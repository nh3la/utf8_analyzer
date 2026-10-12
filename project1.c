#include <stdio.h>
#include <stdint.h>
#include <string.h>

int8_t is_ascii(char string[]) {
    for (int i = 0; string[i] != '\0'; i++) {
        if ((unsigned char)string[i] > 127) {
            return 0;
        }
    }
    return 1;
}

int32_t capitalize_ascii(char str[]) {
    int32_t count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - ('a' - 'A');
            count++;
        }
    }

    return count;
}

int8_t codepoint_size(char string[]) {
uint8_t b0 = (unsigned char)string[0];
    int8_t n;

    if ((b0 & 0x80) == 0) {
        n = 1;
    } else if ((b0 & 0xE0) == 0xC0) {
        n = 2;
    } else if ((b0 & 0xF0) == 0xE0) {
        n = 3;
    } else if ((b0 & 0xF8) == 0xF0) {
        n = 4;
    } else {
        return -1;
    }
    return n;
}

int32_t utf8_strlen(char str[]) {
    int counter = 0;
    int i = 0;
    while(str[i] != '\0'){
    uint8_t b0 = (unsigned char)str[i];
    uint32_t n;

    if ((b0 & 0x80) == 0) {
        n = 1;
    } else if ((b0 & 0xE0) == 0xC0) {
        n = 2;
    } else if ((b0 & 0xF0) == 0xE0) {
        n = 3;
    } else if ((b0 & 0xF8) == 0xF0) {
        n = 4;
    } else {
        return -1;
    }
    i += n;
    counter++;
    }
    return counter;

}

void utf8_substring(const char str[], int start, int end, char result[]){
    // TODO: Implement this function
    
    if (start < 0 || start >= end) {
    result[0] = '\0';
    return;
    }
    
    int counter = 0;
    int i = 0;
    int j = 0;
    int tot = 0;
    while(str[i] != '\0'){
    uint8_t b0 = (unsigned char)str[i];
    uint32_t n;

    if ((b0 & 0x80) == 0) {
        n = 1;
    } else if ((b0 & 0xE0) == 0xC0) {
        n = 2;
    } else if ((b0 & 0xF0) == 0xE0) {
        n = 3;
    } else if ((b0 & 0xF8) == 0xF0) {
        n = 4;
    } else {
        //return -1;
    }
    i += n;
    if(counter >= start && counter < end){
        for(int k = 0; k < n; k++){
        result[j] = str[tot + k];
        j++;
        }
    }
    counter++;
    tot += n;
    }
    
    result[j] = '\0';

}

int32_t codepoint_at(char str[], int32_t byte_index) {
    // TODO: Implement this function
    uint32_t len = strlen(str);

    if (byte_index >= len) {
        return -1;
    }

    uint8_t b0 = (unsigned char)str[byte_index];
    uint32_t cp;
    uint32_t n;

    if ((b0 & 0x80) == 0) {
        cp = b0;
        n = 1;
    } else if ((b0 & 0xE0) == 0xC0) {
        cp = b0 & 0x1F;
        n = 2;
    } else if ((b0 & 0xF0) == 0xE0) {
        cp = b0 & 0x0F;
        n = 3;
    } else if ((b0 & 0xF8) == 0xF0) {
        cp = b0 & 0x07;
        n = 4;
    } else {
        return -1;
    }

    for (uint32_t i = 1; i < n; i++) {
        uint8_t b = (unsigned char)str[byte_index + i];

        if ((b & 0xC0) != 0x80) {
            return -1;
        }

        cp = (cp << 6) | (b & 0x3F);
    }

    return (int32_t)cp;
}

int is_animal_emoji_at(const char str[], int index){
uint32_t len = strlen(str);

    int byte_index = 0;

      int counter = 0;
      int i = 0;
      while(str[i] != '\0'){
      uint8_t b0 = (unsigned char)str[i];
      uint32_t n;

      if ((b0 & 0x80) == 0) {
          n = 1;
      } else if ((b0 & 0xE0) == 0xC0) {
          n = 2;
      } else if ((b0 & 0xF0) == 0xE0) {
          n = 3;
      } else if ((b0 & 0xF8) == 0xF0) {
          n = 4;
      } else {
          return -1;
      }
      i += n;
      counter++;

      if(counter == index){
      byte_index = i;
      break;
      }

    }

    if (byte_index < 0 || byte_index >= len) {
        return 0;
    }

    uint8_t b0 = (unsigned char)str[byte_index];
    uint32_t cp;
    uint32_t n;
	if ((b0 & 0x80) == 0) {
        cp = b0;
        n = 1;
    } else if ((b0 & 0xE0) == 0xC0) {
        cp = b0 & 0x1F;
        n = 2;
    } else if ((b0 & 0xF0) == 0xE0) {
        cp = b0 & 0x0F;
        n = 3;
    } else if ((b0 & 0xF8) == 0xF0) {
        cp = b0 & 0x07;
        n = 4;
    } else {
        return -1;
    }


    for (uint32_t i = 1; i < n; i++) {
        uint8_t b = (unsigned char)str[byte_index + i];

        if ((b & 0xC0) != 0x80) {
            return -1;
        }

        cp = (cp << 6) | (b & 0x3F);
    }

    uint32_t up1 = 128000;
    uint32_t do1 = 128063;
    uint32_t up2 = 129408;
    uint32_t do2 = 129454;
    if(((int32_t)cp >= up1 && (int32_t)cp <= do1) || ((int32_t)cp >= up2 && (int32_t)cp <= do2)){
    return 1;
    }
    else{
    return 0;
    }
}

int main()
{
/*    printf("Is 🔥 ASCII? %d\n", is_ascii("🔥"));
    
    int32_t ret = 0;
    char str1[] = "abcd";
    ret = capitalize_ascii(str1);
    printf("Capitalized String: %s\nCharacters updated: %d\n", str1, ret);
    
    printf("Size: %d bytes\n", codepoint_size("éclair")); 
    char s[] = "Héy";
    printf("Size: %d\n", codepoint_size(&s[2]));
    
    char str2[] = "Joséph";
    printf("Length of string %s is %d\n", str2, utf8_strlen(str2));

	char str3[] = "🦀🦮🦮🦀🦀🦮🦮"; // these emoji are 4 bytes long
    char result[17];
    utf8_substring(str3, 3, 7, result);
    printf("String: %s\nSubstring: %s\n", str3, result);

	char str4[] = "Joséph"; // J o s é é p h
                       // 0 1 2 3 4 5 6  <- byte indices; é takes bytes 3 and 4
	printf("Codepoint at byte 5 in %s is %d\n", str4, codepoint_at(str4, 5)); // 'p' starts at byte 5
	printf("Codepoint at byte 3 in %s is %d\n", str4, codepoint_at(str4, 3)); // 'é' starts at byte 3
	printf("Codepoint at byte 4 in %s is %d\n", str4, codepoint_at(str4, 4)); // byte 4 is the middle of 'é'
	char str[] = "I 🐶 you";
	printf("%d %d\n", is_animal_emoji_at(str, 2), is_animal_emoji_at(str, 0)); // 🐶 is code point 2
	*/
	char sen[50];
	printf("Enter a UTF-8 encoded string: ");
	fgets(sen, sizeof(sen), stdin);
	sen[strcspn(sen, "\n")] = '\0';
	printf("Valid ASCII: ");
	if(is_ascii(sen) == 1){
	printf("true\n");
	}
	else{
		printf("false\n");
	}

	printf("Uppercased ASCII: ");
	char res[50];
	strcpy(res, sen);
	int ret = capitalize_ascii(res);
	printf("%s\n", res);

	printf("Length in bytes: ");
	int length = strlen(sen);
	printf("%d\n", length);
	
	printf("Number of code points: ");
	int32_t len = utf8_strlen(sen);
	printf("%d\n", len);

	printf("Bytes per code points: ");
	for(int i = 0; sen[i] != '\0'; i++){
		int8_t num = codepoint_size(&sen[i]);
		if(num != -1){
			printf("%d ", num);
		}
	}

	printf("\nSubstring of the first 6 code points: ");
	char result[50];
	utf8_substring(sen, 0, 6, result);
	printf("%s\n", result);

	printf("Code points as decimal numbers: ");
	for(int i = 0; sen[i] != '\0'; i++){
		int32_t nu  = codepoint_at(sen, i);
		if(nu != -1){
			printf("%d ", nu);
		}
	}

	printf("\nAnimal emojis: ");
	char result2[50];
	for(int i = 0; sen[i] != '\0'; i++){
		int che = is_animal_emoji_at(sen, i);
		if(che == 1){
			utf8_substring(sen, i, (i + 1), result2);
			printf("%s ", result2);
		}
	}





	return 0;
}

