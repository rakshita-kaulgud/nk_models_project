from django import forms

ECONOMIC_MODELS = [('1', 'Cournot'), ('2', 'Differential Model')]

RULE_PARAMS_CHOICES = [('0', 'Imitation'), ('1', 'Innovation')]


class HomeForm(forms.Form):
    def __init__(self, *args, **kwargs):
        super(HomeForm, self).__init__(*args, **kwargs)
        for field in self.fields:
            help_text = self.fields[field].help_text
            self.fields[field].help_text = None
            if help_text != '':
                self.fields[field].widget.attrs.update(
                    {'class': 'has-popover', 'data-content': help_text, 'data-placement': 'right',
                     'data-container': 'body'})

    numTasks = forms.IntegerField(label='Number of Tasks', initial=10)
    numFirms = forms.IntegerField(label='Number of Firms', initial=10)
    alpha = forms.DecimalField(label='Alpha', initial=1.0, help_text="This is a demand parameter. Change "
                                                                     "this value carefully.")
    beta = forms.DecimalField(label='Beta', initial=1.0, help_text="This is a demand parameter. Change "
                                                                   "this value carefully.")
    enter_rule = forms.DecimalField(label='Enter rule', required=False)
    exit_rule = forms.DecimalField(label='Exit rule', required=False)
    mutation = forms.DecimalField(label='Mutation', required=False)
    num_time_periods = forms.IntegerField(label="Number of time periods", initial=100)
    num_of_runs = forms.IntegerField(label="Number of runs", initial=2000)
    rule_params = forms.MultipleChoiceField(label="Rule Parameters",
                                            widget=forms.CheckboxSelectMultiple(attrs={'id': 'rule_params_id'}),
                                            choices=RULE_PARAMS_CHOICES,
                                            help_text="0 - pure random, 1 - pure imitation")
