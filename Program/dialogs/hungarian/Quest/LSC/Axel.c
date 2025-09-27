// торговец Аксель Йост
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Megnéznéd ezt..."+GetFullName(pchar)+"! Visszatértél a túlvilágról? Hogyan lehetséges ez?";
				link.l1 = "Az emberek nem jönnek vissza a túlvilágról, Axel. Ez egyszerû - nem voltam halott, ha-ha!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Heh, haver, nem fogok veled üzletelni, amíg nem rendezed a dolgokat a Narwhalokkal. Nem akarok bajt. Menj Fazio-hoz, ô majd elintézi.";
				link.l1 = "Rendben, azonnal megteszem.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nem akarok veled beszélni. Ok nélkül támadsz békés emberekre, és harcra provokálod ôket. Tûnjetek el!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ó! Egy új arc! Mi szél hozott ide? Bár ez nem az én dolgom. Hadd mutatkozzam be: a nevem Axel Yost és az én boltom. Lát valamit, ami tetszik?";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Milyen árucikkeid vannak?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! Örülök, hogy látlak. Akarsz venni vagy eladni valamit?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Figyelj, Axel, van egy szép muskétád, amit eladnál? Nem egy alkalmi katona kézifegyver, hanem valami pontos és nagy hatótávolságú?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Figyelj, Axel, Chad Kapper megkért, hogy szerezz neki egy whiskey-hordót? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Figyelj, Axel, biztosan hallottad a beszélgetésemet azzal a helyi idiótával. Milyen gyöngyöt kért? Nem értem.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Nem értem. Cseréljünk, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Mi történt mostanában a szigeten?", "Bármilyen pletyka?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Még semmi. Csak üdvözölni akartalak.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Mindenféle dolgok. Keverékek, pengék, lôfegyverek, lôszerek, lôszerek, köpenyek, drágakövek és ásványok. Elvarázsolt amulettek és talizmánok. Szemét és hétköznapi tárgyak. Az emberek mindent elhoznak nekem, amit a lezuhant hajókon találnak, olyan dolgokat, amikre maguknak nincs szükségük\nSzóval nyugodtan tegyétek ugyanezt. De figyelmeztetlek titeket. Nem kínálok élelmiszert vagy hajóárut.";
			link.l1 = "Rendben, Axel. Lássuk az árut.";
			link.l1.go = "Trade_items";
			link.l2 = "Köszönöm, Axel. Majd észben tartom. Találkozunk, amint szükségem lesz a szolgáltatásaidra.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "Ez biztos valami vicc. Te vagy a harmadik, aki megkérdezi. Nem hordok itt ilyen fegyvereket. De néhány hónappal ezelôtt Adolf Barbier megpróbálta eladni nekem a vadászpusztáját. Csodálatos fegyver, én mondom. Pontosan az, amit keres\nDe Barbier pokoli árat kért érte. Így hát vissza kellett utasítanom az ajánlatát.";
			link.l1 = "Érdekes! És hol találom Barbier-t?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Fogalmam sincs. Valószínûleg itt kószál valahol. Gyakran megfordul Sancho kocsmájában, minden este szeret inni egyet.";
			link.l1 = "Köszönöm! Azt hiszem, ott fogom megtalálni. Mondja, Axel, ki kérdezett még a puskáról? Említettél másokat is, akik érdeklôdtek, kik lennének azok?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper és Marcello, más néven Küklopsz. Fogalmam sincs, miért lenne szüksége a lánynak puskára, de a mi Vörös Marynk köztudottan ôrült. Egy évvel ezelôtt tonnányi puskaport vásárolt ki, hogy aknákat készítsen, rákok elkábítására, azt mondta. Hála az égnek, nem engedték meg neki\nA Marcello pedig puskát akart venni madárvadászathoz, a férfi megunta a sózott marhahúst. Mindkettôjüket Adolfhoz irányítottam, nem tudom, hogy megvették-e tôle a puskát vagy sem\nAz a ravasz kutya, Giuseppe Fazio is érdeklôdött Adolf után nemrég. Lehet, hogy ô is meg akarja venni ezt a stutzen.";
			link.l1 = "Heh, sok versenytársam van. Rendben, megkeresem Adolfot - remélhetôleg még nem adta el a fegyvert.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "Ezt mindenki tudja, uram! Mindenkitôl elkéri ezeket a gyöngyöket, így hívja a nagy gyöngyöket. Adj neki egyet, és te leszel a legjobb barátja.";
			link.l1 = "Most már értem. Köszönöm, Axel, magam sem gondoltam volna.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "De igen, haver, így van. De csalódást okozok neked, ha esetleg te is vennél egy hordó Bushmills-t. Nekem csak egy hordóm volt, és Chad megvette. Skót whiskyt tudok ajánlani - az ugyanolyan jó, mint az ír, sôt, nekem sokkal jobban tetszik az íze.";
			link.l1 = "Talán késôbb. Chad vett már tôled valamit?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Nem. Az arzén érdekelte, azt mondta, hogy túl sok a patkány a Tartaroszban, és ki akarja irtani ôket. Nem volt szükségem arzénre, mióta felbéreltem azt az idióta Olle-t, hogy takarítsa ki a boltomat, minden patkány szegény Sancho kocsmájába ment. Nem tudom, miért félnek a patkányok annyira Olle-tól...";
			link.l1 = "Talán mert macskák vannak a családjában...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ha-ha! Talán... Sanchóban van arzén - az biztos.";
			link.l1 = "Értem. Akkor köszönöm az információt!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
