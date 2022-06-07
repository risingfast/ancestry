// mcaListPeople.js
// Author: Geoffrey Jarman
// References: 
//      https://www.youtube.com/watch?v=_5yhmkDQqIQ&list=PLyuRouwmQCjmQTKvgqIgah03HF1wrYkA9&index=14
//      https://medium.com/@dtkatz/3-ways-to-fix-the-cors-error-and-how-access-control-allow-origin-works-d97d55946d9
// Log:
//    04-Aug-2021 started
//    06-Aug-2021 implemented test of retrieving all peopole
//    10-Aug-2021 add filter to all person listing
//    11-Aug-2021 revise for changes in mcaListPeople.html to revert main menu and compress choices
//    11-Aug-2021 change file name to mcaListPeople.js
//    15-Aug-2021 add filters to all listings
//    15-Aug-2021 use the hidden option to change the behaviour of the filter/person ID text box divisions
//    19-Aug-2021 add PersonID division to reset button action
//    23-Aug-2021 clear references region when choosing a new action
//    26-Aug-2021 minor changes and fixes to verbiage in messages
//    09-Sep-2021 add function to support button to reveal background image
//    14-Sep-2021 changes to troubleshoot grid layout on ancestry
//    15-Sep-2021 fix the personIDdiv reference for the profile CGI call
//    15-Sep-2021 fix focus unhiding elements
//    16-Sep-2021 changes to messages with technical references removed
//    16-Sep-2021 change error message to red
//    12-May-2022 change "none" to "" for x.style.display in fShowHelp()
//    15-May-2022 remove fShowHelp() moved to common.js
//    31-May-2022 add math.random() to fSetCornerImage()
//    05-Jun-2022 add fSetFocusOnSubmit();

// Enhancements:
//

'use strict';

const uri = "http://www.risingfast.com/cgi-bin/mcaListPeople.cgi";
const uri2 = "http://www.risingfast.com/cgi-bin/setCornerImage.cgi";

// function to ajax fetch all people from the server ------------------------------------------------------------------

