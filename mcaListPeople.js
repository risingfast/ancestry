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
//    31-May-2022 add math.random() to fSetCornerImage()
//    05-Jun-2022 add fSetFocusOnSubmit();
//    18-Jun-2022 move fSetCornerImage() to common.js
//    02-Aug-2022 set focus on diifferent fields for each optionchoice
//    31-Aug-2022 add portrait logic to read the json file of portraits
//    01-Sep-2022 remove console log debugs for portraits
//    01-Sep-2022 add a check for no portraits found
//    09-Sep-2022 add fPrintProfile()
//    09-Sep-2022 enable print-button for profiles only


// Enhancements:
//

'use strict';

const uri = "http://www.risingfast.com/cgi-bin/mcaListPeople.cgi";

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

// show portraits if the portraits option is chosen -------------------------------------------------------------------

    else if (document.getElementById("portraits-input").checked === true) 
    {
        PersonIDValue = document.getElementById("personid-input").value;
        const portraitDiv = document.getElementById("portraitsframe-div");
        portraitDiv.innerHTML = '';
        let text1 = "";
        if (PersonIDValue.length === 0)
        {
            document.getElementById("message-input").value= "A Person ID is required if the Profile option is selected";
            document.getElementById("message-input").style.color= "red";
        }
        const uri = "http://www.risingfast.com/cgi-bin/mcaListPortraits.cgi" + "?PersonID=" + PersonIDValue;
        let response = await fetch(uri);
        if (response.ok)
        {
            text1 = await response.text();
            const array1 = text1.split("\n");
            if (array1.length < 2) {
                document.getElementById("message-input").value="No portraits found for this person";
                document.getElementById("message-input").style.color="black";
            } else {
                for (let i = 0; i < array1.length - 1; i++) 
                {
                    let portrait = JSON.parse(array1[i]);
                    portraitDiv.innerHTML = portraitDiv.innerHTML + `<div class = "singleportrait-div">
                                                                         <img src="${portrait['Portrait Path']}" width="150" height="150"><br>
                                                                         <figcaption width="150" height="30">${portrait['Portrait Caption']}</figcaption>
                                                                     </div>`
                }
                document.getElementById("message-input").value="Portraits shown - all portraits for a person";
                document.getElementById("message-input").style.color="black";
                document.getElementById("results-textarea").value=text2;
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
        document.getElementById("portraits-div").hidden = true; 
        document.getElementById("portraitpersonid-div").hidden = true; 
        document.getElementById("results-div").hidden = false;
        document.getElementById("filter-div").hidden = false;
        document.getElementById("jump-div").hidden = false; 
        document.getElementById("jump-input").value = ""; 
        document.getElementById("references-links").innerHTML="";
        document.getElementById("filter-input").focus();
        document.getElementById("print-button").disabled = true;
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
        document.getElementById("results-div").hidden = false;
        document.getElementById("portraits-div").hidden = true; 
        document.getElementById("portraitpersonid-div").hidden = true; 
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = false; 
        document.getElementById("filter-div").hidden = true; 
        document.getElementById("jump-div").hidden = true; 
        document.getElementById("references-links").innerHTML="";
        document.getElementById("personid-input").focus();
        document.getElementById("print-button").disabled = false;
    } 
    if (document.getElementById("portraits-input").checked === true) {
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
        document.getElementById("message-input").value = "Portraits action selected - enter a Person ID then click 'Submit' to proceed (use the People option to find a Person ID)";
        document.getElementById("personid-input").style.backgroundColor = "lightyellow"
        document.getElementById("results-div").hidden = true;
        document.getElementById("personid-div").value = "";
        document.getElementById("personid-div").hidden = true; 
        document.getElementById("portraits-div").hidden = false; 
        document.getElementById("portraitpersonid-div").hidden = false; 
        document.getElementById("filter-div").hidden = true; 
        document.getElementById("jump-div").hidden = true; 
        document.getElementById("references-links").innerHTML="";
        document.getElementById("personid-input").focus();
        document.getElementById("print-button").disabled = true;
        const selectList = document.getElementById("portraitpersonid-select");
        fRemoveAllChildNodes(selectList);
        fFetchPortraitPeople();
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
        document.getElementById("results-div").hidden = false;
        document.getElementById("portraits-div").hidden = true; 
        document.getElementById("portraitpersonid-div").hidden = true; 
        document.getElementById("jump-div").hidden = false; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
        document.getElementById("filter-input").focus();
        document.getElementById("print-button").disabled = true;
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
        document.getElementById("results-div").hidden = false;
        document.getElementById("portraits-div").hidden = true; 
        document.getElementById("portraitpersonid-div").hidden = true; 
        document.getElementById("jump-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
        document.getElementById("print-button").disabled = true;
        document.getElementById("filter-input").focus();
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
        document.getElementById("results-div").hidden = false;
        document.getElementById("portraits-div").hidden = true; 
        document.getElementById("portraitpersonid-div").hidden = true; 
        document.getElementById("jump-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
        document.getElementById("filter-input").focus();
        document.getElementById("print-button").disabled = true;
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
        document.getElementById("results-div").hidden = false;
        document.getElementById("portraits-div").hidden = true; 
        document.getElementById("portraitpersonid-div").hidden = true; 
        document.getElementById("jump-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
        document.getElementById("filter-input").focus();
        document.getElementById("print-button").disabled = true;
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
        document.getElementById("results-div").hidden = false;
        document.getElementById("portraits-div").hidden = true; 
        document.getElementById("portraitpersonid-div").hidden = true; 
        document.getElementById("jump-div").hidden = true; 
        document.getElementById("filter-div").hidden = false;
        document.getElementById("references-links").innerHTML="";
        document.getElementById("filter-input").focus();
        document.getElementById("print-button").disabled = true;
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
    document.getElementById("portraits-div").hidden = true; 
    document.getElementById("portraitpersonid-div").hidden = true; 
    document.getElementById("references-links").innerHTML="";
    document.getElementById("results-textarea").rows="30";
    document.getElementById("results-div").hidden = false;
    document.getElementById("results-textarea").style.width = "80%";
    document.getElementById("message-input").style.color="black";
    document.getElementById("print-button").disabled = true;
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

// function to focus the options button when a filter is entered

function fSetFocusOnSubmit() {
  document.getElementById("options-button").focus();
}

// function to focus the jumpt button when a person id is entered

function fSetFocusOnJump() {
  document.getElementById("jump-button").focus();
}

// function jump to a person's profile from the peopel list jump field

function fonclick_jump_submit() {
    document.getElementById("profiles-input").checked = true;
    document.getElementById("personid-input").value = document.getElementById("jump-input").value;
    fMcaListPeople();
    fGetAction();

}

async function fFetchPortraitPeople() {
    const uri = "http://www.risingfast.com/cgi-bin/mcaListPortraitPeople.cgi";
    let response = await fetch(uri);
    let defaultSelection = '0 Choose';
    var option = document.createElement("option");
    option.text = defaultSelection;
    option.value = '0';
    var defaultSelect = document.getElementById("portraitpersonid-select");
    defaultSelect.appendChild(option);
    if (response.ok) {
        let text1 = await response.text();
        const array1 = text1.split("\n");
        for (let i = 0; i < array1.length - 1; i++) 
        {
            let element = JSON.parse(array1[i]);
            let selection = element['Person ID'] + ' ' + element.Name + ' (' + element.Count + ')';
            var option = document.createElement("option");
            option.text = selection;
            option.value = element['Person ID'];
            var select = document.getElementById("portraitpersonid-select");
            select.appendChild(option);
        }
        document.getElementById("message-input").value="People with portraits listed - choose to show their portraits";
        document.getElementById("message-input").style.color= "black";
    }
    fFetchPortraits();
}

function fRemoveAllChildNodes(parent) {
    while (parent.firstChild) {
        parent.removeChild(parent.firstChild);
    }
}

// fetch portraits----------------------------------------------------------------------------------------

async function fFetchPortraits() {

    let PersonIDValue = document.getElementById("portraitpersonid-select").value;
    const portraitDiv = document.getElementById("portraitsframe-div");
    portraitDiv.innerHTML = '';
    let text1 = "";
    if (PersonIDValue.length === 0)
    {
        document.getElementById("message-input").value= "A Person ID is required if the Profile option is selected";
        document.getElementById("message-input").style.color= "red";
    }
    const uri = "http://www.risingfast.com/cgi-bin/mcaListPortraits.cgi" + "?PersonID=" + PersonIDValue;
    let response = await fetch(uri);
    if (response.ok)
    {
        text1 = await response.text();
        const array1 = text1.split("\n");
        if (array1.length < 2) {
            document.getElementById("message-input").value="No portraits found for this person";
            document.getElementById("message-input").style.color="black";
        } else {
            for (let i = 0; i < array1.length - 1; i++) 
            {
                let portrait = JSON.parse(array1[i]);
                portraitDiv.innerHTML = portraitDiv.innerHTML + `<div class = "singleportrait-div">
                                                                     <img src="${portrait['Portrait Path']}" width="150" height="150"><br>
                                                                     <figcaption width="150" height="30">${portrait['Portrait Caption']}</figcaption>
                                                                 </div>`
            }
            document.getElementById("message-input").value="Portraits shown - all portraits for a person";
            document.getElementById("message-input").style.color="black";
        }
    }
}

function fPrintProfile() {
    let profiletext = document.getElementById("results-textarea").value.replaceAll("\n", "<br />\r\n");
    let restorepage = document.body.innerHTML;
    document.body.innerHTML = profiletext;
    window.print();
    document.body.innerHTML = restorepage;
}
