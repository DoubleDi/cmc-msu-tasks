#! /usr/bin/env python3
# -*- coding: utf-8 -*-
# Дорожкин Денис 425 группа

import numpy as np
import scipy
import re
import sklearn
import sklearn.feature_extraction.text
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.datasets import fetch_20newsgroups
from sklearn.naive_bayes import MultinomialNB, BernoulliNB
from sklearn.linear_model import SGDClassifier, LogisticRegression
from sklearn.metrics import classification_report


import xml.etree.ElementTree as ET


def parse_xml(path):
    train_data = {'data': [], 'target': [], 'type': [], 'url': []}

    tree = ET.parse(path)
    root = tree.getroot()

    for child in root:
        new_item = {}
        for param in child:
            if param.tag == 'speech':
                new_item['data'] = re.sub(r'[\!\"\#\$\%\&\\(\)\*\+\,\-\.\/\:\;\<\=\>\?\@\[\\\]\^\_\`\{\|\}\~]', 
                    '', param.text.strip().lower())
                new_item['type'] = param.attrib['type'].strip()
            elif param.tag == 'evaluation':
                new_item['target'] = param.text.strip()[0]
            elif param.tag == 'url':
                new_item['url'] = param.text.strip()

        if new_item['target'] in {'-', '+', '0'}:
            train_data['data'].append(new_item['data'])
            train_data['type'].append(new_item['type'])
            train_data['target'].append(new_item['target'])
            train_data['url'].append(new_item['url'])

    return train_data


train_data = parse_xml("news_eval_train.xml")
test_data = parse_xml("news_eval_test.xml")


#########################################################################
# Binary + Multinomial Naive Bayes ngram_range=(1, 2) min_df = 1 
#########################################################################
count_vect = sklearn.feature_extraction.text.CountVectorizer(
    ngram_range=(1, 2), min_df=1, encoding='windows-1251', binary=True)
X_train_counts = count_vect.fit_transform(np.asarray(train_data['data']))

tfidf_transformer = TfidfTransformer()
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
clf = MultinomialNB().fit(X_train_tfidf, train_data['target'])


X_new_counts = count_vect.transform(test_data['data'])
X_new_tfidf = tfidf_transformer.transform(X_new_counts)

predicted = clf.predict(X_new_tfidf)

print("Binary + Multinomial Naive Bayes ngram_range=(1, 2) min_df = 1")
print(classification_report(test_data['target'], predicted))



#########################################################################
# TF-IDF + Multinomial Naive Bayes ngram_range=(1, 2) min_df = 1 
#########################################################################
count_vect = sklearn.feature_extraction.text.CountVectorizer(encoding='windows-1251')
X_train_counts = count_vect.fit_transform(np.asarray(train_data['data']))

tfidf_transformer = TfidfTransformer()
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
clf = MultinomialNB().fit(X_train_tfidf, train_data['target'])


X_new_counts = count_vect.transform(test_data['data'])
X_new_tfidf = tfidf_transformer.transform(X_new_counts)

predicted = clf.predict(X_new_tfidf)

print("TF-IDF + Multinomial Naive Bayes ngram_range=(1, 2) min_df = 1")
print(classification_report(test_data['target'], predicted))


#########################################################################
# TF-IDF + Multinomial Naive Bayes ngram_range=(1, 5) min_df = 5
#########################################################################
count_vect = sklearn.feature_extraction.text.CountVectorizer(
    ngram_range=(1, 5), min_df=5, encoding='windows-1251')
X_train_counts = count_vect.fit_transform(np.asarray(train_data['data']))

tfidf_transformer = TfidfTransformer()
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
clf = MultinomialNB().fit(X_train_tfidf, train_data['target'])


X_new_counts = count_vect.transform(test_data['data'])
X_new_tfidf = tfidf_transformer.transform(X_new_counts)

predicted = clf.predict(X_new_tfidf)