async function fMcaListPeople() {

    var arrBuffer = new Array(2);
    var strTemp = "";
    var text1 = "";
    var text2 = "";
    var text3 = "";
    var filter1 = "";
    var i = 0;
    var j = 0;
    var k = 0;
    var PersonIDValue = "";

// list people if the all people option is chosen ---------------------------------------------------------------------

    if (document.getElementById("people-input").checked === true) 
    {
        const uri = "http://www.risingfast.com/cgi-bin/mcaListPeople.cgi";
        let response = await fetch(uri);
        if (response.ok) {
            text1 = await response.text();
            text2 = text1.replace(/\|/g, ", ");
            text1 = text2;
            text2 = text1.replace(/, , , /g, ", ");
            text1 = text2;
            const array1 = text2.split("\n");
            text2 = "";
            filter1 = (document.getElementById("filter-input").value).toUpperCase();
            if(filter1.length != 0)
            {
                 for(i = 0; i < array1.length; i++)
                 {
                     if((array1[i]).toUpperCase().indexOf(filter1) != -1)
                     {
                         text2 = text2 + array1[i] + "\n";
                     }
                 }
            }
            else
            {
                text2 = text1;
            }
            document.getElementById("message-input").value="People listing shown - all (or a filtered list of) people in the ancestry, ascending by Person ID";
            document.getElementById("message-input").style.color= "black";
            document.getElementById("results-textarea").value=text2;
        }
    }

// show a person's profile if the profile option is chosen ------------------------------------------------------------

    else if (document.getElementById("profiles-input").checked === true) 
    {
        PersonIDValue = document.getElementById("personid-input").value;
        if (PersonIDValue.length === 0)
        {
            document.getElementById("message-input").value= "A Person ID is required if the Profile option is selected";
            document.getElementById("message-input").style.color= "red";
        }
        else
        {
            const uri = "http://www.risingfast.com/cgi-bin/mcaListProfile.cgi" + "?PersonID=" + PersonIDValue;
            let response = await fetch(uri);
            if (response.ok) {
                text1 = await response.text();
                text2 = text1.replace(/\|/g, ", ");
                text1 = text2;
                text2 = text1.replace(/, , , /g, ", ");
                document.getElementById("message-input").value="A Person Profile shown - a single person's profile in the ancestry";
                document.getElementById("message-input").style.color="black";
                document.getElementById("results-textarea").value=text2;
            }
        }

// show a person's reference links if the profile option is chosen ------------------------------------------------------------

        PersonIDValue = document.getElementById("personid-input").value;
        if (PersonIDValue.length === 0)
        {
            document.getElementById("message-input").value= "A Person ID is required if the Profile option is selected";
        }
        else
        {
            const uri = "http://www.risingfast.com/cgi-bin/mcaListProfRefLinks.cgi" + "?PersonID=" + PersonIDValue;
            let response = await fetch(uri);
            if (response.ok) {
                text3 = await response.text();
                document.getElementById("message-input").value="A Person's Profile and Reference Links shown - a person's profile and reference links in the ancestry";
                document.getElementById("message-input").style.color="black";
                document.getElementById("references-links").innerHTML=text3;
            }
        }
    }

// list marriages if the marriages option is chosen -------------------------------------------------------------------

    else if (document.getElementById("marriages-input").checked === true) 
    {
        const uri = "http://www.risingfast.com/cgi-bin/mcaListMarriages.cgi";
        let response = await fetch(uri);
        if (response.ok) {
            text1 = await response.text();
            text2 = text1.replace(/\|/g, ", ");
            text1 = text2;
            text2 = text1.replace(/, , , /g, ", ");
            text1 = text2;
            const array1 = text2.split("\n");
            text2 = "";
            filter1 = (document.getElementById("filter-input").value).toUpperCase();
            if(filter1.length != 0)
            {
                 for(i = 0; i < array1.length; i++)
                 {
                     if((array1[i]).toUpperCase().indexOf(filter1) != -1)
                     {
                         text2 = text2 + array1[i] + "\n";
                     }
                 }
            }
            else
            {
                text2 = text1;
            }
            document.getElementById("message-input").value="Marriages and Unions shown - all (or a filtered list of) marriages and unions in the ancestry";
            document.getElementById("message-input").style.color="black";
            document.getElementById("results-textarea").value=text2;
        }
    }

// list residents if the residents option is chosen -------------------------------------------------------------------

    else if (document.getElementById("residents-input").checked === true) 
    {
        const uri = "http://www.risingfast.com/cgi-bin/mcaListResidents.cgi";
        let response = await fetch(uri);
        if (response.ok) {
            text1 = await response.text();
            text2 = text1.replace(/\|/g, ", ");
            text1 = text2;
            text2 = text1.replace(/, , , /g, ", ");
            text1 = text2;
            const array1 = text2.split("\n");
            text2 = "";
            filter1 = (document.getElementById("filter-input").value).toUpperCase();
            if(filter1.length != 0)
            {
                 for(i = 0; i < array1.length; i++)
                 {
                     if((array1[i]).toUpperCase().indexOf(filter1) != -1)
                     {
                         text2 = text2 + array1[i] + "\n";
                     }
                 }
            }
            else
            {
                text2 = text1;
            }
            document.getElementById("message-input").value="Residents shown - all (or a filtered list of) residents and their addresses in the ancestry";
            document.getElementById("message-input").style.color="black";
            document.getElementById("results-textarea").value=text2;
        }
    }

// list references if the references option is chosen -----------------------------------------------------------------

    else if (document.getElementById("references-input").checked === true) 
    {
        const uri = "http://www.risingfast.com/cgi-bin/mcaListReferences.cgi";
        let response = await fetch(uri);
        if (response.ok) {
            text1 = await response.text();
            text2 = text1.replace(/\|/g, ", ");
            text1 = text2;
            text2 = text1.replace(/, , , /g, ", ");
            text1 = text2;
            const array1 = text2.split("\n");
            text2 = "";
            filter1 = (document.getElementById("filter-input").value).toUpperCase();
            if(filter1.length != 0)
            {
                 for(i = 0; i < array1.length; i++)
                 {
                     if((array1[i]).toUpperCase().indexOf(filter1) != -1)
                     {
                         text2 = text2 + array1[i] + "\n";
                     }
                 }
            }
            else
            {
                text2 = text1;
            }
            document.getElementById("message-input").value="References shown - all (or a filtered list of) references (source documents) in the ancestry";
            document.getElementById("message-input").style.color="black";
            document.getElementById("results-textarea").value=text2;
        }
    }

// list cohorts if the cohorts option is chosen -----------------------------------------------------------------------

    else if (document.getElementById("cohorts-input").checked === true) 
    {
        const uri = "http://www.risingfast.com/cgi-bin/mcaListCohorts.cgi";
        let response = await fetch(uri);
        if (response.ok) {
            text1 = await response.text();
            text2 = text1.replace(/\|/g, ", ");
            text1 = text2;
            text2 = text1.replace(/, , , /g, ", ");
            text1 = text2;
            const array1 = text2.split("\n");
            text2 = "";
            filter1 = (document.getElementById("filter-input").value).toUpperCase();
            if(filter1.length != 0)
            {
                 for(i = 0; i < array1.length; i++)
                 {
                     if((array1[i]).toUpperCase().indexOf(filter1) != -1)
                     {
                         text2 = text2 + array1[i] + "\n";
                     }
                 }
            }
            else
            {
                text2 = text1;
            }
            document.getElementById("message-input").value="Cohorts shown - the cohort of each  person  with a known birthdate, ascending by Person ID";
            document.getElementById("message-input").style.color="black";
            document.getElementById("results-textarea").value=text2;
        }
    }

// list birthdays if the birthdays option is chosen -------------------------------------------------------------------

    else if (document.getElementById("birthdays-input").checked === true) 
    {
        const uri = "http://www.risingfast.com/cgi-bin/mcaListBirthdays.cgi";
        let response = await fetch(uri);
        if (response.ok) {
            text1 = await response.text();
            text2 = text1.replace(/\|/g, ", ");
            text1 = text2;
            text2 = text1.replace(/, , , /g, ", ");
            text1 = text2;
            const array1 = text2.split("\n");
            text2 = "";
            filter1 = (document.getElementById("filter-input").value).toUpperCase();
            if(filter1.length != 0)
            {
                 for(i = 0; i < array1.length; i++)
                 {
                     if((array1[i]).toUpperCase().indexOf(filter1) != -1)
                     {
                         text2 = text2 + array1[i] + "\n";
                     }
                 }
            }
            else
            {
                text2 = text1;
            }
            document.getElementById("message-input").value="Birthdays shown - an ordered list of upcoming birthdays, birth dates and count of months to next birthday";
            document.getElementById("message-input").style.color="black";
            document.getElementById("results-textarea").value=text2;
        }
    }

// show error if no valid option selected

    else 
    {
        document.getElementById("results-textarea").value = "This wasn't supposed to happen!";
    }
}

