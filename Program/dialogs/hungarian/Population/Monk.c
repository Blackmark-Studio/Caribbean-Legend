//Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

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
	
	iTest = FindColony(NPChar.City);
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = "Jó napot, fiam. Arra kérlek, hogy mutass némi szívességet, és adományozz néhány ezüstpénzt a szegények, a te lelked és a Szent Szûz Anyaszentegyház javára.";
					link.l1 = "Nos atyám, úgy gondolom, hogy mindannyiunknak segítenünk kell egymáson, ahogy Krisztus és az Ô Egyháza tanít minket. Meg tudná nekem mondani, hogy hová megy majd a pénz?";
					link.l1.go = "donation";
					link.l2 = "Bocsásson meg, atyám, de most olyan szegény vagyok, mint egy templom egere.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)//монах-пассажир
				{
					dialog.text = "Szép napot, fiam. Szeretnélek megkérni egy szívességre. Természetesen fizetni fogok.";
					link.l1 = "Hallgatlak, atyám. Mire van szükséged?";
					link.l1.go = "passenger";
					link.l2 = "Nagyon sajnálom, apám, de mennem kell.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))//корабельный капеллан
				{
					dialog.text = "Üdvözletem, fiam. Gondolom, kapitány vagy. Van egy javaslatom a számodra.";
					link.l1 = "Hallgatlak, apám.";
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(LinkRandPhrase("Üdvözletem, fiam. Mi bánt téged?","Üdvözletem, fiam. Menj a lelkészhez, ha gyónni akarsz.","Üdvözletem, fiam. 'emlékezz Teremtôdre ifjúságod napjaiban.'"),LinkRandPhrase("Üdvözletem, fiam. Mi bánt téged?","Jó napot kívánok neked, fiam, Isten áldjon meg!","Jó napot kívánok neked, fiam, Isten arca ragyogjon rád!"));
				link.l1 = LinkRandPhrase("Neked is, atyám. Hogy vagy?","Jó napot kívánok, atyám. Hogy van az egyházközséged?","Hogy van, atyám?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Van egy kérdésem hozzád, atyám.", "Információra van szükségem.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
				{
					link.l3 = "Atyám, emberek vannak a hajómon. Rabszolgák, keresztények és kereszteletlen pogányok. Szeretném, ha megkeresztelnéd a pogányokat és áldoznál a keresztényeknek. Utána mindannyiukat felszabadítom Isten és egyházunk dicsôségére.";
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Atyám, szeretném, ha megáldanád a hajómat és misét mutatnál be a legénységemért. Mennyibe kerülne ez?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Bocsásson meg, atyám, de mennem kell.","Elnézést a zavarásért, apám.","Vissza kell mennem a hajóra, apám. Isten veled!");
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = LinkRandPhrase("Már megint te, fiam? Mit akarsz?","Van még valami mondanivalód, fiam?","Jó újra látni téged, fiam.");
				link.l1 = LinkRandPhrase("Neked is, atyám. Hogy vagy?","Jó napot kívánok, atyám. Hogy van az egyházközséged?","Hogy van, atyám?");
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = RandPhraseSimple("Van egy kérdésem hozzád, atyám.", "Információra van szükségem.");
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
					{
						link.l3 = "Atyám, emberek vannak a hajómon. Rabszolgák, keresztények és kereszteletlen pogányok. Szeretném, ha megkeresztelnéd a pogányokat és áldoznál a keresztényeknek. Utána mindannyiukat felszabadítom Isten és egyházunk dicsôségére.";
						link.l3.go = "slaves";
					}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = "Atyám, szeretném, ha megáldanád a hajómat és misét mutatnál be a legénységemért. Mennyibe kerülne ez?";
					link.l4.go = "shipshine";
				}
				link.l10 = LinkRandPhrase("Bocsásson meg, atyám, de mennem kell.","Elnézést a zavarásért, atyám.","A hajómra kell mennem, apám. Isten veled!");
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "check":
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = "Sürgôs dolgom van számodra, fiam. Át kell adnom ezeket a papírokat a  "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+"lelkészének. Arrafelé hajózol? Az iratokat két héten belül át kell adni...";
				link.l1 = "Elég könnyû, apa. Add ide azokat a papírokat, és én elviszem ôket a "+XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen")+".";
				link.l1.go = "Monkletter";
				link.l2 = "Szívesen megteszem, atyám, de másfelé hajózom.";
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city;//город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = "Fiam, hajlandó lennél segíteni nekem egy sürgôs ügyben? A gyülekezetünknek fogytán vannak a Bibliák és imakönyvek, amelyeket mindenkinek adunk, akinek szüksége van rájuk\nVitorláznál a legközelebbi kolóniára "+NationNameGenitive(sti(npchar.nation))+", hogy elhozz néhány Bibliát és imakönyvet a helyi gyülekezetbôl, és idehozd ôket? És próbáljátok meg ezt egy hónap alatt megtenni, nem sok van már belôle.";
				link.l1 = "Szívesen segítek az egyházadnak. Ezeket a könyveket bármelyik lelkésztôl megkaphatom?";
				link.l1.go = "Churchbooks";
				link.l2 = "Szívesen, atyám, de most nem tehetem meg.";
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}
			
			dialog.text = RandPhraseSimple("Semmi baj, fiam. Köszönöm a kedves szavakat.", "Az egyházközségünk jól van, fiam. Köszönöm az aggodalmadat.");
			link.l1 = "Akkor mennem kell, atyám.";
			link.l1.go = "exit";
		break;
		
//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = "Persze, fiam. "+sTemp+"";
			link.l1 = "Milyen adományt tekintenél elegendônek?";
			link.l1.go = "donation_1";
		break;
		
		case "donation_1":
			dialog.text = "Minden a pénztárcádtól és a személyes kívánságodtól függ, fiam. 'Isten szereti a vidám adakozókat.' Mélységesen hálásak vagyunk minden adományért.";
			link.l1 = "100 pezó";
			link.l1.go = "donation_rate_1";
			link.l2 = "1000 pezó";
			link.l2.go = "donation_rate_2";
			link.l3 = "5000 pezó";
			link.l3.go = "donation_rate_3";
			link.l4 = "10000 pezó";
			link.l4.go = "donation_rate_4";
		break;
		
		case "donation_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Köszönjük az érméket, fiam! Jó célt szolgálnak majd!";
				link.l1 = "Szívesen, szent atyám.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "'Ne tévesszen meg senkit, Isten nem gúnyolódik. Mert amit az ember vet, azt aratja is. Mert aki a testében vet, az a testébôl is romlást arat. Aki pedig lélekben vet, az a lélekbôl arat örök életet.'";
				link.l1 = "Ha-ha! Hagyd a prédikációt, nem jótékonykodom. Tûnjetek el!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_2":
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Köszönöm, fiam. Ez az összeg valóban segíteni fogja egyházközségünk misszióját. Áldjon meg az ég!";
				link.l1 = "Sok szerencsét, atyám!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCrewMorale(pchar, 2);
			}
			else
			{
				dialog.text = "Isten megtorlása vár rád, uram! Krisztus szent egyházának szolgáját kigúnyolni istenkáromlás!";
				link.l1 = "Ha-ha! Nem jótékonykodom. Tûnjetek el!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_3":
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "El sem tudtam volna képzelni, hogy ilyen nagylelkû vagy, fiam! A következô levelemben megemlítelek a püspökünknek, és minden nap imádkozni fogunk érted! Megáldalak és hálásan fogadom a pénzedet!";
				link.l1 = "A pénz nem ér semmit, ha nem Isten céljaira használjuk! Sok szerencsét, atyám!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCrewMorale(pchar, 3);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			}
			else
			{
				dialog.text = "Isten megtorlása vár rád, uram! Krisztus szent egyházának szolgáját kigúnyolni istenkáromlás!";
				link.l1 = "Ha-ha! Nem jótékonykodom. Tûnjetek el!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_rate_4":
			if (sti(pchar.money) >= 10000)
			{
				AddMoneyToCharacter(pchar, -10000);
				dialog.text = "Mi... jól hallottam? Tényleg adományozol tízezer pesót?!? Megáldalak és hálásan elfogadom a pénzedet. A következô levelemben megemlítem önt a püspökünknek, és minden nap imádkozni fogunk önért! Ez hatalmas segítség az egyháznak!";
				link.l1 = "'Akinek sok adatott, annak sok kell,' igaz? Sok szerencsét, szentatya!";
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 10);
				AddCharacterExpToSkill(pchar, "Leadership", 60);
				AddCrewMorale(pchar, 5);
				ChangeCharacterComplexReputation(pchar, "nobility", 1);
				ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
				ChangeCrewExp(pchar, "Sailors", 5);
				ChangeCrewExp(pchar, "Cannoners", 5);
				ChangeCrewExp(pchar, "Soldiers", 5);
			}
			else
			{
				dialog.text = "Isten megtorlása vár rád, uram! Krisztus szent egyházának szolgáját kigúnyolni istenkáromlás!";
				link.l1 = "Ha-ha! Nem jótékonykodom. Tûnjetek el!";
				link.l1.go = "donation_exit";
			}
		break;
		
		case "donation_exit":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterHealth(pchar, -5);
			LAi_CharacterDisableDialog(npchar);
		break;
		
//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = "Természetesen, fiam. Szent kötelességünk, hogy segítsünk ezeknek a szegény nyomorultaknak. Megteszem, amit kérsz.";
			link.l1 = "Köszönöm, atyám. Tíz darab pesot adományozok minden megkeresztelt és beadott fogoly után.";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES)*10);
			dialog.text = "Bár nem szükséges, de hálásan elfogadom a lopási díjat. A pénzét egyházközségünk különbözô misszióira fordítjuk. Elvezetne a hajójához?";
			link.l1 = "Igen, atyám. Kövessenek.";
			link.l1.go = "slaves_2";
		break;
		
		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam("Két órával késôbb"+ NewStr() +"A rabszolgákat felszabadították.", "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
//<-- отпустить рабов

//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
			//поиск старшего класса
			iTemp = 7;
			for (i=0; i<COMPANION_MAX; i++)
			{
				int iIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iIdx >= 0)
				{
					sld = GetCharacter(iIdx);
					if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
				}
			}
			switch (GetCompanionQuantity(pchar))
			{
				case 1: 
					sTemp = "Csak egy hajó van a századomban, és az "+iTemp+" rangú.";
					pchar.GenQuest.Shipshine.Money = 5000*(7-iTemp);
				break;
				case 2:
					sTemp = "Két hajó van a századomban, és a legnagyobb a "+iTemp+" rangú.";
					pchar.GenQuest.Shipshine.Money = makeint(1.8*(5000*(7-iTemp)));
				break;
				case 3:
					sTemp = "Három hajó van a századomban, és a legnagyobb a "+iTemp+" rangú.";
					pchar.GenQuest.Shipshine.Money = makeint(2.6*(5000*(7-iTemp)));
				break;
				case 4:
					sTemp = "Négy hajó van a századomban, és a legnagyobb a "+iTemp+" rangú.";
					pchar.GenQuest.Shipshine.Money = makeint(3.4*(5000*(7-iTemp)));
				break;
				case 5:
					sTemp = "Öt hajó van a századomban, és a legnagyobb a "+iTemp+" rangú.";
					pchar.GenQuest.Shipshine.Money = makeint(4.2*(5000*(7-iTemp)));
				break;
			}
			dialog.text = "Minden attól függ, hogy összesen hány hajó van a századodban és mekkora a méretük.";
			link.l1 = ""+sTemp+"";
			link.l1.go = "shipshine_1";
		break;
		
		case "shipshine_1":
			dialog.text = "Ez az ára "+FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money))+", fiam.";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = "Ezt az összeget ki tudom fizetni neked, apám. Vedd el a pénzt.";
				link.l1.go = "shipshine_2";
			}
			link.l2 = "Sajnos, nincs nálam ennyi pénz.";
			link.l2.go = "shipshine_exit";
		break;
		
		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = "Rendben, fiam. Hadd gyûjtsem össze a szent edényeket, és elmegyünk a kikötôbe.";
			link.l1 = "Kövess, apám.";
			link.l1.go = "shipshine_3";
		break;
		
		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam("Néhány órával késôbb"+ NewStr() +"A pap misét tartott a hajótokon és megáldotta azt.", "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
//<-- освятить корабль

//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = "Helló kapitány, hadd mutatkozzam be. Pap vagyok, és van némi tapasztalatom káplánként hadihajók fedélzetén. Az utolsó hajómat azért hagytam ott, mert a kapitány és én... erkölcsi nézeteltéréseink voltak. Szeretne felvenni a legénységébe?";
			link.l1 = "Egy papot a fedélzetre? Mondja atyám, mit csinál egy hajóskáplán?";
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;
		
		case "capellan_1":
			dialog.text = "Miért, ez teljesen nyilvánvaló. Imádkozom Istenhez önért és a legénységéért, naponta tartson misét, áldja meg az embereit és hallgassa meg a gyónást a csata elôtt. Isten igéje ad erôt a legénységed kezének és lelkének. A legénységednek lehetôsége lesz arra, hogy rendszeresen részesüljön szentáldozásban és gyónásban. Higgye el, egy kegyelmi állapotban lévô matróz olyan helyzetekben is kitart, ahol egy istentelen meginog\nNem kérek sokat magamnak: egyszeri ötvenezer pesót a szülôegyházközségemnek, egy egyszerû priccset a kabinban és egy fedélzetet, ami a tisztjeivel azonos. Ennyi lenne minden.";
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = "Érdekes... Igaza van, egy jó kapitánynak nemcsak a legénysége testét, hanem a lelkét is hordoznia kell. Isten hozta a fedélzeten, atyám!";
				link.l1.go = "capellan_2";
			}
			link.l2 = "Nem, atyám. Sajnálom, de nem engedhetem meg magamnak a szolgálatait.";
			link.l2.go = "capellan_exit";
		break;
		
		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Köszönöm a bizalmadat, fiam. Bölcsen költötted a pénzed. De figyelmeztetlek, csak méltó kapitányokat szolgálok, akár kereskedô, akár kalóz, nem számít. De soha nem fogok kalózhajó fedélzetén prédikálni!\nHa tehát valaha is felemeled az ördög Jolly Rogert, azonnal elhagyom a hajódat a legelsô kikötôben.";
			link.l1 = "Megfontolom, atyám, és igyekszem nem csalódást okozni neked. Kérlek, menj a fedélzetre, és mutatkozz be a legénységnek!";
			link.l1.go = "capellan_3";
		break;
		
		case "capellan_3":
			DialogExit();
			pchar.questTemp.ShipCapellan.id = npchar.id;
			AddDialogExitQuestFunction("Monk_Capellan_DlgExit");
		break;
		
		case "capellan_4":
			dialog.text = "Szükséged van valamire, fiam?";
			link.l1 = "Nem, semmi, apám.";
			link.l1.go = "exit";
			link.l2 = "Padre, szeretném, ha a következô kikötôben elhagyná a hajót. Nem magyarázkodom tovább.";
			link.l2.go = "capellan_5";
			NextDiag.TempNode = "capellan_4";
		break;
		
		case "capellan_5":
			dialog.text = "Rendben, fiam. Itt te vagy a fônök. A következô településen elhagyom a hajódat.";
			link.l1 = "Köszönöm a megértésedet, atyám.";
			link.l1.go = "capellan_6";
		break;
		
		case "capellan_6":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			ShipCapellan_Remove();
		break;
		
		case "capellan_7":
			dialog.text = "Fie, kapitány! Figyelmeztettelek, hogy elhagylak, ha felvonod a kalózzászlót! A következô kikötôben elhagyom a hajóját. Imádkozni fogok az azonnali bûnbánatodért és a Szent Anya Egyház ölelésébe való visszatérésedért.";
			link.l1 = "A fenébe is...";
			link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;
