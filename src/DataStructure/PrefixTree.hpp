// MIT License
// Copyright 2017 zhaochenyou16@gmail.com

#ifndef DATASTRUCTURE_PREFIXTREE_HPP
#define DATASTRUCTURE_PREFIXTREE_HPP

#include <string.h>
#include <assert.h>
#ifndef MAX
#define MAX 64
#endif

struct PrefixTree {
  char letter;
  const char *word;
  /* next letter if exist */
  PrefixTree *child[26];
};

auto ChildIndex(char letter) -> int {
  return (int)(letter - 'a');
}

auto PrefixTreeNew() -> PrefixTree* {
  PrefixTree *t = new PrefixTree();
  if (!t) return nullptr;
  t->letter = (char)-1;
  t->word = nullptr;
  memset(t->child, 0, sizeof(t->child));
  return t;
}

auto PrefixTreeFree(PrefixTree *t) -> void {
  if (!t)
    return;
  for (int i = 0; i < 26; i++)
    PrefixTreeFree(t->child[i]);
  delete t;
}

auto PrefixTreeInsert(PrefixTree *t, const char *word) -> void {
  int n = strlen(word);
  PrefixTree *e = t;
  for (int i = 0; i < n; i++) {
    int index = ChildIndex(word[i]);
    if (e->child[index] == nullptr) {
      e->child[index] = new PrefixTree();
      // initialize e->child[index]
      PrefixTree *he = e->child[index];
      he->letter = word[i];
      he->word = nullptr;
      memset(he->child, 0, sizeof(he->child));
    }
    e = e->child[index];
    if (i == n - 1) {
      e->word = word;
    }
  }
}

auto PrefixTreeFind(PrefixTree *t, const char *word) -> int {
  PrefixTree *e = t;
  int n = strlen(word);
  for (int i = 0; i < n; i++) {
    int index = ChildIndex(word[i]);
    if (!e)
      return 0;
    e = e->child[index];
    if (!e)
      return 0;
    if (i == n - 1 and e->word and strcmp(e->word, word) == 0)
      return 1;
  }
  return 0;
}

auto PrefixTreeErase(PrefixTree *t, const char *word) -> void {
  PrefixTree *e = t;
  int n = strlen(word);
  for (int i = 0; i < n; i++) {
    int index = ChildIndex(word[i]);
    e = e->child[index];
    if (i == n-1) {
      e->word = nullptr;
      return;
    }
  }
}


#endif // DATASTRUCTURE_PREFIXTREE_HPP
