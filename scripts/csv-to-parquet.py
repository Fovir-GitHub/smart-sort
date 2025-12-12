import pandas as pd
import os

chunk_size = 2000
csv_file = "./data.csv"
output_dir = "./parquet-data"
os.makedirs(output_dir, exist_ok=True)

dtype_map = {
    "size": "int64",
    "order_ratio": "float64",
    "effective_order": "int64",
    "duplicated_rank": "int64",
    "unique_ratio": "float64",
    "entropy": "float64",
    "value_range": "int64",
    "sorted_prefix_length": "int64",
    "sorted_suffix_length": "int64",
    "sort_direction": "int64",
    "best_algorithm": "string"
}

i = 0
for chunk in pd.read_csv(csv_file, chunksize=chunk_size):
    chunk = chunk.astype(dtype_map)
    output = os.path.join(output_dir, f"part{i:04d}.parquet")
    chunk.to_parquet(output, index=False, engine="pyarrow", compression="snappy")
    print(f"Write {output}  (rows: {len(chunk)})")
    i += 1
