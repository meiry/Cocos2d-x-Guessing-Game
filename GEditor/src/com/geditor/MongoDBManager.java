package com.geditor;

import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.MongoClient;

public class MongoDBManager {
	static MongoClient mongoClient = null;
	static DB db = null;
	public static void connectToDb()
	{
		 try{   
			 // To connect to mongodb server
		         mongoClient = new MongoClient( "localhost" , 27017 );
		         // Now connect to your databases
		         db = mongoClient.getDB( "geeditor" );
		         System.out.println("Connect to database successfully");
		         
				 
		      }catch(Exception e){
			     System.err.println( e.getClass().getName() + ": " + e.getMessage() );
			  }
	}
	
	public static boolean createDocument(BasicDBObject doc,String collectionName)
	{
		try{ 
			DBCollection coll = db.getCollection(collectionName);
			coll.insert(doc);
			System.out.println("Document inserted successfully");
			return true;
		}catch(Exception e){
		     System.err.println( e.getClass().getName() + ": " + e.getMessage() );
		     return false;
		}
	}
}
