import pandas as pd


def normalize_column(column):
    min_val = column.min()
    max_val = column.max()
    return (column - min_val) / (max_val - min_val)


data = pd.read_csv('synthetic_credit_consumers.csv')
data_clean = data.dropna()
columns_to_normalize = ['Age', 'CreditScore', 'TransactionAmount', 'LoanAmount', 'LatePayments']
for col in columns_to_normalize:
    data_clean[col] = normalize_column(data_clean[col])
data_clean.to_csv('preprocessed_data.csv', index=False)
