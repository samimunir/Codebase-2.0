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
print('csv_data_frame ->\n----------------------\n', csv_data_frame)
print(csv_data_frame.info())

# use '|' as a delimiter/separator to parse data into rows/columns.
text_data_frame = pd.read_table(r'data\moviesSample.txt', sep='|')
print('\ntext_data_frame ->\n----------------------\n', text_data_frame)
print(text_data_frame.info())

text_2_date_frame = pd.read_table(r'data\moviesSample_2.txt', sep='|')
print('\ntext_2_data_frame ->\n----------------------\n', text_2_date_frame)
print(text_2_date_frame.info())