import pandas as pd
# --- PART 1: Movies Recommendation ---

# 1.1
def load_movies_dataframe(file_path):
    pass

# 1.2
# Define the function to load the ratings data from a CSV file
def load_ratings_dataframe(file_path):
    pass

# 1.3
def count_unique_genres(movies_df):
    """
    Counts the unique genres in the movies DataFrame.
    
    Parameters:
    movies_df (DataFrame): A pandas DataFrame containing movie data.
    
    Returns:
    int: The count of unique genres.
    """
    pass

# 1.4
def average_rating_by_genre(movies_df, ratings_df):
    """
    Calculates the average rating for each genre.
    
    Parameters:
    movies_df (DataFrame): A pandas DataFrame containing movie data, indexed by 'movie_id'.
    ratings_df (DataFrame): A pandas DataFrame containing ratings data.
    
    Returns:
    Series: A pandas Series where the index is the genre and the value is the average rating for that genre.
    """
    pass

# 1.5
def calculate_average_ratings(ratings_df):
    """
    Calculates the average rating for each movie.

    Parameters:
    ratings_df (DataFrame): DataFrame containing ratings data, with 'movie_id' and 'rating' columns.
    
    Returns:
    Series: A pandas Series where the index is 'movie_id' and the value is the average rating for each movie.
    """
    pass

# 1.6
def highest_rated_movie_id_by_genre_and_year(movies_df, ratings_df, genre, year):
    """
    Finds the movie_id of the highest-rated movie for a given genre and year.
    
    Parameters:
    movies_df (DataFrame): DataFrame containing movie data.
    ratings_df (DataFrame): DataFrame containing ratings data.
    genre (str): The genre to filter movies by.
    year (int or str): The year to filter movies by.
    
    Returns:
    The `movie_id` of the highest-rated movie for the specified genre and year. Returns `None` if no movie matches the criteria.
    """
    pass

# --- PART 2: Mythical Creature ---
# 2.1
def prepare_monster_data(file):
    pass

# 2.2
def monster_type_analysis(monster_df):
    pass

#2.3
def top_three_env_to_see_monsters(monster_df):
    pass

#2.4
def most_gargantuan_monsters_env(monster_df):
    pass