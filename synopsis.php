<html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=yes">
<script src="https://code.jquery.com/jquery-1.12.4.min.js"
integrity="sha256-ZosEbRLbNQzLpnKIkEdrPv7lOy9C27hHQ+Xp8a4MxAQ="
crossorigin="anonymous"></script>
<script>
    // Check for wasm support.
    if (!('WebAssembly' in window)) {
      alert('you need a browser with wasm support enabled :(');
    }

    // Loads a WebAssembly dynamic library, returns a promise.
    // imports is an optional imports object
    function loadWebAssembly(filename, imports) {
      // Fetch the file and compile it
const importObject = {
  imports: {
    imported_func: function(arg) {
      console.log(arg);
    }
  }
};
      return fetch(filename)
        .then(response => response.arrayBuffer())
        .then(buffer => WebAssembly.compile(buffer))
        .then(module => {
          // Create the instance.
          return WebAssembly.instantiate(module);
        });
    }

var myArray;
var accentSyllable2;
    // Main part of this example, loads the module and uses it.
    loadWebAssembly('accent.wasm')
      .then(instance => {
        var exports = instance.exports; // the exports of that instance
        accentSyllable2 = exports.accentSyllable2; // the "doubler" function (note "_" prefix)
        var memory = exports.memory;

        myArray = new Uint16Array(memory.buffer, 0, 1024);

        // now we are ready, set up the button so the user can run the code
        //var button = document.getElementById('b');
        //button.value = 'Call a method in the WebAssembly module';
        //button.addEventListener('click', test);
      }
    );

//https://wasmbyexample.dev/examples/strings/strings.c.en-us.html
//emcc -std=gnu99 -s STANDALONE_WASM -s EXPORTED_FUNCTIONS="['_accentSyllable2']" -Wl,--no-entry "utilities.c" "accent.c" -o "accent.wasm"
//https://stackoverflow.com/questions/3923089/can-i-conditionally-change-the-character-entered-into-an-input-on-keypress/3923320#3923320
//https://gist.github.com/kripken/59c67556dc03bb6d57052fedef1e61ab

var la = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"];
var gr = ["α","β","ψ","δ","ε","φ","γ","η","ι","ξ","κ","λ","μ","ν","ο","π","","ρ","σ","τ","θ","ω","ς","χ","υ","ζ","Α","Β","Ψ","Δ","Ε","Φ","Γ","Η","Ι","Ξ","Κ","Λ","Μ","Ν","Ο","Π","","Ρ","Σ","Τ","Θ","Ω","Σ","Χ","Υ","Ζ"];

var forceLowercase = true;

function transliterate(char)
{
	var theChar = (forceLowercase) ? char.toLowerCase() : char;
	var idx = la.indexOf(theChar);
	if (idx > -1)
	{
		return gr[idx];
	}
	else
	{
		return char;
	}
}

function transformTypedChar(origChars, key) {
	var len = origChars.length;
	var debug = "Before: ";
	for (var i = 0; i < len; i++) {
		myArray[i] = origChars.codePointAt(i);
		debug += myArray[i].toString(16) + ", ";
	}
	debug += "len: " + len;
	console.log(debug);

    
    len = accentSyllable2(myArray.byteOffset, len, key, 1, 2);


	var newLetter = "";
	var debug = "After: ";
	for (var i = 0; i < len; i++) {
		newLetter += String.fromCodePoint(myArray[i]);
		debug += myArray[i].toString(16) + ", ";
	}
	debug += "len: " + len;
	console.log(debug);

    return [len, newLetter];
}

