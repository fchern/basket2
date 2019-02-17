# %matplotlib inline

from __future__ import print_function
import patsy
import numpy as np
import pandas as pd
import statsmodels.api as sm
import statsmodels.formula.api as smf
import matplotlib.pyplot as plt
from statsmodels.regression.quantile_regression import QuantReg

data = sm.datasets.engel.load_pandas().data
print(data.head())

#col_dict = {'dependent_name': 'foodexp', 'predictor_name': 'income'}

dependent_name = 'foodexp'

predictor_name_list= ['income', 'education']


for symbol in data.symbol.unique():
    
    for predictor_name in predictor_name_list:
        formular = '{dependent_name} ~ 0 + {predictor_name}'.format(dependent_name, predictor_name)

        mod = smf.quantreg(formular, data)

        res = mod.fit(q=.5)

        print(res.summary())

        print('beta for {1} are {0}'.format(res.params[predictor_name], predictor_name))

        print('pseudo R squared is {0}'.format(res.prsquared))

# for attribute in dir(res):
# if not attribute.startswith('_'):
# print(attribute)
