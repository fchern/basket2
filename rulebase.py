import patsy
import numpy as np
import pandas as pd
import statsmodels.api as sm
import statsmodels.formula.api as smf
import logging
import sys
from pathlib import Path


class Rule(object):
    working_dir = None
    rule_name = None
    context = dict()

    def _setup_logger(self):
        self.log = logging.getLogger('')
        self.log.setLevel(logging.DEBUG)
        format = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")

        ch = logging.StreamHandler(sys.stdout)
        ch.setFormatter(format)
        self.log.addHandler(ch)

        fh = logging.FileHandler("{0}/{1}.log".format(self.working_dir, self.rule_name))
        fh.setFormatter(format)
        self.log.addHandler(fh)

    def __init__(self, rule_name):
        self.rule_name = rule_name
        self.context = self._load_context(self)

    def _load_context(self):
        pass

    def touch_target(self):
        Path(self.working_dir + self.rule_name + '.touch').touch()

    def work(self):
        pass
