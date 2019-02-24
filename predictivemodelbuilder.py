import pandas as pd
import glob
import getpass
import argparse
import matplotlib as mpl
import utilities
import matplotlib.pyplot as plt
from enum import Enum
from abc import ABCMeta, abstractmethod

mpl.use('Agg')

__author__ = 'cchen'


class PredictiveModelBuilder(object):
    __metaclass__ = ABCMeta
    r_square = 0
    sse = 0

    X = pd.DataFrame()
    y = pd.DataFrame()
    w = pd.DataFrame()
    input_predictors = pd.DataFrame()
    output_predictors = pd.DataFrame()

    model_behavior = None
    research_context = None

    def __init__(self, context, y, X, w, descriptor):
        self.research_context = context
        self.X = X
        self.y = y
        self.w = w
        self.input_predictors = descriptor

    @abstractmethod
    def build(self): pass

    def get_model_as_data_frame(self):
        return self.output_predictors


class TreeBasedModelBuilder(PredictiveModelBuilder):
    model_behavior = 'dt'

    def __init__(self, context, y, X, w, descriptor):
        super(TreeBasedModelBuilder, self).__init__(context, y, X, w, descriptor)

    def build(self): pass


class LinearPredictiveModelBuilder(PredictiveModelBuilder):
    model_behavior = 'linear'

    def __init__(self, context, y, X, w, descriptor):
        super(LinearPredictiveModelBuilder, self).__init__(context, y, X, w, descriptor)

        # predictor_columns = [x for x in samples.columns if x[0:4] == 'PRED']
        # print('all the predictors we will process for modelling {}'.format(', '.join(list(predictor_columns))))

    def _dump_data_to_disk(self):
        modeling_directory = self.research_context.get_modeling_direcectory()
        self.X.to_csv(modeling_directory + '/X.csv', encoding='utf-8', index=False)
        self.y.to_csv(modeling_directory + '/y.csv', encoding='utf-8', index=False)
        self.w.to_csv(modeling_directory + '/w.csv', encoding='utf-8', index=False)
        self.input_predictors.to_csv(modeling_directory + '/predictors.input.csv', encoding='utf-8', index=False)

    def _call_r_script(self):
        template = '/usr/bin/Rscript--vanilla {source}/terran_scripts/glmnetWrapper.R -X {modeling}X.csv -y {modeling}/y.csv -w {modeling}/w.csv -p {modeling}/predictors.input.csv'
        command = template.format(source_dir=self.research_context.get_source_directory(), modeling=self.research_context.get_modeling_direcectory())
        utilities.run_command(command)

    def build(self):
        pass


class RidgeLinearModelBuilder(LinearPredictiveModelBuilder):
    def __init__(self, context, y, X, w, descriptor):
        super(LinearPredictiveModelBuilder, self).__init__(context, y, X, w, descriptor)

    def build(self):
        self._dump_data_to_disk()
        self._call_r_script()

        output = self.research_context.get_modeling_direcectory() + '/predictors.output.csv'

        print('loading output predictors from {}'.format(output))
        self.output_predictors = pd.read_csv(output)


class LassoLinearModelBuilder(LinearPredictiveModelBuilder):
    def __init__(self, context, y, X, w, descriptor):
        super(LinearPredictiveModelBuilder, self).__init__(context, y, X, w, descriptor)

    def build(self):
        self._dump_data_to_disk()
        self._call_r_script()
