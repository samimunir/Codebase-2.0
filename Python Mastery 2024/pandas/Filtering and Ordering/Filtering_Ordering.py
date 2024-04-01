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
# print('\ntext_data_frame ->\n----------------------\n', text_data_frame)
text_2_date_frame = pd.read_table(r'data\moviesSample_2.txt', sep='|')
# print('\ntext_2_data_frame ->\n----------------------\n', text_2_date_frame)

# print('\n', csv_data_frame['RATING'] >= 3.5)
# printing out movies with a rating >= 3.5.
specific_ratings = csv_data_frame[csv_data_frame['RATING'] >= 3.5]
print('\nRATING >= 3.5 -->\n', specific_ratings)
# printing out movies with IDs 5 and 10.
specific_movies = [5, 10]
print('\n', csv_data_frame[csv_data_frame['MOVIE'].isin(specific_movies)])
# printing out user IDs from that are <= 10.
print('\n', csv_data_frame[csv_data_frame['USER'] <= 10])

# csv_data_frame_v2 = csv_data_frame.set_index('USER')
# print('\n', csv_data_frame_v2.filter(items=['MOVIE', 'RATING'], axis=1))

# printing RATINGs by order of RATINGs under 3.5 in descending order.
# print('\n', csv_data_frame[csv_data_frame['RATING'] <= 3.5].sort_values(by=['USER', 'RATING'], ascending=[True, True]))

# type code here...