// function to set form status based on action chosen -----------------------------------------------------------------

function fGetAction() {

    if (document.getElementById("people-input").checked === true) {
        document.getElementById("profiles-input").disabled = false;
        document.getElementById("profiles-input").required = false;
        document.getElementById("marriages-input").disabled = false;
        document.getElementById("marriages-input").required = false;
        document.getElementById("residents-input").disabled = false;
        document.getElementById("residents-input").required = false;
        document.getElementById("references-input").disabled = false;
        document.getElementById("references-input").required = false;
        document.getElementById("cohorts-input").disabled = false;
        document.getElementById("cohorts-input").required = false;
        document.getElementById("birthdays-input").disabled = false;
        document.getElementById("birthdays-input").required = false;
        document.getElementById("options-button").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message-input").value = "People action selected - click 'Submit' or set a filter then click 'Submit' to proceed";
        document.getElementById("results-textarea").value = "";
        document.getElementById("filter-input").value = "";
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
    }
    if (document.getElementById("profiles-input").checked === true) {
        document.getElementById("people-input").disabled = false;
        document.getElementById("people-input").required = false;
        document.getElementById("marriages-input").disabled = false;
        document.getElementById("marriages-input").required = false;
        document.getElementById("residents-input").disabled = false;
        document.getElementById("residents-input").required = false;
        document.getElementById("references-input").disabled = false;
        document.getElementById("references-input").required = false;
        document.getElementById("cohorts-input").disabled = false;
        document.getElementById("cohorts-input").required = false;
        document.getElementById("birthdays-input").disabled = false;
        document.getElementById("birthdays-input").required = false;
        document.getElementById("options-button").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message-input").value = "Profiles action selected - enter a Person ID then click 'Submit' to proceed (use the People option to find a Person ID)";
        document.getElementById("personid-input").style.backgroundColor = "lightyellow"
        document.getElementById("results-textarea").value = "";
        document.getElementById("filter-input").value = "";
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = false; 
        document.getElementById("filter-div").hidden = true; 
        document.getElementById("references-links").innerHTML="";
    } 
    if (document.getElementById("marriages-input").checked === true) {
        document.getElementById("people-input").disabled = false;
        document.getElementById("people-input").required = false;
        document.getElementById("profiles-input").disabled = false;
        document.getElementById("profiles-input").required = false;
        document.getElementById("residents-input").disabled = false;
        document.getElementById("residents-input").required = false;
        document.getElementById("references-input").disabled = false;
        document.getElementById("references-input").required = false;
        document.getElementById("cohorts-input").disabled = false;
        document.getElementById("cohorts-input").required = false;
        document.getElementById("birthdays-input").disabled = false;
        document.getElementById("birthdays-input").required = false;
        document.getElementById("options-button").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message-input").value = "Unions action selected - click 'Submit' or set a filter then click 'Submit' to proceed";
        document.getElementById("results-textarea").value = "";
        document.getElementById("filter-input").value = "";
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
    }
    if (document.getElementById("residents-input").checked === true) {
        document.getElementById("people-input").disabled = false;
        document.getElementById("people-input").required = false;
        document.getElementById("profiles-input").disabled = false;
        document.getElementById("profiles-input").required = false;
        document.getElementById("marriages-input").disabled = false;
        document.getElementById("marriages-input").required = false;
        document.getElementById("references-input").disabled = false;
        document.getElementById("references-input").required = false;
        document.getElementById("cohorts-input").disabled = false;
        document.getElementById("cohorts-input").required = false;
        document.getElementById("birthdays-input").disabled = false;
        document.getElementById("birthdays-input").required = false;
        document.getElementById("options-button").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message-input").value = "Residents action selected - click 'Submit' or set a filter then click 'Submit' to proceed";
        document.getElementById("results-textarea").value = "";
        document.getElementById("filter-input").value = "";
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
    }
    if (document.getElementById("references-input").checked === true) {
        document.getElementById("people-input").disabled = false;
        document.getElementById("people-input").required = false;
        document.getElementById("profiles-input").disabled = false;
        document.getElementById("profiles-input").required = false;
        document.getElementById("marriages-input").disabled = false;
        document.getElementById("marriages-input").required = false;
        document.getElementById("residents-input").disabled = false;
        document.getElementById("residents-input").required = false;
        document.getElementById("cohorts-input").disabled = false;
        document.getElementById("cohorts-input").required = false;
        document.getElementById("birthdays-input").disabled = false;
        document.getElementById("birthdays-input").required = false;
        document.getElementById("options-button").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message-input").value = "References action selected - click 'Submit' or set a filter then click 'Submit' to proceed";
        document.getElementById("results-textarea").value = "";
        document.getElementById("filter-input").value = "";
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
    }
    if (document.getElementById("cohorts-input").checked === true) {
        document.getElementById("people-input").disabled = false;
        document.getElementById("people-input").required = false;
        document.getElementById("profiles-input").disabled = false;
        document.getElementById("profiles-input").required = false;
        document.getElementById("marriages-input").disabled = false;
        document.getElementById("marriages-input").required = false;
        document.getElementById("residents-input").disabled = false;
        document.getElementById("residents-input").required = false;
        document.getElementById("references-input").disabled = false;
        document.getElementById("references-input").required = false;
        document.getElementById("birthdays-input").disabled = false;
        document.getElementById("birthdays-input").required = false;
        document.getElementById("options-button").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message-input").value = "Cohorts action selected - click 'Submit' or set a filter then click 'Submit' to proceed";
        document.getElementById("results-textarea").value = "";
        document.getElementById("filter-input").value = "";
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
    }
    if (document.getElementById("birthdays-input").checked === true) {
        document.getElementById("people-input").disabled = false;
        document.getElementById("people-input").required = false;
        document.getElementById("profiles-input").disabled = false;
        document.getElementById("profiles-input").required = false;
        document.getElementById("marriages-input").disabled = false;
        document.getElementById("marriages-input").required = false;
        document.getElementById("residents-input").disabled = false;
        document.getElementById("residents-input").required = false;
        document.getElementById("references-input").disabled = false;
        document.getElementById("references-input").required = false;
        document.getElementById("cohorts-input").disabled = false;
        document.getElementById("cohorts-input").required = false;
        document.getElementById("options-button").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message-input").value = "Birthdays action selected - click 'Submit' or set a filter then click 'Submit' to proceed";
        document.getElementById("results-textarea").value = "";
        document.getElementById("filter-input").value = "";
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
    }
}

