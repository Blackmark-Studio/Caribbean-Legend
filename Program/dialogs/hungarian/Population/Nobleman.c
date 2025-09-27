//Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	iTest = FindColony(NPChar.City); // 170712
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> проверка межнациональных отношений
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
				dialog.text = NPCStringReactionRepeat("Hm. A "+NationNameGenitive(sti(pchar.nation))+"zászlaja alatt hajózol, pajtás. Mi a fenét keresel itt, a mi városunkban? Tûnjetek el!", 
					"Nem akarom, hogy a "+NationNameAblative(sti(pchar.nation))+"barátjaként gyanúsítsanak ! Tûnj el, vagy jelentem az ôrségnek!", 
					"Ez az utolsó esélyed, hogy elmenekülj. Különben csak magadat hibáztathatod.",
					"Figyelmeztettelek. Most megfizetsz a szemtelenségedért, te szemétláda!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Micsoda hazafi, ha!", 
					"Rendben, rendben, nyugodj meg. Elmegyek.",
					"Ne csapjatok akkora zajt. Elmegyek.", 
					"Mi?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation.nobility) < 10)
			{
				dialog.text = NPCStringReactionRepeat("Ezt nézd meg! És hogy engedhetik az ôreink, hogy egy ilyen fattyú, mint te, csak úgy sétálgasson a városban? Ez lehetetlen...", 
					"Tûnj el, nem is akarok veled beszélni! Hóhér...", 
					"Ez az utolsó esélyed, hogy elmenekülj. Különben csak magadat hibáztathatod.",
					"Figyelmeztettelek. Most megfizetsz a szemtelenségedért, te szemétláda!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Hé, hé, hé! Mutasson több tiszteletet, uram!", 
					"Nézz magadra, szent...",
					"Nyugodj meg...", 
					"Mi?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
			}
			
			//--> диалог первой встречи
            if(NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//дворянин-пассажир
				{
					dialog.text = "Üdvözlet, "+GetAddress_Form(NPChar)+". Látom, hogy Ön egy szilárd hajó kapitánya. Szeretnélek megkérni valamire. Elfogadhatod vagy elhagyhatod.";
					link.l1 = "Figyelek, "+GetAddress_FormToNPC(NPChar)+". Hogy érted ezt?";
					link.l1.go = "passenger";
					link.l2 = "Elnézést, "+GetAddress_FormToNPC(NPChar)+", de sietek.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
				{
					dialog.text = "Üdvözlet, "+GetAddress_Form(NPChar)+". Látom, hogy Ön egy szilárd hajó kapitánya. Szeretnélek megkérni valamire. Elfogadhatod vagy elhagyhatod.";
					link.l1 = "Figyelek, "+GetAddress_FormToNPC(NPChar)+". Hogy érted ezt?";
					link.l1.go = "passenger";
					link.l2 = "Elnézést, "+GetAddress_FormToNPC(NPChar)+", de sietek.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation"))//клянчит деньги
				{
					dialog.text = "Aha, jó látni egy úriembert a mi kis városunkban! Biztos vagyok benne, hogy éppen Európából jöttél. Figyeljen, szeretném megkérni, hogy segítsen nekem - úriember az úriembernek. Remélem, hogy jól fog érteni engem.";
					link.l1 = "Jó napot, uram. Hallgatom.";
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//семейная реликвия
				{
					dialog.text = "Jó napot, "+GetAddress_Form(NPChar)+"! Jó találkozni egy úriemberrel városunk utcáin! Megengedi, hogy elraboljak néhány percet Öntôl?";
					link.l1 = "Persze, uram. Hallgatom.";
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//привезти рабов
				{
					dialog.text = "Jó napot, kapitány úr! Örülök, hogy látom, mert olyan embernek tûnik, aki képes megoldani a problémákat.";
					link.l1 = "A problémától függ. Én arra specializálódtam, hogy erôszakkal oldjam meg ôket, ezt keresed, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = RandPhraseSimple("Hello, "+GetAddress_Form(NPChar)+". Akarsz tôlem valamit?", "Mit akar, uram?");
				link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Nem fogom sokáig rabolni az idejét, csak azt szeretném kérdezni...";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Információra van szükségem a kolóniáról.", "Információra van szükségem.");
				link.l2.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
				
				//==> прибыла инспекция на Святом Милосердии
				if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
				{
					dialog.Text = LinkRandPhrase(LinkRandPhrase("Az egész város izgatott - don Fernando de Alamida, a királyi felügyelô megérkezett. Tudja, sok mindent láttam már itt, de ez... Nem a gyász változtatja meg az embert, hanem az, ahogyan kezeli. Azt mondják, más ember lett az apja halála után. Most már nem találsz megvesztegethetetlenebb és... kíméletlenebb szolgáját a Koronának az egész szigetvilágban.", "Nézd csak meg a 'Holy Mercy'! Azt mondják, maga a király rendelte meg, hogy különleges tervek alapján épüljön. És vegyük észre - egyetlen karcolás sincs rajta. Mintha maga Szûz Mária védelmezné. Bár hallottam pletykákat... talán nem is a Szûzanya.", "Tudod, hányszor próbálták már megölni don Fernandót? Tizenkét támadás nyílt vízen - és ez csak az elmúlt évben! Nos, egy ilyen hûséges és képzett legénységgel, és az Úr oltalma alatt - túl fogja élni a tizenharmadikat is!"), LinkRandPhrase("Hallottad? Don Fernando de Alamida megérkezett városunkba, és azt mondják, most is valahol az utcán van. Szeretném a saját szememmel látni ôt...", "Bonyolult ember ez a don Fernando. Egyesek szerint ô a megmentô, aki megtisztítja a hazát a mocsoktól. Mások azt suttogják, hogy valami megtört benne az apja halála után, és hamarosan mindannyian sírni fogunk. De én azt mondom nektek: ne féljetek tôle. Féljetek azoktól, akik azzá tették, ami.", "Milyen jóképû ember ez a don Fernando! De tudod mi a furcsa? Olyan, mintha senkit sem venne észre. Csupa kötelesség és szolgálat. Hallottam, hogy volt egy lány... de miután találkozott valami pappal, teljesen elutasította a világi örömöket. Mintha fogadalmat tett volna."), RandPhraseSimple(RandPhraseSimple("Átkozott felügyelô! Amíg ô itt van - a város olyan, mintha halott lenne. Se kereskedelem, se szórakozás. Még a légzés is, úgy tûnik, csendesebbnek kell lennie. És tudod, mi a legijesztôbb? Minden kikötôben ugyanez a helyzet. Mint az óramû. Ô királyi felsége nem találhatta ki szándékosan ezt a kínzást mindannyiunk számára!", "Don Fernando ismét meglátogatta az árvaházat. Nagylelkûen adakozik, órákig imádkozik. Egy ilyen méltó embert példaként kellene állítani az átkozott sikkasztók elé!"), RandPhraseSimple("Ha! 'Szent' Fernando ismét bezáratta az összes bordélyházat. Sebaj, nemsokára elhajózik, és újra kinyitnak.", "Megérkezett az insp... felügyelô, ez az! Don Fernando de Almeyda, vagy hogy is hívják, Alamida! Annyira fontos, hogy maga a kormányzó is lábujjhegyen járkál körülötte. Azt mondják, belenéz a szemedbe, és rögtön meglátja minden bûnödet. Félelmetes!")));
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== прибыла инспекция на Святом Милосердии
				//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat("Mi az? Már megint? Nincs idôm rád. Keress valaki mást, akivel beszélhetsz. Sok közember járkál az utcákon. Nekem pedig mennem kell, ma este bankett lesz a kormányzó rezidenciáján, és elô kell készítenem a ruhámat...", 
					"Nem, most már tényleg idegesítô! Hát nem érted? Vagy lassú az agyad?", 
					"Uram, kezdem azt gyanítani, hogy ön nem csak egy idióta, hanem egy paraszt és egy tahó. Figyelmeztetem, hagyjon békén, különben megbánja, hogy zaklat engem.",
					"Elég. Majd én megtanítalak, te szemtelen fickó!", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Értem. Viszontlátásra.", 
					"Igen-igen, csak elfelejtettem, mit akartam kérdezni...",
					"Rosszul értettél meg...", 
					"Mi?!", npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = LinkRandPhrase("Folytasd.","Mit akarsz?","Kérdések? Rendben, tengerész, hallgatlak.");
			link.l1 = LinkRandPhrase("Nem akarod elmondani a legújabb pletykákat a városodban?","Történt itt valami érdekes mostanában?","Van valami hír a Karib-tengerrôl, uram?");
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				dialog.text = ""+GetSexPhrase("Uram","Asszonyom")+", el kell jutnom a kolóniára" + XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+", amilyen hamar csak lehet ez a "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+", a "+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+". A hajód masszívnak és gyorsnak tûnik az itt hajózó kis kádárok többségéhez képest. Tudok fizetni neked "+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+". Mit szólna hozzá?"; // belamour gen
			}
			else
			{
				dialog.text = "Jó napot, "+GetSexPhrase("uram","asszonyom")+"! El kell jutnom a " + XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"! Az egyébként a "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+"oldalon van. Igen, igen, tudom - azok a szemetek csak arra várnak, hogy ott felbukkanjunk. De nekem ott van egy nagyon sürgôs és fontos találkozóm! Nem vagyok fukar ember - bár nem szeretek fizetni, mindig fizetek. Hagyjatok abba mindent, amit csináltok, és amint megérkezünk, adok nektek " + FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)) + ".";
			}
			link.l1 = "Hm. Én is erre tartok, úgyhogy kész vagyok ilyen feltételekkel a fedélzetre venni.";
			link.l1.go = "passenger_1";
			link.l2 = "Sajnálom, "+GetAddress_FormToNPC(NPChar)+", de én más irányba hajózom. Nem tudok segíteni.";
			link.l2.go = "passenger_exit";
		break;
		
		case "passenger_exit":
			dialog.text = "Kár érte. Nos, akkor várok egy másik hajóra. Viszontlátásra.";
			link.l1 = "Viszlát.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Nagyszerû! Belefáradtam a várakozásba. Megkapja a fizetését, ha odaértünk.";
			link.l1 = "Menj a hajómra, "+GetAddress_FormToNPC(NPChar)+". Hamarosan indulunk.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo."+sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle+sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo,   pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo."+sTitle);

				Trace("Duplicate Citizpassenger record "+sTitle+" copied to "+sTitle1+" **");
			}
// <--

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "nobleman");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", at " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Itt vagyunk, kiválóan! Az utazás a hajóján nagyon kielégítô volt. Fegyelmezett a legénysége és tiszta a fedélzete! Köszönöm. Vigye a pénzét, uram.";
			link.l1 = "Sok sikert, "+GetAddress_FormToNPC(NPChar)+"! Búcsúzás.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			OfficersReaction("good");				
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
//<-- дворянин-пассажир

//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = "Van egy elég kényes üzletem..."+sTemp+" Pénzre van szükségem, különben nagy bajban vagyok. Normális esetben soha nem kérnék pénzt egy másik úriembertôl, de a helyzet nagyon rossz.";
			link.l1 = "Mennyi pénzre van szüksége?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			iTemp = hrand(4)+1;
			pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
			dialog.text = "Az összeg elég kicsi, ez "+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+". Szóval mi van, tudtok segíteni?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = "Igen, persze. Fogja.";
				link.l1.go = "donation_2";
			}
			link.l2 = "Szívesen segítek, de az én zsebem is üres - egyetlen pezó sem maradt.";
			link.l2.go = "donation_exit";
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeOfficersLoyality("bad_all", 1);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		
		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = "Hálás köszönetem, "+GetAddress_Form(NPChar)+"! Megmentettél engem! Vannak barátaim a kormányzói rezidencián, és el fogom nekik mondani az önök nagylelkûségét. Ezer köszönet még egyszer!";
			link.l1 = "Szívesen, uram. Biztos vagyok benne, hogy ön is ugyanezt tenné velem.";
			link.l1.go = "donation_3";
		break;
		
		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2)+1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