//<-- капеллан
	
//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				dialog.text = "A "+GetSexPhrase("fiam","lányom")+", el kell jutnom a " + XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+" ez a "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+", a "+FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty))+". Ezért fizetek neked "+FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money))+" . Mit szólsz hozzá?";
			}
			else
			{
				dialog.text = "Az én "+GetSexPhrase("fiam","lányom")+", az Úr titokzatos utakon jár, ezért keresek egy megbízható kapitányt. Tudsz segíteni nekem eljutni a " + XI_ConvertString("Colony"+pchar.GenQuest.Monkpassenger.City)+", ami a "+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Dat")+"oldalon van ? Úgy tudom, hogy ez olyan, mint egy utazás a tüzes Gehennába, mivel az ellenségeink soha nem alszanak. És megértem, hogy te nem vagy Jézus Krisztus, de én sem vagyok apostol, és ezért van némi megtakarításom. Elég lesz neked a " + FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)) + " ?";
			}
			link.l1 = "Egyetértek, atyám.";
			link.l1.go = "passenger_1";
			link.l2 = "Sajnálom, atyám, de én más irányba hajózom. Nem tudok segíteni neked.";
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;
		
		case "passenger_exit":
			dialog.text = "Ez Isten akarata mindenkinek, fiam. Várok egy másik hajóra. Béke legyen veled!";
			link.l1 = "Ég veled, atyám.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;
		
		case "passenger_1":
			dialog.text = "Isten áldjon meg téged! Megkapod a fizetséged, ha megérkeztünk a célállomásunkra.";
			link.l1 = "Menj a hajómra, atyám. Hamarosan indulunk.";
			link.l1.go = "passenger_2";
		break;
		
		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
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
			AddQuestUserDataForTitle(sTitle, "sType", "monk");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Monkpassenger.City+"Gen") + ", which is on " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City)+"Voc")+"."; // belamour gen
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City+"_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;
		
		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = "Köszönöm, az én "+GetSexPhrase("fiam","lányom")+". Te teljesítetted az ígéretedet, és most én jövök. Vedd el a pénzed, ahogy ígértem.";
			link.l1 = "Köszönöm. Sok szerencsét, apa.";
			link.l1.go = "passenger_4";
		break;
		
		case "passenger_4":
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
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			{
				AddCharacterExpToSkill(pchar, "Sneak", 50);
				TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
			}
			else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			sTitle = npchar.index+"Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
