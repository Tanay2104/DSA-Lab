#include "dictionary.h"
using namespace std;

/*
Commands:
  QUIT
  INS <key> <value>
  DEL <key>
  FIND <key>
*/

void dictionaryHandlerInteractive(Dictionary &dictionary){
  while(true) {
    char input[32];
    cout << ">>> " ;
    if(!(cin >> input)) break;
    if(strcmp(input,"QUIT") == 0){
      break;
    }

    if(strcmp(input,"INS") == 0){
      char inputKey[32];
      int value;
      cin >> inputKey >> value;
      Entry data;
      data.key = new char[32];
      strcpy(data.key,inputKey);
      data.value  = value;
      int hashValueData = dictionary.hashValue(data.key);
      int freeIndexData = dictionary.findFreeIndex(data.key);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        dictionary.put(data);
        cout << "Successfully Added" << endl;
      }
      else{
        cout << "NO Available space" << endl;
      }
    }
    else if(strcmp(input, "DEL") == 0){
      char inputKey[32];
      cin >> inputKey;
      if(dictionary.remove(inputKey)){
        cout << "Entry removed Successfully" << endl;
      }
      else{
        cout << "Entry not present" << endl;
      }
    }
    else if(strcmp(input,"FIND") == 0){
      char inputKey[32];
      cin >> inputKey;
      Entry *entry = dictionary.get(inputKey);
      if(entry != NULL){
        cout << inputKey << " has value: " << entry->value << endl;
      }
      else{
        cout << inputKey << " not Found" << endl;
      }
    }
  }
}

// No ">>> " prompts in testcase mode
void dictionaryHandlerTestcase(Dictionary &dictionary){
  while(true) {
    char input[32];
    if(!(cin >> input)) break;
    if(strcmp(input,"QUIT") == 0){
      break;
    }

    if(strcmp(input,"INS") == 0){
      char inputKey[32];
      int value;
      cin >> inputKey >> value;
      Entry data;
      data.key = new char[32];
      strcpy(data.key,inputKey);
      data.value  = value;
      int hashValueData = dictionary.hashValue(data.key);
      int freeIndexData = dictionary.findFreeIndex(data.key);
      cout << "Hash Value: " << hashValueData << endl;
      cout << "Free Location: "<< freeIndexData << endl;
      if(freeIndexData >= 0){
        dictionary.put(data);
        cout << "Successfully Added" << endl;
      }
      else{
        cout << "NO Available space" << endl;
      }
    }
    else if(strcmp(input, "DEL") == 0){
      char inputKey[32];
      cin >> inputKey;
      if(dictionary.remove(inputKey)){
        cout << "Entry removed Successfully" << endl;
      }
      else{
        cout << "Entry not present" << endl;
      }
    }
    else if(strcmp(input,"FIND") == 0){
      char inputKey[32];
      cin >> inputKey;
      Entry *entry = dictionary.get(inputKey);
      if(entry != NULL){
        cout << inputKey << " has value: " << entry->value << endl;
      }
      else{
        cout << inputKey << " not Found" << endl;
      }
    }
  }
}

void testcase() {
  Dictionary dictionary;
  dictionaryHandlerTestcase(dictionary);
}

void automatic()
{
  std::cout << "Start" << std::endl;
  Dictionary dictionary;
  freopen("sample.txt", "r", stdin);
  int frequency[DICT_SIZE] = {0};
  char word[32];
  while (cin >> word)
  {
    int hash = dictionary.hashValue(word);
    frequency[hash]++;
  }
  for (int i = 0; i < DICT_SIZE; i++)
  {
    cout << frequency[i] << endl;
  }
}

void english()
{
  std::cout << "Start" << std::endl;
  Dictionary dictionary;
  freopen("words.txt", "r", stdin);
  int frequency[DICT_SIZE] = {0};
  char word[32];
  while (cin >> word)
  {
    int hash = dictionary.hashValue(word);
    frequency[hash]++;
  }
  for (int i = 0; i < DICT_SIZE; i++)
  {
    cout << frequency[i] << endl;
  }
}

void interactive() {
  cout<<"Welcome to Dictionary \n";
  Dictionary dictionary;
  dictionaryHandlerInteractive(dictionary);
}

int main(int argc, char **argv) {
  if(argc < 2) return 1;
  char which = argv[1][0];

  if( argv[1][0] == '-' ) {
    cout<<"Give mode of operation:\n 0 for interactive testing \n"
      " 1 for finding distribution of keys on random words \n"
      " 2 for finding distribution of keys on English words\n"
      " 3 for automated testcases"<<endl;
    return 1;
  }
  if( (argv[1][0] != '0' && argv[1][0] != '1' && argv[1][0] != '2' && argv[1][0] != '3') ) {
    freopen(argv[1], "r", stdin); // Redirect the standard input to a file
    which = '0';
  }

  if(which == '0'){
    interactive();
  } else if(which == '1') {
    automatic();
  } else if(which == '2') {
    english();
  } else if(which == '3'){
    testcase();
  }
  return 0;
}
