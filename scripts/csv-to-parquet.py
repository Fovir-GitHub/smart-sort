import pandas as pd

chunck_size = 2000
csv_file = "./data.csv"

i = 0
for chunk in pd.read_csv(csv_file, chunksize=chunck_size):
  output = f"./parquet-data/part{i:04d}.parquet"
  chunk.to_parquet(output, index=False)
  print(f"Write {output}")
  i+=1
