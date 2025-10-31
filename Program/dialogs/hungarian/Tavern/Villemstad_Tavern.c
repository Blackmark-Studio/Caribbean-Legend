// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Ismétled ugyanazt, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//работорговец
			if (pchar.questTemp.Slavetrader == "EscapeSlave_Villemstad")
            {
                link.l1 = "Úgy hallottam, hogy a szigeten komoly zûrzavar van... Rabszolgák?";
                link.l1.go = "EscapeSlaveVillemstad_T1";
            }
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "SeekPortVillemstad")
            {
                link.l1 = "Úgy hallottam, hogy az a nyomorult gazember Bart, a portugál végre igazságot szolgáltatott! Börtönben van? Mikor lesz a kivégzése, tudod? Szeretném megnézni, van egy kis gondom azzal a söpredékkel...";
                link.l1.go = "Portugal";
            }
			//--> Тайна Бетси Прайс
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern"))
			{
				link.l1 = "Figyelj, "+npchar.name+", hallottam, hogy nemrég volt egy új gyönyörû pincérnôd... és máris eltûnt?";
				link.l1.go = "TBP_Tavern_1";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern2"))
			{
				link.l1 = "Mondja, "+npchar.name+", azon az éjszakán, amikor Betsy eltûnt, nem vett észre valakit gyanúsat a közelében? Talán beszélt valakivel?";
				link.l1.go = "TBP_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TBP_Tavern3"))
			{			
				sld = CharacterFromID("Villemstad_waitress");
					if (CheckAttribute(sld, "model") && sld.model != "Marquesa")
					{
						link.l1 = "Nos, "+npchar.name+", jó hírek - a drága pincérnôd él és virul. Fel kell töltened a rumkészletedet, az emberek hamarosan visszajönnek.";
						link.l1.go = "TBP_Tavern3_21";
					}
					else
					{
						link.l1 = "Na, "+npchar.name+", a dolog el van intézve – a drága pincérnőd visszatért. Itt az ideje újra feltölteni a rumkészleteket, mert hamarosan visszatérnek a vendégek.";
						link.l1.go = "TBP_Tavern3_21_1";
					}
			}
			//<-- Тайна Бетси Прайс
 		break;

		//работорговец
		case "EscapeSlaveVillemstad_T1":
			dialog.text = "Igen, még soha nem volt ilyen zûrzavar... Több mint ezer néger lázadt fel. Két ültetvényt porig égettek, és mindegyikük gazdáját meggyilkolták. A parancsnok aggódik, hogy a rabszolgák megtámadják a várost, ezért statáriumot rendelt el. És az egész két néger, egy Tamango nevû bak és egy Isauri nevû ôzike miatt kezdôdött...";
			link.l1 = "Elég drámaian hangzik. Mesélje el az egész történetet, kik ezek a négerek?";
			link.l1.go = "EscapeSlaveVillemstad_T2";
		break;
		
		case "EscapeSlaveVillemstad_T2":
				dialog.text = "Tamango és Izaura - rabszolgák a blenheimi ültetvényen, az elsô felégetett ültetvényen. Ez a két néger szerette egymást. De Európából megérkezett az ültetvényes egyik fia, Leonsio, aki megkedvelte az ôzbakot. Izaurát a személyes ágyasává akarta tenni. A fekete bak Tamango nem volt oda az ötletért, és Izaura sem, ô nagyon szerette a fekete ördögöt\nTamango valamiféle fônök volt, vagy valami ilyesmi Afrikában... Egy óriási bak - a bûnnél is feketébb és halálos volt a fejszéjével, a többi néger félt és tisztelte. Szóval ez a néger vezeti a többi rabszolga felkelését. Éjszaka megtámadták az ôröket, megöltek minden fehéret a nagy házon kívül, a mulattokat is\nAztán Izaura kinyitotta az ültetvény kapuit, és a vad majmok mindenkit megöltek odabent. Blenburg porig égett. Aztán a rabszolgák elmenekültek a dzsungelbe, és eltûntek...";
			link.l1 = "Hát ez milyen történet, úgy hangzik, mint egy regény cselekménye! Egy igazi rabszolgalázadás, mint az ókori Rómában. Egyébként honnan tudta meg mindezt?";
			link.l1.go = "EscapeSlaveVillemstad_T3";
		break;
		
		case "EscapeSlaveVillemstad_T3":
			dialog.text = "A pletykák szerint, mynheer, a föld hemzseg tôlük. A rum meglazítja a nyelveket, csak hallgatni kell...";
			link.l1 = "És hogy végzôdött mindez? Megtalálták azokat a négereket?";
			link.l1.go = "EscapeSlaveVillemstad_T4";
		break;
		
		case "EscapeSlaveVillemstad_T4":
				dialog.text = "Ha, semmi esélye! Amíg az erôsítésnek végre sikerült megérkeznie, senki sem tett egy lépést sem a dzsungelbe. Aztán megérkezett egy század hadihajó egy egységnyi katonával, és átkutatták a szigetet. Nem találtak egyetlen elszabadult néger fekete bôrét vagy göndör haját sem.";
			link.l1 = "Na, mit szólsz ehhez! Ezer néger csak úgy eltûnt a semmibe?";
			link.l1.go = "EscapeSlaveVillemstad_T5";
		break;
		
		case "EscapeSlaveVillemstad_T5":
			dialog.text = "Valójában a vízbe.";
			link.l1 = "Mirôl beszélsz, " + npchar.name + "? Te is ugyanolyan jól tudod, mint én, hogy a négerek nem tudnak úszni.";
			link.l1.go = "EscapeSlaveVillemstad_T6";
		break;
		
		case "EscapeSlaveVillemstad_T6":
			dialog.text = "He-he... ó nem, azok a feketék nem olyan gyorsan cápák. Az a helyzet, hogy a lázadás után a következô éjjel eltûnt egy bárka a dokkokból. Feketére festhetsz, én meg bendzsózok és táncolok neked, ha nem az a Tamango bakó és a négerei keze által történt! Ezért nincsenek többé a szigeten.";
			link.l1 = "Ha, most már mindent hallottam, " + npchar.name + ". Azt várod, hogy elhiggyem, hogy egy rakás félvad néger tudja kezelni a vitorlákat és navigálni? Inkább arra számítanék, hogy egy majomhajó jön Guineából.";
			link.l1.go = "EscapeSlaveVillemstad_T7";
		break;
		
		case "EscapeSlaveVillemstad_T7":
			dialog.text = "Én sem hittem el, mynheer, de a bizonyíték a hiányzó hajóban van. Talán az egyik néger hajón szolgált stewardként, és elsajátította a hajózási technikát. Talán fekete mágiát használtak, ki tudja! Ugorj be hozzám máskor is, " + pchar.name + ", legközelebb is lesz még néhány történetem.";
			link.l1 = "Köszönöm! Nos, itt az ideje, hogy induljak.";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "22_2");
			pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_P";
		break;						

		case "Portugal":
			dialog.text = "Igen, így van. Elkapták azt a kalózt. És el tudjátok hinni, hogyan? Egy kakasülôn fogták el, egyedül a tenger közepén. Még csak egy hangot sem adott ki, mielôtt a patkányoknak küldték a raktérbe. Igazán mulatságos, tudod, hogy egy ilyen veszélyes kalózt úgy kaptak el, mint egy ilyen senkiházit!";
			link.l1 = "És miért volt egyedül a tengeren?";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Valószínûleg úgy döntött, hogy elválik a lakájoktól, semmi kétség... Nem tudták igazságosan elosztani a zsákmányt. Most pedig magának a Társaságnak a kezében van, és azok a fickók nem szeretik a tréfát. Azt mondják, hogy a Társaság egyik hajóját birtokba vette valami értékes dologgal. Úgy látszik, csak azért, mert valami információt akarnak kipréselni belôle, még mindig nem lógott már hurokban.";
			link.l1 = "Szóval, mikor lesz a kivégzése, nem tudod?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Senki sem tudja. Azt hiszem, amint a Társaság kideríti, hogy mit akar, kenderkötôt kötnek a nyakába. A portugál most is a börtönben van, megbízható ôrzés alatt\nNemrég hozták ide a hajóskapitányát is. Az ô története még meglepôbb volt, Philipsburgban feladta magát a hollandoknak. Szóval, egy cellában helyezték el közvetlenül a volt kapitánya mellett, így most már szomszédok, he-he...";
			link.l1 = "Csodák történnek! Rendben, figyelni fogom a híreket. Nem akarok lemaradni az akasztásról. Viszlát, "+npchar.name+"!";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			DialogExit();
			pchar.questTemp.Portugal = "PortugalInPrison";
			AddQuestRecord("Portugal", "32");
		break;
		
		//--> Тайна Бетси Прайс
		case "TBP_Tavern_1":
			dialog.text = "Ó, bárcsak látta volna, kapitány úr! Betsy... micsoda kecsesség, micsoda mosoly! Az emberek csak azért jönnének ide, hogy megnézzék. És az ezüst, amit a kocsmámban hagytak... De három nappal ezelôtt nem jelent meg a munkában. Persze küldtem embereket a házához, de nem volt ott. A házban rendetlenség van, a személyes holmijai eltûntek\nNem tudom már, mit gondoljak. Az ôrök, mint mindig, most is csak vállat vontak. Azt mondták, hogy fontosabb dolguk is van, mint egy eltûnt lányt keresni. Azt mondták, hogy valószínûleg csak elment, és hamarosan visszajön. Kapitány, talán maga meg tudná találni? Ha visszahozza ide, fizetek száz dublont. Nem veszíthetem el csak úgy, érted? Ô egy igazi kincs! Mindenáron vissza kell szereznem!";
			link.l1 = "Lássuk, mit tehetek. Nem viselkedett furcsán, mielôtt eltûnt, vagy kapott valami rossz hírt?";
			link.l1.go = "TBP_Tavern_2";
			link.l2 = "Keressünk egy lányt, aki valószínûleg csak úgy elszökött? Van jobb dolgom is. Intézd el te magad.";
			link.l2.go = "TBP_Tavern_End";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern_End":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TBP_Tavern");
			CloseQuestHeader("TBP");
		break;

		case "TBP_Tavern_2":
			dialog.text = "Az eltûnése elôtti utolsó napon jókedvûen, sôt boldogan távozott! Semmi jele bajnak, egy szót sem szólt a távozásáról. Csak úgy eltûnt!";
			link.l1 = "Érdekes... Hol találom a házát?";
			link.l1.go = "TBP_Tavern_3";
		break;

		case "TBP_Tavern_3":
			dialog.text = "Az utca végén lakott, egy kunyhóban, közvetlenül a kék erkélyes kúriával szembeni ház mögött. Nincs messze innen.";
			link.l1 = "Nos, akkor nem vesztegetem az idôt. Ha találok valamit, szólok.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_Poorman");
		break;

		case "TBP_Tavern2_11":
			dialog.text = "Gyanús? Mindig is kérôk tömegei voltak körülötte, és mindegyik gyanús volt a maga módján! Elég jól flörtölt, tudta, hogyan kell felhívni magára a figyelmet.";
			link.l1 = "Ennyire már"+GetSexPhrase(""," rájöttem")+" . De volt valaki, aki kiemelkedett?";
			link.l1.go = "TBP_Tavern2_12";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern2_12":
			dialog.text = "Hmm... Nos, volt egy. Aznap este egy drágaköves medált adott neki. Itt ült, szemét a lányra szegezve, egész éjjel ott lebegett körülötte.";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon"))
			{
				link.l1 = "Az a medál véletlenül nem ez lenne? (Mutasd a koldustól vásárolt kámeát)";
				link.l1.go = "TBP_Tavern2_13";
			}
			else
			{
				link.l1 = "Azt mondja, hogy a medál drágakövekkel...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			}
		break;

		case "TBP_Tavern2_13":
			dialog.text = "Ez az! Pontosan az! Kapitány, talált már valamit?";
			link.l1 = "Részletek késôbb, "+npchar.name+", most nincs vesztegetni való idô.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_SearchHouseWithFonar");
			RemoveItems(pchar, "jewelry24", 1); 
			notification("Adott: Cameo medál", "None");
		break;

		case "TBP_Tavern3_21":
			dialog.text = "Ez kiváló, kapitány! Már kezdtem azt hinni, hogy soha többé nem látom ôt. Szóval, mi történt? Tényleg el akart szökni?";
			link.l1 = "Mondjuk úgy, hogy meg kellett küzdenie néhány problémával a múltjából. De úgy tûnik, hogy ez már a múlté, és hamarosan újra munkába áll.";
			link.l1.go = "TBP_Tavern3_22_leadership";
			link.l2 = "Mondjuk, hogy szüksége volt egy kis szünetre, hogy ne kelljen az unalmas arcodat néznie. Ha-ha! Ne ráncolja a homlokát, csak vicceltem. Minden hölgynek kell, hogy legyenek kis titkai...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership":
			dialog.text = "Nos, a lényeg az, hogy visszamegy dolgozni. Megérdemelte a jutalmát, kapitány. Tessék, vegye el - száz dublont, ahogy megbeszéltük. Fogd ezt a térképet is. Az egyik vendég itt hagyta és nem tért vissza. Úgy tûnik, kincsekhez vezet.";
			link.l1 = "Nos, akkor megnézem. Köszönöm.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune":
			dialog.text = "Nos, a lényeg az, hogy visszamegy dolgozni. Megérdemelte a jutalmát, kapitány. Tessék, vegye el - száz dublont, ahogy megbeszéltük. Fogd ezt a térképet is. Az egyik vendég itt hagyta és nem tért vissza. Úgy tûnik, kincsekhez vezet.";
			link.l1 = "Nos, akkor megnézem. Köszönöm.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		
		case "TBP_Tavern3_21_1":
			dialog.text = "Megmentett engem, kapitány! Már nem is reméltem, hogy újra látom őt... Szóval mi is történt pontosan? Tényleg el akart szökni? Nem mertem személyesen rákérdezni nála.";
			link.l1 = "Mondjuk úgy, néhány régi problémát kellett rendeznie. De úgy tűnik, már túl van rajta, és hamarosan visszatérhet a munkához.";
			link.l1.go = "TBP_Tavern3_22_leadership_1";
			link.l2 = "Nos, mondjuk úgy, kellett neki egy kis szünet attól, hogy a te unalmas képedet nézze. Ha-ha! Ne húzd így az arcod, csak vicceltem. Minden hölgynek megvannak a maga kis titkai...";
			link.l2.go = "TBP_Tavern3_22_fortune";
			DelLandQuestMark(npchar);
		break;

		case "TBP_Tavern3_22_leadership_1":
			dialog.text = "Nos, a lényeg, hogy visszatért a munkába. Megérdemelte a jutalmát, kapitány. Tessék – száz doblon, ahogy megbeszéltük. És még ezt a térképet is vegye el. Az egyik vendég hagyta itt, és soha nem tért vissza. Úgy tűnik, kincsekhez vezet.";
			link.l1 = "Rendben, utánanézek. Köszönöm.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;

		case "TBP_Tavern3_22_fortune_1":
			dialog.text = "Nos, a lényeg, hogy visszatért a munkába. Megérdemelte a jutalmát, kapitány. Tessék – száz doblon, ahogy megbeszéltük. És még ezt a térképet is vegye el. Az egyik vendég hagyta itt, és soha nem tért vissza. Úgy tűnik, kincsekhez vezet.";
			link.l1 = "Rendben, utánanézek. Köszönöm.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_BetsiBackToWork");
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddItems(pchar, "gold_dublon", 100);
			if (!CheckCharacterItem(PChar, "map_full")) GiveItem2Character(PChar, "map_full");
			else AddMapPart();
		break;
		//<-- Тайна Бетси Прайс
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