// function to reset fields -------------------------------------------------------------------------------------------

function fReset() {
    document.getElementById("people-input").checked = true;
    document.getElementById("people-input").disabled = false;
    document.getElementById("profiles-input").checked = false;
    document.getElementById("profiles-input").disabled = false;
    document.getElementById("marriages-input").checked = false;
    document.getElementById("marriages-input").disabled = false;
    document.getElementById("residents-input").checked = false;
    document.getElementById("residents-input").disabled = false;
    document.getElementById("references-input").checked = false;
    document.getElementById("references-input").disabled = false;
    document.getElementById("cohorts-input").checked = false;
    document.getElementById("cohorts-input").disabled = false;
    document.getElementById("birthdays-input").checked = false;
    document.getElementById("birthdays-input").disabled = false;
    document.getElementById("options-button").disabled = false;
    document.getElementById("reset").disabled = false;
    document.getElementById("message-input").value = "Reset action selected - all fields are reset";
    document.getElementById("results-textarea").value = "Results are reset";
    document.getElementById("filter-input").value = "";
    document.getElementById("personid-div").hidden = true; 
    document.getElementById("filter-div").hidden = false;
    document.getElementById("references-links").innerHTML="";
    document.getElementById("results-textarea").rows="30";
    document.getElementById("results-textarea").style.width = "80%";
    document.getElementById("message-input").style.color="black";
}

