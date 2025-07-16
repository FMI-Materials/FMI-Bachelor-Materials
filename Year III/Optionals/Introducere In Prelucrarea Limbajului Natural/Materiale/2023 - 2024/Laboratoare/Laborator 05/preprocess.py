import os
import re

from collections import defaultdict

import dateparser
import spacy

from bs4 import BeautifulSoup

from nltk import sent_tokenize, word_tokenize
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer, PorterStemmer

def parse_texts():
    with open("titles-data_index.txt") as f:
        raw_titles = f.readlines()
    entries = defaultdict(lambda: [])
    for raw_title in raw_titles:
        # TODO: replace cedilla diacritics with Romanian diacritics
        # this also needs to be done for stopwords
        date_str, title_str = raw_title.replace("&nbsp;", "").strip().split(". ", 1)
        date_idx = re.search("\d+", date_str).start()
        date = dateparser.parse(date_str[date_idx:])
        entries[date].append(title_str)
    return dict(sorted(entries.items()))


def parse_anpc_texts():
    with open("../scraper-anpc/index/index-1.html") as fp:
        soup = BeautifulSoup(fp, features='html.parser')
    html_posts = soup.find_all(class_='brz-posts__item')
    entries = defaultdict(lambda: [])
    def valid_details_link(link):
        return link.get('href').startswith("https://anpc.ro") and not link.get('href').startswith("https://anpc.ro/category/")
    for post in html_posts:
        raw_text = post.get_text()
        date_str = raw_text[0:raw_text.find("Comunicate de Presă")]
        date = dateparser.parse(date_str)
        details_link = [link.get('href') for link in html_posts[0].find_all('a') if valid_details_link(link)][0]
        entries[date].append(raw_text)
    return entries


def tokenize_texts(old_entries):
    new_entries = defaultdict(lambda: [])
    # nltk.download('stopwords')
    stopwords_nltk = stopwords.words('romanian')
    # nltk.download('wordnet')
    lemmatizer = WordNetLemmatizer()
    stemmer = PorterStemmer()
    # python -m spacy download ro_core_news_sm
    nlp = spacy.load("ro_core_news_sm")
    # nltk.download('punkt_tab')  # sent_tokenize
    for i, date in enumerate(old_entries):
        raw_title = ' '.join(old_entries[date]).lower()
        sents_title = sent_tokenize(raw_title)
        words_title = word_tokenize(raw_title)
        words_lemmatized = [lemmatizer.lemmatize(word) for word in words_title]
        words_stemmed = [stemmer.stem(word) for word in words_title]
        words_no_stopwords = [word for word in words_lemmatized if word not in stopwords_nltk]
        doc = nlp(raw_title)
        if i < 2:
            print(f"sents: {sents_title}")
            print(f"words: {words_title}")
            print(f"lemmatize: {words_lemmatized}")
            print(f"stem: {words_stemmed}")
            print(f"no sw: {words_no_stopwords}")
            print("--------------\nspacy\n")
            print("sents:")
            for sent in doc.sents:
                print(sent)
            print("--------------")
            print("text\tlemma\tpos\ttag\tdep\tstop")
            print("--------------")
            for token in doc:
                print(f"{token.text}\t{token.lemma_}\t{token.pos_}\t{token.tag_}\t{token.dep_}\t{token.is_stop}")
            print("--------------")
            print("entities")
            for ent in doc.ents:
                print(ent.text, ent.start_char, ent.end_char, ent.label_)
            print("--------------")
        else:
            break
        


if __name__ == "__main__":
    # entries = parse_texts()
    entries = parse_anpc_texts()
    tokenize_texts(entries)
