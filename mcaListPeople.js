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
// Enhancements:
//

'use strict';

const uri = "http://www.risingfast.com/cgi-bin/mcaListPeople.cgi";

// function to ajax fetch all people from the server ------------------------------------------------------------------

async function mcaListPeople() {

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

    if (document.getElementById("people").checked === true) 
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
            filter1 = (document.getElementById("filter").value).toUpperCase();
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
            document.getElementById("message").value="mcaListPeople.cgi fired - showing all (or a filtered list of) people in the ancestry, ascending by Person ID";
            document.getElementById("results").value=text2;
        }
    }

// show a person's profile if the profile option is chosen ------------------------------------------------------------

    else if (document.getElementById("profiles").checked === true) 
    {
        PersonIDValue = document.getElementById("personID").value;
        if (PersonIDValue.length === 0)
        {
            document.getElementById("message").value= "A Person ID is required if the Profile option is selected";
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
                document.getElementById("message").value="mcaListProfile.cgi fired - showing a person's profile in the ancestry";
                document.getElementById("results").value=text2;
            }
        }

// show a person's reference links if the profile option is chosen ------------------------------------------------------------

        PersonIDValue = document.getElementById("personID").value;
        if (PersonIDValue.length === 0)
        {
            document.getElementById("message").value= "A Person ID is required if the Profile option is selected";
        }
        else
        {
            const uri = "http://www.risingfast.com/cgi-bin/mcaListProfRefLinks.cgi" + "?PersonID=" + PersonIDValue;
            let response = await fetch(uri);
            if (response.ok) {
                text3 = await response.text();
                document.getElementById("message").value="mcaListProfile.cgi and mcaListProfRefLinks fired - showing a person's profile reference links in the ancestry";
                document.getElementById("profreflinks").innerHTML=text3;
            }
        }
    }

// list marriages if the marriages option is chosen -------------------------------------------------------------------

    else if (document.getElementById("marriages").checked === true) 
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
            filter1 = (document.getElementById("filter").value).toUpperCase();
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
            document.getElementById("message").value="mcaListMarriages.cgi fired - showing all (or a filtered list of) marriages in the ancestry";
            document.getElementById("results").value=text2;
        }
    }

// list residents if the residents option is chosen -------------------------------------------------------------------

    else if (document.getElementById("residents").checked === true) 
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
            filter1 = (document.getElementById("filter").value).toUpperCase();
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
            document.getElementById("message").value="mcaListResidents.cgi fired - showing all (or a filtered list of) residents in the ancestry";
            document.getElementById("results").value=text2;
        }
    }

// list references if the references option is chosen -----------------------------------------------------------------

    else if (document.getElementById("references").checked === true) 
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
            filter1 = (document.getElementById("filter").value).toUpperCase();
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
            document.getElementById("message").value="mcaListReferences.cgi fired - showing all (or a filtered list of) references (source documents) in the ancestry";
            document.getElementById("results").value=text2;
        }
    }

// list cohorts if the cohorts option is chosen -----------------------------------------------------------------------

    else if (document.getElementById("cohorts").checked === true) 
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
            filter1 = (document.getElementById("filter").value).toUpperCase();
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
            document.getElementById("message").value="mcaListCohorts.cgi fired - showing the cohort of each  person  with a known birthdate, ascending by Person ID";
            document.getElementById("results").value=text2;
        }
    }

// list birthdays if the birthdays option is chosen -------------------------------------------------------------------

    else if (document.getElementById("birthdays").checked === true) 
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
            filter1 = (document.getElementById("filter").value).toUpperCase();
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
            document.getElementById("message").value="mcaListBirthdays.cgi fired - showing upcoming birthdays, birth dates and months to next birthday";
            document.getElementById("results").value=text2;
        }
    }

// show error if no valid option selected

    else 
    {
        document.getElementById("results").value = "This wasn't supposed to happen!";
    }
}

// function to set form status based on action chosen -----------------------------------------------------------------

