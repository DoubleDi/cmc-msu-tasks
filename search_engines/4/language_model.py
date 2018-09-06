#! /usr/bin/env python
# -*- coding: utf-8 -*-
# Дорожкин Денис 425 группа

import numpy as np

import sys
reload(sys)
sys.setdefaultencoding('utf-8')

docs = {}
all_words = []

l= 0.9

# На вход файл с путями всех документов
file_path = raw_input("File with all the doc files:\n")
with open(file_path) as f:
    doc_files = f.read().splitlines()
f.close()

total_documents = len(doc_files)

for doc_path in doc_files:
    
    with open(doc_path) as f:
        phrase = f.readline().lower()        
        number = int(f.readline().lower()) 
    f.close()

    words = phrase.split()
        
    docs.setdefault(doc_path, {})
    docs[doc_path].setdefault('words', [])
    docs[doc_path].setdefault('number', [])
    docs[doc_path]['words'] = words
    docs[doc_path]['number'] = number

    all_words += words 

query_path = raw_input("File with query:\n")
query = docs[query_path]["words"]
del docs[query_path]

for path in docs.keys():
    docs[path].setdefault('p', 1)
    for q in query:
        docs[path]['p'] *= (float(docs[path]["words"].count(q)) / len(docs[path]["words"]) * l + \
                            float(all_words.count(q)) / len(all_words) * (1 - l))

# Сортировка ответов
ordered_docs = docs.keys()
ordered_docs = sorted(ordered_docs, key = lambda d: docs[d].get('p', 0), reverse = True)  

for d in ordered_docs:
    print(d, docs[d]['p'])

dcg = 0.0
for i in range(len(ordered_docs)):
    if i == 0:
        dcg = docs[ordered_docs[0]]['number']
    else:
        dcg += float(docs[ordered_docs[i]]['number']) / np.log2(i + 2)

# сортировка ответов для iDCG
idcg_ordered_docs = sorted(ordered_docs, key = lambda d: docs[d].get('number', 0), reverse = True) 
# for d in idcg_ordered_docs:
#     print d, docs[d]['number']

idcg = 0.0
for i in range(len(idcg_ordered_docs)):
    if i == 0:
        idcg = docs[idcg_ordered_docs[0]]['number']
    else:
        idcg += float(docs[ordered_docs[i]]['number']) / np.log2(i + 2)

print "DCG: ", dcg
print "iDCG: ", idcg 
print "nDCG: ", dcg / idcg

     
