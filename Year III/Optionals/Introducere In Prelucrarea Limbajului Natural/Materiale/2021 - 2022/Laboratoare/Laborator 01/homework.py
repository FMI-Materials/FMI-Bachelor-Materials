import json

import bs4
import requests


def parse_html(html):
    return bs4.BeautifulSoup(html, "html.parser")


def parse_html_from_link(link):
    res = requests.get(link)
    return parse_html(res.content)


def parse_review_page(html_review):
    reviews_tags = html_review.findAll("div", attrs={"class": "imdb-user-review"})
    reviews = []
    for review_tag in reviews_tags:
        title = review_tag.find("a", attrs={"class": "title"}).text
        text = review_tag.find("div", attrs={"class": "text"}).text
        try:
            rating = review_tag.find("span", attrs={"class": "rating-other-user-rating"}).find("span").text
        except:
            rating = 0
        data = review_tag.find("span", attrs={"class": "review-date"}).text
        username = review_tag.find("span", attrs={"class": "display-name-link"}).find("a").text
        reviews.append({
            "title": title,
            "text": text,
            "data": data,
            "rating": rating,
            "username": username,
            "movie": movie['movie']
        })
    return reviews


if __name__ == "__main__":
    # 1. Pornind de la lista cu cele mai populare 250 de filme de pe IMDb ([https://www.imdb.com/chart/top/](https://www.imdb.com/chart/top/)), identificati pentru toate aceste filme link-ul catre pagina sa de recenzii.
    #
    # Exemplu: aici se gaseste pagina cu recenzii pentru "The Shawshank Redemption": [https://www.imdb.com/title/tt0111161/reviews](https://www.imdb.com/title/tt0111161/reviews)

    movies = list()
    html = parse_html_from_link("https://www.imdb.com/chart/top/")
    tds = html.findAll("td", attrs="titleColumn")
    for td in tds:
        a = td.find("a")
        link = a.attrs['href']
        movie_id = link.split("/")[2]
        reviews_link = f"https://www.imdb.com/title/{movie_id}/reviews"
        movies.append({
            "reviews_link": reviews_link,
            "movie": a.text,
            "movie_id": movie_id
        })
        print(f"Loaded movie: {a.text}. Id: {movie_id}. Reviews link: {reviews_link}")

    # 2. Pentru fiecare film colectati date despre recenziile sale (titlu, text, rating, data, utlizator, etc.)
    reviews = list()
    for movie in movies:
        html_review = parse_html_from_link(movie['reviews_link'])
        reviews.extend(parse_review_page(html_review))
        print(f"Saved movie reviews: {movie['movie']}")

    # 3. Creati un dataset de recenzii, pentru fiecare recenzie stocati:
    #  * filmul caruia ii apartine
    #  * titlul recenziei
    #  * textul recenziei
    #  * ratingul
    #  * data
    #  * utilizator
    #
    #  Salvati datasetul intr-un fisier JSON.

    with open("reviews.json", "w") as f:
        f.write(json.dumps(reviews))

    # 4. Pe o pagina cu recenzii putem gasi un numar mic de astfel de date. Butonul de "Load more" de la final, cand este apasat,
    # produce un request care returneaza HTML-ul urmatoarelor recenzii.
    # Folosind aceasta logica colectati automat pentru fiecare film un numar mai mare de recenzii.
    reviews = list()
    for movie in movies:
        html_review = parse_html_from_link(movie['reviews_link'])
        limit_pages = 5
        while html_review is not None and limit_pages > 0:
            reviews.extend(parse_review_page(html_review))
            pagination_key = html_review.find("div", attrs={"class": "load-more-data"}).attrs['data-key']
            html_review = parse_html_from_link(f"https://www.imdb.com/title/{movie['movie_id']}/reviews/_ajax?ref_=undefined&paginationKey={pagination_key}")
            limit_pages -= 1
        print(f"Saved movie extended reviews (5 pages): {movie['movie']}")

    with open("reviews_extended.json", "w") as f:
        f.write(json.dumps(reviews))
