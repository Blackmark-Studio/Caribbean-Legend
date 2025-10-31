// общий диалог ростовщиков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag;
	string NPC_Area, sTemp, sTitle, sDepositType1, sDepositType2;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp, iTotalDublonQty;
	int iRes, iPer, iDep;
	float fPer;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;
	sDepositType1 = NPC_Area + "_Type1";
	sDepositType2 = NPC_Area + "_Type2";
 
	if(!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	} 
 
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Usurer\" + NPChar.City + "_Usurer.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }
    if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
    {
        npchar.quest.FindCitizenNoShip = 0;
    }

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				//--> работорговец
				if(pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = " Vége. Most pedig hagyd el ezt a helyet, " + pchar.name + ". Majd én eltakarítom ezt a mocskot.";
					link.l1 = "Rendben, én elhajózom!";
					link.l1.go = "exit";
					break;
				}
				//<-- работорговец
			
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("A városban riadó van, és mindenhol keresnek téged! A helyedben én nem maradnék itt sokáig.", "Minden ôr téged keres. Nem vagyok hülye és nem kockáztatom meg, hogy szóba álljak veled!", "Fuss, "+ GetSexPhrase("pajtás","lány") +", mielôtt a katonák szitává tesznek téged..."), 
					LinkRandPhrase("Mit akarsz, hitvány teremtmény?! A városôrök tisztában vannak a helyzeteddel és nem fogsz elszökni, "+ GetSexPhrase("mocskos kalóz","te kalóz kurva") +"!", "mocskos gyilkos, tûnj el a helyemrôl! Ôrség!", "Nem félek tôled, hitvány teremtmény! Hamarosan felakasztanak az erôdünkben, nem menekülsz..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, nekem ez nem probléma...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Fogd be a szád, " + GetWorkTypeOfMan(npchar, "") + ", vagy levágom a rohadt nyelved!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", akarsz te is kalózt fogni? Figyelj, fiú, ülj itt csendben, és életben maradsz..."));
				link.l1.go = "fight";
				break;
			}
		//Jason ---------------------------------------Бремя гасконца------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_bank")
			{
				dialog.text = "Szüksége van valamire, monsieur?";
				Link.l1 = "Információra van szükségem... Szeretnék kérdezni valamit.";
				Link.l1.go = "quests";
				Link.l2 = "Mit szólnál egy kis kölcsönhöz?";
				Link.l2.go = "sharlie_credit";
				Link.l3 = "Nem, meggondoltam magam.";
				Link.l3.go = "exit";
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Nézze meg ezeket a fülbevalókat, monsieur. Egy bandita zsebében találtam a dzsungelben. Egyértelmûen egy kiváló ékszerész munkája, aki biztos vagyok benne, hogy nem ebbôl a vadonból való. Mit szól hozzá?";
					link.l4.go = "Sharlie_junglejew";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
				{
					link.l1 = "Tudom, hogy van egy Folke Deluc nevû adósa. Mondja csak, mennyire súlyos a... tartozása?";
					link.l1.go = "Sharlie";
				}	
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
				{
					link.l1 = "Folke Deluc adóssága miatt vagyok itt.";
					link.l1.go = "Sharlie_repeat";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
				{
					link.l1 = "Elvégeztem a feladatát, uram. Itt van az ön... spanyol barátja.";
					link.l1.go = "Sharlie_14";
				}
				break;
			}			
		//<-- Бремя гасконца
			
			//--> работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Nos, végre egy méltó kapitány látogatott el hozzám, annyira elegem lett az idiótákból, akik azt hiszik, hogy én csak elültetem a dublonaikat és guineáikat, és havonta szedem a termést, hogy kifizessem nekik a kamatokat\nMinden fillérre figyelnek, miközben fogalmuk sincs, hogy szegény uzsorás hogyan folyamodik különféle trükkökhöz, hogy ne haljon éhen maga is, és közben lehetôséget adjon nekik, hogy karácsonyra libát vehessenek.";
				Link.l1 = "Gondolom, az ön ügyfelei nem örülnek majd, ha ilyen szavakat hallanak attól az embertôl, aki a megtakarításaikat tartja.";
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = "Figyelj, vén hörcsög, most már tényleg mindent meg kell tenned, hogy mindent megmagyarázz nekem! A hajó rakományában nem rabszolgák voltak, hanem egy század katona! Igazán kemény küldetés volt velük elbánni! Nagyon dühös vagyok, úgyhogy jobb, ha megmagyarázod!";
				Link.l1.go = "Slaveshore_5";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Á, végre itt vagy! Az egész szigetvilág pletykál a merész támadásodról. Örülök, hogy látlak!";
				Link.l1 = "Inkább az ismeretlenséget választanám, mint ezt a fajta hírnevet... Túl veszélyes.";
				Link.l1.go = "Win_Havana_Fort";
				break;
			}	
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Elhoztad az ötezer rabszolgámat?";
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = "Hoztam. A raktérben vannak.";
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = "Nem, még dolgozom rajta.";
					Link.l1.go = "exit";
				}
				break;
			}	
			
			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Hm... Még életben vagy? Furcsa. De nem sokáig fog tartani. Katonák! Segítség! Van itt egy bandita!";
				link.l1 = "Micsoda szemétláda!";
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}
			
			if(pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "Jó napot! A nevem " + GetFullName(npchar) + ". Miben lehetek a szolgálatára?";
				link.l1 = "Ó! Mit keres itt, uram?";
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<-- работорговец
			// ФМК-Гваделупа
			if(CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers" && npchar.location == "BasTer_bank")
			{
				dialog.Text = "...";
				link.l1 = "Hé, te szemétláda. Volt egy ragyogó ötlete? Felbéreltél gengsztereket, hogy megöljenek? Le akartál állítani? Beszéljen, most!";
				link.l1.go = "FMQG_x";
				break;
			}
			// Леди Бет -->
			if (pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_Bank" && !CheckAttribute(pchar, "questTemp.LadyBeth_Usurer")) // Блеквуд в городе
			{
				dialog.Text = "Ó, kapitány úr! Kérem, nézze meg, mi van ma nálam. Néhány tárgy, amit Blackwood embereitôl szereztem. Pénzre van szükségük egy új expedícióhoz, és nekünk - profitra, igaz?";
				link.l1 = "Blackwood tudja, hogy az emberei eladják a leleteket?";
				link.l1.go = "LadyBeth_Usurer_1";
				break;
			}
			// Леди Бет <--
			if(NPChar.quest.meeting == "0")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Jó napot kívánok, "+GetAddress_Form(NPChar)+". Miben segíthetek? Ismerem Önt?","Jöjjön be, kapitány. A nevem "+GetFullName(npchar)+" és én vagyok a helyi bankár.","Örvendek, "+GetAddress_Form(NPChar)+"! Én vagyok a helyi bankár, és ha pénzproblémája van, akkor tudok segíteni."), LinkRandPhrase("Találkoztunk már korábban, kapitány úr? A nevem "+GetFullName(npchar)+", és helyi bankár vagyok.","Jöjjön be, kapitány. A nevem "+GetFullName(npchar)+" és én vagyok a helyi bankár.","Üdvözlöm, "+GetAddress_Form(NPChar)+". Én vagyok "+GetFullName(npchar)+", a helyi bankár."), LinkRandPhrase("Örvendek, "+GetAddress_Form(NPChar)+", én "+GetFullName(npchar)+" csak egy szerény bankár vagyok ebben a csodálatos városban.","Az ön döntése, kapitány! Szeretne kölcsönkérni tôlem egy kis érmét, vagy kölcsönadni pénzt kamatra?","Kapitány úr! Nagyon örülök, hogy ellátogatott szerény irodámba!"));
				link.l1 = RandPhraseSimple(LinkRandPhrase("Örömmel! Éppen a városban sétálgattam, és úgy döntöttem, hogy meglátogatom Önt.","Örvendek, a nevem "+GetFullName(pchar)+", örülök, hogy megismerhetem.",""+GetFullName(pchar)+" , a "+pchar.ship.name+" nevû hajó kapitánya, örülök, hogy megismerhetem. Ez egy bank, igaz?"), RandPhraseSimple("Örülök, hogy megismerhetem. A nevem "+GetFullName(pchar)+". A "+pchar.ship.name+"nevû hajó kapitánya. Csak szerettem volna megismerni magát.","Aha, tehát van itt egy bankja, ugye? Örülök, hogy megismerhetem, én vagyok "+GetFullName(pchar)+", a saját hajóm kapitánya."));
				link.l1.go = "next";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_bank")
				{
					dialog.text = "Lady MacArthur, üdvözlöm, jöjjön be.";
					link.l1 = "És önnek is, "+npchar.lastname;
					link.l1.go = "Helen_next";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Te vagy az! Mit akarsz, "+GetAddress_Form(NPChar)+"?","Mit keresel itt, kapitány? Sajnálom, de a hírneve nem teszi magát túl kívánatos ügyféllé.","Aha, egy újabb ügyfél! Elôször azt hittem, hogy maga egy rabló... ha-ha csak vicceltem."),LinkRandPhrase("Ó! Mit akarsz? Ez egy bank, nem egy kocsma.","Jó napot, kapitány. Tájékoztatnom kell, hogy eléggé megválogatom az ügyfeleimet.","Mit akar, "+GetFullName(pchar)+"? Remélem, nem felejted el, hogy a hírneved nem engedi, hogy nagy összegû kölcsönt vegyél fel?"),LinkRandPhrase("Remélem, hogy pénzt akar befektetni, "+GetAddress_Form(NPChar)+"? Nem lesz könnyû hitelt felvenni neked.","Kapitány "+GetFullName(pchar)+" mit akarsz a szerény bankártól? Sajnálom, de nem fogok tudni hitelt szerezni önnek. Nekem csak kamatra adhat kölcsön pénzt.","Jöjjön be, "+GetAddress_Form(NPChar)+". Sajnálattal közlöm, hogy nem ön a legkedvesebb ügyfél, de általában nem szoktam azonnal elutasítani az embereket.")),LinkRandPhrase(LinkRandPhrase("Jó napot, uram "+GetFullName(pchar)+"! Mindig készen állok arra, hogy segítsek Önnek az üzleti problémákban.","Hello, uram "+GetAddress_Form(NPChar)+". Mindig kész vagyok kölcsönt felvenni vagy bármilyen befektetést elfogadni.","Kedves "+GetFullName(pchar)+"! Örülök, hogy látom! Mit kíván?"),LinkRandPhrase("Kapitány "+GetFullName(pchar)+"! Mindig a szolgálatára állok. Szeretne kölcsönt felvenni vagy pénzt befektetni kamatra?","Üdvözlöm kapitány úr! Ön mindig egy kívánatos ügyfél itt. Kiváló üzleti hírneve van!","Jó napot, "+GetFullName(pchar)+". Örülök, hogy ismét meglátogatott. Remélem, hogy egy jövedelmezô üzleti megállapodásra jött?"),LinkRandPhrase("Jó napot kívánok, kapitány úr! Mit szeretne? Kölcsönt szeretne felvenni vagy befektetni?","kapitány "+GetFullName(pchar)+"! Szeretne kölcsönadni pénzt nyereséges feltételekkel? Mindig örülök, ha ilyen tiszteletreméltó ügyfelet látok.","Örülök, hogy újra látom, kapitány úr! Mindig kész vagyok segíteni Önnek, akár hitelfelvételrôl, akár befektetésrôl van szó.")));
				link.l1 = pcharrepphrase(RandPhraseSimple(LinkRandPhrase("Ne viccelj, bankár, nekem itt üzletem van.","Túl sokat beszélsz, haver. Térjünk rögtön az üzletre.","Hallottad, hogy a pénznek nincs szaga? Szóval csukd be az orrod, és térjünk rá az üzletre."), LinkRandPhrase("És így találkozol az ügyfeleiddel? Még szerencse, hogy ma jó kedvem van.","Ha! Nem örülsz, hogy látsz engem, mi? És nem vagyok én egy aranydublon, hogy pozitív benyomást tegyek rád. Mindenesetre, üzleteljünk, uzsorás.","Eh, szeretnék némi tiszteletet tanítani neked, de erre nincs idôm. Beszéljünk inkább a pénzrôl.")),
				RandPhraseSimple(LinkRandPhrase("Örülök, hogy látom régi barátom!","Mindig öröm idejönni, haver. Térjünk rögtön az üzletre.","Én is nagyon örülök. Beszéljünk az üzletrôl, barátom."),LinkRandPhrase("Nagyon örülök, hogy találkoztunk. Mi újság a pénzügyi tengereken?","Örülök, hogy még emlékszik rám. Sietek, úgyhogy térjünk rögtön az üzletre.","Helló, régi barátom! Örülök, hogy újra látlak!")));
				link.l1.go = "next";
			}
			break;
			
			case "next":
			dialog.text = NPCStringReactionRepeat("Miben segíthetek?", 
				"Ezúttal mit szeretne?", 
				"Hm... mi a gondja?",
                "Eh, " + GetAddress_Form(npchar) + ", el sem tudja képzelni, milyen idegesítôek tudnak lenni az ügyfelek..." , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nem, köszönöm, csak sétálgatok és beszélgetek.", 
				"Én megint. Csak beszélgetni akartam veled.",
                "Igen, megint én vagyok. Semmi komoly, csak beszélgetni akartam veled.", 
				"Igen, bankárnak lenni néha nem is olyan könnyû. Csak beszélgetni akartam...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Meg akarom beszélni a pénzügyi ügyeinket.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Érdekelnek az ékszerek és a szokatlan bálványok vagy drágakövek.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Szükségem van néhány információra. Nos, szeretnék kérdezni valamit.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Az üzleti papírokat a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"hoztam el neked.";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Egy ember parancsára vagyok itt. Ô egy kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " küldött ide. Meg kell szereznem valamit tôled.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Jó napot, a fia hívott meg."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Szeretném tudni, hogy ki a dokumentum tulajdonosa.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Az ügyfele adósságáról szeretnék beszélni. A neve "+pchar.GenQuest.Noblelombard.Name+". Elzálogosította a családi ereklyéjét. Én képviselem itt az érdekeit, és jogom van megbeszélni önnel a visszaszolgáltatását.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Három hónappal ezelôtt volt egy találkozónk, és egy ember ereklyéjérôl beszéltünk. A neve "+pchar.GenQuest.Noblelombard.Name+"volt. Emlékszik rá? Meg kellett nyitnia egy letétet a nevemre. Az összeg  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "A te rabszolga megbízásodról van szó.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + NPChar.name + ", beszéljünk a feladatáról.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + NPChar.name + ", beszéljünk a feladatáról.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + NPChar.name + ", beszéljünk a feladatáról.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Eljöttem, ahogy megbeszéltük. Van egy munkád számomra?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Eljöttem, ahogy ígértem. Mit szólnál egy munkához?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + npchar.name + ". Hogy van? Van egy új megbízásod számomra?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "A küldetésednek vége. Sikerült megtalálnom azokat a szökevényeket. Bár nem volt olyan könnyû.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + npchar.name + ". Egy új jövedelmezô megbízás miatt jöttem.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Rossz hírek," + npchar.name + ". Nem sikerült megszereznem a brigantit.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Nézd,  " + npchar.name + ". A brigantit levadásztam, de nem találtam papírokat. Biztos vagy benne, hogy ott voltak?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó hír," + npchar.name + ". Sikerült levadásznom azt a brigantint, és megtaláltam a papírokat. Itt vannak.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + npchar.name + ". Készítettél nekem egy új feladatot?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", sikerült elkapnom azt az úgynevezett 'galleont.'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", Sajnálom, de nem tudtam felszállni a gályára.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + npchar.name + ". A pénzemért jöttem.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", A küldetésed teljesítve. Az a rohadék Gontier halott, és a legénysége is.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", Sajnálom, de nem sikerült elkapnom Francois Gontier-t, pedig követtem ôt Tortugára. Sikerült elmenekülnie a korvettájával elôlem.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot," + npchar.name + ". Mesélj nekem arról az új küldetésrôl, amit nekem készítettél.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;
		
		case "Helen_next":
			dialog.text = NPCStringReactionRepeat("Nem mondanám, hogy pénzre van szüksége, vagy hogy a vagyonát szeretné gyarapítani. Mi szél hozta az irodámba?", 
				"Ezúttal mit akar?", 
				"Hm... mi a gondja?",
                "Eh, " + GetAddress_Form(npchar) + ", el sem tudja képzelni, milyen idegesítôek tudnak lenni az ügyfelek..." , "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nem, köszönöm, csak sétálgatok és beszélgetek.", 
				"Én megint. Csak beszélgetni akartam veled.",
                "Igen, megint én vagyok. Semmi komoly, csak beszélgetni akartam veled.", 
				"Igen, bankárnak lenni néha nem is olyan könnyû. Csak beszélgetni akartam...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = "Meg akarom beszélni a pénzügyi ügyeinket.";
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = "Érdekelnek az ékszerek és a szokatlan bálványok vagy drágakövek.";
			if (!isMultiObjectKnown("gold_dublon"))
			{
				link.l3.go = "items_0";
			}
			else
			{
				link.l3.go = "items_1";
			}	
			link.l4 = "Szükségem van néhány információra. Nos, szeretnék kérdezni valamit.";
			link.l4.go = "quests";//(перессылка в файл города)
//Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Az üzleti papírokat a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"hoztam el neked.";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//квесты мэра, проникновение во враждебный город
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Egy ember parancsára vagyok itt. Ô egy kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " küldött ide. Meg kell szereznem valamit tôled.");
				link.l7.go = "IntelligenceForAll";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l9 = "Jó napot, a fia hívott meg."; 
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}	
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l10 = "Szeretném tudni, hogy ki a dokumentum tulajdonosa.";
				link.l10.go = "ShipLetters_Usurer1";			
			}
			
			//--> семейная реликвия // лесник переписал с нпчара на чара 
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "quest.noblelombard"))// вот тут 
			{
				link.l11 = "Az ügyfele adósságáról szeretnék beszélni. A neve "+pchar.GenQuest.Noblelombard.Name+". Elzálogosította a családi ereklyéjét. Én képviselem itt az érdekeit, és jogom van megbeszélni önnel a visszaszolgáltatását.";
				link.l11.go = "Noblelombard";			
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l11 = "Három hónappal ezelôtt volt egy találkozónk, és egy ember ereklyéjérôl beszéltünk. A neve "+pchar.GenQuest.Noblelombard.Name+"volt. Emlékszik rá? Meg kellett nyitnia egy letétet a nevemre. Az összeg  "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Regard))+"...";
				link.l11.go = "Noblelombard_5";			
			}
			//<-- семейная реликвия
			
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id) 
			{
				link.l8 = "A te rabszolga megbízásodról van szó.";
				link.l8.go = "Checkslaves";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + NPChar.name + ", beszéljünk a feladatáról.";
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + NPChar.name + ", beszéljünk a feladatáról.";
				link.l8.go = "Pinas_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + NPChar.name + ", beszéljünk a feladatáról.";
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Eljöttem, ahogy megbeszéltük. Van egy munkád számomra?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Eljöttem, ahogy ígértem. Mit szólnál egy munkához?";
				link.l8.go = "Takeslaves_3";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + npchar.name + ". Hogy van? Van egy új megbízásod számomra?";
				link.l8.go = "EscapeSlave";
				break;
			}
			if(pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "A küldetésednek vége. Sikerült megtalálnom azokat a szökevényeket. Bár nem volt olyan könnyû.";
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + npchar.name + ". Egy új jövedelmezô megbízás miatt jöttem.";
				link.l8.go = "Slaveshore";
				break;
			}			
			
			if(pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Rossz hírek," + npchar.name + ". Nem sikerült megszereznem a brigantit.";
				link.l8.go = "Brig_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Nézd,  " + npchar.name + ". A brigantit levadásztam, de nem találtam papírokat. Biztos vagy benne, hogy ott voltak?";
				link.l8.go = "Letter_lose";
				break;
			}
			if(pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó hír," + npchar.name + ". Sikerült levadásznom azt a brigantint, és megtaláltam a papírokat. Itt vannak.";
				link.l8.go = "Brig_win";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + npchar.name + ". Készítettél nekem egy új feladatot?";
				link.l8.go = "SlaveGalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", sikerült elkapnom azt az úgynevezett 'galleont.'.";
				link.l8.go = "Wingalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", Sajnálom, de nem tudtam felszállni a gályára.";
				link.l8.go = "Lostgalleon";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot, " + npchar.name + ". A pénzemért jöttem.";
				link.l8.go = "FindRat";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", A küldetésed teljesítve. Az a rohadék Gontier halott, és a legénysége is.";
				link.l8.go = "Wincorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "" + npchar.name + ", Sajnálom, de nem sikerült elkapnom Francois Gontier-t, pedig követtem ôt Tortugára. Sikerült elmenekülnie a korvettájával elôlem.";
				link.l8.go = "lostcorvette";
				break;
			}
			if(pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = "Jó napot," + npchar.name + ". Mesélj nekem arról az új küldetésrôl, amit nekem készítettél.";
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			NextDiag.TempNode = "First time";
		break;

		case "items_0":
			dialog.text = "Akarsz venni nekik néhány aranydublont vagy ládát? Hidd el, ez egy nagyon értékes befektetés.";
			link.l1 = "Igen, ez nagyon érdekes.";
			link.l1.go = "items";
			AddQuestRecordInfo("Recipe", "Gold_dublon");
			SetAlchemyRecipeKnown("gold_dublon");
			SetAlchemyRecipeKnown("Chest");
			npchar.quest.meeting = "1"; 			
		break;
		
		case "items_1":
			dialog.text = "Pesóra vagy dubloonra akarsz cserélni?";
			link.l1 = "Pezókért.";
			link.l1.go = "items";
			link.l2 = "Dubloonokért.";
			link.l2.go = "items_dub";
		break;
		
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "items_dub":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}
			if(CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu")) AddItems(npchar, "gold_dublon", 100);
			if(CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat")) AddItems(npchar, "gold_dublon", 100);
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		//<<<<----------генератор -"Shipping documents". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = "Sok idômbe telik elolvasni ezeket a papírokat, és az idôm sokba kerül.";
			link.l1 = "Talán a " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " pezó kárpótolja az idejét?";
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = "Ahogy óhajtja. Viszontlátásra!";
			link.l2.go = "exit";
		break;
		
		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Hadd nézzem meg! Nem, még sosem láttam ezt a nevet. Mutasd meg a kikötômesterünknek.";
				link.l1 = "Sajnálom, de megegyeztünk! Megígérte, hogy mesél nekem errôl a kapitányról!";
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = "Hát... Ismerem ennek a hajónak a tulajdonosát. Nem túl gazdag ember, de van némi vagyona.";
				dialog.text = s1 + " Azt mondják, hogy sikeres csempész. Ezt akartad hallani?";
				link.l1 = "Úgy tûnik...";
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = "Hát... Nem vagyok biztos benne, hogy gratulálhatok a megtalálásához.";
				dialog.text = s1 + "Ezt a dokumentumot a gyarmati járôrhajónknak írták alá, és a kapitánya ismert a határozott elveirôl.";
				link.l1 = "Egy járôrhajó? A parancsnok parancsnoksága alatt?";
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;
		
		case "ShipLetters_Usurer2_1":
			dialog.text = "Megígértem, hogy megnézem azokat a papírokat, de semmi többet. Elmehet.";
			link.l1 = "Köszönöm... Azt hiszem.";
			link.l1.go = "exit";
		break;
		
		case "ShipLetters_Usurer2_2":
			dialog.text = "A te döntésed. A parancsnokunk már régóta eléggé 'érdeklôdést' ezért az egy személyért. Van már valami ötlete? És itt vannak a rakománylevelek, amiken nincsenek jelek...";
			link.l1 = "Értem, értem. Hálámat fejezem ki!";
			link.l1.go = "exit";		
		break;
		
		case "ShipLetters_Usurer2_3":
			s1 = "Pontosan. A csempészeink egyébként haragszanak erre a kapitányra.";
			dialog.text = s1 + "És mint már említettem, a papír tulajdonosa az elvek embere, és nem igazán szereti a helyi bûnöket.";
			link.l1 = "Értem, értem. Hálámat fejezem ki!";
			link.l1.go = "exit";		
		break;

		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ah, úgy veszem, hogy maga egy kapitány, aki elhozta a tékozló fiamat a fiatal menyasszonyával?";
				link.l1 = "Igen, én voltam az, aki segített nekik megszökni.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Á, hát itt vagy, jótevôm. Gondolom, a jutalomra vár?";
				link.l1 = "Legalább a köszönet jól esne...";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Igazán hálás vagyok, hogy segítettél a fiamnak, és nem hagytad ôt abban a bajos helyzetben. Kérem, engedje meg, hogy megköszönjem, amennyire csak tudom. Fogadja el ezt a szerény összeget és egy kis ajándékot tôlem.";
			link.l1 = "Köszönöm. Örömömre szolgált, hogy segíthettem ennek a fiatal párnak.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Köszönöm. Miért? Ez a tökfej fél évig munkanélküli volt, és máris talált idôt arra, hogy szerezzen magának egy lányt! Az ô korában én is a saját üzletemet vezettem. Van egy házasulandó kormányzó lánya, és ô hozta ide ezt a szajhát, Uram, bocsáss meg, hogy ezt mondom! És most az áldásomat kéri!";
			link.l1 = "Gondolom, nem hiszel az érzelmekben?";
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
			dialog.text = "Az érzésekben? Miféle érzésekben? Te egy felnôtt férfi vagy, és te is ilyen érzésekrôl beszélsz? Micsoda szégyen, hogy a fiatalságot pocskondiázod. Elvette a lányt a szüleitôl, és tönkretette a fiam életét. Nem kapsz tôlem köszönetet. Viszontlátásra.";
			link.l1 = "Akkor viszlát...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("saw","saw"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Кредитный генератор Loan
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			if (npchar.id == "Panama_Usurer")
			{
				if (sti(pchar.reputation.nobility) > 70 && ChangeCharacterNationReputation(pchar, SPAIN, 0) >= 80 && !CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
				{
					dialog.text = "Beszéljük meg. Hallgatlak.";
				}
				else
				{
					dialog.text = "Uh, uh. Attól tartok, vissza kell utasítanom, "+GetAddress_Form(NPChar)+". Sajnálom, de a bankom nem nyújt szolgáltatásokat Spanyolország ellenségeinek.";
					link.l1 = "A pénznek nincs nemzetisége, senor bankár.";
					if (CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
					{
						if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
						{
							dialog.text = "Mm-hmm, "+GetAddress_Form(NPChar)+". Tájékoztatnom kell, hogy a letét már nem érvényes.";
							Link.l1 = "Milyen alapon?!";
							Link.l1.go = "Panama_Deposit_SgorelVklad";
							DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
							break;						
						}
						else
						{
							link.l1.go = "Panama_Deposit_Cartahena";
							break;
						}
					}
					if (sti(pchar.reputation.nobility) < 71 || ChangeCharacterNationReputation(pchar, SPAIN, 0) < 80)
					{
						link.l1.go = "Panama_Deposit_NoReputation";
						break;
					}
				}
			}
			dialog.text = "Beszéljük meg. Hallgatlak.";
			//кредиты
            if(CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);// boal 23.01.2004
				if(makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = "Tartozom neked "+ FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + LinkRandPhrase(", kész vagyok visszaadni a pénzed", ". Vissza akarom fizetni az adósságot.", ".  Végre itt az ideje, hogy visszafizessem.");
					Link.l5.go = "loan_return";	
					sTemp = "kredit";
				}					
			}
			else
			{
				Link.l6 = LinkRandPhrase("Szeretnék kölcsönkérni néhány érmét.", "Tényleg szükségem van néhány pesóra.", "Mit szólnál egy kis kölcsönhöz?");
				Link.l6.go = "loan";					
				if(makeint(Pchar.money) >= 100)
				{
					Link.l7 = LinkRandPhrase("Szeretném a pénzemet kamatra befizetni.","Elfogadná, hogy néhány zsák ezüstömet megtartsa?", "Hagyhatok neked egy kis ezüstöt egy szerencsétlen napra?"); // patch
					Link.l7.go = "deposit";				
				}			
				if(CheckUseDublons(NPChar))
				{
					Link.l8 = "Szeretnék letétbe helyezni néhány dublont kamatra.";
					Link.l8.go = "deposit_dub";				
				}
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)) && makeint(Pchar.Quest.Deposits.(sDepositType1)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType1).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType1).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType1).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType1).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType1).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType1).Result = makeint(Pchar.Quest.Deposits.(sDepositType1).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)/100)*makefloat(Pchar.Quest.Deposits.(sDepositType1).Interest))*iPastMonths;
				}
				Link.l9 = LinkRandPhrase("Azért jöttem, hogy visszakapjam a befektetésemet, pezóban.", "Itt az ideje, hogy visszakapjam az ezüstöm, amivel tartozik nekem.", "Vissza akarom kapni a befektetésemet pesóban, a kamatokkal együtt.");
				Link.l9.go = "Deposit_return";									
			}
			
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)) && makeint(Pchar.Quest.Deposits.(sDepositType2)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(sDepositType2).StartYear),makeint(Pchar.Quest.Deposits.(sDepositType2).StartMonth),makeint(Pchar.Quest.Deposits.(sDepositType2).StartDay), makefloat(Pchar.Quest.Deposits.(sDepositType2).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
				if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths+sti(Pchar.Quest.Deposits.(sDepositType2).Rem);
				}
				else
				{
					Pchar.Quest.Deposits.(sDepositType2).Result = makeint(Pchar.Quest.Deposits.(sDepositType2).Sum) + ((makeint(Pchar.Quest.Deposits.(sDepositType2).Sum)/100)*makeint(Pchar.Quest.Deposits.(sDepositType2).Interest))*iPastMonths;
				}
				Link.l10 = LinkRandPhrase("Vissza akarom szerezni a dubloonokba fektetett pénzemet.", "Itt az ideje, hogy visszakapjam az aranyamat, amivel tartozol nekem.", "Vissza akarom kapni a dubloonokban lévô befektetésemet minden kamatával együtt.");
				Link.l10.go = "Deposit_return_dub";									
			}
