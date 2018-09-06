#! /usr/bin/env python
# -*- coding: utf-8 -*-
# Дорожкин Денис 425 группа

import numpy as np

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

all_docs = {}
df = {}
idf = {}

# На вход файл с путями всех документов
file_path = raw_input("File with all the doc files:\n")
with open(file_path) as f:
    doc_files = f.read().splitlines()
f.close()

total_documents = len(doc_files)

# Для каждого документа подсчет его tf и df по всем его словам 
for doc_path in doc_files:
    
    with open(doc_path) as f:
        phrase = f.read().lower()
    f.close()

    words = phrase.split()
        
    all_docs.setdefault(doc_path, {})
    all_docs[doc_path].setdefault('phrase', '')
    all_docs[doc_path]['phrase'] = phrase
     
    for word in words:
        all_docs[doc_path].setdefault('tf', {})
        all_docs[doc_path]['tf'].setdefault(word, 0)
        all_docs[doc_path]['tf'][word] += 1 
        
    for word in all_docs[doc_path]['tf']:
        df.setdefault(word, 0)
        df[word] += 1

# idf подсчет
for word in df.keys():
    idf[word] = np.log10(total_documents / float(df[word]))

# Абсолютный порядок слов в векторе
word_order = df.keys()

# Вычисление tf, idf, веса W в ачестве векторов
idf_vector = [ idf[word] for word in word_order ]

# Параметр который определяет - нужно ли использовать tf-idf или просто tf
use_tf_idf = bool(input("use tf-idf?\n"))
for doc in all_docs.values():
    tf_vector = [ doc['tf'].get(word, 0) for word in word_order ]
    
    if use_tf_idf :
        weight = np.asarray(idf_vector) * tf_vector
        weight = weight / float(np.sqrt(np.sum(weight ** 2)))
    else:
        weight = np.asarray(tf_vector)

    doc['tf_vector'] = tf_vector
    doc['weight'] = weight

# Обработка запроса
query_path = raw_input("File with query:\n")
query = all_docs[query_path]
del all_docs[query_path]

# Подсчет косинуса угла между векторами запроса и документов
for doc in all_docs.values():
    rank = np.sum(doc['weight'] * query['weight']) / float(np.sqrt(np.sum(doc['weight'] ** 2)) * np.sqrt(np.sum(query['weight'] ** 2)))
    doc['rank'] = rank

# Сортировка ответов
ordered_docs = all_docs.keys()
ordered_docs = sorted(ordered_docs, key = lambda d: all_docs[d].get('rank', 0), reverse = True)  

# На выход - упорядоченные по убыванию путь к фразе, ранк
for d in ordered_docs:
    print(d, all_docs[d]['rank'])
    # print(d, all_docs[d]['rank'], all_docs[d]['phrase'])
