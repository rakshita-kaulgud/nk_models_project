import sys
import subprocess
import os
import boto3
import io

import botocore
from botocore.handlers import disable_signing
from django.http import HttpResponseRedirect, HttpResponse, FileResponse
from django.shortcuts import render
from django.utils import http
from django.views.generic import TemplateView
from .cFile.differentialModel import *
from dfmodel.forms import HomeForm
from .cFile.cournotModel import *


# from dfmodel.forms import IndexForm


class Index(TemplateView):
    def get(self, request):
        # form = IndexForm()
        return render(request, 'home.html')

    def post(self, request):
        # return HttpResponseRedirect('/cournot/')
        if "Cournot" in request.POST:
            print("in index post cournot")
            return render(request, 'cournot_form.html')
            # return HttpResponseRedirect('/cournot/')
        elif "Differential" in request.POST:
            success = "Work in progress!"
            args = {'success': success}
            return render(request, 'home.html', args)
        success = "Wrong choice"
        args = {'success': success}
        return render(request, 'home.html', args)


class Cournot(TemplateView):
    def post(self, request):
        print("in cournot form")
        inputs = {}
        numTasksStart = int(request.POST['numTasksStart'])
        inputs['numTasksStart'] = numTasksStart
        numTasksEnd = int(request.POST['numTasksEnd'])
        inputs['numTasksEnd'] = numTasksEnd
        numInteractionsStart = int(request.POST['numInteractionsStart'])
        inputs['numInteractionsStart'] = numInteractionsStart
        numInteractionsEnd = int(request.POST['numInteractionsEnd'])
        inputs['numInteractionsEnd'] = numInteractionsEnd
        numFirmsStart = int(request.POST['numFirmsStart'])
        inputs['numFirmsStart'] = numFirmsStart
        numFirmsEnd = int(request.POST['numFirmsStart'])
        inputs['numFirmsEnd'] = numFirmsEnd
        alphaStart = float(request.POST['alphaStart'])
        inputs['alphaStart'] = alphaStart
        alphaEnd = float(request.POST['alphaEnd'])
        inputs['alphaEnd'] = alphaEnd
        betaStart = float(request.POST['betaStart'])
        inputs['betaStart'] = betaStart
        betaEnd = float(request.POST['betaEnd'])
        inputs['betaEnd'] = betaEnd
        inputs['mutationStart'] = float(request.POST['mutationStart'])
        inputs['mutationEnd'] = float(request.POST['mutationEnd'])
        inputs['enterRuleStart'] = float(request.POST['enterRuleStart'])
        inputs['enterRuleEnd'] = float(request.POST['enterRuleEnd'])
        inputs['exitRuleStart'] = float(request.POST['exitRuleStart'])
        inputs['exitRuleEnd'] = float(request.POST['exitRuleEnd'])
        inputs['numRuns'] = int(request.POST['numRuns'])
        inputs['numTimePeriods'] = int(request.POST['numTimePeriods'])
        inputs['ruleParams'] = float(request.POST['ruleParams'])

        params_list = str(inputs)
        params_list = params_list[1:len(params_list) - 1]
        temp = cournotModel(params_list)
        success = "Success!"
        args = {'success': success}
        return render(request, temp, args)


class Home(TemplateView):
    def get(self, request):
        return render(request, 'cournot_form.html')
        # form = HomeForm()
        # return render(request, 'index.html', {'form': form})

    def post(self, request):
        print("in cournot form")
        form = HomeForm(request.POST)
        inputs = {}
        temp = ""
        print("========================")
        print("alpha = " + str(request.POST['alpha']))
        if form.is_valid():
            numTasks = form.cleaned_data['numTasks']
            inputs['numTasks'] = numTasks
            numFirms = form.cleaned_data['numFirms']
            inputs['numFirms'] = numFirms
            alpha = float(request.POST['alpha'].strip("\'"))
            inputs['alpha'] = alpha
            beta = float(request.POST['beta'])
            inputs['beta'] = beta
            enter_rule = float(request.POST['enter_rule'].strip("\'"))
            inputs['enter_rule'] = enter_rule
            exit_rule = float(
                request.POST['exit_rule'])  # if we use form.cleaned_data - we get this 'exit_rule': Decimal('0.4')
            inputs['exit_rule'] = exit_rule
            mutation = float(request.POST['mutation'])
            inputs['mutation'] = mutation
            num_time_periods = form.cleaned_data['num_time_periods']
            inputs['num_time_periods'] = num_time_periods
            num_of_runs = form.cleaned_data['num_of_runs']
            inputs['num_of_runs'] = num_of_runs

            # write input to input file
            filename = "inputs.txt"
            f = open("inputs.txt", "w")
            f.write(str(inputs))
            f.close()
            params_list = str(inputs)
            print("params-list before: " + params_list)
            params_list = params_list[1:len(params_list) - 1]  # removing opening and closing braces in dictionary
            print("params-list after:" + params_list)
            temp = dfModel(numTasks, numFirms, params_list)
        success = "Success!"  # "alpha: " + str(alpha) + " beta: " + str(beta) + " Computation successful with num task equal to " + numTasks + " and number of firms equal to " + numFirms
        args = {'form': form, 'success': success}
        return render(request, temp, args)