/*			
			
*/			
			//выход
			if (sTemp == "credit")
			{
				link.l11 = "Emlékszem az adósságomra, mégsem vagyok hajlandó kifizetni...";
				link.l11.go = "Loan_Remind";
			}
			else
			{
				link.l11 = "Az én hibám, nincs semmilyen pénzügyi ügyem veled. Viszlát.";
				link.l11.go = "exit";
			}
		break;
		
		//============== кредиты ===============
		case "loan":
            if (sti(NPChar.nation) == PIRATE)
            {
                dialog.text = "Nem, nem tudok segíteni. Csak befektetéseket tudok elfogadni ezen a problémás helyen. Befektethet ezüst pezót vagy arany dublont.";				
                if(makeint(Pchar.money) >= 100)
				{
	                Link.l1 = "Én pesót szeretnék befektetni, és beszéljünk az összegrôl.";
	                Link.l1.go = "deposit";
				}				
				if(CheckUseDublons(NPChar))
				{
					Link.l2 = "Én dublont akarok befektetni. Tisztázzuk az összeget.";
					Link.l2.go = "deposit_dub";
				}
                Link.l3 = "Nem érdekel.";
				link.l3.go = "exit";
                break;
            }
			// проверка на проф пригодность -->
            if (isBadReputation(pchar, 42))
            {
                dialog.text = RandSwear() + "A neved " + GetFullName(pchar)+ ", igaz? Önnek " +
                              RandPhraseSimple("rossz híre ","rossz híre ") + " van, és nem akarok magával üzletet kötni.";
				link.l1 = RandPhraseSimple("Az ember nem hibázhat?", RandSwear() + "Mindegy!");
				link.l1.go = "exit";
                break;
            }
            // проверка на проф пригодность <--
			Dialog.snd = "voice\USDI\USDI016";
			dialog.text = "Ó, mindig szívesen látunk. Milyen összegre van szüksége?";
			Link.l1 = "Egy kis összegre.";
			Link.l1.go = "Small";
			Link.l2 = "Mérsékelt.";
			Link.l2.go = "Medium";
			Link.l3 = "Amennyire csak lehet.";
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500*makeint(Pchar.rank)+125*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI017";
			dialog.text = "Kiváló! Mindig sokkal könnyebb kis összegekkel üzletelni - kisebb a kockázat mindkét fél számára. Tudok ajánlani Önnek " + FindRussianMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)) + "...";
			Link.l1 = "Megegyeztünk. Mi a helyzet a kamatokkal?";
			Link.l1.go = "Interest";
			Link.l2 = "Nekem nem fog mûködni. Változtassunk rajta.";
			Link.l2.go = "Loan";
			Link.l3 = "Azt hiszem, jobb, ha nem adósodom el. Viszontlátásra.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500*makeint(Pchar.rank)+325*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI018";
			dialog.text = "Nem probléma. Remélem, hogy a " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + " segít megoldani a problémáit. Ez elég jelentôs összeg.";
			Link.l1 = "Megegyeztünk. Mi a helyzet a kamatokkal?";
			Link.l1.go = "Interest";
			Link.l2 = "Nekem nem fog mûködni. Változtassunk rajta.";
			Link.l2.go = "Loan";
			Link.l3 = "Azt hiszem, jobb, ha nem adósodom el. Viszontlátásra.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000*makeint(Pchar.rank)+600*GetSummonSkillFromName(pchar,SKILL_COMMERCE);
			Dialog.snd = "voice\USDI\USDI019";
			dialog.text = "Nos... ez kockázatos. Rendben, kész vagyok hitelt felvenni neked a " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)) + ". Remélem, megérti, kapitány, ez egy igazán jelentôs összeg. Arra kérem, hogy vegye komolyan.";
			Link.l1 = "Megegyeztünk. Mi a helyzet a kamatokkal?";
			Link.l1.go = "Interest";
			Link.l2 = "Nekem nem fog mûködni. Változtassunk rajta.";
			Link.l2.go = "Loan";
			Link.l3 = "Azt hiszem, jobb, ha nem adósodom el. Viszontlátásra.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Interest":
			Pchar.Quest.Loans.(NPC_Area).Interest = 4.0 + (makeint((((6.0 - 4.0) * (GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 200) ) / 0.5 + 0.5)) * 0.5;
			//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			// Rebbebion, добавил фикс отображения знака процента
			Dialog.snd = "voice\USDI\USDI020";
			dialog.text = fts(stf(Pchar.Quest.Loans.(NPC_Area).Interest), 1) + "%% havonta. Ennél jobb feltételeket nem tudok ajánlani az alapján, amit rólad tudok."; 
			Link.l1 = "Nekem megfelel. Beszéljünk az idôrôl.";
			Link.l1.go = "Period";
			Link.l3 = "Azt hiszem, jobb, ha nem adósodom el. Viszontlátásra.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation.nobility)/20) + 1;			
			Dialog.snd = "voice\USDI\USDI021";
			dialog.text =  "Figyelembe véve a rólad szóló információimat, " + Pchar.name + ", várom a kölcsön visszafizetését a " + FindRussianMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)) + ". Ezt követôen megteszek bizonyos intézkedéseket. Remélem, hogy ezt megérti."; 
			Link.l1 = "Örömmel elfogadom a feltételeit... és az érméit.";
			Link.l1.go = "LoanGranted";
			Link.l3 = "Elnézést, de ez nekem nem fog menni. Viszontlátásra.";
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			Dialog.snd = "voice\USDI\USDI022";
			dialog.text = "Ôszintén örülök. De hadd figyelmeztesselek. Hosszú ideje csinálom ezt, és tudom, hogyan kell megtéríteni a befektetéseimet. Szóval ha valaha is ostoba ötleteid támadtak, javaslom, hogy hagyd el\nNem sértés, csak figyelmeztetés.";
			Link.l1 = "Hm... Nos. Viszlát.";
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			Dialog.snd = "voice\USDI\USDI023";
			dialog.text = "A maga döntése, kapitány. Az én érdeklôdésem egyre nô, és magának nincs annyi ideje.";
			Link.l1 = "Ne aggódjon emiatt. Viszlát.";
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
            if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
            {
    			AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
    			AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			Dialog.snd1 = "voice\USDI\USDI024";
			Dialog.snd2 = "voice\USDI\USDI025";
			Dialog.snd3 = "voice\USDI\USDI026";
			dialog.text = LinkRandPhrase("Csodálatos! Gyere hozzám, ha érmékre van szükséged. Bármikor a rendelkezésedre állok.", "Hálám. Mindig öröm olyan emberrel üzletelni, aki képes idôben visszafizetni a tartozását. A dolgok néha megtörténnek, és ezt meg tudom érteni, tudod... de jobban szeretem, ha a problémákat meg lehet oldani.",  "Ó, jól tettem, hogy bíztam benned, " + GetAddress_Form(NPChar) + "! Remélem, hogy nem utoljára veszed igénybe a szolgáltatásaimat. Talán még jobb üzleteket is köthetünk neked, hiszen most már tudom, hogy becsületes ember vagy.");
			Link.l1 = LinkRandPhrase("Kölcsönt szeretnék kérni.", "Tényleg szükségem van néhány pesóra.", "Mit szólnál egy kis kölcsönhöz?");
			Link.l1.go = "loan";			
			if(makeint(PChar.money) >= 100)
			{
				Link.l2 = LinkRandPhrase("Szeretném befektetni a pénzemet.","Megtartasz egy kis kalózzsákmányt?", "Hagyhatok neked egy kis ezüstöt egy szerencsétlen napra?");
				Link.l2.go = "deposit";				
			}		
			if(CheckUseDublons(NPChar))	
			{
				Link.l3 = "Szeretnék befektetni néhány dublont a kamatokért.";
				Link.l3.go = "deposit_dub";				
			}
			Link.l4 = "Isten veled, " + NPchar.name + ".";
			Link.l4.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = LinkRandPhrase("Egy bölcs embert látok! Milyen összeget szeretne befektetni?", "Rendben. Bízz bennem, ez az összeg itt biztonságban és minden kamatával együtt megvár téged.", "Látom, hogy tudod, mi az igazán fontos ebben az életben. Mennyit szeretnél befektetni?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result";
		break;
		
		case "result":
			Pchar.QuestTemp.Deposits.(sDepositType1).Interest = GetDepositRate();
			Pchar.QuestTemp.Deposits.(sDepositType1).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Viccelsz, mi?";
				link.l1 = "Az én hibám.";
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = "Hm, sajnos nincs ennyi pénze. Legyünk komolyak...";
				link.l1 = "Rendben.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Jól van, rendben. Felajánlhatok neked... mondjuk..." + fts(stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest), 1) + " %. Havonta, természetesen.";
			Link.l1 = "Nekem megfelel.";
			Link.l1.go = "Deposit_placed";
			Link.l2 = "Jobb, ha megváltoztatom az összeget.";
			Link.l2.go = "Deposit";
			Link.l3 = "Úgy tûnik, ez egy rossz ötlet volt... Viszlát.";
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType1).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum)) > sti(NPChar.UsurerDeposit)*1000)
			{
			    dialog.text = "Elnézést, kapitány, de ez az összeg túl nagy az én gyarmati bankomnak. Nem fogom tudni kifizetni a kamatokat. És a megbízható ôrség hiánya... Remélem, megérti. Mindenesetre a maximális összeg, amit el tudok fogadni öntôl, " +
						FindRussianMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*1000, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "Kár, akkor keresnem kell egy másik bankárt.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Most már biztos lehetsz benne, hogy még a legerôsebb vihar sem hagyna érme nélkül.";
				Link.l1 = "Rendben. Viszlát.";
				Link.l1.go = "Deposit_Exit";
			}
		break;
		
		case "Deposit_return":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Tekintettel az ígért kamatra és az eltelt idôre, tartozom neked " + FindRussianMoneyString(sti(Pchar.Quest.Deposits.(sDepositType1).Result)) + "... Biztos, hogy el akarod venni a pénzt?";
			Link.l1 = "Teljesen. Add ide.";			
			Link.l1.go = "Deposit_return_1";		
			Link.l2 = "El akarom venni a pénzem egy részét.";			
			Link.l2.go = "Deposit_return_part";
			Link.l3 = "Igazad van. Hagyom, hogy egy ideig nálad maradjon. Szép napot.";			
			Link.l3.go = "Exit";		
		break;		
		
		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType1)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType1)+ ".Rem");
			}
			Pchar.Quest.Deposits.(sDepositType1).Interest = stf(Pchar.QuestTemp.Deposits.(sDepositType1).Interest);
			Pchar.Quest.Deposits.(sDepositType1).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1).city 	  = NPC_Area;	

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(sDepositType1).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(sDepositType1).Sum = sti(Pchar.Quest.Deposits.(sDepositType1).Result) + sti(Pchar.Quest.Deposits.(sDepositType1).Sum);
			Pchar.Quest.Deposits.(sDepositType1) = true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
			DialogExit();
		break;
		
		//--> Jason забор денег по частям
		case "Deposit_return_part":
			dialog.text = "És mennyit?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_part";
		break;

		case "result_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Ez egy hülye vicc volt, uram!";			
				link.l1 = "A francba! Nagyon sajnálom... Változtassuk meg az összeget.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Nincs ennyi pénz a számláján.";			
				link.l1 = "A francba! Az én hibám. Változtassuk meg az összeget.";	
				Link.l1.go = "Deposit_return_part";
				break;
			}
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType1).Result))
			{
				dialog.text = "Az egészet? Rendben, ahogy mondod. Itt a pénzed.";			
				link.l1 = "Köszönetnyilvánítás!";	
				Link.l1.go = "Deposit_return_all";
				break;
			}
			dialog.text = "Rendben. Vegye el. Itt a pénzed.";			
			link.l1 = "Köszönjük!";	
			Link.l1.go = "result_part_1";
		break;
		
		case "result_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType1).Result)-iTemp; //остаток на счете
			fPer = stf(Pchar.Quest.Deposits.(sDepositType1).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType1).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType1).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType1).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
				Pchar.Quest.Deposits.(sDepositType1).Interest = fPer;
				Pchar.Quest.Deposits.(sDepositType1).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType1).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType1).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType1) 			= true;
			Pchar.Quest.Deposits.(sDepositType1).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType1).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType1).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType1).StartTime 	= getTime();
		break;
		
		case "Deposit_return_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			addMoneyToCharacter(Pchar, iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_1":
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(sDepositType1).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Ó... Olyan nehéz elveszíteni. Tényleg hozzászoktam ehhez a pénzhez. Azért gyere újra.";			
			Link.l1 = "Majd ha kell. Viszontlátásra.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType1));
		break;
		
		//  ugeen -> вклады в дублонах	
		case "deposit_dub":
			dialog.text = LinkRandPhrase("Egy bölcs embert látok! Milyen összeget szeretne befektetni?", "Rendben. Bízz bennem, ez az összeg itt biztonságban és minden kamatával együtt megvár téged.", "Látom, hogy tudod, mi az igazán fontos ebben az életben. Mennyit szeretnél befektetni?");
			link.l1.edit = 3;
			link.l1 = "";	
			Link.l1.go = "result_dub";
		break;
		
		case "result_dub":		
			iTotalDublonQty = GetCharacterItem(pchar,"gold_dublon") + CheckItemMyCabin("gold_dublon");		
			Pchar.QuestTemp.Deposits.(sDepositType2).Interest = 1;
			Pchar.QuestTemp.Deposits.(sDepositType2).Sum = dialogEditStrings[3];
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp <= 0)
			{
				dialog.text = "Viccelsz, mi?";
				link.l1 = "Hm, az én hibám...";
				link.l1.go = "exit";
				break;
			}						
			if (iTemp > iTotalDublonQty)
			{
				dialog.text = "Hm, sajnos nincs ennyi pénze. Legyünk komolyak...";
				link.l1 = "Hm... jó.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Jól van, rendben. Felajánlhatok neked... mondjuk..." + Pchar.QuestTemp.Deposits.(sDepositType2).Interest + " %. Havonta, természetesen.";
			Link.l1 = "Nekem bevált.";
			Link.l1.go = "Deposit_placed_dub";
			Link.l2 = "Jobb, ha megváltoztatom az összeget.";
			Link.l2.go = "Deposit_dub";
			Link.l3 = "Azt hiszem, jobb, ha megtartom az aranyamat. Viszontlátásra.";
			Link.l3.go = "Exit";
		break;
		
		case "Deposit_placed_dub":
			Dialog.snd = "voice\USDI\USDI033";
			if ( !CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+".Result"))
			{
			    Pchar.Quest.Deposits.(sDepositType2).Result = 0;//fix
			}
			// boal limit
			if ( (sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum)) > sti(NPChar.UsurerDeposit)*10)
			{
			    dialog.text = "Elnézést, kapitány, de ez az összeg túl nagy az én gyarmati bankomnak. Nem fogom tudni kifizetni a kamatokat. És a megbízható ôrség hiánya... Remélem, megérti. Mindenesetre a maximális összeg, amit el tudok fogadni öntôl, " +
						FindRussianDublonString(MakeMoneyShow(sti(NPChar.UsurerDeposit)*10, MONEY_SIGN,MONEY_DELIVER)) + ".";
				Link.l1 = "Kár, akkor keresnem kell egy másik bankárt.";
				Link.l1.go = "Exit";
			}
			else
			{
				dialog.text = "Most már biztos lehetsz benne, hogy még a legerôsebb vihar sem hagyna érme nélkül.";
				Link.l1 = "Szép volt. Viszontlátásra.";
				Link.l1.go = "Deposit_Exit_dub";
			}
		break;
		
		case "Deposit_return_dub":
			Dialog.snd = "voice\USDI\USDI034";
			dialog.text = "Tekintettel az ígért kamatra és az eltelt idôre, tartozom neked " + FindRussianDublonString(sti(Pchar.Quest.Deposits.(sDepositType2).Result)) + "... Biztos, hogy el akarod venni a pénzt?";
			Link.l1 = "Teljesen. Add ide.";			
			Link.l1.go = "Deposit_return_dub_1";		
			Link.l2 = "El akarom venni a pénzem egy részét.";			
			Link.l2.go = "Deposit_return_dub_part";
			Link.l3 = "Igaza van. Hagyom, hogy egy darabig veled maradjon. Szép napot!";			
			Link.l3.go = "Exit";		
		break;	

		case "Deposit_exit_dub":
			NextDiag.CurrentNode = NextDiag.TempNode;		
			if(CheckAttribute(Pchar, "Quest.Deposits." + (sDepositType2)+ ".Rem"))
			{
				DeleteAttribute(Pchar,"Quest.Deposits." + (sDepositType2)+ ".Rem");
			}	
			Pchar.Quest.Deposits.(sDepositType2).Interest = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Interest);
			Pchar.Quest.Deposits.(sDepositType2).Sum      = sti(Pchar.QuestTemp.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2).city 	  = NPC_Area;	
			
			iTemp = GetCharacterItem(pchar,"gold_dublon");
			if(iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Sum))
			{
				TakeNItems(pchar,"gold_dublon", -sti(Pchar.Quest.Deposits.(sDepositType2).Sum));
			}
			else
			{
				TakeNItems(pchar,"gold_dublon", -iTemp));
				iTemp = sti(Pchar.Quest.Deposits.(sDepositType2).Sum) - iTemp;
				GetItemMyCabin("gold_dublon", iTemp);
			}
						
			// общий долг
			Pchar.Quest.Deposits.(sDepositType2).Sum = sti(Pchar.Quest.Deposits.(sDepositType2).Result) + sti(Pchar.Quest.Deposits.(sDepositType2).Sum);
			Pchar.Quest.Deposits.(sDepositType2) = true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
			DialogExit();
		break;	
		
		//-->забор дублонов по частям
		case "Deposit_return_dub_part":
			dialog.text = "És mennyit?";
			link.l1.edit = 4;
			link.l1 = "";	
			Link.l1.go = "result_dub_part";
		break;
		
		case "result_dub_part":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0)
			{
				dialog.text = "Micsoda ostoba vicc, uram!";			
				link.l1 = "A francba! Nagyon sajnálom... Változtassuk meg az összeget...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp > sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Nincs ennyi arany a számláján, uram.";			
				link.l1 = "A francba! Az én hibám. Változtassuk meg az összeget...";	
				Link.l1.go = "Deposit_return_dub_part";
				break;
			}			
			if (iTemp == sti(Pchar.Quest.Deposits.(sDepositType2).Result))
			{
				dialog.text = "Az egészet? Rendben, ahogy mondod. Itt a pénzed.";			
				link.l1 = "Köszönjük!";	
				Link.l1.go = "Deposit_return_dub_all";
				break;
			}
			dialog.text = "Rendben. Vegye el. Itt a pénzed.";			
			link.l1 = "Köszönetnyilvánítás!";	
			Link.l1.go = "result_dub_part_1";
		break;
		
		case "result_dub_part_1":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			iRes = sti(Pchar.Quest.Deposits.(sDepositType2).Result)-iTemp; //остаток на счете
			iPer = sti(Pchar.Quest.Deposits.(sDepositType2).Interest);
			iDep = sti(Pchar.Quest.Deposits.(sDepositType2).Sum); //стартовая сумма
			if (iRes <= sti(Pchar.Quest.Deposits.(sDepositType2).Sum)) // стало меньше начальной суммы
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iRes;
				Pchar.Quest.Deposits.(sDepositType2).Result = 0;
			}
			else // если остаток больше начальной суммы - проценты продолжаем считать с неё, а не с остатка, ибо нефиг, дельту приплюсуем к набежавшим процентам - банкир Jason :) 
			{
				DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
				Pchar.Quest.Deposits.(sDepositType2).Interest = iPer;
				Pchar.Quest.Deposits.(sDepositType2).Sum = iDep;
				Pchar.Quest.Deposits.(sDepositType2).Rem = iRes-iDep;
			}
			Pchar.Quest.Deposits.(sDepositType2).city 	  	= NPC_Area;	
			Pchar.Quest.Deposits.(sDepositType2) 			= true;
			Pchar.Quest.Deposits.(sDepositType2).StartDay 	= getDataDay();
			Pchar.Quest.Deposits.(sDepositType2).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(sDepositType2).StartYear 	= getDataYear();
			Pchar.Quest.Deposits.(sDepositType2).StartTime 	= getTime();
		break;
		
		case "Deposit_return_dub_all":
			DialogExit();
			iTemp = sti(dialogEditStrings[4]);
			TakeNItems(pchar,"gold_dublon", iTemp);
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//<-- забор денег по частям		
		
		case "Deposit_return_dub_1":
			TakeNItems(pchar,"gold_dublon", sti(Pchar.Quest.Deposits.(sDepositType2).Result));
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Ó... Olyan nehéz elveszíteni. Tényleg hozzászoktam ehhez a pénzhez. Azért gyere újra.";			
			Link.l1 = "Megteszem, ha kell. Viszontlátásra.";			
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (sDepositType2));
		break;
		//  ugeen <- вклады в дублонах	
		
		case "DeadMotherfucker":
			Dialog.TempNode = "DeadMotherFucker_1";
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Még mindig élsz? Talán vissza akarod adni a pénzem? Cseszd meg! Annyi pénzt vesztettem, hogy soha nem tudnád visszafizetni! És addig nem nyugszom, amíg nem látom az élettelen tested!";
            Link.l1 = "Csak békésen akarom rendezni a dolgokat.";
			Link.l1.go = "LoanRestore_1";
			Link.l2 = LinkRandPhrase("Rendben, akkor lássuk! Tudd meg, hogy te sem vagy védve a haláltól!", "fenyegetés?! Akkor lássuk, mit fogsz csinálni...", "Nem a pénz a legfontosabb dolog az életünkben. Ne búslakodj túl sokat rajta és ne gyilkolj embereket, gyerünk merem mondani.");
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":			
			Dialog.snd = "voice\USDI\USDI035";
			dialog.text = "Kifelé! Bárcsak soha többé nem látnálak.";			
			Link.l1 = "...";			
			Link.l1.go = "ExitDelLoan2";
            Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
            iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear),makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth),makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(),getDataMonth(),GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum)/100)*makefloat(Pchar.Quest.Loans.(NPC_Area).Interest))*(iPastMonths+1);
			dialog.text = "Tényleg? És mi a gondod?";
			Link.l1 = "A mai napért tartozom neked " + FindRussianMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ". És ezt a pénzt neked ajánlom fel.";
			Link.l1.go = "DeadMotherFucker_1";
            if (sti(Pchar.Money) >= 2*sti(Pchar.Quest.Loans.(NPC_Area).Result))
            {
    			Link.l2 = "Felajánlom adósságomat, hogy helyreállítom a jó kapcsolatokat. Ez " + FindRussianMoneyString(2*sti(Pchar.Quest.Loans.(NPC_Area).Result)) + ".";
    			Link.l2.go = "LoanRestore_2";
			}
		break;
		
		case "LoanRestore_2":
			dialog.text = "Most már beszélgetünk! Mégiscsak tudok veled üzletelni.";
			Link.l1 = "Köszönöm. Többé nem hagylak cserben.";
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";			
			addMoneyToCharacter(Pchar, -2*sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;
		
        case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;			
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";
			
			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
        
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 100;
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;
			dialog.Text = "Ah, ugyan már! Mi komoly emberek vagyunk, te és én, jobbak vagyunk, mint azok az idióták, akik készek meghalni egyetlen dublónért, de soha, de soha nem próbálnak meg két dublónt keresni belôle\nEgy olyan embert keresek, akinek komoly üzletet ajánlhatok. Egy bátor és aktív, becsületes és pontos férfit, akit nem terhel... eh... túl sok lelkiismeretfurdalás az erkölcsi dilemmák tekintetében. És remélem, hogy te vagy az a férfi, akit keresek.";
			Link.l1 = "Ez attól függ, hogy milyen 'alkut' fogsz nekem ajánlani.";
			Link.l1.go = "GiveTaskSlave_1";
		break;
			
		case "GiveTaskSlave_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity(npchar.city);
			dialog.Text = "Rendben, akkor figyelj. A rabszolgatartás a legjövedelmezôbb üzlet a Karib-térségben manapság. Nem vagyok ültetvényes, de vannak megbízható ügyfeleim\nSzóval, a következô mennyiségû rabszolgára van szükségem - " + pchar.questTemp.Slavetrader.iSlaveQuantity + " fejekre. Kész vagyok 250 peso-t fizetni mindegyikért. Higgye el, ez egy jó ár. Összességében keresni fogsz " + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + ".";
			Link.l1 = "Nem, nem vagyok rabszolgakereskedô. Keress magadnak egy másik asszisztenst, aki nem törôdik a lelkiismeretével.";
			Link.l1.go = "exit_slaves";
			Link.l2 = "Csábító ajánlat. Szívesen megtenném. Mikorra lesz szükséged a rabszolgákra?";
			Link.l2.go = "GiveTaskSlave_2";
		break;
			
		case "exit_slaves":
			dialog.Text = "Meh, úgy tûnik, hogy senki sem lelkesedik azért, hogy megmozdítsa a fenekét és elvegye az aranyat a lába alól. Csalódott vagyok, nagyon. Viszlát és eszedbe se jusson pletykákat terjeszteni a beszélgetésünkrôl. Hosszú a karom...";
			Link.l1 = "A kezed piszkos, akárcsak a nyelved. Búcsúzz el.";
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
		break;
			
		case "GiveTaskSlave_2":
			dialog.Text = "Nem fogom korlátozni az idôdet, de igyekezz minél hamarabb teljesíteni a küldetésedet. A 'fekete elefántcsont' iránti kereslet óriási. Ha jól végzed a munkádat, akkor a jövôben is adok neked ilyen jellegû munkákat hébe-hóba.";
			Link.l1 = "Jól hangzik. Nos, várjatok a jó hírekre.";
			Link.l1.go = "exit";						
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", makeint(pchar.questTemp.Slavetrader.iSlaveQuantity));
			AddQuestUserData("Slavetrader", "sSum", makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], true); // блокируем вход офицеров 2015
		break;
			
		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Sikerült megszereznie azt a szállítmányt 'fekete elefántcsontból.'?";
            if (amount < 0)
			{
				Link.l1 = "Még nem. Csak ellenôrzöm, hogy a megállapodásunk még mindig érvényben van-e.";
            	Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = "Én igen. Mind a rakományomban van.";
            	Link.l1.go = "Takeslaves";
			}
		break;
		
		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = "Pompás. Az embereim elviszik ôket... Ne aggódjon a vámosok vagy az erôd parancsnoka miatt. Én egy hatalmas mûveletet vezetek itt, úgyhogy ne számítson semmilyen problémára, és senki sem fogja magát csempészettel vádolni.";
			Link.l1 = "Úgy tûnik, hogy erôs pozícióban van itt... És mi a helyzet a fizetségemmel?";
            Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;
		
		case "Takeslaves_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = "Itt van. Nem beszélek tétlenül. Maradj velem, kapitány, és hamarosan annyi aranyat fogsz birtokolni, hogy egy gályára is szükséged lenne, hogy elszállítsd!";
			Link.l1 = "Az nagyszerû lenne, ha-ha... Mi lesz a következô?";
            Link.l1.go = "Takeslaves_2";
		break;
		
		case "Takeslaves_2":
			dialog.Text = "Mi a következô? Gyere ide három hét múlva. Éppen most készítek elô egy üzletet, és addigra készen kell lennie.";
			Link.l1 = "Rendben, megegyeztünk. Viszlát.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
		break;
		
		case "Takeslaves_3":
			if (4-sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = "Van egy munkám, de a hajód túl gyenge. Nem akarom, hogy megbukj a küldetésen, és azt sem, hogy a saját halálodba küldjelek. Még van idô, úgyhogy szerezz magadnak egy nagyobb hajót, mint például barkentine, brigantine, brigg vagy flotta legalább. Ne vesztegessétek az idôt!";
				Link.l1 = "Értem, majd én elintézem. Viszlát!";
            	Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = "Végre! Már vártam rád. Most pedig térjünk a lényegre. Mint tudja, minden üzletben vannak versenytársak... és nekem is vannak. Ezek a kapzsi és gátlástalan gazemberek mindig el akarnak venni tôlem egy ügyfelet! Valójában, én ki akarom iktatni az egyiket közülük, és közben jó pénzt keresni.";
				Link.l1 = "Csupa fül vagyok.";
            	Link.l1.go = "Takeslaves_4";
			}
		break;
		
		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "A legkiválóbb. Most hallgassátok. Ez a " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + "nevû gazember rabszolgákat hozott Afrikából, és lehorgonyzott " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + ", egy " + XI_ConvertString(pchar.questTemp.Slavetrader.Island) + "nevû szigeten. Ott várja az embercsempészeket. Gályája neve '" + pchar.questTemp.Slavetrader.ShipName + ". Az alkukat mindenáron fel kell bontani!";
			link.l1 = "És mi a helyzet a rabszolgákkal? Nagy kár lenne elsüllyeszteni ôket!";
			link.l1.go = "Takeslaves_5";
		break;
		
		case "Takeslaves_5":
			dialog.Text = "Miért tenné ezt? Erre semmi szükség. " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " rossz híre van, és senki sem fog felháborodni az eltûnésén. Szállj fel a gályájára, öld meg az embert és gondoskodj róla, hogy halott maradjon, hozd el nekem a rakományt és én eladom. Forrásaim szerint kb. másfél ezer rabszolga van.";
			Link.l1 = "Hûha. Ez elég nagy szám. És mi lesz a fizetségemmel?";
            Link.l1.go = "Takeslaves_6";
			Link.l2 = "Nem, uram, ez az intrika nem nekem való. Miért rontanám el a kapcsolatomat a csempészekkel?";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "exit_slaves_1":
			dialog.Text = "Nos... Úgy tûnik, tévedtem veled kapcsolatban... Viszlát és felejtsd el a beszélgetésünket. És ne terjessz pletykákat arról, amit itt hallottál. Ez a város az enyém. És ha azt tervezi, hogy felszáll a '" + pchar.questTemp.Slavetrader.ShipName + " magának... ...gondoskodom róla, hogy a bitófán végezd. Gondoljatok bele.";
			Link.l1 = "Ne aggódj, nem fogom jelenteni a hatóságoknak, és nincs szükségem a gályádra. Viszontlátásra.";
            Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(" agreed"," agreed"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста
		break;
		
		case "Takeslaves_6":
			dialog.Text = "Tekintettel arra, hogy megadtam a rakomány helyét, és nem kell hajózni a keresésben 'a díj' a fizetés egy kicsit alacsonyabb - 200 pezó egy fejért. És még ez is nagy összeg - háromszázezer pezó siker esetén és a hajó.";
			Link.l1 = "Áll az alku. Mennyi idôm van még?";
            Link.l1.go = "Takeslaves_7";
			Link.l2 = "Ho-ho! Ezt úgy mondod, mintha azok a rabszolgák maguktól úsznának a hajómhoz, abban a reményben, hogy minél hamarabb bejuthatnak a rakományomba! Tényleg azt akarod, hogy az embereim kockáztassák a fejüket egy ilyen apró összegért? Növelje a jutalmamat, vagy kiszállok az üzletbôl.";
            Link.l2.go = "exit_slaves_1";
		break;
		
		case "Takeslaves_7":
			dialog.text = "Két hetet kapsz. Ne késsen, különben átadja a rakományát, és vége az egésznek.";
			link.l1 = "Akkor sietnünk kell. Várjatok a jó hírekkel.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Voc")); // belamour gen
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;
            pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это заглушка
		break;
		
		case "Takeslaves_4_lose":
			dialog.text = "Nos, " + GetFullName(pchar) + ", mi a helyzet a küldetésünkkel? A derûtelen arcod azt mondja nekem, hogy elbuktad.";
			link.l1 = "A fenébe, igazad van... Én... nos, tudod... Elkéstem. Úgy tûnt, hogy már elhagyta a helyet, mert senkit sem találtam ott. Egész úton a széllel kellett vitorláznom, a fenébe is... ";
			link.l1.go = "Takeslaves_5_lose";
		break;
		
		case "Takeslaves_4_win":
			dialog.text = "Nos, " + GetFullName(pchar) + ", mi a mai fogásod? Azt mondták, hogy " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " eteti a halakat! Ha-ha-ha-ha!";
			link.l1 = "Igen, épp idôben érkeztem! " + GetName( NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM) + " rabszolgákat szállított a csempészhajóra. Mindkettôjüket fel kellett szállítani, és elküldeni ôket magának Davy Jonesnak, így most kevesebb versenytársad van.";
			link.l1.go = "Takeslaves_5_win";
		break;
		
		case "Takeslaves_5_lose":
			dialog.text = "Igen, azt hiszem, tévedtem veled kapcsolatban. Késtél? Vagy csak túlságosan féltél a harctól? Mindegy. Most már nincs jelentôsége. Tûnj el. Végeztem veled. Felejts el mindent, amit itt láttál vagy hallottál.";
			link.l1 = "Akkor viszlát.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if (amount < 0)
			{
				dialog.text = "Igazam volt veled kapcsolatban - "+ GetSexPhrase(" te vagy a merész gengszter"," te vagy a vad Maiden") +"! Szükségem van az olyan férfiakra, mint te. A küldetésedet a legkiválóbban teljesítetted - több mint másfél ezer rabszolgát hoztál! Sajnos, csak ezerhatszáz rabszolgáért tudok neked fizetni. Nincs elég pénzem, hogy a többit is kifizessem neked, így neked kell eladnod ôket. A jutalmad 320 000 pezó.";
				link.l1 = "Hála. Örülök, hogy üzletet kötöttünk Önnel, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", 1600);
				AddQuestUserData("Slavetrader", "sMoney", 320000);
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				dialog.text = "Igazam volt veled kapcsolatban - "+ GetSexPhrase(" te vagy a merész gengszter"," te vagy a vad Maiden") +"! Szükségem van az olyan férfiakra, mint te. A küldetésedet a legkiválóbb módon teljesítetted - rabszolgákat hoztál nekem "+ sTemp +" . A jutalmad " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Hála. Örülök, hogy üzletet kötöttünk Önnel, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				dialog.text = "Legalább a legnehezebb helyzetet is becsülettel túlélted. Bár a díj kevesebb, mint amire számítottam, mégis elégedett vagyok. Hoztál "+ sTemp +" rabszolgákat. A jutalmad " + FindRussianMoneyString(iSlaveMoney) + "";
				link.l1 = "Hála. Örülök, hogy üzletet kötöttünk Önnel, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Értem... Ezt meg tudom érteni, de én sokkal többet vártam. Csak "+ sTemp +" rabszolgákat hoztál. Legalább elpusztítottad a versenytársaimat, és ez ér valamit. A jutalmad  " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Köszönöm. Nagyra értékelem a megértését, " + npchar.name + "!";
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = "Jól hangzik, de... hmmm. Úgy tûnik, tévedtem veled kapcsolatban. Mit hoztál? "+ sTemp +" rabszolgákat? És mi van a többivel? És ne mondd, hogy elsüllyesztetted ôket. Biztos vagyok benne, hogy eladtad ôket csempészeknek, vagy ami még rosszabb - annak a szemét Lavoisier-nek. Takarodj a picsába, nem akarok veled többé üzletet kötni!";
				link.l1 = "Ahogy óhajtja, viszlát.";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Jól hangzik, de... hol vannak a rabszolgáink? Hol van a rakományunk? És ne mondd, hogy elsüllyesztetted. Biztos eladtad a csempészeknek, vagy ami még rosszabb, annak a szemét Lavoisier-nek. Tûnj el, végeztem veled.";
			link.l1 = "Ahogy óhajtja, viszlát.";
			link.l1.go = "node_hanter_1";
		break;
		
		case "node_hanter_1":
			dialog.text = "Még nincs vége. Engem senki sem mer átverni! És meg fogsz fizetni a próbálkozásodért - gondoskodom róla, hogy gondjaid legyenek. Most pedig tûnj el innen!";
			link.l1 = "Baszd meg a rabszolga-kereskedésedet! Ott kéne megvágjalak, ahol állsz, de én jobb ember vagyok, mint te valaha is leszel.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Takeslaves_6_win":
			dialog.text = "Úgy tûnik, jól megvagyunk együtt, " + pchar.name + ". Nagyon örülök. Találkozzunk egy hónap múlva, és talán találok egy munkát, ami csak neked való. Már van néhány ötletem.";
			link.l1 = "Persze, egy hónap múlva találkozunk. A veled való munkám nagyon jövedelmezô.";
			link.l1.go = "Takeslaves_7_win";
		break;
			
		case "Takeslaves_7_win":
			dialog.text = "Egy vagyont fog keresni... Még egy utolsó kérdés, " + pchar.name + ", találtál valami szokatlant a gálya kabinjában?";
			link.l1 = "Semmi különöset... Lemaradtam valamirôl?";
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "talisman8"))
			{
				link.l2 = "Erre a régi csatra gondolsz, valami 'scoripion' amulettre?";
				link.l2.go = "Yestatue";
			}
		break;
			
		case "Nostatue":
			dialog.text = "Talán igen, talán nem... Most már mindegy. Egy hónap múlva találkozunk. Viszontlátásra!";
			link.l1 = "Viszlát, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Yestatue":
			dialog.text = "Pontosan! Ez egy Medici fibula... hallottál már róluk? Ez azt jelenti, hogy tényleg a fattyú kabinjában volt... Megnézhetem?";
			link.l1 = "Persze, tessék.";
			link.l1.go = "Yestatue_1";
			RemoveItems(PChar, "talisman8", 1);
		break;
			
		case "Yestatue_1":
			Log_Info("Adtál egy talizmánt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nos, nos... Tényleg az. Figyelj, " + pchar.name + ", add el nekem. Kész vagyok százezer pezót fizetni.";
			link.l1 = "Százezer? Hm... egyetértek. Tessék!";
			link.l1.go = "Buystatue";
			link.l2 = "Nem, nem adom el. Ennek a fibulának az igazi árát nem lehet ezüsttel vagy arannyal felbecsülni. Tudom, hogy mûködnek az ilyen dolgok.";
			link.l2.go = "Nobuystatue";
		break;
			
		case "Buystatue":
			dialog.text = "Tökéletes! Örülök, hogy megegyeztünk. Fogd a pénzed. Alig várom, hogy egy hónap múlva találkozzunk.";
			link.l1 = "Isten veled, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue":
			dialog.text = "Látod, nekem nagy szükségem van erre a fibulára! Teljesen egyetértek veled, pénzzel nem lehet értékelni, bármelyik hülye eladó nem fog érte ötezret sem fizetni. De úgy tûnik, hogy te tényleg tudod, mire képes, hiszen nem vagy hajlandó eladni ilyen összegért.\n Hadd ajánljak fel egy cserét, ha nem akarsz pénzt. Van nálam valami, amit érdekesnek találhatsz. Tessék, nézze meg. Egy csodálatos könnyû páncél! Nézd meg magad! Felajánlom neked a fibuláért cserébe\nEz egyébként nem egyedi. Ti matrózok, ti mindig találhattok magatoknak többet, én meg nem. Most már egyetértesz?";
			link.l1 = "Heh... Gondolom. Add ide a páncélt, és vidd ezt a fibulát.";
			link.l1.go = "Nobuystatue_yes";
			link.l2 = "Nem, ennek a fibulának sokkal nagyobb ára van számomra, mint ennek a páncélnak. Megtartom magamnak.";
			link.l2.go = "Nobuystatue_no";
		break;
			
		case "Nobuystatue_yes":
			dialog.text = "Pompás! Örülök, hogy megegyeztünk. Ez most már a te páncélod. Vedd el. Egy hónap múlva találkozunk. Viszlát.";
			link.l1 = "Viszlát, " + npchar.name + ".";
			link.l1.go = "exit";
			TakeNItems(pchar, "cirass7", 1);
			Log_Info("Kaptál egy Brigandine-t");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "Nobuystatue_no":
			dialog.text = "Kár... Nagyon rossz. Nos, vedd el. Nem ítéllek el. Viszlát egy hónap múlva. Viszlát.";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
			TakeNItems(pchar, "talisman8", 1);
			Log_Info("Kaptál egy talizmánt");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
		break;
			
		case "EscapeSlave":
			dialog.text = "Épp idôben jöttél, " + pchar.name + ". Van egy küldetésem a számodra, ha készen állsz arra, hogy elkezdd.";
			link.l1 = "Persze, készen állok.";
			link.l1.go = "EscapeSlave_1";
		break;
			
		case "EscapeSlave_1":
			dialog.text = "Kitûnô! Most pedig, egyenesen a lényegre. Hallottad a legfrissebb híreket?";
			link.l1 = "Hm, mire gondolsz? Minden nap rengeteg hír érkezik.";
			link.l1.go = "EscapeSlave_2";
		break;
			
		case "EscapeSlave_2":
			dialog.text = "Ez a mi üzletünkrôl szól. Az Újvilág történetében a legnagyobb rabszolgaszökés történt! Több mint ezer lélek szökött meg, és közben elpusztították és felgyújtották Hollandia néhány elôôrsét.";
			link.l1 = "Érdekes. Folytassa.";
			link.l1.go = "EscapeSlave_3";
		break;
			
		case "EscapeSlave_3":
			dialog.text = "De nem csak úgy elszöktek, valahogy sikerült elhagyniuk a szigetet! Nem maradtak nyomok. Mathias Beck felháborodott. De nem ez a lényeg... A lényeg az, hogy megkérem, hajózzon Curacaóba, tudja meg, mi történt ott, találja meg a menekülteket, és fogja el ôket\nés persze mentse meg ôket a holland igazságszolgáltatás kezétôl, amely kegyetlen lenne velük. Fejenként 300 pesót fizetek - úgy hallottam, hogy nagyon jó rabszolgák.";
			link.l1 = "Megvan. Curacao felé tartok. Várjatok a jó hírekkel.";
			link.l1.go = "EscapeSlave_yes";
			link.l2 = "Tudod, hogy nem vállalom a küldetést. Nem fosztom meg az embereket a szabadságuktól. Az életüket tették kockára, hogy megszerezzék. Megérdemelték.";
			link.l2.go = "EscapeSlave_no";
		break;
			
		case "EscapeSlave_no":
			dialog.text = "Milyen kár... Ezt nem vártam tôled... és a legmegfelelôbb idôpontban. Gondolom, számodra egyértelmû, hogy a partnerségünknek vége. Viszontlátásra.";
			link.l1 = "Legyen szép napod.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
		break;
			
		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum)*100;
			if (amount < 0)
			{
				dialog.text = "Ha! Nemcsak hogy sikerült a nehéz küldetésed, de még több rabszolgát is hoztál, mint amennyit kértem - "+ sTemp +" rabszolgákat. De "+ sNum +" rabszolgák nem szöktek meg Curacaóból. 100 pezót fizetek egy fejért. Gondolom, ez megfelel önnek. A jutalmad 330 000 pezó és " + FindRussianMoneyString(iSlaveMoneyH) + " egy feleslegért, ha-ha.";
				link.l1 = "Ha! Téged biztosan nem lehet becsapni. Egyetértek, bármit is mondasz, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, makeint(iSlaveMoneyH));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoneyH));
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				dialog.text = "A legkiválóbb módon teljesítetted ezt a kellemetlen küldetést, és elhoztad nekem a "+ sTemp +" rabszolgákat. A jutalmad " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Köszönöm. Öröm veled üzletelni, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				dialog.text = "Sikerrel teljesítetted ezt a nehéz küldetést. A díj nem olyan gazdag, mint amire számítottam, de így is elégedett vagyok. Tehát ide hoztad "+ sTemp +" rabszolgákat. A jutalmad " + FindRussianMoneyString(iSlaveMoney) + ".";
				link.l1 = "Köszönöm. Örülök, hogy üzletet kötöttünk, " + npchar.name + "!";
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", sTemp);
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = "Megtaláltad ôket? Hm... mit hoztál nekem?"+ sTemp +" rabszolgákat? Hol van a rakomány többi része? És meg se próbáld azt mondani, hogy elsüllyesztetted. Biztos eladtad csempészeknek, vagy ami még rosszabb - annak a szemét Lavoisier-nek az Isla-Tesoro-ról. Tûnj innen, nem akarok többé veled dolgozni.";
				link.l1 = "Ég veled!";
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = "Megtaláltad ôket? Mi van a rabszolgákkal? Hol van a rakományunk? És meg se próbáld azt mondani, hogy elsüllyesztetted. Biztos eladtad csempészeknek, vagy ami még rosszabb - annak a szemét Lavoisier-nek az Isla-Tesoro-ról. Takarodj innen, nem akarok veled tovább dolgozni.";
			link.l1 = "Ég veled!";
			link.l1.go = "node_hanter_1";
		break;
		
		case "Escape_slaves_win_1":
			dialog.text = "Nagyra értékelem, " + pchar.name + ". Tényleg. Gyere ide újra egy hónap múlva, és elôkészítek egy új üzletet, ami mindkettônk számára nyereséges lesz.";
			link.l1 = "Én is elégedett vagyok a partnerségünkkel, " + npchar.name + ". Találkozunk egy hónap múlva.";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
		break;
			
		case "Slaveshore":
			dialog.text = "Épp idôben jöttél, " + pchar.name + ". Bátor és nem lelkiismeretes matrózt keresek, ha-ha. Készen állsz a munkámra?";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "Slaveshore_1";
		break;
			
		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Ezúttal nagyon egyszerû. A mai napon egy pinace '" + pchar.questTemp.Slavetrader.ShipName + "' zászló alatt " + NationNameGenitive(sti(npchar.nation)) + " horgonyt vetett a " + XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen") + " öbölben. Nagy mennyiségû 'ebony' val volt megrakodva a helyi csempészek segítségével. Kétezer fej, nem kevesebb\nNincs katona a legénységben, és a kapitány egy kereskedô. Összességében egyáltalán nem fenyegetô. Szálljatok fel a hajóra, és hozzátok ide a rakományt. 200 pezó fejenként, mint mindig.";
			link.l1 = "Hm... Ez nem ugyanaz, mint a legutóbbi munka. Azt javaslod, hogy támadjam meg a saját nemzeted hajóját!";
			link.l1.go = "Slaveshore_2";
		break;
			
		case "Slaveshore_2":
			dialog.text = "Nem értem, " + pchar.name + ". Számít a hajó zászlaja? Tényleg érdekel ez téged?";
			link.l1 = "Tényleg? Nem, leszarom, az aranynak nincs nemzetisége. Csak egy kicsit váratlanul ért...";
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = "Engem érdekel. Nem akarom, hogy " + NationNameAblative(sti(npchar.nation)) + " az ellenségeim között legyen.";
			link.l2.go = "Slaveshore_3_no";
		break;
			
		case "Slaveshore_3_no":
			dialog.text = "Komolyan mondod? Ugye csak viccelsz velem, nem bízhatsz meg senkiben manapság... Ebben az esetben, menj el. És felejts el mindent, amit itt láttál vagy hallottál!";
			link.l1 = "Viszlát," + npchar.name + ".";
			link.l1.go = "node_hanter_1";
		break;
			
		case "Slaveshore_3_yes":
			dialog.text = "Miért lepôdik meg? Mert nem érdekelnek az érmék' nemzetiség? Biztosíthatlak, hogy valóban nem. Hogy ôszinte legyek, a hazafiság nem tesz jót egy profi bankárnak, hacsak nem akar egy nap csôdbe menni\nDe elég a filozófiából. Térjünk a lényegre - a hajó éjfélig itt marad, úgyhogy nincs sok idôd hátra. Készen állsz a folytatásra?";
			link.l1 = "Igen, " + npchar.name + ", már úton vagyok.";
			link.l1.go = "Slaveshore_4";
		break;
			
		case "Slaveshore_4":
			dialog.text = "Pompás. Nincs kétségem afelôl, hogy sikerrel teljesíti a küldetésünket. Sok szerencsét." + pchar.name + ".";
			link.l1 = "Köszönöm! Viszontlátásra.";
			link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
            pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//заглушка
		break;
			
		case "Pinas_lose":
		dialog.text = "Nos, " + GetFullName(pchar) + ", mi a helyzet a küldetéseddel? A derûtelen arcod elárulja, hogy kudarcot vallottál.";
			link.l1 = "Átkozottul igazad van... Én... Nos... Elkéstem. A kocsmában voltam, és amikor elhajóztam, senki sem volt a tengeren.";
			link.l1.go = "Takeslaves_5_lose";
		break;
			
		case "Slaveshore_5":
			dialog.text = "" + pchar.name + ", Kérem, nyugodjon meg. Nem az én hibám! A fenébe, túl késôn kaptam meg a jelentést... Árulás történt! Az egyik megbízható emberem elárult engem!";
			link.l1 = "Rendben, látom, hogy igazat beszélsz. Szerencsés vagy, hogy a pinnace kapitánya elmondta, hogy a 'üzletünk' leleplezôdött. Már rég megöltelek volna, ha nem fecsegi ki. De te, te kibaszott pénzeszsák, végig azt mondogattad, hogy te 'birtoklod ezt a várost'!.";
			link.l1.go = "Slaveshore_6";
		break;
			
		case "Slaveshore_6":
			dialog.text = "A rajtaütést nem a helyi hatóságok szervezték, különben tudtam volna... " + pchar.name + ", ez nem a megfelelô idô a veszekedésre. Mindketten veszélyben vagyunk, az egyik volt vállalkozóm felültetett minket\nSikerült megtudnom, hogy az összegyûjtött bizonyítékokat - egy papírcsomagot - a fôkormányzónkhoz szállítják. Ha nála vannak, nekünk végünk! Egyébként te fogsz a legjobban szenvedni.";
			link.l1 = "Most már értem, mire gondolt az a szemét kapitány!";
			link.l1.go = "Slaveshore_7";
		break;
			
		case "Slaveshore_7": //выбор острова, куда бригантина пойдёт
			switch (sti(NPChar.nation))
            {
                case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
                break;
                case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Nevis";
                break;
                case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";  
                break;
                case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";     
                break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = "Hallgassanak figyelmesen. Még van esélyünk. A csomagot a brigantine '" + pchar.questTemp.Slavetraderbrig.ShipName + ". Ez az egyetlen dolog, amiben biztos vagyok. Az iratokat a fôkormányzó rezidenciájára szállítják a " + XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island) + ". El kell fogni, beszállni és megtalálni azokat a hiteltelenítô bizonyítékokat.";
			link.l1 = "Nincs sok választásunk. Imádkozzatok értem, magatokért, és reméljétek, hogy sikerül elkapnom. Mindezt majd újra megbeszéljük, ha visszajöttem. Ne higgyétek, hogy csak úgy elengedem a dolgot.";
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
            pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);	//таймер
			pchar.questTemp.Slavetrader = "wait1";	//это нода ожидания, пустая
		break;
		
		case "Slaveshore_8":
			dialog.text = "Ennek a csomagnak a beszerzése a legfontosabb prioritás! Nem leszek biztos a biztonságomban, amíg nem szállítja le nekem... A fenébe..." + pchar.name + ", úgy tûnik, van egy kis gondunk...";
			link.l1 = "Mi a baj?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
			break;
			
		case "Brig_lose":
			dialog.text = "A fenébe... Számítottam rád, " + pchar.name + ". Akkor jó. De nem fogunk többé üzletet kötni. Ha nem vagyok képes megvesztegetni egy nyomozót, akkor el kell menekülnöm. És nem ajánlom, hogy itt maradj - a katonák bármikor idejöhetnek. Viszontlátásra.";
			link.l1 = "Isten veled, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Letter_lose":
			dialog.text = "Ott voltak. Nos, nem tudunk együtt üzletelni, ez már nem biztonságos. Viszontlátásra.";
			link.l1 = "Isten veled, " + npchar.name + ".";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Brig_win":
			dialog.text = "Kiváló! Nem kételkedtem benned, " + pchar.name + ". Kérem, adja meg nekem azokat a papírokat, túl ideges vagyok.";
			link.l1 = "Fogd ôket.";
			link.l1.go = "Brig_win_1";
		break;
			
		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = "Jól van... Most már biztonságban vagyok. A fôkormányzó semmit sem fog tudni, és már minden problémát megoldottam a helyi hatóságokkal, de ez elég drága volt, mondom neked.";
			link.l1 = "Jól hangzik, de nem gondolja, hogy kárpótolnia kell a gondatlansága miatt felmerült problémáimért?";
			link.l1.go = "Brig_win_2";
		break;
			
		case "Brig_win_2":
			dialog.text = "Persze, " + pchar.name + ". Sôt, még sokkal tartozom is neked. És nagyon várom, hogy folytassuk az üzletet. De kérem, értsen meg - hatalmas összeget költöttem - a kormányzó és a parancsnok hûsége sokba kerül. És az egész ôrjárat meggyilkolásával a bankomban kellett foglalkoznom...";
			link.l1 = "Úgy érti, hogy nem fogja megtéríteni a költségeimet?!";
			link.l1.go = "Brig_win_3";
		break;
			
		case "Brig_win_3":
			dialog.text = "Ne légy ilyen szigorú, " + pchar.name + ". Most tényleg bajban vagyok a pénzzel, ezért másfajta fizetést ajánlok.";
			link.l1 = "Akkor figyelek rád.";
			link.l1.go = "Brig_win_4";
		break;
			
		case "Brig_win_4":
			dialog.text = "Engem és a társamat egy évvel ezelôtt a Main déli partjainak közelében érte el a vihar. Hajóinkat a Boca de la Serpienta partvidék szikláinak vetette, és bár hamarosan elsüllyedtek, a rakományunkat sikerült partra húznunk. Drágakövekkel és ékszerekkel teli ládákat. Az öböl elég hangulatosnak tûnt, így gond nélkül elrejtettük a kincseket\nDe másnap reggel, amint a vihar véget ért, ránk támadtak az indiánok. Így halt meg a túlélôk többsége, köztük a társam is. Nekem és néhány matróznak sikerült elmenekülnünk egy hosszúhajón\nBiztonságban elértük Cumana-t, mégsem kockáztattam meg, hogy visszatérjek a kincsekért. Biztos vagyok benne, hogy a helyi vademberek még mindig védik a partot és a ládáimat is. De azzal a csapat rézbôrûvel elbánhatsz\nAz ékszerek, amiket ott találsz, elegendôek ahhoz, hogy fedezd az összes kiadásodat, beleértve egy dél-maini expedíciót is.";
			link.l1 = "Hm... rendben. Akkor én Cumana felé tartok.";
			link.l1.go = "Brig_win_5";
		break;
			
		case "Brig_win_5":
			dialog.text = "Biztos lehetsz benne, " + pchar.name + ", hogy mindaz, amit mondtam, igaz volt. Várom, hogy egy hónap múlva találkozzunk. Már van a fejemben még egy üzlet, és hogy hogyan kellene segítenem az akadozó üzletemet. Viszontlátásra.";
			link.l1 = "Viszlát, " + npchar.name + ".";
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
            Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
            Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
		break;
			
		case "SlaveGalleon":
			dialog.text = "És itt vagy, " + pchar.name + ". Szép, pont idôben jöttél, mint mindig. Szeretnék még több információt adni a karibi rabszolgapiacról, mielôtt a következô küldetést adnám neked. Tudod, hogy mit jelent az a szó 'repartimiento' mean?";
			link.l1 = "Hm, nem, " + npchar.name + ", nem tudom. De feltételezem, hogy arról szól, hogy valakitôl elvesznek valamit. Igazam van?";
			link.l1.go = "SlaveGalleon_1";
		break;
			
		case "SlaveGalleon_end":
			dialog.text = "Meglepsz. Mit vártál tôlem? Tûnj el!";
			link.l1 = "Egy illegális üzlet túl kemény az én erkölcsömnek. Különösen a rabszolga-kereskedelem.";
			link.l1.go = "node_hanter_1";
		break;
			
		case "SlaveGalleon_1":
			dialog.text = "Már majdnem megvan," + pchar.name + ". Elvenni valakinek a szabadságát. A Repartimiento egy trükkös és legális módja a helyi indiánok rabszolgasorba taszításának. Hogy úgy mondjam. A spanyol hatóságok használják a Main ôslakosokkal szemben. Érdekli, hogy többet tudjon meg?";
			link.l1 = "Miért ne?";
			link.l1.go = "SlaveGalleon_2";
		break;
			
		case "SlaveGalleon_2":
			dialog.text = "A spanyol korona képviselôi meglátogatják az indián településeket. Cinikus megtévesztéssel és közvetlen fenyegetéssel arra kényszerítik az indiánokat, hogy mesés áron vásároljanak mindenféle szemetet, például rothadt húst és régi borotvákat. Hitelre\nMivel késôbb, mondjuk egy év múlva a képviselôk visszatérnek, és fizetést követelnek. Ha az indiánok nem tudnak fizetni, ami általában meg is történik, a spanyolok elviszik a munkaképes embereik egy részét, állítólag egy idôre, és hogy 'megtanítsák ôket földet mûvelni'\nAmint érthetô, soha nem térnek vissza a településeikre. Így jutnak el a mi megbízható rézbôrûjeink a cukorültetvényekre és a mamutfenyôgyárakba.";
			link.l1 = "A fenébe... tényleg... Mit csinálnak az indiánok? Ellenállnak, amikor a spanyolok leigázzák ôket? Vagy csak nem értik, hogy mi történik?";
			link.l1.go = "SlaveGalleon_3";
		break;
			
		case "SlaveGalleon_3":
			dialog.text = "Gondolom, mindig látják, hogy ez lesz, de csak néhányan mernek nyíltan ellenkezni, különösen akkor, amikor a spanyolok felmutatnak egy papírt a törzsfônök ujjlenyomatával. Persze, ilyen taktikát általában az olyan békés törzseknél alkalmaznak, mint az arawakok vagy a miskitók. A harcias Itza vagy Akawoys\nilyen trükk nem fog mûködni... Nos, beszéljünk a küldetésedrôl.";
			link.l1 = "Már érzem a sok érme szagát! Figyelek rád, " + npchar.name + ".";
			link.l1.go = "SlaveGalleon_4";
		break;
			
		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Caracasból hamarosan egy nehéz gálya indul. A neve " + pchar.questTemp.Slavetrader.ShipName + ". Hatalmas mennyiségû rabszolgát tartalmaz - körülbelül 3000 embert - orinocói indiánokat, akiket a repartimentos politika szerint fogtak el. A gálya Santiagóba hajózik, a kubai cukorültetvényeknek sok munkásra van szükségük. El kell foglalnod a gályát a rakományával együtt. Én a helyedben legalább két hajót vinnék magammal, azt mondják, hogy a gálya a legjobb a maga nemében. A fizetés marad a szokásos - 200 pezó fejenként. ";
			link.l1 = "Heh! Jól hangzik. Egyetértek.";
			link.l1.go = "SlaveGalleon_5";
			link.l2 = "Tudod, hogy nem szeretem a repartimiento-t. Túl cinikus. Nem fogom ezt csinálni.";
			link.l2.go = "SlaveGalleon_end";
		break;
			
		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add; 
			dialog.text = "Akkor sok szerencsét kívánok. Tudjátok, hogy ennek a gályának a kapitánya nagyon képzett és tapasztalt haditengerész. Nem lesz könnyû harc, úgyhogy készüljetek fel. Ne vesztegessétek az idôt, tizenöt-húsz napba telik, mire eléri " + sTemp + " Santiagót. Próbáld meg nem elszalasztani, bár ezt a gályát tényleg nehéz eltéveszteni\nIgen! Majdnem elfelejtettem! A hajón rengeteg indián csecsebecse van, a rézbôrûek gyakran fizetnek adósságot a kultikus tárgyaikkal és kézmûves termékeikkel. Hozzatok el nekem bármi különlegeset, amit találtok, minden értékes tárgyért, amit elhoztok, busásan megfizetek.";
			link.l1 = "Megértem, uram.";
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 20, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
		break;
			
		case "Lostgalleon":
			dialog.text = "Nos, " + pchar.name + ", ez volt az utolsó reményem... Ezért ajánlottam neked ezt a munkát. Senki más, csak te vagy képes erre... és úgy látom, hogy te sem vagy rá képes. Akkor búcsúzzunk el. A legutóbbi kudarc és a pletykák után az összes ügyfelem elment. És majdnem csôdbe mentem, talán el kell hagynom ezt a várost. Nem hibáztatlak - ez a munka túl kemény volt. Eh... Viszlát," + pchar.name + ".";
			link.l1 = "Nagyon sajnálom, " + npchar.name + ", ez túl messzire ment. Nagyon sajnálom. Talán majd minden lecsillapodik. Viszontlátásra.";
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			if(amount < 1) 
			{
				dialog.text = "Fuh, most már jobban érzem magam... Igazam volt, hogy bíztam benned... Honnan jött ez az irónia? Mi a baj?";
				link.l1 = "Kedves uram, ez nem egy gálya volt... vagy egy nagyon nagy gálya... A fenébe! Ez egy vonalhajó volt! És még csak nem is figyelmeztettél! De sikerült felszállnom rá. Vannak "+ sTemp +" rabszolgáim, és készen állok arra, hogy átadjam ôket neked. Az egyezségünk értelmében tartozol nekem - " + FindRussianMoneyString(iSlaveMoney) + ". Jó lenne némi kárpótlást kapni a félretájékoztatásodért.";
				link.l1.go = "Wingalleon_1";
			}
			else
			{
			dialog.text = "Megtaláltad a gályát? Mi van a rabszolgákkal? Állítólag háromezer van belôlük, és nem kevesebb! A fenébe is, mindenki patkány és áruló! Ezt nem tôled vártam... te voltál az utolsó reményem\nNagyon jó... Esküszöm, minden pénzemet arra fogom költeni, hogy elpusztítsalak, hogy megöljelek! Az egész " + NationNameGenitive(sti(npchar.nation)) + " flotta vadászni fog rád! Tûnjetek el innen!";
				link.l1 = "Nos...";
				link.l1.go = "Wingalleon_goaway";
			}
		break;
			
		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			DialogExit();
		break;
			
		case "Wingalleon_1":
			dialog.text = "Nem mondod! Esküszöm, fogalmam sem volt róla. Egy nehéz gályának kellett volna hajózni, nem egy átkozott hajónak! Úgy tûnik, az utolsó pillanatban változtattak a tervükön... De mégis sikerült!\nTeljesen egyetértek veled a pénzzel és a költségeid megtérítésével kapcsolatban, a helyzet az, hogy nekem most nincs ilyen összegem. Tudsz a mostani gondjaimról... De ne haragudj, " + pchar.name + ", az Isten szerelmére. Adja ide a rakományt, és én eladom, az ügyfelem már várja\nÖt napon belül meglesz az egész összeg, így megkapja, amit megérdemel. Bízhat bennem. Tessék, vegye el az összes készpénzemet, amim most van.";
			link.l1 = "Hm... Azt vártam, hogy most megkapom a pénzt. Bárcsak tudnád, hogy milyen harcokon kellett keresztülmennem! Ah, mindegy... Együttérzek veled. De ne feledd, ha megpróbálsz átverni, még Európában is megtalállak!";
			link.l1.go = "Wingalleon_yes";
			link.l2 = "Tudod, " + npchar.name + ", cseszd meg! Nem volt alku. El sem tudod képzelni, hogy milyen harcot kellett kezelnem. Minden rabszolgát magamhoz veszek és eladom ôket a te közvetítésed nélkül.";
			link.l2.go = "Wingalleon_no";
		break;
			
		case "Wingalleon_no":
			dialog.text = "Szóval, most már beszélsz! Úgy tûnik, a gyanútlan " + npchar.name + " csak egy tehén volt, amit meg lehet fejni, egy egyszerû késedelem elég ahhoz, hogy átverjetek engem, és saját magatoknak indítsatok egy mûveletet. Úgy látszik, elfelejtetted, hogy én voltam az, aki a munkát és a tippet adta neked a zsákmányról\nNagyon jó... Esküszöm, minden pénzemet arra fogom költeni, hogy tönkretegyelek, hogy megöljelek! Az egész " + NationNameGenitive(sti(npchar.nation)) + " flotta vadászni fog rád! Tûnj a szemem elôl!";
			link.l1 = "Ne merészelj megijeszteni engem, egy üres pénzesláda. Elsüllyesztem az összes flottátokat, és rákokat etetek vele.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
		break;
			
		case "Wingalleon_yes":
			dialog.text = "Köszönjük megértését, " + pchar.name + ". Ígérem, hogy minden rendben lesz, nincs szükség a fenyegetéseidre\nFogadd ezt elôlegnek. Tizenöt láda. Ebbôl öt az erkölcsi kár kompenzálására szolgál. Öt nap múlva gyere el hozzám a többiért.\nNe felejtsd el elhozni az összes indiai tárgyat, amit a hajón találtál... ha egyáltalán találtál, természetesen. Amúgy sincs mit fizetnem értük.";
			link.l1 = "Öt nap alatt" + npchar.name + ". Öt nap múlva...";
			link.l1.go = "Wingalleon_yes_1";
		break;
			
		case "Wingalleon_yes_1":
			TakeNItems(pchar, "chest", 15);
			Log_Info("Kaptál kreditládát");
			PlaySound("interface\important_item.wav");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp)*200-120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
		break;
	
		case "FindRat":
			dialog.text = "Ahogy ígértem, " + pchar.name + ", kész vagyok fizetni. A rabszolgák elkeltek, a vevô boldog, és mi is. Az elôleg levonása után a jutalmad" + FindRussianMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)) + ". Kérem, vegye el a pénzét.";
			link.l1 = "Pompás, " + npchar.name + ". Jó olyan emberrel üzletelni, aki tartja a szavát...";
			link.l1.go = "FindRat_1";
		break;
			
		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = "Mindig bízhatsz a szavamban, " + pchar.name + ". Soha nem adtam okot arra, hogy kételkedj bennem. A partnereknek ôszintének kell lenniük egymással, ez az üzlet kulcsa\nBeszéljünk most az indiai mûtárgyakról. Mutasd meg, mid van, ne várakoztasd meg a hozzám hasonló gyûjtôket.";
			link.l1 = "Hm... Nézd meg.";
			link.l1.go = "FindRat_2";
		break;
			
		case "FindRat_2":
			if (CheckCharacterItem(pchar, "talisman16"))
			{
				dialog.text = "Igen! Kitûnô! Egy arany rituális kés! Ritka dolog. Mindig is szerettem volna egy ilyet a gyûjteményemben. 30 000-et ajánlok érte vagy egy 'Ehecatl' amulettet cserébe. Nekem amúgy is van belôle kettô.";
				link.l1 = "Elfogadom a pénzt.";
				link.l1.go = "BG_money";
				link.l2 = "Cserébe elfogadnék egy 'Ehecatl' amulettet.";
				link.l2.go = "BG_change";
				link.l3 = "Jobb, ha ezt a kést magamnál tartom.";
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = "Lássuk csak... Sajnos nincs semmi érdekes számomra.";
				link.l1 = "Ahogy akarod.";
				link.l1.go = "BG_PF";
			}
		break;
			
		case "BG_money":
			dialog.text = "Nagyszerû. Fogd a 30 000-ed, és ez az indiai kés az enyém.";
			link.l1 = "Rendben. És ez minden, ami érdekli...";
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			Log_Info("Adtál egy arany kést");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
		break;
			
		case "BG_change":
			dialog.text = "Nagyszerû! Itt van az amuletted, és ez az indiai kés mostantól az enyém.";
			link.l1 = "Rendben. És ez minden, ami érdekli...";
			link.l1.go = "BG_PF";
			Log_Info("Adtál egy arany kést");
			Log_Info("Kaptál egy Ehecatl-amulettet.");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "talisman16", 1);
			TakeNItems(pchar, "obereg_9", 1);
		break;
			
		case "BG_no":
			dialog.text = "Tökmindegy. De amúgy is kár érte...";
			link.l1 = "Rendben. És ez minden, ami érdekli...";
			link.l1.go = "BG_PF";
		break;
			
		case "BG_PF":
			dialog.text = "Várj! Hadd nézzem meg újra...";
			link.l1 = "Persze. Gyere, nézd meg és válaszd ki, amit akarsz.";
			link.l1.go = "PF_check";
		break;
			
		case "PF_check":
			if (CheckCharacterItem(pchar, "mineral31"))
			{
				dialog.text = "Ez! És elôször észre sem vettem. Engem ez a rézbôl készült gyûrûs csont érdekel. Egy ilyen érdekes dolog, amit mondanék neked... Tudok fizetni 20 000 pezót, vagy cserébe adhatok egy 'Cimaruta' amulettet.";
				link.l1 = "Elfogadom a pénzt.";
				link.l1.go = "PF_money";
				link.l2 = "Cserébe elfogadnék egy 'Cimaruta' amulettet.";
				link.l2.go = "PF_change";
				link.l3 = "Ezt a leletet megtartanám magamnál.";
			link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = "Nem... nincs itt semmi más érdekes.";
				link.l1 = "Tökmindegy!";
				link.l1.go = "FindRat_3";
			}
		break;
			
		case "PF_money":
			dialog.text = "Nagyszerû! Itt van a 20 000 pezód, és ez a csont mostantól az enyém.";
			link.l1 = "Szép. Jól érzem magam az üzlet miatt.";
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("Adtál egy mágikus csontot");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
		break;
			
		case "PF_change":
			dialog.text = "Pompás! Itt van az amuletted, és ez a csont most már az enyém.";
			link.l1 = "Szép. Jól érzem magam az üzlet miatt.";
			link.l1.go = "FindRat_3";
			Log_Info("Adtál egy mágikus csontot");
			Log_Info("Kaptam egy Cimaruta amulettet.");
			PlaySound("interface\important_item.wav");
			RemoveItems(PChar, "mineral31", 1);
			TakeNItems(pchar, "amulet_11", 1);
		break;
			
		case "PF_no":
			dialog.text = "Tökmindegy. De amúgy is kár érte...";
			link.l1 = "Szükségem van arra a csontra magamnak, nagyon sajnálom.";
			link.l1.go = "FindRat_3";
		break;
			
		case "FindRat_3":
			dialog.text = "Nos... azzal, hogy felszálltál a gályára, ó, bocsánat, a vonalhajóra, megmentettél engem. Nagyra értékelem a partnerségünket, " + pchar.name + ". Te vagy a legjobb ügynököm.";
			link.l1 = "Ez hízelgô. Túlbecsülöd a teljesítményemet...";
			link.l1.go = "FindRat_4";
		break;
			
		case "FindRat_4":
			dialog.text = "Teljesen komolyan mondom. És megkérem, hogy hajtson végre egy újabb küldetést a rendkívüli képességei miatt, és mert bízom magában.";
			link.l1 = "Heh! Meglepô! Hallgatom. Hol van egy másik gálya a kenôcsökkel?";
			link.l1.go = "FindRat_5";
		break;
			
		case "FindRat_5":
			dialog.text = "Ezúttal nem a rabszolgákról van szó. Meglepôdtél? Jól megfizetlek a küldetésért... Nagyon jól.";
			link.l1 = "Térjünk rá az üzletre.";
			link.l1.go = "FindRat_6";
		break;
			
		case "FindRat_6":
			dialog.text = "Ez az üzlet kapcsolódik a közelmúltbeli eseményekhez, amelyeknek ön is részese volt... Szóval, mint talán tudod, egy eléggé illegális üzletet csinálok - rabszolga-kereskedelmet. Talán azt is tudod, hogy mindenféle megbízatásra felbérelek olyan kalózokat, mint te\nEgyik emberem nemrég ismeretlen okokból elárult engem. Bizonyítékokat gyûjtött, és jelentést tett a hatóságoknak. Önnek volt szerencséje a saját szemével látni a következményeket. Egy hajó katonákkal érkezett ide... a többit már tudod\nA helyzet rendezése elég nagy erôfeszítésembe került. Ahogy valószínûleg megérti, nem hagyhatom ezt az árulást válasz nélkül. Emellett nem tudok nyugodtan élni és dolgozni, tudván, hogy a patkány még mindig életben van. Küldtem fejvadászokat, de még nincs eredmény\nKérem, hogy személyesen foglalkozzon ezzel az üggyel. Annál is inkább, mert a tettei téged is érintettek.";
			link.l1 = "Hm... ezt a fattyút fel kell akasztani egy karóra! Mesélj még róla, és persze a munkámért járó fizetségemrôl.";
			link.l1.go = "FindRat_7";
		break;
			
		case "FindRat_7":
			dialog.text = "Ne aggódj emiatt. Nagyon sokat fogok fizetni a megszüntetéséért, és nem csak a pénzrôl beszélek. Nem kímélem a gyûjteményem legjobb darabjait sem. Beszéljünk inkább az emberrôl. A neve Francois Gontier\nTudott a vadászatomról, ezért eladta a fregattját, hogy elrejtse a nyomait. A kollégáim elmondták, hogy látták Panamában. Úgy gondolom, hogy onnan kellene kezdenie a keresést.";
			link.l1 = "Nos, akkor már úton vagyok.";
			link.l1.go = "FindRat_8";
		break;
			
		case "FindRat_8":
			dialog.text = "Akkor sok szerencsét kívánok. Tudd, hogy ez a Gontier nagyon tapasztalt tengerész, és a legénysége vakmerô gyilkosokból áll. Nincs vesztenivalója, ezért nagyon elkeseredetten fog harcolni.";
			link.l1 = "Én nem félek az ilyen emberektôl, mint ô, de megfontolom, amit mondtál. Isten veled, és légy biztos benne, hogy még a pokolban is elkapom.";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
		break;
			
		case "Wincorvette":
			dialog.text = "Pompás! Most már megírhatja a jelentéseit a medúzáknak. Senki sem mer velem szórakozni. Köszönöm neked, " + pchar.name + ", nélkülözhetetlen ember vagy.";
			link.l1 = "Köszönöm, " + npchar.name + ", hogy ilyen pozitívan értékelted a tetteimet. Mi a helyzet a fizetésemmel?";
			link.l1.go = "Wincorvette_1";
		break;
			
		case "Wincorvette_1":
			dialog.text = "Persze. Megfelelô árat fizetnék egy ilyen nehéz munkáért. Elôször is, bemutatom önnek ezt a kiváló távcsövet.";
			link.l1 = "Hû, micsoda ajándék!";
			link.l1.go = "Wincorvette_2";
		break;
			
		case "Wincorvette_2":
			dialog.text = "Emellett itt van 100 000 pezó az elsôdleges fizetséged és 50 000 pezó a saját költségeid kompenzálására.";
			link.l1 = "Köszönöm, " + npchar.name + ". Még egyszer mondom, hogy igazán öröm veled üzletelni.";
			link.l1.go = "Wincorvette_3";
			Log_Info("Kaptál egy kiváló távcsövet.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "spyglass4", 1);
		break;
			
		case "Wincorvette_3":
			dialog.text = "Várni fogom Önt egy hónap múlva, mint mindig. Ez egy nagyon nagy üzlet a sorban és szükséged lesz egy jól felszerelt századra. Kérem, hogy ezt értsék meg és készüljenek fel jól. Ha a tervem beválik, gazdagok leszünk.";
			link.l1 = "Jó," + npchar.name + ". Visszajövök, ha készen állok.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
			
		case "Lostcorvette":
			dialog.text = "Kár, milyen kár... Hát, ne búsulj, nem te vagy az elsô ember, akit ez a söpredék átvert. Egyszer úgyis elkapom\nAmíg te, gyere el hozzám egy hónap múlva. Ez nagy dolog lesz, úgyhogy gyûjts össze egy jól felszerelt és felfegyverzett osztagot. Kérlek, vedd komolyan, és igyekezz a lehetô legjobban felkészülni. Ha a tervem beválik, gazdagok leszünk.";
			link.l1 = "Jó, " + npchar.name + ". Visszajövök, ha készen állok.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
		break;
		
		case "Havana_fort":
			dialog.text = "Épp idôben jöttél, " + pchar.name + "! Már majdnem elkezdtem aggódni, el akartam küldeni egy embert, hogy keressen meg\nLássunk hozzá! A küldetésed most igazán nagy és kockázatos, de a jutalom megfelelô. Több mint egymillió pezót fogsz kapni a munka elvégzése után.";
			link.l1 = "Most már beszélgetünk! Figyelek, " + npchar.name + ".";
			link.l1.go = "Havana_fort_1";
		break;
		
		case "Havana_fort_1":
			dialog.text = "A rabszolgasorba vett indiánokat kisebb csokrokban szállították Havannába az egész Mainon keresztül, néhány gálya is érkezett Afrikából, és kirakodták ôket. Mostanra már majdnem ötezer rabszolga van a havannai erôd magas falai mögött.";
			link.l1 = "Az az érzésem, hogy az üzlet a Havanna megrohamozásáról szól.";
			link.l1.go = "Havana_fort_2";
		break;
		
		case "Havana_fort_2":
			dialog.text = "Jól érzed, " + pchar.name + ". Pontosan ezt szeretném kérni tôled. Téged és csakis téged. Kétlem, hogy bárki más az ügynökeim közül képes lenne erre\nhiszem, hogy ön benne van?";
			link.l1 = "Hogy ôszinte legyek, " + npchar.name + ", most egy kicsit meg vagyok döbbenve. Fogalmam sem volt róla, hogy a tevékenységed ilyen... nagyszabású. Persze, benne vagyok. " + RandSwear() + "";
			link.l1.go = "Havana_fort_3";
			link.l2 = "Tudod mit, " + npchar.name + ", ez már túl messzire megy. Elegem van ezekbôl a meglepetéseidbôl. Legközelebb a kapzsiságod azt akarja majd, hogy hadat üzenjek Spanyolországnak, és akkor egyedül kell majd harcolnom ellenük. Ha tényleg szükséged van azokra a rabszolgákra, akkor rohamozd meg Havannát egyedül.";
			link.l2.go = "Havana_fort_not";
		break;
		
		case "Havana_fort_not":
			dialog.text = "Ezt nem vártam tôled... A francba, mit mondjak az ügyfelemnek? Jól van. Ez a te döntésed, és új partnert kell találnom. Viszlát, " + pchar.name + ". És a jövôben nem veszem igénybe a szolgáltatásait. Ne feledje, hogy elejtette azt az üzletet, amely a hetedik generációig gazdaggá tehette volna az utódait.";
			link.l1 = "Nem kaphatsz meg minden pénzt a világon, és többet harapsz le, mint amennyit meg tudsz rágni. Isten veled, " + npchar.name + ".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
		break;
		
		case "Havana_fort_3":
			dialog.text = "Tudtam, hogy egyet fogsz érteni. Most pedig hallgassátok meg a részleteket. A havannai erôd mindig is nehéz célpont volt, de most még nehezebb\nKét hadihajó ôrzi Kuba partjait, és elôször velük kell foglalkoznod, mielôtt megrohamoznád az erôdöt...";
			link.l1 = "Értem. Nem ez lesz az elsô alkalom, hogy Line Ships ellen harcolok, ha-ha. Mennyi idôm van még?";
			link.l1.go = "Havana_fort_4";
		break;
		
		case "Havana_fort_4":
			dialog.text = "Nem sok. Három hét, nem több, és utána a rabszolgákat a kubai spanyol elôôrsökre szállítják. Sietned kell. ";
			link.l1 = "Akkor ne vesztegessük az idônket. Már úton vagyok!";
			link.l1.go = "Havana_fort_5";
		break;
		
		case "Havana_fort_5":
			dialog.text = "Egy pillanat!" + pchar.name + ", neked és nekem soha nem voltak félreértéseink és nézeteltéréseink. Mindazonáltal szeretném, ha tudnád, mi folyik itt. Számítok rád, és az ügyfél számít rám\nEzzel a mûvelettel rengeteg erôfeszítést és pénzt fektettünk be. Minden egyes rabszolgát, mind az ötezret le kell szállítania nekem\nellenkezô esetben nagyon radikális intézkedéseket fogunk tenni ön ellen. Ne vegye sértésnek, ez csak egy figyelmeztetés. ";
			link.l1 = "Ne aggódjon, " + npchar.name + ", én értem, hogy mi az üzlet, ezért ne felejtsen el fizetni nekem, amint leszállítom ôket. Viszontlátásra.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
            pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);	//таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
		break;
		
		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = "Nos... És mi lesz a gyôzelmed jutalmával?";
				link.l1 = "Van " + sTemp + " rabszolgám.";
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = "Nocsak, nocsak. Elfelejtetted, amit mondtam? Nem kevesebb, mint ötezer rabszolgát kellett volna idehoznod, és neked van " + sTemp + ". Miért van ez?";
				link.l1 = "Hmm... Egy részük nem élte túl az utat Havannából... az élelem és a gyógyszerek fogytán voltak.";
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = "Nos, nos... Meg akarsz csalni? Elfelejtetted, amit mondtam? Hol vannak a rabszolgáim, kérdem én! Hol vannak?!";
			link.l1 = "Hm... Nos, tudod...";
			link.l1.go = "Havana_Fort_no";
		break;
		
		case "Havana_Fort_no":
			dialog.text = "Jól van. Nincs szükségem a magyarázatodra. Megegyeztünk, és egy hetet adok neked, hogy legalább ötezer rabszolgát szerezz. Máskülönben sok problémád lesz.";
			link.l1 = "Rendben, rendben, csak nyugi, megszerzem ôket neked.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			if(bImCasual)
			{
				NewGameTip("Felfedezô mód: a küldetés idôtartama megduplázódott");
				SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 14, false);
			} 
			else SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;
		
		case "Havana_Fort_yes":
			dialog.text = "Pompás! Elvégezted a feladatomat, mint mindig. Nagyon elégedett vagyok veled.";
			link.l1 = "Én is... De még jobban örülnék, ha megkapnám a pénzt a rakományért.";
			link.l1.go = "Havana_Fort_yes_1";
		break;
		
		case "Havana_Fort_yesA":
		dialog.text = "Nagyon örülök neki. Késtél, de a feladatomat a legkiválóbban teljesítetted.";
			link.l1 = "És most szeretném megkapni a pénzt a rakományért.";
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;
		
		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp)*200;
			dialog.text = "Persze. Eladom a rabszolgákat az ügyfelemnek, ô fizet, te pedig megkapod az érméket. Mint legutóbb. Lássuk csak, ide hoztál " + sTemp + " rabszolgákat. Az összeg " + FindRussianMoneyString(iSlaveMoney) + ". Egy hét múlva gyere ide a fizetségért.";
			link.l1 = "Rendben, " + npchar.name + ", megegyeztünk. Egy hét múlva itt leszek. De légy nagyon óvatos...";
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;
		
		case "Havana_Fort_yes_2":
			dialog.text = "" + pchar.name + ", Kérem, ne tegye. Társak vagyunk, és nincs helye megcsalásnak és bizalmatlanságnak köztünk. Sok érmét ígértem neked, és te megkaptad. Ígértem neked érdekes feladatokat, és te is megkaptad. Mindig kompenzáltam a költségeidet még a legsötétebb napokban is az üzletem számára. Soha nem tartottam be a szavamat?";
			link.l1 = "Hmm... Nem... csak fizetést akarok, ennyi az egész.";
			link.l1.go = "Havana_Fort_yes_3";
		break;
		
		case "Havana_Fort_yes_3":
			dialog.text = "Nézd meg most..." + pchar.name + ", Ön a legjobb ügynököm, és számítok rá, hogy a jövôben is üzletet kötök Önnel. ";
			link.l1 = "Fine, " + npchar.name + ". De meg kell értened engem is - egymillió pezó hatalmas összeg.";
			link.l1.go = "Havana_Fort_yes_4";
		break;
		
		case "Havana_Fort_yes_4":
			dialog.text = "Nagyon jól megértelek, de elôször el kell adnom a rabszolgákat, és csak utána kapok pénzt.";
			link.l1 = "Rendben. Azt hiszem, megértettük egymást.";
			link.l1.go = "Havana_Fort_yes_5";
		break;
		
		case "Havana_Fort_yes_5":
			dialog.text = "Nagyszerû. Egy hét múlva találkozunk. És most fel kell készülnöm és indulnom kell, hogy kereskedjek az ügyfelemmel.";
			link.l1 = "Akkor nem foglak zavarni. Találkozunk egy hét múlva, " + npchar.name + ".";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city +"_town";
			LocatorReloadEnterDisable(npchar.city +"_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
		break;

		case "Usurer_Escape":
			dialog.text = "Mit keresek én itt? Nos... ez az én bankom. Két napja vettem. Maga az elsô ügyfelem, és nagyon csábító hitelfeltételeket tudok ajánlani...";
			link.l1 = "Baszd meg a kreditpontokat! Hol van a " + pchar.questTemp.Slavetrader.Name + "?";
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = "Nyugodjon meg, kérem! Már régen elszökött.";
			link.l1 = "Hogyan?";
			link.l1.go = "Usurer_Escape_2";
		break;
		
		case "Usurer_Escape_2":
			dialog.text = "Nem tudod? Egy hete tûnt el. Kiderült, hogy elvitte az ügyfelei összes befektetését. Azt mondják, hogy még a kormányzó is szenvedett. Ez a ház megmaradt, és én vettem meg a teleprôl.";
			link.l1 = "Eltûnt? Hogyan?";
			link.l1.go = "Usurer_Escape_3";
		break;
		
		case "Usurer_Escape_3":
			dialog.text = "Úgy hallottam, hogy elszökött a teleprôl... Gondolom, ô is tartozik neked. Sokkal?";
			link.l1 = "Több mint egy millióval! De akkor is elkapom ezt a patkányt! Hová tûnt? A hajója neve?";
			link.l1.go = "Usurer_Escape_4";
		break;
		
		case "Usurer_Escape_4":
			dialog.text = "Senki sem tud róla. Komolyan. Csak úgy eltûnt. A 'Mauritius' vagy 'Maurdius' nevû hajó aznap elhajózott, talán azt használta fel a menekülésre.";
			link.l1 = "Bassza meg! És én bíztam abban a szemétládában! Már az elsô nap áruló szaga volt! És én voltam olyan ostoba, hogy elhittem, hogy igazi társak vagyunk! De egy nap majd megbánja... Rendben," + npchar.name + ", bocsánatot kérek a viselkedésemért... Ha jó ember vagy, a jövôben foglalkozni fogok veled, légy biztos benne, de egyelôre búcsúzom.";
			link.l1.go = "Usurer_Escape_5";
		break;
		
		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = "Rendben van. Megértem. Ha pénzre van szüksége, vagy befektetni akar, mindig állok rendelkezésére.";
			link.l1 = "Köszönöm. De jobb, ha a pénzemet megtartom magamnak. Viszlát.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			pchar.questTemp.SanBoxTarget.Slavetrader = true;
			ChangeCharacterComplexReputation(pchar, "fame", 25);
			LAi_LocationDisableOfficersGen(&Locations[FindLocation(pchar.location)], false); // разблокируем вход офицеров 2015
		break;
	//<--работорговец	

	//--> семейная реликвия
		case "Noblelombard":
			dialog.text = "Tényleg? Úgy tûnik, hogy nem akar velem egyedül beszélni..... Rendben, beszéljük meg veled a dolgot. "+pchar.GenQuest.Noblelombard.Name+" tartozik nekem "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+": "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Money))+" és a kamatomat is - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent))+" három hónapig. Ha nem látok pénzt a közeli napon belül, akkor eladom az ereklyéjét, és nem érdekel az értéke neki. Az üzlet az üzlet.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = "Pompás! Ebben az esetben azonnal kifizetem a teljes összeget a kamatokkal együtt - "+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Summ))+". Az ereklyéjét maga viszi el. Itt van a pénze.";
				link.l1.go = "Noblelombard_1";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent)*2)
			{
				link.l2 = "Az ügyfelem három hónapon belül megkapja a pénzt. Egyezzünk meg, kifizetem az elmúlt három hónap és a következô három hónap kamatát."+FindRussianMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)*2)+". Magát az adósságot pedig késôbb fizetjük ki.";
				link.l2.go = "Noblelombard_2";
			}
			if(sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = "Az ügyfelemnek három hónap múlva lesz pénze. Mi lenne, ha kifizetném a kamatot az elmúlt három hónapra, és te megvárod, amíg az ügyfelemnek lesz elég pénze?";
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = "Ez a ritkaság egy vagyonba kerül! Úgy néz ki, hogy az ügyfelemnek magának kell kifizetnie.";
			link.l4.go = "Noblelombard_4";
			pchar.quest.noblelombard = "true";//лесник с нпчара на пчара
		break;
		
		case "Noblelombard_1":
			dialog.text = "Kiváló! Minden jól alakult, megkaptam a pénzem, és "+pchar.GenQuest.Noblelombard.Name+" visszakapja az ereklyéjét.";
			link.l1 = "Örülök, hogy üzletet kötöttünk, "+npchar.name+"! Viszontlátásra.";
			link.l1.go = "exit";
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ)*2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
	
		break;
		
		case "Noblelombard_2":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = "Hm... Rendben. Ez nekem megfelel. De ha a "+pchar.GenQuest.Noblelombard.Name+" nem talál pénzt három hónapon belül, akkor nem fogok megint késlekedni. Gyôzôdj meg róla, hogy ezt ô is tudja.";
				link.l1 = "Tudni fogom! Örülök, hogy megegyeztünk. Viszontlátásra.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent)*2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
			
			}
			else
			{
				dialog.text = "Nem. Nem fog mûködni. Szükségem van a teljes összegre, még napnyugta elôtt. Gyôzôdjön meg róla, hogy a 'client' tudja ezt. Nincs több mondanivalóm.";
				link.l1 = "Hm... rendben. Kár, hogy nem akar kompromisszumot kötni.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			
			}
		break;
		
		case "Noblelombard_3":
			if(sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = "Hm... Rendben. Csak azért fogadom el, mert tisztelem az ügyfelét. De ha a "+pchar.GenQuest.Noblelombard.Name+" nem talál pénzt három hónapon belül, akkor nem fogok újra késlekedni. Gyôzôdjön meg róla, hogy ezt ô is tudja.";
				link.l1 = "Úgy lesz! Örülök, hogy megegyeztünk. Viszontlátásra.";
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent)*2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = "Nem. Nem fog mûködni. Szükségem van a teljes összegre, még napnyugta elôtt. Gyôzôdjön meg róla, hogy a 'client' tudja ezt. Nincs több mondanivalóm.";
				link.l1 = "Hm... rendben. Kár, hogy nem akar kompromisszumot kötni.";
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);
	
			}
		break;
		
		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;
		
		case "Noblelombard_5":
			if(sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = "Nem mondod! "+pchar.GenQuest.Noblelombard.Name+" nem nyitott betétet a nevedre. Nincs is a mi telepünkön - elhajózott Európába. Én mondom, hogy még soha nem láttam ilyen becstelen embert. Meg akart csalni, de nem sikerült neki - nekem is vannak saját trükkjeim...";
				link.l1 = "Szemétláda! Nekem adta a szavát....";
				link.l1.go = "Noblelombard_6";
			}
			else
			{	// Addon-2016 Jason уменьшаем раздачу дублонов
				dialog.text = "Helyes. A "+pchar.GenQuest.Noblelombard.Name+" befizetést tett az Ön nevére. Kérem, vegye el...";
				link.l1 = "Pompás! Viszlát, "+npchar.name+".";
				link.l1.go = "Noblelombard_9";
			}
		break;
		
		case "Noblelombard_6":
			dialog.text = "Az olyan emberek számára, mint a "+pchar.GenQuest.Noblelombard.Name+" , nincs ilyen, mert nincs becsületük és lelkiismeretük. Gondolom, hogy megcsalt téged?";
			link.l1 = "Gondolom, igen. Mindegy, "+npchar.name+", én sem maradok itt sokáig, és Európa kicsi... Talán egyszer még találkozunk. Viszontlátásra!";
			link.l1.go = "Noblelombard_7";
		break;
		
		case "Noblelombard_7":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_bad");
		break;
		
		case "Noblelombard_9":
			DialogExit();
			AddDialogExitQuestFunction("Noblelombard_Usurer_good");
		break;
