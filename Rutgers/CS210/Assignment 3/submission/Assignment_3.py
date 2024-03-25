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
    print('\nsorted_movies_dataframe ->\n', sorted_movies_dataframe)
    return sorted_movies_dataframe

# Part 1.2
"""
Write a function load_ratings_dataframe(file_path) that reads a
    ratings .csv file into a pandas DataFrame with columns "user_id",
    "movie_id", and "rating", sorted by the user ID (use default index).
"""
def load_ratings_dataframe(file_path):
    ratings_dataframe = pd.read_csv(file_path, header=None, names=["user_id", "movie_id", "rating"])
    sorted_ratings_dataframe = ratings_dataframe.sort_values(by='user_id', ascending=True)
    print('\nsorted_ratings_dataframe ->\n', sorted_ratings_dataframe)
    return sorted_ratings_dataframe

# Part 1.3
"""
Write a function named count_unique_genres(movies_df) that takes a
    pandas DataFrame as input and returns the count of unique genres
    available in the movies dataset. This function should work on the
    DataFrame loaded by your previously defined load_movies_dataframe()
    function.
"""
def count_unique_genres(movies_df):
    movies_dataframe = movies_df
    unique_count = len(pd.unique(movies_dataframe['genre']))
    print('\nunique_count:', unique_count, '\n')
    return unique_count

# Part 1.4
"""
Write a function average_rating_by_genre(movies_df, ratings_df) that
    performs an analysis on the movie ratings dataset. Your function
    will take two pandas DataFrames as input:
    - 1) movies data (movies_df)
    - 2) ratings data (ratings_df)
    Your goal is to calculate the average rating received by movies in
    each genre. Both DataFrames are created in 1.1 and 1.2.

    Given that each movie is associated with a single genre in the movies_df
    DataFrame, and that movies_df is indexed by movie_id, you will need to
    merge this DataFrame with ratings_df, which contains ratings for each movie.
    After merging, calculate the average rating for movies in each genre and return
    the result as a pandas Series. The index of the Series should be the genre, and
    the value should be the average rating for that genre.

    Your goal is to calculate the average rating received by movies within each genre.
    The calculation should aggregate all ratings for all movies in a genre and then
    compute the average of these ratings. The means you should not calculate the average
    rating per movie and then average those averages across a genre; instead, all individual
    ratings for movies within each genre should be averaged together directly.
"""
def average_rating_by_genre(movies_df, ratings_df):
    print('\nmovies_df ->\n', movies_df)
    print('\nratings_df ->\n', ratings_df)
    merged_dataframe = pd.merge(movies_df, ratings_df, left_on=movies_df.index, right_on='movie_id')
    print('\nmerged_dataframe ->\n', merged_dataframe)
    rating_by_genre_avg = merged_dataframe.groupby('genre')['rating'].mean()
    print('\nrating_by_genre_avg ->\n', rating_by_genre_avg)
    return rating_by_genre_avg

# Part 1.5
"""
Write a function named calculate_average_ratings(ratings_df) that takes a pandas
    DataFrame as input: ratings_df (created in 1.2).

    Your function should return a pandas Series where the index represents the
    movie_id and each value is the average rating of the corresponding movie.

    For example:
    1 3.8333333
    2 3.4166667
    3 4.0000000

    This Series will allow easy access to the average rating of each movie by using
    its movie_id.
"""
def calculate_average_ratings(ratings_df):
    average_ratings = ratings_df.groupby('movie_id')['rating'].mean()
    print('\naverage_ratings ->\n', average_ratings)
    return average_ratings

# Part 1.6
"""
Write a function named highest_rated_movie_by_genre_and_year(movies_df, ratings_df,
    genre, year) that takes four parameters:
    1) movies_df: a pandas DataFrame containing movie data with columns "title", "year",
        and "genre" (created in 1.1).
    2) ratings_df: a pandas DataFrame containing ratings data with columns "user_id",
        "movie_id", and "rating" (created in 1.2).
    3) genre (str): the genre to filter movies by.
    4) year (int or str): the year to filter movies by.

    Definition of highest-rated: for the purpose of this function, a highest-rated movie
    is defined by its average rating, calculated from all the ratings it has received in
    the ratings_df.

    In cases where multiple movies share the same highest average rating for the specified
    genre and year, the movie with the greater number of ratings should be returned as the
    highest-rated movie. If no movies match the specified genre and year criteria, or if all 
    movies in the category have not received any ratings, the function should return None.
"""
def highest_rated_movie_id_by_genre_and_year(movies_df, ratings_df, genre, year):
    filtered_movies = movies_df[(movies_df['genre'] == genre)]
    filtered_movies_by_year = filtered_movies[(filtered_movies['year'] == year)]
    if filtered_movies_by_year.empty:
        print('\nfiltered_movies_by_year is empty...\n')
        return None
    merged_dataframe = pd.merge(filtered_movies_by_year, ratings_df, left_on=filtered_movies_by_year.index, right_on='movie_id')
    movie_stats = merged_dataframe.groupby('movie_id')['rating'].agg(['mean', 'count'])
    sorted_movie_stats = movie_stats.sort_values(by=['mean', 'count'], ascending=False)
    highest_rated_movie_id = sorted_movie_stats.index[0]
    print('\nhighest_rated_movie_id:', highest_rated_movie_id, '\n')
    return highest_rated_movie_id


movies_dataframe = load_movies_dataframe(r'data\moviesSample.txt')
movies_ratings_dataframe = load_ratings_dataframe(r'data\ratingsSample.csv')
# unique_genre_count = count_unique_genres(movies_df=movies_dataframe)
# average_rating_by_genre(movies_df=movies_dataframe, ratings_df=movies_ratings_dataframe)
# calculate_average_ratings(ratings_df=movies_ratings_dataframe)
highest_rated_movie_id_by_genre_and_year(movies_df=movies_dataframe, ratings_df=movies_ratings_dataframe, genre='Action', year=1995)