package com.geditor;

import java.io.IOException;


import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Enumeration;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.Stack;
import java.util.TreeMap;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;

import com.mongodb.BasicDBObject;


//http://nirlevy.blogspot.co.il/2009/02/utf8-and-hebrew-in-tomcat.html

 
/**
 * Servlet implementation class GEditor
 */
@WebServlet("/geditor")
public class GEditor extends HttpServlet {
	static Logger log = Logger.getLogger(GEditor.class);
	
	private static final long serialVersionUID = 1L;
	private static final String[] heb = new String[22];
	private static TreeMap<String,CharStruct> hebMap = new TreeMap<String,CharStruct>();
	private static TreeMap<String,CharStruct> enMap = new TreeMap<String,CharStruct>();
    private static TreeMap<String,ExpretionStruct >  dataArray = new  TreeMap<String,ExpretionStruct >();
    public enum ExpeelementsTypes {IMAGE,EXPSTR};
    private static String lang =""; 
    PrintWriter out = null;
    /**
     * @see HttpServlet#HttpServlet()
     */
    public GEditor() {
        super();
      //http://www.i18nguy.com/unicode/hebrew.html  
      hebMap.put("u05D0",new CharStruct("heb","",0));
  	  hebMap.put("u05D1",new CharStruct("heb","",1));
  	  hebMap.put("u05D2",new CharStruct("heb","",2));
  	  hebMap.put("u05D3",new CharStruct("heb","",3));
  	  hebMap.put("u05D4",new CharStruct("heb","",4));
  	  hebMap.put("u05D5",new CharStruct("heb","",5));
  	  hebMap.put("u05D6",new CharStruct("heb","",6));
  	  hebMap.put("u05D7",new CharStruct("heb","",7));
  	  hebMap.put("u05D8",new CharStruct("heb","",8));
  	  hebMap.put("u05D9",new CharStruct("heb","",9));  	 
  	  hebMap.put("u05DB",new CharStruct("heb","",10));
  	  hebMap.put("u05DC",new CharStruct("heb","",11));
  	  hebMap.put("u05DE",new CharStruct("heb","",12));
  	  hebMap.put("u05E0",new CharStruct("heb","",13));
  	  hebMap.put("u05E1",new CharStruct("heb","",14));
  	  hebMap.put("u05E2",new CharStruct("heb","",15));
  	  hebMap.put("u05E4",new CharStruct("heb","",16));
  	  hebMap.put("u05E6",new CharStruct("heb","",17));
  	  hebMap.put("u05E7",new CharStruct("heb","",18));
  	  hebMap.put("u05E8",new CharStruct("heb","",19));
  	  hebMap.put("u05E9",new CharStruct("heb","",20));
  	  hebMap.put("u05EA",new CharStruct("heb","",21));
  	 
  	  hebMap.put("u05DA",new CharStruct("heb","",22)); //final chafaf
  	  hebMap.put("u05DD",new CharStruct("heb","",23)); //final mem
  	  hebMap.put("u05DF",new CharStruct("heb","",24)); //final non
  	  hebMap.put("u05E3",new CharStruct("heb","",25)); //pi sofit
  	  hebMap.put("u05E5",new CharStruct("heb","",26)); //tchadik sofit
  	  //A	B	C	D	E	F	G	H	I	J	K	L	M	N	O	P	Q	R	S	T	U	V	W	X	Y	Z

  	  enMap.put("A",new CharStruct("en","",0));
  	  enMap.put("B",new CharStruct("en","",1));
  	  enMap.put("C",new CharStruct("en","",2));
  	  enMap.put("D",new CharStruct("en","",3));
	  enMap.put("E",new CharStruct("en","",4));
	  enMap.put("F",new CharStruct("en","",5));
	  enMap.put("G",new CharStruct("en","",6));
  	  enMap.put("H",new CharStruct("en","",7));
  	  enMap.put("I",new CharStruct("en","",8));
  	  enMap.put("J",new CharStruct("en","",9));
	  enMap.put("K",new CharStruct("en","",10));
	  enMap.put("L",new CharStruct("en","",11));
	  enMap.put("M",new CharStruct("en","",12));
  	  enMap.put("N",new CharStruct("en","",13));
  	  enMap.put("O",new CharStruct("en","",14));
  	  enMap.put("P",new CharStruct("en","",15));
	  enMap.put("Q",new CharStruct("en","",16));
	  enMap.put("R",new CharStruct("en","",17));
	  enMap.put("S",new CharStruct("en","",18));
  	  enMap.put("T",new CharStruct("en","",19));
  	  enMap.put("U",new CharStruct("en","",20));
  	  enMap.put("V",new CharStruct("en","",21));
	  enMap.put("W",new CharStruct("en","",22));
	  enMap.put("X",new CharStruct("en","",23));
	  enMap.put("Y",new CharStruct("en","",24));
  	  enMap.put("Z",new CharStruct("en","",25));
  	   
     
    
     
  	  
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		//MongoDBManager.connectToDb();
		log.debug("Server Started"); 
		
		response.setContentType("text/html");
		response.setCharacterEncoding("utf-8");
	     out = response.getWriter();
	    
 
	    lang = request.getParameter("lang");
	    Enumeration paramNames = request.getParameterNames();
	    while(paramNames.hasMoreElements()) {
	      String paramName = (String)paramNames.nextElement();
	      paramHandler(paramName,request);
	       
    	 
	    }
	    int ii =1;
	    PrintWriter writer = response.getWriter();
        String CollectionOfExpes ="";
	    for(String key : dataArray.keySet())
	    {
	    	ExpretionStruct pExpretionStruct = dataArray.get(key);
	    	String str = "\"";
	    	for(String data : pExpretionStruct.StrLinkedList)
	    	{
	    		str+=data+",";
	    	}
	    	str= str.substring(0,str.length()-1);
	    	str+="\",";
	    	str+="\""+pExpretionStruct.ImgName+"\"";
	    	 
	    	
	    	String commentOrigString = StringArrayToString(pExpretionStruct.paramValues);
	    	insertIntoDB(pExpretionStruct);
	    	String exp= "expressionsMap.insert(std::pair<int,PhraseHolder>("+String.valueOf(ii)+",PhraseHolder("+str+"))); //"+commentOrigString+"\n";
	    	ii+=1;
	    	//TODO 
	    	CollectionOfExpes+=exp;
	    	 
	    }
	     
	    //http://stackoverflow.com/questions/18831659/how-to-redirect-the-response-of-a-servlet-into-the-same-jsp-page-from-where-we-g
    	//http://stackoverflow.com/questions/8627902/new-line-in-text-area
	    if(dataArray.size()>0)
	    {
	    	log.debug(CollectionOfExpes); 
	    	writer.write(CollectionOfExpes);
	    	 
	    }
	    
	   
 		 
	}
	
