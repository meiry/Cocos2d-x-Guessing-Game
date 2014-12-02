package com.geditor;

public class CharStruct
{
	public CharStruct(String lang,String letter,int n)
	{
		Letter = letter;
		iOrderNum = n;
		sOrderNum = String.valueOf(iOrderNum);
		lang = lang;
	}
	public String Letter;
	public int iOrderNum;
	public String sOrderNum;
	public String lang;
}