// function to show internal information ------------------------------------------------------------------------------

function fShowInternals() {
    var y = document.getElementById("internalsDiv");
    if (y.style.display === "") {
        y.style.display = "block";
    } else {
         y.style.display = "";
    }
    document.getElementById("message-input").value="See internal information below the Internals button. Click Internals again to hide it";
}

function fResetShows() {
    var x = document.getElementById("helpDiv");
    x.style.display = "";
}

function fShowAncestryHelp() {
    var x = document.getElementById("help-div");
    if (x.style.display === "") {
        x.style.display = "block";
    } else {
        x.style.display = "";
    }
}


// function to ajax fetch the current corner image and captiona

async function fSetCornerImage() {
    let response = await fetch(uri2);
    if (response.ok) {
        let text = await response.text();
        let array = text.split("\n");
        array.pop();                      // remove the last element (empty element) created by the split("\n")
        let intRecords = array.length/3;
        let intRecordSelected = Math.trunc(Math.random() * intRecords);
        document.getElementById("ASIDE2IMG").src=array[intRecordSelected * 3]
        document.getElementById("ASIDE3-PARA").innerHTML=array[(intRecordSelected * 3) + 1];
    } else {
        alert("HttpError: " + response.status);
    }
}

function fSetFocusOnSubmit() {
  document.getElementById("options-button").focus();
}
