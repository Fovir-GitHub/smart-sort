import yaml
import pandas as pd
from sklearn.ensemble import RandomForestClassifier
import xgboost as xgb
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report
from pathlib import Path
from model.model import save_model

def load_config():
    current_file = Path(__file__).resolve()
    project_root = current_file.parents[2]
    config_path = project_root / "config.yaml"
    return yaml.safe_load(open(config_path, "r"))

def main():
    config = load_config()

    project_root = Path(__file__).resolve().parents[2]
    train_path = project_root / config["data"]["train_path"]
    save_path = project_root / config["save_path"]

    features = config["features"]
    label = config["label"]

    # data set segmentation
    split_cfg = config.get("split", {"test_size": 0.2, "random_state": 42})
    ts = split_cfg.get("test_size", 0.2)
    rs = split_cfg.get("random_state", 42)

    print("Loading train data from", train_path)
    df = pd.read_csv(train_path)

    X = df[features] # metric matrix
    y = df[label] # label

    X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=ts, random_state=rs, stratify=y if len(y.unique()) > 1 else None)

    models = {
        "xgboost": xgb.XGBClassifier(**config["model"]["params"]),
        "random_forest": RandomForestClassifier(n_estimators=200, max_depth=12, n_jobs=-1)
    }

    best_score = -1
    best_name = None
    best_model_obj = None

    # train then evaluate each model
    for name, model in models.items():
        print("\nTraining", name)
        model.fit(X_train, y_train)
        preds = model.predict(X_val)
        acc = accuracy_score(y_val, preds)

        print(f"{name} val acc: {acc:.4f}")
        print(classification_report(y_val, preds))
        if acc > best_score:
            best_score = acc
            best_name = name
            best_model_obj = model

    print("\nBest model: ", best_name, f"(acc={best_score:.4f})")
    save_model(best_model_obj, str(save_path))
    print("Saved to: ", save_path)

if __name__ == "__main__":
    main()