function accentSyllable(evt) {
    var val = this.value;
    evt = evt || window.event;

    var charCode = typeof(evt.which) == "number" ? evt.which : evt.keyCode;
    //console.log(charCode);

    if (charCode && charCode > 64 && charCode < 123)
    {
	    var start = this.selectionStart;
        var end = this.selectionEnd;
    	var key = String.fromCharCode(charCode);

    	var mappedChar = transliterate(key);
    	var charsToReplace = 0;
	    this.value = val.slice(0, start - charsToReplace) + mappedChar + val.slice(end);
        // Move the caret
        this.selectionStart = this.selectionEnd = start + 1 - charsToReplace;
        return false;
    }
    else if (charCode && charCode > 47 && charCode < 58) { //0-9 are 48-57
        var key = String.fromCharCode(charCode);

        var start, end;
        if (typeof(this.selectionStart) == "number" && typeof(this.selectionEnd) == "number") {
        	//console.log("1111");
            // Non-IE browsers and IE 9
            start = this.selectionStart;
            end = this.selectionEnd;

            // Transform typed character
            var hckey = 0;
            switch( parseInt(key) ) {
                case 1:
                    hckey = 5;
                    break;
                case 2:
                    hckey = 6;
                    break;
                case 3:
                    hckey = 1;
                    break;
                case 4:
                    hckey = 3;
                    break;
                case 5:
                    hckey = 2;
                    break;
                case 6:
                    hckey = 4;
                    break;
                case 7:
                    hckey = 10;
                    break;
                case 8:
                    hckey = 7;
                    break;
                case 9:
                    hckey = 9;
                    break;
                case 0:
                    hckey = 1;
                    break;
            }
            var combining = [0x0300, 0x0301, 0x0304, 0x0306, 0x0308, 0x0313, 0x0314, 0x0323, 0x0342, 0x0345];
            var off = 1;
            for (var i = start; i > -1; i--)
            {
            	if (combining.indexOf(val.codePointAt(i - 1)) > -1)
            	{
            		off++;
            		//alert( val.codePointAt(i - 1));// == 0x0345)
            	}
            	else
            	{
            		break;
            	}
            }
	        var ret = transformTypedChar(val.slice(start - off, start), hckey.toString());
	        var mappedChar = ret[1];
	        var charsToReplace = start - (start - off);//ret[0];
 
            if (ret[0] > 0 && mappedChar != "")
            {
	            this.value = val.slice(0, start - charsToReplace) + mappedChar + val.slice(end);
	            // Move the caret
	            console.log("start: " + start + ", old: " + charsToReplace + ", " + ret[0]);
	            this.selectionStart = this.selectionEnd = (start - charsToReplace) + ret[0];
        	}

        } else if (document.selection && document.selection.createRange) {
        	//console.log("2222");
            // For IE up to version 8
            var selectionRange = document.selection.createRange();
            var textInputRange = this.createTextRange();
            var precedingRange = this.createTextRange();
            var bookmark = selectionRange.getBookmark();
            textInputRange.moveToBookmark(bookmark);
            precedingRange.setEndPoint("EndToStart", textInputRange);
            start = precedingRange.text.length;
            end = start + selectionRange.text.length;

            // Transform typed character
	        var ret = transformTypedChar(val.slice(start - 1, start), key);
	        var mappedChar = ret[1];
	        var charsToReplace = ret[0];

            if (charsToReplace > 0 && mappedChar != "")
            {
	            this.value = val.slice(0, start) + mappedChar + val.slice(end);
	            start++;

	            // Move the caret
	            textInputRange = this.createTextRange();
	            textInputRange.collapse(true);
	            textInputRange.move("character", start - (this.value.slice(0, start).split("\r\n").length - 1));
	            textInputRange.select();
	        }
        }
        return false;
    }
    return true;
}

function start() {
	$(".gkinput").keypress(accentSyllable);
	$("#submitbutton").click(submitSynopsis);
}

function submitSynopsis()
{
	var json = new Object();
	json.r = new Array();
	$(".gkinput").each(function(){	
		//alert(parseInt(this.id.substring(6)));
		json.r[ parseInt(this.id.substring(6)) ] = this.value.trim();
	});
	
	//console.log(JSON.stringify(json));

    $.ajax({
		url: "synopsissave.php",
		type: "POST",
		data: {rese:JSON.stringify(json)},
		dataType: "text",//JSON automatically deserializes json
		success: function (data, textStatus, jqXHR){ 
			//procResponse(data, textStatus); 
			//showToast("success: " + data);
			//alert(data);
		},
		error: function(response) {
			//getwords(url); //redo request on error
			//showToast("error");
			//alert(response);
		}
    });

	//alert(JSON.stringify(json));
}