function getAction() {

    if (document.getElementById("people").checked === true) {
        document.getElementById("profiles").disabled = false;
        document.getElementById("profiles").required = false;
        document.getElementById("marriages").disabled = false;
        document.getElementById("marriages").required = false;
        document.getElementById("residents").disabled = false;
        document.getElementById("residents").required = false;
        document.getElementById("references").disabled = false;
        document.getElementById("references").required = false;
        document.getElementById("cohorts").disabled = false;
        document.getElementById("cohorts").required = false;
        document.getElementById("birthdays").disabled = false;
        document.getElementById("birthdays").required = false;
        document.getElementById("go").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message").value = "People action selected - click Go or set a filter then click Go to proceed";
        document.getElementById("results").value = "";
        document.getElementById("filter").value = "";
        document.getElementById("personID").value = "";
        document.getElementById("personIDdiv").hidden = true; 
        document.getElementById("filterdiv").hidden = false;
        document.getElementById("profreflinks").innerHTML="";
    }
    if (document.getElementById("profiles").checked === true) {
        document.getElementById("people").disabled = false;
        document.getElementById("people").required = false;
        document.getElementById("marriages").disabled = false;
        document.getElementById("marriages").required = false;
        document.getElementById("residents").disabled = false;
        document.getElementById("residents").required = false;
        document.getElementById("references").disabled = false;
        document.getElementById("references").required = false;
        document.getElementById("cohorts").disabled = false;
        document.getElementById("cohorts").required = false;
        document.getElementById("birthdays").disabled = false;
        document.getElementById("birthdays").required = false;
        document.getElementById("go").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message").value = "Profiles action selected - enter a person ID then click Go to proceed (use the People option to find a Person ID)";
        document.getElementById("personID").style.backgroundColor = "lightyellow"
        document.getElementById("results").value = "";
        document.getElementById("filter").value = "";
        document.getElementById("personID").value = "";
        document.getElementById("personIDdiv").hidden = false; 
        document.getElementById("filterdiv").hidden = true; 
        document.getElementById("profreflinks").innerHTML="";
    } 
    if (document.getElementById("marriages").checked === true) {
        document.getElementById("people").disabled = false;
        document.getElementById("people").required = false;
        document.getElementById("profiles").disabled = false;
        document.getElementById("profiles").required = false;
        document.getElementById("residents").disabled = false;
        document.getElementById("residents").required = false;
        document.getElementById("references").disabled = false;
        document.getElementById("references").required = false;
        document.getElementById("cohorts").disabled = false;
        document.getElementById("cohorts").required = false;
        document.getElementById("birthdays").disabled = false;
        document.getElementById("birthdays").required = false;
        document.getElementById("go").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message").value = "Marriages action selected - click Go or set a filter then click Go to proceed";
        document.getElementById("results").value = "";
        document.getElementById("filter").value = "";
        document.getElementById("personID").value = "";
        document.getElementById("personIDdiv").hidden = true; 
        document.getElementById("filterdiv").hidden = false;
        document.getElementById("profreflinks").innerHTML="";
    }
    if (document.getElementById("residents").checked === true) {
        document.getElementById("people").disabled = false;
        document.getElementById("people").required = false;
        document.getElementById("profiles").disabled = false;
        document.getElementById("profiles").required = false;
        document.getElementById("marriages").disabled = false;
        document.getElementById("marriages").required = false;
        document.getElementById("references").disabled = false;
        document.getElementById("references").required = false;
        document.getElementById("cohorts").disabled = false;
        document.getElementById("cohorts").required = false;
        document.getElementById("birthdays").disabled = false;
        document.getElementById("birthdays").required = false;
        document.getElementById("go").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message").value = "Residents action selected - click Go or set a filter then click Go to proceed";
        document.getElementById("results").value = "";
        document.getElementById("filter").value = "";
        document.getElementById("personID").value = "";
        document.getElementById("personIDdiv").hidden = true; 
        document.getElementById("filterdiv").hidden = false;
        document.getElementById("profreflinks").innerHTML="";
    }
    if (document.getElementById("references").checked === true) {
        document.getElementById("people").disabled = false;
        document.getElementById("people").required = false;
        document.getElementById("profiles").disabled = false;
        document.getElementById("profiles").required = false;
        document.getElementById("marriages").disabled = false;
        document.getElementById("marriages").required = false;
        document.getElementById("residents").disabled = false;
        document.getElementById("residents").required = false;
        document.getElementById("cohorts").disabled = false;
        document.getElementById("cohorts").required = false;
        document.getElementById("birthdays").disabled = false;
        document.getElementById("birthdays").required = false;
        document.getElementById("go").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message").value = "References action selected - click Go or set a filter then click Go to proceed";
        document.getElementById("results").value = "";
        document.getElementById("filter").value = "";
        document.getElementById("personID").value = "";
        document.getElementById("personIDdiv").hidden = true; 
        document.getElementById("filterdiv").hidden = false;
        document.getElementById("profreflinks").innerHTML="";
    }
    if (document.getElementById("cohorts").checked === true) {
        document.getElementById("people").disabled = false;
        document.getElementById("people").required = false;
        document.getElementById("profiles").disabled = false;
        document.getElementById("profiles").required = false;
        document.getElementById("marriages").disabled = false;
        document.getElementById("marriages").required = false;
        document.getElementById("residents").disabled = false;
        document.getElementById("residents").required = false;
        document.getElementById("references").disabled = false;
        document.getElementById("references").required = false;
        document.getElementById("birthdays").disabled = false;
        document.getElementById("birthdays").required = false;
        document.getElementById("go").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message").value = "Cohorts action selected - click Go or set a filter then click Go to proceed";
        document.getElementById("results").value = "";
        document.getElementById("filter").value = "";
        document.getElementById("personID").value = "";
        document.getElementById("personIDdiv").hidden = true; 
        document.getElementById("filterdiv").hidden = false;
        document.getElementById("profreflinks").innerHTML="";
    }
    if (document.getElementById("birthdays").checked === true) {
        document.getElementById("people").disabled = false;
        document.getElementById("people").required = false;
        document.getElementById("profiles").disabled = false;
        document.getElementById("profiles").required = false;
        document.getElementById("marriages").disabled = false;
        document.getElementById("marriages").required = false;
        document.getElementById("residents").disabled = false;
        document.getElementById("residents").required = false;
        document.getElementById("references").disabled = false;
        document.getElementById("references").required = false;
        document.getElementById("cohorts").disabled = false;
        document.getElementById("cohorts").required = false;
        document.getElementById("go").disabled = false;
        document.getElementById("reset").disabled = false;
        document.getElementById("message").value = "Birthdays action selected - click Go or set a filter then click Go to proceed";
        document.getElementById("results").value = "";
        document.getElementById("filter").value = "";
        document.getElementById("personID").value = "";
        document.getElementById("personIDdiv").hidden = true; 
        document.getElementById("filterdiv").hidden = false;
        document.getElementById("profreflinks").innerHTML="";
    }
}