def deleteFile(filename):
    pass


class DownloadFile(TemplateView):
    def post(self, request):
        print(request.POST['file_id'])
        file_val = request.POST['file_id'].strip('[]').strip("'")
        s3 = boto3.client('s3')
        s3_res = boto3.resource('s3')
        file_vals = file_val.split('/')
        file_name = file_vals[len(file_vals) - 1].strip("'")
        print(file_name)
        try:
            myBucket = s3_res.Bucket('dardendifferentialmodeloutput')
            for object in myBucket.objects.all():
                if object.key == file_val:
                    print(":::" + object.key)
                    s3.download_file('dardendifferentialmodeloutput', file_val,
                                     os.path.join(os.curdir, os.path.basename(object.key)))
        except botocore.exceptions.ClientError as e:
            if e.response['Error']['Code'] == "404":
                print("The object does not exist.")
            else:
                raise
        success = "Your file has been downloaded!"
        args = {'success': success}
        return render(request, 'display.html', args)


class Display(TemplateView):
    def get(self, request):
        s3 = boto3.resource('s3')
        s3_client = boto3.client('s3')
        bucket = s3.Bucket('dardendifferentialmodeloutput')
        file = []
        for obj in bucket.objects.all():
            key = obj.key
            # body = obj.get()['Body']._raw_stream.readlines()
            temp = []
            temp.append(key)
            file.append(temp)
        result = {'output': file}
        return render(request, 'display.html', result)

    def post(self, request):
        print(request.POST['file_id'])
        file_val = request.POST['file_id'].strip('[]').strip("'")
        print(file_val)
        s3 = boto3.client('s3')
        s3_res = boto3.resource('s3')
        s3_res.meta.client.meta.events.register('choose-signer.s3.*', disable_signing)

        file_vals = file_val.split('/')
        file_name = file_vals[len(file_vals) - 1].strip("'")
        print(file_name)
        try:
            myBucket = s3_res.Bucket('dardendifferentialmodeloutput')
            for object in myBucket.objects.all():
                if object.key == file_val:
                    print(":::" + object.key)
                    if 'Delete' in request.POST:
                        print("deleting %", object.key)
                        s3.delete_object(Bucket='dardendifferentialmodeloutput', Key=object.key)
                    else:
                        s3.download_file('dardendifferentialmodeloutput', file_val,
                                         os.path.join(os.curdir, os.path.basename(file_name)))

                        file = s3.get_object(Bucket='dardendifferentialmodeloutput', Key=object.key)
                        print(file['Body'].read())
                        content = open(os.path.join(os.curdir, os.path.basename(file_name)), "rb") #file['Body'].read()
                        response = FileResponse(content)
                        # Auto detection doesn't work with plain text content, so we set the headers ourselves
                        response["Content-Type"] = "text/plain"
                        response["Content-Disposition"] = 'attachment; filename="' + object.key + '"'
                        return response

        except botocore.exceptions.ClientError as e:
            if e.response['Error']['Code'] == "404":
                print("The object does not exist.")
            else:
                raise
        if 'Delete' in request.POST:
            success = "File deleted successfully"
            return HttpResponseRedirect('/display/')
        else:
            success = "Your file has been downloaded!"
        args = {'success': success}
        return render(request, 'display.html', args)
