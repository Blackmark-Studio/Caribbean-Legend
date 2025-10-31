void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Kapitány","Lady") +"! Kérlek, légy kegyes! Védj meg, könyörgöm!","Segítség! "+ GetSexPhrase("Idegen","Ifjú hölgy") +", ments meg, könyörgöm!");
			link.l1 = LinkRandPhrase("Mi történt?","Mi a helyzet?",RandPhraseSimple("Mi a baj?","Mi történik?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Kapitány! Kapitány","Lass! Lass") +", kérem tartson ki!","Tarts ki, "+ GetSexPhrase("kapitány","ifjú hölgy") +"! Kérem, kérem, kérem!");
			link.l1 = LinkRandPhrase("Mi történt?","Mi a helyzet?",RandPhraseSimple("Mi a baj?","Mi történik?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, m"+ GetSexPhrase("iser","iss") +"! Kérem, segítsen egy szegény lányon, könyörgöm! Azok az emberek valami szörnyûséget akarnak tenni velem!";
			link.l1 = LinkRandPhrase("Mi történt?","Mi a helyzet?",RandPhraseSimple("Mi a baj?","Mi történik?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("Ezek a gazemberek meg akarnak erôszakolni! Minden jó érdekében ne hagyjátok, hogy megtegyék!","Az Isten szerelmére, védj meg ezektôl a szörnyetegektôl! Meg fognak gyalázni engem!");
			link.l1 = "Ne pánikolj"+ GetSexPhrase(", szépség","") +". Mi történt itt?";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Nemi erôszaktevôk üldöznek engem!"+ GetSexPhrase(" Kiállnál egy hölgy becsületéért?","") +"","Kapitány, "+ GetSexPhrase("légy férfi","te is nô vagy") +" nem mentenél meg egy lányt a szégyentôl!");
			link.l1 = "Ne pánikolj"+ GetSexPhrase(", szépség","") +". Mi történt itt?";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "Elgázolnak engem! A banditák! Mondd meg nekik, hogy hagyjanak békén!";
			link.l1 = "Ne pánikolj"+ GetSexPhrase(", szépség","") +". Mi történt itt?";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Segítség! Segítség! Üldöznek engem! Mentsetek meg!",
				"Aaah! Segítség, "+ GetSexPhrase("idegen","ifjú hölgy") +"! Mentsetek meg ezektôl a gazemberektôl!",
				"Mutass kegyelmet és védj meg ezektôl a gazemberektôl! Kérem!");
			Link.l1 = LinkRandPhrase("Mi történik?", "Mi a helyzet?", "Mi történt?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("Ôk... meg akarnak erôszakolni! Az ég szerelmére, ne hagyd, hogy megerôszakoljanak! Kérem!",
				"Ezek a szörnyek... valami szörnyûséget terveznek... Védj meg tôlük, kérlek!",
				"Urunk nevében, ments meg ezektôl a kéjes vadállatoktól! Meg akarnak gyalázni engem!");
			Link.l1 = "Akkor oldjuk meg az egészet.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Köszönöm, "+ GetSexPhrase("kapitány","ifjú hölgy") +". Annyira megijedtem!","Köszönöm, hogy megmentettél! Annyira hálás vagyok neked!");
					link.l1 = "Rendben, "+ GetSexPhrase("szépség","kedves") +", nyugodj meg, ez már a múlté.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Ó, köszönöm, "+ GetSexPhrase("nemes ember! Ön egy igazi úriember!","hölgy! Megmentettél engem!") +"";
					link.l1 = "Nem tehettem mást.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Ó, köszönöm, "+ GetSexPhrase("nemes ember! Ön egy igazi úriember!","idegen! Megmentettél engem!") +"";
					link.l1 = "Nem tehettem mást.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "Mit tettél? Miért ölted meg ôket?! Most engem fognak keresni! Istenem, mit tettem, hogy ezt érdemlem!";
					link.l1 = "Ez aztán a hála!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "Mit tettél, "+ GetSexPhrase("kapitány","ifjú hölgy") +"?! Miért ölted meg ôket? Valójában az apám küldte ôket... Ó, most már biztos meg fog ölni...";
				link.l1 = "Na, ez aztán a hír! És mit gondoltál, hogy kiabálsz, hogy banditák üldöznek?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "Van egy kis pénzem, kérem, fogadja el hálám jeléül. Most mindenkinek elmondom, "+ GetSexPhrase("milyen jó és nemes ember vagy","milyen jó és nemes nô vagy") +".";
			link.l1 = "Hát persze. Köszönöm... Most menj haza.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "Még mindig nem tudom összerakni magam. Megtennéd, hogy elhozol "+ GetSexPhrase("egy hölgyet","nekem") +" a településre " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "? Tudod, most már minden bokor mögött erôszaktevôk tûnnek fel nekem.";
			link.l1 = RandPhraseSimple("Ne aggódj annyira, tényleg... Rendben, menjünk.","Olyan gyáva vagy, nem igaz? Rendben, elviszlek oda.");
			link.l1.go = "Node_121Next";
			link.l2 = "Sajnálom, drágám, de egyszerûen nincs idôm, túl elfoglalt vagyok.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "Arra gondoltam, hogy csak elijeszted ôket! Most el kell vinned a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "településen lévô kocsmába, rajtad kívül nincs senki más, akitôl segítséget kérhetnék.";
			link.l1 = "Ó, a fenébe! Rendben, menjünk. Csak ne maradj le.";
			link.l1.go = "Node_122Next";
			link.l2 = "Nem, ez az, "+ GetSexPhrase("szépség","kedves") +"! Mára elég volt a meglepetésekbôl. Keress valaki mást, aki segít neked.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "És mit kellett volna tennem?! Az apám azt akarja, hogy menjek hozzá az uzsorás fiához, ahhoz a tejesemberhez... csak azért, mert az apjának egy rakás pénz van a kasszájában! De én egy másik férfit szeretek! Vigyél el hozzá, kérlek...";
			link.l1 = "Micsoda teher vagy! Nos, rendben, menjünk. Nem hagyhatlak csak úgy itt, ugye?... Hogy hívják a választottadat, hová vigyelek?";
			link.l1.go = "Node_32";
			link.l2 = "Nem, ez az, "+ GetSexPhrase("szépség","kedves") +"! Mára elég volt a meglepetésekbôl. Keress valaki mást, aki segít neked.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "A neve " + pchar.GenQuest.EncGirl.sLoverId + ", ô egy újonc. Jelenleg a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "településen tartózkodik , próbált ott munkát találni, de nehéz idôk járnak. Mindenki folyamatosan válságról beszél... És most már úgysem lehet hazajönni.";
			link.l1 = "Vészhelyzet? Ha... Egy igazi kalóz számára a válság az, amikor egy kereskedelmi karaván van a láthatáron, de nincs szél, hogy megtöltse a vitorlákat...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Tudja, "+ GetSexPhrase("kapitány","ifjú hölgy") +"? Annyira megijedtem, hogy még a lábam is remegett egy kicsit.","Ó, tudod, annyira megijedtem. Nagyszerû, hogy Isten elküldött hozzám.");
			link.l1 = RandPhraseSimple("Hála Istennek, hogy még élsz.","Ezt ne vedd a szívedre. Jó, hogy így alakult, tudod.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Köszönöm, "+ GetSexPhrase("kapitány","fiatal hölgy") +", még egyszer. Tényleg, nagyon hálás vagyok neked.","nagyon köszönöm, "+ GetSexPhrase("kapitány","ifjú hölgy") +". Fogalmam sincs, mihez kezdenék a segítséged nélkül.");
			link.l1 = RandPhraseSimple("Ez legyen tanulság számodra. Rendben, sok szerencsét...","Legközelebb óvatosabbnak kell lenned... Most pedig szaladj haza, nekem dolgom van.");
			link.l1.go = "Node_1End";
			link.l2 = "Hogy lehettél ilyen óvatlan? Miért mentél egyedül a dzsungelbe?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Meggondolta magát?","Kapitány úr, nagyszerû, hogy meggondolta magát!");
			link.l1 = RandPhraseSimple("Nem, nem, drágám, kihagyom.","Ne táplálj hamis reményeket...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "Valószínûleg ki fogsz nevetni, de... Szerelmi bájitalt gyûjtöttem... Egy boszorkány mondta, hogy van egy gyökér, ami segíthet a szerelmi ügyekben.";
						link.l1 = "Ó, Istenem! Mire "+ GetSexPhrase("gondolnak ezek a nôk","gondoltak") +"?! Úgy látszik, sokat gyûjtöttél belôlük, elég sok kérô üldözött, nehezen vertem le mindet. Ha-ha-ha-ha-ha... Viszontlátásra.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "Csak elmentem sétálni, hogy gyógynövényeket gyûjtsek és friss levegôt szívjak. Úgy tûnik, nem a legjobb idô a sétához.";
						link.l1 = "Micsoda figyelmetlenség?! Hála Istennek, hogy idôben érkeztem. Nos, sok szerencsét neked.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "Az úrnôm valahol itt szórta ki a nyakláncának gyöngyeit, amikor sétálni volt. Ahogy hazaért, rám kiáltott, és megparancsolta, hogy menjek ki és szedjem össze ôket. Azt mondta, 'Ne is mutatkozz itt, amíg össze nem szeded mindet!', És még a pontos helyet sem tudom. Különben is, hogy találjam meg ôket ebben a sûrû fûben? A gyöngyök olyan kicsik... Szóval, csak bolyongok itt, fogalmam sincs, hogy egyáltalán mit csináljak...";
					link.l1 = "És miféle nyaklánc volt ez? Talán egyszerûbb lenne egyszerûen venni egy újat, mint a dzsungelben bolyongani? Hány gyöngyöt vesztett el az úrnôd?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "Néhai apám hagyott rám egy térképet, és a társai el akarták venni tôlem. Amíg élt, mindannyian reszkettek elôtte a félelemtôl, de amint eltemettem, nyugtalan idôk kezdôdtek. Elôször megpróbálták megvenni tôlem ezt a térképet, de én visszautasítottam, ezért elkezdtek megfélemlíteni.";
					link.l1 = "És miért nem adtad el egyszerûen? Mi olyan különleges ebben a térképben, hogy kalózbandák keresik?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "Ez a nyaklánc válogatott gyöngyökbôl állt, ezeket nem lehet olcsón megvenni. Voltak " + sti(pchar.GenQuest.EncGirl.BigCoins) + " nagy gyöngyök és " + sti(pchar.GenQuest.EncGirl.SmallCoins) + " kisebbek. Ha ezek a gyöngyök elôkerülnének, akkor egy másik ilyen nyakláncot is megrendelhetnénk.";
			link.l1 = "Biztos, hogy ez nem lesz könnyû feladat... Nos, ha az úrnôd adott neked egy megrendelést, akkor nem sokat tehetsz. Próbáld meg megtalálni a gyöngyöket. Sok szerencsét.";
			link.l1.go = "Node_131End";
			link.l2 = "Semmi értelme. Könnyebb lenne tût találni a szénakazalban, mint gyöngyöt ebben a sûrû fûben. Arról nem is beszélve, hogy még azt sem tudod, hol veszett el a gyöngy...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "Apám megjelölt rajta egy helyet, ahová elrejtette a kincsét. Hallottál már a híres kalózról " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_VOC) + "?";
			link.l1 = "Nem, soha nem hallottam róla.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "Nos, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM) + " volt az apám. Mindenki félt tôle, senki nem mert egy szót sem szólni. Most persze szemtelenek lettek. Amikor nem voltam hajlandó eladni nekik a térképet, azt állították, hogy nekik is ki kell venniük a részüket a kincsbôl. El akartam rejteni a térképet, de ôk mégis a nyomomra bukkantak...";
			link.l1 = "És egyáltalán miért rejtegetnéd el? Bérelj egy hajót, és menj, követeld a kincset. Apád nem a semmiért rejtette volna el.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Könnyebb mondani, mint megtenni. Nincs pénzem hajót bérelni, és... Attól tartok... Hogy ássam ki az egészet, hogy vigyem a hajóra... És hová vinném utána a kincset? Bárki könnyû prédát csinálna belôlem útközben...";
			link.l1 = "Ez egy jó érv... Rendben, akkor menj és rejtsd el a térképet. Csak ne felejtsd el jól elhelyezni.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hmm... Ez valószínûleg igaz. Annál is inkább, mert el kellett volna adnod.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Próbáltál már társat találni?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "Elszomorít, hogy elvesztettem egy ilyen lehetôséget... Apa mesélt nekem a kincsekrôl, amiket ott rejtett el. Senki sem fizetne nekem ennyit...";
			link.l1 = "Nos, ne add el túl olcsón. És különben is, az arany nem éri meg az életedet. Arról nem is beszélve, hogy ez a legkönnyebb út számodra, csak összeszeded a pénzt, és megszabadulsz minden gondtól...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "Ez csábítóan hangzik... És mennyit tudsz érte ajánlani?";
			link.l1 = "Nem hiszem, hogy többet érhet, mint " + sti(pchar.GenQuest.EncGirl.mapPrice) + " pezó.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Nônek lenni nem könnyû... Rendben, egyetértek. Végre vége lesz ennek a rémálomnak... Talán jobb is, hogy ez a térkép a tiéd,"+ GetSexPhrase(" egy nemes úriemberé","") +", mint azoké a gazembereké.";
				link.l1 = "Jól van. Itt a pénzed... csak próbáld meg nem egyszerre elkölteni.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "Nem, "+ GetSexPhrase("kapitány","fiatal hölgy") +". Nem fogom eladni. Hozzámegyek egy jó emberhez, és akkor együtt követeljük a kincset.";
				link.l1 = "Nos, ez a döntés rajtad múlik. A te papírdarabkád amúgy sem ér többet.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap, "");
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "És hol fogom megtalálni ôket? A fiatalok nem megbízhatóak, és nem nagyon törôdnek a kincsekkel annyira, mint, más dolgokkal. Az idôsebbektôl pedig félek, mind apám haverjaira emlékeztetnek. Olyan ravaszak és alattomosak, hogy az ember sosem tudná, mire számítson tôlük.";
			link.l1 = "Ha-ha-ha-ha... Rendben, de magaddal viszel?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "És te? És elmennél? De akkor vissza kell hoznod ide, a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "településre, rendben?";
			link.l1 = "Rendben, a szavamat adom. Csak mutasd meg az utat.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "A kincs a " + XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc") + "barlangban van elrejtve, a " + XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen") + "helyen kell leszállnunk, ahol megmutatom magam... De ne felejtsétek el, hogy csak a felét kapjátok meg!";
			link.l1 = "Rendben, nem foglak becsapni, ígérem. Kövessetek és ne essetek vissza.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Kapitány, most meg kell találnunk a barlangot.";
			link.l1 = "Rendben, nézzük meg most.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Kapitány, meg kell találnunk a barlangot.";
			link.l1 = "Rendben, nézzük meg most.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "Itt van! Megtaláltam! Ahogy apám mondta! Egy hatalmas halom kincs! A fele a tiéd, ahogy megbeszéltük.";
			link.l1 = "Látod? Nem volt nehéz, szóval nem volt mitôl félni.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ha-ha-ha-ha! Most már gazdag vagyok! Elveszed most a részed?";
			link.l1 = "Gondolom.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "Akkor vedd el, és kérlek, segíts nekem, hogy az összes cuccot a hajóra cipeljem. Emlékszel még arra, hogy megígérted, hogy hazaviszel?";
			link.l1 = "Nem felejtettem el! Persze, elviszlek.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("Megkaptad a kincsbôl a részed");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Gazdagnak lenni egyszerûen nagyszerû! Olyan másképp érzem magam."; 
			link.l1 = "Örülök neked.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "Rendben, kapitány. Az én utamnak vége. Köszönöm a segítségét.";
			link.l1 = "Szívesen... Szóval, mit tervezel kezdeni az újonnan szerzett gazdagságoddal? Veszel egy ültetvényt rabszolgákkal?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "Nem tudom, még nem döntöttem el. Talán Európába költözöm...";
			link.l1 = "Jól van, rendben! Sok szerencsét neked.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Várj egy kicsit... Ez a csecsebecse apám kincsei között volt. Nekem nincs rá szükségem, de neked talán tetszeni fog. Kérlek, fogadd el személyes hálám jeléül azért, amit értem tettél. Ez az én részembôl van, ha-ha-ha-ha!";
			link.l1 = "Hû, ez aztán a szép ajándék. Köszönöm"+ GetSexPhrase(", szépség","") +". Találj magadnak egy szép vôlegényt, jó lesz...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "De mit tehetnék? Nem hagyhatom figyelmen kívül az úrnôm parancsait, élve megnyúzna.";
			link.l1 = "Várj meg a település templomában " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + ", elhozom neked a gyöngyöket, hogy új nyakláncot készíts.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Tessék. Fogd ezt a 15000 pezót. Ez több mint elég lesz, hogy kiválassza a gyöngyöket a nyaklánchoz, vagy vegyen egy újat.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+ GetSexPhrase("Kapitány","ifjú hölgy") +", annyira örülök, hogy újra látom! Sikerült gyöngyöket gyûjtened a nyaklánchoz?","Üdvözlöm, kapitány úr! Elhoztad nekem a gyöngyöket? Tudja, az úrnôm kezd nagyon ideges lenni...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Igen. Itt vannak a gyöngyök. Vidd el az úrnôdnek, és mondd meg neki, hogy legközelebb legyen óvatosabb.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Még nem. Ez nem olyan könnyû, tudod... De elhozom ôket, csak várj.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Ó, "+ GetSexPhrase("kapitány","ifjú hölgy") +", annyira örülök, hogy megismertelek! Hálám jeléül mindazért, amit értem tettél, szeretném neked adni ezt a csecsebecsét és ezeket a drágaköveket. Remélem, hogy hasznosnak találod majd ôket.";
			link.l1 = "Hûha! Nos, köszönöm is"+ GetSexPhrase(", szépség","") +", nem vártam... Viszlát, és légy boldog.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Ó, "+ GetSexPhrase("kapitány","ifjú hölgy") +", számítok rád.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Ó, "+ GetSexPhrase("kapitány","ifjú hölgy") +", ma már másodszor segített ki. Köszönöm szépen. Soha nem fogom elfelejteni a kedvességét.";
			link.l1 = "Szívesen. Mondd 'hi' az úrnôdnek...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("Nem kellett volna pénzt adnod nekik. Hazudtak.","Ne higgy nekik. Hazugok. És nem kellett volna pénzt adnod nekik.");
					link.l1 = "Meg kellett volna ölnöm ôket?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Ó, micsoda nemes tett! Rögtön láttam, hogy Ön "+ GetSexPhrase("egy igazi úriember","egy nemes hölgy") +"! Kérem, fogadja legôszintébb hálámat. Remélem, nem hitted el, amit ezek a gazemberek mondtak?";
					link.l1 = "Az nem számít. Egy lány és egy csapat rongybaba a dzsungelben, ez olyan természetes...";
					link.l1.go = "Node_210";
					link.l2 = "Mirôl beszélsz, "+ GetSexPhrase("szépség","kedves") +"? Hogy is tehettem volna?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Köszönöm, kapitány. Sajnálom, hogy belekevertelek ebbe a kellemetlen ügybe, de egyszerûen nem volt más választásom.";
					link.l1 = "Nos, látom, hogy maga is eléggé elakadt. Hogy jutottunk idáig?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Talán... Most már soha nem hagynak békén.";
				link.l1 = "Ó, ugyan már! Csak menj haza, most már nincs mitôl félned.";
				link.l1.go = "Node_200End";
				link.l2 = "Hûha! Miért van ilyen ellenszenved a férfiakkal szemben?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Persze, hogy nem! De amúgy sem hagynak békén. Elvinnél a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "településre, kérlek?";
				link.l1 = "Csak menj haza, nem fognak hozzád nyúlni. Nekik most a kocsmába kellene menniük, hogy elpazarolják a könnyû pénzüket.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Ne aggódj annyira, tényleg... Rendben, menjünk.","Olyan gyáva vagy, nem igaz? Rendben, elviszlek oda...");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "Ó, ne, mit mondasz? Túl jól ismerem ezeket a gazembereket. Apám egykori cimborái. Megpróbálják megtalálni azt a helyet, ahová elrejtette a kincseit.";
			link.l1 = "És mi a helyzet az apáddal?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "Egy kalózhajó kapitánya volt. Nemrég meghalt... Mindannyian olyan udvariasak voltak a temetéskor, de ahogy telt az idô, elfelejtették ôt, és nem sokkal késôbb a becsületüket és a becsületességüket is. Jó, hogy észrevettem ôket. Amint megtudják, hol vannak a kincsek, nekem végem.";
			link.l1 = "Ez egy szomorú történet. Szóval, azt tervezed, hogy tovább bujkálsz elôlük?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "Nem tarthatok otthon ékszereket, nincs, aki megvédjen. Ezért megyek éjjel a barlangba, amikor elfogy a pénz...\nVigyél, kérlek, a barlangba, és odaadom a pénzt, amit adtál nekik ... Azt hiszem, a kalózok nem kockáztatnák meg, hogy kövessenek minket, amíg velem vagy.";
			link.l1 = "Sajnálom, drágám, de más terveim vannak. Majd máskor begyûjtöd a kincset.";
			link.l1.go = "Node_200End";
			link.l2 = "Rendben, menjünk, ha nem félsz tôlem.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "Tudod, valamiért nem félek...";
			link.l1 = "Nos, ez jó dolog.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Kapitány, megígérte, hogy elvisz a barlanghoz.";
			link.l1 = "Menjünk...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "Rendben, kapitány, annyi van, amennyire szükségem volt. Most már visszatérhetünk.";
			link.l1 = "Látom, a haverjaid nincsenek itt.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Hála Istennek. Nem akarok több bajt... Tessék, fogd ezeket az érméket... ez elég lesz a költségeid fedezésére. Menjetek egyedül, én más utat választok...";
			link.l1 = "Rendben, sok szerencsét, ha nem félsz.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Hmm, "+ GetSexPhrase("kapitány","ifjú hölgy") +", nem tetszik az iróniája.";
			link.l1 = "Jól van, mehetsz, "+ GetSexPhrase("szépség","kedves") +". És inkább sietsz a városba, mielôtt újra üldöznek.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "Annyira izgatott voltam! Megtennéd, hogy elviszel a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "településen lévô kocsmába ? Különben, attól tartok, megint üldözni fognak.";
			link.l1 = "Talán igazad van. Menjünk...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Ó, kapitány, ez egy hosszú történet, és nem vagyok benne biztos, hogy érdekesnek találná. Bár... Most sem fogom megtenni a segítsége nélkül. Megtenné, hogy elvisz a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "településen lévô kocsmába ? Attól tartok, hogy nem hagynának békén.";
			link.l1 = "Sajnálom, drágám, erre nincs idôm. Dolgom van.";
			link.l1.go = "Node_221";
			link.l2 = "Miért vagy ilyen titokzatos?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "És hogy ne legyek titokzatos, ha mindenki hasznot akar húzni a szerencsétlenségembôl?";
			link.l1 = "Rendben, akkor...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Kapitány, megígérte, hogy elvisz a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + "településen lévô kocsmába.";
			link.l1 = RandPhraseSimple("Emlékszem.","Ne aggódj, ott találkozunk.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "Túl sok ember van ott. Menjünk a privát szobába. El kell mondanom valamit.";
					link.l1 = LinkRandPhrase("Már így is túl sokat tettem érted, úgyhogy most búcsúzz el tôled.","Nem kellene visszaélned a kegyeimmel. Viszlát, drágám.","Mostantól nincs szükségem a történeteidre, magad is rájössz mindenre.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, rendben. Akkor elveszem a kulcsokat a csapostól.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Köszönöm szépen a segítségét, kapitány. Nem fogom elfelejteni.";
					link.l1 = "Ó, ne fáradjon. Csak próbáljon meg óvatosabb lenni a jövôben.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Köszönöm szépen a segítségét, kapitány. Nem fogom elfelejteni.";
					link.l1 = "Ó, ne fáradjon. Csak próbáljon meg óvatosabb lenni a jövôben.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "Túl sok ember van ott. Menjünk a privát szobába. El kell mondanom valamit.";
					link.l1 = LinkRandPhrase("Már így is túl sokat tettem érted, úgyhogy most búcsúzz el tôled.","Nem kellene visszaélned a kegyeimmel. Viszlát, drágám.","Mostantól nincs szükségem a történeteidre, magad is rájössz mindenre.");
					link.l1.go = "Node_226";
					link.l2 = "Hmm, rendben. Akkor elveszem a kulcsokat a csapostól.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Szóval, még mindig akarja hallani a történetemet?";
				link.l1 = "Hmm... Azt hiszem, itt az ideje, hogy elmenjek. Viszlát!";
				link.l1.go = "Node_232";
				link.l2 = "Nos, akkor köpd ki.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Ó, nemes megmentôm, végre eléggé meg tudom neked köszönni úgy, ahogy csak egy nô tudja megköszönni\nAmikor megláttalak a dzsungelben, minden megváltozott bennem. Elfelejtettem a megerôszakolókat és az éles pálmaleveleket, amelyek az arcomon korbácsoltak. Elfelejtettem, hová fussak, miért fussak ... Csak téged láttalak. És csak téged akartalak ... És azok után, amit értem tettél...";
				link.l1 = "Hûha! Micsoda temperamentum! Az üldözôid biztosan tudták, kit kell üldözni...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Figyelj, szépségem, én tökéletesen megértem, de kérlek, tartsd meg magadnak az indulataidat.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Gyere hozzám, hôsöm...";
			link.l1 = "Ó, drágám...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Ó! Hogy... Hogy merészeled?! Micsoda szemétláda! Egy lány teljes szívébôl és lelkébôl köszönetet mondott neked, és te...";
			link.l1 = "Hát, ha nem flörtölnél annyit, és nem csinálnál egy halottat az elsô férfinak, akivel találkoztál, biztosan kevesebb bajod lett volna. Többé nem mentem meg az ilyen flörtölôket a dzsungelben...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "Még soha nem hallottam ilyen szavakat senkitôl! És nem bocsátom meg nekik! Még emlékezni fogsz rám!";
			link.l1 = "Menj már, rendben? És próbálj meg felfrissülni, hacsak nem akarod, hogy újra megmentselek...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "A családom a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City) + "településen él. Véletlenül kerültem ide, azon a hajón, amin a vôlegényem vitt volna a szüleihez, de azt kalózok elfogták. A hajót elvitték, az utasokat pedig a nem messze innen lévô öbölben kötöttek ki. A vôlegényemet a hajóra szállás közben megölték, én pedig a dzsungelen való átkelés alatt súlyosan megbetegedtem\nA helyi bordélyház asszonya kezelt, és amikor talpra álltam, követelte a kezelésre költött pénzt. Kurva voltam, de nem voltam a Madame kedvére, ezért Ma'am eladott néhány banditának, hogy legalább némi pénzt keressek. A történet másik részét ismered.";
			link.l1 = "Szóval csak lépj ki és térj haza! Miért hagyod, hogy rabszolgaként bánjanak veled?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "Nem tehetem! Minden holmim: tisztességes ruhák, pénz, iratok... Mind a bordélyházban van az utazótáskámban. Elrejtettem a randiszobában. És amíg így vagyok felöltözve, a kikötôben minden matróz utánam fog futni. És ki vesz fel a fedélzetre okmányok és pénz nélkül? És most még a képemet sem mutathatom a városban, különben rács mögé kerülök...";
			link.l1 = "Nem lehet probléma. Gyerünk, menjünk. Én magam viszlek haza.";
			link.l1.go = "Node_235";
			link.l2 = "Várj itt. Hozom az utazótáskádat.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "Kit érdekelnek a papírjaid? Mennyi pénzre van szükséged, hogy hazajuss?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Ó, köszönöm, kapitány úr... De... tudja, nincs semmim, amivel fizethetnék.";
			link.l1 = "Milyen fizetségrôl beszélsz? Menjünk, mielôtt megtalálják ôket...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Ó, kapitány, tudja, én soha nem merném megkérdezni...";
			link.l1 = "Ne féljen. Hamarosan visszajövök.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Ó, már aggódtam, hogy valami történhetett veled.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "Mi történhetett? Tessék, fogd a cuccaidat.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Figyelj, nem találtam ott semmit. Biztos vagy benne, hogy az utazótáskádat a randiszobában hagytad?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Köszönöm, "+ GetSexPhrase("nemes kapitány","nemes lány") +". Soha nem felejtem el, amit értem tettél. Nincs sok mindenem, de kérlek fogadd el ezt az amulettet. Talán ez a csecsebecse mentette meg az életemet a kalóztámadás során.";
			link.l1 = "Köszönöm és jó utat! Viszontlátásra...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Tényleg megtalálták a táskámat?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "Mennyi pénzre van szükséged, hogy hazajuss?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Talán igen. Mindenesetre, az utak itt elválnak. Viszontlátásra!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Köszönöm, kapitány. Tudja, nehéz elhinni, hogy végre itthon vagyok. Kérem, jöjjön velem, bemutatlak a szüleimnek.";
			link.l1 = "Figyelj, "+ GetSexPhrase("szépség","drága") +", erre tényleg nincs idôm. Talán majd máskor?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "Milyen kár... Nos, akkor viszlát, és az Úr vigyázzon rád. Nincs semmim, amivel meghálálhatnám, de kérlek fogadd el ezt az amulettet.";
			link.l1 = "Köszönöm! Fuss haza, hogy a szüleid boldogok legyenek!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Hát, nem is tudom... Talán meg kell várnom egy átutazót. De pénzt nem kérhetek tôled.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Értem. Rendben, vegyél 5000 pezót. Ez elég lesz.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Értem, értem. Rendben, fogj 25000 pezó-t és menj haza.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "Értem. Rendben, vegyél 35000 pezó-t. Ez elég lesz a legjobb kabinra a hajón.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Köszönöm, "+ GetSexPhrase("nemes kapitány","nemes lány") +". Soha nem felejtem el, amit értem tettél.";
			link.l1 = "Akkor jó utat. Viszontlátásra...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Köszönöm, "+ GetSexPhrase("nemes kapitány","nemes lány") +". Soha nem felejtem el, amit értem tettél.";
			link.l1 = "Akkor jó utat. Viszontlátásra...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Köszönöm, "+ GetSexPhrase("nemes kapitány","nemes lány") +". Soha nem felejtem el, amit értem tettél.";
			link.l1 = "Akkor jó utat. Viszontlátásra...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Hallottad? Egy kurva megpróbált felszökni egy hajó fedélzetére papírok nélkül, de elkapták és visszavitték a bordélyházba. Azt mondják, hogy a hölgynek elég nagy összeggel tartozott.",  
				"Hallottad? Egy okmányok nélküli kurvát kaptak el a kikötôben. Azt mondják, a madám pénztárcáját tisztogatta, mielôtt megpróbált elmenekülni a bordélyházból. Mondom, ezt a mocsok és tolvajlás forrását már régen el kellett volna zárni. Még a gyerekeink is ezt látják, és mit tanulhatnak egy ilyen példából?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Ne tegye tönkre az életemet, kapitány úr! Az apám azt akarja, hogy menjek hozzá az uzsorás fiához, ahhoz a mocskos tejesemberhez... csak azért, mert az apjának egy rakás pénz van a kasszájában! Nos, inkább maradok a dzsungelben, hogy felfaljanak a vadállatok, minthogy életfogytiglant kapjak vele!";
			link.l1 = "Mi a baj a házasságoddal, "+ GetSexPhrase("szépség","drága") +"? Tartsd meg azt, aki feleségül akar venni, és légy boldog. Egy idô múlva már boldog lennél, ha elvehetnéd azt a tejfelesszájú férfit, de lehet, hogy már késô lesz...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Nem! Nem, kapitány, szeretem " + pchar.GenQuest.EncGirl.sLoverId + " és nem megyek hozzá más férfihoz! És az apám hallani sem akar semmirôl! Azt mondja, hogy " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) + " csak látogatóban van itt, ezért soha nem fog itt munkát találni, és az a sorsa, hogy szegénységben haljon meg, és én vele együtt! És én a világ végére is vele tartanék, csak hogy mellette lehessek! Vigyél el hozzá, könyörgöm!";
			link.l1 = "Rendben, menjünk. Azt hiszem, majd kitalálom, mit csináljak veled...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Kapitány, megígérte, hogy elvisz a " + XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city) +"településre.";
			link.l1 = RandPhraseSimple("Emlékszem.","Ne aggódj, elviszlek oda.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Köszönöm, "+ GetSexPhrase("kapitány","fiatal hölgy") +", még egyszer. Tényleg, nagyon hálás vagyok neked.","nagyon köszönöm, "+ GetSexPhrase("kapitány","ifjú hölgy") +". Fogalmam sincs, mihez kezdenék a segítséged nélkül.");
				link.l1 = RandPhraseSimple("Ez legyen tanulság számodra. Rendben, sok szerencsét...","Legközelebb óvatosabbnak kell lenned... Most pedig szaladj haza, nekem dolgom van.");
				link.l1.go = "Node_260End";
				link.l2 = "Hogy lehettél ilyen óvatlan? Miért mentél egyedül a dzsungelbe?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Ó, "+ GetSexPhrase("kapitány","ifjú hölgy") +", tényleg fogalmam sincs, hogyan köszönjem meg.";
				link.l1 = "Semmiség volt. Mindig örömmel segítek...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "El tudsz vinni a kocsmába? Meg kell várnom a nénikémet, és pihennem kell egy kicsit, ez 'kaland' minden energiámat elszívta...";
			link.l1 = "Nem, "+ GetSexPhrase("szépség","drága") +", ez nekem biztosan elég. Sok dolgom van még.";
			link.l1.go = "Node_262";
			link.l2 = ""+ GetSexPhrase("Ó, nôk! Van bármi, amit férfi segítsége nélkül meg tudnak csinálni?","Miért vagy ilyen tehetetlen?") +" Menjünk...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "Van egy kis pénzem... Kérlek, fogadd el hálám jeléül!";
				Link.l1 = "Köszönöm. Köszönöm. Legközelebb próbálj meg óvatosabb lenni.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "Mindenkinek el fogom mondani, hogy megmentettél! Hadd tudja meg mindenki, "+ GetSexPhrase("milyen bátor és bátor férfi vagy","milyen bátor és bátor hölgy vagy") +"!";
					Link.l1 = "Köszönöm. És most menj haza.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "Van egy kis pénzem... Kérlek, fogadd el hálám jeléül!";
					Link.l1 = "Köszönöm. Köszönöm. Legközelebb próbálj meg óvatosabb lenni.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "Mindenkinek el fogom mondani, hogy megmentettél! Hadd tudja meg mindenki, "+ GetSexPhrase("milyen bátor és bátor férfi vagy","milyen bátor és bátor hölgy vagy") +"!";
			Link.l1 = "Köszönöm. És most menj haza.";
			Link.l1.go = "exit";
		break;
	}
}
