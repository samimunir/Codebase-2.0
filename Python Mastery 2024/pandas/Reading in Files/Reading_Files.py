# Sami Munir
# March 24th, 2024
# Python Mastery 2024
# pandas
# Reading_Files.py
import pandas as pd

print('Reading in Files with Pandas.\n')

# use 'r' to read in file path as raw text.
csv_data_frame = pd.read_csv(r'data\ratingsSample.csv', header=None, names=['USER', 'MOVIE', 'RATING'])
# ratingSample.csv -> [user_ID, movie_ID, movie_rating (0.0-5.0)]
print('csv_data_frame ->\n', csv_data_frame)

text_data_frame = pd.read_table(r'data\moviesSample.txt', sep='|')
print('text_data_frame ->\n', text_data_frame)