# Sami Munir
# March 25th, 2024
# Aircraft Data Analytics Project
# - Aircrafts_Analysis.py
# Data: Aircrafts_Data.csv
# - AC_ID, AC_NAME, AC_CODE, AC_REG,
# - AC_AIRLINE, ENG_TYPE
# (in that order left -> right)

import pandas as pd

print('\nAircrafts_Analysis.py\n')

FILE_PATH = r'data\Aircrafts_Data.csv'

def load_and_print_dataframe():
    aircrafts_dataframe = pd.read_csv(FILE_PATH)
    print('aircrafts_dataframe ->\n----------------------\n', aircrafts_dataframe)
    return aircrafts_dataframe

def print_dataframe_info(aircrafts_dataframe):
    print('\naircrafts_dataframe.info() ->\n-----------------------------')
    print(aircrafts_dataframe.info())

def get_aircrafts_from_airline(aircrafts_dataframe, airline):
    filtered_aircrafts_dataframe = aircrafts_dataframe[(aircrafts_dataframe['AC_AIRLINE'] == airline)]
    print(f'\naircrafts from airline: {airline} ->\n------------------------------------------')
    print(filtered_aircrafts_dataframe)
    return filtered_aircrafts_dataframe

def exec_pandas():
    aircrafts_dataframe = load_and_print_dataframe()
    # print_dataframe_info(aircrafts_dataframe=aircrafts_dataframe)
    get_aircrafts_from_airline(aircrafts_dataframe=aircrafts_dataframe, airline='United Airlines')

exec_pandas()