//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\
// developed by meir yanovich meiry242@gmail.com , https://github.com/meiry
//*+*+**+*+**+*+**+*+**+*+**+*+**+*+**+*+*\\

#include "UT.h"
#include "SignFactory.h"
#include "config/ConstAppDefine.h"
#include "Sign.h"

#define SECS_PER_MIN 60
#define SECS_PER_HOUR 3600 

UT::UT()
{
     
}

UT::~UT()
{
	;
}


std::string UT::trim(const std::string& str,
                 const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string UT::reduce(const std::string& str,
                        const std::string& fill,
                        const std::string& whitespace)
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}


int UT::getRandomWithInRange(int min,int max)
{
   //static bool first = true;
   //if ( first ) 
   //{  
   //   srand(time(NULL)); //seeding for the first time only!
   //   first = false;
   //}
   //return min + rand() % (max - min);

   //int ran = rand()%(max - min - 1) + min;
   int ran = rand()%(max - (min-1)) + min;
   return ran;
}
 int UT::getRandomWithInRangeUsingTime(int min,int max)
 {
    srand(time(0));
    int r = rand() % ((max) - min) + min;
    return r;
 }

void UT::getRandomUniqueWithInUsingFisherYates(std::vector<int>* &vecOfNumbers)
{
   auto currentIndexCounter = vecOfNumbers->size();

    for (auto iter = vecOfNumbers->rbegin(); iter != vecOfNumbers->rend();
        iter++, --currentIndexCounter)
    {
        int randomIndex = std::rand() % currentIndexCounter;

        if (*iter != vecOfNumbers->at(randomIndex))
        {
            std::swap(vecOfNumbers->at(randomIndex), *iter);
        }
    }

}

int UT::rand_int(int n,int max) 
{
  int limit = max - max % n;
  int rnd;

  do {
    rnd = rand();
  } while (rnd >= limit);
  return rnd % n;
}

void UT::shuffle(std::vector<char> &charVec,int max) {
  int i, j;
  //char tmp;

  for (i = charVec.size() - 1; i > 0; i--) {
    j = rand_int(i + 1,max);
    char tmp = charVec.at(j);
    charVec.insert(charVec.begin()+j,charVec.at(i));
    charVec.insert(charVec.begin()+i,tmp);
    
  }
}


float UT::getScaleFactorBasedOnWinWidth(float winWidth,
                                        Size BoundingBoxSize)
{
     //calculate the scale of the latter sign
    float LatterWidth = winWidth/10;
    float LatterSidesOffSet = LatterWidth/10;
    Size LatterOrigSize = BoundingBoxSize;
    float latterScaleFactor = (LatterWidth-LatterSidesOffSet) / LatterOrigSize.width;
    return latterScaleFactor;
 
}


std::vector<std::string> &UT::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> UT::split(const std::string &s, char delim) 
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}



std::vector<std::string> UT::split(std::string &s, std::string delimiter)
{
	std::vector<std::string> vec;
 
	auto start = 0U;
    auto end = s.find(delimiter);
	bool hasDelimiter = false;
    while (end != std::string::npos)
    {
        //std::cout << s.substr(start, end - start) << std::endl;
		vec.push_back(s.substr(start, end - start) );
        start = end + delimiter.length();
        end = s.find(delimiter, start);
		
		hasDelimiter = true;
		 
    }
	//if(!hasDelimiter)
	//{
		vec.push_back(s.substr(start, end)); 
	//}


	return vec;
}


std::string UT::int_to_string(int num)
{
    int input = num;
    char buffer[100] = {0};
     
    sprintf(buffer, "%d", input);
    std::string output(buffer);
    return output;
}



std::string UT::ConstractTimeView(float sec,LevelDataHolder& levelDataHolder)
{
    unsigned int seconds, minutes, hours, secs_left, mins_left;
    seconds = static_cast<int>(sec);
    std::string timePassed = "";
    // do some calculations using modulus operator
    hours = seconds / SECS_PER_HOUR;
    minutes = seconds / SECS_PER_MIN;
    mins_left = minutes % SECS_PER_MIN;
    secs_left = seconds % SECS_PER_MIN;
    minutes = minutes % SECS_PER_MIN;
    seconds = seconds % SECS_PER_MIN;
    std::string sHours ="0";
    std::string sMinutes ="0";
    std::string sSeconds ="0";
    //log("now secs_left: %d mins_left:%d seconds:%d\n",secs_left,mins_left,seconds,minutes);
    if(hours<10)
    {
        sHours+= String::createWithFormat("%d",hours)->getCString();
    }
    else
    {
        sHours = String::createWithFormat("%d",hours)->getCString();
    }
    if(minutes<10)
    {
        sMinutes+= String::createWithFormat("%d",minutes)->getCString();
    }
    else
    {
        sMinutes = String::createWithFormat("%d",minutes)->getCString();
    }
    if(seconds<10)
    {
        sSeconds+= String::createWithFormat("%d",seconds)->getCString();
    }
    else
    {
        sSeconds = String::createWithFormat("%d",seconds)->getCString();
    }

    timePassed = sHours+":"+sMinutes+":"+sSeconds;
    levelDataHolder.iHours = hours;
    levelDataHolder.iMinutes = minutes;
    levelDataHolder.iSeconds = seconds;
    return timePassed;
   
}

