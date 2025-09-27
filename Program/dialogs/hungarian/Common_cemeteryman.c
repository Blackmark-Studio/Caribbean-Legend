// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("A város riadókészültségben van. Úgy tûnik, itt az ideje, hogy én is fegyvert fogjak...", "Nem üldöz téged az egész városôrség? Nekem katonák!!!", "Itt nem találsz menedéket. De találsz pár centi hideg acélt egy borda alatt!"), 
					LinkRandPhrase("Mit akarsz, gazember?! Egy városi ôrség máris a nyomodba eredt, nem menekülsz messzire, "+ GetSexPhrase("mocskos kalóz!","gazember") +"!", "Állj! "+ GetSexPhrase("mocskos gyilkos! Ôrség!!!","Nem félek tôled! Hamarosan felakasztanak az erôdünkben, nincs hova elbújni...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Úgy tûnik, belefáradtál az életbe...", "És miért nem akartok nyugodtan élni, polgárok..." + XI_ConvertString("Colony" + npchar.city + "Gen") + "!"), 
					RandPhraseSimple("Menjetek a pokolba!", "Már csak néhány másodperc van hátra számotokra ezen a világon..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "A-a-ah! Ah, te vagy az... Ki vagy te? Miért jöttél a temetôbe?";
				link.l1 = "A nevem "+GetFullName(pchar)+". És te ki vagy és mit keresel itt? És miért félsz ennyire?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "Szóval, milyen volt? Megnézted? Most már hiszel nekem?";
				link.l1 = "Nem, még nem mentem le a kriptába. Várj még egy kicsit, mindent megnézek.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "Na, és? Megnézted már? Láttad?";
				link.l1 = "Igen, persze, hogy láttam! Igazad volt!";
				link.l1.go = "Lantern_10";
				link.l2 = "Nem egészen az volt, amire gondoltál.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("Helló, tengerész! A nevem "+GetFullName(npchar)+", és én vagyok itt az egyetlen élô lélek. Valójában mindannyian meg fogunk halni, ha-ha-ha-ha! Miért jöttél?", "Hello! Már régóta nem láttam élô embert... Engedd meg, hogy bemutatkozzam - "+GetFullName(npchar)+", és ez a temetô az utolsó menedékem. Úgy tûnik, itt fogok eltemetkezni. Miben segíthetek?");
				link.l1 = "Hello, "+npchar.name+"! A nevem "+GetFullName(pchar)+", és kapitány vagyok. A dzsungelen keresztül sétáltam és idejöttem. Gondoltam benézek ebbe a kényelmes házba, hogy lássam, ki nem fél itt lakni....";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Á, öreg barátom, kapitány "+GetFullName(pchar)+"! Gyere be, gyere be!";
				link.l1 = "Isten hozott, barátom! Nagyon örülök, hogy látlak. Nem látsz táncoló csontvázakat éjjelente és halott embereket rézpénzzel a szemükön az álmaidban?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "És miért kellene félnem, kapitány? Félni az élô emberektôl kell, a holtak nem harapnak. Eh! Valaha egészen más életem volt, most pedig ennek a temetônek az ôre vagyok. Én vigyázok a sírokra. És néha kereskedem is néhány furcsa dologgal...";
			link.l1 = "És milyen tárgyakkal kereskedsz, mondd el, kérlek?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "Most mi szél hozta ide?";
			link.l1 = "Mutasd meg, mit árulsz ma.";
			link.l1.go = "trade";
			link.l2 = "Szeretnék kérdezni valamit...";
			link.l2.go = "quests";
			link.l3 = "Semmi komolyat. Csak üdvözölni jöttem.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Sok szabadidôm van, ezért szeretek a dzsungelben sétálni, hogy hasznos növényeket és díszes köveket gyûjtsek. Aztán eladom ôket a városban. Nem kerülnek sokba, de - jobb, mint a semmi. A barátaimtól pedig sokféle dolgot kapok...";
			link.l1 = "Barátaidtól? Úgy érted, hogy továbbadod, amit mások hoznak neked?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "O-ho-ho... Nem, mindent ingyen adnak nekem. Ki lehet egy temetôôr barátja, ha nem a halottak?";
			link.l1 = "Mi... Holttesteket rabolsz ki?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "Nem rabolok, csak elveszek dolgokat azoktól, akiknek már nincs rájuk szükségük. Sokféle ember van itt eltemetve - néhány ismeretlen és nem a mi földünkrôl való. A parancsnok hoz egy holttestet a városból, és azt mondja: 'Ez a tiéd, "+npchar.name+", küldd el utolsó útjára.' Hontalanok, felakasztott kalózok, ôrök által megölt banditák - mind itt vannak eltemetve. És az öreg "+npchar.name+" keresztény szokás szerint eltemeti a holttestüket.";
			link.l1 = "Értem. Nos, a pénz az pénz, mutasd meg, mid van.";
			link.l1.go = "trade";
			link.l2 = "Megvan. Mennem kell. Örültem a találkozásnak.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Te pedig, "+GetFullName(pchar)+", egy tolvaj vagy! Ôrség!!!", "Mi a fene! Egy pillanatra félrenéztem, és máris megpróbálod ellopni, ami az enyém! Fogjátok meg a tolvajt!!!", "Ôrség! Rablás!!! Fogjátok meg a tolvajt!!!");
			link.l1 = "A francba!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "Hú, szóval te csak egy utazó vagy... A nevem "+GetFullName(npchar)+", én vagyok ennek az isten háta mögötti helynek a gondnoka.";
			link.l1 = "Miért érzel így a temetôvel kapcsolatban? Éppen ellenkezôleg, a mi Urunk innen viszi el az igazakat a temetés után.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "De az igazságtalanok, úgy látszik, itt maradnak a temetés után! Az elmúlt néhány éjszakán valami zaj hallatszott a kriptából. És a nyögések olyan dermesztôek, hogy kiráz a hideg... Úgy tûnik, hogy egy elveszett lélek nem talál nyugalmat! Most már csak nappal alszom - éjszaka nem tudom elhagyni a helyemet, és nem tudok aludni...";
			link.l1 = "Zajok? Nyögések? De nincs ott senki, csak az elhunytak.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "Errôl beszélek, érted? Jobb, ha eltûnsz innen, mielôtt a szellem megérez téged... Különben nem fogsz tudni aludni, akárcsak én.";
			link.l1 = "Hm, igen, azt hiszem, jobb, ha elmegyek innen.";
			link.l1.go = "Lantern_04";
			link.l2 = "Talán segíthetek neked? Hadd nézzek utána azoknak a furcsa zajoknak ma este.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "Elment az eszed?! Látom, van fegyvered, de hogy akarsz vele harcolni az élôholtak ellen? És ha ott végzed, hogy feldobod a talpad, akkor mi lesz? A szellem szabadon fog kóborolni, és még az is lehet, hogy felnevel téged, mint a szolgáját!";
			link.l1 = "Nos, ez csak babona...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "Milyen babona? Ez nem Európa jámbor földje, a fenébe is... A bennszülöttek, azok a vörös arcú emberek, bármit képesek elôvarázsolni - és most itt kell élnünk!";
			link.l1 = "De azért hadd próbáljam meg. Megvárom az estét, aztán lemegyek a kriptába.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "Rendben, tedd, amit akarsz. De ha napkeltéig nem térsz vissza, mindent bezárok, elbarikádozom, és magam megyek el innen! Akár a fedélzetet söprögetve, mint egy matróz, akár ládákat cipelve, mint egy dokkmunkás - én úgysem jövök ide vissza!";
			link.l1 = "Csak nyugodj meg... Minden rendben lesz.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "Várjatok... Fogd ezt a lámpást. Van egy tartalékom. Ott szükséged lesz rá. Koromsötét van!";
			link.l1 = "Köszönöm, egy lámpa valóban jól jön egy ilyen helyen.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lámpás' megérkezett");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "Ugye? Mi volt ott? Mondd el!";
			link.l1 = "Egy nô nyugtalan szelleme volt ott! Szerencsére a helyi pap megáldotta a pengémet, hogy lesújtson a gonoszra, így minden rendben volt. Az a szellem nem fog többé zavarni.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "Ó Uram, mentsd meg bûnös lelkünket! Figyelmeztettelek! És te nem hittél nekem!";
			link.l1 = "Igen, és ezt ôszintén sajnálom. De most már minden rendben van - szentelt vízzel locsoltam meg ezt a helyet, és egyetlen szellem sem mer majd feltámadni a sírból. Nyugodtan alhatsz.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "Köszönöm szépen! Fogalmad sincs, mit jelent ez nekem! Tessék, kérlek, fogd ezt. Nem sok, de nem engedhetlek el jutalom nélkül.";
			link.l1 = "Köszönöm, nem utasíthatom vissza. Sok szerencsét!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "Nem? Akkor mi az ördög... Úgy értem, mi az isten történt ott?";
			link.l1 = "Egyáltalán nem volt ott szellem. Egy fiatal pár választotta ezt a kriptát a randevújuk helyszínéül. A szüleik ellenzik ezt az egyesülést, ezért kerestek egy helyet, ahol kettesben lehetnek.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "Egyedül? Azok a fiatalok! Csak próbáljanak meg még egyszer idejönni! Vagy elkergetem mindkettôjüket egy korbáccsal, vagy bezárom ôket a kriptába, hogy ott is maradjanak!!!";
			link.l1 = "Többé nem fognak ide visszajönni. Mondtam nekik, hogy a kis szökésükkel nagyon megijesztették a helyi ôrséget. Szándékosan csinálják ezt. Amúgy meg a zár az ajtón amúgy is el van törve.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "Nem baj, majd kicserélem. De ha valaha is elkapom ôket...";
			link.l1 = "Ne légy olyan mérges. Mindannyian voltunk már ilyen idôsek. Nem azért jöttek ide, mert ez a legjobb randizóhely.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "Ez így van rendjén... Ó, nos, az Úr legyen velük. Köszönöm, hogy nem hagytál egy öregembert bajban. Tessék, kérem, fogadja el ezt. Nem sok, de nem engedhetem el jutalom nélkül.";
			link.l1 = "Köszönöm, nem utasíthatom vissza. Sok szerencsét!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}
