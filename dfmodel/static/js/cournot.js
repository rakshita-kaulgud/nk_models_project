$(document).ready(function () {
$('#innovation_perc').on("input", function(e){
    var value = $('#innovation_perc').val();
    console.log("val = " + value);
    var isvalid = true;
    if (parseFloat(value) > parseFloat(1)){
        $("#innovation_perc").css("border-color", "red");
        isvalid = false;
        $("#imitation_perc" ).text("Enter value between 0.0 and 1.0");
    } else {
        $("#innovation_perc").css("border-color", "#ced4da");
        isvalid = true;
        $("#imitation_perc" ).text("");
    }
    if (value == null || value == ""){
    $("#imitation_perc" ).text( "" );
    }
    else if (isvalid == true){
        var imitation_val = (1.0 * 100 - value * 100)/100;
        $("#imitation_perc" ).text( "Imitation: " + imitation_val.toFixed(2) );
    }

});
});
//var RegExp = new RegExp(/^\d*\.\d*$/);
var invalidrange = "Range start is greater than Range end";
function validateInputs(){
    var iserror = false;

    Nstart = document.getElementById("N_start");
    Nend = document.getElementById("N_end");
    if (Nend.value < Nstart.value){
        $("#N_start").css("border-color", "red");
        $("#N_end").css("border-color", "red");
        document.getElementById("id-N-error").innerHTML = "Range start for N is greater than Range end for N";
        $("#id-N-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("K_end").value < document.getElementById("K_start").value){
        $("#K_start").css("border-color", "red");
        $("#K_end").css("border-color", "red");
        document.getElementById("id-K-error").innerHTML = "Range start for K is greater than Range end for K";
        $("#id-K-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("num_firms_end").value < document.getElementById("num_firms_start").value){
        $("#num_firms_start").css("border-color", "red");
        $("#num_firms_end").css("border-color", "red");
        document.getElementById("id-firms-error").innerHTML = "Range start is greater than Range end";
        $("#id-firms-error").show();
        if(!iserror){
            iserror = true;
        }
    }
     if (document.getElementById("alpha_end").value < document.getElementById("alpha_start").value){
        $("#alpha_start").css("border-color", "red");
        $("#alpha_end").css("border-color", "red");
        document.getElementById("id-alpha-error").innerHTML = "Range start is greater than Range end";
        $("#id-alpha-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("beta_end").value < document.getElementById("beta_start").value){
        $("#beta_start").css("border-color", "red");
        $("#beta_end").css("border-color", "red");
        document.getElementById("id-beta-error").innerHTML = "Range start is greater than Range end";
        $("#id-beta-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("mutation_end").value < document.getElementById("mutation_start").value){
        $("#mutation_start").css("border-color", "red");
        $("#mutation_end").css("border-color", "red");
        document.getElementById("id-mutation-error").innerHTML = "Range start is greater than Range end";
        $("#id-mutation-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("enter_rule_end").value < document.getElementById("enter_rule_start").value){
        $("#enter_rule_start").css("border-color", "red");
        $("#enter_rule_end").css("border-color", "red");
        document.getElementById("id-enter-rule-error").innerHTML = invalidrange;
        $("#id-enter-rule-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("exit_rule_end").value < document.getElementById("exit_rule_start").value){
        $("#exit_rule_start").css("border-color", "red");
        $("#exit_rule_end").css("border-color", "red");
        document.getElementById("id-exit-rule-error").innerHTML = invalidrange;
        $("#id-exit-rule-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("num_tp").value == "" || document.getElementById("num_tp").value == null){
        document.getElementById("id-tp-error").innerHTML = "This field cannot be empty";
        document.getElementById("id-tp-error").style.visibility = "visible";
        $("#num_tp").css("border-color", "red");
        $("#id-tp-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("num_runs").value == "" || document.getElementById("num_runs").value == null){
        document.getElementById("id-runs-error").innerHTML = "This field cannot be empty";
        document.getElementById("id-runs-error").style.visibility = "visible";
        $("#num_runs").css("border-color", "red");
        $("#id-runs-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("innovation_perc").value == "" || document.getElementById("innovation_perc").value == null){
        document.getElementById("id-rule-param-error").innerHTML = "Rule parameter cannot be empty";
        document.getElementById("id-rule-param-error").style.visibility = "visible";
        $("#innovation_perc").css("border-color", "red");
        $("#id-rule-param-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("innovation_perc").value == "" || document.getElementById("innovation_perc").value == null){
        document.getElementById("id-rule-param-error").innerHTML = "Rule parameter cannot be empty";
        document.getElementById("id-rule-param-error").style.visibility = "visible";
        $("#innovation_perc").css("border-color", "red");
        $("#id-rule-param-error").show();
        if(!iserror){
            iserror = true;
        }
    } else {
        var innovation_perc = document.getElementById("innovation_perc").value;

        if (Number.isInteger(innovation_perc)){
            document.getElementById("id-rule-param-error").innerHTML = "Rule parameter should be a decimal value.";
            document.getElementById("id-rule-param-error").style.visibility = "visible";
            $("#innovation_perc").css("border-color", "red");
            $("#id-rule-param-error").show();
            if(!iserror){
                iserror = true;
            }
        } else {
            innovation_perc = innovation_perc * 1.0;
            console.log(innovation_perc)
            if (parseFloat(innovation_perc) > parseFloat(1.0)){
            //if (innovation_perc < 0.0 && innovation_perc > 1.0){
                document.getElementById("id-rule-param-error").innerHTML = "Rule parameter should be between 0 and 1.";
                document.getElementById("id-rule-param-error").style.visibility = "visible";
                $("#innovation_perc").css("border-color", "red");
                $("#imitation_perc").text("");
                $("#id-rule-param-error").show();
                if(!iserror){
                    iserror = true;
                }

            }
        }
    }

    if (document.getElementById("fudge_factor_end").value < document.getElementById("fudge_factor_start").value){
        $("#fudge_factor_start").css("border-color", "red");
        $("#fudge_factor_end").css("border-color", "red");
        document.getElementById("id-fudgefactor-error").innerHTML = "Range start is greater than Range end";
        $("#id-fudgefactor-error").show();
        if(!iserror){
            iserror = true;
        }
    }

    if (document.getElementById("fudge_factor_end").value > 0.9){
        document.getElementById("id-fudgefactor-error").innerHTML = "Value should be between -0.9 and 0.9";
        $("#fudge_factor_end").css("border-color", "red");
        $("#id-fudgefactor-error").show();
        if(!iserror){
            iserror = true;
        }
    }
    if (document.getElementById("fudge_factor_start").value > 0.9){
        document.getElementById("id-fudgefactor-error").innerHTML = "Value should be between -0.9 and 0.9";
        $("#fudge_factor_start").css("border-color", "red");
        $("#id-fudgefactor-error").show();
        if(!iserror){
            iserror = true;
        }
    }
    if (document.getElementById("fudge_factor_end").value < -0.9){
        document.getElementById("id-fudgefactor-error").innerHTML = "Value should be between -0.9 and 0.9";
        $("#fudge_factor_end").css("border-color", "red");
        $("#id-fudgefactor-error").show();
        if(!iserror){
            iserror = true;
        }
    }
    if (document.getElementById("fudge_factor_start").value < -0.9){
        document.getElementById("id-fudgefactor-error").innerHTML = "Value should be between -0.9 and 0.9";
        $("#fudge_factor_start").css("border-color", "red");
        $("#id-fudgefactor-error").show();
        if(!iserror){
            iserror = true;
        }
    }
    return iserror;
}

function clearErrors(){
    $(".error-field").empty();
     $("input").css('border-color', '#ced4da');
    $(".error-field").hide();
    $("#imitation_perc").text("");
}
function prepForSubmit(){
    clearErrors();
    var iserror = validateInputs();
    console.log("hi")

    if (iserror == false){
    var numTasksStart = document.getElementById("N_start").value;
    document.getElementById('numTasksStart').value = numTasksStart;
    var numTasksEnd = document.getElementById("N_end").value;
    document.getElementById('numTasksEnd').value = numTasksEnd;

    var numInterationsStart = document.getElementById("K_start").value;
    document.getElementById('numInteractionsStart').value = numInterationsStart;
    var numInterationsEnd = document.getElementById("K_end").value;
    document.getElementById('numInteractionsEnd').value = numInterationsEnd;

    var numFirmsStart = document.getElementById("num_firms_start").value;
    document.getElementById('numFirmsStart').value = numFirmsStart;
    var numFirmsEnd = document.getElementById('num_firms_end').value;
    document.getElementById('numFirmsEnd').value = numFirmsEnd;

    var alphaStart = document.getElementById("alpha_start").value;
    document.getElementById('alphaStart').value = alphaStart;
    var alphaEnd = document.getElementById('alpha_end').value;
    document.getElementById('alphaEnd').value = alphaEnd;

    var betaStart = document.getElementById("beta_start").value;
    document.getElementById('betaStart').value = betaStart;
    var betaEnd = document.getElementById('beta_end').value;
    document.getElementById('betaEnd').value = betaEnd;

    var enterRuleStart = document.getElementById("enter_rule_start").value;
    document.getElementById('enterRuleStart').value = enterRuleStart;
    var enterRuleEnd = document.getElementById('enter_rule_end').value;
    document.getElementById('enterRuleEnd').value = enterRuleEnd;

    var exitRuleStart = document.getElementById("exit_rule_start").value;
    document.getElementById('exitRuleStart').value = exitRuleStart;
    var exitRuleEnd = document.getElementById('exit_rule_end').value;
    document.getElementById('exitRuleEnd').value = exitRuleEnd;

    var mutationStart = document.getElementById("mutation_start").value;
    document.getElementById('mutationStart').value = mutationStart;
    var mutationEnd = document.getElementById('mutation_end').value;
    document.getElementById('mutationEnd').value = mutationEnd;

    var num_tp = document.getElementById("num_tp").value;
    document.getElementById('numTimePeriods').value = num_tp;

    var num_runs = document.getElementById('num_runs').value;
    document.getElementById('numRuns').value = num_runs;

    var ruleParams = document.getElementById('innovation_perc').value;
    console.log("rule param = " + ruleParams);
    document.getElementById('ruleParams').value = ruleParams; //not needed

    var techParams = document.getElementById('newtech_adoption_perc').value;
    console.log("tech param = " + techParams);
    document.getElementById('techParams').value = techParams; //not needed

    var fudgeFactorStart = document.getElementById('fudge_factor_start').value;
    console.log("fudgeFactorStart = " + fudgeFactorStart);
    document.getElementById('fudgeFactorStart').value = fudgeFactorStart;

    var fudgeFactorEnd = document.getElementById('fudge_factor_end').value;
    console.log("fudgeFactorEnd = " + fudgeFactorEnd);
    document.getElementById('fudgeFactorEnd').value = fudgeFactorEnd;

    var form = document.forms['cournot-form'];
    form.submit();
    }

}