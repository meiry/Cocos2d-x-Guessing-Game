<%@ page  import="com.geditor.*,java.util.*" %>
<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<style type="text/css"> 
.main_container {
  
  height: 100%;
  width:100%;
  border: 0px solid;
}
.TextBoxDivClass
{
   
  width: 300px;
  height:400px; 
  border: 1px solid;
  overflow:hidden; 
  display: inline-block;
}

.img_holder {
  float: left;
  width: 250px;
  height:250px; 
  padding: 0px;
  border: 1px solid;
  text-align: center;
  margin-top: 0px;
  margin-left: 0px;  
}

.txt_holder {
  float: auto; 
  padding: 0px;  
  text-align: right;
  margin-top: auto;
  margin-left: 50px; 
   
}
</style>
<script src="jquery-1.11.1.min.js"></script>
<script type='text/javascript'>
function readURL(input,imageValuStripet) {
	
	var arr = input.name.split('_');
	previewHolderNum = arr[arr.length-1];
	
    if (input.files && input.files[0]) {
    	var previewHolderName = "previewHolder_"+previewHolderNum;
        var reader = new FileReader();
        reader.onload = function(e) {
        	 
            $('#'+previewHolderName).attr('src', e.target.result);
             $('#imagetotxt_' + previewHolderNum).attr('value',imageValuStripet) ;
        }

        reader.readAsDataURL(input.files[0]);
    }
}

var filenameHandler=function(extension){
    var s= extension.replace(/\\/g, '/');
    s= s.substring(s.lastIndexOf('/')+ 1);
    return extension? s.replace(/[?#].+$/, ''): s.split('.')[0];
}
 
$(document).ready(function() {
	var iCounter = 0;
	$('#langcheckhebrew').attr('checked', 'checked'); 
	$('#lang').attr('value', 'heb');
    $(document).on('change','#fileOpen',function() 
    {
    	 
		var name1 = $(this).attr("name");
		var imageValue = $(this).val();
		var imageValuStripet =  filenameHandler(imageValue);
		 
		 
        readURL(this,imageValuStripet);
    });
    
    var AddLevelTohtml = function() 
    {
    	
    	var newTextBoxDiv = $(document.createElement('div'))
	     .attr("id", 'TextBoxDiv_' + iCounter);
		 newTextBoxDiv.attr("class", 'TextBoxDivClass');

		newTextBoxDiv.after().html('<label>Textbox #'+ iCounter + ' : </label><br/>' +
			  '<input type="file" id="fileOpen" name="fileOpen_' + iCounter + '"  value="add Image" accept="image/png"/>' +
			  '<input type="hidden" value="" id="imagetotxt_' + iCounter + '" name="imagetotxt_' + iCounter + '" />' +
			  '<img id="previewHolder_' + iCounter + '"  alt="Uploaded Image Preview Holder" width="250px" height="250px" class="img_holder" /><br/>'+	
		      '<input class="txt_holder" type="text" size="20" maxlength="10" name="textbox_' + iCounter + '" id="textbox_' + iCounter + '" value="" ><br/>'+
		      '<input class="txt_holder" type="text" size="20" maxlength="10" name="textbox_' + iCounter + '" id="textbox_' + iCounter + '" value="" ><br/>'+
		      '<input class="txt_holder" type="text" size="20" maxlength="10" name="textbox_' + iCounter + '" id="textbox_' + iCounter + '" value="" ><br/>' 
		      
		      );

		newTextBoxDiv.appendTo("#searchForm");
		iCounter++;
        
    	
    	
    };
    
    
	$("#add_Level").click(function(){
		AddLevelTohtml();
		
    });
	$("#add_Level_2").click(function(){
		AddLevelTohtml();
		
    });
    
	$("#Remove_Level").click(function () {
		if(iCounter==0){
	          alert("No more textbox to remove");
	          return false;
	    }   
	 
		iCounter--;
	 
	    $("#TextBoxDiv_" + iCounter).remove();
	 
	});
	$("#Remove_Level_2").click(function () {
		if(iCounter==0){
	          alert("No more textbox to remove");
	          return false;
	    }   
	 
		iCounter--;
	 
	    $("#TextBoxDiv_" + iCounter).remove();
	 
	});
	
	$('#save_set').click(function(e){
		 
		e.preventDefault();
		//alert($( "#searchForm" ).serialize());
		if (window.confirm("Are you sure?")) {
			$.post('geditor',$( "#searchForm" ).serialize() ,function(rsp){
				//alert(rsp);
				$('#text_result').text(rsp);
			});
		}
		
		return false;
	}); 
	 
    $("*[type='radio']").change(function(){
        //alert($(this).is(':checked')); 
        if($(this).attr('value')=='english')
        {
        	$('#lang').attr('value', 'en');
        }
        else if($(this).attr('value')=='hebrew')
        {
        	$('#lang').attr('value', 'heb');
        }
     });

	 
});
</script>
<title>GEditor</title>
</head>
<body>
<div style="background-color:orange;text-align:left">
  <p>
    <input type ="button" id="add_Level" value="Add Level +"/>
	<input type ="button" id="Remove_Level" value="Remove Level -"/>
 </p>
</div>
<form  action="geditor"  id="searchForm" method="get">
<div  id="main_container" class="container" >
<input type="hidden" id="lang" name="lang" value=""/>
<div>
    <input type="radio" name="langcheck" class='rg' value="english" id="langcheckenglish">
    <label for="english">English</label>
  </div>
  <div>
    <input type="radio" name="langcheck" class='rg' value="hebrew" id="langcheckhebrew"  >
    <label for="hebrew">Hebrew</label>
  </div>
  
  <div id="log"></div>
<div style="background-color:DarkGreen;text-align:left">
  <p>
	<input type ="submit" id="save_set" value="Save set"/>
 </p>
</div>
</form>

 </div>
 <div style="background-color:orange;text-align:left">
  <p>
    <input type ="button" id="add_Level_2" value="Add Level +"/>
	<input type ="button" id="Remove_Level_2" value="Remove Level -"/>
 </p>
</div>
<textarea cols='100' rows='20' id='text_result'>


 

</textarea>
</body>
</html>