//<-- семейная реликвия

		// Бремя гасконца
		case "sharlie_credit":
			dialog.text = "Monsieur, nem ismerem magát. Én csak a helyi polgároknak vagy a kapitányoknak adok kölcsön pénzt. Bocsásson meg...";
			link.l1 = "Értem, értem. Kár.";
			link.l1.go = "exit";
		break;
		// Бремя гасконца
		
		// Addon-2016 Jason, французские миниквесты (ФМК)
		// ФМК-Гваделупа
		case "FMQG_x":
			DelLandQuestMark(npchar);
			dialog.text = "Mi-mi... Hogy érti ezt?";
			link.l1 = "Egy kibaszott patkány vagy! Most pedig figyelj rám nagyon figyelmesen: Nem vagyok olyan hülye. Pinette két példányban írta a levelet. Az egyiket neked adtam, a másik a megbízható ügynökömnél van. Ha bármi történne velem - az emberem egyenesen a kormányzó kezébe fogja eljuttatni...";
			link.l1.go = "FMQG_x1";
		break;
		
		case "FMQG_x1":
			dialog.text = "";
			link.l1 = "Szóval azt javaslom, hogy imádkozzanak a templomban minden reggeli prédikáción a jó egészségemért, ahelyett, hogy bérgyilkosokat küldenek az életemre. Egy utolsó figyelmeztetés! Ha megmozdulsz ellenem, neked annyi. Megértetted? Megértetted? Vegyél egy mély lélegzetet és számold tovább a dublónjaidat.";
			link.l1.go = "FMQG_x2";
		break;
		
		case "FMQG_x2":
			DialogExit();
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "27");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		// Другое
		case "NeHochuRazgovarivat":
			dialog.text = "Nem akarok beszélni veled.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		// Леди Бет -->
		case "LadyBeth_Usurer_1":
			dialog.text = "Persze, hogy tudja! Sokan csak a pénzüket akarják és elmennek. Különösen a legutóbbi pletykákat figyelembe véve...";
			link.l1 = "Milyen pletykák?";
			link.l1.go = "LadyBeth_Usurer_2";
		break;
		
		case "LadyBeth_Usurer_2":
			dialog.text = "Azt mondják, a legénységben egyre rosszabbak a körülmények. Monsieur Blackwood még rendszeres veszteségeket is kezdett elviselni - ami korábban soha nem fordult elô. De ez nem az én dolgom. Én csak árut árulok. Akkor mi érdekli magát?";
			link.l1 = "Térjünk a tárgyra.";
			link.l1.go = "next";
			npchar.quest.item_date = "LadyBeth";
			pchar.questTemp.LadyBeth_Usurer = true;
		break;
		// Леди Бет <--
	}	
}

// ugeen проверка, можем ли мы использовать дублоны в качестве вклада
bool CheckUseDublons(ref NPChar)
{
	int iTest 	= FindColony(NPChar.City); // город банка
	if(iTest == -1) return false;
	
	ref rColony = GetColonyByIndex(iTest);
	 	 
	bool bOk1 = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea); 
	bool bOk2 = (GetCharacterItem(pchar,"gold_dublon") > 10) || (CheckItemMyCabin("gold_dublon") > 10);
	
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk1 && bOk2) return true;

	return false;
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "", "man", "man", 45, SPAIN, 20, true, "quest"));
	FantomMakeCoolSailor(sld, SHIP_LINESHIP, sName, CANNON_TYPE_CANNON_LBS42, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade_21", "pistol5", "bullet", 100);
	sld.Ship.Mode = "war";	
	SetCaptanModelByEncType(sld, "war");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;
	sld.DontRansackCaptain = true;
	sld.WatchFort = true;
	sld.AlwaysEnemy = true;


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придёт
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	//Log_TestInfo("Captain of the galleon sailed away from " + sld.city + "and heading to " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = "Galleon '" + sName + " '";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
}
