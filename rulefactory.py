import construct_basket
import rulebase


class RuleFactory(object):
    @staticmethod
    def create_rule(rule_name, config):
        if rule_name == 'HamMushroom':
            return construct_basket.ConstructBasket()
        elif rule_name == 'Hawaiian':
            pass
