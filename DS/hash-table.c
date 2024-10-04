#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
  int value;
  char key[];
} Record;

typedef struct {
  int capacity;
  int length;
  Record **array;
} HashTable;

Record *createRecord(char key[], int value) {
  int keyLength = strlen(key) + 1;
  Record *r = malloc(sizeof(Record) + keyLength);
  strcpy(r->key, key);
  r->value = value;
  return r;
}

int hashAdd(Record **array, char key[], int m) {
  int prime = 31;
  unsigned int hashValue = 0;
  for (int i = 0; i < strlen(key); i++) {
    hashValue = (hashValue * prime + key[i]) % m;
  }
  Record *existingRecord = array[hashValue];
  while (existingRecord != NULL && (strcmp(existingRecord->key, key) ||
                                    !strcmp(existingRecord->key, ""))) {
    hashValue = (hashValue + 3) % m;
    existingRecord = array[hashValue];
  }

  return hashValue;
}

int hash(Record **array, char key[], int m) {
  int prime = 31;
  unsigned int hashValue = 0;
  for (int i = 0; i < strlen(key); i++) {
    hashValue = (hashValue * prime + key[i]) % m;
  }
  Record *existingRecord = array[hashValue];
  while (existingRecord != NULL && strcmp(existingRecord->key, key)) {
    hashValue = (hashValue + 3) % m;
    existingRecord = array[hashValue];
  }

  return hashValue;
}

void resize(HashTable *obj) {
  int newCapacity = obj->capacity * 2;
  Record **newArray = calloc(newCapacity, sizeof(Record *));
  for (int i = 0; i < obj->capacity; i++) {
    Record *record = obj->array[i];
    if (record != NULL) {
      unsigned int newHashValue = hash(newArray, record->key, newCapacity);
      newArray[newHashValue] = record;
    }
  }
  free(obj->array);
  obj->array = newArray;
  obj->capacity = newCapacity;
}

void add(HashTable *obj, char key[], int value) {
  int m = obj->capacity;
  if (obj->length == (m * 2 / 3))
    resize(obj);
  unsigned int hashValue = hashAdd(obj->array, key, m);
  Record *r = obj->array[hashValue];
  if (r == NULL) {
    obj->array[hashValue] = createRecord(key, value);
    obj->length++;
  } else {
    r->value = value;
  }
}

Record *get(HashTable *obj, char key[]) {
  int m = obj->capacity;
  unsigned int hashValue = hash(obj->array, key, m);
  return obj->array[hashValue];
}

int exists(HashTable *obj, char key[]) {
  int m = obj->capacity;
  unsigned int hashValue = hash(obj->array, key, m);
  return obj->array[hashValue] != NULL;
}

void delete(HashTable *obj, char key[]) {
  int m = obj->capacity;
  Record *r = get(obj, key);
  if (r == NULL)
    return;
  free(r);
  obj->length--;
}

int main() {
  HashTable obj;
  obj.capacity = 8;
  obj.length = 0;
  obj.array = calloc(obj.capacity, sizeof(Record *));
  add(&obj, "adel", 123);
  add(&obj, "adel", 275);
  add(&obj, "bassel", 122);
  add(&obj, "menu", 420);
  add(&obj, "cat", 684);
  add(&obj, "paw", 981);
  add(&obj, "bonk", 790);
  add(&obj, "dame", 512);
  add(&obj, "lua", 886);
  add(&obj, "extra", 679);
  delete (&obj, "extra");

  for (int i = 0; i < obj.capacity; i++) {
    Record *record = obj.array[i];
    if (record == NULL)
      continue;

    printf("key: %s, value:%d \n", record->key, record->value);
  }
  printf("hash table capacity: %d, length: %d\n", obj.capacity, obj.length);
  free(obj.array);

  return 0;
}
