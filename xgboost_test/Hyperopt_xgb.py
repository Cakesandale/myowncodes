from hyperopt import fmin, tpe, hp, partial
import numpy as np
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.metrics import mean_squared_error, zero_one_loss
import xgboost as xgb
import pandas as pd

def GetNewDataByPandas():
    wine = pd.read_csv("/Users/01384573/Documents/Mycodes/leet_git/myowncodes/xgboost_test/winequality-red.csv", delimiter=';')
    print(wine.head(1))
    wine['alcohol**2'] = pow(wine["alcohol"], 2)
    wine['volatileAcidity*alcohol'] = wine["alcohol"] * wine['volatile acidity']
    y = np.array(wine.quality)
    X = np.array(wine.drop("quality", axis=1))

    columns = np.array(wine.columns)

    return X, y, columns


# 首先将数据分割为三份，一部分用于预测，训练数据则同样分成额外的两部分用于evallist参数。
# 同时为了加快速度和减少内存，我们将数据转换为xgboost自带的读取格式。
# Read wine quality data from file
X, y, wineNames = GetNewDataByPandas()

# split data to [[0.8,0.2],0.1]
x_train_all, x_predict, y_train_all, y_predict = train_test_split(X, y, test_size=0.10, random_state=100)

x_train, x_test, y_train, y_test = train_test_split(x_train_all, y_train_all, test_size=0.2, random_state=100)

dtrain = xgb.DMatrix(data=x_train,label=y_train,missing=-999.0)
dtest = xgb.DMatrix(data=x_test,label=y_test,missing=-999.0)

evallist = [(dtest, 'eval'), (dtrain, 'train')]


# 自定义hyperopt的参数空间
space = {"max_depth": hp.randint("max_depth", 15),
         "n_estimators": hp.randint("n_estimators", 300),
         'learning_rate': hp.uniform('learning_rate', 1e-3, 5e-1),
         "subsample": hp.randint("subsample", 5),
         "min_child_weight": hp.randint("min_child_weight", 6),
         }

def argsDict_tranform(argsDict, isPrint=False):
    argsDict["max_depth"] = argsDict["max_depth"] + 5
    argsDict['n_estimators'] = argsDict['n_estimators'] + 150
    argsDict["learning_rate"] = argsDict["learning_rate"] * 0.02 + 0.05
    argsDict["subsample"] = argsDict["subsample"] * 0.1 + 0.5
    argsDict["min_child_weight"] = argsDict["min_child_weight"] + 1
    if isPrint:
        print(argsDict)
    else:
        pass

    return argsDict

def xgboost_factory(argsDict):
    argsDict = argsDict_tranform(argsDict)

    params = {'nthread': -1, 'max_depth': argsDict['max_depth'], 'n_estimators': argsDict['n_estimators'],
              'eta': argsDict['learning_rate'], 'subsample': argsDict['subsample'],
              'min_child_weight': argsDict['min_child_weight'], 'objective': 'reg:linear', 'silent': 0, 'gamma': 0,
              'colsample_bytree': 0.7, 'alpha': 0, 'lambda': 0, 'scale_pos_weight': 0, 'seed': 100, 'missing': -999,
              'eval_metric': ['rmse']}

    xrf = xgb.train(params, dtrain, 300, evallist, early_stopping_rounds=100)

    return get_tranformer_score(xrf)

def get_tranformer_score(tranformer):

    xrf = tranformer
    dpredict = xgb.DMatrix(x_predict)
    prediction = xrf.predict(dpredict, ntree_limit=xrf.best_ntree_limit)

    return mean_squared_error(y_predict, prediction)


# 开始使用hyperopt进行自动调参
algo = partial(tpe.suggest, n_startup_jobs=1)
best = fmin(xgboost_factory, space, algo=algo, max_evals=20, pass_expr_memo_ctrl=None)


RMSE = xgboost_factory(best)
print('best :', best)
print('best param after transform :')
argsDict_tranform(best,isPrint=True)
print('rmse of the best xgboost:', np.sqrt(RMSE))