//<-- монах-пассажир
		
//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		
		case "Monkletter":
			dialog.text = "Tessék. Fogd ezt a csomagot, fiam. Ne feledd, hogy csak két heted van a kézbesítésre. A lelkész már várja. Menj, és Isten legyen veled!";
			link.l1 = "Nem hagylak cserben, atyám. Isten veled.";
			link.l1.go = "Monkletter_1";
		break;
		
		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
//<-- Церковная депеша
		
//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = "Igen. Bármelyik kolóniában beszerezheted ôket "+NationNameGenitive(sti(npchar.nation))+". Az összes könyvet, amit találsz, hozd el a lelkészünknek a templomba. Isten áldjon meg benneteket!";
			link.l1 = "Köszönöm! Hamarosan megkapjátok a könyveket.";
			link.l1.go = "Churchbooks_1";
		break;
		
		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(4))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
				case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
				case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
				case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
				case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
			}
			OfficersReaction("good");
		break;
//<-- доставить молитвенники
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
		case 0: sText = "Pénzt gyûjtök egy kápolna "+LinkRandPhrase("építésére","egy alamizsnaház","egy kórház")+". A helyi lakosok keveset adnak alamizsnára, ezért olyan jómódú embereket kell megkérnem, mint ti." break;
		case 1: sText = "Adományokat gyûjtök a templomunk számára. A tengerészeknek általában nincs sok idejük Isten házának meglátogatására, de mindenkinek meg kell tennie mindent a saját lelke megmentéséért." break;
		case 2: sText = "Pénzt gyûjtök, hogy élelmet és gyógyszereket vásároljak a szegényházunk számára a betegek, özvegyek, árvák és gyengék számára. Kérem, adakozzanak uram, mert csak Isten kegyelmébôl megyünk mindnyájan." break;
		case 3: sText = "Pénzt gyûjtök új szent edényekre, mert az Európából hozott edényeinket megviselte a folyamatos használat. Minden kereszténynek kötelessége, hogy gondoskodjon egyházunkról." break;
		case 4: sText = "Pénzt gyûjtök templomunk felújítására, a tetô borzasztóan beázik, és a padokat is meg kell javítani. Minden kereszténynek kötelessége, hogy gondoskodjon a templomunkról." break;
		case 5: sText = "Pénzt gyûjtök arra, hogy ki tudjuk fizetni azt a jó mûvészt, aki képes kifesteni templomunk falait, és jeleneteket rajzol rájuk a Bibliából azok számára, akik nem tudnak olvasni az egyházközségünkben. Minden kereszténynek kötelessége, hogy törôdjön a templomával." break;
		case 6: sText = "Pénzt gyûjtök egy új fôoltárra templomunk számára. Plébániánk szegény, és szeretnénk egy nemes helyet a Szentségnek. Nagyon remélem a segítségeteket." break;
		case 7: sText = "Sok sebesült tengerész van a kórházunkban a kalóztámadásokból. Gyógyszerekre és kötszerekre van szükségük. Imádkozzatok, hogy segítsetek nekik, mert ti igazán megértitek az egyszerû tengerészek szenvedéseit." break;
		case 8: sText = "Próbálok pénzt szerezni ruhákra és élelmiszerre legszegényebb polgárainknak. Az egyetlen reményük a mi szent egyházunk. Kérlek, segítsetek nekik." break;
		case 9: sText = "Szigetünk mélyére megyek missziós munkára, hogy Krisztus evangéliumának világosságát elvigyem a pogány indiánok elveszett lelkeinek. Gyûjtöm az alapokat ehhez az expedícióhoz. Kérem, segítsétek jótettünket!" break;
	}
	return sText;
}
