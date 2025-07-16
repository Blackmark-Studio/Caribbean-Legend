// Вильям Патерсон
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
			dialog.text = "Czy czegoś chcesz?";
			link.l1 = "Nie, nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "Czołem, Monsieur. Cholera jasna, to ty jesteś tym, który wywołał tu całe to wojskowe zamieszanie?!";
			link.l1 = TimeGreeting()+", panie. Tak, to był mój statek, który prowadził desant. O co w ogóle chodzi? Kim jesteś? Anglikiem, jak mniemam?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "Szkot, monsieur. Kapitan angielskiej marynarki William Paterson, a to mój pierwszy oficer i prawa ręka, Archibald Calhoun. Rzecz w tym, że w dżungli znajduje się hiszpański fort. Moje zadanie to wypędzenie przeklętych łajdaków z fortu, który zbudowali niebezpiecznie blisko angielskiego terytorium.\nNiedawno próbowaliśmy go szturmować, ale łajdaki zdołały się utrzymać pomimo ich strat. Wyruszyłem po posiłki i...";
			link.l1 = "Nie ma potrzeby teraz tego robić. Wykonałem twoje niedokończone zadanie, fort w dżungli jest pusty. Hiszpański dowódca Diego de Montoya nie żyje, a jego eskadra została również zniszczona.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "Co to za samowola? Jaki masz powód, by wszczynać takie działania wojenne na angielskim terytorium?";
			link.l1 = "Śmiem przypomnieć ci, kapitanie Paterson, że to nie Belize. Jaka angielska posiadłość? Cała ta awantura zaczęła się przez Don Diego de Montoya i jego ryzykowną decyzję zaatakowania mnie i moich statków.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "Khmm... a cóż to za powód miał Don Diego, by cię zaatakować, co kapitanie?";
			link.l1 = "Między nami jest od dawna zatarg... Od dnia, kiedy to eskadra, którą dowodził, zaatakowała St. Pierre i nieco później została wyeliminowana przy moim bezpośrednim udziale.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "Do stu piorunów! Potrzebowałem tego czcigodnego caballero żywego! Zamierzałem go przesłuchać, dlaczego założył bazę wojskową w dżungli. To nie mogło być bez powodu...";
			link.l1 = "Przykro mi, ale teraz nie jest w stanie nic ci powiedzieć. W każdym razie, fort może zawierać rannych żołnierzy z garnizonu. Czy jest szansa, że mogliby coś powiedzieć?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "Żołnierze... Ach, po co nam jakieś tępe pałki!... Gdzie jest ciało Don Diego? Na nim mogły być ważne dokumenty!";
			link.l1 = "Zostawiłem Don Diego na ziemi w zbrojowni. Jeśli tak bardzo go potrzebujesz, możesz go tam znaleźć. Nie sądzę, żeby mógł uciec.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "Eh... a kto cię prosił wtrącać się w cudze sprawy... Narobiłeś mi wystarczająco dużo kłopotów...";
			link.l1 = "Kapitanie, nie rozumiem, dlaczego mnie upominasz. Wykonałem twoje zadanie, wysłałem moich ludzi do bitwy, ryzykowałem własnym życiem, a mimo to jesteś niezadowolony. Wszystko, co musisz teraz zrobić, to poinformować Port Royal o swoim sukcesie w misji i wszystkich swoich sprawach. Zapewniam cię, że nie będę rościł sobie zasług za twoją chwałę.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "Przypisać sobie zasługi? Co masz na myśli przez chwałę?! Nic z tego nie rozumiesz... Eh, dobrze. Żegnaj, panie.";
			link.l1 = "Wszystkiego najlepszego również dla ciebie!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "Człowieku, plotki nie kłamią, że masz dziewięć żyć jak kot! "+TimeGreeting()+", Monsieur de Maure. Nie wyglądasz zbyt dobrze...";
			link.l1 = TimeGreeting()+", Panie Paterson. Muszę powiedzieć, że ty i twój przyjaciel Archibald odegraliście swoje role i nieźle mnie oszukaliście, psia mać... Do diabła z wami wszystkimi! Nawet się tego nie spodziewałem...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "Ej, nie przeklinaj przed bramami Ziemi Świętej. Nie spodziewałeś się tego? Jestem pochlebiony: udało mi się oszukać jednego z najsłynniejszych intrygantów archipelagu. Pomysł z dziennikiem był genialny, nie sądzisz?\nMusiałem cię zwabić w jakieś mroczne miejsce, zabicie cię na otwartym polu byłoby skandalem, jesteś bliskim przyjacielem Philippe'a de Poincy, prawda? Teraz znikniesz bez śladu i nikt nigdy nie dowie się jak.";
			link.l1 = "Więc wszystko, co powiedział mi Calhoun... było kłamstwem?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "Skądże znowu. Naprawdę znalazłem biednego Archibalda w tym miejscu. Nie napisał jednak żadnych wspomnień, dziennik, który znalazłeś w jego pokoju, był napisany na moje polecenie specjalnie dla ciebie, Monseniorze de Maure.\nObserwowałem cię od naszego spotkania na Cape Catoche. To ty zabrałeś mapę Dwóch Wystąpień z ciała don Diego? Nie zaprzeczaj, wiem, że to byłeś ty.";
			link.l1 = "Ty także wiesz o Strażniku Prawdy?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "To głupie pytanie. Oczywiście, że tak. I wiem, że masz przy sobie Pazur Wodza. I wkrótce oddasz te przedmioty, które do ciebie nie należą.";
			link.l1 = "Cieszę się, że nie chwiejesz się jak Don Diego. Doceniam szczerość i bezpośredniość. Jak rozumiem, masz kompas, Strzałę Drogi?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "Haw-haw! Cóż, będziemy szczerzy aż do samego końca... Czy naprawdę wierzysz, panie, że jestem takim idiotą, jak ty i Don Diego, że nosiłbym przy sobie tak cenny przedmiot? Kompas jest na Jamajce i nawet nie w Port Royal, lecz w miejscu, gdzie nikt by nawet nie pomyślał szukać i pod bezpiecznym zamkiem. Ale nie będziesz potrzebował tych informacji.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "Jak rozumiem, już mnie pan pochował, panie Paterson? Ośmielam się ogłosić, że kot ma jeszcze jedno życie!.. Gdzie są moi oficerowie?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "Jak rozumiem, już mnie pan pochował, panie Paterson? Ośmielam się stwierdzić, że kot ma jeszcze jedno życie!..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "Zmartwiony o swoją damę, kapitanie? Twoja kobieta leży tam w krzakach z dziurą w czole. Wytyczyła ci drogę i wkrótce do niej dołączysz. Powiem, była taką ładną dziewczyną! Mam nadzieję, że przeleciałeś ją więcej niż raz?";
				link.l1 = "Ty... TY SKURWYSYNIE! Zabiłeś moją ukochaną?! Zapłacisz za to, ty chuju!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "Twoi oficerowie wytyczyli ci drogę, monsieur de Maure. Leżą tam w krzakach. Wkrótce dołączysz do nich.";
				link.l1 = "Jeszcze się przekonamy!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "Upewnimy się, że to naprawdę będzie twój ostatni.";
			link.l1 = "Zobaczymy, jak będzie!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "Rozśmieszasz mnie. Jeden przeciwko całemu oddziałowi! Tak czy inaczej, dość gadania... Celujcie muszkiety! Ognia!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
