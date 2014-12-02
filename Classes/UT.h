//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#ifndef _UT_
#define _UT_
#include "cocos2d.h"
#include "Settings.h"
class Sign;
USING_NS_CC;


class UT
{
    public:
	    UT();
	    virtual  ~UT();
        std::string trim(const std::string& str,
                 const std::string& whitespace = " \t");

         std::string reduce(const std::string& str,
                            const std::string& fill = " ",
                            const std::string& whitespace = " \t");


         int getRandomWithInRange(int min,int max);
         int getRandomWithInRangeUsingTime(int min,int max);
         void getRandomUniqueWithInUsingFisherYates(std::vector<int>* &vecOfNumbers);
         int rand_int(int n,int max)  ;
         void shuffle(std::vector<char> &array, int max) ;
         float getScaleFactorBasedOnWinWidth(float winWidth,
                                            Size BoundingBoxSize);


         std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
         std::vector<std::string> split(const std::string &s, char delim); 
		 std::vector<std::string> split(std::string &s, std::string delimiter);

         std::string int_to_string(int num);
         std::string ConstractTimeView(float sec,LevelDataHolder& levelDataHolder);
         void appendCubicBezier(int startPoint, std::vector<Vec2>& verts,
                           const Vec2& from, const Vec2& control1,
                           const Vec2& control2, const Vec2& to, uint32_t segments);
         Node* createRoundedRectMaskNode(Size size, 
                                    float radius, float borderWidth, int cornerSegments);
         Sprite* setFacebookIcon();
         Sprite* setHelpIcon();
          void setSignScalefactor(Sign* &rpSign);
    
};

#endif