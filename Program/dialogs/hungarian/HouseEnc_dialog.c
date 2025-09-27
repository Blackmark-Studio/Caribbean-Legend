void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("A városban riadalmat keltettek. Úgy tûnik, itt az ideje, hogy én is fegyvert fogjak...", "A városôrök nem futnak utánad véletlenül? ", "Itt nem fogsz menedéket találni, de lehet, hogy több centi hideg acélt találsz a bordáid között!"), 
					LinkRandPhrase("Mit akarsz,"+ GetSexPhrase("gazember","gazember") +"?! A városôrök már megtalálták a szagodat, nem mész messzire, "+ GetSexPhrase("mocskos kalóz","te kalóz mikorch") +"!", "mocskos gyilkos! Ôrség!!!", "Nem félek tôled, "+ GetSexPhrase("görény","whench") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Látom, belefáradtál az életbe...", "Úgy tûnik, nincs békés élet a " + XI_ConvertString("Colony" + npchar.city + "Gen") + "polgárainak !"), 
					RandPhraseSimple("Menjetek a pokolba!", "Heh, ezek lesznek életed utolsó másodpercei..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Figyelmeztettelek titeket. Aztán majd eldöntheted magad, hogy akarsz-e bajba kerülni.";
					link.l1 = "Heh!";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Mi szükséged van a házamban, gazember?! Tíz másodperced van, hogy eltûnj innen!";
					link.l1 = LinkRandPhrase("Heh, úgy tûnik, itt is ismernek engem!", "A hírnevem megelôzött...", "Hmm, értem.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Örömmel üdvözlöm Önöket az otthonomban. Van valami dolga velem?", 
						"Mit tehetek önért?", 
						"Hmm... Mit tehetek önért?",
						"Sajnálom, de ha nincs dolga velem, kérem, ne zavarjon...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Nem, csak körülnézek, új emberekkel találkozom...", 
						"Nem, semmi különös...",
						"Semmi...", 
						"Rendben, ahogy mondod.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Sajnálom, de az éjszaka nem a legjobb idôpont a látogatásra, ezért arra kérem, hogy azonnal hagyja el a házamat!", 
						"Már mondtam, hogy késô van. Kérem, távozzon.", 
						"Nem akarok udvariatlannak tûnni, de ragaszkodom hozzá, hogy azonnal hagyja el a házamat!",
						"Az istenit, mi folyik itt?! Ôrség! Tolvajok!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Rendben, értem...", 
						"Igen, csak egy pillanat...",
						"Rendben, csak ne izgulj annyira.", 
						"Milyen tolvajok?! Kuss legyen!", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Ó, engedje meg, hogy bemutatkozzam - " + GetFullName(npchar) + ". Nagyon örülünk, hogy a vendégünk vagy. Ebben a városban tiszteletben tartják a vendégszeretet törvényeit.";
			link.l1 = GetFullName(pchar) + ", ...ha megkérhetem...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Te "+ GetSexPhrase("tolvaj vagy, látom! Ôrök, fogjátok el","tolvaj, látom! Ôrség, fogjátok el") +"!!!", "Nem hiszem el! Egy pillanatra elfordultam - és máris a holmimba merülsz! Állítsatok meg egy tolvajt!!!", "Ôrség! Rablás! Állítsanak meg egy tolvajt!!!");
			link.l1 = "Aaaah, ördög!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Figyelmeztetlek, hogy a férjem hamarosan visszatér! Jobb, ha most azonnal elhagyod a házamat!", "Nem hiszem, hogy sikerül elmenekülnöd! És vigyázz, hogy a férjem hamarosan hazaér!", "A férjem hamarosan hazajön! Azonnal el kell menned!"), 
					LinkRandPhrase("Kár, hogy a férjem nincs itthon... Kifelé! Azonnal!!!", "Mocskos gyilkos, takarodj a házamból azonnal! Ôrség!", ""+ GetSexPhrase("Micsoda gazember","Micsoda mocsok") +"... Hamarosan visszatér a férjem, és látni fogja, milyen színû a véred!"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Ó, a férjed... oooooh... reszketek...", "Heh... Tudod, kislány, a férjed csak egy ember... nem akarod, hogy a lábad elôtt haljon meg, ugye?"), 
					RandPhraseSimple("Fogd be, te szajha, mielôtt kibelezlek...", "Addig maradok itt, ameddig csak akarok. És jobb, ha befogod a szád, ha tudod, mi a jó neked..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Figyelmeztettelek. Kifelé, vagy megbánod!";
					link.l1 = "Micsoda hülye kurva...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "Mit keresel a házamban, "+ GetSexPhrase("gazember","gazember") +"?! Ha nem mész el tíz másodpercen belül, hívom az ôrséget!";
					link.l1 = "Micsoda hülye kurva...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Örülök, hogy a házunkban látlak. A nevem " + GetFullName(npchar) + ". Mit tehetek érted?", 
						"Még mindig itt vagy?", 
						"Hm, elnézést, de nem gondolja, hogy ideje lenne már távoznia?",
						"Megkérném, hogy ne sértse meg a vendégszeretetünket.", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat( GetFullName(pchar) + " az Ön szolgálatára. Különösebb ok nélkül jöttem ide, csak ismerkedni.", 
						"Még mindig itt vagyok.",
						"Hát, nem is tudom...", 
						"Rendben.", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Jaj, miért törnek be a házamba ilyenkor! Nagyon megijesztettél... Kérlek, látogass meg minket holnap!", 
						"Kérem, hagyja el a házunkat!"+ GetSexPhrase("","Én férjes asszony vagyok!") +"", 
						"Utoljára kérem, hogy hagyja el a házunkat!",
						"De mi folyik itt?!", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Ne félj, nem foglak bántani.", 
						"Rendben, csak ne izgulj annyira.",
						"Elmegyek.", 
						"Mi a helyzet?", npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "Mindig örömmel fogadunk vendégeket. Csak ne maradjanak itt túl sokáig,"+ GetSexPhrase(", mivel férjes asszony vagyok..."," mivel sok dolgom van...") +"";
			link.l1 = "Ó, igen, persze...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "Szóval így állunk? Vendégként üdvözöltelek, te meg a ládáinkban turkálsz?! Ôrség!";
			link.l1 = "Kussolj, ribanc!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "Barátságosan megkértelek, hogy hagyd el a házunkat, de te csak nem hallgatsz rám! Elég legyen! Segítség! Ôrség!";
			link.l1 = "Fogd be, te ostoba nôszemély! Megôrültél?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("A városban riadalmat keltettek. Úgy tûnik, itt az ideje, hogy én is fegyvert fogjak...", "A városôrök nem futnak utánad véletlenül? ", "Itt nem fogsz menedéket találni, de lehet, hogy több centi hideg acélt találsz a bordáid között!"), 
					LinkRandPhrase("Mit akarsz,"+ GetSexPhrase("gazember","gazember") +"?! A városôrök már megtalálták a szagodat, nem mész messzire, "+ GetSexPhrase("mocskos kalóz","mikorch") +"!", "mocskos gyilkos! Ôrség!!!", "Nem félek tôled, "+ GetSexPhrase("görény","whench") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Látom, belefáradtál az életbe...", "Úgy tûnik, nincs békés élet a " + XI_ConvertString("Colony" + npchar.city + "Gen") + "polgárainak !"), 
					RandPhraseSimple("Menjetek a pokolba!", "Heh, ezek lesznek életed utolsó másodpercei..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("Üdvözöljük! A nevem " + GetFullName(npchar) + ". Itt én vagyok a fônök, szóval eszedbe se jusson bármit is magaddal vinni...", 
				"Viselkedjetek illedelmesen és ne feledjétek, hogy szemmel tartalak titeket.", 
				"Amíg nem leskelôdsz a ládákba, addig itt maradhatsz. Úgyis unatkozom egyedül...",
				RandPhraseSimple("Jaj, de unatkozom!", "Az istenit, mit vegyek fel? Olyan unalmas itt lenni!"), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Rendben, ne aggódj.", 
				"Persze!",
				"Értem...", 
				"Igen, ez problémásnak hangzik.", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("A városban riadalmat keltettek. Úgy tûnik, itt az ideje, hogy én is fegyvert fogjak...", "A városôrök nem futnak utánad véletlenül? ", "Itt nem fogsz menedéket találni, de lehet, hogy több centi hideg acélt találsz a bordáid között!"), 
					LinkRandPhrase("Mit akarsz,"+ GetSexPhrase("gazember","gazember") +"?! A városôrök már megtalálták a szagodat, nem mész messzire, "+ GetSexPhrase("mocskos kalóz","mikorch") +"!", ""+ GetSexPhrase("mocskos","mocskos") +" gyilkos! Ôrség!!!", "Nem félek tôled, "+ GetSexPhrase("görény","whench") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Látom, belefáradtál az életbe...", "Úgy tûnik, nincs békés élet a " + XI_ConvertString("Colony" + npchar.city + "Gen") + "polgárainak !"), 
					RandPhraseSimple("Menjetek a pokolba!", "Heh, ezek lesznek életed utolsó másodpercei..."));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("Itt én vagyok a fônök, szóval eszedbe se jusson bármit is magaddal vinni...", 
				"Viselkedj tisztességesen, és ne feledd, hogy szemmel tartalak.", 
				"Amíg nem leskelôdsz a ládákba, addig itt maradhatsz. Úgyis unatkozom egyedül...",
				RandPhraseSimple("Jaj, de unatkozom!", "Az istenit, mit vegyek fel? Olyan unalmas itt lenni!"), "block", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Rendben, ne aggódj.", 
				"Persze!",
				"Értem...", 
				"Igen, ez problémásnak hangzik.", npchar, Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Figyelj, haver, nyíltan akarok beszélni veled.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "Van egy csábító ajánlatom számodra. Talán érdekelhet téged.";
					link.l7 = "Tényleg? Rendben, hallgatlak.";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Vigyél a raktárba. Látni akarom, milyen állapotban van.";
						link.l7.go = "storage_0";
						link.l8 = "Úgy döntöttem, hogy kiürítem a raktárat. Már nincs rá szükségem.";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "Említettél egy raktárat. Még mindig üres?";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "Van egy raktárnak alkalmas területünk. Szeretné bérbe adni ésszerû áron? Gondoljon csak bele, lenne egy saját raktára, ahol értékes árut tárolhatna...";
			link.l1 = "Egy raktár, azt mondja? Igen, csábító, valóban... Elég nagy? És mennyit kér a bérleti díjért?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Még egy kikötôi raktárhoz képest is elég tágas, elfér benne, lássuk csak ... 50000 centi rakományt. A  havi " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + "  áron tudom biztosítani az áruk ôrzését. "+
				"Ez magában foglalja az ôrzését az embereimmel, a vizesedéstôl való védelmet és a patkányok elleni harcot. Mit szóltok hozzá? Ó, és a titoktartás is, ez magától értetôdô.";
			link.l1 = "Rendben. Megnézhetem?";	
			link.l1.go = "storage_rent2";
			link.l2 = "Ez már túl sok. És lefogadom, hogy elárasztották és patkányokkal van tele.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Persze, persze. De... Egy havi elôleget kérek. ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Maga... eléggé kereskedô, azt kell mondjam. Itt a pénze... Bérbe veszem ezt a fészert.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "Maga... eléggé kereskedô, azt kell mondjam. Rendben, hozom a pénzt.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "Ahogy óhajtja. Ha meggondolná magát, csak szóljon. És ne feledje, hogy egy ilyen szép raktár nem valószínû, hogy sokáig üresen marad...";
			link.l1 = "Nem probléma. Majd szólok, ha szükségem lesz rá.";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "És a bérleti díjért még mindig tartozol nekem  " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
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
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Menjen csak.";
				link.l1 = "Köszönjük!";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("Kapitány, hol van a hajója? Hogyan tervezi a rakományt mozgatni?", "Nem látom a hajóját a kikötôben kikötve. Pontosan hogyan akarja megrakodni?");
                link.l1 = RandPhraseSimple("Ó... errôl teljesen megfeledkeztem!", "A francba, így van!");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "Nem, meggondoltam magam.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "Nem, "+ GetSexPhrase("uram","asszonyom") +", még mindig üres és várja önt. Tudtam, hogy végül nem utasítja vissza az ajánlatomat.";
			link.l1 = "Nagyon jó. Ki fogom bérelni.";
			link.l1.go = "storage_1";
			link.l2 = "Nem, csak eszembe jutott...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Emlékeznie kell, hogy egy havi elôleget kérek elôre.";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Persze, emlékszem. Tessék, tessék.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "A francba. Rendben, hozom a pénzt.";
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
			dialog.text = "Máris indulsz? Milyen kár, ez tényleg egy kiváló hely, nagyszerû feltételekkel. Biztosíthatom, hogy ilyen üzletet sehol a Karib-térségben nem fog kapni.";
			link.l1 = "Mondtam, hogy kiürítem. Vagy azt javasolja, hogy fizessem ki a levegô tárolását? Kereshet egy másikat.";
			link.l1.go = "storage_4";
			link.l2 = "Azt mondja, sehol a Karib-tengeren? Rendben, akkor egy ideig megtartom. De a bérleti díj, azt kell mondjam, egy kicsit magas.";
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
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Szedje össze az árut, és én bezárom a raktárat.";
				link.l1 = "Rendben.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("Kapitány, hol van a hajója? Hogyan tervezi a rakományt mozgatni?", "Nem látom a hajóját a kikötôben kikötve. Pontosan hogyan akarja megrakodni?");
                link.l1 = RandPhraseSimple("Ó... errôl teljesen megfeledkeztem!", "A francba, így van!");
			    link.l1.go = "exit";
				break;
                }				
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

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Heh! Rendben, beszéljünk.";
			link.l1 = "El kell jutnom a hajógyárba éjszaka, amikor senki sincs a környéken.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Nézzenek oda! Hé, ôrök, van itt egy tolvaj!!!";
				link.l1 = "Milyen tolvaj? Csak beszélgetni akartam!";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Hûha! Nézzenek oda, "+ GetSexPhrase("haver","lass") +". Ilyen kéréssel jönni a hajógyár raktárába!";
				link.l1 = "El kell jutnom a hajógyárba. Engem nem érdekel a raktárad.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "De miért van rá szükséged?";
			link.l1 = "Szükségem van rá. És hajlandó vagyok fizetni érte...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Hmm, így már jobb... Jól van! Csúsztasd nekem a " + FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000) + ", és a következô nap folyamán nyitva hagyom a hajógyár ajtaját.";
			link.l1 = "Ez túl drága. Akkor nélkülöznöm kell...";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "Rendben, egyetértek. Fogd a pénzed és tedd, ahogy megbeszéltük.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Ne aggódj, meglesz.";
			link.l1 = "Remélem is...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
