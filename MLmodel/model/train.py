import yaml
import pandas as pd
import json
from pathlib import Path
import xgboost as xgb
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report
from model.model import save_model

def main():
    project_root = Path(__file__).resolve().parents[1]
    config = yaml.safe_load(open(project_root / "config.yaml", "r"))

    train_path = project_root / config["data"]["train_path"]
    save_path = project_root / config["save_path"]
    label_map_path = save_path.parent / "label_mapping.json"

    features = config["features"]
    label = config["label"]
    params = config["model"]["params"]

    print("Loading train data from", train_path)
    df = pd.read_csv(train_path)

    # standardize labels
    df[label] = (
        df[label]
        .astype(str)
        .str.strip()
        .str.lower()
    )

    X = df[features]

    original_labels = sorted(df[label].unique())
    label_mapping = {str(v): int(i) for i, v in enumerate(original_labels)}

    with open(label_map_path, "w") as f:
        json.dump(label_mapping, f, indent=2)

    y = df[label].map(label_mapping) # label map

    bad = y.isna().sum()
    if bad > 0:
        raise RuntimeError(f"Found {bad} unmapped labels in training data") # double check!

    X_train, X_val, y_train, y_val = train_test_split( # divide train set and test set
        X, y,
        test_size=config["split"]["test_size"],
        random_state=config["split"]["random_state"],
        stratify=y
    )

    print("Training XGBoost with params", params)
    model = xgb.XGBClassifier(**params)
    model.fit(X_train, y_train)

    preds = model.predict(X_val)
    print(f"Validation accuracy: {accuracy_score(y_val, preds):.4f}") # validate
    print(classification_report(y_val, preds))

    save_model(model, save_path)
    print("Model saved to:", save_path)
    print("Label mapping saved to:", label_map_path)

if __name__ == "__main__":
    main()