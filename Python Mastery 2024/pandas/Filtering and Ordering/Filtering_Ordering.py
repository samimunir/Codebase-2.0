# Sami Munir
# March 24th, 2024
# Python Mastery 2024
# pandas
# Filtering_Ordering.py
import pandas as pd

print('Filtering & Ordering Data.\n')

csv_data_frame = pd.read_csv(r'data\ratingsSample.csv', header=None, names=['USER', 'MOVIE', 'RATING'])
print('csv_data_frame ->\n----------------------\n', csv_data_frame)
text_data_frame = pd.read_table(r'data\moviesSample.txt', sep='|')
print('\ntext_data_frame ->\n----------------------\n', text_data_frame)
text_2_date_frame = pd.read_table(r'data\moviesSample_2.txt', sep='|')
print('\ntext_2_data_frame ->\n----------------------\n', text_2_date_frame)