	private void setExpretionStructIndataArray(String sSuffix,LinkedList<String> stlettersStackResult,String sImgName,ExpeelementsTypes type,String[] _paramValues)
	{
		if(!dataArray.containsKey(sSuffix))
		{
			if(type == ExpeelementsTypes.EXPSTR)
			{
				dataArray.put(sSuffix,new ExpretionStruct(stlettersStackResult,"",_paramValues,sSuffix));
			}
			else if(type == ExpeelementsTypes.IMAGE)
			{
				dataArray.put(sSuffix,new ExpretionStruct(null,sImgName,_paramValues,sSuffix));
			}
		}
		else
		{
			if(type == ExpeelementsTypes.EXPSTR)
			{
				
				dataArray.get(sSuffix).StrLinkedList = stlettersStackResult;
				 
			}
			else if(type == ExpeelementsTypes.IMAGE)
			{
				dataArray.get(sSuffix).ImgName = sImgName;
			}
		}
	}
	
	
	////[textbox_0(arr), add_imagetotxt_0]
	private void paramHandler(String param,HttpServletRequest request)
	{
		LinkedList<String> lettersListResult = new LinkedList<String>(); 
		String[] paramValues = request.getParameterValues(param);
		String suffix = "";
		
		if(param.toLowerCase().contains("textbox_".toLowerCase()))
		{
			suffix = param.split("_")[1];
			if(lang.equalsIgnoreCase("heb"))
			{
				lettersListResult = HandleRightToLeftString(paramValues);
			}
			else
			{
				lettersListResult = HandleLeftToRightString(paramValues);
			}
			setExpretionStructIndataArray(suffix,lettersListResult,"",ExpeelementsTypes.EXPSTR,paramValues);
		}
		else if(param.toLowerCase().contains("imagetotxt_".toLowerCase()))
		{
			suffix = param.split("_")[1];
			String imageName = HandleImage(paramValues);	
			setExpretionStructIndataArray(suffix,null,imageName,ExpeelementsTypes.IMAGE,paramValues);
		}
	}
	public LinkedList<String> HandleLeftToRightString(String[] paramValues)
	{
		  LinkedList<String> lettersList = new LinkedList<String>();
	      for(int i=0;i<paramValues.length;i++)
	      {
	    	  
	    	  String line = paramValues[i].trim();
	    	  if(line.length()==0)
	    	  {
	    		  continue;
	    	  }	
	    	  for(int j=0;j<line.length();j++)
	    	  {
	    		  char ch = line.charAt(j);//String.valueOf(line.charAt(j));
	    		  String s = "";
	    		  String upper = "";
	    		  if(ch !=' ')
	    		  {  
	    			  s = String.valueOf(ch);
	    			  upper = s.toUpperCase();
	    			  try
	    			  {
	    			  CharStruct charStruct= (CharStruct)enMap.get(upper);	      			   
	    			  setLettersList(lettersList,charStruct.sOrderNum);
	    			  }catch(NullPointerException npe)
	    			  {
	    				  System.out.println("ERROR IN :"+upper);
	    			  }
	    		  }
	    		  else
	    		  {
	    			  setLettersList(lettersList,"-");
	    		  }
	    	  }	  
	    	  if(i <paramValues.length-1)
	    	  {
	    		  if(paramValues[i+1].trim().length()>0  )
	    		  {
	    			  setLettersList(lettersList,"|");
	    		  }
	    	  }
	      }
	      
	      
	      
	      return lettersList;
	}
	public LinkedList<String> HandleRightToLeftString(String[] paramValues)
	{
 		 LinkedList<String> lettersList = new LinkedList<String>();
 		 if(lang.equalsIgnoreCase("heb"))
 	  	  {
 			Collections.reverse(Arrays.asList(paramValues));
 	  	  }
 		 
	      for(int i=0;i<paramValues.length;i++)
	      {
	    	  
	    	  String line = paramValues[i].trim();
	    	  if(line.length()==0)
	    	  {
	    		  continue;
	    	  }	
	    	  for(int j=0;j<line.length();j++)
	    	  {
 	    		  char ch = line.charAt(j);//String.valueOf(line.charAt(j));
	    		  String s = "";
	    		  String upper = "";
	    		  if(ch !=' ')
	    		  {  
	    			  s = String.format("%04x", (int) ch);
	    			  upper = s.toUpperCase();
	    			  upper="u"+upper;
	    			  CharStruct charStructheb= (CharStruct)hebMap.get(upper);	    			   
	    			  setLettersList(lettersList,charStructheb.sOrderNum);	    			   
	    		  }
	    		  else
	    		  {
	    			  setLettersList(lettersList,"-");
	    		  }
	    	  }	  
	    	  if(i <paramValues.length-1)
	    	  {
	    		  if(paramValues[i+1].trim().length()>0  )
	    		  {
	    			  setLettersList(lettersList,"|");
	    		  }
	    	  }
	      }
	      
	      
	      
	      return lettersList;
	}
	
