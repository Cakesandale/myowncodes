import numpy as np
import pandas as pd
import lightgbm as lgb
from sklearn.model_selection import train_test_split
from hyperopt import fmin, tpe, hp, partial
from sklearn.metrics import mean_squared_error


def GetNewDataByPandas():
    wine = pd.read_csv("/Users/01384573/Documents/Mycodes/leet_git/myowncodes/xgboost_test/winequality-red.csv")
    wine['alcohol**2'] = pow(wine["alcohol"], 2)
    wine['volatileAcidity*alcohol'] = wine["alcohol"] * wine['volatile acidity']
    y = np.array(wine.quality)
    X = np.array(wine.drop("quality", axis=1))

    columns = np.array(wine.columns)

    return X, y, columns


##首先将数据分割为三份，一部分用于预测，训练数据则同样分成额外的两部分用于evallist参数。
## 同时为了加快速度和减少内存，我们将数据转换为lightgbm自带的读取格式。


# Read wine quality data from file
X, y, wineNames = GetNewDataByPandas()

# split data to [[0.8,0.2],01]
x_train_all, x_predict, y_train_all, y_predict = train_test_split(X, y, test_size=0.10, random_state=100)
x_train, x_test, y_train, y_test = train_test_split(x_train_all, y_train_all, test_size=0.2, random_state=100)

train_data = lgb.Dataset(data=x_train, label=y_train)
test_data = lgb.Dataset(data=x_test, label=y_test)

# 自定义hyperopt的参数空间
space = {"max_depth": hp.randint("max_depth", 15),
         "num_trees": hp.randint("num_trees", 300),
         'learning_rate': hp.uniform('learning_rate', 1e-3, 5e-1),
         "bagging_fraction": hp.randint("bagging_fraction", 5),
         "num_leaves": hp.randint("num_leaves", 6),
         }


def argsDict_tranform(argsDict, isPrint=False):
    argsDict["max_depth"] = argsDict["max_depth"] + 5
    argsDict['num_trees'] = argsDict['num_trees'] + 150
    argsDict["learning_rate"] = argsDict["learning_rate"] * 0.02 + 0.05
    argsDict["bagging_fraction"] = argsDict["bagging_fraction"] * 0.1 + 0.5
    argsDict["num_leaves"] = argsDict["num_leaves"] * 3 + 10
    if isPrint:
        print(argsDict)
    else:
        pass


def lightgbm_factory(argsDict):
    argsDict = argsDict_tranform(argsDict)

    params = {'nthread': -1, 'max_depth': argsDict['max_depth'], 'num_trees': argsDict['num_trees'],
              'eta': argsDict['learning_rate'], 'bagging_fraction': argsDict['bagging_fraction'],
              'num_leaves': argsDict['num_leaves'], 'objective': 'regression', 'feature_fraction': 0.7, 'lambda_l1': 0,
              'lambda_l2': 0, 'bagging_seed': 100, 'metric': ['rmse']}

    model_lgb = lgb.train(params, train_data, num_boost_round=300, valid_sets=[test_data], early_stopping_rounds=100)

    return get_tranformer_score(model_lgb)


def get_tranformer_score(tranformer):
    model = tranformer
    prediction = model.predict(x_predict, num_iteration=model.best_iteration)

    return mean_squared_error(y_predict, prediction)


# 开始使用hyperopt进行自动调参
algo = partial(tpe.suggest, n_startup_jobs=1)
best = fmin(lightgbm_factory, space, algo=algo, max_evals=20, pass_expr_memo_ctrl=None)

RMSE = lightgbm_factory(best)
print('best :', best)
print('best param after transform :')
argsDict_tranform(best, isPrint=True)
print('rmse of the best lightgbm:', np.sqrt(RMSE))