void UT::appendCubicBezier(int startPoint, std::vector<Vec2>& verts,
                           const Vec2& from, const Vec2& control1,
                           const Vec2& control2, const Vec2& to, uint32_t segments)
{
	float t = 0;
	for(int i = 0; i < segments; i++)
	{
        float x = powf(1 - t, 3) * from.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * to.x;
        float y = powf(1 - t, 3) * from.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * to.y;
        verts[startPoint + i] = Vec2(x,y);
		t += 1.0f / segments;
	}
}

Node* UT::createRoundedRectMaskNode(Size size, 
                                    float radius, float borderWidth, int cornerSegments)
{
    const float kappa = 0.552228474;
    float oneMinusKappa = (1.0f-kappa);

    // define corner control points
    std::vector<Vec2> verts(16);

    verts[0] = Vec2(0, radius);
    verts[1] = Vec2(0, radius * oneMinusKappa);
    verts[2] = Vec2(radius * oneMinusKappa, 0);
    verts[3] = Vec2(radius, 0);

    verts[4] = Vec2(size.width - radius, 0);
    verts[5] = Vec2(size.width - radius * oneMinusKappa, 0);
    verts[6] = Vec2(size.width, radius * oneMinusKappa);
    verts[7] = Vec2(size.width, radius);

    verts[8] = Vec2(size.width, size.height - radius);
    verts[9] = Vec2(size.width, size.height - radius * oneMinusKappa);
    verts[10] = Vec2(size.width - radius * oneMinusKappa, size.height);
    verts[11] = Vec2(size.width - radius, size.height);

    verts[12] = Vec2(radius, size.height);
    verts[13] = Vec2(radius * oneMinusKappa, size.height);
    verts[14] = Vec2(0, size.height - radius * oneMinusKappa);
    verts[15] = Vec2(0, size.height - radius);

    // result
    std::vector<Vec2> polyVerts(4 * cornerSegments + 1);

    // add corner arc segments
    appendCubicBezier(0 * cornerSegments, polyVerts, verts[0], verts[1], verts[2], verts[3], cornerSegments);
    appendCubicBezier(1 * cornerSegments, polyVerts, verts[4], verts[5], verts[6], verts[7], cornerSegments);
    appendCubicBezier(2 * cornerSegments, polyVerts, verts[8], verts[9], verts[10], verts[11], cornerSegments);
    appendCubicBezier(3 * cornerSegments, polyVerts, verts[12], verts[13], verts[14], verts[15], cornerSegments);
    // close path
    polyVerts[4 * cornerSegments] = verts[0];

    // draw final poly into mask
    auto shapeMask = DrawNode::create();
    shapeMask->drawPolygon(&polyVerts[0], polyVerts.size(), Color4F::WHITE, 0.0f, Color4F::WHITE);

    // create clip node with draw node as stencil (mask)
    return ClippingNode::create(shapeMask);
}



Sprite* UT::setFacebookIcon()
{
    float scaleIcon = 0.7f;
    Sprite* ptempFaceBook_PostToWall = Sprite::createWithSpriteFrameName(sFacebook_post_to_wall_icon);
    ptempFaceBook_PostToWall->retain();
	ptempFaceBook_PostToWall->setTag(buttons_tags::FACEBOOK_POST_TO_WALL);
    ptempFaceBook_PostToWall->setScale(scaleIcon);
    //Vec2 v = this->getAnchorPoint();
    ptempFaceBook_PostToWall->setAnchorPoint(Vec2(0.0f,0.0f)); 
    
    return ptempFaceBook_PostToWall;
}

Sprite* UT::setHelpIcon()
{
    float scaleIcon = 0.7f;
    Sprite* ptempHelp = Sprite::createWithSpriteFrameName(sHelp_icon);
    ptempHelp->retain();
	ptempHelp->setTag(buttons_tags::HELP_BT);
    ptempHelp->setScale(scaleIcon);
    ptempHelp->setAnchorPoint(Vec2(0.0f,0.0f)); 
    
    return ptempHelp;
}

void UT::setSignScalefactor(Sign* &rpSign)
{
    float latterScaleFactor =   SignFactory::getInstance()->getLatterScaleFactor();
    rpSign->setScale(latterScaleFactor,latterScaleFactor+fSignScaleAddition);
}

