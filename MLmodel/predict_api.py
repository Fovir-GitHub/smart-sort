import sys
import json
import yaml
import pandas as pd
from pathlib import Path
from model.model import load_model
from features.features_extractor import extract_features

def get_input_from_user():
    while True:
        choice = input("Select input method:\n1. Direct input\n2. Input from file\nEnter 1 or 2: ").strip()
        if choice in ("1", "2"):
            break
        print("Invalid choice. Please enter 1 or 2.")

    if choice == "1": # array directly input
        arr_str = input("Enter array (e.g. [1,2,3]): ").strip()
        try:
            arr = json.loads(arr_str)
        except Exception:
            print("Invalid array format")
            sys.exit(2)
    else: # file indirectly input
        file_path = input("Enter path to JSON file containing array: ").strip()
        try:
            with open(file_path, "r") as f:
                arr = json.load(f)
        except Exception:
            print("Failed to read array from file")
            sys.exit(3)

    while True:
        sort_dir_str = input("Enter sort direction (1 for ascending, -1 for descending): ").strip()
        try:
            sort_direction = int(sort_dir_str)
            if sort_direction not in (+1, -1):
                raise ValueError
            break
        except ValueError:
            print("Invalid sort direction. Enter 1 or -1.")

    return arr, sort_direction

def main():
    project_root = Path(__file__).resolve().parent
    config = yaml.safe_load(open(project_root / "config.yaml", "r")) # load .yaml

    features = config["features"]
    model_path = project_root / config["save_path"]
    label_map_path = model_path.parent / "label_mapping.json" # load .json

    model = load_model(model_path) # load model

    with open(label_map_path, "r") as f:
        label_mapping = json.load(f)
    inverse_label_mapping = {v: k for k, v in label_mapping.items()}

    arr, sort_direction = get_input_from_user()

    feats = extract_features(arr, sort_direction)
    X = pd.DataFrame([[feats[f] for f in features]], columns=features)

    pred_id = int(model.predict(X)[0])
    pred_label = inverse_label_mapping[pred_id]

    print(f"Predicted sorting algorithm: {pred_label}")

if __name__ == "__main__":
    main()
