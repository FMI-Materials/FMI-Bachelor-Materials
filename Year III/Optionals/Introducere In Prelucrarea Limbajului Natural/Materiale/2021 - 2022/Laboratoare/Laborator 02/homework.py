# TASK:

# Deadline: 10 martie ora 23:59. Formular pentru trimiterea temei: https://forms.gle/kMcWxv8e39wwXy1W7.
# Folosind datasetul urmator, https://github.com/ancatache/LaRoSeDa/tree/main/data -
# o colectie de review-uri pentru produse in romana, rezolvati urmatoarele cerinte:

# 1) Curatati si normalizati corpus-ul aplicand urmatoarele operatiii:
#   a) afisati caracterele diferite de literele mici ale alfabetului englez
#   b) transformati numerele in cuvinte folosind num2words
#   c) eliminati linkurile si alte referinte
#   d) curatati-l de semnele de punctuatie
#   e) impartiti textele in cuvinte (tokens), va recomandam sa folositi spacy incarcand unul
#      din modelele pentru limba romana (https://spacy.io/models/ro)
#   f) eliminati stopwords
#   g) aplicati stemming
#   h) aplicati lematizare peste cuvintele obtinute la punctul f.
#      Comparand cu rezultatele de la punctul g, afisati top 15 cuvinte pentru care stemul este diferit de lema,
#      sortate descrescator dupa numarul de caractere prin care stemul difera de lema.
#   i) cautati top 20 trigrame (collocations)
# 2) Calculati frecventele de aparitie ale fiecarui token la punctul e) si punctul g).
#    Plotati-le cum doriti, prin wordcloud sau plotbar. Ce diferente observati?
#    (intrucat numarul de cuvinte distincte poate fi mare, puteti plota informatii
#    doar despre cele mai frecvente N cuvinte)
# 3) Plotati distributia numarului de tokens per review (nr. de reviews vs. nr. de tokens),
#    atat pentru review-urile negative, cat si, separat, pentru cele pozitive. Ce observati?


import json
import re

import matplotlib.pyplot as plt
import pandas as pd
from num2words import num2words
import spacy
from nltk.stem.snowball import SnowballStemmer
import string
from nltk.collocations import TrigramCollocationFinder, TrigramAssocMeasures

nlp = spacy.load("ro_core_news_sm")
stemmer = SnowballStemmer(language='romanian')


def num_to_words(sentence):
    new_content = []
    for x in sentence.split(" "):
        if x.isnumeric():
            x = num2words(float(x), lang="ro")
        new_content.append(x)
    return ' '.join(new_content)


def plot_words(all_words, all_steamed_words, n=25):
    all_words_and_steamed = dict()
    for word in all_words:
        if word in all_words_and_steamed:
            all_words_and_steamed[word]['word'] += 1
            continue
        all_words_and_steamed[word] = {'word': 1, 'steamed': 0}
    for word in all_steamed_words:
        if word in all_words_and_steamed:
            all_words_and_steamed[word]['steamed'] += 1
            continue
        all_words_and_steamed[word] = {'word': 0, 'steamed': 1}
    top_words = list(all_words_and_steamed.keys())
    top_words.sort(
        key=lambda x: 0 if x in ['', ' '] else all_words_and_steamed[x]['word'] + all_words_and_steamed[x]['steamed'],
        reverse=True)
    top_words = top_words[:n]
    xx = [all_words_and_steamed[x]['word'] for x in top_words]
    yy = [all_words_and_steamed[x]['steamed'] for x in top_words]
    df = pd.DataFrame({'tokens': xx, 'steamed': yy}, index=top_words)
    df.plot.bar(rot=0)
    plt.figure(figsize=(25, 10))
    plt.show()


