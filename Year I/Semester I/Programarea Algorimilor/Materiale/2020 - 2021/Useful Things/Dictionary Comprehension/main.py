# dictionary comprehension = create dictionaries using an expression
#                            can replace for loops certain lambda functions

# dictionary = {key: expression for (key, value) in iterable}
cities_in_F = {"New York": 32, "Boston": 75, "Los Angeles": 100, "Chicago": 50}
cities_in_C = {key: round((value - 32) * (5 / 9)) for (key, value) in cities_in_F.items()}
print(cities_in_C)      # it prints {'New York': 0, 'Boston': 24, 'Los Angeles': 38, 'Chicago': 10}

# dictionary = {key: expression for (key, value) in iterable if conditional}
weather = {"New York": "snowing", "Boston": "sunny", "Los Angeles": "sunny", "Chicago": "cloudy"}
sunny_weather = {key: value for (key, value) in weather.items() if value == "sunny"}
print(sunny_weather)    # it prints {'Boston': 'sunny', 'Los Angeles': 'sunny'}

# dictionary = {key: (if/else) for (key, value) in iterable}
cities = {"New York": 32, "Boston": 75, "Los Angeles": 100, "Chicago": 50}
desc_cities = {key: ("WARM" if value >= 40 else "COLD") for (key, value) in cities.items()}
print(desc_cities)      # it prints {'New York': 'COLD', 'Boston': 'WARM', 'Los Angeles': 'WARM', 'Chicago': 'WARM'}

# dictionary = {key: function(value) for (key, value) in iterable}
def check_temp(value):
    if value >= 70:
        return "HOT"
    elif 69 >= value >= 40:
        return "WARM"
    else:
        return "COLD"

cities2 = {"New York": 32, "Boston": 75, "Los Angeles": 100, "Chicago": 50}
desc_cities2 = {key: check_temp(value) for (key, value) in cities.items()}
print(desc_cities2)     # it prints {'New York': 'COLD', 'Boston': 'HOT', 'Los Angeles': 'HOT', 'Chicago': 'WARM'}