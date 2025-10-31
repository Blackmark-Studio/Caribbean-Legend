// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	

	string iDay, iMonth, sTemp, sMoney, attrL;
	
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
	
	int iMoney, iQuantityGoods, iTradeGoods, iTmp;
	
	bool  ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;
	
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

	if(!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}
    
	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c";
	if(LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	
	string attrLoc   = Dialog.CurrentNode;
	
	if(HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("A városban riadó van, és mindenki téged keres. Én a helyedben nem maradnék ott.", "Az összes városôr téged keresve pásztázza a várost. Nem vagyok bolond, és nem állok szóba veled!", "Fuss, "+ GetSexPhrase("pajtás","lány") +", mielôtt a katonák szitává változtatnak..."), 
					LinkRandPhrase("Mit akarsz, "+ GetSexPhrase("gazember","gazember") +"?! A városôrök már a szagodat érzik, nem jutsz messzire, "+ GetSexPhrase("mocskos kalóz","gyilkos mocsok") +"!", "mocskos gyilkos, azonnal hagyd el a házamat! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("görény","bûzös") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, a riasztó nekem sosem jelent problémát...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Fogd be a kibaszott pofád, " + GetWorkTypeOfMan(npchar, "") + ", vagy kitépem a mocskos nyelved!!!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", és mindenki ott - azért vannak itt, hogy kalózokat fogjanak! Mondok én neked valamit, haver: ülj csendben, és nem fogsz meghalni..."));
				link.l1.go = "fight";
				break;
			}
			if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
			{
				dialog.text = RandPhraseSimple("Hé, te szemétláda! Azt hiszed, elveheted, amit csak akarsz? Dehogyis! Srácok! Fegyverbe! Vágjátok le a pszichopatát!", "Ha akarsz valamit, vedd meg, te vadállat! Most megmutatom neked, hogy mi micsoda! Srácok, fogjátok a fegyvereiteket! Riadó!");
				link.l1 = RandPhraseSimple("Huh? Mi az?", "Uh, miért csinálod ezt?");
				link.l1.go = "fight";
				bDisableFastReload = true;//закрыть переход
				pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
				pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
				pchar.quest.pirate_in_town.function = "TownPirate_battle";
				break;
			}
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				//Jason --> мини-квест Дефицитный товар
				if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Egy tétel európai bort szeretnék venni tôled - ötven-hatvan palackot. Azt mondták, hogy van belôle elég a raktárban."; 
					link.l13.go = "Wine_Trader";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Üdvözlöm újra. Kérem, nézze meg ezt a levelet - talán átgondolná az álláspontját, hogy bort adjon el nekem?"; 
					link.l13.go = "Wine_Repeat2";
				}
				if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
				{
					link.l13 = "Megint én vagyok. Folytathatnánk a megszakított borüzletünket? Sikerült elég pénzt összegyûjtenem."; 
					link.l13.go = "Wine_Price";
				}
				// <-- мини-квест Дефицитный товар
				dialog.text = "Szeretne vásárolni valamit, monsieur?";
				Link.l1 = "Persze, hogy akartam - mi másra vannak a boltok? Mutassa az áruját.";
				Link.l1.go = "trade_1";
				Link.l2 = "Egy bizonyos üzleti céllal jöttem...";
				Link.l2.go = "quests";
				Link.l3 = "Sajnálom, de mennem kell.";
				Link.l3.go = "exit";
				// туториал Мартиника
				if(NPChar.City == "FortFrance")
				{
					if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
					{
						Link.l2 = "Figyeljen, uram, munkát keresek. Nem fôállású munkát vagy zsákos rakományt cipelô munkát, hanem inkább úgymond megbízásokat teljesítek. Szüksége van véletlenül segítségre?";
						Link.l2.go = "Sharlie_storehelper";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
					{
						Link.l2 = "Elvégeztem a küldetését. Megtaláltam Gralam Lavoie-t.";
						Link.l2.go = "Sharlie_storehelper_2";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
					{
						Link.l2 = "Bemutatom az új asszisztensét, monsieur.";
						Link.l2.go = "Sharlie_storehelper_11";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
					{
						Link.l2 = "Megint én vagyok, uram. A jutalmamért jöttem.";
						Link.l2.go = "Sharlie_storehelper_13";
					}
					if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
					{
						link.l4 = "Nézze meg ezeket a fülbevalókat, uram. Egy bandita testén találtam, akit a dzsungelben öltek meg. Ez egyértelmûen egy olyan ékszerész munkája, aki biztos vagyok benne, hogy nem idevalósi. Tud valamit mondani ezekrôl a fülbevalókról?";
						link.l4.go = "Sharlie_junglejew";
					}
				}
				break;
			}			
			//<-- Бремя гасконца
			
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Kapitány, köszönöm, hogy megmentett.";
				Link.l1 = "Ó, szívesen.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Mi a helyzet, kapitány? Elvesztett valamit? Miért rohangálsz így a boltomban?";
				Link.l1 = "Nos, képzelje csak el - tényleg eljöttem! Hol van az az átkozott Gerard LeCroix? Elvégeztem az összes feladatot, amit Florian Shoke rám bízott, és, nyelje el a cápa az egészet, rohadt nehéz volt ezt megtennem! És most, amikor eljöttem a jutalmamért, kiderült, hogy ez a madár elrepült!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Hogy is mondjam... Elveszett. Nem láttad az ügyfelemet? A neve Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Kapitány, szeretnék egy szívességet kérni. Segítene nekem?";
				link.l1 = "Hogyan segíthetnék?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition			
            dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Örülök, hogy megismerhetem, uram! Új vagy ezeken a földeken?","Üdvözlöm, kapitány! A boltom az ön szolgálatára áll, uram.","Uram, kérem, jöjjön be! Örömmel kínálom Önnek a legjobb árukat, amiket ezen a szigetcsoporton kaphat."), LinkRandPhrase("Ó, kapitány úr! Az összes francia gyarmat legjobb árui - itt és most, kizárólag az Ön számára!","Micsoda kellemes találkozás, monsieur! A legjobb üzlet, amely a legjobb francia árukat kínálja - az Ön szolgálatára!","Találkoztunk már korábban, kapitány úr? Tudja, az én boltom olyan jó, mint az anyaország legjobb üzletei!"), LinkRandPhrase("Oh! Senor kapitány! Annyira örülök, hogy az üzletemben látom!","Örülök, hogy egy ilyen ragyogó caballerót üdvözölhetek a spanyol gyarmatok legjobb üzletében!","Ó, nemes hidalgo! Maga a sors hozta szerény boltomba! Itt mindent megtalálsz, amire csak vágysz!"),LinkRandPhrase("Jó napot, mynheer kapitány. Ez az elsô látogatása itt?","Hello, mynheer. Most jár itt elôször? Biztosíthatom, hogy holland árucikkeink minôsége kellemesen meg fogja lepni!","Kérem, jöjjön be, mynheer kapitány! A legjobb árucikkek a legalacsonyabb áron - ez a holland kereskedelmi szokás!"));
			Link.l1 = LinkRandPhrase("Én is örülök, hogy megismerhettem. A nevem "+GetFullName(pchar)+" és eléggé új vagyok ezeken a földeken. Nos, mutasd meg nekem a szigetvilág gazdagságát!","Én is örülök, hogy megismerhetlek. Én vagyok "+GetFullName(pchar)+". a hajó kapitánya '"+pchar.ship.name+"'. Szóval, mik a menô ajánlatok?",""+GetFullName(pchar)+", hajóskapitány '"+pchar.ship.name+"', örülök, hogy megismertem. Szóval, mit tudsz ajánlani nekem?");
			link.l1.go = "node_1";
			
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_store")
			{
				dialog.text = "Helen kapitány! Mindig örömömre szolgál.";
				link.l1 = "Ahogy nekem is, köszönöm.";
				link.l1.go = "Helen_node_1";
			}
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("A városban riadó van, és mindenki téged keres. A helyedben én nem maradnék ott.", "Az összes városôr téged keresve pásztázza a várost. Nem vagyok bolond, és nem állok szóba veled!", "Fuss, "+ GetSexPhrase("pajtás","lány") +", mielôtt a katonák szitává változtatnak..."), 
					LinkRandPhrase("Mit akarsz, "+ GetSexPhrase("gazember","gazember") +"?! A városôrök már a szagodat fogják, nem jutsz messzire, "+ GetSexPhrase("mocskos kalóz","gyilkos mocsok") +"!", "mocskos gyilkos, azonnal hagyd el a házamat! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("görény","bûzös") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, a riasztó nekem sosem jelent problémát...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Fogd be a szád, " + GetWorkTypeOfMan(npchar, "") + ", vagy kitépem a mocskos nyelvedet!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", és mindenki ott - azért vannak itt, hogy kalózokat fogjanak! Mondok én neked valamit, haver: ülj csendben, és nem fogsz meghalni..."));
				link.l1.go = "fight";
				break;
			}
            
			//--> Jason, Сомнительное предложение
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
			{
				dialog.text = "Kérem, bocsásson meg, de most nincs idôm magára.";
				link.l1 = "Igen, persze. Akkor majd máskor beugrom.";
				link.l1.go = "exit";
				break;
			}
			//<-- Сомнительное предложение
            
			// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = "Kapitány, köszönöm, hogy megmentett.";
				Link.l1 = "Ó, szívesen.";
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}
			// Карибские нравы
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Mi a helyzet, kapitány? Elvesztett valamit? Miért rohangálsz így a boltomban?";
				Link.l1 = "Hát, képzeld csak el - én tényleg meghaltam! Hol van az az átkozott Gerard LeCroix? Elvégeztem minden feladatot, amit Florian Shoke adott nekem, és - nyelje el a cápa egészben - rohadt nehéz dolgom volt! És most, amikor eljöttem a jutalmamért, kiderült, hogy ez a madár elrepült!";
				Link.l1.go = "trial";
				// belamour legendary edition -->
				Link.l2 = "Hogy is mondjam... Elveszett. Nem láttad az ügyfelemet? A neve Gerard LeCroix.";
				Link.l2.go = "trialA";
				//<-- legendary edition
				DelLandQuestMark(npchar);
				break;
			}
 			// belamour legendary edition Бесчестный конкурент -->
			if(!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
			{
				dialog.text = "Kapitány, szeretnék egy szívességet kérni. Segítene nekem?";
				link.l1 = "Hogyan segíthetnék?"; 
				link.l1.go = "Shadowtrader_begin";
				break;
			}
			// <-- legendary edition           
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Nézd csak, ki van ott! Nos, ahogy mondják, a pénznek nincs szaga, szóval jöjjön be, kapitány, és cseréljünk...","Nem mondhatom, hogy örülök, hogy látlak, "+GetFullName(pchar)+"... De attól még tudok veled kereskedni.","He-he... Nos, nem hívnám meg az otthonomba, kapitány - de a boltom továbbra is a rendelkezésére áll."),LinkRandPhrase("Ó, nézd csak, ki van ott! Hát nem "+GetFullName(pchar)+"! Akarsz cserélni, vagy csak ingyen elvinni pár cuccot? Hé, csak vicceltem...","Nem mondhatom, hogy örülök, hogy itt látlak, "+GetAddress_Form(NPChar)+". De ha van pénzed költeni - gyere be, gyere be...","Akarsz cserélni, kapitány "+GetFullName(pchar)+"? Ha igen, akkor nem tudnád gyorsan elintézni? A többi vásárló elkerüli önt, és ez rosszat tesz az üzletemnek,"),LinkRandPhrase("Akar cserélni, mynheer? Csak egy pillanat, és készpénzre váltom - tudod, vannak itt kétes alakok... Természetesen nem rád gondolok, kapitány!","Ha a nyílt tengeren látnálak, "+GetAddress_Form(NPChar)+", valószínûleg vitorlákat rendelnék hozzá... De itt, a boltomban, fel tudom ajánlani neked cserére.","sapka, rögtön figyelmeztetlek: ha az anyag vérfoltos és a kávé puskaporszagú, nem veszem el. Egyébként nézd meg és válassz.")),LinkRandPhrase(LinkRandPhrase("És örülök, hogy újra üdvözölhetlek, "+GetAddress_Form(NPChar)+"! Vásárlás vagy eladás - mindig szívesen segítek.","Könyörgöm, "+GetAddress_Form(NPChar)+", gyere be! Mindig örülök, ha itt látom kedvenc vásárlómat. Mi legyen ezúttal - vásárlás vagy eladás?","Ó, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Annyira örülök, hogy újra látlak! Mi lesz ezúttal - vásárlás vagy eladás?"),LinkRandPhrase("Tetszik a portékánk, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Mindig állok rendelkezésére - nézze meg és válasszon.","Hello, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Örülök, hogy újra látlak! Szeretné megnézni a választékunkat?","Örülök, hogy látom, kapitány! Tudtam, hogy tetszeni fognak a minôségi árucikkeink. Szeretné megnézni, mi újság?"),LinkRandPhrase("Ó, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Kérem, jöjjön be! Minden árut csak önnek - és ebbôl az alkalomból nagy kedvezményekkel!","Kapitány "+GetFullName(pchar)+", ismét megörvendeztetett a látogatásával! Kérem, válasszon, amit csak szeretne!","Ezúttal mit szeretne, kapitány úr? Örülök, hogy még mindig emlékszel, hogyan találsz meg. Nálunk minden áru megtalálható, amire szüksége lehet - a legjobb minôségben!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Így üdvözölsz engem, haver? Nos, ezt megjegyzem, ha a tengeren találkozunk... Ne reszkess, csak vicceltem. Mutasd meg, mit tudsz.","Rendben, haver. Lehet, hogy szükségem van az árudra, de a nyelvedre nem. Tudod tartani, vagy segítségre lesz szükséged? Fogd be és mutasd meg az árudat."),RandPhraseSimple("Lépjünk közelebb az üzlethez, árus. Nincs idôm erkölcsi kérdéseket megvitatni veled, úgyhogy kereskedjünk, mint tisztességes emberek.","Nyugalom, haver. Viccelni jó, de ne feledd, hogy tudok dühös lenni... Szóval ne idegesíts, hanem mutasd meg az árudat.")),RandPhraseSimple(RandPhraseSimple("Mindig örülök, ha meglátogatlak, haver. Mi van nálad, ami megérné a figyelmemet?","Mindig örülök, hogy látlak, haver. Szóval, mi újság van a tengeri vándoroknak, akik hónapok óta nem jártak a szárazföldön?"),RandPhraseSimple("És ismét a "+XI_ConvertString("Colony"+npchar.City+"Acc")+"vagyok ! Örülök, hogy nem azért voltam itt, hogy elfelejtsem. De maradt valami a raktáraitokban nekem? Minden rendben van?","Hogyhogy nem jöttél? Mindig jobban örülök neked. Nos, mi van nálad?")));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar,
			                                         pcharrepphrase(RandPhraseSimple("Mindenki a fedélzetre! ","Ellenôrzést tartani! ") +LinkRandPhrase("Mit keres egy "+ GetSexPhrase("úriember","úriember, ó, bocsánat - egy szerencsés hölgy") +" a boltomban, he-he?",
													                                 "Micsoda meglepetés egy szegény öreg boltosnak! He-he!", "Szóval, milyen szép szél hozta önt a boltomba?"),
            														LinkRandPhrase("Nyissátok ki a kapukat!", "Horgokat oldalra!","Hajózzatok egyenesen elôre!")+RandPhraseSimple(" Itt megtalálod"," A boltomban")
																	+LinkRandPhrase(" a legjobb árak vannak az egész szigeten."," kiváló áruválaszték."," áruk a legjobb minôségûek.")
																	+RandPhraseSimple(" állok rendelkezésére"," Bármire vágyik")+", kapitány!"),
													 pcharrepphrase(RandPhraseSimple("Bármilyen árut "+ GetSexPhrase("uraknak","uraknak és hölgyeknek") +" szerencse! He-he! Amíg fel nem akasztják ôket a napon száradni!",
													                                 "A szél lengeti a kikötôben a felakasztottakat, és viszi a láncok csörgését. De a pénznek nincs szaga, ugye?"),
                 												"Szeretné " +LinkRandPhrase("legjobb áruját " + NationNameGenitive(sti(NPChar.nation)),"megvenni vagy eladni a rakományát", "kapott egy jövedelmezô szállítmányt?")
																	+RandPhraseSimple("? Állok rendelkezésére!","? Üzletem az Ön szolgálatára áll!")
																	+RandPhraseSimple(" Örülök, hogy látlak"," Örülj magadnak") +", kapitány!")),
				                                  NPCharRepPhrase(npchar,
												  	 pcharrepphrase("Ha a tanácsomra vagy kíváncsi, kapitány - ne sajnáld a pénzt a grapeshotra. Tudod, a halottakat sokkal könnyebb átkutatni!",
													                "rögtön észrevettem, hogy te egy "+ GetSexPhrase("ravasz pajtás vagy","ravasz lány") +". " +RandPhraseSimple("De most már látom, hogy egy igazi "+ GetSexPhrase("hôs vagy","fenegyerek") +".", "Fiatal vagy még, de "
																	+RandPhraseSimple("az eszed is megvan.", "téged biztosan nem lehet egykönnyen becsapni."))),
													 pcharrepphrase("hajlandó vagyok megvenni tôled a zsákmányolt zsákmányok összes rakományát. Akarsz ezüsttel vagy arannyal? Az a cucc mindig drága.",
													                "A kereskedelmi hajózás jövedelmezô üzlet, kapitány " + GetFullName(pchar)+", nem igaz?")),
												  NPCharRepPhrase(npchar,
												     RandPhraseSimple("Becsomagoltuk 'em mindet egy hálóba' tight Kétszer tíz fordulatnyi kötélhurokkal És átemeltük 'em és eltûntünk a szemünk elôl! " ,
													   RandPhraseSimple("Tizenöt ember egy halott ember mellkasán!","Italt és az ördög tette a többit!") +" Yo ho ho és egy üveg rum! ")
													   +RandPhraseSimple("Mi a helyzet, kapitány?", "Szeretne venni valamit, kapitány?"),
													 pcharrepphrase("Úgy látom, maga aztán tud alkudozni, kapitány " + GetFullName(pchar)+". Mivel ön visszatérô vásárló, nagyon jó árat ajánlok önnek!",
													                "Rendben, kapitány " + GetFullName(pchar)+", az ön iránti tiszteletbôl egy kicsit többet tudok ajánlani! Mit szeretne?")),
												  NPCharRepPhrase(npchar,
												     "Esküszöm, hányingerem van attól, hogy magával beszélgetek. "
													 +LinkRandPhrase("Vegyen egy pár mogyorót. A disznók szeretik azt a cuccot. ","Azt várod, hogy itt valaki rummal fényesítse a csizmádat? ",
													 pcharrepphrase("Ismerem a fajtádat. Töltsd meg magad rummal - és egyenesen az akasztófára.","Vajon hogyan engedte meg anyád, hogy matróz legyél! Tengerész lett belôled! Sokkal jobb szabó lennél...")),
													 pcharrepphrase(RandPhraseSimple("Azt hittem, hogy ","reméltem, hogy ")+RandPhraseSimple("végleg elhagytad a szigetünket.","hogy soha többé nem látlak.")
													 +RandPhraseSimple(" A halottak úgy lógnak a nyakadon, mint a malomkövek..."," Hány tengerészt hagytál megrohadni a korallok között?!"),
													 "Kapitány " + GetFullName(pchar)+", a kereskedelem iránti szenvedélyed minden várakozásomat felülmúlta!"
													 +RandPhraseSimple(" Szeretnél az utolsó pillanatban vásárolni, mielôtt kihajózol?", " Valami különlegeset keres?"))),
										"cycle", 10, npchar, Dialog.CurrentNode);
			// belamour legendary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
			{
				if(pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
				{
					dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Nézd csak, ki van ott! Nos, ahogy mondják, a pénznek nincs szaga, szóval jöjjön be, kapitány, és cseréljünk...","Nem mondhatom, hogy örülök, hogy látlak, "+GetFullName(pchar)+"... De attól még tudok veled kereskedni.","He-he... Nos, nem hívnám meg az otthonomba, kapitány - de a boltom továbbra is a rendelkezésére áll."),LinkRandPhrase("Ó, nézd csak, ki van ott! Hát nem "+GetFullName(pchar)+"! Akarsz cserélni, vagy csak ingyen elvinni pár cuccot? Hé, csak vicceltem...","Nem mondhatom, hogy örülök, hogy itt látlak, "+GetAddress_Form(NPChar)+". De ha van pénzed költeni - gyere be, gyere be...","Akarsz cserélni, kapitány "+GetFullName(pchar)+"? Ha igen, akkor nem tudnád gyorsan elintézni? A többi vásárló elkerüli önt, és ez rosszat tesz az üzletemnek,"),LinkRandPhrase("Akar cserélni, mynheer? Csak egy pillanat, és készpénzre váltom - tudod, vannak itt kétes alakok... Természetesen nem rád gondolok, kapitány!","Ha a nyílt tengeren látnálak, "+GetAddress_Form(NPChar)+", valószínûleg vitorlákat rendelnék hozzá... De itt, a boltomban, fel tudom ajánlani neked cserére.","sapka, rögtön figyelmeztetlek: ha az anyag vérfoltos és a kávé puskaporszagú, nem veszem el. Egyébként nézd meg és válassz.")),LinkRandPhrase(LinkRandPhrase("És örülök, hogy újra üdvözölhetlek, "+GetAddress_Form(NPChar)+"! Vásárlás vagy eladás - mindig szívesen segítek.","Könyörgöm, "+GetAddress_Form(NPChar)+", gyere be! Mindig örülök, ha itt látom kedvenc vásárlómat. Mi legyen ezúttal - vásárlás vagy eladás?","Ó, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Annyira örülök, hogy újra látlak! Mi lesz ezúttal - vásárlás vagy eladás?"),LinkRandPhrase("Tetszik a portékánk, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Mindig állok rendelkezésére - nézze meg és válasszon.","Hello, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Örülök, hogy újra látlak! Szeretné megnézni a választékunkat?","Örülök, hogy látom, kapitány! Tudtam, hogy tetszeni fognak a minôségi árucikkeink. Szeretné megnézni, mi újság?"),LinkRandPhrase("Ó, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Kérem, jöjjön be! Minden árut csak önnek - és ebbôl az alkalomból nagy kedvezményekkel!","Kapitány "+GetFullName(pchar)+", ismét megörvendeztetett a látogatásával! Kérem, válasszon, amit csak szeretne!","Ezúttal mit szeretne, kapitány úr? Örülök, hogy még mindig emlékszel, hogyan találsz meg. Nálunk minden áru megtalálható, amire szüksége lehet - a legjobb minôségben!")));
					link.l14 = "Figyeljen, most indulok Porto Bello-ba, és szeretnék egy szállítmány kávét és kakaót vásárolni önöktôl. Mondjuk, háromszáz egységet mindkettôbôl."; 
					link.l14.go = "SharkGoldFleet";
				}
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Nézd csak, ki van ott! Nos, ahogy mondják, a pénznek nincs szaga, szóval jöjjön be, kapitány, és cseréljünk...","Nem mondhatom, hogy örülök, hogy látlak, "+GetFullName(pchar)+"... De attól még tudok veled kereskedni.","He-he... Nos, nem hívnám meg az otthonomba, kapitány - de a boltom továbbra is a rendelkezésére áll."),LinkRandPhrase("Ó, nézd csak, ki van ott! Hát nem "+GetFullName(pchar)+"! Akarsz cserélni, vagy csak ingyen elvinni pár cuccot? Hé, csak vicceltem...","Nem mondhatom, hogy örülök, hogy itt látlak, "+GetAddress_Form(NPChar)+". De ha van pénzed költeni - gyere be, gyere be...","Akarsz cserélni, kapitány "+GetFullName(pchar)+"? Ha igen, akkor nem tudnád gyorsan elintézni? A többi vásárló elkerüli önt, és ez rosszat tesz az üzletemnek,"),LinkRandPhrase("Akar cserélni, mynheer? Csak egy pillanat, és készpénzre váltom - tudod, vannak itt kétes alakok... Természetesen nem rád gondolok, kapitány!","Ha a nyílt tengeren látnálak, "+GetAddress_Form(NPChar)+", valószínûleg vitorlákat rendelnék hozzá... De itt, a boltomban, fel tudom ajánlani neked cserére.","sapka, rögtön figyelmeztetlek: ha az anyag vérfoltos és a kávé puskaporszagú, nem veszem el. Egyébként nézd meg és válassz.")),LinkRandPhrase(LinkRandPhrase("És örülök, hogy újra üdvözölhetlek, "+GetAddress_Form(NPChar)+"! Vásárlás vagy eladás - mindig szívesen segítek.","Könyörgöm, "+GetAddress_Form(NPChar)+", gyere be! Mindig örülök, ha itt látom kedvenc vásárlómat. Mi legyen ezúttal - vásárlás vagy eladás?","Ó, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Annyira örülök, hogy újra látlak! Mi lesz ezúttal - vásárlás vagy eladás?"),LinkRandPhrase("Tetszik a portékánk, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"? Mindig állok rendelkezésére - nézze meg és válasszon.","Hello, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+". Örülök, hogy újra látlak! Szeretné megnézni a választékunkat?","Örülök, hogy látom, kapitány! Tudtam, hogy tetszeni fognak a minôségi árucikkeink. Szeretné megnézni, mi újság?"),LinkRandPhrase("Ó, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Kérem, jöjjön be! Minden árut csak önnek - és ebbôl az alkalomból nagy kedvezményekkel!","Kapitány "+GetFullName(pchar)+", ismét megörvendeztetett a látogatásával! Kérem, válasszon, amit csak szeretne!","Ezúttal mit szeretne, kapitány úr? Örülök, hogy még mindig emlékszel, hogyan találsz meg. Nálunk minden áru megtalálható, amire szüksége lehet - a legjobb minôségben!")));
				link.l14 = "Kávéért és kakaóért jöttem. "; 
				link.l14.go = "SharkGoldFleet_again";
			}
										
			// <-- на пару с Акулой
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Mutasd meg, mit tudsz, te vén kalóz!",
													               "Csak meg akartam nézni a portékádat, jóember."),
													pcharrepphrase("Az akasztófára esküszöm, " +GetFullName(npchar)+", nem hagyom, hogy elriasszon! Mutasd meg az árudat, most azonnal!",
													               "Nézzük meg az árudat, " +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Az biztos! A halottak nem harapnak! Nos, mi van a rakományodban?",
													               "Jobb, ha a dolgodra térsz, jóember. Milyen árut tudsz nekem kínálni?"),
												    pcharrepphrase("Eljön majd a nap, amikor te leszel a zsákmányom, he-he. Csak vicceltem. Mutasd meg az árudat.",
													               "Beszéljük meg a kereskedelmi ügyeinket, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Mit akarok? Venni akarok valamit!",
													               "Az ivás a sírba visz, " +GetFullName(npchar)+ ". Szeretném megnézni az áruját."),
												    pcharrepphrase("Ismerem a kedvezményeidet! Két kiló kakaó három kiló áráért! Most pedig mutassa meg az áruját!",
													               "Ez mindig jó. Akkor alkudozzunk.")),
											  "Mutasd meg az árudat! A legkevesebbet mond, a leghamarabb javít. Sietek.",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Ó, nagyon szeretnék leszúrni valakit, Rendben, térjünk a tárgyra.",
													               "Térjünk rá másra, jóember."),
													pcharrepphrase("Caramba! Én egy másik ügy miatt vagyok itt!",
													               "Egy bizonyos üzletrôl szeretnék beszélni veled, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Nekem dolgom van veled, öreg kalóz!",
													               "Térjünk rá az üzletre, pajtás!"),
													pcharrepphrase("Az ördögre esküszöm, nem fogsz átverni, gazember! Nekem más dolgom van veled!",
													               "Teljesen egyetértek, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", más ügyeket akartam megbeszélni veled.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Már fel is töltötted? Nekem dolgom van veled.",
													               "Nem kereskedni jöttem ide, jóember. Más dolgom van."),
													pcharrepphrase("Az ilyen árakért sújtson le rád a mennydörgés! Nekem veled van üzletem.",
													               "A kedvezmények mindig szépek, " + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", de nekem más dolgom van veled.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Fogd be a szád, te vén részeges, nekem veled van üzletem",
													               "A rumtól vagy rosszul, gondolom. Nem mintha én is kedvelném magadat. Térjünk rá az üzletre."),
													pcharrepphrase("Már így is átvertél, gazember! Nekem dolgom van veled.",
													               "Az iróniád nem helyénvaló. Más dolgom van veled.")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("First business, then merry-making. I want to ask you something.",
													               "Not right now. I need information."),
													pcharrepphrase("To hell with your prices! First you're gonna tell me everything I need.",
													               "With pleasure. I wanted to ask something.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Thanks for the advice, old murderer. I wanted to ask you something.",
													               "I had a particular question."),
												    pcharrepphrase("Gold can wait. I wanted to ask you something.",
													               "Yes, I agree. I wanted to ask you something.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("I do believe that you know, what I was going to ask.",
													               "I hope you will answer my question."),
													pcharrepphrase("Can you think of anything besides your price tags? 'Cause that's what I was going to ask you about.",
													               "That doesn't interest me. I need information.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Don't get too excited, pal! I was just going to ask you a question.",
													               "Don't get too excited, or you'll have a stroke. Just answer one question, and I shall leave"),
													pcharrepphrase("I don't expect you to say something smart, since you have the brain of a roach. But surely you must know something.",
													               "I will not delay you for long. Just one question.")),
											   npchar, Dialog.CurrentNode);*/
			//link.l3 = "I'm on another matter.";
			//link.l3.go = "quests";
			// --> Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l12 = "Hoztam egy árlistát a város "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
					link.l12.go = "Postcureer_LevelUp_ForAll";
				}
			}
			//<--генер почтового курьера 2 уровня	
						
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Szeretnék egy tétel európai bort vásárolni önöktôl - ötven-hatvan palackot. Azt mondták, hogy van elég belôle a raktárban..."; 
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Üdvözlöm újra. Kérem, nézze meg ezt a levelet - talán átgondolná az álláspontját a nekem való boreladással kapcsolatban?"; 
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Megint én vagyok. Folytathatnánk a megszakított borüzletünket? Sikerült elég pénzt összegyûjtenem."; 
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			
			// туториал Мартиника
			if(CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "Figyeljen, uram, munkát keresek. Nem fôállású munkát vagy zsákos rakományt cipelô munkát, hanem inkább úgymond megbízásokat teljesítek. Szüksége van véletlenül segítségre?";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "Elvégeztem a küldetését. Megtaláltam Gralam Lavoie-t.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "Bemutatom az új asszisztensét, monsieur.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "Megint én vagyok, uram. A jutalmamért jöttem.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Nézze meg ezeket a fülbevalókat, uram. Egy bandita testén találtam, akit a dzsungelben öltek meg. Ez egyértelmûen egy olyan ékszerész munkája, aki biztos vagyok benne, hogy nem idevalósi. Tud valamit mondani ezekrôl a fülbevalókról?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
						
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Jó napot, a fia meghívására jöttem."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "A lányáról van szó...";
						link.l9.go = "EncGirl_1";
					}
				}				
			}			
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Viszlát, vén részeges.",
													               "További szép napot, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("Caramba! Ne menj el sehova, még visszajövök.",
													               "Örülök, hogy itt voltál, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! Viszlát!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Vesszôt le!",
													               "Viszontlátásra, jóember!"),
													pcharrepphrase("Hé! Mit rejtegetsz ott? Rumot? Nem?! Jól van, megyek, megnedvesítem a torkomat.",
													               "Sajnálom, de sürgôs dolgom van a városban.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Heh! Nos, viszlát!",
													               "Mennem kell. Viszlát, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("És eszedbe se jusson vitatkozni velem! Erre nincs idôm!",
													               "Talán el kell mennem megnézni, mi van a hajómon. Viszlát, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Mi a helyzet, öregfiú? Én vagyok az - " +GetFullName(pchar)+ "! Aludj józanul, késôbb visszajövök.",
													               "Attól tartok, hogy a májad végez veled, mielôtt újra eljutnék hozzád."),
													pcharrepphrase("Számold tovább a guineáidat és a dublónjaidat, te vén róka! Még visszajövök.",
													               "Örültem, hogy láttalak, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;
		
		case "Helen_node_1":
			dialog.text = "Mit tehetek érted? Feltölteni a Szivárványt, eladni egy kis zsákmányt? Kétlem, hogy érdekelnének a mostani jövedelmezô szállítmányok, ha-ha.";
			link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Mutasd meg, mit tudsz, te vén kalóz!",
													               "Csak meg akartam nézni a portékádat, jóember."),
													pcharrepphrase("Az akasztófára esküszöm, " +GetFullName(npchar)+", nem hagyom, hogy elriasszon! Mutasd meg az árudat, most azonnal!",
													               "Nézzük meg az árudat, " +GetAddress_FormToNPC(NPChar)+ ".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Az biztos! A halottak nem harapnak! Nos, mi van a rakományodban?",
													               "Jobb, ha a dolgodra térsz, jóember. Milyen árut tudsz nekem kínálni?"),
												    pcharrepphrase("Eljön majd a nap, amikor te leszel a zsákmányom, he-he. Csak vicceltem. Mutasd meg az árudat.",
													               "Beszéljük meg a kereskedelmi ügyeinket, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ "")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Mit akarok? Venni akarok valamit!",
													               "Az ivás a sírba visz, " +GetFullName(npchar)+ ". Szeretném megnézni az áruját."),
												    pcharrepphrase("Ismerem a kedvezményeidet! Két kiló kakaó három kiló áráért! Most pedig mutassa meg az áruját!",
													               "Ez mindig jó. Akkor alkudozzunk.")),
											  "Mutasd meg az árudat! A legkevesebbet mond, a leghamarabb javít. Sietek.",
											  npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Ó, nagyon szeretnék leszúrni valakit, Rendben, térjünk a tárgyra.",
													               "Térjünk rá másra, jóember."),
													pcharrepphrase("Caramba! Én egy másik ügy miatt vagyok itt!",
													               "Egy bizonyos üzletrôl szeretnék beszélni veled, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+".")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Nekem dolgom van veled, öreg kalóz!",
													               "Térjünk rá az üzletre, pajtás!"),
													pcharrepphrase("Az ördögre esküszöm, nem fogsz átverni, gazember! Nekem más dolgom van veled!",
													               "Teljesen egyetértek, " +GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", más ügyeket akartam megbeszélni veled.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Már fel is töltötted? Nekem dolgom van veled.",
													               "Nem kereskedni jöttem ide, jóember. Más dolgom van."),
													pcharrepphrase("Az ilyen árakért sújtson le rád a mennydörgés! Nekem veled van üzletem.",
													               "A kedvezmények mindig szépek, " + GetAddress_FormToNPC(NPChar)+ " " +GetFullName(npchar)+ ", de nekem más dolgom van veled.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Fogd be a szád, te vén részeges, nekem veled van üzletem",
													               "A rumtól vagy rosszul, gondolom. Nem mintha én is kedvelném magadat. Térjünk rá az üzletre."),
													pcharrepphrase("Már így is átvertél, gazember! Nekem dolgom van veled.",
													               "Az iróniád nem helyénvaló. Más dolgom van veled.")),
											   npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Elôször az üzlet, aztán a vidámság. Szeretnék kérdezni valamit.",
													               "Ne most. Információra van szükségem."),
													pcharrepphrase("A pokolba az áraival! Elôször is elmondasz mindent, amire szükségem van.",
													               "Örömmel. Kérdezni akartam valamit.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Köszönöm a tanácsot, öreg gyilkos. Én is kérdezni akartam valamit.",
													               "Volt egy különleges kérdésem."),
												    pcharrepphrase("Az arany várhat. Kérdezni akartam tôled valamit.",
													               "Igen, egyetértek. Kérdezni akartam valamit.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Azt hiszem, tudja, hogy mit akartam kérdezni.",
													               "Remélem, hogy válaszol a kérdésemre."),
													pcharrepphrase("Az árcéduláidon kívül tudsz még valamire gondolni? 'Mert pont ezt akartam kérdezni.",
													               "Ez nem érdekel. Nekem információra van szükségem.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Ne izgulj túlságosan, haver! Csak egy kérdést akartam feltenni.",
													               "Ne izgulj túlságosan, mert még agyvérzést kapsz. Csak egy kérdésre válaszolj, és elmegyek"),
													pcharrepphrase("Nem várom el, hogy valami okosat mondj, hiszen olyan agyad van, mint egy csótánynak. De valamit biztosan tudsz.",
													               "Nem fogom sokáig feltartani. Csak egy kérdés.")),
											   npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,
			                                        pcharrepphrase("Viszlát, vén részeges.",
													               "További szép napot, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),
													pcharrepphrase("Caramba! Ne menj el sehova, még visszajövök.",
													               "Örülök, hogy itt voltál, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! Viszlát!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Vesszôt le!",
													               "Viszontlátásra, jóember!"),
													pcharrepphrase("Hé! Mit rejtegetsz ott? Rumot? Nem?! Jól van, megyek, megnedvesítem a torkomat.",
													               "Sajnálom, de sürgôs dolgom van a városban.")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Heh! Nos, viszlát!",
													               "Mennem kell. Viszlát, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),
													pcharrepphrase("És eszedbe se jusson vitatkozni velem! Erre nincs idôm!",
													               "Talán el kell mennem megnézni, mi van a hajómon. Viszlát, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											   NPCharRepPhrase(npchar,
											        pcharrepphrase("Mi a helyzet, öregfiú? Én vagyok az - " +GetFullName(pchar)+ "! Aludj józanul, késôbb visszajövök.",
													               "Attól tartok, hogy a májad végez veled, mielôtt újra eljutnék hozzád."),
													pcharrepphrase("Számold tovább a guineáidat és a dublónjaidat, te vén róka! Még visszajövök.",
													               "Örültem, hogy láttalak, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),
											  npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
//navy -->
			//занят ПГГ
			if (CheckFreeServiceForNPC(NPChar, "Store") != -1)	 // to_do имя сунуть
			{
				dialog.text = "Sajnálom, de most túl elfoglalt vagyok. Annyi ügyfél! Jöjjön vissza holnap.";
				link.l1 = "Ó, tényleg? Akkor majd késôbb visszajövök.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = RandPhraseSimple("Van nálam gömböc, vitorlavászon, gyógyszer, értékes faanyag és más áruk! Mi érdekli?", "Szeretnél cukrot és fûszereket venni? Vagy esetleg rumot és puskaport?");
			link.l1 = pcharrepphrase(LinkRandPhrase("Rengeteg zsákmány van a raktáramban! A pénznek nincs szaga, ugye?",
			                         "Ki kell dobnom a zsákmányt a raktérbôl, és meg kell töltenem a te aranyaddal. Ha-ha!",
									 "Ó, tudom, hogy az anyádat is eladnád egy zsák dublonnáért! De nekem csak fel kell töltenem a készleteimet."),
									 LinkRandPhrase("Szeretném eladni a rakományomat és feltölteni a készleteimet.",
			                         "Szeretnék árut vásárolni eladásra.",
									 "Mutasd meg az ágyúgolyókat, bombákat és hasonló dolgokat."));
			link.l1.go = "trade_1";

			if(CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
			{
				link.l5 = "A pénztárosom minden szükséges vásárlást meg fog tenni...";
				link.l5.go = "TransferGoods";
			}
			
			link.l3 = pcharrepphrase(RandPhraseSimple("Csere nélkül távozom. Viszlát!",
			                                          "Megyek, megnedvesítem a torkomat. Te maradj ott!"),
									 RandPhraseSimple("Nem, most nincs idôm kereskedni. Búcsúzom.",
									                  "Sajnálom, sürgôs dolgom van. Viszontlátásra!"));
			link.l3.go = "exit";
		break;
		
		case "EncGirl_1":
			dialog.text = "Csupa fül vagyok.";
			link.l1 = "Elhoztam a szökevényét.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ó, kapitány, nagyon köszönöm! Hogy van? Megsérült? Már egy napja, hogy elszökött, rossz kislány. Úgy néz ki, hogy bántani fogom? Találtam neki egy férjet. Megszerveztem a házasságot. Egy gazdag, fiatal vôlegényt. Lehet, hogy rosszul néz ki, de kit érdekelnek az arcvonásai. Nem! Nem! Mindig mindent a maga módján próbál elérni. Ugyanúgy, ahogy az anyja is mindig tette, lángok!\nBár, nem született volna meg, ha az anyja nem szökik meg valami ígéretes idiótával már régen... nos, mindegy... A fiatalság naiv, ostoba és kegyetlen.";
			link.l1 = "Persze, te vagy az apa, és a döntés a te dolgod, de én nem sietnék az esküvôvel...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Mit tudsz te? Vannak saját gyerekeid? Nincsenek? Beszélj velem, ha lesznek...\nIgen... Jutalmat ígértem annak, aki visszahozza ôt, tessék, vedd el.";
			link.l1 = "Köszönöm. Köszönöm. És tartsd rajta a szemed. Van egy olyan érzésem, hogy nem állna le ennyivel.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ó, szóval te vagy "+ GetSexPhrase("az a kapitány, aki elhozta","azt a lányt, aki elhozta") +" a tékozló fiamat egy fiatal arával?";
				link.l1 = "Igen, segítettem nekik megszökni.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ó, ott "+ GetSexPhrase("ô, a mi jótevônk","ô, a mi jótevônk") +". Jutalomra számítasz, ugye?";
				link.l1 = "Nos, jutalom nélkül is jól megvagyok, de a köszönet is megteszi.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Nagyon hálás vagyok neked, hogy nem hagytad magára a gyermekemet a legnagyobb bajban, és segítettél neki kiutat találni a kényes helyzetbôl. Engedje meg, hogy megköszönjem, és kérem, fogadja el ezt a szerény összeget és személyesen tôlem kapott ajándékot.";
			link.l1 = "Köszönöm. Örömömre szolgált, hogy segíthettem ennek a fiatal párnak.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Köszönöm. Milyen köszönet?! Ez a tökfej már fél éve lóg munka nélkül - és nézzétek meg, van ideje szerelmi ügyekre is! Amikor én annyi idôs voltam, mint ô, már a saját vállalkozásomat vezettem! Pff! Egy kormányzónak van egy házasulandó lánya - és ez a tökfilkó egy rokonok nélküli ribancot hozott a házamba, és még az áldásomat is kérni merte!";
			link.l1 = "Hmm... Úgy tûnik, nem hiszel az ôszinte érzésekben?";
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
			dialog.text = "Milyen érzésekben? Miféle érzésekrôl beszélsz? Érzelmek... hogy lehet valaki ennyire könnyelmû a te korodban?! Szégyelld magad, hogy engedsz a fiatalok szeszélyeinek, és kerítônôként viselkedsz! Nemcsak egy lányt vettél el az otthonától, hanem tönkretetted a zöldfülû életemet is. Nem lesz köszönet neked. Búcsúzzatok el!";
			link.l1 = "Rendben, és minden jót neked is...";
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
		
		// Warship. Автозакупка товаров -->
		case "TransferGoods":
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.text = LinkRandPhrase("...már megtörtént. Most már csak az van hátra, hogy eldöntsük, melyik hajóra rakodjunk.",
					"A kincstárnokuk már megtette ezt. Most már csak azt kell eldönteni, hogy melyik hajót rakodjuk meg.",
					"Igen, " + PChar.name + ", tudom. Már meglátogatott. Nos, melyik hajót fogjuk megrakodni?");
					
				for(i=0; i<COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						if(!GetRemovable(chref)) continue;
						
						attrL = "l"+i;
						Link.(attrL)    = "Ez lesz " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "TransferGoodsTo_" + chref.id;
					}
				}
				
				Link.l99    = "Már átgondoltam, semmi sem kell.";
				Link.l99.go = "exit";
			}
			else // Корабля нету
			{
				dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Viccelsz velem? Hol van a hajód? Nem látom a mólónál!",
					"Az ördögre esküszöm, nem fogsz átverni! A hajója nincs a mólónál!"),
					pcharrepphrase("Nem látom a hajóját a kikötôben, kapitány " +GetFullName(pchar)+ ". Nagyon remélem, hogy nem a 'repülô holland'?",
					"kapitány, sokkal könnyebb a rakományt a mólóról felrakodni. És én jobban szeretem így csinálni. Hozza gyorsan a hajóját, és jöjjön vissza."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Micsoda baj! Jól van, öreg ravasz, hamarosan találkozunk!",
					"Nem akartalak becsapni, " +GetFullName(npchar)+ ", egy hajó van a sziget másik oldalán."),
					pcharrepphrase("Nem. A hajómat a 'Fekete Gyöngynek'. hívják. Miért sápadtál el? Haha! Csak vicceltem!",
					"Köszi a tanácsot, feltétlenül használni fogom."));
				link.l1.go = "exit";
			}
			break;
			
		case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
			dialog.text = LinkRandPhrase("Szóval, kapitány, melyik hajóra fogunk felszállni?",
				"Szóval, akkor melyik hajót rakodjuk meg?",
				PChar.name + ", melyik hajó rakterét rakodjuk meg az áruval?");
				
			for(i=0; i<COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if(cn > 0)
				{
					chref = GetCharacter(cn);
					if(!GetRemovable(chref)) continue; // Если квестовый - пропускаем
					
					attrL = "l"+i;
					Link.(attrL)    = "Ez lesz " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}
			
			Link.l99    = "Meggondoltam magam, nincs szükségem semmire.";
			Link.l99.go = "exit";
			break;
			
		case "TransferGoods_Start":
			chref = CharacterFromID(NPChar.CharToTransferGoodsID);
			
			iQuantityGoods = TransferGoods_CalculateWeight(chref);
			
			if(GetCargoFreeSpace(chref) >= iQuantityGoods)
			{
				if(TransferGoods_StartTransfer(chref, NPChar.City) != 0)
				{
					dialog.text = LinkRandPhrase("Minden készen áll! A kiválasztott hajó berakodása megkezdôdött.", 
						"Rendben, az áruk berakodása a kiválasztott hajóra megkezdôdött.",
						"Cap, az áruk berakodása a kiválasztott hajóra megkezdôdött.");
					link.l1 = "Köszönöm. Köszönöm. Öröm volt önnel üzletelni.";
					link.l1.go = "exit";
          SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
					WaitDate("", 0, 0, 0, 1, 0); // Крутим время
				}
				else
				{
					dialog.text = LinkRandPhrase("Kapitány, a kincstárnok által kért összes áru már az Ön által megjelölt hajó fedélzetén van!", 
						"Kapitány, az összes áru már az Ön által megjelölt hajó fedélzetén van!",
						"Kapitány, az a hajó nem igényel karbantartást, mivel az összes áru már ott van.");
					link.l1 = "Igen, persze.";
					link.l1.go = "exit";
					link.l2 = "Akkor azt hiszem, egy másik hajót kell választanom.";
					link.l2.go = "TransferGoods_2";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Attól tartok, egy ilyen típusú hajó egyszerûen nem bír el ennyit.", 
					"Cap, a hajódon nem fér el ennyi rakomány!",
					"Kapitány, a hajója raktere nem bír el ennyi rakományt!");
				link.l1 = "Igen, igazad van. Másik hajót kell választanom.";
				link.l1.go = "TransferGoods_2";
				link.l2 = "Gondolkodtam... Nem kell vennem semmit.";
				link.l2.go = "exit";
			}
			break;
		// <-- Автозакупка товаров

		case "trade_1":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
			    DialogExit();
			    Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			    LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Most viccelsz velem? Hol van a hajód? Nem látom a mólónál!",
					"Az ördögre esküszöm, nem fogsz átverni! A hajója nincs a mólónál!"),
					pcharrepphrase("Nem látom a hajóját a kikötôben, kapitány " +GetFullName(pchar)+ ". Nagyon remélem, hogy nem a 'repülô holland'?",
					"kapitány, sokkal könnyebb a rakományt a mólóról felrakodni. Hozza gyorsan a hajóját, és jöjjön vissza."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Micsoda baj! Jól van, öreg ravasz, hamarosan találkozunk!",
					"Nem akartalak becsapni, " +GetFullName(npchar)+ ", egy hajó van a sziget másik oldalán."),
					pcharrepphrase("Nem, az én hajómat úgy hívják, hogy 'Fekete Gyöngy'. Miért sápadtál el? Haha! Csak vicceltem!",
					"Köszönöm a tanácsot, használni fogják."));
			    link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "Ami a bérleti díjat illeti, még mindig tartozol nekem " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "Rendben, most már kifizetem a bérleti díjat.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Késôbb visszajövök.";
					link.l1.go = "exit";
				}
			}		
			else
			{
				dialog.text = "Gyere.";
				link.l1 = "Köszönjük!";
				link.l1.go = "storage_2";
			}
			link.l2 = "Nem, meggondoltam magam.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Igen, van egy raktáram a kikötôben - 50000 centi rakományt tud befogadni. A " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " havonta biztosíthatom az áruk ôrzését. "+
				"Ez magában foglalja az ôrzést, a vízbetörés elleni védelmet és a patkányok elleni küzdelmet. Mit szól hozzá? Szintén... Egy havi elôlegre lenne szükségem.";	
			link.l1 = "Öltöny. Megnézhetem? Sok patkány van ott?";
			link.l1.go = "storage_1";
			link.l2 = "Nem, csak kérdeztem. Használhatom, ha szükséges...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Mint mondtam, egy hónapra elôre kérem a fizetséget. És patkányok nélkül!";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Maga... eléggé kereskedô, azt kell mondjam. Itt van a pénze, én pedig kibérelem ezt a fészert.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Maga... elég kereskedô, azt kell mondjam. Rendben, hamarosan visszajövök a pénzzel.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "Máris elmegy? Milyen kár - ez tényleg egy kiváló hely, remek feltételekkel. Biztosíthatom, hogy a Karib-térségben sehol máshol nem kap ilyen üzletet.";
			link.l1 = "Azt mondtam - abszolválom. Vagy azt javasolja, hogy fizessek a levegô tárolásáért? Keressen egy másik bérlôt.";
			link.l1.go = "storage_4";
			link.l2 = "Azt mondja, sehol a Karib-tengeren? Rendben, akkor egy idôre bezsákolom.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "És a bérleti díjért még mindig tartozol nekem " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "Rendben.";
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = "Szedje össze az árut, és én bezárom a raktárat.";
				link.l1 = "Rendben.";
				link.l1.go = "storage_6";
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		case "business":
			iTest = 0;			
	
	
			//Jason --> генератор Сомнительное предложение
			/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0) 
			{
				if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) 
				{
					dialog.text = "Ó! Épp idôben jött, kapitány. Szeretném megkérni, hogy tegyen meg nekem egy szívességet.";
					link.l1 = "Hallgassuk meg."; 
					link.l1.go = "Contraoffer";
					break;
				}
			}
		
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store") 
			{
				dialog.text = "Csupa fül vagyok, kapitány.";
				link.l5 = "Elhoztam a parancsát."; 
				link.l5.go = "Contraoffer_check";
			}
			
			if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
			{
				dialog.text = "Ó! Épp idôben jött, kapitány. Egy különleges szívességet kérek.";
				link.l5 = "Hallgassuk meg."; 
				link.l5.go = "Contraoffer_slaves";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store") 
			{
				dialog.text = "Csupa fül vagyok, kapitány.";
				link.l5 = "Elhoztam a rabszolgákat."; 
				link.l5.go = "Contraoffer_slaves_check";
			}*/
			// <-- генератор Сомнительное предложение
	
			//Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
			{
   				link.l16 = "Figyelj, te mindenféle áruval kereskedsz... Tegnap vagy ma - felajánlotta neked valaki, hogy megveszed "+pchar.GenQuest.Device.Shipyarder.Type+"?";
				link.l16.go = "Device_Trader";
			}
			// <-- генератор Неудачливый вор
			
			//Jason --> генератор Место под солнцем
			// belamour legendary edition втречается чаще
			if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block")) 
			{
				dialog.text = "Kapitány, egy szívességet szeretnék kérni, és hajlandó vagyok busásan megfizetni, ha beleegyezik.";
				link.l1 = "Érdekes. Nos, mi a baj?"; 
				link.l1.go = "Sunplace_begin";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Kapitány, örülök, hogy látom. Már tudom, hogy teljesítette a kérésemet a "+pchar.GenQuest.Sunplace.Trader.Enemyname+".";
				link.l1 = "Heh! Az biztos. "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "név")))+" "+pchar.GenQuest.Sunplace.Trader.ShipName+" és a rakomány - " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ ", már nem a riválisodé."; 
				link.l1.go = "Sunplace_complete";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store") 
			{
				dialog.text = "Uram, kapitány... Miért ölted meg? Csak arra kértelek, hogy süllyeszd el a hajóját! Szent Szûz, egy ártatlan ember vére tapad a kezemhez...";
				link.l1 = "Heh! Mi a bajod, " + npchar.name + "? Kit érdekel - soha többé nem fog zavarni, és csak ez számít!"; 
				link.l1.go = "Sunplace_complete_murder";
				break;
			}
			// <-- генератор Место под солнцем
			
