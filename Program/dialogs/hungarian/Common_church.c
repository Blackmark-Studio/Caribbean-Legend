// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    
    string iDay, iMonth, lastspeak_date, eggStr;
    string sTemp, sTitle;

	iDay           = environment.date.day;
	iMonth         = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
    {
        npchar.quest.HealthMonth = "";
    }
	
    if (!CheckAttribute(npchar, "quest.BadMeeting"))
    {	
        npchar.quest.BadMeeting = "";
    }
    if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
    {
        npchar.quest.GhostShipMonth = "";
    }
    
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}
	
	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}
	
	if(!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
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
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("Fiam","lányom") +", sajnos nem tudok menedéket adni. Futás!", "A városôrség átfésüli a várost, téged keresve, "+ GetSexPhrase("fiam","lányom") +". Templomom ajtajai mindig nyitva állnak a szenvedôk elôtt, de én nem tudok neked menedéket adni...", ""+ GetSexPhrase("fiam","lányom") +", menekülnöd kell! Ne késlekedj, könyörgöm neked!"), 
					LinkRandPhrase("Mit keresel a templomban, bukott lélek? Követelem, hogy azonnal távozz, mielôtt a katonák itt találnak és mészárlást követnek el!", "Azonnal hagyd el a templomot, te gúnyolódó! Egy ilyen gazembert, mint te, soha nem fogok megvédeni!", "Azonnal hagyd el Urunk templomát! Nincs szükségünk itt gyilkosokra!"));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Ugyan már, atyám...", "Úgysem kell a segítséged..."), 
					LinkRandPhrase("Csak ne álljon az utamba, atyám...", "Elmegyek, ne aggódjon...", "Atyám, hagyja abba a felhajtást - tényleg nincs idôm rá."));
				link.l1.go = "fight";
				break;
			} 
            if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
				{
					dialog.text = "...örökké a tüzes pokolban fognak égni! Soha nem fogják látni...";
					link.l1 = RandPhraseSimple("Ahem! Zavarok, atyám?", "Ez a beszéd!");
					link.l1.go = "GenQuest_Church_2_Start_1";
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
				{
					Dialog.Text = ""+ GetSexPhrase("Fiam","lányom") +", örülök, hogy újra látlak!";
					link.l1 = "És örülök, hogy jó egészségben látlak, padre " + NPChar.name + "...";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
					break;
				}
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
				{
					Dialog.Text = ""+ GetSexPhrase("A fiam","A lányom") +"! Örülök, hogy újra jó egészségben és jókedvûen látlak. Az Úr biztosan megsegített bennünket a mi ügyünkben, nem igaz?";
					link.l1 = "Igen, " + RandPhraseSimple("padre", "szent atya") + ", bár nem mindig fújt a következô szél a vitorláimban, bár még több idôt, erôt és pénzt költöttem - a küldetésed teljesült.";
					link.l1.go = "GenQuest_Church_1_Complete_1";
					break;
				}
				Dialog.Text = "Üdvözöllek szent hajlékunkban, "+ GetSexPhrase("fiam","lányom") +".";
				link.l1 = "Helló, szent Atyám.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
				{
					dialog.text = "Üdvözletem, Ellen, gyermekem.";
					link.l1 = "És neked is, Atyám.";
				}
				link.l1.go = "node_3";
				Link.l2 = "Te nem vagy az apám, és soha többé ne szólíts így.";
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = "Távozz az Úr templomából, te káromló! Nincs mirôl beszélnünk!";
				Link.l1 = "Nem is akartam.";
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "node_2":
			dialog.text = "Ó, te istenkáromló! Menj innen! Ne merészeld bemocskolni Urunk templomát a jelenléteddel!";
			link.l1 = "Nem is akartam itt maradni.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "Örülök, hogy a Jannal való... foglalatosságaid ellenére sem feledkezel meg Urunkról és az Ô házáról. Miben segíthetek?";
			}
			else
			{
				dialog.text = "Áldjon meg az Úr téged és a dolgaidat... Valamilyen különleges okból jöttél hozzám?";
			}
    		link.l1 = RandPhraseSimple("Szeretnék adományozni.", "Szeretnék adományozni egy jó célra.");
    		link.l1.go = "donation";
    		link.l2 = RandPhraseSimple("Azt hiszem, itt az ideje egy vallomásnak.","Szeretnék gyónni, "+RandPhraseSimple("padre.", "szentatya."));
    		link.l2.go = "ispoved";
    		link.l3 = RandPhraseSimple("Üzleti ügyem van veled, " + RandPhraseSimple("padre.", "szentatya."),
                                           "Üzleti ügyben érkeztem, " + RandPhraseSimple("padre.", "szentatya."));
    		link.l3.go = "work";
			
			//--> Сага
			// Картахена, Чика Гонсалес
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
			{
				link.l4 = "Szeretnék egy imaórát rendelni egy hölgy lelkének békéjéért.";
				link.l4.go = "saga";				
			}
			// поиски исцеления от заклятий
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
			{ // все церкви, кроме Бриджтауна
				link.l4 = "Atyám, segítségre van szükségem. Nagyon beteg vagyok. Valami gonosz pogány átok sújtott le rám. Kérem, segítsen rajtam, könyörgöm!";
				link.l4.go = "seektreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
			{ // попал в Бриджтаун
				link.l4 = "Atyám, segítségre van szükségem. Nagyon beteg vagyok. Valami gonosz pogány átok sújtott le rám. Kérem, segítsen rajtam, könyörgöm!";
				link.l4.go = "findtreatment";
			}
			if(CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
			{ // пришёл в Бриджтаун по направлению
				link.l4 = "Atyám, segítségre van szükségem. Nagyon beteg vagyok. Valami gonosz pogány átok sújtott le rám. Azt mondták nekem, hogy te vagy az, aki segíthet rajtam. Könyörgöm...";
				link.l4.go = "findtreatment";
			}
			// исцеление от заклятий Джесс
			if(CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
			{
				link.l4 = "Atyám, segítségre van szükségem. Nagyon beteg vagyok. Valami gonosz pogány átok szállt rám. Hozzád küldött... Jessica Rose. Azt mondta, hogy te tudsz segíteni rajtam.";
				link.l4.go = "treatment";
			}
			if(CheckAttribute(npchar, "quest.candle"))
			{
				link.l4 = "A gyertyákról...";
				link.l4.go = "candle";
			}
			if(CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
			{
				link.l4 = "Készen állok imádkozni, atyám.";
				link.l4.go = "prayer";
			}
			//<-- Сага
			
			// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
			if(CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
				NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = "Szörnyû dolgok történnek, szent Atyám.";
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}
			
			link.l6 = "Elnézést, de mennem kell.";
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Ne aggódj, fiam. Az Úr látja, hogy szenvedsz, és segítô kezet nyújt neked. Mindig hordozz magadon keresztet, hogy megerôsödj a hitedben.";
			Link.l1 = "Köszönöm, szent Atyám.";
			Link.l1.go = "exit";
			AddItems(PChar, "amulet_3", 15);
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
		case "saga" :
			dialog.text = "1000 pezóért alázatosan teljesítem az akaratát.";
			Link.l1 = "Tessék, Atyám - kérlek, vedd el ezeket az érméket.";
			Link.l1.go = "saga_1";
		break;
		
		case "saga_1" :
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Köszönöm, fiam. Mi a neve annak a senorának, akinek a lelkéért imádkozzam?";
			Link.l1 = "A neve Chica Gonzales, és sok évvel ezelôtt elhagyta ezt a világot.";
			Link.l1.go = "saga_2";
		break;
		
		case "saga_2" :
			dialog.text = "Ez furcsa... Történt valami Alvarezzel, és ô kérdezett errôl?";
			Link.l1 = "És ki ez az Alvarez, és mi olyan furcsa a kérésemben?";
			Link.l1.go = "saga_3";
		break;
		
		case "saga_3" :
			dialog.text = "Hát, hogy is van ez? Alvarez, aki két évtizede ôrzi világítótornyunkat, minden hónapban imaszolgálatot rendel el a hölgy lelkének békéjéért. Rajta kívül még mindig senki sem törôdött Lady Gonzales-szel. És maga idejön. Így gondoltam. Ez azonban nem az én dolgom. Természetesen örömmel teljesítem alázatosan a kívánságait, hogy segítsek a kóbor léleknek nyugalmat találni és a paradicsomba vezetô utat.";
			Link.l1 = "Köszönöm, szent Atyám.";
			Link.l1.go = "saga_4";
		break;
		
		case "saga_4" :
			DialogExit();
			if(CheckAttribute(pchar,"questTemp.Saga7"))
			{
				AddQuestRecord("Saga", "151");
				DeleteAttribute(pchar,"questTemp.Saga7");
			}
			else AddQuestRecord("Saga", "15");
			Saga_SetOrtega();
			pchar.questTemp.Saga = "ortega";
			pchar.quest.Saga_Gonsales1.over = "yes"; //снять возможное прерывание
			if (GetCharacterIndex("SagaGonsalesB") != -1)
			{
				sld = characterFromId("SagaGonsalesB");
				sld.lifeday = 0;
			}
		break;
		
		// belamour участвовал в событиях Картахены
		case "saga_5" :
			dialog.text = "Van még valaki másnak a lelke, akinek szeretne halotti búcsút rendelni?";
			Link.l1 = "Mmm... Nem, nem hiszem. Valaki másnak kell rendelnem?";
			Link.l1.go = "saga_6";
		break;
		
		case "saga_6" :
			dialog.text = "Nos, talán annak a több száz ártatlan embernek, akik a te kezed vagy istentelen társaid pengéi által estek el, amikor kifosztottad ezt a szerencsétlen várost... Egy szerény pap azonban aligha remélheti, hogy elérheti egy olyan ember lelkiismeretét, aki bûntudat nélkül gyilkolt egyszerû, békés polgárokat...";
			Link.l1 = "Atyám, te nem érted... Ez már a múlté. Itt és most, nem áll szándékomban senkit sem bántani.";
			Link.l1.go = "saga_7";
		break;
		
		case "saga_7" :
			pchar.questTemp.saga7 = true;
			dialog.text = "Bízhatok a szavadban...? De mindenesetre, ez szent föld, amit nem szabadna vérbe borítani. Szóval, nem hívom az ôrséget. Menjetek békében. Talán mielôtt Isten ítélete elé kerülsz, lesz idôd legalább a bûneid egy részét jóvátenni.";
			Link.l1 = "Talán. Legyen meg Isten akarata.";
			Link.l1.go = "saga_4";
		break;
		// <-- Чика Гонсалес
		
		// --> исцеление от заклятий
		case "treatment":
			dialog.text = "Jessica? Emlékszem rá. Szegény bûnös. De nem halt meg?";
			link.l1 = "Meghalt, szent atyám. Most már halott, az Úr nyugtassa meg a lelkét. De biztosított arról, hogy ön képes lesz segíteni nekem.";
			link.l1.go = "treatment_1";
			DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;
		
		case "treatment_1":
			dialog.text = "Ki bûvölt el téged, fiam? Mondd meg ôszintén.";
			link.l1 = "Ô... igen, meghalt. Jessica.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Isten óvjon minket! Én is így gondoltam. A pogány szertartásokba való belemerülés még a legerôsebb lelkeket is a sötétség szakadékába taszíthatja... De... tényleg meghalt? Vagy... nem teljesen?";
			link.l1 = "Maga rendkívül éleslátó, atyám. Most már teljesen halott.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			dialog.text = "Ez a szegény bûnös többször is meggyónt nálam. A gyûlölet teljesen elpusztította belülrôl. Tudtam, hogy mire készül. Megpróbáltam megállítani, megpróbáltam rávenni, hogy az egyenes útra térjen, de minden erôfeszítésem hiábavaló volt. Figyelmeztettem ôt a szörnyû veszélyre és a szentségtelen tettek szörnyû következményeire...";
			link.l1 = "Igen, szent atyám. Amit láttam, valóban szörnyû volt. De... hogyan gyógyulhatok meg?";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Az ima erejével, fiam. A szent tisztító ima erejével a templomunkban. Nagyon sokáig kell imádkoznod, és nem csak magadért. Imádkoznod kell érte is.";
			link.l1 = "Jessicáért?";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Jessica-ért? - Igen. Magadért és a lelkéért. Gyere ide este tízre, hogy senki ne zavarjon. Egész éjjel imádkoznod kell. Hozz magaddal húsz vastag viaszgyertyát, gyújtsd meg ôket, és imádkozz, amíg mind el nem ég.";
			link.l1 = "És akkor meggyógyulok?";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Minden az Úr kezében van. Megtanítalak imádkozni, és itt hagyom neked a Szentírást. A szent ima ereje elpusztítja a rossz varázslatokat, amelyek rád estek, és megtisztítja szegény Jessica lelkét is.";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Van nálam húsz viaszgyertya. Készen állok arra, hogy a templomban maradjak, és elkezdjek imádkozni.";
				link.l1.go = "treatment_9";
			}
			else
			{
				link.l1 = "Még nincs nálam húsz gyertya. Majd én megszerzem ôket!";
				link.l1.go = "treatment_7";
			}
		break;
		
		case "treatment_7":
			dialog.text = "Rendben van, fiam. Várni fogok rád. Ne vesztegesd az idôt!";
			link.l1 = "Hamarosan itt leszek...";
			link.l1.go = "treatment_8";
		break;
		
		case "treatment_8":
			DialogExit();
			npchar.quest.candle = "true";
		break;
		
		case "candle":
			dialog.text = "Hoztál húsz gyertyát, fiam?";
			if (GetCharacterItem(pchar, "mineral3") >= 20)
			{
				link.l1 = "Igen, atyám. Van nálam húsz viaszgyertya. Készen állok arra, hogy a templomban maradjak és elkezdjek imádkozni.";
				link.l1.go = "treatment_9";
				DeleteAttribute(npchar, "quest.candle");
			}
			else
			{
				link.l1 = "Még nem - de mindenképpen megszerzem ôket.";
				link.l1.go = "exit";
			}
		break;
		
		case "treatment_9":
			dialog.text = "Nos, fiam. Add át ôket nekem, és gyere vissza holnap este tíz óra után. Megtanítalak a szükséges imákra, és éjszakára a templomban hagylak.";
			link.l1 = "Köszönöm, szent atyám. Holnap találkozunk!";
			link.l1.go = "treatment_10";
		break;
		
		case "treatment_10":
			DialogExit();
			RemoveItems(pchar, "mineral3", 20);
			LAi_RemoveLoginTime(npchar);
			LAi_SetLoginTime(npchar, 6.0, 22.99);
			npchar.quest.prayer = "true";
			SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;
		
		case "prayer":
			dialog.text = "Elkészítettem neked az imák szövegét, fiam. Húsz gyertyát és a Szentírást is itt hagytam neked. Gyújtsd meg a gyertyákat és kezdj el imádkozni. Imádkozz megállás nélkül; imádkozz a gyógyulásodért és ennek a szegény bûnös Jessicának a lelkéért. Ha valamit elfelejtesz, vagy ha valamit nem értesz - nem igazán számít. Imádkozz szívbôl, a te ôszinte vágyad az, ami számít a mi Urunknak.";
			link.l1 = "Köszönöm, Atyám. Megvan.";
			link.l1.go = "prayer_1";
		break;
		
		case "prayer_1":
			dialog.text = "Reggel visszajövök. Én is imádkozni fogok értetek...";
			link.l1 = "Köszönöm, szent Atyám.";
			link.l1.go = "prayer_2";
		break;
		
		case "prayer_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "seektreatment":
			dialog.text = "Milyen pogány varázslatok sújtottak téged, fiam?";
			link.l1 = "Nem tudom, hogy hívják ôket. Gyenge és lomha vagyok, nem tudok futni, és nagyon nehezen tudok harcolni.";
			link.l1.go = "seektreatment_1";
		break;
		
		case "seektreatment_1":
			if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
			{
				dialog.text = "Hallottam már azokról... A mi világunkba hozták ôket ezek a vörösbôrû pogányok szentségtelen boszorkányai. Azt tanácsolnám, hogy keresse fel a bridgetowni egyház elöljáró atyját - ô több éven át tanulmányozta az indián átkok káros hatását a keresztények testére és lelkére.";
				link.l1 = "És ô tudna segíteni nekem?!";
				link.l1.go = "seektreatment_4";
			}
			else
			{
				dialog.text = "Hallottam már ezekrôl... E vörösbôrû pogányok szentségtelen boszorkányai hozták ôket a mi világunkba. Sajnos, az egyetlen tanács, amit adhatok neked, hogy tölts több idôt imádkozással, fiam, és reménykedj Urunk kegyelmében.";
				link.l1 = "De hát tényleg nem lehet semmit sem tenni, Atyám?! Ilyen maradok... életeim végéig?";
				link.l1.go = "seektreatment_2";
			}
		break;
		
		case "seektreatment_2":
			dialog.text = "Ne ess kétségbe, fiam! Az Úr meghallgat téged, és segítséget küld neked. De azt javaslom, hogy kérdezôsködj más szent hajlékokban - talán vannak papok, akik tudják, hogyan lehet a pogány átkokat eltávolítani.";
			link.l1 = "Köszönöm, atyám! Meg fogok gyógyulni - még akkor is, ha a szigetvilág összes templomát fel kell keresnem!";
			link.l1.go = "seektreatment_3";
		break;
		
		case "seektreatment_3":
			dialog.text = "Menj, fiam, és az Úr vigyázzon rád.";
			link.l1 = "Viszlát, atyám.";
			link.l1.go = "exit";
			npchar.quest.seektreatment = "true";
			pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment)+1;
		break;
		
		case "seektreatment_4":
			dialog.text = "Csak az Úr segíthet rajtad - és te magad, fiam. Egy pap csak arra taníthat meg, hogy mit és hogyan kell tenned. Gyere el hozzá.";
			link.l1 = "Köszönöm, atyám! Megmentettél engem! Azonnal elhajózom Barbadosra!";
			link.l1.go = "seektreatment_5";
		break;
		
		case "seektreatment_5":
			dialog.text = "Menj most, és az Úr vigyázzon rád.";
			link.l1 = "Viszlát, atyám.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
			pchar.questTemp.Saga.JessFindTreatment = "true";
		break;
		
		case "findtreatment":
			dialog.text = "Milyen pogány átok sújtott téged, fiam? Hadd találjam ki: nem tudsz futni, a szablya túl nehéz neked, a mozdulataid lassúak és lomhák?";
			link.l1 = "Honnan tudtad ezt, atyám?";
			link.l1.go = "findtreatment_1";
		break;
		
		case "findtreatment_1":
			dialog.text = "Nem volt nehéz észrevenni, ahogy a lépteidet figyeltem, ahogy közeledtél felém, fiam. Az Úr legyen irgalmas a mi bûnös lelkünkhöz... Mondd meg, fiam, és légy ôszinte - ki tette rád ezeket a varázslatokat?";
			link.l1 = "Szükséged van egy névre, atyám?";
			link.l1.go = "findtreatment_2";
		break;
		
		case "findtreatment_2":
			dialog.text = "Ha tudod a nevet, akkor mondd ki.";
			link.l1 = "A neve... Jessica Rose.";
			link.l1.go = "findtreatment_3";
		break;
		
		case "findtreatment_3":
			dialog.text = "Isten óvjon minket! A pogány szertartásokba való belemerülés még a legerôsebb lelkeket is a sötétség szakadékába taszíthatja... Mi történt vele, ezzel a szegény lélekkel?";
			link.l1 = "Meghalt, atyám.";
			link.l1.go = "findtreatment_4";
		break;
		
		case "findtreatment_4":
			dialog.text = "De... tényleg meghalt? Vagy... nem teljesen?";
			link.l1 = "Ön rendkívül éleslátó, szent atyám. Most már teljesen halott.";
			link.l1.go = "treatment_3";
			DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
			DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
		//<-- Сага
		
		// Church GenQuest_2 -->	
		case "GenQuest_Church_2_Start_1":
			dialog.text = "...és az Úr kegyelmébôl! Az egyetemes sötétség eméssze el a lelküket a bûneikért...";
			link.l1 = LinkRandPhrase("Szentatya", "atya", "atya") + ", nem túl buzgó egy kicsit? Tudja, akár agyvérzést is kaphat...";
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = "Hát... a francba. Akkor viszlát.";
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_2":
			dialog.text = "Ó, "+ GetSexPhrase("fiam","lányom") +", szörnyû szentségtörés, a legszörnyûbb bûntett történt az imént! Lopás a templomból!!! Mintha magának az Úrnak a zsebébe mártaná az ember a kezét!";
			link.l1 = "Ó, értem... Hogy történhetett ez meg?";
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = LinkRandPhrase("Ez nagyon szomorú, meg minden, de tényleg mennem kell...", "Részvétem, padre, de mennem kell...", "Biztos túlságosan bízott a Mindenhatóban. Biztonságosabb zárakat kellett volna használnod. Nos, nekem mennem kell...");
			link.l2.go = "exit";
		break;
			
		case "GenQuest_Church_2_Start_3":
			dialog.text = "Az éjszaka felhôje alatt néhány gazember elrabolt mindent, amit a plébánia összegyûjtött! Ezek az istenkáromlók még az áldozati kelyhet is elvitték!";
			link.l1 = "O tempora, o mores... De remélem, hogy vállaltál valamit a forró illatodra?";
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;
			
		case "GenQuest_Church_2_Start_4":
			dialog.text = "De hát persze! Kiátkoztam ezeket az istenkáromló rablókat, és most anatémát mondok ki ellenük!";
			link.l1 = "Nincs kétségem afelôl, hogy ez a leghatékonyabb intézkedés. De én valami gyakorlatiasabbra gondoltam. Például az üldözés megszervezésére.";
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;
			
		case "GenQuest_Church_2_Start_5":
			dialog.text = "Á, mit tehet egy egyszerû pap, akit a gonosznak való ellenállás tilalmának fogadalma kötelez? Ezek a gazemberek bizonyára már messze járnak innen, rablásból felhalmozott kocsmákban iszogatnak, vagy bukott nôk társaságában engednek a kicsapongásnak és a kicsapongásnak! Remélem, ott érik majd a végüket!";
			link.l1 = RandPhraseSimple("Biztos vagyok benne, hogy egy ilyen vég sokkal vonzóbb, mint az akasztás. Azonban nem akarom tovább zavarni. Minden jót.", "Nos, egyszer, elôbb-utóbb mindannyian az elôdökhöz fogunk kerülni, de én nem mondanék nemet egy gyorsabb véget nekik. Nekem azonban mennem kell. Sok szerencsét!");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Szentatya", "atya", "atya") + ", de engem nem terhel semmilyen fogadalom, és készséggel segítek az Úrnak, hogy elhozza a megtorlás idejét.";
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = "Imádkozni fogok érted, fiam! Menj most és add meg ezeknek a csalóknak, amit megérdemelnek!";
			link.l1 = "Ne kételkedjen, atyám.";
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;
			
		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;	// Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank)+8)*543+3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount)/3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;
			
		case "GenQuest_Church_2_Thief_2":
			dialog.text = "Nos, talán a mindenható Teremtô pestist és éhséget küld ostoba gyermekeinek, hogy megbüntesse ôket bûneikért...";
				link.l1 = "Például a büszkeség vagy a kapzsiság miatt... Miért sápadtál el, atyám?";
				link.l1.go = "GenQuest_Church_2_Thief_3";
			break;
			
		case "GenQuest_Church_2_Thief_3":
			if(rand(1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = "Jézusom, Uram, könyörülj bûnös szolgádon... Te... Megtaláltad a rablókat? Megölted ôket?";
					link.l1 = "Emlékezzünk a tízparancsolatra, amelyet minden jó keresztény bölcsôjétôl fogva ismer: ne ölj, ne lopj, ne tanúskodj hamisan. Megszegheti-e ezeket egy istenfélô ember - és még inkább egy lelki pap...?!";
					link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = "Olyan sûrû itt a levegô... Hát megtaláltátok a rablókat? Megöltétek ôket?";
					link.l1 = "Emlékezzünk a tízparancsolatra, amelyet minden jó keresztény bölcsôjétôl fogva ismer: ne ölj, ne lopj, ne tégy hamis tanúságot. Megszegheti-e ezeket egy istenfélô ember - és még inkább egy lelki pap!!!";
					link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = ""+ GetSexPhrase("A fiam","A lányom") +"... Isten bocsásson meg... ilyen pénz, ilyen kísértés... az ember gyenge, igazán gyenge! Nem bírtam elviselni... Elment az eszem... Éjjel-nappal imádkoztam, vezekeltem, szigorúan böjtöltem, megaláztam a testemet... Méltatlanul könyörögtem az égieknek, hogy csak kíméljék meg azokat a szegény embereket, akiket saját kapzsiságomtól hajtva kísértésbe ejtettem...";
			link.l1 = LinkRandPhrase("Atya", "Padre", "Atya") + ", nyugodjon meg. Nem mondtak még semmit róla... és nem is fognak, az biztos. Egyébként önként visszaadták nekem az úrvacsorás kelyhet, amit visszahoztam.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = "Uram, köszönöm Neked! Istenem, meghallgattad méltatlan szolgád, egy botcsinálta, mocsokban és erkölcstelenségekben vergôdô bûnös imáit...";
			link.l1 = "Bárki megbotolhatott volna... De mivel bûnbánatod ôszintének tûnik, azt mondom: tisztességes ember és jó pap vagy. Ha a bíróság elé állsz, nem lesz belôle semmi jó. Az pedig már csak rajtad múlik, hogy maradsz-e az Úr szolgálatában vagy sem - ezt csak Ô mondhatja meg és vezethet...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_3":
			if(rand(1) == 0) // Священник хочет всучить ГГ бабло
			{
				dialog.text = ""+ GetSexPhrase("A fiam","A lányom") +"... A bûnbánat és a hála könnyeivel fogadom el tôled ezt a kelyhet. Lelked tisztasága és nemessége valósággal megrázott engem. Teljes szívembôl áldalak és alázatosan kérlek, fogadd el ezt a kis jutalmat " + FindRussianMoneyString(iMoneyToCharacter) + "... Remélem, ez elég lesz a költségeid fedezésére?";
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = "Ez felesleges, szentatya " + NPChar.name + ". Nem vagyok éppen a legszegényebb ember, úgyhogy jobb, ha ezt a pénzt a plébánia javára fordítja.";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = "Köszönöm, " + LinkRandPhrase("atya", "padre", "szentatya") + ", ez több mint elég.";
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = ""+ GetSexPhrase("A fiam","A lányom") +"... A bûnbánat és hála könnyeivel fogadom el tôled ezt a kelyhet az Úr kegyelmének és megbocsátásának jeleként. Lelked tisztasága és nemessége valósággal megrázott engem. Teljes szívembôl áldalak téged!";
				link.l1 = "Köszönöm az áldást, " + LinkRandPhrase("padre.", "atya.") + ".";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l1 = "Az áldás bizonyára szükséges, de nem ártana valami anyagibb dologgal is alátámasztani, tekintve a jelentôs kiadásaimat...";
				link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
			}
			ChurchGenQuest2_RemoveCup();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Ó, gyermekem, igazán sajnálom... Remélem, ez a kis hozzájárulás " + FindRussianMoneyString(iMoneyToCharacter) + " elég lesz a költségeid fedezésére?";
			link.l1 = "Igen, " + LinkRandPhrase("padre.", "atya.") + ", ennyi elég, köszönöm.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;
			
		case "GenQuest_Church_2_Thief_4_1_6_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = "Nem egészen értem a célozgatásait, "+ GetSexPhrase("a fiam","a lányom") +", mirôl beszél?!";
			link.l1 = "A kapzsiság szörnyû dolgokról beszélek, amit a kapzsiság tehet az emberrel, és amit a rongyrázástól kaptam, állítólag kiraboltam a templomotokat... Akarsz mondani valamit?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = "Mondanám neked, gyermekem, hogy egy lelkészhez beszélsz, és egy kicsit több tiszteletet kellene mutatnod, különben a végén még megbánod. Ami ezt a kelyhet illeti - még sosem láttam, de ha hajlandó vagy felajánlani az egyházközségnek, akkor...";
			link.l1 = "Nyugalom, atyám. Nem kapja meg, amíg nem magyarázkodik.";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_3":
			if(rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = "Mit kell magyarázni?! Nézze - maga egy "+ GetSexPhrase("okos ember","okos lány") +", és bizonyára megérti, hogy bármit is mondtak magának ezek a csalók - hogy állítólag én béreltem fel ôket -, az egy szemenszedett hazugság! Az Úr nemcsak szentségtörésért, hanem hamis bizonyítékért is meg fogja büntetni ezeket a káromlókat!";
				link.l1 = "Hagyják békén az Urat! Honnan tudhatnád, hogy mit mondtak nekem azok a szerencsétlenek - akik ellen felültettek? Talán megöltem ôket, mielôtt még volt idejük valami rosszat mondani rólad?";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = "Nincs mirôl beszélnem veled! Nem teljesítetted kötelességedet Urunk elôtt; káromkodsz a templomban; megpróbálsz zsarolni egy papot, felmutatva néhány templomi használati tárgyat - és még nem derült ki, hogyan jutottál hozzá! Hála Istennek, hogy nem hívom az akolitusokat, hogy tetten érjenek!";
				link.l1 = "Hát... Látom, hogy olyan mélyen beleragadtál a bûnbe, hogy már nem félsz az emberek ítéletétôl. De van még isteni igazságszolgáltatás, és elôbb-utóbb mindannyiunknak felelnie kell elôtte. Fogd a 'egyházi használati tárgyaidat' és gondolkozz el, hogy méltó vagy-e arra, hogy megérintsd, atyám " + NPChar.name + ".";
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = "Kérlek, bocsásd meg nekem a kételyeimet, Atyám, mert a halandó szív gyenge, és a lélek zavaros. Kérlek, vedd a kelyhet és add áldásodat.";
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1":
			dialog.text = "Mmmm... "+ GetSexPhrase("A fiam... Mister... Uram...","A lányom... Miss... Lady...") +" " + PChar.name + "... Kész vagyok meghajolni ön elôtt... és úgymond megfontolni a nézeteltéréseinket... és kompenzálni a költségeit ezzel a szerény összeggel " + FindRussianMoneyString(iMoneyToCharacter) + "... persze, ha nem akar másokat is belekeverni ebbe az ügybe...";
			// При этом варианте репу плюсуем
			link.l1 = "Én nem fogok senkit sem belekeverni. Fogd a kelyhet! És még csak ne is gondolja, hogy elfogadnám az aranyat, amit titokban a plébániája zsebébôl csengetett ki!";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
			// При этом - минусуем
			link.l2 = "Nem fogok senkit sem belekeverni. Fogd a kelyhet! Ezt az aranyat csak azért veszem el, mert rengeteg idôt és pénzt áldoztam rád.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterComplexReputation(PChar,"nobility", 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1":
			// ничего не принесли священнику.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
			{
				link.l1 = "Borús hírek, " + LinkRandPhrase("atya", "atya", "atya") + ": a rablók túl alattomosak és találékonyak voltak, ezért nem sikerült visszaszerezni a templom aranyát...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}
			// Принесли священнику только чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = "Borzalmas hírek, " + LinkRandPhrase("atya", "atya", "atya") + ": Sikerült utolérnem a rablókat, de az egyetlen trófeám ez a kehely volt.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Принесли священнику и деньги и чашу.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Biztos vagyok benne, hogy tetszeni fognak a hírek - megközelítôleg megbüntettem a rablókat, és elvettem tôlük a plébánia pénzét, és ezt a kelyhet is.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Atya", "Padre", "Atya") + ", rossz hírt hoztam... Rengeteg idôt, erôt és erôforrást kellett ráfordítanom, hogy levadásszam a gazembereket, de amikor megtaláltam ôket, rájöttem, hogy volt idejük elinni és elkölteni mindent, kivéve ezt a kelyhet...";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				ChurchGenQuest2_RemoveCup();
				break;
			}
			// Священник - вор.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = "Ó, "+ GetSexPhrase("fiam","lányom") +", mi történhetett velem? A te utad tele van veszélyekkel és szorongással, és az én békés cellám, a reflexió és az ima uralma csendes sziget az emberi szenvedélyek tomboló óceánjában...";
					link.l1 = "És semmi sem zavarhatja meg boldog magányod nyugalmát?";
					link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}
			// Короткий вариант прохождения квеста.
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if(sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = "Biztos vagyok benne, hogy ez a hír boldoggá tesz téged - rablókat büntettem meg, és elhoztam a plébánia pénzét.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = LinkRandPhrase("Atya", "Padre", "Atya") + "... Csalódást kell okoznom. Az egész szigetvilágban üldöztem a rablókat, rengeteg veszélyt és akadályt leküzdöttem, majdnem tönkretettem magam, és végül utolértem ôket, de sajnos... már volt idejük elherdálni az egyházi pénzt.";
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			if(rand(1) == 0)	// Священник верит ГГ но не даёт денег...
			{
				if(rand(4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = "Ó, "+ GetSexPhrase("fiam","lányom") +". Szavaid mély bánatba taszítottak - de nem kétségbeesésbe, mert a kétségbeesés halálos bûn! Az Úr újabb próbatétel elé állított minket, hogy megerôsítse hitünket.";
						link.l1 = "Ámen, Atyám...";
						link.l1.go = "exit";
						sQuestTitle = NPChar.City + "ChurchGenQuest2";
						AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
						AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
						CloseQuestHeader(sQuestTitle);
						ChangeCharacterComplexReputation(PChar,"nobility", -2);
						DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = ""+ GetSexPhrase("Fiam","lányom") +", ne hazudj a lelki pásztorodnak.";
						link.l1 = "Nagyon sajnálom, Atyám, de esküszöm, hogy az igazat mondom.";
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = "Ó, "+ GetSexPhrase("fiam","lányom") +". Szavaid mély bánatba taszítottak - de nem kétségbeesésbe, mert a kétségbeesés halálos bûn! Az Úr újabb próbatétel elé állított minket, hogy megerôsítse hitünket. De az erôfeszítéseid és a kiadásaid kárpótolni kell, annak ellenére, hogy eredménytelenek voltak. Kérem, fogadja el ezt a szerény összeget - " + FindRussianMoneyString(iMoneyToCharacter) + " - és folytassa igaz útját!";
					link.l1 = "Hmm!... Köszönöm, atyám, ezt a pénzt erényes célra fogom fordítani.";
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
					link.l2 = LinkRandPhrase("Atya", "Padre", "Atya") + "... Nem fogadhatok el jutalmat azért a munkáért, amit nem végeztem el. Jobb lenne, ha ezt a pénzt az oltár felújítására fordítanád.";
					link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if(rand(6) == 3)
			{
				dialog.text = "Rendben, hiszek neked, "+ GetSexPhrase("fiam","lányom") +". Az Úr egy újabb próbatétellel látogatott meg minket, hogy megerôsítse hitünket.";
				link.l1 = "Ámen...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1"
				break;
			}
				dialog.text = "Megvetendô, tényleg azt gondoltátok, hogy becsapjátok a mi Urunkat?! Átkozott legyél"+ GetSexPhrase(", gazember",", szajha") +"! Takarodjatok és ne feledjétek, hogy ez a pénz semmi hasznot nem hoz nektek!";
				link.l1 = "Hogy lehet ez?! Atyám!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterComplexReputation(PChar,"nobility", -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterComplexReputation(PChar, "nobility", -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			if(rand(1) == 0) // Поверил.
			{
				dialog.text = "Ó, "+ GetSexPhrase("fiam","lányom") +". Szavaid mély bánatba taszítottak - de nem kétségbeesésbe, mert a kétségbeesés halálos bûn! Az Úr újabb próbatétel elé állított minket, hogy megerôsítse hitünket.";
				link.l1 = "Ámen, Atyám...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = "Igen, ez az a kehely, amit a pénzzel együtt elloptak... De... Ha nálad van, hogyhogy nem hoztad vissza a pénzt? Az egy komoly összeg volt, és azok a gazemberek biztosan nem költhették el az egészet ilyen gyorsan... "+ GetSexPhrase("fiam","lányom") +", ne feledd, hogy nincs nagyobb bûn, mint hazudni a lelki pásztorodnak, és hamis bizonyítékot hozni a templomban Isten színe elôtt!";
				link.l1 = "Szentatya " + NPChar.name + ", majdnem elvesztettem az életemet, megszerezve ezt a vázát, gondoltam, hogy boldoggá teszlek. Arról nem is beszélek, hogy mennyi pénzt költöttem az egészre!";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
			break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = "Kifelé, és köszönd meg a Mindenhatónak, aki szelíd szívet adott nekem. Ez az egyetlen oka, hogy még mindig nem bélyegeztek meg tolvajnak és gazembernek!";
			link.l1 = "Hogy lehet ez?! " + LinkRandPhrase("Szentatya", "Padre", "Atya") + "!..";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = "Ó, "+ GetSexPhrase("fiam","lányom") +". Szavaid mély bánatba taszítottak - de nem kétségbeesésbe, mert a kétségbeesés halálos bûn! Az Úr újabb próbatétel elé állított minket, hogy megerôsítse hitünket.";
			link.l1 = "Ámen, Atyám...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			dialog.text = "Uram, köszönöm neked! Valóban, te voltál az Ô eszköze, gyermekem! Tudtam, hogy a mi Mennyei Atyánk megmutatja neked az utat és megad minden segítséget, amire szükséged van. Szünet nélkül imádkoztam, és...";
			link.l1 = "Tudod, atyám, az ilyen ügyekben a fegyverek bizonyára hasznosabbak, mint az imák. De úgy tûnik, az imáit valóban meghallgatták.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = ""+ GetSexPhrase("Fiam","lányom") +", szeretném megfelelôen megjutalmazni, te"+ GetSexPhrase(", mint az Anyaszentegyház igazi lovagja,","") +" mindent megtettél a hatalom felett....";
			link.l1 = "Atyám, maga tényleg túlzásba viszi szerény eredményeimet. Most hagyom, hogy dicsérje Urunkat...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;
			
		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
		break;
		// <-- квесты церкви

		case "donation":
			dialog.Text = "Természetesen "+ GetSexPhrase("fiam","lányom") +". Mennyit szeretnél adományozni a Szentegyháznak?";
			Link.l1 = "Sajnálom, szent atyám, de meggondoltam magam.";
			Link.l1.go = "No donation";
			if(makeint(PChar.money)>=100)
			{
				Link.l2 = "Az adományom szerény lesz, csak 100 pezó.";
				Link.l2.go = "donation paid_100";
			}
			if(makeint(PChar.money)>=1000)
			{
				Link.l3 = "1000 pezó. Azt hiszem, ez elég lesz.";
				Link.l3.go = "donation paid_1000";
			}
			if(makeint(PChar.money)>=5000)
			{
				Link.l4 = "Szerencsés vagyok a pénzzel, ezért 5000 pezót adományozok.";
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if(pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = "Atyám, nem az én nevemben szeretnék adakozni. Egy kérésre teszem.";
				Link.l5.go = "HostessChurch";
			}
			//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = "Hmm... Nos, ez a te döntésed, és szabadon meggondolhatod magad. És ne felejtsd el, hogy ezt az Ítélet Napján számon fogják kérni.";
			Link.l1 = "Mint ahogy sok más dolog is. Váltsunk témát.";
			Link.l1.go = "node_3";
			Link.l2 = "Sajnálom, atyám, de itt az ideje, hogy elmenjek.";
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = "A Szent Egyház nevében köszönöm neked, "+ GetSexPhrase("fiam","lányom") +", az ajándékodat.";
			Link.l1 = "Beszélnem kell veled, atyám.";
			Link.l1.go = "node_3";
			Link.l2 = "Sajnálom, atyám, de itt az ideje, hogy elmenjek.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = "A Szent Egyház nevében köszönöm.";
            Link.l1 = "Beszélnem kell veled, atyám.";
			Link.l1.go = "node_3";
			Link.l2 = "Sajnálom, atyám, de itt az ideje, hogy elmenjek.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = "A Szent Egyház nevében köszönöm az ajándékodat.";
            Link.l1 = "Beszélnem kell veled, atyám.";
			Link.l1.go = "node_3";
			Link.l2 = "Sajnálom, atyám, de itt az ideje, hogy elmenjek.";
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = "Természetesen, "+ GetSexPhrase("fiam","lányom") +", figyelek rád.";
			link.l1 = "Meggondoltam magam. Talán legközelebb.";
			link.l1.go = "exit";
			link.l2 = "Annyira tele vagyok bûnökkel, atyám. Egy nap nem lesz elég, hogy felsoroljam az összes vétkemet...";
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = "Mindannyian bûnösök vagyunk, gyermekem...";
			link.l1 = "Igen, de az én lelkiismeretemre súlyos teherként nehezedik több ezer halálos áldozat terhe. Kiraboltam és vízbe fojtottam hajókat...";
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = "Remélem, nem volt köztük olyan, aki a " + NationNameGenitive(sti(NPChar.nation)) + "zászló alatt hajózott ?";
			link.l1 = "Nem, természetesen nem, atyám.";
			link.l1.go = "ispoved_3";
			link.l2 = "Mindenféle, atyám...";
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = "Akkor a mi Urunk feloldoz téged azok alól a bûnök alól. Mert ez egy kegyetlen kor, és azzal, hogy elpusztítod uralkodód ellenségeit, megmented hûséges alattvalóinak életét.";
			link.l1 = "Köszönöm, atyám, ez nagy vigasz volt... Én most már megyek.";
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = "Az Úr nem fog feloldozni téged ilyen bûn alól! Imádkozzatok és bánjátok meg, bánjátok meg és imádkozzatok! Már csak egy út van számodra - a kolostorba!";
			link.l1 = "A kolostornak várnia kell. Legalábbis ebben az életben nem. Viszlát...";
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

        case "work":
        	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
        	{
        		dialog.text = "Sajnálom, "+ GetSexPhrase("fiam","lányom") +", de jelenleg minden gyóntatószék foglalt. Legalább fél óra múlva meg tudom hallgatni a gyónásodat.";
				link.l1 = "Elnézést, " + RandPhraseSimple("padre", "atya") + ", ez egy másik dolog. Padre " + PChar.GenQuest.ChurchQuest_1.PriestName + ", a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + ", egyszer átadta önnek a teológiai könyvtár felbecsülhetetlen értékû kincseit. Arra kért, hogy adjam vissza ôket.";
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
        	}
			dialog.text = "Miféle üzlet hozta ide, "+ GetSexPhrase("fiam","lányom") +"?";
			link.l1 = "Egy kérdést szeretnék feltenni, atyám...";
			link.l1.go = "quests"; // ссылка к НПС
            link.l2 = RandPhraseSimple("A " + NationNameGenitive(sti(NPChar.nation)) + "egyház javára való munkáról akartam beszélni.",
                                        "Hogy mennek a dolgok az egyházközségben? Szükségetek van segítségre?");
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
	            link.l3 = RandPhraseSimple("Padre", "Atya") + ", pénzügyi ügyekrôl szeretnék beszélni önnel."; //(пересылка в кредиты)
	            link.l3.go = "LoanForAll";
            }
			// -->
            if (stf(pchar.Health.HP) < 60.0)
            {
                link.l4 = "Gyógyulásra van szükségem.";
                link.l4.go = "healthAdd_1";
            }
            
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
	            link.l7 = RandPhraseSimple("Padre", "Szentatya") + ", egy ember kérésére vagyok itt. A neve kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
	            link.l7.go = "IntelligenceForAll";
            }
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
	            link.l10 = "Padre, papírokat hoztam önnek egy szerzetestôl a "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity)+"városból.";
	            link.l10.go = "Monkletter";
            }
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Padre, én a "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity)+"kolóniáról jöttem. A helyi gyülekezetnek több imakönyvre van szüksége, és a helyi szerzetes javasolta, hogy keressük fel Önt ebben az ügyben.";
	            link.l11.go = "Churchbooks";
            }
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
	            link.l11 = "Atyám, elhoztam az imakönyveket a gyülekezete számára.";
	            link.l11.go = "Churchbooks_2";
            }
			//<-- Доставка молитвенников
			link.l99 = "Meggondoltam magam, sok dolgom van.";
			link.l99.go = "exit";
		break;

		case "prihod":
			if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		    {
		        dialog.text = "Ez nagyszerû. És mégis, ezekben a zord idôkben, "+ GetSexPhrase("fiam","lányom") +", nem minden templomlátogató lehet hasznos anyaszentegyházunk számára.";
				link.l1 = LinkRandPhrase("Atya", "Padre", "Atya") + ", én igaz keresztény vagyok, és szándékom, hogy Anyaszentegyházunkat szolgáljam, a legôszintébb."+ GetSexPhrase(" Ki fogja Ôt támogatni, ha nem az olyan hûséges lovagja, mint én?","") +"";
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		    }
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
			}	
            dialog.text = "A plébánián eddig minden csendes, "+ GetSexPhrase("fiam","lányom") +". Köszönöm a felajánlást.";
    		link.l2 = "Nos, ha minden rendben van, akkor azt hiszem, megyek a dolgomra.";
    		link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;	// Если не дал сегодня, то токо на след день.
		break;
		
		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = "Nos, van egy kényes küldetésem, ami nem csak a szándékok tisztaságát, hanem nagy bátorságot és jelentôs diszkréciót is igényel...";
			link.l1 = LinkRandPhrase("Atya", "Padre", "Atya") + ", szívesen teszek önnek bármilyen szolgálatot, még akkor is, ha ehhez egyenesen a pokolba kell mennem! Isten bocsássa meg szentségtelen szavaimat.";
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;
			
		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = "Ó! Jó... De, ismétlem, ez egy nagyon kényes dolog... Nemrég elöljáró atya " + PChar.GenQuest.ChurchQuest_1.ToName + " a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + " a " + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Voc") + "oldalon kölcsönzött nekem egy idôre néhány teológiai mûvet és régi kéziratot egy egyházi könyvtárból. Mivel a kérést az érsek úr ragaszkodása támasztotta alá, hogy ne akadályozza a tudás szép fényének terjesztését, nem utasíthattam vissza, bár feltételeztem, hogy a tengeri utak nehézségei nem teszik lehetôvé, hogy a kéziratokat idôben visszaadja... Tudna-e segíteni nekem a probléma megoldásában?";
			link.l1 = "Attól tartok, " + LinkRandPhrase("atya", "padre", "szent atya") + ", nem fogom tudni ezt megtenni neked. Ez egy nagyon kényes ügy, és csak egy igazi diplomatának sikerülne elintéznie.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Atya", "Padre", "Atya") + ", az ön küldetése nem tûnik túl bonyolultnak számomra. Azonnal odamegyek.";
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;
			
		case "GenQuest_Church_1_Start_3":	// Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;
			
		case "GenQuest_Church_1_Dialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))	// Сцена 2а
			{
				dialog.text = "Ó! Igen... Valóban, most már emlékszem... De, "+ GetSexPhrase("fiam","lányom") +", ezek a kincsek inkább szellemi, mint anyagi természetûek! Már eddig is hatalmas segítséget nyújtottak a plébániámon, és talán a jövôben is fognak!";
				link.l1 = "De, " + LinkRandPhrase("atya", "atya", "atya") + ", plébániájának hívei " + PChar.GenQuest.ChurchQuest_1.PriestName + " is üdvösségre szorulnak, és e mûvek nélkül nem lesz támasza a teológia pilléreinek, prédikációiból pedig hiányzik az ihlet.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else	// Сцена 2б-а и 2б-б
			{
				dialog.text = "Ó, igen!... Valóban... "+ GetSexPhrase("fiam","lányom") +", ezek a kincsek inkább szellemi, mint anyagi természetûek! Már eddig is óriási segítséget nyújtottak a plébániámon, így szégyenszemre, én 'felejtettem' visszaadni ôket jogos tulajdonosuknak...";
				link.l1 = "Valóban, " + RandPhraseSimple("atya", "atya", "atya") + ", valóban. Ezért kért meg Páter " + PChar.GenQuest.ChurchQuest_1.PriestName + " , hogy személyesen adjam át neki ezeket a könyveket.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = "Megértem, gyermekem, de nem imádkozunk-e minden nap az Urunkhoz: 'és bocsásd meg vétkeinket, miképpen mi is megbocsátunk az ellenünk vétkezôknek'? És a templom " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " gazdagabb, mint az én szerény plébániám.";
			link.l1 = "Bizonyára igaza van, atyám, de most eszembe jutottak a Szentírás más sorai: 'ne keressetek könnyû utat, mert ott leselkedik ránk az ördög, és annál finomabb a hangja, és annál erôsebb a kísértés, minél könnyebb az út!' És padre " + PChar.GenQuest.ChurchQuest_1.PriestName + " már el akart küldeni egy üzenetet a feledékenységeddel kapcsolatban az érseknek - csak most beszéltem le róla.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = "Az érsek úrhoz?! Egy ilyen apróság miatt!... Miért? Miért? Miért? Úgyis el akartam küldeni ezeket a mûveket szeretett Krisztusban élô testvéremnek - csak éppen nem volt jó alkalom, hogy átadjam neki. De benned, "+ GetSexPhrase("fiam","lányom") +", Urunk igazán érdemes szolgáját látom. Tessék - fogd ezeket a könyveket és kéziratokat, és kérlek, add át ôket épségben és sértetlenül atyánknak " + PChar.GenQuest.ChurchQuest_1.PriestName + " . És ehhez még hozzáadom legôszintébb hálámat.";
			link.l1 = "Természetesen " + LinkRandPhrase("atya", "atya", "atya") + ". Természetesen...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			// <-- Предмет "рукопись"
		break;
			
		case "GenQuest_Church_1_Dialog_1_2":	// Сцена 2б-а и 2б-б
			// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14)+14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
			FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable  = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "GenQuests_Dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = "De, "+ GetSexPhrase("fiam","lányom") +"... Tudja, az a helyzet, hogy a múlt héten találkoztam egy hajóskapitánnyal '" + sld.Ship.Name + "', ahol egy haldokló matróz áldoztatására hívtak. Nagy örömömre a kapitány " + GetFullName(sld) + " elmondta, hogy ô " + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + ". És bár nem garantált semmilyen feltételt, mégis beleegyezett, hogy segít, és biztosított arról, hogy a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " kikötôt biztosan fel fogja keresni. Így hát kihasználtam ezt a lehetôséget, elküldtem a könyveket ezzel a kedves emberrel, és átadtam a további sorsukat az Úrnak.";
				link.l1 = "Hmm, biztos vagy benne, hogy ebben a kapitányban meg lehet bízni? Felfogta a rábízott mûvek értékét és a küldetés fontosságát?";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = "Ó, "+ GetSexPhrase("fiam","lányom") +"! Csak néhány órát késtél! Már elküldtem apa könyveit " + PChar.GenQuest.ChurchQuest_1.PriestName + " kapitánnyal " + PChar.GenQuest.ChurchQuest_1.CapFullName + ". Ma reggel jött az az istenfélô ember gyónni, és megemlítette, hogy a hajója ma elhajózik " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + ". És bár a kapitány úr nem garantált semmilyen feltételt, mégis beleegyezett a segítségbe, és biztosított arról, hogy a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " kikötôt biztosan fel fogja keresni.";
				link.l1 = LinkRandPhrase("Atya", "Padre", "atya") + "... biztos, hogy ebben a kapitányban meg lehet bízni? És azt is szeretném tudni, hogy a hajójának mi a neve.";
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1":	// 2б-а
			dialog.text = "Bízom az emberekben, "+ GetSexPhrase("fiam","lányom") +", mindannyian Urunk képére és hasonlatosságára lettünk teremtve, és az Ô szent tüze ég minden lélekben!";
			link.l1 = "Ugh. Ez egy súlyos érv, az biztos. Nos... Akkor áldj meg, atyám, és kívánj szerencsét a kapitány kereséséhez.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = "Meg kell bízni az emberekben, "+ GetSexPhrase("fiam","lányom") +". Ami a hajóját illeti - nincs mit mondanom.";
			link.l1 = "És értékes kéziratokat adtál egy kapitánynak anélkül, hogy a hajója nevét is megtudtad volna?!!";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = "Tudja, "+ GetSexPhrase("fiam","lányom") +", kapitány " + PChar.GenQuest.ChurchQuest_1.CapFullName + " nagyon istenfélô...";
			link.l1 = "Nos, ezt már hallottam.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = "Türelem, "+ GetSexPhrase("fiatalember","fiatal hölgy") +"! A kapitány " + PChar.GenQuest.ChurchQuest_1.CapFullName + " nagyon istenfélô ember, és a mai napig olyan nevet viselt a hajója, amit egy papnak még gondolatban sem szabadna kimondania, nemhogy hangosan! És ma a gyónása során erre felhívtam a figyelmét. Mert ahogy a Biblia mondja, a lélek tisztaságát nekünk, bûnösöknek jobban meg kell ôriznünk, mint a test tisztaságát, mert Urunk megtagadja az Ô országát a csúnya szájúaktól...";
			link.l1 = "Látom, " + LinkRandPhrase("Atya", "Padre", "Atya") + ", látom! " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", egy hírhedt szerencsejátékos és iszákos, aki az egész Karib-térségben ismert, úgy döntött, hogy az ön javaslatára átnevezi régi kádját?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = "Nagyon éleslátó vagy, "+ GetSexPhrase("fiam","lányom") +". A hajó új nevét nem tudom, de biztosan valami magasztos.";
			link.l1 = "Ó, " + RandPhraseSimple("Atya", "Padre", "Atya") + "... Köszönök mindent. És imádkozz bûnös lelkemért...";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;
			
		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;
			
		case "GenQuest_Church_1_Complete_1":
			dialog.text = "Ó, gyermekem! Buzgón imádkoztam, és úgy tûnik, minden a lehetô legjobban megoldódott! Segítségedért és hitedért, "+ GetSexPhrase("fiam","lányom") +", a paradicsom és az angyali ének biztosan várni fog...";
			link.l1 = RandPhraseSimple("Padre.", "Atya.") + ", nem fogok egyhamar találkozni Szent Péterrel, Isten ments. Ami az élôket illeti - ôk a mennyei boldogság ígérete mellett sok anyagi dolgot is igényelnek...";
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;
			
		case "GenQuest_Church_1_Complete_2":
			dialog.text = "Igen, igen, "+ GetSexPhrase("fiam","lányom") +", természetesen. Megérdemelten fogom megjutalmazni. Tessék, fogd ezt, és ne feledd, hogy Urunk megbünteti azokat az ostoba lelkeket, akik túlságosan vágynak a földi áldásokra, és imádják a sárga ördögöt!";
			link.l1 = "Köszönöm, " + LinkRandPhrase("atya", "atya", "szentatya") + ". Kérlek, vedd el régóta várt könyveidet és kézirataidat, és imádkozz bûnös lelkemért... Isten veled!";
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;
			
		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveItems(PChar, "Bible", 1);
			items[FindItem("Bible")].Name = "itmname_bible";
			BackItemDescribe("Bible");
			DeleteAttribute(items[FindItem("Bible")], "City");
			ChangeCharacterComplexReputation(PChar,"nobility", 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			TakeNItems(pchar, "chest", 3+hrand(1));
			PlaySound("interface\important_item.wav");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup"); // Трем кэпа
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
			addLiberMisBonus();
			break;
		// <-- Church GenQuest_1

        case "healthAdd_1":
            if (stf(pchar.Health.maxHP) == 60.0) // отлично
            {
                dialog.text = "Az egészséged " + GetHealthNameMaxSmall(pchar) + ", és a sebek maguktól bezáródnak. Csak el kell kerülnöd a vérontást és vigyáznod kell az egészségedre.";
    			link.l1 = "Köszönöm, ez biztosan megkönnyebbülés. Megpróbálom egy ideig visszafogni magam a harcoktól.";
    			link.l1.go = "exit";
            }
            else
            {
    			dialog.text = "Az egészséged " + GetHealthNameMaxSmall(pchar) + ", és bár a sebek maguktól bezáródnak, vigyáznod kell rá.";
    			link.l1 = "Mi kell ehhez?";
    			link.l1.go = "healthAdd_2";
			}
			link.l2 = "És miért romlik az egészségem?";
    		link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = "Ez nagyon egyszerû, "+ GetSexPhrase("fiam","lányom") +". Minden egyes alkalommal, amikor megsebesülsz, sérülést szenvedsz. Ez nem múlik el nyomtalanul. Minden sebesüléssel romlik az egészségi állapotod, és ennek következtében gyengülsz. A legénységed, látva a gyenge kapitányt, elveszti a tiszteletét irántad. Viszont óvatosabbá válsz, és a védekezôképességed átmenetileg megnô. A pihenés és a sebek minimalizálása segít abban, hogy teljes erôbedobással maradj.";
			link.l1 = "Köszönöm a felvilágosítást.";
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = "Imádkozás és tartózkodás az erôszaktól, "+ GetSexPhrase("fiam","lányom") +". Akkor az Úr visszaadja neked, amit elvesztettél.";
			link.l1 = "De imádkoznál értem?";
			link.l1.go = "healthAdd_3";
			link.l2 = "Szóval nincs rá mód? Hmm... Igazán megnyugtattál, köszönöm.";
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
            if (npchar.quest.HealthMonth != iMonth)
            {
    			dialog.text = "Engem? Ez valószínûleg lehetséges. De adományt kell adnia az egyházközségünknek.";
    			link.l1 = pcharrepphrase("Mennyiért?", "Örömmel! Mennyiért?");
    			link.l1.go = "healthAdd_4";
    			link.l2 = "Gondolom, majd én elintézem...";
    			link.l2.go = "exit";
			}
			else
			{
                dialog.text = ""+ GetSexPhrase("Fiam","lányom") +", már most imádkozom a jólétetekért. Ezek az imák a hónap végéig minden idômet lekötik.";
    			link.l1    = "Köszönöm, "+RandPhraseSimple("padre.", "Szentatya.");
    			link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = "Százezer pezó pezó elegendô lesz a gyógyulás csodájáért.";
			link.l1 = pcharrepphrase("Mi?! Teljesen megôrültél? Én is fizetnék egy ekkora összeget, ha egyszer kirabolnék pár templomot!", "Ez nekem túl sok. Mondják az igazat - az egészséget nem lehet pénzért megvenni.");
			link.l1.go = "exit";
            if (sti(pchar.Money) >= 100000)
            {
    			link.l2 = "Egyetértek!";
    			link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
            AddMoneyToCharacter(pchar, -100000);
            AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
            npchar.quest.HealthMonth = iMonth;
			dialog.text = "Rendben. Az egészséged egy kicsit javulni fog. De továbbra is kerülnöd kell a csetepatékat és vigyáznod kell magadra, különben ez a hatás elmúlik. Egy egész hónapot kell imádkoznom a romlandó testedért.";
			link.l1 = "Köszönöm. Ha bármi történne, egy hónap múlva újra meglátogatlak.";
			link.l1.go = "exit";
		break;
		
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = "És ki az a kedves lélek, aki a pénzt adományozza?";
			link.l1 = "Hmm... Ez a helyi bordélyház madame-ja.";
			link.l1.go = "HostessChurch_call";
			link.l2 = "Szeretném titokban tartani a neveket. Névtelenül is lehet adományozni, ugye?";
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		
		case "HostessChurch_call":
			if (isBadReputation(pchar, 5)) 
			{
				if (rand(100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				{
					dialog.text = "Te egy bûnös vagy, mégis egy bûnösért kérdezel? Jobb lenne, ha elôbb a lelkedre gondolnál, valójában mindannyian megjelenünk majd az Úr elôtt!";
					link.l1 = "Ez így van. Remélem, hogy a mi Urunk kegyes lesz hozzám... És mi lesz az adományozással?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Takarodj a hátam mögé, Sátán!!!! Fogd a szentségtelen pénzed és tûnj el!";
					link.l1 = "Hogy van, atyám?! Nyitott szívvel jöttünk hozzád, és te...";
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				{
					dialog.text = "Örülök, hogy segítesz a bûnösöknek, hogy megtalálják az utat a mi Urunkhoz. Ezért megkapjátok majd a mennyben, ami jár nektek!";
					link.l1 = "Az nagyszerû lenne! És mi lesz az adományozással?";
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = "Nem fogadhatok el bûnnel szerzett pénzt. Add vissza annak a bukott asszonynak, "+ GetSexPhrase("fiam","lányom") +". Senki sem találhat utat Istenhez a pénzen keresztül.";
					link.l1 = "Kár, hogy elutasítod ôt. Valóban kár.";
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		
		case "HostessChurch_notCall":
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				dialog.text = "Elvenni ezt a pénzt, anélkül, hogy tudnád, honnan származik...";
				link.l1 = "Igen, atyám, pontosan. Kérem, fogadja el ezt a szívbôl jövô adományt!";
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = "Elvenni ezt a pénzt, anélkül, hogy tudná, honnan származik? Maga megôrült?! És mi van, ha ez a pénz vérrel van bemocskolva!";
				link.l1 = "Atyám, minden pénz véres...";
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = "Elfogadom, "+ GetSexPhrase("fiam","lányom") +". Menj és mondd el, hogy a bukott asszonyod.";
			link.l1 = "Rendben, atyám. Köszönöm, atyám.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_ok_1":
			dialog.text = "Elfogadom, "+ GetSexPhrase("fiam","lányom") +". Mondd el ennek az adományozónak.";
			link.l1 = "Rendben, atyám. Köszönöm, atyám.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		
		case "HostessChurch_bad":
			dialog.text = "Tûnj el, te pokol szülötte, és ne merészeld még egyszer itt mutatkozni!";
			link.l1 = "Heh, ahogy kívánod.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_1":
			dialog.text = "Ez az én döntésem. Menj békében, "+ GetSexPhrase("fiam","lányom") +".";
			link.l1 = "Ég veled, atyám.";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		
		case "HostessChurch_bad_2":
			dialog.text = "Ezt gondolod, te istenkáromló?! Azonnal hagyd el a templomot, és ne merészeld még egyszer itt mutatkozni!";
			link.l1 = "Ó, tényleg? Nem számít, elmegyek...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = "Már majdnem elvesztettem a reményt, hogy újra láthatom ezeket a papírokat. Miért tartott ilyen sokáig, fiam?";
				link.l1 = "Ez... váratlan fejlemények miatt volt, apám.";
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = "Már vártam ezeket a papírokat, fiam. Köszönöm a gyors kézbesítést. Kérlek, fogadd el ezeket az érméket, és menj el az áldásommal.";
				link.l1 = "Köszönöm, atyám. Örömmel segítettem a Szent Egyháznak!";
				link.l1.go = "Monkletter_3";
			}
		break;
		
		case "Monkletter_1":
			dialog.text = "Mindannyian Isten kezében vagyunk, fiam... Az ember javasol, de Isten rendel. Add át ezeket a papírokat és menj békében.";
			link.l1 = "Tessék, atyám. Minden jót neked!";
			link.l1.go = "Monkletter_2";
		break;
		
		case "Monkletter_2":
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter_3":
			dialog.text = "Isten áldása, fiam. A Mindenható vigyázzon rád az utadon!";
			link.l1 = "Viszlát, atyám.";
			link.l1.go = "Monkletter_4";
		break;
		
		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);//заменить на нужный
			AddQuestRecord("Monkletter", "3");
			CloseQuestHeader("Monkletter");
			TakeNItems(pchar, "gold_dublon", 10+rand(5));
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
			addLiberMisBonus();
		break;
		//<-- Церковная депеша
		
		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = "Azért küldtek, hogy imakönyveket vegyél el tôlünk - a "+XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity+"Gen")+"egyház számára ? Nos. Van egy csomagom harminc imakönyvvel. Vedd el, fiam.";
			link.l1 = "Köszönöm, atyám. Viszontlátásra!";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			dialog.text = "Az Úr vigyázzon rád az utadon! Menjetek békében...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");//поставить соотв.предмет
		break;
		
		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = "Köszönöm a segítséget, fiam, bár némi késéssel érkezett.";
				link.l1 = "Elôre nem látott események miatt késlekedtem, atyám.";
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = "Köszönöm a segítségedet, fiam. Éppen idôben hoztad ezeket a könyveket. Kérlek, fogadd el jutalmul ezt a megszentelt amulettet - megment a veszélytôl a legsötétebb órában.";
				link.l1 = "Köszönöm, atyám. Örömmel segítettem a Szent Egyháznak!";
				link.l1.go = "Churchbooks_4";
			}
		break;
		
		case "Churchbooks_3":
			dialog.text = "Minden Isten kezében van, fiam. Menj békében!";
			link.l1 = "Viszlát, atyám.";
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
		
		case "Churchbooks_4":
			dialog.text = "Isten áldása, fiam. A Mindenható ôrizzen meg téged a bajtól utadon!";
			link.l1 = "Viszlát, atyám.";
			link.l1.go = "Churchbooks_5";
		break;
		
		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes"; //снять таймер patch-5
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);//заменить на нужный
			GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
			Log_Info("Ön megkapta '"+XI_ConvertString(pchar.GenQuest.Churchbooks.Item)+"'");
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
			addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr); 
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;
	
	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch(iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2A (just pick up the manuscript from the priest)."); 
		break;
		
		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-A (search for a cap. There is full information about him).");
		break;
		
		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Church generator 1: key scene - 2B-B (search for a cap. The name of the ship is unknown)."); 
		break;
	}
}