</script>
<style>
@font-face {
  font-family: 'WebNewAthenaUnicode';
  src: url('/newathu5.ttf') format('truetype');
}  
.gkinput {
	width: 100%;
	height: 40px;
	font-size: 20pt;
	border-radius: 6px;
	margin: 5px;
	padding-left: 9px;
	border: 0px solid #666;
	font-family: NewAthenaUnicode, WebNewAthenaUnicode,helvetica,arial;
}
.colheader {
	text-align:center;
	padding-top:25px;
}
BODY {
	font-family:helvetica,arial;
	background-color:#ddd;
	width:1024px;
	margin:10px auto;
}
.formcell {padding:0px 6px;}
.tophelp td { text-align:center;
width: 11%;
border: 1px solid black;
padding: 3px;
}
</style>
</head>
<body onload="start()">
	<table class="tophelp" cellpadding=0 cellspacing=0 style="border:1px solid black;width:100%;">
	<tr>
		<td>rough breathing</td><td>smooth breathing</td><td>acute</td><td>grave</td><td>circumflex</td><td>macron</td><td>breve</td><td>iota subscript</td><td>diaeresis</td>
	</tr>
	<tr><td>1</td><td>2</td><td>3</td><td>4</td><td>5</td><td>6</td><td>7</td><td>8</td><td>9</td>
	</tr>
</table>

	<h3>Synopsis of: <u>ἵστημι 2nd sing.</u></h3>
	<button id="submitbutton">Submit</button>

	<table cellpadding=0 cellspacing=0 style="width:94%;margin:0px auto;">
		<tr>
			<td>Principal Parts</td>
			<td colspan=3  class="formcell">
				<input type="text" id="pppppp0" class="gkinput"/>
			</td>
		</tr>
		<tr><td></td><td class="colheader">Active</td><td class="colheader">Middle</td><td class="colheader">Passive</td></tr>

<?php
$template = <<<EOT
<tr><td>%LABEL%</td>
	<td class="formcell">
		<input type="text" id="gkform%IDa%" class="gkinput"/>
	</td>
	<td class="formcell">
		<input type="text" id="gkform%IDb%" class="gkinput"/>
	</td>
	<td class="formcell">
		<input type="text" id="gkform%IDc%" class="gkinput"/>
	</td>
</tr>
EOT;

$rows = ["Present Indicative", "Future Indicative", "Imperfect Indicative", "Aorist Indicative", "Perfect Indicative", "Pluperfect Indicative", "Present Subjunctive", "Aorist Subjunctive", "Present Optative", "Future Optative", "Aorist Optative","Present Imperative", "Aorist Imperative", "Present Infinitive", "Aorist Infinitive", "Perfect Infinitive", "Present Partciple", "Future Participle", "Aorist Participle", "Perfect Participle"];
$n = 1;
for ($i = 0; $i < count($rows); $i++)
{
	$a = str_replace("%LABEL%", $rows[$i], $template);
	$a = str_replace("%IDa%", $n++, $a);
	$a = str_replace("%IDb%", $n++, $a);
	$a = str_replace("%IDc%", $n++, $a);
	echo $a;
}
?>
	</table>

	<div class="tophelp" style="display:none;">
		<table cellpadding=0 cellspacing=0>
			<tr><td>rough breathing</td><td>1</td></tr>
			<tr><td>smooth breathing</td><td>2</td></tr>
			<tr><td>acute</td><td>3</td></tr>
			<tr><td>grave</td><td>4</td></tr>
			<tr><td>circumflex</td><td>5</td></tr>
			<tr><td>macron</td><td>6</td></tr>
			<tr><td>breve</td><td>7</td></tr>
			<tr><td>iota subscript</td><td>8</td></tr>
			<tr><td>diaeresis</td><td>9</td></tr>
		</table>


</body>
</html>
