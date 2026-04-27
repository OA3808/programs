import kagglehub
import pandas as pd
from sklearn.tree import DecisionTreeRegressor

# Download latest version
path = kagglehub.dataset_download("muhammadshahidazeem/customer-churn-dataset")

print("Path to dataset files:", path)

data = pd.read_csv(path)
y = data.TotalSpend
feature_columns = ['CustomerID', 'Age', 'Gender', 'Tenure']
X = data[feature_columns]
customer_model = DecisionTreeRegressor()
customer_model.fIt(X, y)

print(customer_model.predict(X.head()))

