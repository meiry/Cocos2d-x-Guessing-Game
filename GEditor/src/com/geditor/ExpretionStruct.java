package com.geditor;

import java.util.LinkedList;
import java.util.Stack;

public class ExpretionStruct
{
	public ExpretionStruct(LinkedList<String > strLinkedList,String imgName,String[] _paramValues,String _suffixCounter)
	{
		StrLinkedList = strLinkedList;
		ImgName = imgName;
		paramValues = _paramValues;
		suffixCounter = _suffixCounter;
		 
	}
	public LinkedList<String > StrLinkedList;
	public String ImgName;
	public String[] paramValues; 
	public String suffixCounter;
}