	private boolean insertIntoDB(ExpretionStruct pExpretionStruct)
	{
		String[] exp = pExpretionStruct.paramValues;
		String icounter =  pExpretionStruct.suffixCounter;
		String imgname = pExpretionStruct.ImgName;
		
//		BasicDBObject doc = new BasicDBObject("title", "exp").
//		            				append("exp_line_1",exp[0]).
//		            				append("exp_line_2",exp[1]).
//		            				append("exp_line_3",exp[2]).
//		            append("icounter", icounter).
//		            append("imgname",imgname);
//		
//		MongoDBManager.createDocument(doc,"expressions");
		 
		
		return false;
		
	}
	
	private String StringArrayToString(String[] arr)
	{
		StringBuilder builder = new StringBuilder();
		for(String s : arr) {
		    builder.append(s);
		}
		return builder.toString();
	}
	
	private void setLettersList(LinkedList<String> olettersList,String s) {
	  if(lang.equalsIgnoreCase("heb"))
  	  {
		  olettersList.addFirst(s);
  	  }
	  else if(lang.equalsIgnoreCase("en"))
	  {
		olettersList.addLast(s);
	  }
	}

	private String HandleImage(String[] paramValues)
	{
		String sImageName= paramValues[0];
		return sImageName;
	}
	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
		
	}
	 
}