print("TF-IDF + Multinomial Naive Bayes ngram_range=(1, 5) min_df = 5")
print(classification_report(test_data['target'], predicted))


#########################################################################
# TF-IDF + Bernoulli Naive Bayes 
#########################################################################
count_vect = sklearn.feature_extraction.text.CountVectorizer(encoding='windows-1251')
X_train_counts = count_vect.fit_transform(np.asarray(train_data['data']))

tfidf_transformer = TfidfTransformer()
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
clf = BernoulliNB().fit(X_train_tfidf, train_data['target'])


X_new_counts = count_vect.transform(test_data['data'])
X_new_tfidf = tfidf_transformer.transform(X_new_counts)

predicted = clf.predict(X_new_tfidf)

print("TF-IDF + Bernoulli Naive Bayes")
print(classification_report(test_data['target'], predicted))


#########################################################################
# Binary + Linear classifiers with SGD training
#########################################################################
count_vect = sklearn.feature_extraction.text.CountVectorizer(
    ngram_range=(1, 3), min_df=1, encoding='windows-1251', binary=True)
X_train_counts = count_vect.fit_transform(np.asarray(train_data['data']))

tfidf_transformer = TfidfTransformer(use_idf=False)
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
clf = SGDClassifier(loss='hinge', penalty='l2',
    alpha=1e-3, random_state=42, max_iter=5, tol=None).fit(X_train_tfidf, train_data['target'])


X_new_counts = count_vect.transform(test_data['data'])
X_new_tfidf = tfidf_transformer.transform(X_new_counts)

predicted = clf.predict(X_new_tfidf)

print("Binary + Linear classifiers with SGD training")
print(classification_report(test_data['target'], predicted))


#########################################################################
# TF-IDF + Linear classifiers with SGD training
#########################################################################
count_vect = sklearn.feature_extraction.text.CountVectorizer(
    ngram_range=(1, 3), min_df=1, encoding='windows-1251')
X_train_counts = count_vect.fit_transform(np.asarray(train_data['data']))

tfidf_transformer = TfidfTransformer()
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
clf = SGDClassifier(loss='hinge', penalty='l2',
    alpha=1e-3, random_state=42, max_iter=5, tol=None).fit(X_train_tfidf, train_data['target'])


X_new_counts = count_vect.transform(test_data['data'])
X_new_tfidf = tfidf_transformer.transform(X_new_counts)

predicted = clf.predict(X_new_tfidf)

print("TF-IDF + Linear classifiers with SGD training")
print(classification_report(test_data['target'], predicted))


#########################################################################
# TF-IDF + Logistic Regression
#########################################################################
count_vect = sklearn.feature_extraction.text.CountVectorizer()
X_train_counts = count_vect.fit_transform(np.asarray(train_data['data']))

tfidf_transformer = TfidfTransformer()
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
clf = LogisticRegression().fit(X_train_counts, train_data['target'])

X_new_counts = count_vect.transform(test_data['data'])
X_new_tfidf = tfidf_transformer.transform(X_new_counts)

predicted = clf.predict(X_new_counts)

print("TF-IDF + Logistic Regression")
print(classification_report(test_data['target'], predicted))


#########################################################################
# Binary + Logistic Regression
#########################################################################
count_vect = sklearn.feature_extraction.text.CountVectorizer(binary=True)
X_train_counts = count_vect.fit_transform(np.asarray(train_data['data']))

tfidf_transformer = TfidfTransformer(use_idf=False)
X_train_tfidf = tfidf_transformer.fit_transform(X_train_counts)
clf = LogisticRegression().fit(X_train_counts, train_data['target'])

X_new_counts = count_vect.transform(test_data['data'])
X_new_tfidf = tfidf_transformer.transform(X_new_counts)

predicted = clf.predict(X_new_counts)

print("Binary + Logistic Regression")
print(classification_report(test_data['target'], predicted))
