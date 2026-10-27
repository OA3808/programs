"""Customer Spend Prediction Model.

Predicts a customer's total spend from their profile and usage data
using a Decision Tree Regressor, and reports how well it does on
customers the model has never seen.

Dataset: "Customer Churn Dataset" on Kaggle (muhammadshahidazeem/customer-churn-dataset)
Run:     pip install kagglehub pandas scikit-learn
         python aiproject.py
"""

import glob
import os

import kagglehub
import pandas as pd
from sklearn.metrics import mean_absolute_error, r2_score
from sklearn.model_selection import cross_val_score, train_test_split
from sklearn.tree import DecisionTreeRegressor

RANDOM_STATE = 42


def load_data() -> pd.DataFrame:
    """Download the dataset and load its training CSV."""
    folder = kagglehub.dataset_download("muhammadshahidazeem/customer-churn-dataset")
    csv_files = sorted(glob.glob(os.path.join(folder, "*.csv")))
    if not csv_files:
        raise FileNotFoundError(f"No CSV files found in {folder}")

    # Prefer the training file if the dataset has separate train/test files.
    training = [f for f in csv_files if "train" in os.path.basename(f).lower()]
    path = training[0] if training else csv_files[0]
    print(f"Loading {os.path.basename(path)}")

    data = pd.read_csv(path)
    # Column names in this dataset contain spaces ("Total Spend"), so normalize them.
    data.columns = [c.strip().replace(" ", "") for c in data.columns]
    return data.dropna()


def build_features(data: pd.DataFrame):
    """Pick features and turn text columns into numbers."""
    target = "TotalSpend"
    # CustomerID is just a label, and Churn is an outcome, so neither is used as a feature.
    candidates = [
        "Age", "Gender", "Tenure", "UsageFrequency", "SupportCalls",
        "PaymentDelay", "SubscriptionType", "ContractLength", "LastInteraction",
    ]
    features = [c for c in candidates if c in data.columns]

    X = pd.get_dummies(data[features], drop_first=True)  # encodes Gender, SubscriptionType, ContractLength
    y = data[target]
    return X, y


def main():
    data = load_data()
    X, y = build_features(data)
    print(f"{len(X):,} customers, {X.shape[1]} features: {', '.join(X.columns)}")

    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.2, random_state=RANDOM_STATE
    )

    # Pick the tree depth with 5-fold cross-validation on the training set only,
    # so the test set stays untouched until the final score.
    best_depth, best_cv_mae = None, float("inf")
    for depth in [3, 5, 8, 12, None]:
        model = DecisionTreeRegressor(max_depth=depth, min_samples_leaf=20, random_state=RANDOM_STATE)
        cv_mae = -cross_val_score(model, X_train, y_train, cv=5, scoring="neg_mean_absolute_error").mean()
        print(f"max_depth={str(depth):>4}  cross-validated MAE=${cv_mae:,.2f}")
        if cv_mae < best_cv_mae:
            best_depth, best_cv_mae = depth, cv_mae

    depth = best_depth
    model = DecisionTreeRegressor(max_depth=depth, min_samples_leaf=20, random_state=RANDOM_STATE)
    model.fit(X_train, y_train)
    preds = model.predict(X_test)
    mae, r2 = mean_absolute_error(y_test, preds), r2_score(y_test, preds)

    # Baseline: always predict the average spend. A useful model should beat this.
    baseline_mae = mean_absolute_error(y_test, [y_train.mean()] * len(y_test))

    print("\n--- Results on the 20% test set ---")
    print(f"Best max_depth:        {depth}")
    print(f"Model MAE:             ${mae:,.2f}")
    print(f"Baseline MAE (mean):   ${baseline_mae:,.2f}")
    print(f"Model R^2:             {r2:.3f}")

    importances = pd.Series(model.feature_importances_, index=X.columns).sort_values(ascending=False)
    print("\nTop features:")
    print(importances.head(5).round(3).to_string())


if __name__ == "__main__":
    main()
