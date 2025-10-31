// Алонсо де Мальдонадо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Szükséged van valamire?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "Állj, kapitány "+GetFullName(pchar)+"...";
			link.l1 = "Valahogy még a spanyol katonák' jelenléte sem lep meg... Azt hiszem, már megszoktam, hogy valaki mindig a nyomomban van. Mit keresel ezen az isten háta mögötti szigeten, kasztíliai? Egy gyors módot keresel, hogy felrúgd a sarkad?";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "A nevem Alonso de Maldonado. Ez talán nem mond önnek semmit, de Diego de Montoya talán ismerôsen cseng. Ô volt a legjobb barátom. Megmentette az életemet, és most az ô vére tapad a maga kezéhez.";
			link.l1 = "Gondolom, azért követett ide, hogy bosszút álljon?";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "Nem csak bosszút akarok állni. Ha jól tudom, nálad van Kukulcan maszkja?";
			link.l1 = "Hát, az ördög vigyen el! Még egy kincsvadász! Valami befejezetlen ügy miatt jöttél, amit Don Diego kezdett el?";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "Nem érdekelnek a kincsek. Láttam a gazdagságot Tayasalban. Miguel Dichoso nem tudott többet kihozni egy falatnál. A maszk az, amit akarok.";
			link.l1 = "Jártál Tayasalban? Ezt nehéz elhinni. Amennyire emlékszem, Dichoso volt az expedíció egyetlen túlélôje.";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "Én húsz évvel Dichoso elôtt jártam Tayasalban. Ugyanabban az idôben, amikor az az ôrült varázsló Kanek azt az aljas emberáldozati rituálét alkalmazta, hogy elrejtse a maszkot ezen a szigeten.";
			link.l1 = "Nem hiszem el, amit hallok! Ugyanabból a hódító bandából származol, akiket oda hoztak, hogy feláldozzák ôket, amikor az Igazság Ôrzôjét létrehozták? Mindannyian halottak vagytok!";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "Nem mindannyian. Én túléltem.";
			link.l1 = "Miért döntött úgy az Itza, hogy megkímél téged? Mi különböztet meg téged annyira?";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "Nem értenéd meg. A pokolba is, én sem értettem. Senki sem kímélt meg. Úgy emlékszem rá, mintha tegnap lett volna... Rögtön azután, hogy az a vadember elôvett egy tôrt, és kifilézett egy bôrdarabot Casco hátáról, mielôtt halálra ítélte volna, és üvölteni kezdett, mint egy ôrült, azt hiszem, beszippantott a bálvány. Húsz évvel késôbb ébredtem Tayasaltól messze, egy pillanatnak tûnô pillanat alatt!";
			link.l1 = "Egy tér-idô tölcsér... Az istenit, minden, amit Ksatl Cha mondott, teljesen igaz volt! Honnan tudtál a maszkról? Mire kell neked?";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "Meg kell állítanom a pokol ivadékát, akit egy ôrült indiai varázsló idézett meg. Ez a förtelem máglyát akar gyújtani a világunkból!";
			link.l1 = "Hmm... Beszéltél Vincento atyával, ugye? Az inkvizítor a nyúllal tart, és a kutyákkal fut. Meglepetés, meglepetés. Azért küldött téged, hogy megtalálj engem, hogy csatát vívj velem? Szép munka! Teljesítetted a küldetésed, Don Alonso!";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "A nagyúr megerôsíti kezemet a gonosz elleni harcban. Visszatérek Tayasalba, és a maszkkal örökre bezárom a kapukat. És egyetlen emberi alakú démon sem léphet át a mi világunkba.";
			link.l1 = "Csak egy kis probléma van a terveddel, Don Alonso. A démon már köztünk van. Csak annyit kell tennünk, hogy nem hagyjuk, hogy elhagyja ezeket a kapukat. Erre nem lesz képes, amíg távol tartod tôle a maszkot.  ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "Ennél többre lesz szükség. Bárkinek is legyen igaza közülünk, egy dolog biztos: a kapukat örökre be kell zárni. És erre csak egy mód van: elpusztítani a maszkot Tayasal oltárán. Ezzel a démon minden erejét elveszítjük.";
			link.l1 = "Hm. Egyetértek, hogy ez a legjobb esélyünk... Hogyan tervezed, hogy eljutsz Tayasalba? Tudod az utat oda?";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "Az a könnyû út, amit akkoriban használtunk, már nem létezik. Az utakat kövek temették be, és eltûntek a dzsungelben. Van egy másik út a városba, de az hosszú és veszélyes. Az út Yucatán legészakibb öblénél kezdôdik.\nVincento atya és don Ramon de Mendoza segítségével összegyûjtöm az elit katonák egy csapatát, és átverekszük magunkat az Itza vademberek által védett selván. Nem lesz könnyû, de Isten erôt és bátorságot ad nekünk a hitünk nevében vívott harcunkhoz.";
			link.l1 = "Don Alonso, az én törekvéseim történetesen egybeesnek a tiéddel. Nem lenne itt az ideje, hogy egy pillanatra félretegyük a haragot és egyesítsük erôinket? Együtt nagyobb esélyünk lesz arra, hogy sikeresen befejezzük ezt a keresztes hadjáratot.";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "Spanyol katona vagyok. Nem kötök szövetséget eretnekekkel, és nem kötök alkut franciákkal. Mellesleg, már bejelentettem, hogy bosszút állok rajtad Don Diego miatt. Egy életet egy életért!";
			link.l1 = "Makacs vagy, mint egy ökör, Don Alonso! Ott állsz, és azt prédikálod, hogy a világot nagy gonoszság fenyegeti, és mégis visszautasítod a segítségemet, hogy sikerüljön egy ilyen csillagászati feladat!";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "Most én hozom a döntéseket, nem Vincento atya! Mondd el az imáidat és készülj a halálra, francia kapitány!...";
			link.l1 = "Ó, ezt már annyiszor hallottam az elmúlt hónapokban! En guard, keményfejû caballero!";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