//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = "Volt egy munkám, de " + GetFullName(&Characters[iTmp]) + " már vállalta, hogy megcsinálja helyettem.";
				link.l1 = "Ó, tényleg? Akkor majd késôbb visszajövök.";
				link.l1.go = "exit";
				break;
			}
//navy <--
			dialog.text = NPCharRepPhrase(npchar,"Milyen üzlet?! Mondj el mindent!","Figyelek. Mi az az üzlet, amirôl beszélsz?");
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
    			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress",  "failed"))
    			{
    				if (pchar.CargoQuest.TraderID == npchar.id )
    				{
    					link.l1 = RandPhraseSimple("A hajóm rakterében van egy rakomány áru a boltod számára.", "A hajómat azért béreltük fel, hogy az árut az ön üzletébe szállítsa. Az árut most rakodják ki.");
    					link.l1.go = "generate_quest_2";
    				}
    				else
    				{
                        if (!CheckQuestAttribute("generate_trade_quest_progress",  "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
                        {
                            link.l1 = "Sajnos, kénytelen vagyok lemondani a kötelezettségvállalásukról. A politikai helyzet nem teszi lehetôvé, hogy leszállítsam az árut.";
            				link.l1.go = "generate_quest_cannot_done";
                        }
                        else
                        {
                            if (rand(1) == 1)
                            {
                                link.l1 = RandPhraseSimple("Felajánlhatom, hogy kibérelheti a hajómat rakomány szállítására.",
								                           "Van egy nagyszerû hajóm, és bármilyen rakományt el tudok szállítani bárhová, ahová csak szüksége van rá.");
            				    link.l1.go = "generate_quest_not_closed";
        				    }
    				    }
    				}
    			}
    			else
    			{
    				link.l1 = "Szeretne hajót bérelni, " +GetAddress_FormToNPC(NPChar)+ "? Megbízható hajóval és tapasztalt legénységgel rendelkezem.";
    				link.l1.go = "generate_quest";
    			}
				link.l22 = "Én mással foglalkozom.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Ó, én tényleg ki voltam merülve a tengerben... Hát, haver, a pénz most tényleg gondot okoz nekem.",
	                                                          "Rendben, öreg róka, beszéljük meg a pénzügyeinket."),
	                                        RandPhraseSimple("Szeretném megbeszélni veled a pénzügyi kérdéseket.",
	                                                         "Beszéljük meg a pénzügyi ügyeket, beszélnünk kell róluk."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l4 = RandPhraseSimple("Egy ember kérésére vagyok itt. A neve kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " küldött hozzád. Azért jöttem, hogy elvigyek valamit...");
					link.l4.go = "IntelligenceForAll";
				}	
				
				//homo 25/06/06 слухи
                link.l6 = pcharrepphrase(RandPhraseSimple("Elmondaná a legfrissebb pletykákat? Úgyis egész nap itt lógsz.",
                                                          "Ne csinálj bajt, te vén csaló - inkább mondd el, mi újság a szárazföldön?"),
                                        RandPhraseSimple("Úgy tûnik, örökké a tengeren töltöttem. Mi újság a ti vidéketeken?",
                                                         "Biztos minden újdonságot tudsz? Mi fontos történt?"));,

    		    link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if(CheckAttribute(NPChar,"Storage") && Pchar.location.from_sea == "Pirates_town")
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Vigyél a raktárba. Látni akarom, milyen állapotban van.";
						link.l7.go = "storage_0";
						link.l8 = "Úgy döntöttem, hogy felszabadítom a raktárat. Most már nincs rá szükségem.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Elnézést, jóember - nem bérel véletlenül raktárakat?";
							link.l7.go = "storage_01";
						}	
					}
				}				
				// <-- ugeen
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Tudod, próbálom megtalálni a társamat, "+pchar.GenQuest.FindFugitive.Name+" a neve. Kikötô-Royalban a kocsmában azt mondták nekem, hogy a ti településetek felé tart. Találkozott vele véletlenül?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
				
				// <-- homo
				link.l99 = "De most nincs idô beszélgetni.";
    			link.l99.go = "no_quests";
			}
			else
			{
                link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"A sziget másik oldalán hagytam el a hajót. Késôbb visszajövök!", "Elnézést kérek, " +GetFullName(npchar)+ ", késôbb jövök. A hajóm még nem közelítette meg a mólót."), pcharrepphrase("ördög! Ezek az idióták nem készítették elô a hajót a berakodásra! Majd késôbb visszajövök!", "Elnézést, parancsot kell adnom, hogy a hajóm kikötjön a mólónál!"));
                link.l1.go = "exit";
				link.l22 = "Én mással foglalkozom.";
				link.l22.go = "quests";
    			// --> на кредитный генератор
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
    			{
	                link.l3 = pcharrepphrase(RandPhraseSimple("Ó, a tengerben nagyon lemerültem... Hát, haver, a pénz most tényleg gondot okoz nekem.",
	                                                          "Rendben, öreg róka, beszéljük meg a pénzügyeinket."),
	                                        RandPhraseSimple("Szeretném megbeszélni veled a pénzügyi kérdéseket.",
	                                                         "Beszéljük meg a pénzügyi ügyeket, beszélnünk kell."));,
	
	                link.l3.go = "LoanForAll";
                }
				//квест мэра - на связь с нашим шпионом
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") 
				{
					link.l7 = RandPhraseSimple("Egy ember kérésére vagyok itt. A neve kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " küldött hozzád. Azért jöttem, hogy elvigyek valamit...");
					link.l7.go = "IntelligenceForAll";
				}
				// Jason --> квест губера на поиск дезертира
				if(CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
				{
					link.l8 = "Tudod, próbálom megtalálni a társamat, "+pchar.GenQuest.FindFugitive.Name+" a neve. Kikötô-Royalban a kocsmában azt mondták nekem, hogy a ti településetek felé tart. Találkozott vele véletlenül?";
					link.l8.go = "FindFugitiveSt";
				}
				//<-- поиск дезертира
			}
		break;
		
		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = "Nem, nincs szükségem a szolgálataira! Legalábbis amíg ellenségek vagytok a " + NationNameAblative(sti(NPChar.nation)) + ".";
					link.l1 = "Ebben az esetben, viszlát.";
					link.l1.go = "exit";
				}
				else
				{
                    // проверка на проф пригодность -->
                    if (isBadReputation(pchar, 42))
                    {
                        dialog.text = RandSwear() + "Te vagy " + GetFullName(pchar)+ ", ugye? Azt mondják " +
                                      RandPhraseSimple("sok ijesztô dolgot mondanak rólad","sok csúnya dolgot mondanak rólad") + ", és én nem akarok veled foglalkozni.";
						link.l1 = RandPhraseSimple("Persze - ha egyszer hibázol, mindenki örömmel köpköd rád.",
						                           RandSwear()+ "Nos, vannak jobb dolgok is a tengeren, "+GetFullName(npchar)+".");
						link.l1.go = "exit";
                        break;
                    }
                    // проверка на проф пригодность <--
                    int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

					if (iTradeNation < 0)
					{
						dialog.text = NPCharRepPhrase(npchar, "Heh, "+GetAddress_Form(NPChar)+", ma nincs idôm teherautókra. Gyere vissza holnap.","Gyere vissza holnap. Talán teszek neked egy elônyös ajánlatot.");
						link.l1 = "Rendben, holnap visszajövök.";
						link.l1.go = "exit";
					}
					else
					{
                        int storeMan = findStoreMan(NPChar, iTradeNation);
                        if (storeMan > 0)
                        {
                            //проверяем импорт/экспорт
							iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); //Jason
    						//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
    						RecalculateSquadronCargoLoad(pchar); // fix неверное место
    						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
							if (sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units)*sti(iQuantityGoods) > 1500) iQuantityGoods = makeint(1500/(sti(Goods[iTradeGoods].Weight)/sti(Goods[iTradeGoods].Units))); //Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
    						if (iQuantityGoods < 100)// это в шт. товара
    						{
    							dialog.text = NPCharRepPhrase(npchar, "A szánalmas öreg kádad nem bírja el az egész adagot, így ma nem lesz üzlet.","Sajnos, kapitány "+GetFullName(pchar)+", egy tágasabb hajóra lesz szükségem a szállításhoz.");
    							link.l1 = NPCharRepPhrase(npchar, "A hajóm tisztességes, de értem, mire gondolsz. Viszontlátásra.","Értem az álláspontját, az üzlet az üzlet. Viszontlátásra.");
    							link.l1.go = "exit";
    						}
    						else
    						{
    							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods/3)) - 10;
    							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4+rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

    							pchar.CargoQuest.iTradeGoods = iTradeGoods;
    							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
    							pchar.CargoQuest.iMoney = iMoney;
    							pchar.CargoQuest.iTradeNation = iTradeNation;
    							pchar.CargoQuest.iDaysExpired = 25 + rand(5);
    							
    							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
    							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
    							pchar.CargoQuest.TraderID     = Characters[storeMan].id;
    							pchar.CargoQuest.GiveTraderID = NPChar.id;
                                SaveCurrentQuestDateParam("CargoQuest");
    							string sNation = XI_ConvertString("Colony"+Characters[storeMan].city);
                                sTemp = "";
                                if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
								{
                                    sTemp = ", ...ami a " + XI_ConvertString(pchar.CargoQuest.iTradeIsland+"Voc");
                                }
                                dialog.text =  "Ó! Épp egy szívességet akartam kérni tôled. Tudja, el kell szállítanom a " +
                                               GetGoodsNameAlt(iTradeGoods)+ " mennyiségû " + FindRussianQtyString(iQuantityGoods) + " rakományt a " +
                                           sNation + sTemp + "városba, és minél hamarabb, annál jobb. Ha sikerül ezt a " +  FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)) +
                                           ", akkor a megérkezéskor megkapod a " +
                                           FindRussianMoneyString(iMoney) + " jutalmadat. Mit szólsz hozzá?";
    							link.l1 = "Azt hiszem, egyetértek.";
    							link.l1.go = "exit_trade";
    							link.l2  = "Ez valószínûleg nem nekem való.";
    							link.l2.go = "exit";
    						}
                        }
                        else
                        {
                            dialog.text = "A szigetvilág politikai realitásai nem teszik lehetôvé számomra a kereskedelmet. "+
                                          XI_ConvertString(NationShortName(sti(NPChar.nation))+"vadász") + " mindenkivel ellenségeskedik, és csak engem hagyott a boltban.";
    						link.l1 = "Ó! Sajnálom. Sok szerencsét.";
    						link.l1.go = "exit";
                        }
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar, "Tûnj el, nincs idôm üres fecsegésre!","Már mondtam neked, hogy nincs semmim számodra.");
				link.l1 = NPCharRepPhrase(npchar, "Udvariasnak kell lenned, vagy megtanítalak udvariasságra!", "Ó, sajnálom!");
				link.l1.go = "exit";
			}
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = RandSwear() + "Nem gondolod, hogy egy kicsit késôn jutott eszedbe az üzlet? Újra meg kellett rendelnem az árut. Viszontlátásra.";
				link.l1 = "Bocsásson meg, de nagyon siettem. Talán ha fedezem a veszteségeit, helyreáll a hírnevem?";
				link.l1.go = "generate_quest_failed";
				link.l9 = "Minden jót.";
				link.l9.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
                iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
                iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
                
                dialog.text = "Valóban! Már régóta vártam rá. Le kell szállítanod nekem egy rakományt " +
                GetGoodsNameAlt(iTradeGoods) + " összegben " + FindRussianQtyString(iQuantityGoods) + " és kapj érte " +
                FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + ".";
				link.l1 = "Pontosan.";
				link.l1.go = "generate_quest_ready";
			}
		break;
		
		case "generate_quest_ready":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            // блок кидалова нас на бабки -->
            if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
            {
                dialog.text = RandSwear() + "Bocsánatot kell kérnem tôled, "+GetAddress_Form(NPChar)+
                              ".  Látja, A probléma az, hogy én " + RandPhraseSimple("kínos helyzetbe kerültem, és nem fogom tudni kifizetni Önnek"," már megvásároltam azt a rakományt egy másik eladótól jobb áron")+
                              ". A bérleti díj kifizetéseként javaslom, hogy tartsa meg az összes szállítmányt, amit leszállított.";
				link.l1 = RandSwear() + RandPhraseSimple("És én megvédtem azt az átkozott rakományt minden veszélytôl! Kétszáz patkányt öltem meg miatta!",
                                                         "Patthelyzetbe hoztál, és kénytelen leszek egyetérteni.");
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
                break;
            }
            // блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
                iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
                dialog.text = "Ez nem az egész adag! Az egyezségünk szerint még "
                              + FindRussianQtyString(iTmp) + " egységre van szükségem.";
				link.l9 = RandPhraseSimple("Igen, valóban. Akkor majd pótolnom kell a hiányt. Viszlát késôbb.",
                                           RandSwear() +"Ezek az átkozott patkányok elrontották a rakományt. Kárpótolni fogom a hiányt, és visszajövök újra.");
				link.l9.go = "exit";
                AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
                dialog.text = "Kiváló! Itt a jutalmad, kapitány "+GetFullName(pchar)+".";
				link.l1 = "Öröm volt veled dolgozni.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
				
                OfficersReaction("good");
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;
		
		case "generate_quest_failed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Rendben... A " + FindRussianMoneyString(iMoney) + " összeg éppen fedezi a megállapodásunk feltételeinek megszegésébôl eredô károkat.";
			link.l1 = "Hûha! Nem, ez nem lesz elég! Soha többé nem szállítok semmilyen rakományt! Van elég ilyen szar a tengeren!";
			link.l1.go = "exit";
            if (sti(pchar.Money) >= iMoney)
            {
    			link.l2 = "Itt van a szükséges összeg.";
    			link.l2.go = "generate_quest_failed_2";
			}
            else
            {
                AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            }
		break;
		
		case "generate_quest_failed_2":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            iMoney =  3*makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = "Kitûnô. Most már elmondhatom a kollégáimnak, hogy még mindig ésszerû veled üzletelni.";
			link.l1 = "Köszönöm! Nem fogok még egyszer csalódást okozni.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

            AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
            AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen"));
            CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;
		
		case "generate_quest_not_closed":
            iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);

            dialog.text = "Hmm. Úgy hallottam, hogy nem teljesítette az elôzô szerzôdésben foglalt kötelezettségeit - és most újabbat kér? A " +
            LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name)+ " rakományt kellett volna leszállítania a " + XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony) + ".";
			link.l1 = "Igen, valóban! Igaza van!";
			link.l1.go = "exit";
		break;
		
		case "generate_quest_cannot_done":
            dialog.text = RandSwear() + GetAddress_Form(NPChar) +", cserbenhagysz engem!!! Talán teszel valamit a probléma megoldása érdekében?";
			link.l1 = "Rendben. Mindent megteszek, hogy kézbesítsem a küldeményt.";
			link.l1.go = "exit";
			link.l2 = "Nem, nem tudom. Sajnálom.";
			link.l2.go = "generate_quest_cannot_done_2";
			
		break;
		
		case "generate_quest_cannot_done_2":
		    iTradeGoods    =  makeint(pchar.CargoQuest.iTradeGoods);
            iQuantityGoods =  makeint(pchar.CargoQuest.iQuantityGoods);
            if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = "Várjatok! Nincs elég áru a hajótokon! Nincs "
                              + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + " egységnyi rakományod.";
				link.l9 = RandPhraseSimple("Igen, valóban. Akkor majd pótolnom kell a hiányt.",
                                           RandSwear() +"A patkányok elrontották a rakományt. Megveszem a hiányzó mennyiséget, és visszajövök újra.");
				link.l9.go = "exit";
			}
			else
			{
                dialog.text = "Értem, értem... Visszaveszem a szállítmányt.";
    			link.l1 = "Köszönöm! Nem hagylak cserben még egyszer!";
    			link.l1.go = "exit";
    			ChangeCharacterComplexReputation(pchar,"nobility", -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));
                
                AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
                AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
    		    AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony",XI_ConvertString("Colony"+pchar.CargoQuest.iTradeColony+"Gen")); // belamour gen
                CloseQuestHeader("DELIVERY_TRADE_QUEST");
            }
		break;
	
