#pragma once
#include <string>
#include <carte.h>

/*Structure pour faciliter le declenchement d'une exception, utile pour debug et voir ce qui ne va pas
mettre les instructions ou peuvent se produire des exceptions dans un bloc try{...}

inclure dans le try :
	if *condition qui declenche une exception si vrai*
		throw Exception("type d'exception d�clench�e");


A la suite du try :

	catch(Exception e) {
		cout<<e.get_info()<<"\n";
		}
	catch(...) { #gestionnaire d'exception g�n�rique
		cout<<"erreur exception g�n�rique"<<"\n";
	}
	*/
class Exception {
	string info;
public:
	inline Exception(const string s) : info(s) {}
	inline const string& get_info() const { return info; }
};