// function to reset fields -------------------------------------------------------------------------------------------

function reset() {
    document.getElementById("people").checked = true;
    document.getElementById("people").disabled = false;
    document.getElementById("profiles").checked = false;
    document.getElementById("profiles").disabled = false;
    document.getElementById("marriages").checked = false;
    document.getElementById("marriages").disabled = false;
    document.getElementById("residents").checked = false;
    document.getElementById("residents").disabled = false;
    document.getElementById("references").checked = false;
    document.getElementById("references").disabled = false;
    document.getElementById("cohorts").checked = false;
    document.getElementById("cohorts").disabled = false;
    document.getElementById("birthdays").checked = false;
    document.getElementById("birthdays").disabled = false;
    document.getElementById("go").disabled = false;
    document.getElementById("reset").disabled = false;
    document.getElementById("message").value = "Reset action selected - all fields are reset";
    document.getElementById("results").value = "Results are reset";
    document.getElementById("filter").value = "";
    document.getElementById("personIDdiv").hidden = true; 
    document.getElementById("filterdiv").hidden = false;
    document.getElementById("profreflinks").innerHTML="";
}

// function to show internal information ------------------------------------------------------------------------------

function showInternals() {
    var y = document.getElementById("internalsDiv");
    if (y.style.display === "none") {
        y.style.display = "block";
    } else {
         y.style.display = "none";
    }
    document.getElementById("Message").value="See internal information below the Internals button. Click Internals again to hide it"
}

// function to show help information --------i-------------------------------------------------------------------------

function showHelp() {
    var x = document.getElementById("helpDiv");
    if (x.style.display === "none") {
        x.style.display = "block";
    } else {
        x.style.display = "none";
    }
    document.getElementById("Message").value="See Help information below the Help button. Click Help again to hide it"
}

// fetch the initial display attribute for the internals division -----------------------------------------------------

var x = document.getElementById("helpDiv");
const stx = getComputedStyle(x);
x.style.display = stx.display;
var y = document.getElementById("internalsDiv");
const sty = getComputedStyle(y);
y.style.display = sty.display;

getAction();