//Jason --> мини-квест Дефицитный товар
		case "Wine_Trader":
			dialog.text = "Mirôl beszélsz? Nyilvánvalóan félrevezették - soha nem kereskedtem ilyen mennyiségben európai borokkal. Egy-két üveggel, nem többel. De a helyi bor más tészta - abból van nekem elég, és demizsononként árulják, nem palackonként!";
			link.l1 = "Tessék! De nekem azt mondták...";
			link.l1.go = "Wine_Trader_1";
		break;
		
		case "Wine_Trader_1":
			dialog.text = "Fogalmam sincs, mit mondtak neked, de megismétlem: Nincs európai borom raktáron. Ennyit tudok mondani az üggyel kapcsolatban.";
			link.l1 = "Rendben... Akkor megyek és elintézem!";
			link.l1.go = "exit";
			AddQuestRecord("Wine", "5");
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
			DeleteAttribute(pchar, "questTemp.Wine.Trader");
			pchar.questTemp.Wine.Repeat1 = "true";
		break;
		
		case "Wine_Repeat2":
			RemoveItems(PChar, "letter_1", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ez már egy másik történet. Tudja, különbözô típusok jönnek ide, és felesleges kérdéseket tesznek fel. Szóval, akkor alkudjunk?";
			link.l1 = "Persze!";
			link.l1.go = "Wine_Price";
			pchar.questTemp.Wine.wait = "true";
			DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
			SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;
		
		case "Wine_Price":
			dialog.text = "Hány üvegre van szükséged? Egy palack ára 500 pezó, és a minimális tétel 20 palack.";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Wine_Qty";
			link.l2 = "Most nincs elég pénzem. Majd késôbb visszajövök.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Wine.Qty = sti(iQty);
			if (iQty < 20)
			{
				dialog.text = "Nem vagyok házaló, kapitány. Ha jól emlékszem, nagyobb tételrôl beszélt?";
				link.l1 = "Sajnálom... Akkor gondoljuk át újra az összeget.";
				link.l1.go = "Wine_Price";
				break;
			}
			if (iQty > 70)
			{
				dialog.text = "Sajnos, nincs ennyi.";
				link.l1 = "Kár... Akkor gondoljuk át újra a mennyiséget.";
				link.l1.go = "Wine_Price";
				break;
			}
			pchar.questTemp.Wine.Summ = sti(iQty)*500;
			dialog.text = ""+sti(iQty)+" Palackok? Rendben. Ez a " + FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ))"ára lesz.";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
			{
				link.l1 = "Tessék, tessék.";
				link.l1.go = "Wine_Qty_1";
			}
			link.l2 = "Most nincs elég pénzem. Majd késôbb visszajövök.";
			link.l2.go = "Wine_Qty_exit";
		break;
		
		case "Wine_Qty_exit":
			dialog.text = "Rendben van, de ne tartson túl sokáig. Ez a cucc elég népszerû itt.";
			link.l1 = "Hamarosan visszajövök!";
			link.l1.go = "exit";
		break;
		
		case "Wine_Qty_1":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
			dialog.text = "Lássuk csak... Úgy tûnik, minden rendben van. Átveheti a vásárolt árut.";
			link.l1 = "Köszönöm! Sok szerencsét!";
			link.l1.go = "Wine_Qty_2";
		break;
		
		case "Wine_Qty_2":
			pchar.quest.Wine_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.wait");
			TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			PlaySound("interface\important_item.wav");
			Log_Info ("Bort kaptál");
			AddQuestRecord("Wine", "8");
			DelLandQuestMark(npchar);
			DialogExit();
		break;
		// <-- мини-квест Дефицитный товар
		
// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
		case "Contraoffer":
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
			{
				pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
			}
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15*(sti(pchar.rank)+30)/(sti(Goods[iCGood].Weight)/sti(Goods[iCGood].Units))*(8-sti(RealShips[sti(pchar.ship.type)].Class)));//количество
			pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost)/sti(Goods[iCGood].Units)*3;//цена единицы товара
			pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price)*sti(pchar.GenQuest.Contraoffer.Trader.Qty);//сумма
			pchar.GenQuest.Contraoffer.Trader.Days = 30+hrand(20);//срок
			pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);//17% вероятности, что патруль накроет
			dialog.text = "Úgy terveztem, hogy jó üzletet kötök, de ehhez még szükségem van egy bizonyos árura - " + GetGoodsNameAlt(iCGood)+ ". A probléma az, hogy ez az áru csempészáru a kolóniánkon, így nem számíthatok arra, hogy a kereskedelmi kapitányoktól megvásárolhatom\nMindössze " + FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)) + " egységre van szükségem belôle. Esetleg el tudná szállítani nekem? Jól megfizetem, " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price)) + " egységenként, ami " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ". Ó, és legkésôbb "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days))+". Szóval, segítene nekem?";
			link.l1 = "Hmm... Érdekesen hangzik. Egyetértek!";
			link.l1.go = "Contraoffer_1";
			link.l2 = "Csempészett árut szállítani? Sajnálom, nem érdekel.";
			link.l2.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;
		
		case "Contraoffer_1":
			dialog.text = "Kiváló. Örülök, hogy beleegyezett. Szóval, várom, hogy visszatérjetek az áruval.";
			link.l1 = "Hamarosan visszajövök!";
			link.l1.go = "exit";
			rColony = GetColonyByIndex(FindColony(npchar.city));
			SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods));//нулим товар
			pchar.GenQuest.Contraoffer = "begin";
			pchar.GenQuest.Contraoffer.Trader = "true";
			pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
			pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
			iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "1");
			AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Trader.City+"Gen"));
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;
		
		case "Contraoffer_check":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
			if (amount > 0)
			{
				dialog.text = "Most viccelsz? Nincs nálad annyi áru, amennyire szükségem van!";
				link.l1 = "Sajnálom, az én hibám...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lássuk csak. Egy rakományt kellett volna szállítania " + GetGoodsNameAlt(iCGood)+ " mennyiségben " + FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty) + ". Így van?";
				link.l1 = "Pontosan, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Contraoffer_pay";
			}
		break;
		
		case "Contraoffer_pay":
			dialog.text = "Köszönöm a munkáját. Kérjük, vegye fel a fizetést - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ".";
		link.l1 = "Köszönöm! Öröm volt önnel üzletelni.";
		link.l1.go = "Contraoffer_complete";
		break;
		
		case "Contraoffer_complete":
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			npchar.quest.Contraoffer.chance = rand(2);//личный шанс торговца для 'пасхалки'
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
			{
				dialog.text = "Hoppá... Kapitány, úgy tûnik, van egy kis problémánk...";
				link.l1 = "Mi is az?";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("Contraoffer_Patrol");
				pchar.GenQuest.Contraoffer.Trader.busy = "true";
				pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
				pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
				pchar.quest.Contraoffer_busy.function = "Trader_free";
			}
			else
			{
				DialogExit();
				AddQuestRecord("Contraoffer", "3");
				CloseQuestHeader("Contraoffer");
				DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
			}
		break;
		
		case "Contraoffer_slaves"://единичный вариант за всю игру, ака 'пасхалка'
			pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
			pchar.GenQuest.Contraoffer.Slaves.Price = 300;//цена на рабов, пока фиксированная, можно подставить формулу
			pchar.GenQuest.Contraoffer.Slaves.Qty = 300+rand(50);//количество
			pchar.GenQuest.Contraoffer.Slaves.Days = 14+rand(6);//срок
			pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty)*sti(pchar.GenQuest.Contraoffer.Slaves.Price);
			dialog.text = "Sürgôsen szükségem van egy tétel rabszolgákra - "+sti(pchar.GenQuest.Contraoffer.Slaves.Qty)+" fejek. Kész vagyok fizetni "+sti(pchar.GenQuest.Contraoffer.Slaves.Price)+" érmét lélekenként, ami összesen "+sti(pchar.GenQuest.Contraoffer.Slaves.Money)+" pezót tesz ki; határidô - "+FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days))+".";
			link.l1 = "Azt hiszem, beleegyezem. Ez egy kellemetlen, de nagyon jövedelmezô üzlet.";
			link.l1.go = "Contraoffer_slaves_1";
			link.l2 = "Engem nem érdekel.";
			link.l2.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;
		
		case "Contraoffer_slaves_1":
			dialog.text = "Pontosan - valóban nagyon jövedelmezô. Nos, akkor a rabszolgáimmal együtt várom a visszatérésedet.";
			link.l1 = "Nem fogok sokáig várakoztatni. Viszlát!";
			link.l1.go = "exit";
			pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
			pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
			ReOpenQuestHeader("Contraoffer");
			AddQuestRecord("Contraoffer", "4");
			AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
			AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
			AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
			AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Contraoffer.Slaves.City+"Gen"));
			SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;
		
		case "Contraoffer_slaves_check":
			amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
			if (amount > 0)
			{
				dialog.text = "Most viccelsz? Nincs meg az összes rabszolgád, amire szükségem van!";
				link.l1 = "Sajnálom, az én hibám...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lássuk csak. Úgy volt, hogy szállít nekem egy adag rabszolgát " + FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty) + ". Így van?";
				link.l1 = "Pontosan, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Contraoffer_slaves_pay";
			}
		break;
		
		case "Contraoffer_slaves_pay":
			dialog.text = "Köszönöm a munkáját. Kérjük, vegye át a fizetést - " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)) + ". Kérjük, fogadja el ezt is. Biztos vagyok benne, hogy hasznosnak fogja találni.";
			link.l1 = "Köszönöm! Öröm volt önnel üzletelni.";
			link.l1.go = "Contraoffer_slaves_complete";
		break;
		
		case "Contraoffer_slaves_complete":
			DialogExit();
			pchar.quest.Contraoffer_Over.over = "yes";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
			AddQuestRecord("Contraoffer", "5");
			CloseQuestHeader("Contraoffer");
			SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
			AddCharacterExpToSkill(pchar, "Sailing", 150);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			TakeNItems(pchar, "cirass3", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
		// <-- генератор Сомнительное предложение
		
		//Jason --> генератор Неудачливый вор
		case "Device_Trader":
			dialog.text = "Hmm, "+pchar.GenQuest.Device.Shipyarder.Type+"? Még sosem hallottam róla... Mi is ez tulajdonképpen? Még sosem hallottam ilyesmirôl.";
			link.l1 = "Nos, ez egy hajóépítô szerszám, "+pchar.GenQuest.Device.Shipyarder.Describe+". Ajánlott valaki ilyesmit neked?";
			link.l1.go = "Device_Trader_1";
			npchar.quest.Device = "true";
		break;
		
		case "Device_Trader_1":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
			{
				dialog.text = "Hmm... Igen, volt egy furcsa fickó. De nem mondta el, hogy mi az a dolog, csak megpróbálta eladni nekem. De mire kell nekem, ha fogalmam sincs, mire való? Hogy adhatnám el? Úgyhogy visszautasítottam.";
				link.l1 = "És hogy nézett ki és hova ment? Nekem nagyon kell az a hangszer.";
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
		case "Sunplace_begin":
			dialog.text = "Verseny... Nélküle nincs üzlet. Kapzsi szemetek, akik igyekeznek betörni a te hangulatos üzletedbe, és mindenféle aljas módszerrel magukhoz csábítják az ügyfeleket\nDe ez a szöveg. És valójában arra szeretném kérni, hogy segítsen megszabadulni az egyik ilyen versenytársamtól. Nem, megölni nem szükséges. Egyszerûen csak elfogni vagy elsüllyeszteni a hajóját a rakományával.";
			link.l1 = "Hmm... nos, ha jól fizet, akkor el tudom intézni.";
			link.l1.go = "Sunplace_1";
			link.l2 = "Nem, nem avatkozom bele a kereskedelmi vitáidba. Menjetek és süllyesszétek el a riválisotokat a segítségem nélkül.";
			link.l2.go = "Sunplace_exit";
		break;
		
		case "Sunplace_exit"://если отказал - этот непись больше никогда не даст
			npchar.quest.Sunplace = "true";
			DialogExit();
		break;
		
		case "Sunplace_1":
			GetSunplaceShore();//бухта и остров
			pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");//имя конкурента
			pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;//нация общая для торговца и конкурента
			pchar.GenQuest.Sunplace.Trader.City = npchar.City;//город квестодателя
			pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);//город конкурента
			pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();//тип корабля
			pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя корабля
			pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);//дни
			pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype)*3000;//оплата
			pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));//товар
			dialog.text = "Nagyon jó. Tehát az embered neve "+pchar.GenQuest.Sunplace.Trader.Enemyname+". Nemrég küldte ki "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "név") + "Acc"))+" '"+pchar.GenQuest.Sunplace.Trader.ShipName+"' rakományával " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods))+ ". Elég tisztességes összeget fizetett ezért a rakományért, így annak elvesztése eléggé meg fogja érinteni a pénztárcáját.";
			link.l1 = "És meg tudnád mondani, hogy pontosan hol keressem azt a 'barátodat' ?";
			link.l1.go = "Sunplace_2";
		break;
		
		case "Sunplace_2":
			dialog.text = "Az én 'barátom' jelenleg az otthonában van "+XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.CityT+"Voc")+". Nem rá van szükséged - a hajójára van szükséged, ami, mint megtudtam, miután körülbelül "+FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty))+" fog elhaladni a " + XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen") + "közelében . Elsüllyesztheted, elfoglalhatod a beszállással - mindegy. A lényeg, hogy a hajó és a rakomány már ne legyen a "+pchar.GenQuest.Sunplace.Trader.Enemyname +"tulajdona. És nem érdekel, hogy ki fogja igényt tartani rá - te vagy a tenger. Ezért a munkáért fizetni fogok neked " + FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)) + ".";
			link.l1 = "Megvan. Nos, akkor ideje indulni!";
			link.l1.go = "Sunplace_3";
		break;
		
		case "Sunplace_3":
			DialogExit();
			pchar.GenQuest.Sunplace.Trader = "true";
			if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9) pchar.GenQuest.Sunplace.Bonus = "true";
			ReOpenQuestHeader("Sunplace");
			AddQuestRecord("Sunplace", "1");
			AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
			AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
			AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
			AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Sunplace.Trader.City+"Gen"));
			AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
			AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore+"Gen"));
			SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
			pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
			pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
			pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
			pchar.quest.Sunplace_Trader.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.Sunplace_Trader.win_condition.l2.date.day   = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.win_condition.l2.date.year  = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)-2));
			pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;
		
		case "Sunplace_complete":
			dialog.text = "Kitûnô! Tudtam, hogy számíthatok rád. Azt hiszem, nem fogok kérdezôsködni a hajó és a rakomány holléte felôl. Végül is ez nem az én dolgom. És a barátomnak elég sok idôre lesz szüksége, hogy felépüljön egy ilyen csapásból, he-he-he. Tessék, vegye el a pénzét - és köszönöm a remek munkát.";
			link.l1 = "Szívesen... Viszlát, " + npchar.name + "!";
			link.l1.go = "Sunplace_complete_1";
		break;
		
		case "Sunplace_complete_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "12");
			CloseQuestHeader("Sunplace");
			pchar.GenQuest.Sunplace.Chance = rand(2);
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		case "Sunplace_complete_murder":
			dialog.text = "Szegény "+pchar.GenQuest.Sunplace.Trader.Enemyname+", micsoda borzalmas sors! És bár közvetve, de én vagyok az oka a halálának! Nem érti, kapitány! Én kértem, hogy ölje meg? Úgy terveztem, hogy a rakományra költött pénz elvesztése után ismét... nos, mindegy... Maga...";
			link.l1 = "Hé, figyelj - hagyd abba a nyafogást, rendben? Megkértél, hogy szabadítsalak meg egy riválistól - megtettem. És ami még jobb - a rakomány elvesztése után is újra gazdaggá válhat, és tovább károsíthatja az üzletedet. Most már nem sok mindent tehet halott emberként.";
			link.l1.go = "Sunplace_complete_murder_1";
		break;
		
		case "Sunplace_complete_murder_1":
			dialog.text = "Ez az! Elég volt! Nem akarom tovább hallgatni ezeket a káromló beszédeket! Fogja a rohadt pénzét és azonnal hagyja el a boltomat!";
			link.l1 = "Hé, " + npchar.name + ", nyugodj meg, jó? Vagy én magam fogom lehûteni az indulataidat - a szablyám mindig mellettem van! Jól van, ne ijedj meg, csak vicceltem. Figyelj, sajnálom, hogy így alakult - de te voltál az, aki elôször félrevezetett. Viszlát.";
			link.l1.go = "Sunplace_complete_murder_2";
		break;
		
		case "Sunplace_complete_murder_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
			AddQuestRecord("Sunplace", "13");
			AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
			CloseQuestHeader("Sunplace");
			npchar.quest.Sunplace = "true";//этот непись повторно квест больше не даст
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			DialogExit();
		break;
		
		//Jason --> поиск дезертира
		case "FindFugitiveSt":
			if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
			{
				dialog.text = NPCStringReactionRepeat(""+pchar.GenQuest.FindFugitive.Name+"? Igen, ismerem ôt. Tôlem vásárolt ellátmányt a hosszú hajójához. Napközben általában valahol eldugott öblökben halászik, de minden este a kocsmában találjuk.", "Már kérdezett arról az emberrôl, és én mindent elmondtam, amit tudok!", "Most viccelsz velem, vagy tényleg idióta vagy?! Már harmadszorra is felteszed ugyanazokat a kérdéseket!", "Ha belegondolok, hogy egy ilyen idióta hogyan lett kapitány...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Köszönöm, nagyon sokat segítettél nekem!", "Igen, igen, rendben.", "Na, na, ne izgulj már ennyire. Csak elfelejtettem.", "Nos, igen, ahogy láthatod...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = NPCStringReactionRepeat("Nem tudom, mit beszéltek az emberek a Port Royal kocsmában, de én soha nem találkoztam azzal az emberrel a boltomban. Valójában soha sehol nem láttam ôt. Kérdezôsködjön a faluban - talán valaki majd elmondja...", "Már kérdezett arról az emberrôl, és én elmondtam: Nem tudom!", "Most viccelsz velem, vagy tényleg hülye vagy?! Már harmadszor kérdezed ugyanazt a kérdést!", "Csak belegondolni, hogy egy ilyen idióta hogyan lett kapitány...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Értem. Nos, azért köszönöm.", "Igen, igen, rendben.", "Na, na, ne izgulj annyira. Csak elfelejtettem.", "Nos, igen, ahogy láthatod...", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
			}
		break;
		
		case "FindFugitiveSt_1":
			DialogExit();
			AddQuestRecord("MayorsQuestsList", "12-2");
			sld = characterFromId("Fugitive");
			LAi_SetSitType(sld);
			sld.dialog.currentnode = "Fugitive_tavern";
			LAi_SetLoginTime(sld, 20.0, 23.99);
			FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City+"_tavern", "sit", "sit_front1");
		break;
		//<-- поиск дезертира
		
		// --> Карибские нравы - временное завершение
		// belamour legendary edition -->
		case "trial":
			dialog.text = "Uram, mi van veled, fiatalember! Kérlek, légy visszafogottabb, és gondosan válaszd meg a szavaidat, amikor tisztelt emberekrôl beszélsz! Gerard LeCroix elhagyta Guadeloupe-t egy expedícióval a szárazföldre, de a jutalmadat itt hagyta neked. Most már elégedett vagy?";
			link.l1 = "Hm... Kérem, bocsásson meg, monsieur. Kicsit felhevültem...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Nagyon jó. Lecroix úr a jutalmát a helyi világítótoronyôrre hagyta - régi barátok. Csak fel kell keresnie ôt, és átvenni az esedékes fizetséget. Monsieur Lecroix becsületes ember, úgyhogy azt hiszem, elégedett lesz a jutalmával.";
			link.l1 = "Megvan, köszönöm! Aztán elmegyek a világítótoronyôrhöz. Most hadd tartsak egy kis szünetet.";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			//TakeNItems(pchar, "gold_dublon", 400);
			link.l1 = "...";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "trialA":
			dialog.text = "Igen, itt volt, és várt rád. De valószínûleg a feladat, amit rád bízott, nehezebbnek bizonyult, mint amire eredetileg számított, ezért nem várt, és expedícióra indult a szárazföldre. A jutalmadat egy megbízható személynél hagyta.";
			link.l1 = "Igen, tényleg váratlan körülmények közé kerültem, de sikeresen teljesítettem a feladatot. Örömmel hallom, hogy a fizetésem vár rám. Kitôl kaphatom meg?";
			link.l1.go = "trialA_1";
		break;
		
		case "trialA_1":
			dialog.text = "Monsieur Lecroix a helyi világítótoronyôrre hagyta a jutalmát - régi barátok. Önnek csak fel kell keresnie ôt, és átvenni az esedékes fizetséget. Monsieur Lecroix becsületes ember, így azt hiszem, elégedett lesz a jutalmával.";
			link.l1 = "Megvan, köszönöm! Aztán elmegyek a világítótoronyôrhöz. Most hadd tartsak egy kis szünetet.";
			link.l1.go = "trialA_2";
		break;
		
		case "trialA_2":
			dialog.text = "Sok szerencsét, monsieur.";
			link.l1 = "...";
			link.l1.go = "trialA_3";
		break;
		
		case "trialA_3":
			DialogExit();
			AddQuestRecord("Trial", "22");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Commerce", 80);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			sld = characterFromId("BasTer_Lightman");
			sld.quest.trial_usurer = true;
			AddLandQuestMark(sld, "questmarkmain");
		break;
		// <-- legendary edition
		/*case "trial":
			dialog.text = "Istenem, miért vagy ilyen hangos, fiatalember! Nyugodj meg, és vigyázz a nyelvedre, amikor a tisztelt emberekrôl beszélsz! Gerard LeCroix elhagyta Guadeloupe-t egy expedícióval a szárazföldre, de önnek üzenetet hagyott\nMegnyugodott, uram? Készen áll meghallgatni engem?";
			link.l1 = "Hm... Kérem, bocsásson meg, uram. Kicsit felhevültem. Hallgatom.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Nagyon jó. Legközelebb próbáljon meg elôször kérdezni, és utána hangosan kiabálni. Rendben... Ismer egy Simon Maurois nevû embert?";
			link.l1 = "Ha! Mindenki hallott már Simon Mauroisról! Persze, hogy ismerem.";
			link.l1.go = "trial_2";
			link.l2 = "Soha nem hallottam róla. Ki ô?";
			link.l2.go = "trial_3";
		break;
		
		case "trial_2":
			dialog.text = "Kitûnô. Akkor menjen el hozzá. Ô volt az, aki finanszírozta Shoke úr expedícióját, úgyhogy tôle veheti fel a jutalmát. Szóval, tényleg szükséges volt ennyire felhúzni magad?";
			link.l1 = "Még egyszer, elnézését kérem... Köszönöm a segítségét, monsieur. Azonnal felkeresem Maurois urat!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_3":
			dialog.text = "Ô a Maurois bankház tulajdonosa és a capsterville-i fiók vezetôje. Tehát el kell mennie Saint-Christopherbe, és fel kell keresnie a capsterville-i bankot. Maurois monsieur volt az, aki finanszírozta Shoke monsieur expedícióját, így tôle veheted fel a jutalmadat. Szóval, tényleg szükséges volt ennyire felhúzni magad?";
			link.l1 = "Még egyszer, elnézését kérem... Köszönöm a segítségét, monsieur. Azonnal felkeresem Maurois urat!";
			link.l1.go = "trial_exit";
		break;
		
		case "trial_exit":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.Trial = "usurer";
			AddQuestRecord("Trial", "22");
		break;*/
		
		// belamour legendary edition на пару с Акулой -->
		case "SharkGoldFleet":
			dialog.text = "Á, a vállalkozó szellemû kereskedô! Azonnal látja az üzleti megközelítést. Tisztelem. Persze, megvan az áru, amire szüksége van.";
			link.l1 = "Biztos vagyok benne, hogy nyereséggel el tudom adni. Amennyire tudom, Porto Bellóban jó kereslet van erre az árura. Mennyibe fog nekem kerülni?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			pchar.questTemp.SharkGoldFleet = "buyincar";
			dialog.text = "Így-úgy... Szóval, háromszáz egység kávé... És ugyanannyi kakaó... Az ára..."+sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300))+" pezó!";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Hmm... Elnézést, úgy tûnik, nincs nálam elég pénz. Várjon, kérem: Most szaladok a hajóhoz pénzért - és mindjárt visszajövök!";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Tessék, tessék.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		
		case "SharkGoldFleet_02":
			if(GetCargoFreeSpace(pchar) < 1200)
			{
				dialog.text = "Várjon egy percet, senor. Úgy tûnik, nincs elég hely a hajón egy ilyen partira. Takarítsa ki a raktérbôl és térjen vissza.";
				link.l1 = "Ó, elfelejtettem kirakodni! Várjon egy percet - mindjárt megyek!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Remek! Azonnal kiadom a parancsot, hogy az árut rakodják fel a hajójára. Öröm önnel üzletelni!";
				link.l1 = "Kölcsönösen, senor! És most hadd búcsúzzak: a dolgok nem várnak.";
				link.l1.go = "SharkGoldFleet_03";
			}
		break;
		
		case "SharkGoldFleet_03":
			DialogExit();
			AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE)+300);
			SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE)+300);
			AddQuestRecord("SharkGoldFleet", "4");
			pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;
		
		case "SharkGoldFleet_again":
			dialog.text = "Az áruk várnak önre. Hoztál pénzt?";
			if(pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			{
				link.l1 = "Még nincs. Csak biztos akartam lenni benne, hogy az ajánlatod áll. És a pénz is hamarosan megérkezik.";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Tessék, tessék.";
				link.l1.go = "SharkGoldFleet_02";
			}
		break;
		//<-- на пару с Акулой
		case "no_quests":
			dialog.text = "Jelenleg nincs szükségem a szolgálataira.";
			link.l1 = "Kár. Váltsunk témát.";
			link.l1.go = "node_1";
		break;
		
        case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":			
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();			
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
    ref ch;
	int n;
    int storeArray[30];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
        if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            if (sti(ch.nation) !=  iTradeNation) continue;
            if (NPChar.id == ch.id) continue;
            if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader") continue; // fix 2016-03-07
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city)) continue; // хрен вам, а не читы!
            storeArray[howStore] = n;
            howStore++;
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}

int Sunplace_Shiptype() // new
{
	int i;
	
	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6) i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11) i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18) i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18) i = SHIP_GALEON_L;
	
	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