//<-- помощь деньгами

//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			dialog.text = "Szükségem van a segítségedre. Ön gazdag és úriember, ezért remélem, hogy megérti. Nemrég nagy pénzszükségletem volt, ezért el kellett mennem a bankárhoz és zálogba "+pchar.GenQuest.Noblelombard.Item+"\njó feltételeket ajánlott. Tíz százalékot minden hónapra, összesen három hónapra. De az idô letelt, és a szerencsétlen események szerencsétlen alakulása miatt nem rendelkezem pénzzel, hogy kiváltsam a tárgyat\nMost azt mondja, hogy talált egy vevôt a "+pchar.GenQuest.Noblelombard.Item+" és eladja, ha nem fizetem vissza azonnal a tartozásomat és a százalékokat. De most nincs sok pénzem, és a tárgy, amit zálogba adtam, nagyon drága...";
			link.l1 = "És ebben miben segíthetek, "+GetAddress_FormToNPC(NPChar)+"?";
			link.l1.go = "lombard_1";
		break;
		
		case "lombard_1":
			dialog.text = "Arra kérlek, hogy beszélj a bankárunkkal. Ajánljon neki pénzt, kezeskedjen értem... vagy tegyen valami mást. Sajnos, nincs kitôl kérnem, minden jó barátom hirtelen 'csôdbe ment'. három hónap múlva "+pchar.GenQuest.Noblelombard.Text+", és én minden költségét visszafizetem, duplán! A szavamat adom, mint úriember!";
			link.l1 = "Rendben, megpróbálok segíteni neked ebben az esetben.";
			link.l1.go = "lombard_2";
			link.l2 = "Sajnos, én most 'csôdbe' túlságosan is csôdben vagyok. Szóval nem tudok segíteni, nagyon sajnálom!";
			link.l2.go = "lombard_exit";
		break;
		
		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_2":
			dialog.text = "Köszönöm a megértését. Várni fogom a kocsmában. Jöjjön oda, amilyen hamar csak tud.";
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;
		
		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true"
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000+hrand(60)*500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = hrand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;
		
		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = "Mit is mondhatnánk, "+GetAddress_Form(NPChar)+"? Voltál már a bankban? Van jó vagy rossz hír?";
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = "Nekem van. Visszafizettem az összes adósságodat. Elmehetsz oda és visszaveheted az ereklyédet.";
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "Visszaszereztem. Visszafizettem az összes kamatot az elmúlt három hónapra, és a következô három hónapra is. Nyugodtan várhatsz a pénzedre. Csak ne felejtsd el visszafizetni a fô adósságodat három hónap múlva.";
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "Igen, megtettem. Az elmúlt három hónap összes kamatát visszafizettem. A bankár beleegyezett, hogy még három hónapot várjon, amíg megkapja a teljes összeget.";
				link.l1.go = "lombard_5";
			break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = "Mit is mondhatnánk, "+GetAddress_Form(NPChar)+"? Voltál már bankban? Van jó vagy rossz hír?";
				link.l1 = "Igen, voltam. Ez a fösvény hihetetlen összeget kért. Visszautasított minden engedményt, és nincs nálam a kért összeg. Így nem tudtam segíteni. Sajnálom.";
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = "Mit is mondhatnánk, "+GetAddress_Form(NPChar)+"? Voltál már bankban? Van jó vagy rossz hír?";
				link.l1 = "Rajta vagyok. Várjon, várjon.";
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;
		
		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = "Meh, "+GetAddress_Form(NPChar)+"... Most már te is tanúja vagy ezeknek az átkozott vérszomjas uzsorásoknak a féktelen kapzsiságának. Istenemre uram, a zsidókat is megszégyenítik! Emlékezz erre, amikor megpróbálsz tôlük kölcsönt felvenni, mint én tettem. Köszönöm, hogy legalább megpróbálta...";
			link.l1 = "Soha nem szerettem ôket. Ki szereti az uzsorásokat? Sajnálom, "+GetAddress_FormToNPC(NPChar)+". Búcsúzom.";
			link.l1.go = "lombard_fail_1";
		break;
		
		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
			DeleteAttribute(sld, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;
		
		case "lombard_5":
			dialog.text = "Hihetetlen! Megmentettél, "+GetAddress_Form(NPChar)+"! Soha nem fogom elfelejteni. Biztosíthatlak, hogy minden költséged kétszeresen megtérül. Jöjjön el három hónap múlva a bankárunkhoz. Nyitok egy betétet az ön nevére.";
			link.l1 = "Rendben, azt teszem, amit mond. Viszlát!";
			link.l1.go = "lombard_6";
		break;
		
		case "lombard_6":
			dialog.text = "Még egyszer köszönöm, kapitány. Sok szerencsét!";
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;
		
		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeOfficersLoyality("good_all", 1);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
		break;
//<-- семейная реликвия

//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3+hrand(1);//цена на рабов в дублонах
			npchar.quest.slaves.qty = 50+hrand(5)*10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
			dialog.text = "Van egy "+LinkRandPhrase("gyáram","bányám","ültetvényem")+" és mindig szükségem van friss rabszolgákra. Az éghajlat nagyon megviseli ôket. Jelenleg szükségem van "+sti(npchar.quest.slaves.qty)+" fejekre. Hajlandó vagyok rendelni belôlük egy adagot. Fejenként aranyat fizetek, "+sti(npchar.quest.slaves.price)+" dublont\nNem kell sietni, nem korlátozlak idôben, ha megkapod, amire szükségem van. Persze az ésszerûség határain belül, fél évnél tovább ne húzd el. Szóval mit szólsz hozzá? Áll az alku?";
			link.l1 = "Megegyeztünk! A rabszolgamunka mocskos dolog, de megéri a kockázatot.";
			link.l1.go = "slaves_1";
			link.l2 = "Elnézést, de én nem vagyok rabszolga. Nem az én szakmám.";
			link.l2.go = "exit_slaves";
		break;
		
		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "slaves_1":
			dialog.text = "Rendben van. Várni foglak, amikor elhozod a rakományt. A templomban találsz meg minden nap délelôtt 11-tôl délután 1-ig. A nap többi részében elfoglalt vagyok, vagy dolgozom.";
			link.l1 = "Jól van. Ezt megjegyzem. Viszlát, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			DialogExit();
			sGlobalTemp = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city+"Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;
		
		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = "Elhozta a "+sti(npchar.quest.slaves.qty)+" rabszolgákat, ahogy kértem, kapitány?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = "Igen. Az egész rakomány a raktérben van. Készen állok, hogy átadjam ôket neked.";
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = "Nem, rajta vagyok.";
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = "Kapitány, ha a rabszolgák miatt van itt... Már eleget vettem, és most nincs szükségem többre. Túl sokáig tartott, sajnálom.";
				link.l1 = "Milyen kár! De igazad van, nem voltam elég gyors. Viszontlátásra!";
				link.l1.go = "slaves_8";
			}
		break;
		
		case "slaves_4":
			dialog.text = "Remek. Azonnal küldök értük egy hosszúhajót.";
			link.l1 = "Mi lesz a fizetségemmel?";
			link.l1.go = "slaves_5";
		break;
		
		case "slaves_5":
			dialog.text = "Ne aggódj, emlékszem rá. Tessék, itt van az összeg, "+sti(npchar.quest.slaves.price)+" dubloon fejenként. Jó üzlet mindkettônknek, ugye?";
			link.l1 = "Köszönöm, uram. Örülök, hogy üzletet kötöttünk.";
			link.l1.go = "slaves_6";
		break;
		
		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
			Log_Info("Megkaptad "+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
			PlaySound("interface\important_item.wav");
			dialog.text = "Mondhatni... Elnézést, most mennem kell. Viszlát!";
			link.l1 = "Sok szerencsét, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "slaves_7";
		break;
		
		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
         	ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city+"Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
		break;
//<-- привезти рабов под заказ

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, mint a város polgára arra kérem, hogy tegye hüvelybe a pengéjét.", "Figyelj, mint e város polgára arra kérlek, hogy tedd hüvelybe a pengédet.");
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod.", "Rendben.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "Tegnap elvesztettem az összes pénzemet a szerencsejátékban, és nincs elég pénzem, hogy eltöröljem az adósságot. Tudsz segíteni?" break;
		case 1: sText = "Tegnap jól éreztem magam egy... bizonyos hölgy társaságában, és most megpróbál megzsarolni. Elôször ki kell fizetnem ôt, aztán majd én foglalkozom vele... Tudna nekem segíteni egy kis pénzzel?" break;
		case 2: sText = "Nemrég átgázoltam egy helyi bolondon a pengémmel, és most a parancsnok kenôpénzt követel, hogy elhallgattassa az esetet. Most már kevés a pénzem. Tudnál segíteni?" break;
		case 3: sText = "Volt szerencsétlenségem, hogy elvesztettem egy fogadást, és nincs egy csekély összegem, hogy visszafizessem a becsületbeli adósságomat. Segítene nekem?" break;
		case 4: sText = "Valami szemétláda tud az én... indiszkrét tevékenységemrôl egy férjes asszonnyal kapcsolatban. Nincs elég pénzem, hogy befogjam a száját. Csak néhány aranypénzre van szükségem... " break;
		case 5: sText = "Valami fattyú ellopott fontos iratokat a házamból, és jelentôs összeget követel a visszaszolgáltatásukért. Már majdnem megvan, már csak néhány érme hiányzik. Tudsz segíteni?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = "anyám gyémánt medálját egy madridi ékszerész készítette.";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("Meg fogom kapni az örökségemet","a hajóm visszatér Afrikából rabszolgákkal megrakodva.");
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = "a nôvérem smaragd nyaklánca, amit egy párizsi ékszerész készített.";
				pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("Egy európai megyét fogok örökölni","a hajóm fûszerekkel és selyemmel megrakodva tér vissza Indiából.");
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = "családi gyûrû a rokonságunk jelvényével";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("az expedícióm aranyrudakkal tér vissza a spanyol fôfolyóról","Megkapom az örökségemet.");
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = "egy rubin karkötôt a feleségemtôl, az anyjától kaptam ajándékba.";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("A befektetésemet a kamatokkal együtt egy európai banktól kapom meg","Az ültetvényem nyereségét kapom meg.");
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = "egy arany és gyémánt nyaklánc, darabos munka, a feleségem büszkesége.";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("A jelenlegi vállalkozásomból fogok profitálni","a hajóm vissza fog térni Afrikából, a rakteret fekete elefántcsonttal megtömve.");
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = "egy elefántcsont botot féldrágakövekkel, ajándék a nagyapámtól.";
			pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("a hajóm selyemmel és fûszerekkel megrakott rakterével érkezik vissza Indiából","Egy európai bankból kapom meg a kamatomat.");
		break;
	}
}
