from tqdm.notebook import tqdm


import pandas as pd
import numpy as np

whole_csv = pd.read_csv("biogears_py/csv/wholepsv.csv", index_col=['pid', 'time'])
whole_csv = whole_csv.groupby(level=0).filter(lambda x: (~np.isnan(x["Hgb"])).sum() > 1)
# split the whole_csv into sepsis and nonsepsis subdf
sepsis_csv = whole_csv[whole_csv["SepsisLabel"] == 1]

sepsis_pids = sepsis_csv.index.get_level_values(0).unique()
nonsepsis_pids = whole_csv.index.get_level_values(0).unique().difference(sepsis_pids)

sepsis_csv = whole_csv.loc[sepsis_pids]
nonsepsis_csv = whole_csv.loc[nonsepsis_pids]

print("sepsis patients mean feat values")
print(sepsis_csv.groupby(level=0).mean().mean())
print("nonsepsis patients mean feat values")
print(nonsepsis_csv.groupby(level=0).mean().mean())


def slid_convet(whole_csv, win_size, step_size):
    # slid processing over the second level of the multiindex
    # output shape: N, win_size, features
    pids = whole_csv.index.get_level_values(0).unique()
    samples = []
    labels = []
    for _id in tqdm(pids):
        subdf = whole_csv.loc[[_id]]
        t_s = 0
        while t_s + win_size  < len(subdf):
            samples_tmp = subdf.iloc[t_s:t_s + win_size]
            featcols = [col for col in samples_tmp.columns if col != "SepsisLabel"]
            samples.append(samples_tmp[featcols].values)
            labels_tmp = subdf.iloc[t_s + win_size]
            labels_tmp = labels_tmp["SepsisLabel"]
            labels.append(labels_tmp)
            t_s += step_size
    return np.array(samples), np.array(labels)


from sklearn.model_selection import train_test_split
import xgboost as xgb
from sklearn.metrics import classification_report

# first discretize the realtime vts
real_time_vtcols = ["HR", "O2Sat", "Temp", "SBP", "MAP", "DBP", "Resp"]
real_time_vts = whole_csv[real_time_vtcols]
real_time_vts_disc = real_time_vts.apply(lambda x: pd.qcut(x, q=[0, 0.33, 0.66, 1], labels=[0, 1, 2]), axis=0)
whole_csv_rts_disced = whole_csv.copy()
whole_csv_rts_disced[real_time_vtcols] = real_time_vts_disc
# takes only the real time vitalsigns
whole_csv_rts_disced = whole_csv_rts_disced[real_time_vtcols + ["SepsisLabel"]]

samples, labels = slid_convet(whole_csv_rts_disced, 12, 5)

# next trying training the model using the feat max - min values
pos_samples = samples[labels == 1]
neg_samples = samples[labels == 0]

# get the max and min values of the features
wholecsvfeatcols = [col for col in whole_csv.columns if col != "SepsisLabel"]
reshaped_feat_cols = []
for i in range(samples.shape[1]):
    for col in wholecsvfeatcols:
        reshaped_feat_cols.append(f"{col}_past_{i}")

samples_df = pd.DataFrame(samples.reshape(samples.shape[0], -1), columns=reshaped_feat_cols)

# xgboost model
X_train, X_test, y_train, y_test = train_test_split(samples_df, labels, test_size=0.33, random_state=42)

# balance the dataset of class sepsis 0 and sepsis 1
pos_count = np.sum(y_train).astype(int)
neg_count = len(y_train) - pos_count
# balance the dataset using subsampling
train_idxes = np.arange(len(y_train))
pos_idxes = train_idxes[y_train == 1]
neg_idxes = train_idxes[y_train == 0]
np.random.seed(42)
neg_idxes = np.random.choice(neg_idxes, pos_count, replace=False)
train_idxes = np.concatenate([pos_idxes, neg_idxes])
X_train = X_train.iloc[train_idxes]
y_train = y_train[train_idxes]

model = xgb.XGBClassifier()
model.fit(X_train, y_train)

preds = model.predict(X_test)

print(classification_report(y_test, preds > 0.5))

# plot the feature importance
xgb.plot_importance(model)