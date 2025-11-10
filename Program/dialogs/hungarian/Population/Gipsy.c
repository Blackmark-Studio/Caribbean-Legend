//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Á, helló, drágám. Mit szeretnél?";
			link.l1 = "Gondolom, semmit.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "információra van szükségem.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Drágám, lennél szíves megosztani egy kis aranyat? Elmondom neked a jövôdet.","Hé, tengerész, ne siess így! Akarod tudni a jövôt?","Adj egy kis dohányt és néhány ezüstpénzt, bátor fiatalember. És megnézem a jövôdet. (kacsint) Akarsz hallani egy kis titkos cigány varázslatot?");
				link.l1 = "Sajnálom, de mennem kell.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Figyelj bádogos hölgy, tudom, hogy a te néped a bájitalok és mérgek szakértôje. Azt mondták, hogy téged érdekelhet ez a növény. Nézd meg. Mit gondolsz?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "Hé, sötétszemû, van valamim a számodra... Ez itt mangarosa. Akarsz venni belôle?";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "Tudsz nekem jósolni?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("Lenne egy kérdésem hozzád.", "információra van szükségem.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "Egy cigányasszonyt keresek, aki betegeket ápol. Te lennél az?";
				link.l6.go = "dwh_ne_ta";
			}
			// <-- Тёмные воды исцеления

			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "Hé, sötétszemû, van valami patkányméreg? Átkozottul bosszantóak a hajómon.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "Persze, szépfiú. Adj néhány érmét, és mutasd a jobb kezed. Elmondom a jövôdet, és segítek elkerülni a katasztrófát. Soha nem csalok! Pénzvisszafizetési garancia!";
			link.l1 = "Úgy érzem, ez az a rész, amikor a honfitársad zsebre vág... Meggondoltam magam. Nincs kedvem hozzá.";
			link.l1.go = "exit";
			link.l2 = "Mennyi pénzt akarsz?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "Ah kedvesem, amennyit a pénztárcád megenged és a szíved kíván. Minél több darab pesó, annál messzebbre látok a jövôbe!";
			link.l1 = "100 pezó";
			link.l1.go = "guess_rate_1";
			link.l2 = "500 pezó";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 pezó";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000 pezó";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "Ah, köszönöm a jótékonyságodat, szép fiatal sólyom! Most figyelj:  "+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Ez nagyon érdekes. Megfontolom...","Tényleg? Megfontolom...","Ó, tényleg? Komolyan mondod? Ezt megjegyzem...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "A legcsúnyább és elkerülhetetlen szerencsétlenség vár rád. Átkozott gúnyolódó! Gyûljenek rád a sötét felhôk, és a büntetés találjon rád!";
				link.l1 = "Ha-ha! Tényleg azt hitted, hogy pénzt adok neked, te cigány boszorkány? Tûnj az utamból! Remélem, az Inkvizíció elkap!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "Á, köszönöm, szép fiatal sólymom! Most figyeljetek:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Ez nagyon érdekes. Megfontolom...","Tényleg? Megfontolom...","Ó, tényleg? Komolyan mondod? Hát, ezt megjegyzem...","Hé, máris jobban érzem magam!");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "A legcsúnyább és elkerülhetetlen szerencsétlenség vár rád. Átkozott gúnyolódó! Gyûljenek rád a sötét felhôk, és a büntetés találjon rád!";
				link.l1 = "Ha-ha! Tényleg azt hitted, hogy pénzt adok neked, te cigány boszorkány? Tûnj az utamból! Remélem, az Inkvizíció elkap!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "Ah, köszönöm az ezüstöt, szép fiatal sólyom! Most figyelj:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Ez nagyon érdekes. Megfontolom...","Tényleg? Megfontolom...","Ó, tényleg? Komolyan mondod? Hát, ezt majd megjegyzem...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "A legcsúnyább és elkerülhetetlen szerencsétlenség vár rád. Átkozott gúnyolódó! Gyûljenek rád a sötét felhôk, és a büntetés találjon rád!";
				link.l1 = "Ha-ha! Tényleg azt hitted, hogy pénzt adok neked, te cigány boszorkány? Tûnj az utamból! Remélem, az Inkvizíció elkap!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "Oh la la! Köszönöm a nagylelkûségedet, szép fiatal sólyom! Most figyelj:"+sTemp+"";
				link.l1 = LinkRandPhrase("Heh! Ez nagyon érdekes. Megfontolom...","Tényleg? Megfontolom...","Ó, tényleg? Komolyan mondod? Hát, ezt majd megjegyzem...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "A legcsúnyább és elkerülhetetlen szerencsétlenség vár rád. Átkozott gúnyolódó! Gyûljenek rád a sötét felhôk, és a büntetés találjon rád!";
				link.l1 = "Ha-ha! Tényleg azt hitted, hogy pénzt adok neked, te cigány boszorkány? Tûnj az utamból! Remélem, az Inkvizíció elkap!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("Ó, nem vagyok benne biztos, szépfiú! Nemrég volt egy fickó, aki segítséget kért a patkányok irtásához, aztán valaki megmérgezte az erôdben lévô katonákat. Elég forró lett a helyzet az embereimnek a szigeten, míg az ôrök két hétig vallattak minket, amíg meg nem találták a gyilkost. Egy ellenséges kém volt.",
				                             "És honnan tudhatom biztosan, hogy mi a célod? Talán csak meg akarsz mérgezni egy nemest, akivel túl gyáva vagy ahhoz, hogy becsületes párbajban megküzdj?",
											 "Azt mondták, hogy valaki megmérgezett egy kereskedôt a kocsmában, és ellopta az összes holmiját. A férfi sokáig szenvedett, mielôtt meghalt. A szájából hab jött ki, és lila lett, mint a padlizsán. Te vagy a felelôs ezért, szerelmem?");
				link.l1 = "Ti cigányasszonyok bizonyára szeretitek megosztani a véleményeteket! Ne aggódj kislány, nem fogom megmérgezni az embereket. Az egy nôies módja a gyilkolásnak, nem az én stílusom. A férfiaknak van kardom, de azokkal az átkozott patkányokkal nem tudok bánni.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Megbízható")) Notification_Perk(true, "Trustworthy");
			}
			else
			{
				dialog.text = "Csapdába akarsz csalni! Nem uram, nincs nálam méreg. Növényeim és bájitalaim vannak, de mérgeim nincsenek.";
				link.l1 = "Akkor mindegy. Ne szegezd rám a gonosz szemét.";
				link.l1.go = "exit";
				Notification_Perk(false, "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "Ó, jóképû, milyen gáláns ember! (suttogás) Fizess nekem "+sti(npchar.quest.poison_price)+" dublont.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "Drága... Ajánlom, hogy ez a cucc mûködjön.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "Ez nem lehet! Ugyanezt vettem otthon öt pisztoláért! Ennyi pénzért minden patkányt el tudnék kapni magam is!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "Akkor kapd el ôket magad, és ne zavarj engem. Legközelebb hívom az ôrséget.";
			link.l1 = "Nincs szükség az ôrökre, boszorkány, én elmegyek.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("Mutasd meg a növényt, kedvesem... Hm... Azt hiszem, megvehetem tôled. Háromszáz darab pesó, rendben?","Mutasd meg, szépfiú... Heh... Nos, kétszáz és felet tudok érte fizetni.","Lássuk csak... Oh! Egy érdekes példa! Kétszáz pezó! Megegyeztünk?")"";
			link.l1 = LinkRandPhrase("Uramisten... sötétszemû, én nem vagyok valami vidéki paraszt. Ismerem ezt a növényt. Ez mangarosa...","Ó, tényleg?! Ez egy tökéletes mangarosa példány. Ne próbálj átverni, gyppo.","Aha, és azt hiszed, hogy ilyen csekély összegért odaadom neked ezt a mangarosát.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "Jól van, jól van, szépfiú. Látom, hogy tudsz valamit errôl a növényrôl. Ötven dublont. Add ide.";
			link.l1 = "Várj egy kicsit! Tudni akarom, hogyan és mire lehet használni. Tudsz errôl mesélni? Az összes embered hajlandó sok aranyat fizetni ezért a kis bokorért!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "Hm... Azt hiszem, nem olyan rossz, ha mesélek róla egy kicsit. Különleges képességek nélkül semmit sem fogsz tudni kezdeni ezzel a növénnyel.";
				link.l1 = "Hallgatlak.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("Az én népem sok aranyat fizethetne, de soha nem fedné fel a titkait.","Az arany az arany, a titkok pedig titkok, fiatalember... ","Igen, hajlandóak vagyunk fizetni, de nem áruljuk el.")+"Szóval eladod nekem a mangarozádat? Ötven dublont adunk érte, senki sem fizet többet.";
				link.l1 = "Oh, rendben... Nekem mindenesetre mûködik. Ötven dublont. Vedd el.";
				link.l1.go = "mangarosa_trade";
				link.l2 = "Értsd meg, nem akarom eladni. Tudni akarom, miért van rá szükséged. Oszd meg velem a tudásodat, és én ingyen odaadom neked.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Fogd az érméidet, fiatal sólyom. És még valami, hozz nekünk még több ilyen növényt. De csak egy-egy növénnyel tudjuk megvenni ôket, mert nem viszünk magunkkal nagy összegeket. Az ôrök nem bíznak a fajtánkban, és szeretnek zaklatni minket...";
			link.l1 = "Jól van, rendben. Ha találok még, hozok.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("Kizárt dolog! Ha nem akarod eladni - akkor ne tedd. Nem mondok neked semmit.","Nem fogom felfedni a titkainkat egy kívülállónak! (spits) Nem akarod eladni? A pokolba veled.","Barátom, ez nem a te fülednek való. Nem akarod eladni ötven dublónért? Menj és add el a kereskedôlánynak kétszáz pezóért.");
			link.l1 = LinkRandPhrase("Akkor kár érted! Egy másik embere úgyis elmondja majd nekem. És ô kapja majd ezt a növényt ajándékba. Viszlát!","Miért vagy ilyen makacs? Ha te nem mondod el, akkor a másik mondja el. És ô kapja meg ezt a mangarosát ajándékba. Viszlát.","A leheleted bûzlik a fokhagymától. Végül is megkapom, amit akarok. Egy másik fajtársad beszédesebb lesz, és ingyen megkapja a növényt. Viszlát.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "És miért kérdezed, sólyom?! Persze! Add ide nekem.";
			link.l1 = "Adj ötven dublont.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "Oups! Úgy tûnik, elvesztettem vagy a hajón felejtettem. Milyen kár. Viszlát...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ne aggódj, nem foglak becsapni. Fogd az érméket.";
			link.l1 = "Fogd a mangarosát. Hozok még, ha találok.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "A rügyeket ilyen különleges módon ôröljük, majd megszárítjuk, kiszedjük a magokat és a szárakat, majd összekeverjük a dohánnyal, megtömjük a pipánkat és elszívjuk a keveréket. És egy... felejthetetlen hatást érünk el. Mint az alkoholos mámor, de utána nem fáj a fejünk. Egy növény elég két tucatnyi pipához.";
			link.l1 = "Most már értem! Meg tudod tanítani nekem ezt a titkos technikát? Jól meg tudom fizetni...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "Fiatal sólyom, bízz bennem, erre nincs szükséged. Ne keveredj bele, a növény tönkretesz téged. Tompítja az agyat és elhízol tôle. Ne is kérdezz engem. De... Egy bátor férfit látok magam elôtt, karddal, egy tengerész... talán még kapitány is?";
			link.l1 = "Igazad van.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "Akkor hallgassa meg itt. Mangarosa sokkal nemesebb dolgokra is felhasználható, és talán hasznosnak találod. Egy gyógyítónk ismeri az összes titkát. Ô az, akire szükséged van\nAdd ide a növényt, és én megmondom a nevét, és hogy hol találod meg. Bár az már a te problémád lesz, hogy meggyôzd, hogy ossza meg veled a titkait.";
			link.l1 = "Rendben. Fogd a növényt, és mondd el, hogyan találom meg a cigánymágusodat.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "A neve Amelia. Egyedül él egy kis házban a dûnék között, nem messze a tengertôl, valahol a spanyol fôsziget délnyugati partján, ahogy a bölcsek mondják.";
			link.l1 = "Ó, az Isten szerelmére, nem tudna pontosabban fogalmazni?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "Te tengerész vagy, bátor sólyom, én pedig nem. Keresd meg ôt ott, ahol mondtam. Az otthona tényleg közel van a tengerparthoz. Közel van egy öbölhöz, közvetlenül a Spanyol-fô délnyugati részén - a tengerészek biztosan ismerik.";
			link.l1 = "Rendben, megpróbálom megtalálni...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "Vigyél hozzá egy Mangarosát, különben nem is áll szóba veled. És ne felejtsd el a dublonokat sem elhozni, ne is hidd, hogy ingyen tanít majd!";
			link.l1 = "Micsoda kapzsiság. Ezt meg fogom fontolni. Köszönöm a történetedet!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Nem, " + GetSexPhrase("kedves", "szépség") + ", nem én vagyok az, akire szükséged van, hanem " + sld.name + ". Ô most itt van a városban. Nemrég láttam ôt.";
			link.l1 = "Köszönöm.";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Figyelj rám bátor sólyom, lehet, hogy cigány vagyok, de még mi is elítéljük a nyílt erôszakot. Kérlek, tedd hüvelybe a kardod.", "Figyelj rám bátor sólyom, mint a város polgára arra kérlek, hogy tedd hüvelybe a pengédet.");
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "Szerencséd lesz, bátor ifjú sólyom, holnap szerencséd lesz a kártyával!" break;
		case 1: sText = "a szerencse kegyes lesz hozzád a kereskedô üzletedben, kapitány!" break;
		case 2: sText = "szerencsétlenség vár rád a nyílt tengeren, csak rád vár, várj három napot!" break;
		case 3: sText = "Látom, hogy segítséget kell kérned a legközelebbi hozzátartozóidtól, egyedül nem fogsz boldogulni a következô harcodban!" break;
		case 4: sText = "Menj és gyújts gyertyát egy templomban, megátkozott az ellenséged! Isten segítsége nélkül nem fogsz boldogulni!" break;
		case 5: sText = "hamarosan sokat fogsz veszíteni, sólymom, de ne ess kétségbe és ne reménykedj magadban, kérj segítséget a barátaidtól..." break;
		case 6: sText = "súlyos veszteség vár rád a tengeren, de úgy látom, hogy te, kapitány, képes leszel átvészelni, még ha nem is kapod meg, amit akarsz." break;
		case 7: sText = "A szerencsétlenség céljába léptél, kapitány! Látogasson el egy bordélyházba, és pihenjen egy kicsit." break;
		case 8: sText = "Meg fogja kapni, amit akar, kapitány, de semmi jót ne várjon tôle. Mindaz, amit olyan szenvedélyesen akartál, kapitány, csak rosszat fog hozni, úgyhogy jobb, ha azonnal megváltoztatod a terveidet." break;
		case 9: sText = "Látom, hogy az arcodon van egy jel, a végsô szerencse jele. Többet fogsz kapni, mint amire számítottál, fiatalember!" break;
		case 10: sText = "Még egyszer értékelned kell a kívánságodat, és döntened kell. Tényleg szükséged van rá? A sorsod lehetôséget ad neked az újragondolásra." break;
		case 11: sText = "Ez ritka szerencse, nem minden nap van esélyünk újragondolni. Pihenj pár napot, okoskodj, gondolkodj el a dolgokon. Ne siess a halálba!" break;
		case 12: sText = "bár minden erôfeszítésed nem hozza meg a várt eredményt, ne ess kétségbe, ifjú sólyom, nagy szerencse vár rád a legváratlanabb napon, ne veszítsd el!" break;
		case 13: sText = "a problémád nem fog pozitívan megoldódni, de te makacs vagy, és megkapod, amit akarsz, de talán nem onnan, ahonnan vártad." break;
		case 14: sText = "Jobb, ha elfelejted az üzletet, amire készülsz. Ebben sosem lesz szerencséd, és ha folytatni fogod, akkor talán a legközelebbi embereidet bántják vagy megölik." break;
		case 15: sText = "van egy esemény, ami rád vár, kapitány, és ez teljesen meg fogja változtatni az életedet. A mostani aggodalmaid ezután minden jelentôségüket elveszítik számodra." break;
		case 16: sText = "az álmodhoz vezetô úton veszély leselkedik rád, kapitány, és igazán szerencsésnek kell lenned, ha súlyos veszteségek nélkül el tudod érni, amit akarsz. Jobb, ha elfordulsz, és elfelejted elérhetetlen álmodat. Vagy talán ezt a sorsot is ki lehet csapni, ha most éppen kártyában vagy kockában veszítesz..." break;
		case 17: sText = "Olyan erôs erôt látok benned, mint egy szikla, és olyan fényt, mint az északi csillag, amely vezeti az embereket. Jó hírek várnak rád!" break;
		case 18: sText = "rossz jel emelkedik az utadon, félj a gonosz szemtôl, és tarts hûséges embereket magad mellett." break;
		case 19: sText = "szerencsés esemény emelkedik az utadba, közvetlenül a saját hátad mögött. Keresse a jót, ami éppen a keze ügyébe kerül, és ne hajszolja az elérhetetlent." break;
	}
	return sText;
}
