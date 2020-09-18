import pandas as pd

if __name__ == "__main__":
    read_file = pd.read_csv(r'sample_output_1.txt')
    read_file.to_csv(r'output2.csv', index=None)
