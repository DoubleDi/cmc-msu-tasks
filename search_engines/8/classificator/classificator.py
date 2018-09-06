#! /usr/bin/env python
# -*- coding: utf-8 -*-
# Дорожкин Денис 425 группа

import numpy as np

import sys
import functools
import os

all_docs = {}
all_words_count = {}
different_words = set()


# На вход файл с путями всех документов
if len(sys.argv) < 2:
    print("В аргументах укажите имя файла, в котром находятся все имена с классифицированными статьями")
    exit

file_path = sys.argv[1]
with open(file_path) as f:
    doc_files = f.read().splitlines()
total_docs_count = len(doc_files)


# Для каждого документа подсчет числа вхождений каждого слова
# Посчет числа разных слов и всех слов
for doc_path in doc_files:
    
    with open(doc_path) as f:
        phrase = f.read().lower()

    words = phrase.split()
    classification = words.pop()

    all_docs.setdefault(classification, {})
    all_docs[classification].setdefault('words', {})
    all_docs[classification].setdefault('p', [])
    all_docs[classification].setdefault('count', 0)
    all_docs[classification]['count'] += 1
    
    for word in words:
        all_docs[classification]['words'].setdefault(word, 0)
        all_docs[classification]['words'][word] += 1
        all_words_count.setdefault(classification, 0)
        all_words_count[classification] += 1
        different_words.add(word)


# Обработка запроса и подсчет вхождений его слов
query_path = input("Введите имя файла, текст которого необходимо классифицировать, обработанный mystem:\n")
with open(query_path) as f:
    words = f.read().lower().split()

query = { 'path': query_path }
query.setdefault('words', {})

for word in words:
    query['words'].setdefault(word, 0)
    query['words'][word] += 1


# Подсчет P(c_i) для всех i
for cl in all_docs.keys():
    all_docs[cl]['p'].append(float(all_docs[cl]['count']) / total_docs_count)

# Подсчет P(x_i|c_j) для всех j и всех x_i из запроса
for word in query['words'].keys():
    for cl in all_docs.keys():
        all_docs[cl]['p'].append(float(all_docs[cl]['words'].get(word, 0) + 1) / (all_words_count[cl] + len(different_words)))

# Складывание и подсчет  log2(P(c_i)) + ... + log2(P(x_k|c_i)) для всех c_i и x_j, подсчитанных ранее
for cl in all_docs.keys():
    all_docs[cl]['p'] = [ np.log2(x + 1) for x in all_docs[cl]['p'] ] # добавляем в логарифм 1 дабы избежать отрицательных чисел
    all_docs[cl]['p_final'] = functools.reduce(lambda x, y: x + y, all_docs[cl]['p'], 0)

# Сортировка и выдача ответов
agregated = [ (all_docs[cl]['p_final'], cl) for cl in list(all_docs.keys()) ]
agregated.sort(key = lambda x: x[0], reverse = True)

print("Веса принадлежности статьи к определенным классам:")
print(agregated)
print("Класс текста: ", agregated[0][1])
