#include"parser.h"

	namespace Parser{
	bool Parser::match(std::string cmp){
		for(int i=0;i<cmp.length();i++){
			if(pos+i>=expr.length()||expr[pos+i]!=cmp[i])
				return false;
		}
		return true;
	}
	double Parser::matchE(){
		return matchT()+matche();
	}
	double Parser::matche(){
		if(match("+")){
			pos++;
			double resT=matchT();
			double rese=matche();
			return resT+rese;
		}else if(match("-")){
			pos++;
			double resT=matchT();
			double rese=matche();
			return -resT+rese;
		}else{
			return 0;
		}
	}

	double Parser::matchT(){
		return matchN()*matcht();
	}
	double Parser::matcht(){
		if(match("*")){
			pos++;
			double resN=matchN();
			double rest=matcht();
			return resN*rest;
		}else if(match("/")){
			pos++;
			double resN=matchN();
			double rest=matcht();
			return rest/resN;
		}else{
			return 1;
		}
	}
	double Parser::matchN(){
		double resM=matchM();
		double resn=matchn();
		return pow(resM,resn);
	}
	double Parser::matchn(){
		if(match("^")){
			pos++;
			double resN=matchN();
			return resN;
		}else{
			return 1;
		}
	}
	double Parser::matchM(){
		if(match("(")){
			pos++;
			double ans=matchE();
			if(!match(")"))
				throw 1;
			else
				pos++;
			return ans;
		}else if(match("sin(")){
			pos+=4;
			double ans=matchE();
			if(!match(")"))
				throw 1;
			else
				pos++;
			return sin(ans);
		}else if(match("tan(")){
			pos+=4;
			double ans=matchE();
			if(!match(")"))
				throw 1;
			else
				pos++;
			return tan(ans);
		}else if(match("cos(")){
			pos+=4;
			double ans=matchE();
			if(!match(")"))
				throw 1;
			else
				pos++;
			return cos(ans);
		}else if(match("ln(")){
			pos+=3;
			double ans=matchE();
			if(!match(")"))
				throw 1;
			else
				pos++;
			if(ans<0)

				throw 1;
			return log(ans);
		}else if(match("lg(")){
			pos+=3;
			double ans=matchE();
			if(!match(")"))
				throw 1;
			else
				pos++;
			if(ans<0)
				throw 1;
			return log(ans)/log(10);
		}else if(match("sqrt(")){
			pos+=5;
			double ans=matchE();
			if(!match(")"))
				throw 1;
			else
				pos++;
			if(ans<0)
				throw 1;
			return sqrt(ans);
		}else if(match("pow(")){
			pos+=4;
			double ans1=matchE();
			if(!match(","))
				throw 1;
			else
				pos++;
			double ans2=matchE();
			if(!match(")"))
				throw 1;
			else
				pos++;
			return pow(ans1,ans2);
		}else if(match("e")){
			pos++;
			return M_E;
		}else if(match("PI")){
			pos+=2;
			return M_PI;
		}else{
			std::string num="";
			int dotCnt=0;
			int flag=1;
			while(match("+")||match("-")){
				if(match("-")){
					flag=-1*flag;
				}
				pos++;
			}
			while(pos<expr.length()&&((expr[pos]>='0'&&expr[pos]<='9')||expr[pos]=='.')){
				if(expr[pos]=='.'){
					dotCnt++;
					if(dotCnt>1)
						throw 1;
				}
				num+=expr[pos++];
			}
			if(num=="")
				throw 1;
			if(dotCnt==0)
				num+=".";
			double rate=pow(10,num.length()-num.find('.')-1);
			double ans=0;
			for(int i=0;i<num.length();i++){
				if(num[i]=='.')
					continue;
				ans*=10;
				ans+=num[i]-'0';
			}
			ans=flag*ans/rate;
			return ans;
		}
	}

	Parser::Parser(){}
	std::string Parser::calculate(std::string s){
		expr=s;
		pos=0;
		try{
			double ans=matchE();
			std::stringstream ss;
			ss<<ans;
			std::string res;
			ss>>res;
			if(pos==expr.length())
				status=SUCCESS;
			else
				status=PARTIAL;
			return res;
		}catch(...){
			status=FAILURE;
			return "Error!";
		}
	}
	int Parser::getStatus(){
		return status;
	}
}

