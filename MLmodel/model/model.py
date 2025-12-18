import xgboost as xgb
from pathlib import Path

def save_model(model, path):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True) # automatically create if not exists parent dir
    model.save_model(str(path)) # professional version (no pickle warning!)

def load_model(path):
    model = xgb.XGBClassifier()
    model.load_model(str(path)) # professional version (no pickle warning!)
    return model
