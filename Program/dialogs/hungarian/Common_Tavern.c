#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Tavern.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	int iTest, iTemp;
	string sTemp;
	string NPCCity = NPChar.City;
    iTest = FindColony(NPChar.City); // город 
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;
	
	if(!CheckAttribute(pchar, "questTemp.TavernVisit."+(NPCCity) )) 
	{
		pchar.questTemp.TavernVisit.(NPCCity) = true;
		pchar.questTemp.TavernVisit.counter = sti(pchar.questTemp.TavernVisit.counter) + 1;
		notification("Elsô kocsmalátogatás " + XI_ConvertString(NPCCity + "TavernName"), "Drunk");
		AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 10.0);
	}	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,
					LinkRandPhrase("A városban riadó van, és mindenki téged keres. A helyedben én nem maradnék itt.", "Az összes városôr téged keresve pásztázza a várost. Nem vagyok bolond, és nem állok szóba veled!", "Fuss, "+ GetSexPhrase("pajtás","lány") +", mielôtt a katonák darált hússá változtatnak..."),
					LinkRandPhrase("Mit akarsz, "+ GetSexPhrase("gazember","büdös") +"?! A városôrök kiszagoltak, nem jutsz messzire"+ GetSexPhrase(", mocskos kalóz!","") +"", "gyilkos, azonnal hagyd el a lakásomat! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("gazember","patkány") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, a riasztó nekem sosem jelent problémát...", "Soha nem fognak elkapni."),
					RandPhraseSimple("Fogd be a szád, " + GetWorkTypeOfMan(npchar, "") + ", vagy kitépem a nyelved!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", és minden ott van - kalózokat fogni! Ezt mondom én neked, pajtás: ülj csendben, és nem halsz meg..."));
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("És te vagy az, te szemétláda! Azt hiszed, hogy mi itt rumot töltünk neked? Dehogyis! Fiúk! Fegyverbe! Öljétek meg ezt a gazembert!", "Kérsz egy italt, kalóz? Ha! Nem! Most megmutatjuk, mi a helyzet! Fiúk, húzzátok elô a pengéteket!");
				link.l1 = RandPhraseSimple("Huh? Mi az?", "Állj!");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//Jason, Бремя гасконца
			if(NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
				{
					link.l1 = "Monsieur, munkát keresek. Van valami munkája?";
					link.l1.go = "Sharlie_rum";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
				{
					link.l1 = "Már teljesítettem a megbízását. A hosszúhajót a rummal a Le Francois öbölbe szállítottuk és átadtuk az embereinek.";
					link.l1.go = "Sharlie_rum_5";
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "crew" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				FreeSitLocator("FortFrance_tavern", "sit7");
				dialog.text = "Kért valamit, monsieur?";
				Link.l1 = "Üdvözlöm, kocsmáros, legénységet szeretnék felvenni a hajómra. Tudna ebben segíteni?";
				Link.l1.go = "Sharlie_crew";
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "skiper" && npchar.city == "FortFrance")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Üdvözlöm újra. Ezúttal mi az, monsieur?";
				Link.l1 = ""+npchar.name+", Tudom, hogy zavarom, de csak még egy kérdés. Szükségem van egy navigátorra - van ötlete, hol találhatnék egyet?";
				Link.l1.go = "Sharlie_skiper";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
    			dialog.text = "Mit akar, monsieur?";
				Link.l1 = "Reméltem, hogy tudna válaszolni néhány kérdésre.";
				Link.l1.go = "quests";
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l2 = "Szeretnék bérelni egy szobát.";
					link.l2.go = "room";
				}
				break;
			}			
			//Бремя гасконца
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "tavern" && npchar.city == "Tortuga")
			{
				dialog.text = "Örülök, hogy látom, uram! Miben lehetek a szolgálatára? Rumot, brandyt, skót whiskyt?";
				Link.l1 = "Szeretnék egy üveggel a legjobb francia borából és egy szobakulcsot.";
				Link.l1.go = "mtraxx_tortuga";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "room" && npchar.city == "Tortuga")
			{
				dialog.text = "Már fizetett, uram, a szobája az emeleten van.";
				Link.l1 = "Köszönöm.";
				Link.l1.go = "exit";
				break;
			}
			
			// Sinistra - Квест "Длинные тени старых грехов" ==>	
			if (CheckAttribute(pchar, "questTemp.DTSG_BasTerTavern") && npchar.city == "BasTer")
			{
				dialog.text = "Miben segíthetek, kapitány? A történtek után valószínûleg szeretne egy italt.";
				Link.l1 = "Az várhat. Igazából meg akarom beszélni a történteket.";
				Link.l1.go = "DTSG_BasTerTavern_1";
				DelLandQuestMark(npchar);
				break;
			}
			// <== Квест "Длинные тени старых грехов" - Sinistra
			
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Start") && !CheckAttribute(pchar, "questTemp.TPZ_Tavern_1") && npchar.city == "BasTer")
			{
				dialog.text = "Elnézést kérek, "+GetAddress_Form(NPChar)+", de ma nem tudok egy csepp szeszes italt sem kínálni.";
				Link.l1 = "Mi az? - Nem... Miféle kocsma az, amelyik egy csepp rumot sem tud nélkülözni? Lemaradtam valami nagy ünnepségrôl, ami kiürítette a raktárakat?";
				Link.l1.go = "TPZ_Tavern_1";
				pchar.questTemp.TPZ_Tavern_1 = true;
				DelLandQuestMark(npchar);
				break;
			}
			//<-- Торговля по закону

			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Üdvözlöm szerény kocsmámban '" + XI_ConvertString(NPChar.City + "TavernName") + "', uram. Örülök, hogy látom.","Szolgálatára, uram! Tavernánkban '" + XI_ConvertString(NPChar.City + "TavernName") + "' mindig örömmel fogadjuk az új látogatókat.","Elôször jár itt, uram? Ne habozzon, itt a '" + XI_ConvertString(NPChar.City + "TavernName") + "' mindig otthon érzi magát!"), LinkRandPhrase("Jöjjön be, kapitány úr. Nem ismerem meg, így biztosan most jár itt elôször '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","Még sosem találkoztunk, monsieur. Ismerkedjünk meg: Én "+GetFullName(npchar)+"vagyok, a '" + XI_ConvertString(NPChar.City + "TavernName") + "'fogadós.","Örülök, hogy üdvözölhetem új vendégünket, Monsieur Kapitányt! Az én kocsmámban '" + XI_ConvertString(NPChar.City + "TavernName") + "' elsô ital mindig a ház vendége! Én vagyok a hely tulajdonosa, "+GetFullName(npchar)+", üdvözlöm Önt."), LinkRandPhrase("Kapitány Úr! Üdvözlöm a kocsmában '" + XI_ConvertString(NPChar.City + "Tavernanév") + "'!","Ó, micsoda ragyogó hidalgo látogatta meg tavernánkat '" + XI_ConvertString(NPChar.City + "TavernName") + "'! Elôször jár itt, uram?","Buenas dias, senor! Én "+GetFullName(npchar)+"vagyok, a '" + XI_ConvertString(NPChar.City + "TavernName") + "'szerény tulajdonosa, örömmel üdvözöljük itt!"),LinkRandPhrase("Hello, mynheer kapitein. Én vagyok a kocsma tulajdonosa '" + XI_ConvertString(NPChar.City + "TavernName") + "'. Elôször száll meg nálunk?","Jó napot, mynheer. Üdvözöljük a tavernában '" + XI_ConvertString(NPChar.City + "TavernName") + "'.","Nagyon örülök, hogy látlak mynheer kapitein! Saját kocsmánk '" + XI_ConvertString(NPChar.City + "TavernName") + "' köszönti Önt! Rum, bor, vagy ha elcsábíthatlak, van egy pajkos új kis holland szeszesitalunk, a gin?"));
				Link.l1 = LinkRandPhrase("Hangulatos hely ez itt... Engedje meg, hogy bemutatkozzam - "+GetFullName(pchar)+", örülök, hogy megismerhetem.",""+GetFullName(pchar)+", örülök, hogy megismerhetem. Szóval, mit tud nekem ajánlani?","A nevem "+GetFullName(pchar)+" és új vagyok ebben a kikötôben. Mondja, mirôl ismert ez a kocsma leginkább?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_tavern")
				{
					dialog.text = "Ahoy, Rumba! Visszatértél egy utazásból, vagy új útra indulsz?";
					link.l1 = "Hello, "+npchar.name+". Csak úgy döntöttem, hogy benézek.";
					Link.l1.go = "Helen_meeting";
					NPChar.quest.meeting = "1";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
		        {
		            if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
		            {
		            	iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
		            	dialog.Text = "Szóval, kapitány, elhoztad nekem " + FindRussianMoneyString(iTemp) + ".";
		            	if(sti(PChar.Money) >= iTemp)
		            	{
							link.l1 = "Igen, hoztam. Itt vannak...";
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = "Nem, még nem hoztam...";
							link.l1.go = "exit";
						}
		            }
		            else
		            {
		            	dialog.Text = "Mit szeretne, jó "+ GetSexPhrase("uram","hölgy") +"?";
						link.l1 = "Egy üveg rumot a társamnak, ott az asztalnál.";
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Ó, tisztelt vendégek! Hé, te - menj arrébb, és csinálj helyet a gáláns kapitánynak! És siessetek, mielôtt kidoblak titeket, haha!","Irgalmas Isten fent! Ha nem "+GetFullName(pchar)+"! Most kaptam egy új szállítmányt a legválogatottabb borokból, kérem, jöjjenek be!","Ó, "+GetAddress_Form(NPChar)+", bajban vagy? Megengedi, hogy megkínáljam? Ez az üveg a ház vendége. Higgye el, ez a legjobb bor a környéken..."),LinkRandPhrase("Ó, ez a kapitány "+GetFullName(pchar)+"! Hé, te! Mutass egy kis tiszteletet a jó kapitánynak! Ez nem egy pajta! Kérem, bocsásson meg, kapitány, az anyjuk nyilván sosem tanította ôket illemre.","Nos, nos, nos, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Hosszú éjszakánk lesz, haha! Lányok, jobb lenne, ha a legjobb ruhátokat vennétek fel!","Jó napot, "+GetFullName(pchar)+", örülök, hogy látom! Kérem uram, lenne egy kérésem. Most vettem új asztalokat, úgyhogy kérem, ma este ne verekedjetek."),LinkRandPhrase("Jó napot, kapitány úr! Érezze magát otthon, de ne feledje, hogy még maga Sharp kapitány is vigyáz az illemre a létesítményemben.","O-ho-ho! Nézd csak, ki van itt? Ô maga "+GetFullName(pchar)+" ! És mi már épp kezdtünk unatkozni a távollétedben! Mi lenne, ha elszórakoztatnád a srácokat egy kalanddal, amíg én kinyitok egy új hordó rumot, kapitány?","O-ho-ho! Ô maga az "+GetFullName(pchar)+" ! Remélem, nem akarja megint a nagy kalandok történeteivel elrabolni a vendégeimet a nyílt tengerre?")),LinkRandPhrase(LinkRandPhrase(""+GetFullName(pchar)+"! Ez az öreg só mindig örömmel látja önt az üzletében! Kérem uram, foglaljon helyet, a lányok majd gondoskodnak önrôl!","Kérem, kapitány, helyezze magát kényelembe! Mindig örömmel köszöntöm kedvenc vendégemet. Mi a méreg?","Örülök, hogy újra látom, "+GetFullName(pchar)+"! Szeretne egy asztalt magának? Vagy szeretne a bárpultnál ülni?"),LinkRandPhrase("Jó napot, kapitány. Hideg van a levegôben, engedje meg, hogy megkínáljam egy kis kitûnô forralt borral, amit most készítettem, a ház vendége!","Hello, kapitány "+GetFullName(pchar)+"! Örülök, hogy ismét meglátogatsz. Mit szeretne?","Örülök, hogy itt vagy, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Örülök, hogy patronálod szegényes létesítményemet! Mindent megteszünk, hogy a kedvében járjunk."),LinkRandPhrase("Kapitány! Üdvözöljük, üdvözöljük! Van egy kis pompás d'Anjou, ami magának Lajos királynak is beillene, és kifejezetten az Ön számára tartogattam!",""+GetFullName(pchar)+"! Nagyon örülök, hogy eljött. Elkergessem ezeket a tengeri patkányokat, vagy inkább maradjanak? Hidd el, szívesen kitakarítanám neked az egész kocsmát!","Istenem, itt van a kapitány "+GetFullName(pchar)+"! Hé, flörtölôk - a legjobb terítôt a kapitány asztalához!")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Ó, látom, itt emlékeznek rám... Avast, töltsd meg a poharam, amíg körülnézek...","Nyugodj meg, haver, ma jó kedvem van. Kezdjük a rummal, jó?..."),RandPhraseSimple("Ó... nem örülsz túlságosan, hogy itt vagyok? Remélem félreértettem, ha!","Ahoy. Remélem, a borod jobb, mint a köszöntésed? Különben tudod, hogy dühös lehetek...")),RandPhraseSimple(RandPhraseSimple("Mindig örülök, hogy meglátogathatlak, haver. Mivel tudsz felmelegíteni egy sós kutyát?","Ahoy haver, a létesítményed minden egyes nappal egyre jobb lesz! Mindig öröm idejönni..."),RandPhraseSimple("Nem felejtettél el egy öreg vándort? Ez hízelgô, haver.","Jó újra látni egy régi barátot... Maradt még rumod?")));
				Link.l1.go = "step_node";
			}
			break;
				
			case "step_node":
				dialog.Text = LinkRandPhrase("Hallgatom, kapitány.","Tavernám '" + XI_ConvertString(NPChar.City + "TavernaNév") + "' szolgálatára, kapitány!","Minden fülnek, kapitány! Mit szeretnél ma?");
				Link.l1 = "Vannak fiúk a szigeten, akik készek szerencsét próbálni a tengeren?";
				Link.l1.go = "crew hire";
				Link.l2 = "Reméltem, hogy tudna válaszolni néhány kérdésre.";
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = "A pénzügyekrôl szeretnék beszélni.";
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				
				// Квестовый генератор священника. Квест №2. Warship -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
		            	{
					link.l10 = LinkRandPhrase("Tudna mondani valamit a templomban nemrég történt rablásról?", "Mit tud a templomban nemrég történt rablásról?", "Hallott valamit a templomban nemrég történt rablásról?");
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
				{
					link.l16 = "Az emberek azt mondják, hogy ön szinte mindent tud ebben a kolóniában. Szeretnék vásárolni "+pchar.GenQuest.Device.Shipyarder.Type+", és azt mondták, hogy az önök városában árulják. Nos, valaki árulta az utcai piacon. Tudna nekem mondani valamit errôl?";
					link.l16.go = "Device_Tavern";
				}
				// <-- генератор Неудачливый вор
			
				//Jason --> генератор Место под солнцем
				if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
				{
					link.l17 = "Egy "+pchar.GenQuest.Sunplace.Trader.Enemyname+"nevû zsarolót keresünk. Hol találom meg?";
					link.l17.go = "Sunplace_Tavern";
				}
				// <-- генератор Место под солнцем
			
				// --> Голландский гамбит
				if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hello, " + npchar.name + ". Jacob van Berget keresem - hol van? Nem látom ôt a kocsmában...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hello, " + npchar.name + ". Egy Fernando Rodriguez nevû caballero-t keresek. Felbukkant a városukban?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				// <-- Голландский гамбит
			
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "A nyereményemért jöttem, amelyet biztonságban tartottam nálad. " + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
			
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Azon gondolkodtam, hogy hol találok egy embert, akinek a neve "+pchar.GenQuest.Marginpassenger.q2Name+"? Az önök városában él.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
				if(!CheckAttribute(pchar,"questTemp.TimeLock"))
				{
					link.l3 = pcharrepphrase("Van egy szabad szobád, haver?", "Van egy szabad szobád, itt maradnék egy darabig.");
					link.l3.go = "room";
				}
				Link.l4 = "Sajnos, én már megyek is, " + NPChar.name + ". Viszlát.";
				Link.l4.go = "exit";
		break;
		
		case "Helen_meeting":
			dialog.Text = "Ah, nos, jöjjön be, jöjjön be. Itt mindig szívesen látjuk.";
			link.l1 = "Igen, köszönöm. Jó volt látni téged. Viszlát.";
			link.l1.go = "exit";
			Link.l2 = "Jól jönne néhány új kéz. Csak gyôzôdj meg róla, hogy alkalmasak, rendben?";
			Link.l2.go = "crew hire";
			link.l3 = "Szeretnék szilárd talajon pihenni és összeszedni a gondolataimat, nem akkor, amikor anyám a ház körül nyüzsög.";
			link.l3.go = "Helen_room";
			Link.l4 = "Kérdezhetek valamit? ";
			Link.l4.go = "quests";
			link.l5 = " Van egy megbeszélnivalóm veled, "+ NPChar.name + ".";
			link.l5.go = "Helen_rumours_tavern";
		break;
		
		case "Meeting":
			// Квестовый генератор священника. Квест №1. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
	        {
	            dialog.Text = "Mit szeretne, kegyelmes "+ GetSexPhrase("uram","hölgy") +"?";
				link.l1 = "Egy üveg rumot a barátomnak, ott az asztalnál.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			dialog.Text = LinkRandPhrase("Hallgatom, kapitány.","Mit ajánlhatok önnek, kapitány?","Szóval, kapitány, mi legyen?");
			Link.l1 = "Szükségem van egy csapatra, " + NPChar.name + ".";
			Link.l1.go = "crew hire";
			Link.l2 = NPChar.name + ", Beszéljünk...";
			Link.l2.go = "int_quests";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = "A pénzügyekrôl szeretnék beszélni.";
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}
			// Квестовый генератор священника. Квест №2. Warship -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	        {
				link.l10 = LinkRandPhrase("Tudna mondani valamit a templomban nemrég történt rablásról?", "Mit tud a templomban nemrég történt rablásról?", "Hallott valamit a templomban nemrég történt rablásról?");
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.
			
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_tavern" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Az emberek azt mondják, hogy ön szinte mindent tud ebben a kolóniában. Szeretnék vásárolni "+pchar.GenQuest.Device.Shipyarder.Type+", és azt mondták, hogy az önök városában árulják. Nos, valaki árulta az utcán. Tudna nekem mondani valamit errôl?";
				link.l16.go = "Device_Tavern";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "continue" && NPChar.location == pchar.GenQuest.Sunplace.Trader.CityT + "_tavern")
			{
   				link.l17 = "Meséljen nekem egy "+pchar.GenQuest.Sunplace.Trader.Enemyname+"nevû zsarolóról. Hol találom meg?";
				link.l17.go = "Sunplace_Tavern";
			}
			// <-- генератор Место под солнцем
			
			//--> Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobOnMain" && NPChar.location == pchar.questTemp.HWIC.Holl.JacobCity + "_tavern")
				{
					link.l18 = "Hello, " + npchar.name + ". Jacob van Berget keresem - hol van? Nem látom ôt a kocsmában...";
					link.l18.go = "HWICHollJacob_Tavern";
				}
				if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "start" && NPChar.nation == SPAIN && !CheckAttribute(npchar, "quest.HWICTalked"))
				{
					link.l18 = "Hello, " + npchar.name + ". Egy Fernando Rodriguez nevû caballero-t keresek. Felbukkant a városukban?";
					link.l18.go = "HWICSelfFernando_Tavern";
				}
				//<-- Голландский гамбит
				
				//Jason --> гонки на гидропланах
				if (CheckAttribute(pchar, "GenQuest.Racing.Go.Advantage") && NPChar.location == pchar.GenQuest.Racing.Go.StartCity + "_tavern")
				{
					link.l19 = "Azért jöttem, hogy átvegyem a nyereményemet, amelyet biztonságban tartanak nálad. " + npchar.name + ".";
					link.l19.go = "Race_Advantage";
				}
				// <-- гонки на гидропланах
				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity+"_tavern")
				{
					link.l20 = "Azon gondolkodtam, hogy hol találok egy embert, akinek a neve "+pchar.GenQuest.Marginpassenger.q2Name+"? Az önök városában él.";
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров
			if(!CheckAttribute(pchar,"questTemp.TimeLock"))
			{
				link.l3 = pcharrepphrase("Van egy szabad szobád, haver?", "Van egy szabad szobád, itt maradnék egy darabig.");
				link.l3.go = "room";
			}
			Link.l4 = "Azt hiszem, késôbb visszajövök.";
			Link.l4.go = "exit";
		break;
		
		case "crew hire":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			ok = sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok;
			
			if (!ok)
			{
				Dialog.text = "És mire kellenek a matrózok, kapitány? Nem látom a hajóját a kikötôben.";
				link.l1 = RandPhraseSimple("Pontosan... Rossz helyen kötöttem ki.", "Elfelejtettem megadni a kikötôt...");
				link.l1.go = "exit";
				break;
			}
			
            if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = "Általában sokan keresnek matróznak, de most már késô - reggel kezdenek majd megjelenni. Talán szeretnél bérelni egy szobát és megvárni ôket?";
				link.l1 = "Rendben. Vannak szabad szobáik?";
				link.l1.go = "room";
				link.l2 = "Jelenleg nem érdekel egy szoba sem. Viszlát.";
				link.l2.go = "exit";
			}
			else
			{
                if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
                {
                    Dialog.text = "Azt hiszi, hogy körözött bûnözôket szolgálunk ki? Legyen hálás, hogy nem hívom az ôröket.";
					link.l1 = "Köszönjük!";
					link.l1.go = "exit";
                }
                else
                {
					if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
					{
						Dialog.text = "Kapitány, ma egy lélek sincs a kocsmában. Mindenki, aki hajlandó volt, elment Blackwood kapitánnyal.";
						link.l1 = "Kár érte!";
						link.l1.go = "exit";
						break;
					}
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = "Ah, bocsánat kapitány, csak egy kicsit elkéstél. Minden srác keres, hogy azt mondják, csak szállított a gáláns kapitány " + GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)) + ".";
						link.l1 = "Kár érte!";
						link.l1.go = "exit_crew";
					}
					else
					{						
						if(bPartitionSet)
						{		
							if(GetPartitionAmount("CrewPayment") > 0)
							{
								if(IsEquipCharacterByArtefact(pchar, "totem_07"))
								{
									DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
									NextDiag.CurrentNode =  NextDiag.TempNode;
									DialogExit();
									LaunchHireCrew();							
								}
								else
								{
									dialog.text = "Kapitány, az emberek azt mondják, hogy maga elég fukar. Nincs itt senki, aki szeretne csatlakozni a legénységéhez.";
									link.l1 = "Értem...";
									link.l1.go = "exit";
								}
							}
							else
							{
								DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
								NextDiag.CurrentNode =  NextDiag.TempNode;
								DialogExit();
								LaunchHireCrew();	
							}
						}	
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode =  NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();							
						}						
					}
				}
			}
		break;
		
		case "exit_crew" :
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode =  NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;
	////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////	
        case "int_quests":
			dialog.text = "Csupa fül vagyok.";
			//link.l1 = "I am looking for a job. Can you help me?";
			//link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = LinkRandPhrase("Elmondaná a legfrissebb híreket?","Mi történik ezeken a földeken?",
                                    "Mi újság a földeken?");
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = "Más ügyben jöttem.";
			link.l3.go = "quests";
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = "Nem tudod, hol találom a " + pchar.GenQuest.EncGirl.name +"?";
					link.l5.go = "EncGirl_1";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = "Meg tudná mondani, hogy hol tudnám megkeresni a " + pchar.GenQuest.EncGirl.sLoverId + "?";
					link.l6.go = "EncGirl_3";
				}
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Ahoy, a fia meghívására jöttem."; 
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern"))
			{
				if(pchar.GenQuest.CaptainComission.variant == "A0")
				{												
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Szóval, láttad már a  " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = "Meg tudná mondani, hogy hol keressem a  " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_1";
					}
				}	

				if(pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = "Nem tudod, hol találom a járôrkapitányt " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
					link.l9.go = "CaptainComission_Tavern7";					
				}				
				if(pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if(pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = "Szóval, láttad már a " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + "?";
						link.l9.go = "CaptainComission_3";
					}
					else
					{					
						link.l9 = "Tudsz valamit a járôrkapitányról " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "?";
						link.l9.go = "CaptainComission_Tavern1";
						if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}	
					}	
				}					
			}
			if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false )
			{
				link.l10 = "Meg tudná mondani, hogy hol találok egy " + pchar.GenQuest.Hold_GenQuest.Name + "nevû embert ?";
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = "Véletlenül találtam nem messze innen egy hajó okmányait.....";
				link.l11.go = "ShipLetters_4";			
			}

			// Jason --> квест губера на поиск дезертира
			if(CheckAttribute(pchar, "GenQuest.FindFugitive") && pchar.GenQuest.FindFugitive != "Late" && sti(NPChar.nation) == PIRATE)
			{
				link.l12 = "Figyeljen, egy régi barátomat keresem, "+pchar.GenQuest.FindFugitive.Name+" a neve. Egy kapitánytársam mondta, hogy a településetek felé tart. Találkozott vele véletlenül?";
				link.l12.go = "FindFugitiveTav";
			}
			//<-- поиск дезертира

			link.l15 = "Semmi, köszönöm.";
			link.l15.go = "exit";
		break;
		
		case "hold_genquest1":
			switch(sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = LinkRandPhrase("Mit mondtál? " + pchar.GenQuest.Hold_GenQuest.Name + "? Hmm... Soha nem hallottam róla.",
						"Biztos, hogy a mi városunkból származik? Soha nem hallottam még ilyen emberrôl.",
						"A mi kis telepünkön nem volt ilyen ember. Soha nem hallottam róla, mióta itt vagyok.");
					link.l1 = "Biztos benne?";
					link.l1.go = "hold_genquest2";					
				break;
				
				case 1: 
					switch (hrand(3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = "a templom";						
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
							pchar.GenQuest.Hold_GenQuest.foundStr = "a hajógyárban";						
							pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = "the church";						
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = "az uzsorás";												
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = "a bolt";						
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					} 
					dialog.text = "Nézd meg a " + pchar.GenQuest.Hold_GenQuest.foundStr + ", ott elég gyakran megtalálható.";
					link.l1 = "Köszönöm, meg is teszem.";
					link.l1.go = "hold_genquest3";				
				break;
				
				case 2:
					dialog.text = LinkRandPhrase(
						RandPhraseSimple("Mit mondtál? " + pchar.GenQuest.Hold_GenQuest.Name + "? Hmm... Soha nem hallottam róla. Biztos, hogy a mi falunkból származik? Soha nem hallottam még ilyen emberrôl.",
						"Ô-ô... Nos, most már csak maga az Úr tudja, hol keressük ôt - a pokolban vagy a mennyben. Több mint egy éve meghalt, de az emberek még mindig kérdezôsködnek róla... Nincs nyugta szegény szerencsétlennek..."),
						RandPhraseSimple("Ott nem fogod megtalálni - legalábbis az élôk földjén. Nem is olyan régen halt meg - sárgalázban... Isten nyugosztalja a lelkét... Micsoda zömök ember volt! Amikor fiatal volt, nagy kalandor volt! De ha a halál eljön utánad, nem sokat tehetsz...",
						"Ó, hiányzott már? Már régen elhagyta ezeket a helyeket. Senki sem tudja, hová ment - talán az észak-amerikai gyarmatokra, talán haza Európába. Csak összeszedte a holmiját és elment."),
						"Ó, azt a " + pchar.GenQuest.Hold_GenQuest.Name + " keresed, aki meggazdagodott és vett magának egy házat New Englandben? Tudja, volt idô, amikor hitelre adtam neki rumot - még mindig tartozik nekem. Az emberek olyan hálátlanok, tudod.");
					link.l1 = "Értem. Nos, azért köszönöm.";	
					link.l1.go = "hold_genquest4";
				break;
				
				case 3:
					dialog.text = "Hol máshol kereshetném, ha nem a kocsmában? Gyakori vendég ott - borba fojtja a bûneit, he-he-he. Gyere vissza késôbb - ha felbukkan, megmondom neki, hogy várjon rád.";	
					link.l1 = "Köszönöm, úgy lesz.";
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;
		
		case "hold_genquest2":
			dialog.text = "Hogyan nem lehetek biztos benne, ha mindenkit személyesen ismerek itt. Nem ez az elsô év, hogy itt vezetem a kocsmát. "+
				"Mindenkit láttam már minden lehetséges körülmények között. Volt, hogy egy feleség jött a férjéért, volt, hogy maguktól mentek el, és volt, hogy ki kellett ôket dobnom. 'Biztos vagyok benne?!' Persze, hogy biztos vagyok!";
			link.l1 = "Hát, azért köszönöm...";	
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();		
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen")); 			
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;
		
		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");			
			DialogExit();
		break;
		
		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");			
		break;
		
		case "CaptainComission_1":
			dialog.text = LinkRandPhrase("Gyakori látogató itt, de most nincs itt. Jöjjön vissza idôrôl idôre - megmondom neki, hogy itt várjon meg, ha felbukkan.","Ô gyakori látogató itt. Ha késôbb visszajössz, biztosan ott találod.","Gyere vissza idôrôl idôre - gyakori látogató itt. Tudatom vele, hogy kerested.");
			link.l1 = "Köszönöm, késôbb visszajövök...";
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;
		
		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_3":
			dialog.text = "Már idejött, szóval valahol itt kell lennie...";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
		break;
		
		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = "Van olyan ember, aki nem ismeri ôt? Az egész település róla beszél már napok óta.";
			link.l1 = "Tudna többet mondani?";
			link.l1.go = "CaptainComission_Tavern2";
		break;
		
		case "CaptainComission_Tavern2":
			dialog.text = "Egy kicsit, a kapitányt kivégezték, ugyanez mondható el a legénységének egy részérôl. A többieket rangjuktól és pozíciójuktól megfosztva szétszórták a Karib-tengeren... Miért? Egy bíró szerint járôrözés közben elsüllyesztett egy kalózt, a zsákmányt pedig elrejtette magának\n"+
				"A helyzet az, hogy sem a hajó tulajdonosát, sem az árut nem találták meg... átfésülték a helyi öblöket és öblöket a keresésükre, de eredménytelenül.";
			link.l1 = "Mi az, a legénység egyik tagja sem árulta el a rejtekhely helyét?";	
			link.l1.go = "CaptainComission_Tavern3";	
		break;
		
		case "CaptainComission_Tavern3":
			dialog.text = "Egyetlenegyet sem! Még kínzás alatt sem! Még mindig nem értem, miért hisz a kormányzó ilyen buzgón ebben a rágalomban. A " + pchar.GenQuest.CaptainComission.Name + " kapitánynak jó híre volt, a legénysége pedig olyan jól képzett és fegyelmezett, hogy bármelyik admirális megirigyelhette volna.";
			link.l1 = "És hol keressem a legénység túlélô tagjait?";
			link.l1.go = "CaptainComission_Tavern4";
		break;
		
		case "CaptainComission_Tavern4":
			dialog.text = "Ezt nem tudom - szétszóródtak a négy szél felé... Bár... egy még mindig maradt közülük, de kétlem, hogy sokat tanulnál tôle. Súlyos agyrázkódást szenvedett. Tudod, tüzérként szolgált a " + pchar.GenQuest.CaptainComission.Name + "alatt. Két nappal a baleset után eszméletlenül találtak rá egy öbölben. Elôször kórházba küldték, és hôsként kezelték, de ahogy sûrûsödött a cselekmény, bedobták a börtönbe, és megpróbálták kihallgatni, de aztán úgy döntöttek, hogy elôbb úgyis orvosi ellátást kell kapnia.";
			link.l1 = "Még mindig itt van?";
			link.l1.go = "CaptainComission_Tavern5";
		break;
		
		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Igen, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM) + " a neve. Idônként beugrik, a koldulásból szerzett filléreit rumra költi. Szegénykém. Ha látom, megmondom neki, hogy itt várjon rád.";
			link.l1 = "Köszönöm, késôbb visszajövök.";
			link.l1.go = "CaptainComission_Tavern6";
		break;
		
		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar,"GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = "Ismerem ôt? Persze, hogy ismerem. És miért van rá szüksége?";
			link.l1 = "Üzleti ügyem van vele...";
			link.l1.go = "CaptainComission_Tavern8";
		break;
		
		case "CaptainComission_Tavern8":
			dialog.text = "" + GetAddress_Form(pchar) + ", óvatosnak kell lenned ezzel 'business'. " + pchar.GenQuest.CaptainComission.Name + " kalózkodás gyanújával ôrizetbe vették, és a kormányzó emberei most a bûntársai után kutatva járják a szigetet.";
			link.l1 = "Ne is mondd! És mit csinált?";
			link.l1.go = "CaptainComission_Tavern9";
		break;
		
		case "CaptainComission_Tavern9":
			dialog.text = "Nem tudom, hogy igaz-e vagy sem, de azt mondják, hogy elrejtette egy átutazó kalózhajóról elkobzott rakományt, és nem adta le. És még mindig nem találták meg sem azt a kalózt, sem a rakományt. Még mindig nem értem, miért hisz a kormányzó ilyen buzgón ebben a rágalomban. A " + pchar.GenQuest.CaptainComission.CapName + "  kapitánynak tisztességes híre volt, és nagyszerû katona volt, a szavamban megbízhatsz, " + GetAddress_Form(pchar) + ".";
			link.l1 = "Nos, köszönöm a figyelmeztetést. Viszlát.";
			link.l1.go = "CaptainComission_Tavern10";
		break;
		
		case "CaptainComission_Tavern10":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}			
			DialogExit();
		break;
				
		case "EncGirl_1":
			dialog.text = "És mire van rá szüksége?";
			link.l1 = "Üzleti ügyem van vele...";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Úgy tûnik, a településünkön a férfiak felének van dolga vele. Ha az asszonyaink elkapták volna, meztelenül dobták volna ki a városkapun kívülre.";
			link.l1 = "Ó, hát... "+ GetSexPhrase("Úgy tûnik, akkor hosszú sorba kerültem. Nos, ha valaki más is jön és ôt keresi, mondd meg neki, hogy álljon be mögém a sorba.","Látom") +"...";
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;
		
		case "EncGirl_3":
			dialog.text = "Gyakori látogató itt - általában munkát keresve jön át, de most nincs itt. Jöjjön vissza idôrôl idôre - megmondom neki, hogy várjon itt önre, ha felbukkan.";
			link.l1 = "Köszönöm, késôbb visszajövök...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ó, szóval te vagy "+ GetSexPhrase("az a kapitány, aki elhozta","azt a lányt, aki elhozta") +" a tékozló fiamat egy fiatal arával?";
				link.l1 = "Igen, én voltam az, aki segített.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ó, ott "+ GetSexPhrase("ô, a mi jótevônk","ô, a mi jótevônk") +". Jutalomra számítasz, ugye?";
				link.l1 = "Nos, jutalom nélkül is jól megvagyok, de már a köszönet is megteszi.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Nagyon hálás vagyok neked, hogy nem hagytad magára a fiamat a legnagyobb bajban, és segítettél neki kiutat találni egy kényes helyzetbôl. Engedje meg, hogy megköszönjem, és kérem, fogadja el ezt a szerény összeget és a személyes ajándékomat.";
			link.l1 = "Köszönöm. Örömömre szolgált, hogy segíthettem ennek a fiatal párnak.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Köszönöm. Milyen köszönet?! Már fél éve, hogy az a tökfej munka nélkül lógott - és nézd meg, van ideje egy viszonyra is! Amikor én annyi idôs voltam, mint ô, már a saját vállalkozásomat vezettem! Pfft! Egy kormányzónak van egy házasulandó lánya - és ez a tökfilkó egy rokonok nélküli ribancot hozott a házamba, és még az áldásomat is kérni merte!";
			link.l1 = "Gondolom, nem hiszel a szerelemben elsô látásra?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "A szerelemben? A szerelemben!? Most gúnyolódsz velem, vagy hülye vagy? Szégyelld magad, hogy engedsz a fiatalok szeszélyeinek, és úgy viselkedsz, mint egy kerítô! Nemcsak egy lányt vettél el az otthonából, hanem tönkretetted a fiam életét is. Nem lesz köszönet neked. Viszlát.";
			link.l1 = "Akkor neked is.";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
				
		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Hadd nézzem meg! Hmm... De te magad is kapitány vagy. Szerintem a kikötômesterrel kellene beszélned errôl.";
				link.l1 = "Köszönöm a tanácsát.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Hadd nézzem meg! Ó! A nevébôl ítélve ez az egyik patrónusomé, egy igen tekintélyes úriemberé. Én magam is átadhatom ezeket az iratokat a tulajdonosnak. Odaadná nekem?";
				link.l1	= "Ha jobban belegondolok...";
				link.l1.go = "exit";
				link.l2 = "Vigye ôket. Örülök, hogy a szolgálatára lehetek.";
				link.l2.go = "ShipLetters_end";				
			}	
		break;
		
		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//zagolski. переделка
		case "work":
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = RandPhraseSimple("Nem érdekel, hogy kit szolgáljak, mivel a pénznek nincs nemzetisége. De nem fogok segíteni neked, mivel a " + NationNameGenitive(sti(pchar.nation)) + "zászlaja alatt jöttél.", "Én csak egy egyszerû kocsmáros vagyok, de a " + NationNameAblative(sti(pchar.nation)) + " együttmûködés nem tûnik vonzónak számomra.");
				link.l1 = RandPhraseSimple("Nos, ahogy kívánod...", "Nos, ahogy kívánod...");
				link.l1.go = "exit";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				dialog.text = RandPhraseSimple("Általában sok utasunk van itt. Mégis, nem hiszem, hogy lenne köztük akár csak egy duffy is, aki hajlandó lenne az önök hajóján utazni. A rossz hírneved megelôz téged, csak egy bolond szállna hajóra egy ilyen gazemberrel.", "engem elég gyakran keresnek meg kereskedôk, akiknek kíséretre van szükségük. De a rossz hírneved megelôz téged, és nem foglak ajánlani senkinek. Tudja, vigyázok a saját hírnevemre. Senki sem akar egy farkast felbérelni, hogy ôrizze a bárányait.");
				link.l1 = RandPhraseSimple("Ó, tényleg, nem kéne elhinni ezt a sok pletykát...", "Értem. Nehéz mindenkit elhallgattatni.", "Az emberek túl puhányak manapság...");
				link.l1.go = "exit";
				break;
			}
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
        	{
				dialog.text = "És hol van a hajód? Vagy a hátadon viszed az utasokat és úszol?";
				link.l1 = "Hé, igazad van...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Talán lenne munkám, ha nem félsz kalóztelepülésekre vagy ellenséges nemzetek kikötôibe jönni. Keres valamit konkrétan?";
			link.l1 = "Az nem lehet probléma. Azt hiszem, tudnék kíséretet biztosítani.";
			link.l1.go = "work_1";
			link.l2 = "Vannak utasai? Oda viszem ôket, ahová csak akarják, ha fizetnek érte.";
			link.l2.go = "work_2";
			link.l3 = "Nem, az ilyen munka nem nekem való. Köszönöm. Köszönöm.";
			link.l3.go = "exit";
		break;

		case "work_1":
				dialog.text = "Általában nem kérdeznek meg a kíséretrôl. Kérdezd meg a kereskedôket a kocsmában - talán szükségük lenne a szolgálataidra.";
				link.l1 = "Rendben, ahogy mondod.";
                link.l1.go = "exit";
		break;

		case "work_2":
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
    		{					
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
				{
					dialog.text = "Sajnálom, de nincs senki, aki hajlandó lenne önnel utazni.";
					link.l1 = "Értem, értem.";
					link.l1.go = "exit";
					break;
				}
		         // пассажир
				if (hrand(6) > 1)
				{
					dialog.Text = "Van egy férfi, aki épp most jött be - nemrég érdeklôdött egy arra járó hajóról. Beszélhetsz vele, ha szeretnél.";
					link.l1 = RandPhraseSimple("Ki ô? Talán egy gazember? Vagy, ami még rosszabb, egy körözött kalóz?", "És ki ô? Vajon lesz-e vele valami baj?");
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = "Nem, ma még senki sem kérdezett róla. Talán majd máskor.";
					link.l1 = RandPhraseSimple("Nos, ha nincs ott, akkor nincs...", "Csak az én szerencsém... Ó, nos, akkor viszlát.");
					link.l1.go = "exit";
				}
            }
    		else
    		{
				dialog.text = "Ma nincs senki. Jöjjön vissza pár nap múlva.";
				link.l1 = "Rendben, ahogy mondod.";
                link.l1.go = "exit";
    		}
        break;

        case "ConvoyAreYouSure":
		    dialog.text = LinkRandPhrase("Ki tudhatja? Te kérdezted - én válaszoltam.", "Nos, ezt neked kell megoldanod. Én nem kezeskednék senkiért ott.", "Mindenféle ember jár ide. Ez egy kocsma, kapitány, nem a kormányzó kastélya.");
			Link.l1 = "Köszönöm, akkor majd alkudozunk.";
			Link.l1.go = "exit";
			pchar.quest.destination = findTraderCity(npchar);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

        case "PassangerAreYouSure":
		    dialog.text = LinkRandPhrase("Ki tudhatja? Te kérdezted - én válaszoltam.", "Nos, ezt neked kell megoldanod. Én nem kezeskednék senkiért ott.", "Mindenféle ember jár ide. Ez egy kocsma, kapitány, nem a kormányzó kastélya.");
			Link.l1 = "Értem, értem. Derítsük ki, ki ez az ember...";
			Link.l1.go = "exit";
			sGlobalTemp = findPassangerCity(npchar);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
        break;

		 case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Helen_room":
			dialog.text = "Természetesen, Helen. Meddig maradsz? És mi van, összevesztél az öreg Gladysszel?";
			if(!isDay())
			{
				link.l1 = "Csak aludni reggelig. Ha most hazamegyek, biztosan felébresztem.";
				link.l1.go = "Helen_room_day";
			}
			else
			{
				link.l1 = "Nem, nem, csak el kell indulnom éjszaka, és nem akarom felébreszteni.";
				link.l1.go = "Helen_room_night";
				link.l2 = "Szeretnék egy jó hosszút aludni, és nyugodtan felkelni. Kiveszek egy szobát egy napra.";
				link.l2.go = "Helen_room_day_next";
			}
		break;

		case "room":
   			if (chrDisableReloadToLocation || CheckAttribute(pchar, "GenQuest.TavernClose")) //кто-то должен подойти к ГГ.
			{
				dialog.text = "A szoba foglalt, " + GetAddress_Form(NPChar) + ", semmit sem tehetek önért.";
				link.l1 = "Hát, ez kár...";
				link.l1.go = "exit";
				break;
			}
			// суп из черепахи
			if (CheckAttribute(pchar, "questTemp.Terrapin.Room_close") && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "Monsieur Henri Thibaut jelenleg bérli a szobát, és egy hónapra elôre kifizette, úgyhogy nem tehetek semmit önért, kapitány úr.";
				link.l1 = "Hát, ez kár...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "cave" && npchar.location == "Tortuga_tavern")
			{
				dialog.text = "A szoba foglalt, " + GetAddress_Form(NPChar) + ", semmit sem tehetek önért.";
				link.l1 = "Hát, ez kár...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "shore" && npchar.location == "Baster_tavern") // 070712
			{
				dialog.text = "A szoba foglalt, " + GetAddress_Form(NPChar) + ", semmit sem tehetek önért.";
				link.l1 = "Hát, ez kár...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_tavern") // Блеквуд в городе
			{
				Dialog.text = "Sajnos nem, kapitány. Minden szobát Blackwood és az emberei foglaltak el.";
				if (CheckAttribute(pchar, "questTemp.LadyBeth_TavernRoomDialog"))
				{
					link.l1 = "Ó, milyen kár!";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Minden szobát? Több szoba is van itt?";
					link.l1.go = "LadyBeth_Room";
				}
				break;
			}
			//-->> квест официантки
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = "Szeretne bérelni egy szobát? Nem probléma. 100 darab pesó, és a magáé.";
				if (sti(pchar.money) >= 100)
				{
					link.l1 = "Itt a pénze.";
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = "Hmm... Azt hiszem, késôbb visszajövök...";
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = "A szoba a tiéd. Gyere be és pihenj.";
				link.l1 = "Kösz, haver.";
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки
			// --> квест "A damsel in the jungle"
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if(pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = "Szeretne bérelni egy szobát? Nem probléma. 100 darab pesó, és a magáé.";
					if (sti(pchar.money) >= 100)
					{
						link.l1 = "Itt a pénze.";
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = "Hmm... Azt hiszem, késôbb visszajövök...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp")//квест  по спасению тетки в пампасах
				{
					dialog.text = "A szoba a tiéd. Gyere be és pihenj.";
					link.l1 = "Kösz, haver.";
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "A damsel in the jungle"

			// belamour постоялец -->
			if (CheckAttribute(pchar, "GenQuest.Unwantedpostor") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && abs(50-sti(pchar.reputation.nobility)) > 20)
			{
				if(pchar.GenQuest.Unwantedpostor == "start")
				{
					SetFunctionTimerCondition("Unwantedpostor_OneDay", 0, 0, 1, false);
					pchar.GenQuest.Unwantedpostor = "timer";
				}
				dialog.text = "Elnézést, kapitány, sajnos nincs szabad szoba. A vendég nem akar elmenni. És még mindig nem fizetett...";
				link.l1 = "Úgy tûnik, az éjszakát a közös helyiségben kell töltenünk...";
				link.l1.go = "Unwantedpostor_hall_day_wait";
				link.l2 = "Sajnálom. Beszéljünk valami másról.";
				link.l2.go = "int_quests";
				if(pchar.GenQuest.Unwantedpostor != "Lose")
				{
					link.l3 = "Akkor hívd az ôröket. Miféle vendég ez: nem fizet, nem akar kiköltözni...";
					link.l3.go = "Unwantedpostor";
				}
				break;
			}
			//<-- постоялец

			dialog.text = "Meddig akar itt maradni?";
			if(!isDay())
			{
				link.l1 = "Reggelig.";
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = "Estig.";
				link.l1.go = "room_night";
				link.l2 = "Másnap reggelig.";
				link.l2.go = "room_day_next";
			}
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				pchar.questTemp.MarySexBlock = true;
				SetTimerFunction("Mary_DeleteSexBlock", 0, 0, 1);
			}
		break;

		case "room_day":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "A szoba az ön rendelkezésére áll, kapitány. Teljesen ingyen.";
				link.l1 = "Kösz, haver.";
				link.l1.go = "room_day_wait";
				link.l3 = "Ne most. Beszéljünk valami másról.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Ez 5 darab pesóba fog kerülni.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Megegyeztünk. Tessék.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase("Ennyiért? Királyi szobát bérelsz? Inkább a közös szobában maradnék ingyen.",
            "Sajnos, az ágyon alvás luxusa meghaladja a jelenlegi lehetôségeimet, úgy tûnik. Azt hiszem, kénytelen leszek a közös szobában aludni egy padon.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Ne most. Váltsunk témát.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_day_next":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "A szoba az ön rendelkezésére áll, kapitány. Teljesen ingyen.";
				link.l1 = "Kösz, haver.";
				link.l1.go = "room_day_wait_next";
				link.l3 = "Ne most. Beszéljünk valami másról.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Ez 10 darab pesóba fog kerülni.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Megegyeztünk. Tessék.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase("Ennyiért? Királyi szobát bérelsz? Inkább a közös szobában maradnék ingyen.",
            "Sajnos, az ágyon alvás luxusa meghaladja a jelenlegi lehetôségeimet, úgy tûnik. Azt hiszem, kénytelen leszek a közös szobában aludni egy padon.");
			link.l2.go = "hall_day_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Ne most. Váltsunk témát.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night":
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_FreeBuhlo") && npchar.id == "PuertoPrincipe_tavernkeeper")
			{
				dialog.text = "A szoba az ön rendelkezésére áll, kapitány. Teljesen ingyen.";
				link.l1 = "Kösz, haver.";
				link.l1.go = "room_night_wait";
				link.l3 = "Ne most. Beszéljünk valami másról.";
				link.l3.go = "int_quests";
				break;
			}
			dialog.text = "Ez 5 darab pesóba fog kerülni.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Megegyeztünk. Tessék.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase("Ennyiért? Királyi szobát bérelsz? Inkább a közös szobában maradnék ingyen.",
            "Sajnos, az ágyon alvás luxusa meghaladja a jelenlegi lehetôségeimet, úgy tûnik. Azt hiszem, kénytelen leszek a közös szobában aludni egy padon.");
			link.l2.go = "hall_night_wait";
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				link.l3 = "Ne most. Váltsunk témát.";
				link.l3.go = "int_quests";
			}
		break;

		case "room_night_wait":
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (hRand(3) == 1)
            {
                Dialog.text = "Takarodj innen a fenébe, te gazember! Lehet, hogy a közös szoba ingyen van, de elvárásaink vannak a tisztességes viselkedéssel szemben!";
				link.l1 = "Rendben, rendben, én megyek.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			// belamour прерывание ночной приключенец -->
			if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
			{
				if(GetCharacterIndex(pchar.GenQuest.NightAdventureId) != -1)
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
				SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
			}
			// <-- прерывание ночного приключенца 
			if (CheckAttribute(pchar, "GenQuest.LigaAttack") && hrand(1) == 1)
			{
				TavernWaitDate("wait_night");
				pchar.GenQuest.LigaAttack.Go = "true"; //атака киллеров
			}
			else TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Takarodj innen a fenébe, te gazember! Lehet, hogy a közös szoba ingyen van, de elvárásaink vannak a tisztességes viselkedéssel szemben!";
				link.l1 = "Rendben, rendben, én megyek.";
				link.l1.go = "exit";
            }
            else
            {
				// belamour прерывание ночной приключенец -->
				if(CheckAttribute(pchar,"GenQuest.NightAdventureId"))
				{
					sld = characterFromId(pchar.GenQuest.NightAdventureId);
					ChangeCharacterAddressGroup(sld, "none", "", "");
					SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
				}
				// <-- прерывание ночного приключенца
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = "Azonnal hagyd abba ezt a felháborító viselkedést a kocsmámban, vagy hívom az ôrséget!";
			link.l1 = "Rendben, rendben, én megyek.";
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = "Nem sokat tudok róla... Jobb, ha megkérdezed a vendégeket.";
			link.l1 = "Értem, köszönöm.";
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;
			
		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = "Nem nyújtunk szolgáltatást hitelre, "+ GetSexPhrase("uram","miss") +".";
			link.l1 = "Jó érmével fizetek. Már nem fogadnak el aranyat vagy ezüstöt?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = "Sajnálom, "+ GetSexPhrase("mister","miss") +" kapitány, de a barátjának adóssága volt, és azt hittem...";
			link.l1 = "Gondolkodj kevesebbet és dolgozz gyorsabban, pajtás. Nos, mennyivel tartozik neked az én bátor barátom?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3)+1)*100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if(rand(1) == 0) // "If he's a simple one and pays right away"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", mis"+ GetSexPhrase("ter","s") +" kapitány, és zálogba adott néhány egyházi könyvet is - ennyi volt nála, ami valamilyen értéket képviselt.";
				if(sti(PChar.money) >= iTemp)
				{
					link.l1 = "Itt vannak az érméid. Add át a kéziratokat. És óvatosan bánjatok velük - ez nem egy fapados fametszetekkel teli könyv, hanem a Szentírás!";
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = "Várj egy kicsit... Visszajövök a pénzzel.";
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "If he's not a simple one"
			{
				dialog.text = FindRussianMoneyString(iTemp) + ", mis"+ GetSexPhrase("ter","s") +" kapitány.";
				link.l1 = "Kifizetem az adósságát, és elveszem, amit otthagyott, hogy biztosítsam.";
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = "Nem, mis"+ GetSexPhrase("ter","s") +", ez így nem fog mûködni.";
			link.l1 = "Hogy érted azt, hogy - 'ez nem fog így mûködni'? Egy kapitány adósságát kifizette - ô jó. Visszakaptad a pénzed - jól vagy. Elfogadom a zálogát - jó vagyok. Mindenki jó - akkor miért 'ez nem fog így mûködni'?";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = "Mert, mis"+ GetSexPhrase("ter","s") +" kapitány, nekem nem kell a pénz. Mert túlságosan jól ismerem azt a kapitányt, ezért igazából soha nem vártam, hogy visszafizeti és elveszi tôlem ezeket a kéziratokat.";
			link.l1 = "Hogy érti, hogy nincs szüksége pénzre? Tehát kezdettôl fogva azt tervezte, hogy megtartja ezeket a könyveket? De miért, az Isten szerelmére?!";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = "Isten nevében - pontosan ezért, mis"+ GetSexPhrase("ter","s") +". A kisfiam nagyon beteg volt, és én és a feleségem fogadalmat tettünk, hogy adakozunk az egyháznak, ha a mi Boldogságos Urunk meggyógyítja a gyermeket a láztól. Urunk kegyelme végtelen, a kisfiam él és egészséges, és most be kell tartanunk fogadalmunkat. És éppen ideje, hogy felbukkanjon " + PChar.GenQuest.ChurchQuest_1.CapFullName + " kapitány és zálogba adja ezeket az egyházi könyveket. Nem engedhettem meg ezt az obszcenitást - az Ige fizet az italokért -, ezért úgy döntöttem, hogy átadom ezeket a könyveket a gyülekezetünk lelkipásztorának.";
			link.l1 = "Nos, ez bizonyára jó cselekedet, de azt is tudnotok kell, hogy ezek a könyvek valójában egy másik papé - valójában nem csak papé, hanem püspöké és lelki pásztoromé. Ô pedig lehet, hogy megharagszik, és még pontosan meg is fogja büntetni azokat, akik lopott egyházi tulajdont merészelnek adományozni. Szeretném megvásárolni önöktôl és biztonságban hazahozni ôket. A pénzt felajánlhatja az egyházközségének, biztos vagyok benne, hogy Isten ezt is értékelni fogja.";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = "Mis"+ GetSexPhrase("ter","s") +"... Mis"+ GetSexPhrase("ter","s") +" captain... Persze, fogalmam sem volt róla! Visszaadom ôket, és nem kérek érte cserébe pénzt. Csak szóljon egy szót az érdekünkben a püspöknél - talán megáld minket, és felment minket a fogadalmunk alól...";
			link.l1 = "Természetesen a fogadalmatokat megtartottnak tekintjük! Elvégre önök lemondtak a nyereségükrôl, hogy visszaadják a könyveket jogos tulajdonosuknak. Az adott egyház nem számít, hiszen csak egy Isten és egy Szent Katolikus Apostoli Egyház van, nem igaz? Rendben, add ide ôket, és sok szerencsét neked...";
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;
			
		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;
		
		//Jason --> генератор Неудачливый вор
		case "Device_Tavern":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Még sosem hallottam róla... Mi is ez tulajdonképpen? Még sosem hallottam ilyesmirôl.";
			link.l1 = "Nos, ez egy hajóépítô szerszám, "+pchar.GenQuest.Device.Shipyarder.Describe+". Ajánlott neked valaki ilyesmit?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 6)
			{
				dialog.text = "Hmm... Igen, egy furcsa típus valóban elhozta nekem ezt a dolgot. Azt azonban nem mondta meg, hogy mi az - csak fáradtan cserélte el piára. Természetesen visszautasítottam - nem volt szükségem arra a csecsebecsére.";
				link.l1 = "És hogy nézett ki, és hová ment? Nagy szükségem van arra a hangszerre.";
				link.l1.go = "Device_Common";
			}
			else
			{
				dialog.text = "Nem, semmi ilyesmi. Sajnálom, nem tudok segíteni. Kérdezôsködjön.";
				link.l1 = "Értem. Nos - itt az ideje, hogy körbekérdezôsködjek!";
				link.l1.go = "exit";
			}
		break;
		// <-- генератор Неудачливый вор
		
		//Jason --> генератор Место под солнцем
		case "Sunplace_Tavern":
			if (makeint(environment.time) > 12.0 && makeint(environment.time) < 17.0)//в магазине
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Nemrég járt ott, és mostanra már el kellett volna jönnie a társához - a boltoshoz. Próbálja megkeresni a boltban - biztosan ott van.";
				link.l1 = "Köszönöm! Sokat segítettél nekem!";
				link.l1.go = "Sunplace_Tavern_1";
			}
			else//ушел на рыбалку
			{
				dialog.text = ""+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Ma kora reggel kihajózott a luggerén egy tengerészhez. Lefogadom, hogy most a bástyánál áll, és gyönyörködik a kilátásban. Ha szükséged van rá, megpróbálhatod megkeresni a tengeren, vagy megvárhatod, amíg pár nap múlva visszajön...";
				link.l1 = "Köszönöm! Azt hiszem, nem fogok várni - könnyebb lesz megtalálni ôt a tengeren. Sok szerencsét!";
				link.l1.go = "Sunplace_Tavern_2";
			}
		break;
		
		case "Sunplace_Tavern_1"://магазин
			pchar.quest.Sunplace_Store.win_condition.l1 = "location";
			pchar.quest.Sunplace_Store.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.CityT + "_store";
			pchar.quest.Sunplace_Store.function = "Sunplace_CreateTrader";
			AddQuestRecord("Sunplace", "6");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		
		case "Sunplace_Tavern_2"://рыбалка
			pchar.GenQuest.Sunplace.Trader.IslandID = GetCharacterCurrentIslandId(npchar);
			pchar.GenQuest.Sunplace.Trader.EnemyNation = npchar.nation;
			pchar.quest.Sunplace_Sea.win_condition.l1 = "location";
			pchar.quest.Sunplace_Sea.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.IslandID;
			pchar.quest.Sunplace_Sea.function = "Sunplace_CreateTraderLugger";
			AddQuestRecord("Sunplace", "7");
			AddQuestUserData("Sunplace", "sName", pchar.GenQuest.Sunplace.Trader.Enemyname);
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Gen"));
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "hunt";
		break;
		// <-- генератор Место под солнцем	
		
		// Jason --> Голландский гамбит
		case "HWICHollJacob_Tavern":
			dialog.text = "Psssst... Miért kiabálsz? Már jó ideje vár rád. Már egy egész liter rumot megivott. Menj fel a szobájába, ott megtalálod.";
			link.l1 = "Ó, értem. Remélhetôleg még ébren van.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern", "reload2_back", false);
			pchar.questTemp.HWIC.Holl = "JacobInRoom";
			AddDialogExitQuestFunction("Create_JacobVanBerg");
			DelLandQuestMark(npchar);
		break;
		
		case "HWICSelfFernando_Tavern":
			if (NPChar.location == pchar.questTemp.HWIC.Self.SpainCity +"_tavern")
			{
				//DelMapTonzagAllQM();
				dialog.text = "Igen, ismerem azt az urat. Valahol a városban kell lennie - nemrég láttam az ablakom elôtt elsétálni.";
				link.l1 = "Köszönöm! Megyek és megkeresem!";
				link.l1.go = "Fernando_Land";
				/* if (makeint(environment.time) > 10.0 && makeint(environment.time) < 18.0)//на улице
				{
					dialog.text = "Igen, ismerem azt az urat. Valahol a városban kell lennie - nemrég láttam az ablakom elôtt elsétálni.";
					link.l1 = "Köszönöm! Megyek és megkeresem!";
					link.l1.go = "Fernando_Land";
				}
				else //в море
				{
					dialog.text = "Igen, most éppen a városunkba látogat. Most nincs itt - elhajózott a brigantijával. Valószínûleg nincs messze innen, a szigetünk vizein belül.";
					link.l1 = "Köszönöm, pajtás! Sokat segítettél nekem!";
					link.l1.go = "Fernando_Sea";
				} */
				pchar.questTemp.HWIC.Self = "KillFernando";
			}
			else
			{
				dialog.text = "Fernando Rodriguez? Sosem hallottam róla. Nem, semmit sem tudok errôl az emberrôl.";
				link.l1 = "Értem... Nos, a keresés folytatódik....";
				link.l1.go = "exit";
			}
			npchar.quest.HWICTalked = "true";
		break;
		
		case "Fernando_Land":
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.SpainCity +"_town";
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnLand";
			AddQuestRecord("Holl_Gambit", "3-2");
			DialogExit();
		break;
		
		case "Fernando_Sea":
			pchar.questTemp.HWIC.Self.FernandoIslandID = GetCharacterCurrentIslandId(npchar);
			pchar.quest.HWIC_Fernando.win_condition.l1 = "location";
			pchar.quest.HWIC_Fernando.win_condition.l1.location = pchar.questTemp.HWIC.Self.FernandoIslandID;
			pchar.quest.HWIC_Fernando.function = "CreateFernandoOnSea";
			AddQuestRecord("Holl_Gambit", "3-3");
			DialogExit();
		break;
		//<-- Голландский гамбит
		
		//Jason --> гонки на гидропланах
		case "Race_Advantage":
			dialog.text = "Igen, persze. Gratulálok, kapitány. Már tudok a gyôzelmérôl. Itt a pénze.";
			link.l1 = "Köszönöm, " + npchar.name + ".";
			link.l1.go = "Race_Advantage_1";
		break;
		
		case "Race_Advantage_1":
			DialogExit();
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Racing.Go.Money)*2);
			AddQuestRecord("Racing", "4");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			CloseQuestHeader("Racing");
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
		break;
		//<-- гонки на гидропланах
		
		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = "Errr, uram, "+pchar.GenQuest.Marginpassenger.q2Name+" meghalt körülbelül "+LinkRandPhrase("egy hónapja","három hete","két hónapja")+" . "+LinkRandPhrase("hirtelen láznak adta át magát","A város kapujában leszúrták - banditák vagy azok a vörösbôrû vademberek","Párbajban lelôtték")+". Isten nyugosztalja a lelkét...";
				link.l1 = "A francba!... És mit csináljak az ô... Hát, mindegy. Köszönöm az információt. Viszlát, " + npchar.name + ".";
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.Marginpassenger.q2Name+"? Igen, valahol a városban kell lennie. Keressétek az utcán. De ne feledd, hogy minden nap délig a kormányzói hivatalban van, este kilenc után pedig bezárkózik a házába.";
				link.l1 = "Köszönöm! Megyek és megkeresem...";
				link.l1.go = "Marginpassenger_2";
			}
		break;
		
		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров
		
		//Jason --> поиск дезертира
		case "FindFugitiveTav":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 0)
			{
				dialog.text = NPCStringReactionRepeat("Úgy tûnik, hogy a kapitánya igazat mondott. "+pchar.GenQuest.FindFugitive.Name+" valóban nemrég érkezett a településünkre. Keressétek ôt az utcákon napközben - általában ott lôdörög az idejét.", "Már kérdezôsködtél arról az emberrôl, és én mindent elmondtam, amit tudok!", "Most viccelsz velem, vagy tényleg idióta vagy?! Már harmadszorra kérdezed ugyanezt!", "Ha belegondolok, hogy egy ilyen idióta hogyan lehetett kapitány...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Köszönöm, barátom, sokat segítettél nekem!", "Igen, igen, rendben.", "Hû, hû, hû, ne izgulj annyira. Csak elfelejtettem.", "Nos, igen, ahogy láthatod...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveTav_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Nem, haver, még sosem hallottam ezt a nevet. Kérdezôsködj - talán valaki ismeri...", "Már kérdezett engem arról az emberrôl, és én elmondtam: Nem tudom!", "Most viccelsz velem, vagy tényleg idióta vagy?! Már harmadszor kérdezed ugyanezt!", "Csak belegondolni, hogy egy ilyen idióta hogyan lehetett kapitány...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Értem. Nos, azért köszönöm.", "Igen, igen, rendben.", "Wow, Wow, ne izgulj annyira. Csak elfelejtettem.", "Nos, igen, ahogy láthatod...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveTav_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-1");
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_city";
			LAi_SetLoginTime(sld, 11.0, 18.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_town", "goto", "goto"+(rand(9)+1));
		break;
		//<-- поиск дезертира
		
		//--> Бремя гасконца
		case "Sharlie_crew":
			dialog.text = "Sajnos, most nem tudok segíteni neked - senki az ismerôseim közül nem szolgálna alattad. De egy tanácsot adhatok - beszélj azzal a matrózzal, aki épp most foglalt asztalt mögötted. Ô és a haverjai épp most hagytak el egy kereskedelmi hajót. Talán hajlandóak lesznek veled tartani.";
			link.l1 = "Rendben, meg is teszem! Köszönöm szépen!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "sailor";
			//усадим матроса Алонсо
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSailor" , "Alonso", "man", "man", 10, FRANCE, -1, true, "quest"));
			sld.name 	= StringFromKey("HollandGambit_23");
			sld.lastname = "";
			FantomMakeCoolFighter(sld, 10, 20, 20, "blade_05", "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Sharlie_sailor";
			sld.greeting = "town_sailor";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("FortFrance_tavern", "sit7");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit7");
			AddQuestRecord("Sharlie", "6-1"); // mitrokosta
		break;
		
		case "Sharlie_skiper":
			dialog.text = "Nem tudok semmi konkrétumot mondani, barátom. Jelenleg nem járnak hozzám navigátorok. Próbálj meg kérdezôsködni a kikötôben - talán az emberek többet tudnak.";
			link.l1 = "Értem, értem. Rendben, megyek és beszélek az emberekkel.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "findskiper";
			//сгенерим наводчика
			sld = GetCharacter(NPC_GenerateCharacter("SharlieSkiperTalker", "citiz_"+(rand(19)+21), "man", "man", 10, FRANCE, -1, true, "marginal"));
			FantomMakeCoolFighter(sld, 10, 20, 20, RandPhraseSimple("blade_04","blade_06"), "", "", 10);
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "skipertalker";
			sld.greeting = "marginal";
			LAi_SetWarriorType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "patrol", "patrol"+(rand(13)+1));
			LAi_SetLoginTime(sld, 6.0, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Бремя гасконца
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_tortuga":
			sld = characterFromId("Tortuga_waitress");
            dialog.text = "Azonnal, uram!... A legjobb francia bor! "+sld.name+"! Menj, készítsd elô a legjobb vendégszobát! Ez 1000 pezó lesz, monsieur.";
			link.l1 = "Tessék.";
			link.l1.go = "mtraxx_tortuga_1";
		break;
		
		case "mtraxx_tortuga_1":
			AddMoneyToCharacter(pchar, -1000);
            DialogExit();
			pchar.questTemp.Mtraxx.Retribution = "room";
			pchar.quest.mtraxx_retribution_room.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.mtraxx_retribution_room.function = "Mtraxx_RetributionToRoom";
		break;
		// belamour постоялец -->
		case "Unwantedpostor_hall_day_wait":
			if (hrand(1) == 1)
            {
                Dialog.text = "Kifelé, gazember! Értékes helyet foglalsz el a fizetô vendégeknek!";
				link.l1 = "Rendben, rendben... Elmegyek.";
				link.l1.go = "exit";
            }
            else
            {
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;
		
		case "Unwantedpostor":
				dialog.text = "Igen - és megijeszted az összes vendégemet azzal, hogy az ôreim kirángatják az embereket a kocsmából? És néhány vendégem nem szeret katonák közelében lenni. Idegesíti ôket, érted? Nem akarom tönkretenni a hírnevemet...";
				link.l1 = "Hmm, mi lenne, ha megoldanám a problémáját?";
				link.l1.go = "Unwantedpostor_1";
		break;
		
		case "Unwantedpostor_1":
				dialog.text = "Meggondolod magad? Fegyver van nála, valamiféle profi zsoldos...";
				link.l1 = "Hmm, igazad van, nincs kedvem vitatkozni egy fegyveres zsoldossal...";
				link.l1.go = "Exit";
				link.l2 = "Nos, én sem vagyok egy zárdába zárt apáca... És még mindig ki akarok bérelni egy szobát.";
				link.l2.go = "Unwantedpostor_2";
		break;
		
		case "Unwantedpostor_2":
				dialog.text = "Nos, ha meg tudod gyôzni, hogy költözzön ki, akkor a szoba reggelig a tiéd. Természetesen ingyen.";
				link.l1 = "Tudja, meggondoltam magam. Nincs kedvem meggyôzni senkit.";
				link.l1.go = "Exit";
				link.l2 = "Ezt nézze meg. A nem kívánt vendéged mindjárt kirepül a kocsmádból, mint egy óriási sirály.";
				link.l2.go = "Unwantedpostor_kikcoff";
		break;
		
		case "Unwantedpostor_kikcoff":
				DialogExit();
				chrDisableReloadToLocation = true; //закрыть локацию
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location+"_upstairs")], true); //запретить драться
				iTemp = sti(pchar.rank) + rand(5);
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Unwantedpostor", "citiz_5"+(rand(3)+1), "man", "man", iTemp, PIRATE, -1, true, "quest")); // "mercen_"+(rand(14)+14)
				FantomMakeCoolFighter(sld, iTemp, 50 + rand(30), 50 + rand(30), "topor_04", "", "bullet", 50);
				sld.dialog.filename = "GenQuests_Dialog.c";
				sld.dialog.currentnode = "Unwantedpostor_room";	
				sld.greeting = "Enc_Raiders"; 
				if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
				{
					DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
					ChangeCharacterAddressGroup(sld, pchar.location+"_upstairs", "quest", "quest3");
				} 
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		// <-- belamour постоялец
		
		case "Helen_room_night":
			dialog.text = "Értem már. Ez öt ezüst lesz.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Persze, tessék.";
				link.l1.go = "room_night_wait";
			}
			link.l2 = "Igazából, tudod mit... Talán majd máskor. A nap hátralévô részét talpon töltöm.";
			link.l2.go = "Helen_night_exit";
		break;
		
		case "Helen_room_day":
			dialog.text = "Bölcs döntés. Öt ezüst lesz, és jó éjszakát kívánok.";
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = "Tessék, és köszönöm - jó éjt.";
				link.l1.go = "room_day_wait";
			}
			link.l2 = "Ha jobban belegondolok, nincs kedvem aludni. Bejárom a várost, szívok egy kis éjszakai levegôt.";
			link.l2.go = "Helen_day_exit";
		break;
		
		case "Helen_room_day_next":
			dialog.text = "Persze, Helen. Tíz pezó lesz.";
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = "Persze, tessék.";
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = "Igazából... Valami hasznosat is csinálhatnék egy egész napot. Talán majd máskor.";
			link.l2.go = "Helen_Next_day_exit";
		break;
		
		case "Helen_night_exit":
			dialog.text = "Ahogy óhajtja, Helen.";
			link.l1 = "Mhm.";
			link.l1.go = "exit";
		break;
		
		case "Helen_day_exit":
			dialog.text = "Talán még álmos is leszel egy jó séta után.";
			link.l1 = "Ha-ha, talán.";
			link.l1.go = "exit";
		break;
		
		case "Helen_next_day_exit":
			dialog.text = "Ahogy jónak látod.";
			link.l1 = "Nos, a következô alkalomig.";
			link.l1.go = "exit";
		break;
		
		case "Helen_rumours_tavern":
			dialog.text = "Persze, Helen, csupa fül vagyok.";
			link.l1 = "Mi a legfrissebb hír vagy érdekes pletyka a városban?";
			link.l1.go = "rumours_tavern";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Room":
			dialog.text = "A szokásos ár háromszorosát fizeti, szóval... érti. És nem ajánlom, hogy visszautasítsa - nehéz természete van. Különösen mostanában.";
			link.l1 = "Mi baja van?";
			link.l1.go = "LadyBeth_Room_2";
		break;
		
		case "LadyBeth_Room_2":
			dialog.text = "Megszállottság, ez az. Eleinte nagylelkû, kedves fickó volt. A matrózai pénzt szórtak a kocsmákban, ajándékokat vettek a lányoknak. Az igazi ünneplés akkor kezdôdött, amikor a 'Lady Beth' kikötôbe érkezett. És most? Most már csak élelmiszert vesznek és válogatás nélkül toboroznak embereket. Mintha nem is matrózokra, hanem csak munkáskezekre lenne szükségük. Nos, beszélhetsz vele te magad is.";
			link.l1 = "Talán fogok is. Köszönöm. Köszönöm.";
			link.l1.go = "exit";
			pchar.questTemp.LadyBeth_TavernRoomDialog = true;
		break;
		// Леди Бет <--
	}
}

string findTraderCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}

string findPassangerCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (colonies[n].nation != "none" && colonies[n].id != "Panama" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (nation == RELATION_ENEMY || sti(npchar.nation) == PIRATE)
			{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hRand(howStore-1)];
	return colonies[nation].id;
}
