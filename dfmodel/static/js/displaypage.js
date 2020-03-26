/*function downloadFile(filename){
    console.log("in download file " + filename);
    //formobj.submit();


    url = /downloadFile/;
    data = { file_id : filename}
    $.post(url, data, function(data, status)){
        console.log('${data} and status is ${status}');
    }


/*
//Create an hidden form
var form = $('<form>', {'method': 'POST', 'action': this.href}).hide();

//Add params
var params = { file_id : filename };
$.each(params, function (k, v) {
form.append('{% csrf_token %}');
    form.append($('<input>', {'type': 'hidden', 'name': k, 'value': v}));
});

//Make it part of the document and submit
$('body').append(form);
form.submit();

//Clean up
form.remove();

}*/

function submitForm(filename, formElem){
    console.log("submitting");
    console.log(filename);
    //formElem.closest.form.submit();

    var form = document.createElement("form");
    document.body.appendChild(form);
    form.method = "POST";
    var element1 = document.createElement("<INPUT NAME='file_id' TYPE='hidden' VALUE='"+filename+"'>");
    form.appendChild(element1);

    form.submit();
}