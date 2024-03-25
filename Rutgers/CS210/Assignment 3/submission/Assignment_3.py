# Sami Munir
# March 24th, 2024
# CS210 - Information & Data Management
# Assignment 3 - Movie Recommendation System
# - Assignment_3.py

import pandas as pd

print('Assignment 3 - Movie Recommendation System\n')
"""
Ratings file:
A text file that contains movie ratings. Each line has the ID of
    the user who rated the movie, the ID of the movie, and its
    rating (range 0-5 inclusive). A movie can have multiple ratings
    from different users. A user can rate multiple movies but can
    rate a particular movie only once.

Movies file:
A text file that contains movies and their genres. Each line has a
    movie ID, the name of the movie, the year it was released, and
    the genre of the movie (e.g., Action, Drama, etc.).
"""

# Part 1.1
"""
Write a function load_movies_dataframe(file_path) that takes in a
    movies file and returns a pandas DataFrame, where the index is
    the movie ID and the columns are "title", "year", and "genre"
    (in that order), sorted by the movie ID.
"""
def load_movies_dataframe(file_path):
    movies_dataframe = pd.read_table(file_path, sep='|', header=None, names=["title", "year", "genre"])
    sorted_movies_dataframe = movies_dataframe.sort_values(by='title', ascending=True)
    # print('sorted_movies_dataframe ->\n', sorted_movies_dataframe)
    return sorted_movies_dataframe

# Part 1.2

# Part 1.3

# Part 1.4

# Part 1.5

# Part 1.6

load_movies_dataframe(r'data\moviesSample.txt')