// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Meg mered mutatni magad a fôkormányzói hivatalban?! Te tényleg ôrült vagy...", "Hogy engedhették ezek a lusta csontok, hogy egy ellenség betörjön a rezidenciámba? Ez már az eszemet is meghaladja...", "Biztos, hogy az ôreim nem érnek egy fillért sem, ha valami csavargó szaladgál a rezidenciámban..."), 
					LinkRandPhrase("Mit akarsz, "+ GetSexPhrase("kúszó","büdös") +"?! A katonáim már a nyomodba eredtek, "+ GetSexPhrase("mocskos kalóz","büdös") +"!", ""+ GetSexPhrase("mocskos","mocskos") +" gyilkos, azonnal hagyd el a rezidenciámat! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("gazember","gazember") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("A katonák szart sem érnek...", "Soha nem fogsz elkapni."), 
					RandPhraseSimple("Kussolj, haver, vagy kitépem a mocskos nyelvedet!", "Én mondom neked, haver: ülj csendben, vagy levágom a fejedet, és bedobom azon az ajtón keresztül az ôrzô kutyáidnak..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Úgy hallottam, hogy nagyon kitartóan kért közönséget. A nevem " + GetFullName(npchar) +
                              ". Én vagyok a " + NationNameGenitive(sti(NPChar.nation))+ "gyarmatok fôkormányzója, a korona helyettes " + NationKingsName(npchar)+
                              " ezeken a vizeken. Most pedig kérem, legyen olyan kedves, mondja el, mi a látogatásának célja, " + GetAddress_Form(NPChar) + ".";
				link.l1 = "A nevem " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Ó, már megint te vagy az? Nos, mit akarsz ezúttal a " + NationNameGenitive(sti(NPChar.nation))+ " fôkormányzótól?",
                              "És már megint elvonja a figyelmemet a fontos államügyekrôl? Mit akarsz, " +GetAddress_Form(NPChar)+"?");
				link.l1 = "Beszélni akarok veled a korona nevében történô munkáról. " + NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "Egy fontos ügyrôl kell beszélnem veled.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "Egy meghívásra jöttem, hogy részt vegyek a regattán. Itt a meghívóm.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "Sajnálom, de dolgom van.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "Szóval mi volt az oka, hogy idejöttél és elvonod a figyelmemet a fontos állami ügyekrôl?";
			link.l1 = "Beszélni akartam veled arról, hogy a Korona nevében dolgozol... " + NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "Egy fontos ügyrôl akartam beszélni veled '.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "Azért jöttem ide, hogy részt vegyek a regattán. Itt a meghívóm.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "Ez csak egy udvariassági látogatás, semmi több, "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Ebben az esetben megkérném, hogy hagyja el az irodámat, és ne zavarjon a munkámban.";
			link.l1 = "Igen, igen, persze. Elnézést a zavarásért.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "Ha munkát keres, beszéljen a kolóniák kormányzóival. Gyakran van szükségük okos és bátor kapitányokra.";
			link.l1 = "Ezt észben fogom tartani. Köszönöm, uram.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Ó, nagyszerû, örülök, hogy látom, kapitány! Épp idôben érkezett - a regatta néhány nap múlva kezdôdik. Elolvasta a regatta szabályait a levélben, amit biztosan futárral kaptak meg?";
			link.l1 = "Igen, uram, olvastam.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "És elôkészítette az 50000 pezót - a nevezési díjat, amely hozzájárul a díjalaphoz?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Igen, természetesen. Kérem, fogadja el a díjamat.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Jelenleg egy kicsit szûkében vagyok a pénznek. De biztosan hozom, amilyen gyorsan csak tudom.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Nagyon jó. Ha nyersz - a pénzed ötszörösen fog visszatérni hozzád. Most már tudnod kell, hogyan ne szegd meg a regatta szabályait.\nTárgyald meg a részleteket Henry Stevensonnal, ô biztosan a rezidencia szobájában van. Találkozzatok vele, ô majd mindent elmagyaráz.";
			link.l1 = "Rendben. Azt teszem, amit mondasz.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Rendben, de kérem, ne tartson túl sokáig, kapitány. A regatta hamarosan kezdôdik.";
			link.l1 = "Értem, értem. Megpróbálok pénzt hozni, mielôtt a regatta elkezdôdik.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "És itt van a regatta gyôztese! Helló, kapitány " + GetFullName(pchar) + "! Engedd meg, hogy gratuláljak ehhez a megérdemelt sikerhez! A regatta gyôztesei mindig népszerûek az angol kolóniákon, méltán népszerûek.";
			link.l1 = "Köszönöm, uram!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Most pedig ugorjunk a számotokra legkellemesebb részhez, a díjátadó ünnepséghez. Az elsô díj pénzben kifejezve 250000 pezó. Tessék!";
			link.l1 = "Köszönjük!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Továbbá, jogosult vagy egy sor értékes nyereményre: "+sAdd+". Most már mind a tiéd.";
			link.l1 = "Nagyon örülök, uram! Tényleg, erre nem számíthattam volna.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Az összes angol gyarmat nevében örömmel köszönöm, hogy részt vettél a regattán, és még egyszer gratulálok a gyôzelmedhez! Ha fogadást kötöttél, most itt az ideje, hogy felkeress Sir Henry Stevensont, és átvedd a nyereményedet, ha még nem tetted meg. Sok szerencsét, kapitány úr!";
			link.l1 = "Köszönöm kedves szavait, uram! Viszont engedje meg, hogy én is megköszönjem, hogy lehetôséget biztosított nekem, hogy részt vehessek egy ilyen nagyszerû eseményen. És most engedje meg, hogy elbúcsúzzak és távozzak.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
