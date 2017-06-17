#include<regex.h>
using namespace std;
int main()
{
	string str;
	while(true)
	{
		cin>>str;
		regex e("abc");
		bool match=regex_match(stre,e);
		
		cout<<(match?"MAtch":"No match")<<endl;
		
	}
}

