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
data.head()

col_dict = {'symbol_return_col': 'foodexp', 'factor_return_col': 'income'}
formular = '{symbol_return_col} ~ 0 + {factor_return_col}'.format_map(col_dict)

mod = smf.quantreg(formular, data)

res = mod.fit(q=.5)

print(res.summary())

print('parameters are {0}'.format(str(res.params['income'])))

print('pseudo R squared is {0}'.format(res.prsquared))
# for attribute in dir(res):
# if not attribute.startswith('_'):
# print(attribute)