def analyse_reviews(reviews):
    # a) afisati caracterele diferite de literele mici ale alfabetului englez
    print("Caractere diferite de alfabetul englez: \n")
    for review in reviews:
        print(re.sub(r'[a-z\s\n]', '', review['content']))

    def get_differences(orig, list1, list2):
        i = 0
        diff = []
        for x in list1:
            y = list2[i]
            if x != y:
                diff.append((orig[i], abs(len(x) - len(y))))
            i += 1
        return diff

    def analyse_sentence(sentence):
        # b) transformati numerele in cuvinte folosind num2words
        sentence = num_to_words(sentence)
        # c) eliminati linkurile si alte referinte
        sentence = re.sub(r'http\S+', '', sentence)
        # d) curatati-l de semnele de punctuatie\
        sentence = sentence.translate(str.maketrans('', '', string.punctuation))
        # e) impartiti textele in cuvinte (tokens), va recomandam sa folositi spacy incarcand unul
        #    din modelele pentru limba romana (https://spacy.io/models/ro)
        doc = nlp(sentence)
        # f) eliminati stopwords
        actual_doc = []
        for token in doc:
            if token.text not in nlp.Defaults.stop_words:
                actual_doc.append(token)
        words = [token.text for token in actual_doc]
        # g) aplicati stemming
        steamed_words = [stemmer.stem(word) for word in words]

        # h) aplicati lematizare peste cuvintele obtinute la punctul f.
        lemma_words = [word.lower() for word in words]
        lemma_steamed_differences = get_differences([token.text for token in actual_doc], steamed_words, lemma_words)

        return words, steamed_words, lemma_words, lemma_steamed_differences

    # Comparand cu rezultatele de la punctul g, afisati top 15 cuvinte pentru care stemul este diferit de lema,
    # sortate descrescator dupa numarul de caractere prin care stemul difera de lema.
    all_lemma_steamed_differences = []
    all_words, all_steamed_words = [], []
    reviews_tokens = []
    for review in reviews:
        r_words, r_steamed_words, r_lemma_words, r_lemma_steamed_differences = analyse_sentence(review['content'])
        all_lemma_steamed_differences.extend(r_lemma_steamed_differences)
        all_words.extend(r_words)
        all_steamed_words.extend(r_steamed_words)
        reviews_tokens.append(r_words)
    all_lemma_steamed_differences.sort(key=lambda x: x[1], reverse=True)
    print("Top 15 cuvinte cu stemul diferit de lema: \n", [x[0] for x in all_lemma_steamed_differences[:15]])

    # i) cautati top 20 trigrame (collocations)
    trigram_measures = TrigramAssocMeasures()
    colloc_founder = TrigramCollocationFinder.from_words(all_words)
    trigram_results = colloc_founder.nbest(trigram_measures.pmi, 20)
    print("Top 20 trigrame: \n", trigram_results)

    return all_words, all_steamed_words, reviews_tokens


def main():
    with open("data/negative_reviews.json", "r") as nrf:
        negative_reviews = json.loads(nrf.read())
    with open("data/positive_reviews.json", "r") as prf:
        positive_reviews = json.loads(prf.read())
    # 1) Curatati si normalizati corpus-ul aplicand urmatoarele operatiii:
    all_positive_words, all_steamed_positive_words, positive_reviews_tokens = analyse_reviews(
        positive_reviews['reviews'])

    # 2) Calculati frecventele de aparitie ale fiecarui token la punctul e) si punctul g).
    #    Plotati-le cum doriti, prin wordcloud sau plotbar. Ce diferente observati?
    #    (intrucat numarul de cuvinte distincte poate fi mare, puteti plota informatii
    #    doar despre cele mai frecvente N cuvinte)
    plot_words(all_positive_words, all_steamed_positive_words)

    # 3) Plotati distributia numarului de tokens per review (nr. de reviews vs. nr. de tokens),
    #    atat pentru review-urile negative, cat si, separat, pentru cele pozitive. Ce observati?
    _, __, negative_reviews_tokens = analyse_reviews(negative_reviews['reviews'])

    plt.plot(range(len(positive_reviews_tokens)), [len(x) for x in positive_reviews_tokens], color='green')
    plt.title('Distributia numarului de tokens per review pozitiv')
    plt.show()
    plt.plot(range(len(negative_reviews_tokens)), [len(x) for x in negative_reviews_tokens], color='red')
    plt.title('Distributia numarului de tokens per review negativ')
    plt.show()

    # OBS: Review-urile negative au mai putine cuvinte in general


if __name__ == "__main__":
    main()
