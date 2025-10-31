void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "Azt mondják, verekedés volt a kocsmában tegnap este... De hogy ki verekedett - átkozott legyek, ha tudom. Az arcom még mindig sértetlen. Azt hiszem.";
				link.l1 = "Úgy látszik, elég nagy volt itt a piálás?";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Oi, "+GetSexPhrase("haver","lass")+", láttad valahol a csizmámat? Valami hitvány tolvaj meglépett vele, amíg én a kocsmaasztal alatt ájultam el.";
						link.l1 = "Tartsd jobban szemmel, különben a másik is követni fogja.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Azt beszélik, hogy tegnap verekedés volt a kocsmában... Bár hogy ki verekedett, azt csak találgatni lehet. Az arcom sértetlennek tûnik. Azt hiszem.";
						link.l1 = "Talán úgy gondolták, hogy az arcod már elég kárt szenvedett.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "Az ördögökre a mélységben, tegnap egy erszény tele voltam arannyal! Hol a fenében van most?";
						link.l1 = "Egy igazi kalóznak nem az arany a legfontosabb jutalom. A szabadság sokkal nagyobb érték.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "Ó, az biztos! A fogadósnak tele volt a keze... hic... És ráadásul... valaki ellopta a ginjét! Nem csak egy üveggel, hanem egy egész hordóval! És nem is akármilyen hordót - olyat, amilyet sehol máshol nem találsz a Karib-tengeren! Azt mondják, Európából hozták. Azt nem árulja el, hogy kinek, de egy dolog biztos: ha nem találják meg hamarosan, szegény fickónak pokoli viharban lesz része!";
			link.l1 = "Ez mulatságos. Hát akkor vigyázz magadra, te vén részeges.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			OS_Start();
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "Mi mást akarsz még? Nem látod, hogy a koponyám mindjárt felhasad? Húzz a picsába!";
					link.l1 = "Talán igyál kevesebbet, és akkor inkább egy rendes embernek néznél ki, mint egy ázott roncsnak.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Hagyj békén... Mindjárt szétrobban a fejem!";
					link.l1 = "Figyelemre méltó, hogy még mindig a válladon van.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Átkozott legyél a mélységig... Hagyj békén, nem látod, hogy nincs kedvem beszélgetni!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Tûnj el! Nem látod, hogy a határon vagyok? Az öklöm már viszket, hogy valakinek az állkapcsába csapódjon.";
			link.l1 = "Nyugodj meg, tengerész. Csak azt akarom hallani, mi történt tegnap a kocsmában.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "Átok és kárhozat! Te "+GetSexPhrase("egy másik szeretôje vagy annak az ôrült szolgálóleánynak","egy rokona")+"? Mit akarsz, talán a tengerbe sodor a szélvihar? Párbajra hívsz ki, mi? Vagy itt és most rögtön acélt húzol?";
			if (pchar.sex == "woman")
			{
				link.l1 = "Egy rokon? Aligha. De maga, barátom, úgy tûnik, nem tartja ôt különösebben nagyra?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "A szeretôje? Aligha. Úgy tûnik, a nôstény inkább a mennyiséget részesíti elônyben a minôséggel szemben, nem gondolja?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Az ô ügyei nem érdekelnek engem. Csak mondja el, mi történt, és békén hagyom. Te voltál az, aki ilyen dühbe kergette, ugye?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "Az a pokolbéli macska olyan válogatós, mint egy éhezô tengerész hónapok után a tengeren - fogd meg, ami a legközelebb van, és késôbb rendezd el! Egész este engem bámult, úgy flörtölt velem, mint egy kocsmai macska, amelyik falatra vadászik. De abban a pillanatban, amikor megpróbáltam horgonyt vetni a kikötôjében - olyan hangosan visított, hogy a halak az öbölben a mélybe merültek!";
			link.l1 = "Talán túl sok rumot ivott, és túlságosan elôremenekült?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "Az a pokolbéli macska olyan válogatós, mint egy éhezô tengerész hónapok után a tengeren - fogd meg, ami a legközelebb van, és késôbb rendezd el! Egész este engem bámult, úgy flörtölt velem, mint egy kocsmai macska, amelyik falatra vadászik. De abban a pillanatban, amikor megpróbáltam horgonyt vetni a kikötôjében - olyan hangosan visított, hogy a halak az öbölben a mélybe merültek!";
			link.l1 = "Talán túl sok rumot ivott, és túlságosan elôremenekült?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "Lehet, hogy a poharamban voltam, de tisztán emlékszem, mint a nyugodt tenger, ami ott történt. Nem én vadásztam rá - úgy körözött körülöttem, mint egy cápa, aki vérszagot érez. Egész átkozott nap körülöttem lebegett!";
			if (pchar.sex == "woman")
			{
				link.l1 = "És egy ilyen jelentéktelen dolog miatt kész vagy összeverekedni az elsô emberrel, akivel találkozol? Vagy valami más történt aznap este?";
			}
			else
			{
				link.l1 = "Figyelj ide, azt mondtad 'még egy szeretô.' Tudsz valamit a tévelygéseirôl?";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "Miután a sikolyai elhaltak, a hajótársaim azt mondták, hogy csak az idômet vesztegetem azzal, hogy az ô vizein próbálok zsinórt vetni. Azt mondták, hogy van egy udvarlója a városban, aki a kapitányunkkal van összebarátkozva.";
			link.l1 = "Érdekes. Észrevett még valami szokatlant? Talán valaki közeledett a bárpult felé a felfordulás alatt?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Az ördög vigye el az egészet... A fejem úgy hasad, mint a hajótest a zátonyon, és te itt vagy a pokoli kérdéseiddel. Nem láttam és nem hallottam semmit. Jobban tenné, ha megspórolna pár pesót, minthogy egy tapasztalt tengerészt kínozzon ezzel a vallatással.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Itt van száz pezó. Vigyázz, nehogy megint elvedd magad, és annak a szolgálólánynak a bûvkörébe kerülj, jó?";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Az én pénzem nélkül nem fogod megúszni. Különben csak elázik, és megint zaklatja azt a pincérnôt.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hé, Jack! Egy kikötôi kurva van a szállásodon! Ha-ha! Csak gyönyörködj a szemedben - elég vonzó kis ördög! Vajon átkutatta az összes ládánkat, vagy csak a legérdekesebb résznél szakítottuk félbe?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "Hé, Jack! Nézd csak, mi van itt - egy tolvaj patkány! Ha-ha! Nézzétek ezt a gazembert! Már a tengeri ládáinkat is átkutatta, ugye, a sunyi gazember?";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Egy merész kis tyúk. Betörni Jack Veils' den - nem sokan mernének. Szóval mi szél hozott ide, édesem? Gondoltad, hogy szórakoztatsz minket, ugye?";
				link.l1 = "Szórakoztatni? Ha! Maguk aztán álmodozók, uraim. Azért jöttem, hogy visszaszerezzem, amit elloptak. Komolyan azt hitték, hogy a szánalmas kis elôadásuk elkerülheti a figyelmet?";
			}
			else
			{
				dialog.text = "Valóban merész féreg. Jack Veils' házba betörni nem sokan mernének megkísérelni. Nos, mi dolgod van itt?";
				link.l1 = "Mondjuk úgy, hogy visszaszerzem a lopott holmit. Vagy az urak tényleg azt hitték, hogy a szánalmas kis színjátékuk észrevétlen marad?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Szánalmas elôadás?! Süssön meg az ördög, elevenen megnyúzlak, és a bôrödet vitorlának használom! Ha-ha! Bár talán elôbb talán... elszórakozhatnánk veled egy kicsit?";
				link.l1 = "Látom, alig várod, hogy találkozz a teremtôddel? Rendben, nem akarlak megvárakoztatni - kapjátok el, mocskos fattyúk!";
			}
			else
			{
				dialog.text = "Szánalmas színjáték? Az ördög vigyen el, lecsupaszítom a hátadról a bôrt, és vitorlavászonnak használom! Elég a beszédbôl - eljött az idôd, te nyomorult kutya!";
				link.l1 = "Ha így akarjátok, akkor legyen, gazemberek!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+"Hol a ginem? Ha nincs nálatok, személyesen küldelek a kikötô fenekére, hogy etessétek a halakat!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "Én magam hoztam. Itt is van.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("Te adtad a hordó gint", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Jó látni, hogy a beléd vetett hitem nem volt helytelen, "+sld.name+". Gyere be holnap a szállásomra a dublónjaidért.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "Kapitány, ami a táblát illeti...";
			link.l1 = "Milyen emléktábla? Á, az a... Merem állítani, hogy nincs szükségem ilyen kitüntetésre. Ne fáradjon miattam.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "Tudok valami sokkal jobbat ajánlani! Ettôl a naptól kezdve mindig ingyen szállást és italt kapsz a ház vendégeinek a kocsmámban! Egy ilyen kaliberû ember bizonyára megérdemli ezt!";
			link.l1 = "Ez már jobban tetszik nekem! Az ilyen kiváltságokat szívbôl értékelem! Amíg útjaink újra keresztezik egymást, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}