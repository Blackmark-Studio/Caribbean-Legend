void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Jelenleg semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//Найти помощника в магазин
		case "Storehelper":
			DelLandQuestMark(npchar);
			dialog.text = "Szüksége van valamire, uram?";
			link.l1 = "Ön Gralam Lavoie, igaz?";
			link.l1.go = "Storehelper_1";
		break;
		
		case "Storehelper_1":
			dialog.text = "Ki kérdezi? Ne zavarjon, amíg rumot iszom, uram. Nincs kedvem beszélgetni.";
			link.l1 = "Nem fogom sokáig rabolni az idejét. Egy Saint-Pierre-i kereskedô küldött ide. Ön volt a korábbi alkalmazottja. Önt keresi és...";
			link.l1.go = "Storehelper_2";
		break;
		
		case "Storehelper_2":
			dialog.text = "Ha, engem keres!? Milyen gazdag ez a kibaszott szarházi! Tényleg azt hitte, hogy egész életemben ilyen csekély fizetésért fogok dolgozni? Ô a legkapzsibb filléres a Karib-tengeren! Öt évig dolgoztam neki, és soha egy fillérrel sem fizetett többet, mint amennyivel megúszta! Bah, még egy italra sem volt elég!\nMost már számolhatja a saját áruját, én kilépek. Saint-Pierre-ben senki sem fog ennek a fukarnak dolgozni, az biztos. Egyetlen érdeke van: többet keresni magának, és kevesebbet fizetni az embereinek.";
			link.l1 = "Gondolom, nem fogsz neki dolgozni?";
			link.l1.go = "Storehelper_3";
		break;
		
		case "Storehelper_3":
			dialog.text = "Nem, Isten verjen meg, ha mégis! Itt fogok várni Le Francois-ban, hogy megérkezzen egy hajó, és ha felvesznek, beállok pénztárosnak. És ha ez nem jön össze, akkor majd egyszerû matrózként dolgozom. Még a szememet sem bírom rávetni arra a pénzsóvárra. Ha már szegény leszek, akkor lehetek szabad ember is...";
			link.l1 = "Értem, ennyit kellett tudnom. Sok szerencsét, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_4":
			DelLandQuestMark(npchar);
			dialog.text = "Uram, lépjen félre. Az utamban áll!";
			link.l1 = "Csak egy kérdés, uram. Ön Gralam Lavoie?";
			link.l1.go = "Storehelper_5";
		break;
		
		case "Storehelper_5":
			dialog.text = "Ha! Igen, én vagyok. Mit akar?";
			link.l1 = "Egy St. Pierre-i kereskedô keresi önt. Neki dolgozott, ugye?";
			link.l1.go = "Storehelper_6";
		break;
		
		case "Storehelper_6":
			dialog.text = "Ha-ha! Micsoda vicc! És mit akar tôlem ôfelsége? Úgy döntött, hogy kifizeti nekem az utolsó két hét munkájáért hiányzó fizetésemet? Vagy gondjai vannak a hordók számolásával és a vásárlók becsapásával egyszerre, mi? Ha-ha-ha-ha!";
			link.l1 = "Megkért, hogy keresselek meg, és tisztázzam, miért nem jössz többé a boltjába dolgozni.";
			link.l1.go = "Storehelper_7";
		break;
		
		case "Storehelper_7":
			dialog.text = "Miért? Mert egy kibaszott fösvény és szörnyû munkaadó! Most már a Parti Testvérek tagja vagyok, szabad ember és rabszolga többé nem! Nézzetek körül, nagyon jól érzem magam!\nHamarosan kihajózom, és banános ládák helyett a spanyoloktól elvett pesókat és dublónokat fogom számolni! És ami azt a szkinhedet illeti - kétlem, hogy találna valakit, aki helyettesíthetne engem. Saint-Pierre-ben senki sem olyan hülye, hogy neki dolgozzon, a sziget összes tanoncának elterjesztettük a hírét, ha-ha!";
			link.l1 = "Értem én. Ennyit kellett tudnom. Sok szerencsét, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_8":
			DelLandQuestMark(npchar);
			dialog.text = "Miben segíthetek?";
			link.l1 = "Jó napot, Gralam! Gralam Lavoie, ugye?";
			link.l1.go = "Storehelper_9";
		break;
		
		case "Storehelper_9":
			dialog.text = "Igen, uram. Mit akar, monsieur?";
			link.l1 = "Egy Saint-Pierre-i kereskedô keresi önt. Neki dolgozott, ugye?";
			link.l1.go = "Storehelper_10";
		break;
		
		case "Storehelper_10":
			dialog.text = "Nos, hadd keressen tovább. Nem tartozom neki semmivel. Még mindig tartozik nekem két heti bérrel, de nem is fogok fáradozni azzal, hogy elkérjem tôle a pénzemet. Remélem, megfullad a saját pénzétôl.";
			link.l1 = "Hm. Szóval végleg elhagyta ôt, ha jól sejtem?";
			link.l1.go = "Storehelper_11";
		break;
		
		case "Storehelper_11":
			dialog.text = "Mindenben igaza van, uram. Az én volt munkaadóm a fösvénység ritka példánya, valóban bibliai léptékû. Most már a Parti Testvér vagyok, és új társaim nagyra értékelik a tehetségemet. Kétszer annyit kapok, plusz bónuszokat\nKétlem, hogy kedves barátunk találna valakit a helyemre. Kapzsisága jól ismert a Saint-Pierre-i emberek körében, ott senki sem olyan ostoba, hogy neki dolgozzon.";
			link.l1 = "Igen. Csak ennyit akartam tudni. Sok szerencsét, Gralam!";
			link.l1.go = "Storehelper_12";
		break;
		
		case "Storehelper_12":
			DialogExit();
			npchar.lifeday = 0;
			AddQuestRecord("SharlieA", "2");
			pchar.questTemp.Sharlie.Storehelper = "return";
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.StorehelperOver.over = "yes"; //снять таймер
			
			pchar.quest.Sharlie_JungleBandos.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleBandos.win_condition.l1.location = "Martinique_Jungle_01";
			pchar.quest.Sharlie_JungleBandos.function = "SharlieJungleBandos";
			
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload6_back");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("lefransua_exittown", "reload", "reload1_back");
		break;
		
		case "Newstorehelper_1":
			dialog.text = "Jó napot, uram. Nem akarok túlságosan tolakodó lenni, de úgy vélem, hogy a jelölésem nagyon is megfelel az ön által felajánlott pozíciónak.";
			link.l1 = "Jó napot kívánok. És miért gondolja ezt?";
			link.l1.go = "Newstorehelper_1_1";
		break;
		
		case "Newstorehelper_2":
			dialog.text = "Üdvözlöm, uram! Engedje meg, hogy meséljek egy kicsit magamról.";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "Newstorehelper_2_1";
		break;
		
		case "Newstorehelper_3":
			dialog.text = "Jó egészséget kívánok, kedves uram. Kereskedôi állást kínál?";
			link.l1 = "Igen, kínálok. Mit tud mondani magáról?";
			link.l1.go = "Newstorehelper_3_1";
		break;
		
		case "Newstorehelper_1_1":
			dialog.text = "Én magának Francis Dubois kapitánynak a parancsnoksága alatt szolgáltam szállásmesterként. Elégedett volt a képességeimmel, de a csatában megsérültem, és szabadságot kellett kivennem, hogy kezeltessenek. Most már jól vagyok, teljesen ép testtel, de a hullámok hullámzásának gondolatától rosszul vagyok. Nem, az egyetlen vágyam most az, hogy a szilárd földön maradjak\n(suttogás) És ha engem választasz, ötszáz pezót és huszonöt aranydublont fizetek érte pluszban.";
			link.l1 = "Értem. Meggondolom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_1":
			dialog.text = "Korábban házaló kereskedô voltam, de néhány adós elôl menekülnöm kellett, és a tengerre mentem, mint pénztáros egy kereskedelmi hajón. A sors hozott ebbe a faluba. A tengerészélet amúgy sem tetszett túlságosan, és szívesen elfogadom az ajánlatodat\n(suttogás) És ha engem választasz, nemcsak ötszáz pezót adok neked, hanem ezt a nehéz borostyáncsomagot is.";
			link.l1 = "Értem. Meggondolom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_1":
			dialog.text = "Az egyik glasgow-i kikötôi raktárban voltam hivatalnok. A Karib-szigetekre a gazdagság keresése miatt jöttem, és sikerült annyi pénzt keresnem, hogy méltósággal éljem meg öregkoromat. De belefáradtam a tengeri utakba, és szeretnék nyugodt életet élni a parton\n(suttogás) És ha engem választ, adok ötszáz pezót, plusz további kétezerötszáz peso ráadásként.";
			link.l1 = "Értem. Meggondolom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_2":
			dialog.text = "Monsieur, döntsön helyesen. És ne feledkezzen meg a dublónokról...";
			link.l1 = "Az ön javára döntöttem. Szedd össze magad. Saint-Pierre-be megyünk.";
			link.l1.go = "Newstorehelper_1_3";
			link.l2 = "Még mindig nem döntöttem...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_1_2";
		break;
		
		case "Newstorehelper_2_2":
			dialog.text = "Remélem, engem választ, uram. És a borostyán is elég értékes, hasznos dolog...";
			link.l1 = "Az ön javára döntöttem. Szedd össze magad. Saint-Pierre-be megyünk.";
			link.l1.go = "Newstorehelper_2_3";
			link.l2 = "Még mindig nem döntöttem...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_2_2";
		break;
		
		case "Newstorehelper_3_2":
			dialog.text = "A kereskedô nem fog csalódni a munkámban. És ne feledkezzen meg a jutalmáról sem.";
			link.l1 = "Az ön javára döntöttem. Szedd össze magad. Saint-Pierre-be megyünk.";
			link.l1.go = "Newstorehelper_3_3";
			link.l2 = "Még mindig nem döntöttem...";
			link.l2.go = "exit";
			NextDiag.TempNode = "Newstorehelper_3_2";
		break;
		
		case "Newstorehelper_1_3":
			dialog.text = "Csak hadd szedjem össze a dolgaimat! A kocsma bejáratánál várom önt.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 0;
		break;
		
		case "Newstorehelper_2_3":
			dialog.text = "Mindjárt ott leszek, uram! A kocsma bejáratánál várom.";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 1;
		break;
		
		case "Newstorehelper_3_3":
			dialog.text = "Hozom a régi bôröndömet, és a kocsma bejáratánál várom önt, uram!";
			link.l1 = "...";
			link.l1.go = "Newstorehelper_exit";
			pchar.questTemp.Sharlie.Storehelper.Quality = 2;
		break;
		
		case "Newstorehelper_exit":
			DialogExit();
			pchar.questTemp.Sharlie.Storehelper.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay")
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Newstorehelper_"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			pchar.quest.storehelper4.win_condition.l1 = "location";
			pchar.quest.storehelper4.win_condition.l1.location = "FortFrance_store";
			pchar.quest.storehelper4.function = "NewstorehelperRegard";
			AddQuestRecord("SharlieA", "4");
			pchar.questTemp.Sharlie.Storehelper = "choise";
			pchar.quest.storehelper.over = "yes"; //снять прерывание
			
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			
			SetLaunchFrameFormParam("Vissza Saint-Pierre-be...", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("FortFrance_store", "reload", "reload1", "");
			LaunchFrameForm();
		break;
		
		case "Newstorehelper_regard":
			dialog.text = "Nos, gondolom, mostantól itt dolgozom? Köszönöm, uram, hogy engem választott. Itt van az ötszáz pezója és a bónusz a tetején, ahogy ígértem.";
			link.l1 = "Hálámat fejezem ki... Hadd mutassam be a munkaadójának.";
			link.l1.go = "Newstorehelper_regard_1";
		break;
		
		case "Newstorehelper_regard_1":
			DialogExit();
			npchar.lifeday = 0;
			switch (sti(pchar.questTemp.Sharlie.Storehelper.Quality))
			{
				case 0:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "gold_dublon", 25);
				break;
				
				case 1:
					AddMoneyToCharacter(pchar, 500);
					TakeNItems(pchar, "jewelry8", 10);
					TakeNItems(pchar, "jewelry7", 1);
				break;
				
				case 2:
					AddMoneyToCharacter(pchar, 3000);
				break;
			}
		break;
		
		//контрабанда рома
		case "Rum_Cap_Over":
			dialog.text = "Monsieur, meg kell kérnem, hogy azonnal hagyja el a hajómat. Horgonyt vetünk és indulunk!";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rum_Cap_Over";
			chrDisableReloadToLocation = false;
			npchar.DontDeskTalk = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
		break;
		
		case "Rum_Cap":
			pchar.quest.Sharlie_rum2.over = "yes"; //снять таймер
			chrDisableReloadToLocation = false; // patch-4
			dialog.text = "Nos? Ki maga, pajtás?";
			//link.l1.edit = 1;			
			link.l1 = ""+pchar.questTemp.Sharlie.Rum.Pass+"!";
			link.l1.go = "Rum_Cap_1";
		break;
		
		case "Rum_Cap_1":
			dialog.text = "Igyál egy kis rumot, matróz! Ha-ha! Isten hozta a hajóm fedélzetén. A termékért jött?";
			link.l1 = "A termék miatt jöttél? Mi másért lennék itt?";
			link.l1.go = "Rum_Cap_2";
			/* if(GetStrSmallRegister(pchar.questTemp.Sharlie.Rum.Pass) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Igyál egy kis rumot, matróz! Ha-ha! Isten hozta a hajóm fedélzetén. A termékért jött?";
				link.l1 = "A termék miatt jöttél? Mi másért lennék itt?";
				link.l1.go = "Rum_Cap_2";
			}
			else
			{
				dialog.text = "Nahát, nahát, micsoda zöld kurafi! Fiúk, ez úgy néz ki, mint egy nyers újonc! Dobjuk ki a fedélzetre!";
				link.l1 = "Hup!";
				link.l1.go = "Rum_Cap_getout";
			} */
		break;
		
		case "Rum_Cap_getout":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			setCharacterShipLocation(pchar, "Shore38"));
			setWDMPointXZ("Shore38");
			DoQuestReloadToLocation("Shore38", "goto", "goto1", "Rum_RemoveBarkas");
		break;
		
		case "Rum_Cap_2":
			dialog.text = "Fiúk! Pakoljátok a ládákat a hajóra!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rum_CarrierEnter");
		break;
		
		case "Rum_Cap_3":
			dialog.text = "Az összes láda rum a hajón van. Kikötô Le Francois innen délre található. Siessetek, ideje, hogy én is behúzzam a horgonyt!";
			link.l1 = "Ne vesztegessük az idôt, uraim! Sok szerencsét!";
			link.l1.go = "Rum_Cap_4";
		break;
		
		case "Rum_Cap_4":
			dialog.text = "Neked is, pajtás...";
			link.l1 = "...";
			link.l1.go = "Rum_Cap_5";
		break;
		
		case "Rum_Cap_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Deck_Near_Ship")], false);
			npchar.DontDeskTalk = true;
			NextDiag.CurrentNode = "Rum_Cap_Over";
			pchar.quest.Sharlie_rum4.win_condition.l1 = "Ship_location";
			pchar.quest.Sharlie_rum4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Sharlie_rum4.function = "Rum_RemoveRum";
			AddQuestRecord("SharlieB", "4");
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 3000;
			
			DoQuestFunctionDelay("MessageRum1", 1.0);
			//NewGameTip("Szállítsd el a rumot Le Francois-hoz. Hajózz tovább a sziget körül.");
			pchar.questTemp.Rum.Tip2.Reload = "l4";
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
			
			Weather.Wind.Angle = PId2;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
			pchar.quest.MessageRum2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.MessageRum2.win_condition.l1.location = pchar.location;
			pchar.quest.MessageRum2.function = "MessageRum2";
		break;
		
		case "Rum_Carrier":
			dialog.text = "Már vártuk önt, monsieur. Hogy mentek a dolgok? Megvannak a ládák?";
			link.l1 = "Minden látványosan ment. A rumos ládák a kilövésnél vannak.";
			link.l1.go = "Rum_Carrier_1";
		break;
		
		case "Rum_Carrier_1":
			dialog.text = "Megvannak a ládák? Innentôl kezdve gondoskodunk róla. Menjetek el St. Pierre-be a kocsmába a fizetésért. Legyetek figyelmesek és óvatosak az éjszakai dzsungelben.";
			link.l1 = "Minden jót, uraim.";
			link.l1.go = "Rum_Carrier_2";
		break;
		
		case "Rum_Carrier_2":
			DialogExit();
			for (i=1; i<=3; i++)
			{
				
				sld = characterFromId("Rum_Carrier2_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			}
			pchar.questTemp.Sharlie.Rum = "regard";
			i = FindLocation("Fortfrance_town");
			setCharacterShipLocation(pchar, GetCityFrom_Sea(locations[i].fastreload));
		    setWDMPointXZ(GetCityFrom_Sea(locations[i].fastreload));
			SetCurrentTime(23, 0);
			Sharlie_removeLocks("");
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("lefransua_town", "reload", "gate_back");
			QuestPointerToLoc("lefransua_exittown", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) QuestPointerToLocTime("fortfrance_town", "reload", "reload9_back", 23.0, 24.0);
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		//доставить девочку из борделя
		case "GigoloMan":
			DelLandQuestMark(npchar);
			dialog.text = "Jó napot, uram! Nem úgy néznek ki, mint a rongyos gazemberek, akik általában a mi telepünkön lógnak. Az öltözékükbôl ítélve, hosszú utat tettek meg... Európából érkezett, ugye?";
			link.l1 = "Pontosan, uram. "+GetFullName(pchar)+", szolgálatára. Mire van szüksége?";
			link.l1.go = "GigoloMan_1";
		break;
		
		case "GigoloMan_1":
			dialog.text = "Engedje meg, hogy bemutatkozzam - "+GetFullName(npchar)+". Néhány éve érkeztem erre a borzalmas helyre Franciaországból. De ez sem itt, sem ott nem számít. Egy nagyon kényes ügyem van az Ön számára\nKérem, értse meg, hogy ha nem lennék biztos abban, hogy Ön úriember, soha nem kérnék Öntôl ilyen szívességet.";
			link.l1 = "Kérem, mondja el a kérését, uram. Ha a lehetôségeimen belül van, akkor természetesen megpróbálok segíteni.";
			link.l1.go = "GigoloMan_2";
		break;
		
		case "GigoloMan_2":
			dialog.text = "Ezt örömmel hallom, Monsieur de Maure. Nos, hogy is mondjam finoman... Van egy bordélyház ebben a városban. Nemrég megjelent ott egy új lány; fiatal, sápadt, szôke, elképesztôen szép! Nos, hetek óta figyelem ôt, és... nagyon erôs a vágyam, hogy egy kis idôt töltsek vele négyszemközt\nDe a birtokom és a státuszom miatt... kényelmetlen egy ilyen helyet meglátogatni. Képzelje el a pletykákat!\nEzért fordulok Önhöz. Egyszerûen fogalmazva, ön újonnan érkezett a szigetünkre, az emberek nem ismerik önt, és nem érdekli ôket, hogy mit csinál... még. Nagy szívességet tehetne nekem, monsieur.";
			link.l1 = "Azt hiszem, értem, mire akar kilyukadni.";
			link.l1.go = "GigoloMan_3";
		break;
		
		case "GigoloMan_3":
			dialog.text = "Nagyra értékelem a diszkrécióját, uram. Nem mehetek a lányhoz, így a lánynak kell hozzám jönnie. A házamban. Arra kérem, hogy menjen el a bordélyházba, és egyezzen meg a madame-mal, hogy megengedje, hogy egy 'házhoz' a szôke lányt egy éjszakára\nAurora nem fogja visszautasítani, ô köztudottan ilyen kézbesítési szolgáltatásokat nyújt, bár mindig egy kicsit többe kerül. Ezután el kell hoznia a lányt a házamhoz. Fizetségként hatezer pezót adok neked. Aurora általában háromezret vagy háromötszázat vesz el egy éjszakáért a lánnyal a házban. A többletet megtarthatod a fáradozásaidért járó kártérítésként.";
			link.l1 = "Nem hangzik túl bonyolultnak. Meg tudom csinálni.";
			link.l1.go = "GigoloMan_4";
			link.l2 = "Monsieur, én is ugyanolyan komolyan veszem az úriember hírnevemet, mint ön. Kérem, bocsásson meg, de nem tudom teljesíteni a kérését. Vissza kell utasítanom. Talán el kellene mennem a kocsmába, és megnézni, hogy a fogadósnak van-e valami munkája számomra.";
			link.l2.go = "GigoloMan_exit";
		break;
		
		case "GigoloMan_exit":
			DialogExit();
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload9", false);// бордель
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", false);// таверна
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
		break;
		
		case "GigoloMan_4":
			dialog.text = "Átkozottul örülök, hogy ezt hallom. Figyelj, a lány neve Lucille. Arra kérem, hogy sötétedéskor, de legkorábban este tizenegykor szállítsa el hozzám, hogy elkerülje a bámészkodók nem kívánt figyelmét. Kopogjon az ajtón, és én kinyitom.\nA házam a kormányzó rezidenciájától balra, attól elfordulva található - egy kétszintes, vörös tetejû kúria. Könnyen megtalálod, és van egy bolt is a közelben. Tulajdonképpen most éppen a házam felé tartok; nyugodtan kövessen, hogy lássa, hogy néz ki, és hogy pontosan hol van, így nem fog eltévedni éjszaka.\n Ami a tárgyalt ügyet illeti - tessék, vegyen hatezer pezót. A megbeszélt idôpontban várom!";
			link.l1 = "Megegyeztünk. A szôke Lucille ma este a küszöbön fog állni.";
			link.l1.go = "GigoloMan_5";
		break;
		
		case "GigoloMan_5":
			DialogExit();
			AddMoneyToCharacter(pchar, 6000);
			AddQuestRecord("SharlieC", "1");
			AddQuestUserData("SharlieC", "sName", GetFullName(npchar));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("Fortfrance_town", "houseSp1", true);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie.Gigolo = "start";
			pchar.questTemp.Sharlie.Gigolo.Rand1 = rand(1);
			pchar.questTemp.Sharlie.Gigolo.Rand2 = rand(1);
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", false);// бордель open
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", false);// бордель
			AddLandQuestMark(characterFromId("Fortfrance_hostess"), "questmarkmain");
			QuestPointerToLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerToLoc("fortfrance_brothel", "reload", "reload3");
			chrDisableReloadToLocation = false;
		break;
		
		case "GigoloGirl":
			if (npchar.quest.meeting == "0")
			{
				DelLandQuestMark(npchar);
				QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
				dialog.text = "Jó napot, uram. Miért, maga az az ember, aki felbérelt ma estére? Azt kell mondanom, szerencsés lány vagyok, hogy egy ilyen jóképû és ápolt úriembert szereztem, nem úgy, mint a dokkokból érkezô, kátránytól és izzadságtól bûzlô vadállatok...";
				link.l1 = "Elnézést kérek, de nem ma este, Lucille. Jó barátom nevében vagyok itt, aki számos, igen bonyolult okból kifolyólag nem tudja elhagyni a házát, ezért elviszem hozzá. Ne bosszankodj, ô egy kedves ember, és nagyon kedvel téged. Azt hiszem, a végén boldog leszel.";
				link.l1.go = "GigoloGirl_1";
				// belamour legendary edition -->
				link.l2 = "Uhm... Teljesen igazad van, kedvesem. Mehetünk?";
				link.l2.go = "GigoloGirl_1a";
				// <-- legendary edition
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Monsieur, remélem, megérti, hogy nem sétálgathatok önnel éjszaka. Gyorsan el kell vinnie a barátnôje házához, különben egyenesen visszamegyek a Madame-hoz, és ön elpazarolja a pénzét.";
				link.l1 = "Rendben, értem. Kövessenek!";
				link.l1.go = "GigoloGirl_2";
			}
		break;
		// belamour legendary edition -->
		case "GigoloGirl_1a":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; //закрыть локацию
			DoQuestReloadToLocation(pchar.location+"_room", "goto", "goto2", "GigoloGirl_Sex");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_room", "goto", "goto1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		case "GigoloGirl_1":
			AddCharacterExpToSkill(pchar, "Fortune", 40);
		// <-- legendary edition
			dialog.text = "Kár, hogy... Rögtön megkedveltem magát, uram. Szívesen töltöttem volna önnel az éjszakát... talán legközelebb. Mehetünk?";
			link.l1 = "Igen, menjünk. Kövessenek!";
			link.l1.go = "GigoloGirl_2";
		break;
		
		case "GigoloGirl_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_Gigolo.win_condition.l1 = "locator";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_Gigolo.win_condition.l1.locator = "houseSp1";
			pchar.quest.Sharlie_Gigolo.function = "Sharlie_GiveGigoloGirl";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_Gigolo1.function = "Sharlie_GigoloGirlOver";
			QuestPointerToLoc("fortfrance_town", "reload", "houseSp1");
		break;
		
		case "GigoloGirl_3":
			dialog.text = "Milyen nagyszerû ház. Ez az a hely?";
			link.l1 = "Igen, ez az. Jöjjön be. Ne félj, a barátom jó ember.";
			link.l1.go = "GigoloGirl_4";
		break;
		
		case "GigoloGirl_4":
			dialog.text = "Alábecsül engem, nem félek, uram. Tudom, hogy kell bánni magammal. Nos, talán valamikor késôbb fizethetne a Madame-nak egy éjszakát velem? Ígérem, hogy ez lesz élete legjobb éjszakája!";
			link.l1 = "Bármi lehetséges, Lucille. Talán még találkozunk. Viszontlátásra!";
			link.l1.go = "GigoloGirl_5";
		break;
		
		case "GigoloGirl_5":
			pchar.quest.Sharlie_Gigolo1.over = "yes";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "GigoloGirl_Remove", 5.0);
			QuestPointerDelLoc("fortfrance_town", "reload", "houseSp1");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Rum"))
			{
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
				pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
				pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
			}
		break;
		
		//пираты с пленным испанцем
		case "CaptivePirate":
			pchar.quest.Captive_CreatePiratesOver.over = "yes";//снять таймер
			pchar.quest.Captive_CreatePiratesOver2.over = "yes";//снять таймер
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			dialog.text = "Mi ez? Ki vagy te? Mit akarsz itt? Gyerünk, tûnjetek innen a pokolba!";
			link.l1 = "Nem túl udvarias, uram.";
			link.l1.go = "CaptivePirate_1";
		break;
		
		case "CaptivePirate_1":
			dialog.text = "Figyelj ide fiú, engem nem udvariasságra neveltek, ahogy írni-olvasni sem tanultam meg, de a koponyádat egy baltával felhasítani olyan könnyû nekem, mint egy hanyatt esett kurvát. És esküszöm a halottlámpáimra, hogy ha nem sétálsz ki innen ebben a percben, akkor kiviszlek. Megértetted?";
			link.l1 = "Nem, te figyelj rám, te gazember. A cselszövésed a nyilvánosság elé került. Élve kell az az ember, úgyhogy dobja el a fegyvert és fusson. Egy csapat francia katona van mögöttem a dzsungelben. Ha elég gyorsan futnak, akkor talán sikerül megmenteniük a szánalmas életüket.";
			link.l1.go = "CaptivePirate_3";
			link.l2 = "Jól van, jól van, nyugodjatok meg. Elmegyek.";
			link.l2.go = "CaptivePirate_2";
		break;
		
		case "CaptivePirate_2":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
				sld.lifeday = 0;
			}
			sld = characterFromId("CaptiveSpain");
			LAi_SetImmortal(sld, true);
			sld.lifeday = 0;
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";//снять прерывание
			AddQuestRecord("SharlieD", "5");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "CaptivePirate_3":
			dialog.text = "Mi van? Blöffölsz, haver! Vigyétek le fiúk, fegyverbe!";
			link.l1 = "A saját fejedre, en garde!";
			link.l1.go = "CaptivePirate_4";
		break;
		
		case "CaptivePirate_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			int n = makeint(MOD_SKILL_ENEMY_RATE/2);
			if (n <= 1) n = 2;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("CaptivePirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Captive_PiratesDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
			sld = characterFromId("CaptiveSpain");
			LAi_SetCitizenType(sld);
			DoQuestFunctionDelay("Ngt_CaptiveEng", 0.5);
		break;
		
		//пленный испанец
		case "CaptiveSpain":
			dialog.text = "Gracias a Dios! Á, maga Francés? Mierda, stílusosan védted ki azokat a rablókat. De ne higgyétek, hogy csak úgy megadom magam, megmutatom, hogyan harcol egy spanyol! Santiago!";
			link.l1 = "Ne várjatok, kérlek!";
			link.l1.go = "CaptiveSpain_1";
		break;
		
		case "CaptiveSpain_1":
			dialog.text = "Inkább meghalok, minthogy a franciák elkapjanak. Elvettem az egyik holttesttôl egy bicskát, amíg ti harcoltatok... most pedig táncoltatlak egy spanyol quadrille-re!";
			link.l1 = "Ti spanyolok olyan makacsok vagytok, mint az öszvérek!";
			link.l1.go = "CaptiveSpain_2";
		break;
		
		case "CaptiveSpain_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			NextDiag.currentnode = "CaptiveSpain_3";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "CaptiveSpain_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "CaptiveSpain_3":
			dialog.text = "Maldito... Te nyertél. Feladom, átkozott francia. Kegyelmednek vagyok kiszolgáltatva.";
			link.l1 = "Tedd fel a pengédet és hagyj beszélni, te makacs kasztíliai! Nem akarom, hogy meghalj, és nem küldelek börtönbe sem!";
			link.l1.go = "CaptiveSpain_4";
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
		break;
		
		case "CaptiveSpain_4":
			dialog.text = "Akkor mit csinálsz? Miért ölted meg a kalózokat? És hol vannak a katonáid?";
			link.l1 = "Nincsenek katonák. Megpróbáltam becsapni a gazembereket, de ahogy körülöttünk láthatjátok, nem sikerült. Egyedül vagyok itt, öreg barátod kérésének megfelelôen. A neve "+pchar.questTemp.Sharlie.Captive.Name+", bankár St. Pierre-ben.";
			link.l1.go = "CaptiveSpain_5";
		break;
		
		case "CaptiveSpain_5":
			dialog.text = ""+pchar.questTemp.Sharlie.Captive.Name+"? Nem ismerek senkit ezen a néven...";
			link.l1 = "Semmit sem tudok rólad vagy a fogságodról. Tôle tudtam meg, hogy átvitték egy angol hajóra. Az a feladatom, hogy átadjam magát neki, és megesküdtem, hogy ezt teljesítem! Most pedig gyere velem, ha élni akarsz.";
			link.l1.go = "CaptiveSpain_6";
		break;
		
		case "CaptiveSpain_6":
			dialog.text = "Úgysincs más választásom... Ez a bankárod nem lehet rosszabb, mint az angolok és a szörnyû fôztjük...";
			link.l1 = "Végre bölcs döntést hozol. Egyelôre elég a beszédbôl, St. Pierre-be megyünk. Maradj mellettem és ne tévedj el. Ha elfutsz, elkaplak, és megint életveszélyesen megverlek.";
			link.l1.go = "CaptiveSpain_7";
		break;
		
		case "CaptiveSpain_7":
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.Notsearchbody"); // 170712
			DialogExit();
			AddQuestRecord("SharlieD", "6");
			LAi_group_Register("TempFriends");
			LAi_group_SetRelation("TempFriends", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "TempFriends");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			pchar.quest.Sharlie_captive3.win_condition.l1 = "locator";
			pchar.quest.Sharlie_captive3.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator_group = "reload";
			pchar.quest.Sharlie_captive3.win_condition.l1.locator = "reload8_back";
			pchar.quest.Sharlie_captive3.win_condition.l2 = "Night";
			pchar.quest.Sharlie_captive3.win_condition.l3 = "Alarm";
			pchar.quest.Sharlie_captive3.win_condition.l3.value = 0;
			pchar.quest.Sharlie_captive3.win_condition.l3.operation = "=";
			pchar.quest.Sharlie_captive3.function = "CaptiveSpain_reload";//вход ночью
			pchar.questTemp.Sharlie = "bankskipercaptive";
			SetFunctionLocationCondition("CaptiveSpain_removeGuard", "fortfrance_town", 0);
			SetFunctionLocationCondition("CaptiveSpain_saveTip", "fortfrance_exittown", 0);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			// Rebbebion, новые марки до места назначения. belamour поправил - были не в ту сторону
			QuestPointerToLoc("shore39", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload8_back");
			AddLandQuestMark(characterFromId("FortFrance_Usurer"), "questmarkmain");
		break;
		
		//горожанин с пропавшей дочерью
		case "Prosper":
			DelLandQuestMark(npchar);
			pchar.quest.Sharlie_RescueDaughter.over = "yes"; //снять прерывание
			dialog.text = "Mire van szüksége, monsieur? Nincs idôm beszélgetni, úgyhogy fogalmazzon röviden.";
			link.l1 = "Ön Prosper Trubal, ugye?";
			link.l1.go = "Prosper_1";
		break;
		
		case "Prosper_1":
			dialog.text = "Igen, én vagyok. De ön elônyben van velem szemben. Kérem, mondja el, hogy ki maga és mi a fenét akar.";
			link.l1 = "A nevem "+GetFullName(pchar)+". Engem a "+GetFullName(characterFromId("Fortfrance_portman"))+", a kikötômester küldött hozzád. Azt mondta, hogy sürgôs segítségre van szüksége...";
			link.l1.go = "Prosper_2";
		break;
		
		case "Prosper_2":
			dialog.text = "Istenem, igen! Az a gazember parancsnok meg sem hallotta a panaszomat! Vagy túl lusta, vagy gyáva ahhoz, hogy segítsen. Tényleg azért jöttél ide, hogy segíts nekem? Ha így van, nem hagylak jutalom nélkül!";
			link.l1 = "Igen, Prosper. Mondja el, mi történt, és mit kell tennem, hogy segítsek. Hallottam, hogy a lánya eltûnt...";
			link.l1.go = "Prosper_3";
		break;
		
		case "Prosper_3":
			dialog.text = "Igen, az én drága lányom, Celene két napja eltûnt. Elment sétálni az erôdbe, nem messze innen. De nem tért vissza, ezért magam mentem el az erôdbe, és a katonák azt mondták, hogy soha nem járt ott!\nDe aztán, amikor visszatértem, két vad indián megtámadott! Botokkal ugrottak rám, és megpróbáltak megütni\nDe én nem vagyok kiscica, ezért az egyiket arcon ütöttem, ezzel elég idôt nyertem, hogy elôvegyem a pisztolyomat és lôjek. Elhibáztam, de elijesztettem ôket. Sikerült elérnem a város kapuját, és szóltam az ôröknek a támadásról. A dzsungelbe rohantak, de a vadak már régen elmentek\nbiztos vagyok benne, hogy ôk a felelôsek Celene eltûnéséért. Ráadásul az elmúlt héten még két ember tûnt el - Cesar Blanchet és Gilbert Courcy! Az egyik az öböl felé tartott, a másik pedig Le Francois felé. Soha nem tértek vissza.";
			link.l1 = "Tehát az indiánok a város kapujában támadtak a városlakókra? Ez hihetetlenül merész...";
			link.l1.go = "Prosper_4";
		break;
		
		case "Prosper_4":
			dialog.text = "Közben én magam is kimentem a dzsungelbe, hogy megkeressem ôt, és találtam egy barlangot a várostól északra. Megtaláltam, hogy a rohadékok ott gubbasztanak. Több indiánt láttam a bejáratnál, de néhányan közülük biztosan bent is vannak\nHallottam egy lány sikolyát... Az én Celene-em volt az, ebben biztos vagyok, az ô hangja volt! Minden önuralmamra szükségem volt, hogy ne fussak be azonnal - az esélyek nem nekem kedveztek, és lemészároltak volna. Holtan nem vagyok hasznára.";
			link.l1 = "De mi a fenéért támadnak és ejtenek foglyul városlakókat?";
			link.l1.go = "Prosper_5";
		break;
		
		case "Prosper_5":
			dialog.text = "Nem tudom... Talán azért, hogy eladják ôket kalózoknak vagy rabszolgatartóknak? Talán csak élve megeszik ôket, elvégre ezek vademberek.";
			link.l1 = "Édes Istenem a mennyekben, ezek kannibálok? Azt hittem, hogy ezek csak mesék, amivel a gyerekeket ijesztgetik Európában...";
			link.l1.go = "Prosper_6";
		break;
		
		case "Prosper_6":
			dialog.text = "Történetek? Nos, néhány hozzád hasonló ember ugyanezt gondolta, amíg a karibiak meg nem fôzték ôket tûzön és meg nem ették... Ezért azonnal a parancsnokhoz fordultam, és kértem egy büntetô rajtaütést, hogy megmentsem a Celene-emet. Elutasította! Azt mondta, hogy ha lányok tûnnek el, akkor valószínûleg egy fiúval szöktek el, nem indiánokkal. Azt javasolta, hogy keressem meg a lányt a helyi szénapadláson\nAm ami pedig a másik két eltûntet illeti... azt mondta, hogy egyikük csempészet gyanújába keveredett, a másik pedig valószínûleg halálra issza magát Le Francoisban' tavernában. Összefoglalva, nem értem el semmit, és úgy döntöttem, hogy magam cselekszem.";
			link.l1 = "Mit szándékozik tenni?";
			link.l1.go = "Prosper_7";
		break;
		
		case "Prosper_7":
			dialog.text = "Odamegyek, és megölöm az összes vörös szemétládát. Csak remélem, hogy Celene még él. Amint látod, vettem egy muskétát - és tudom, hogyan kell vele lôni. Sok pénzt fizettem érte, de nem érdekel\nA küldetésem sokkal könnyebb lesz, ha elkísérsz. Együtt különösebb gond nélkül végezhetünk a vadakkal, ha vigyázol a hátamra, amíg újratöltök. Velem tartasz, hogy megmentsük a lányomat?";
			link.l1 = "Természetesen! Ez becsületbeli ügy! Nem hagyhatom, hogy egy lány meghaljon egy vadember kése által.";
			link.l1.go = "Prosper_8";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1.go = "Prosper_noweapon";
			}
			link.l2 = "Hm. Tudod, azt hiszem, a parancsnok szavainak van értelme. Talán mégis az ô tanácsát kellene követnünk elôször?";
			link.l2.go = "Prosper_exit";
		break;
		
		case "Prosper_noweapon":
			dialog.text = "Monsieur, hol van a pengéje?";
			link.l1 = "Úgy tûnik, elkevertem.";
			link.l1.go = "Prosper_noweapon_1";
		break;
		
		case "Prosper_noweapon_1":
			dialog.text = "Ez egyszerûen nem fog menni. Estig várok önre, azt tanácsolom, hogy térdeljen a kormányzó lábai elôtt, és könyörögjön a segítségéért.";
			link.l1 = "A lábai elôtt térdeljen, mi? Nos, ahogy óhajtja...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prosper_getweapon";
			SetFunctionTimerConditionParam("RescueDaughter_Over", 0, 0, 0, 22, false);
		break;
		
		case "Prosper_getweapon":
			dialog.text = "Nos, uram? Szereztél magadnak fegyvert?";
			if (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) == "") {
				link.l1 = "Még nem, kérem várjon még egy kicsit...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Prosper_getweapon";
			} else {
				link.l1 = "Megvan. Készen állok, hogy segítsek!";
				link.l1.go = "Prosper_8";
				DeleteQuestCondition("RescueDaughter_Over");
			}
		break;

		case "Prosper_exit":
			dialog.text = "Istenem, te menekülsz? Nem! Tûnjetek innen a pokolba! Gyáva!";
			link.l1 = "Hé, hé, nyugi, te együgyû! Jobb, ha kimegyek, és megnézem, hogy Saint-Pierre utcáin van-e olyan nemes, akinek segítségre van szüksége.";
			link.l1.go = "Prosper_exit_1";
			pchar.questTemp.Sharlie.GigoloMan.SamPodbezhit = true;
		break;
		
		case "Prosper_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			//AddTimeToCurrent(2,0);
			SetCurrentTime(17,30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate_back", "none", "", "", "", 10.0);
			CloseQuestHeader("SharlieF");
			chrDisableReloadToLocation = true;
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Prosper_8":
			dialog.text = "Örülök, hogy legalább egy bátor ember van ebben a városban. Tessék, fogd ezt a három fiolát. Ezek egészségmegôrzô gyógynövények, a gyógynövénykereskedônktôl vettem ôket. Jelentôs segítség lehet számotokra a csatában.";
			link.l1 = "És te?";
			link.l1.go = "Prosper_9";
		break;
		
		case "Prosper_9":
			TakeNItems(pchar, "potion1", 3);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ne aggódj, van még több is. Készen állsz?";
			link.l1 = "Igen, ne vesztegessük az idôt. Gyerünk!";
			link.l1.go = "Prosper_10";
		break;
		
		case "Prosper_10":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "fortfrance_exittown", "reload", "reload3", "OpenTheDoors", 10.0);
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1 = "location";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition.l1.location = "FortFrance_ExitTown";
			PChar.quest.RescueDaughter_ProsperGateOutReload.win_condition = "RescueDaughter_ProsperGateOutReload";
			AddQuestRecord("SharlieF", "3");
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter1.win_condition.l1.location = "Martinique_jungle_04";
			pchar.quest.Sharlie_RescueDaughter1.function = "RescueDaughter_NearCave";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "Timer";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.hour  = sti(GetTime()+2);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CaveOver";
			NextDiag.CurrentNode = "Prosper_11";
			pchar.questTemp.Sharlie.RescueDaughter = "true";
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", true);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", true);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", true);//джунгли
		break;
		
		case "Prosper_11":
			dialog.text = "Már majdnem a helyünkön vagyunk, "+pchar.name+". Ezen a kanyaron túl van a barlang bejárata. Gyertek közelebb, és elmondom a tervünket.";
			link.l1 = "Csupa fül vagyok, Prosper.";
			link.l1.go = "Prosper_12";
		break;
		
		case "Prosper_12":
			dialog.text = "Stabilan kell céloznom ezzel a nehéz lôfegyverrel, de ha idôt nyerhetsz nekem, nem fogok hibázni. Ha közelharcba kell bocsátkoznom, felejtsd el a tûztámogatást, csak a csövemmel, mint bunkósbottal tudom majd elhárítani az embereket. Ez a harc a vívótudásodon fog múlni.";
			link.l1 = "Mit akarsz ezzel mondani?";
			link.l1.go = "Prosper_13";
		break;
		
		case "Prosper_13":
			dialog.text = "Csak arra van szükséged, hogy eltereld a figyelmüket, hogy mindet lelôhessem. Nem tudok mozogni és lôni, ezért egy helyhez fogok ragaszkodni. A barlang bejáratához közel van három fattyú. Rohanj rájuk, amilyen gyorsan csak tudsz, a pengéddel a kezedben\nÜsd meg az egyiket, és vedd rá ôket, hogy üldözzenek téged. Csald el ôket a közelembôl. Ha mindhárman rád fognak koncentrálni, akkor madárként lövöm le ôket, miközben hárítasz és kitérsz. De ha azok a vadak lecsapnak rám, végünk van. Készen állsz?";
			link.l1 = "Nem ez lesz az elsô alkalom, hogy kardot fogok, ezek a vademberek nem jelentenek veszélyt.";
			link.l1.go = "Prosper_14";
			// belamour legendary edition -->
			link.l2 = "A vademberek nem jelentenek veszélyt. Ne aggódj miattam. Ez olyan, mint a Le Mans-i vadászat! Csak nehogy véletlenül hátba lôj!";
			link.l2.go = "Prosper_14a";
		break;
		
		case "Prosper_14a":
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			dialog.text = "Menj elôre, én mögötted vagyok. Ne feledd: nem engedheted ôket közel hozzám!";
			link.l1 = "Emlékszem, menjünk. Elôre!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_14":
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			// <-- legendary edition
			dialog.text = "Akkor készüljetek fel az akcióra. Menj elôre, én mögötted leszek. Ne feledjétek: nem engedhetitek ôket közelebb hozzám!";
			link.l1 = "Emlékszem. Mindent megteszek, amit tudok. Gyerünk!";
			link.l1.go = "Prosper_15";
		break;
		
		case "Prosper_15":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_jungle_04", "reload2_back", false);
			NextDiag.CurrentNode = "Prosper_16";
			NewGameTip("Kihívást jelentô küzdelem vár ránk. (F6) a gyors mentéshez.");
		break;
		
		case "Prosper_16":
			dialog.text = "Szép munka, "+pchar.name+"! Ezek a pogány vademberek nem gyilkolnak tovább. Most pedig jöjjön a fô esemény - a barlang. Azt hiszem, hogy hárman vagy négyen vannak odabent, de nem tudhatom biztosan. Most figyeljetek\nTíz évvel ezelôtt már jártam ott. Van egy szûk alagút a barlang belsejében. Egy kis barlangba vezet, amelyet egy fal választ el, amelynek a közepén egy lyuk van. Ismételjük meg a korábbi tervünket. Én mozdulatlanul állok a bejárat közelében, te pedig berohansz\nProvokáld ôket, ne próbálj meg egyszerre harcolni mindegyikkel, csak akadályozd meg, hogy megtámadjanak. Vegyétek fel a pozíciót az említett alagútnál, szûk, így csak egy vagy kettô tud majd egyszerre harcolni ellenetek\nA vállatok fölött lövök rájuk. Készen állsz?";
			link.l1 = "Gyerünk! Végezzünk a vademberek fészkével!";
			link.l1.go = "Prosper_17";
		break;
		
		case "Prosper_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LocatorReloadEnterDisable("Martinique_CaveEntrance", "reload1_back", false);
			AddComplexSelfExpToScill(20, 20, 20, 20);
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter2.win_condition.l1.location = "Martinique_Grot";
			pchar.quest.Sharlie_RescueDaughter2.function = "RescueDaughter_CreateIndiansGrot";
			NextDiag.CurrentNode = "Prosper_18";
		break;
		
		case "Prosper_18":
			dialog.text = "A lányom él! Hála Istennek! Idôben ideértünk, "+pchar.name+". Köszönettel tartozom önnek, uram. Ön egy bátor ember és egy jó harcos!";
			link.l1 = "Örülök, hogy happy end van, Prosper. Nem semmi véres munka volt kiirtani azokat az indiánokat.";
			link.l1.go = "Prosper_19";
		break;
		
		case "Prosper_19":
			DialogExit();
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
		break;
		
		case "Prosper_20":
			dialog.text = "Még egyszer mélyen köszönöm, "+pchar.name+"! Most pedig induljunk vissza a városba. A lányom élete felbecsülhetetlen, pénzzel felbecsülhetetlen, de szeretném megköszönni azzal, hogy odaadom a megtakarításaim maradékát. Amint Saint-Pierre-be érünk, szívesen odaadom önnek. És eszébe se jusson visszautasítani!";
			link.l1 = "Nem utasítom vissza, Prosper. Bár nem a pénz volt a célom, hogy segítsek neked.";
			link.l1.go = "Prosper_21";
		break;
		
		case "Prosper_21":
			dialog.text = "Igazi keresztény lovag vagy, "+pchar.name+"! Most már ne avatkozzunk bele. Menjünk haza, de gyorsan!";
			link.l1 = "...";
			link.l1.go = "Prosper_22";
		break;
		
		case "Prosper_22":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Tutorial_Amulet.over = "yes";
			SetLaunchFrameFormParam("Vissza a városba...", "Reload_To_Location", 0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "gate_back", "");
			LaunchFrameForm();
		break;
		
		case "Prosper_23":
			SelectPresentAmulet();
			dialog.text = "Itt vagyunk, Charles. Még egyszer megköszönöm a segítségedet, és szavaimhoz kötöm ezt a szerény összeget, pezókat és aranydublont. Javaslom, hogy ne pazarold a dublónokat, és tartsd meg ôket különleges alkalmakra. Tudom, hogy ez nem sok pénz egy ilyen szolgálatért, amit nekem nyújtottál, de szívembôl adom. Fogadd el ezt az amulettet is, "+pchar.questTemp.SMQ.Text+"";
			link.l1 = "Köszönöm! Isten veled Prosper, boldogságot kívánok neked és kedves lányodnak!";
			link.l1.go = "Prosper_24";
		break;
		
		case "Prosper_24":
			LocatorReloadEnterDisable("Fortfrance_exittown", "reload2_back", false);//форт
			LocatorReloadEnterDisable("Martinique_Jungle_01", "reload1_back", false);//джунгли
			LocatorReloadEnterDisable("Martinique_Jungle_04", "reload1_back", false);//джунгли
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(pchar, "gold_dublon", 15);
			TakeNItems(pchar, pchar.questTemp.SMQ.Amulet, 1);
			Log_Info("Kaptál 15 dublont");
			Log_Info("Kaptál egy amulettet.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ah, egy olyan férj, mint te, jót tenne neki. Csak azt csinálja, hogy egy csomó sovány lábú, áll nélküli fickó kergeti a városban. Micsoda kár, hogy mindegyikük elment és eltûnt valahová... jó, hogy megszabadult tôlük. Sok szerencsét, Charles!";
			link.l1 = "...";
			link.l1.go = "Prosper_25";
		break;
		
		case "Prosper_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			sld = characterFromId("RD_Selina");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload10_back", "none", "", "", "", 10.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 120);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 70);//скрытность
			AddQuestRecord("SharlieF", "7");
			CloseQuestHeader("SharlieF");
			DeleteAttribute(pchar, "questTemp.SMQ");
			pchar.questTemp.Prosper_fmql = "true"; // Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			pchar.quest.Sharlie_JungleNative.win_condition.l1 = "location";
			pchar.quest.Sharlie_JungleNative.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Sharlie_JungleNative.function = "SharlieJungleNative";
			SetCurrentTime(17,30);
			//AddTimeToCurrent(2,0);
			//QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Selina":
			dialog.text = "Istenem, segíts! (sírás) Te... te el sem tudod képzelni, milyen borzalom történik itt! Ezek... ezek az indiánok azért rángattak ide minket, hogy megöljenek és felfaljanak! Cesar Blanchet itt volt... A vademberek elvitték... Valami szörnyû ördögi rituálét végeztek, aztán... Uram, még csak beszélni sem tudok róla! Nekem kellett volna a következônek lennem! Engem akartak lemészárolni... holnap!";
			link.l1 = "Nyugodj meg, Celine. Már vége van. Azok a szemetek megkapták, amit megérdemeltek, és nem fognak többé senkit sem bántani.";
			link.l1.go = "Selina_1";
		break;
		
		case "Selina_1":
			dialog.text = "Gilbert Coursie is itt van. Ott... ô... még mindig nem épült fel. Beszélj vele... Akkor siessünk és tûnjünk el innen!";
			link.l1 = "Jól van, jól van. Minden rendben, kislány. Elég a sírásból. Minden rendben van. Csodálatos apád van. Nem hagyná, hogy bárki bántson téged... Menj ki, én segítek... Gilbert, és késôbb találkozunk.";
			link.l1.go = "Selina_2";
		break;
		
		case "Selina_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			sld = characterFromId("RD_Prosper");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_1", "", 5.0);
			AddQuestRecord("SharlieF", "5");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
		break;
		
		case "Selina_3":
			dialog.text = "Isten és a Szûzanya meghallgatta imáimat! Azért jöttél, hogy megments minket?";
			link.l1 = "Te... A neved Celine, ugye?";
			link.l1.go = "Selina_4";
		break;
		
		case "Selina_4":
			dialog.text = "Igen... (sírás) Te... el sem tudod képzelni, milyen borzalom történik itt! Ezek... ezek az indiánok azért rángattak ide minket, hogy megöljenek és felfaljanak! Cesar Blanchet itt volt... Elvitték... Valami ördögi rituálét végeztek, aztán... Uram, még csak beszélni sem tudok róla! Én leszek a következô! Engem akartak lemészárolni... holnap!";
			link.l1 = "Nyugodj meg, kislány... Sajnálom, de rossz híreket hoztam neked. Az apáddal jöttem ide. Megölték azok a vörösbôrû vademberek, miközben harcoltunk, hogy eljussunk hozzád. Az életét adta, hogy megmentsen téged.";
			link.l1.go = "Selina_5";
		break;
		
		case "Selina_5":
			dialog.text = "Micsoda?! Az apám... Ó, Istenem! I... I...(sobbing)";
			link.l1 = "Részvétem, Celine. Van itt még valaki veled, igazam van?";
			link.l1.go = "Selina_6";
		break;
		
		case "Selina_6":
			dialog.text = "(könnyeken keresztül) Igen... Gilbert Coursie. Ott van bent... Még mindig nem épült fel. Menj, beszélj vele... Akkor siessünk ki innen!";
			link.l1 = "Igen, persze. Nem vesztegethetünk egy percet sem arra, hogy itt ácsorogjunk.";
			link.l1.go = "Selina_7";
		break;
		
		case "Selina_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_2", "", 5.0);
			AddQuestRecord("SharlieF", "6");
			sld = characterFromId("RD_Jilberte");
			LAi_SetStayType(sld);
			AddComplexSelfExpToScill(20, 20, 20, 20);
		break;
		
		case "Selina_8":
			dialog.text = "Az apám... Szegény, drága apám! Ah, uram, még meg sem köszöntem, hogy megmentettél...";
			link.l1 = "Selina, örülök, hogy te és Gilbert élve kijutottatok a barlangból. Apád hôsi halála nem volt hiábavaló.";
			link.l1.go = "Selina_9";
		break;
		
		case "Selina_9":
			dialog.text = "(sírva) Kérem, uram, vigyen el minket a városba. El kell küldenünk a katonákat, hogy jöjjenek apám holttestéért, hogy megfelelô keresztény temetést kapjon...";
			link.l1 = "Természetesen, Celine. Gyertek utánam!";
			link.l1.go = "Selina_10";
		break;
		
		case "Selina_10":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Selina_11":
			dialog.text = "Köszönöm, uram, hogy elkísérte szegény apámat... Köszönöm, hogy megmentett a biztos haláltól. I... I... Tessék, fogd ezt a zsák dublont. Otthon találtam apám ládájában. Kérlek, eszedbe se jusson visszautasítani!";
			link.l1 = "Köszönöm, Celine. Örülök, hogy sikerült megmentenünk téged. És ôszinte részvétem az apád elvesztése miatt.";
			link.l1.go = "Selina_12";
		break;
		
		case "Selina_12":
			TakeNItems(pchar, "gold_dublon", 15);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ön egy nemes ember, monsieur. Soha nem fogom elfelejteni önt. Viszontlátásra!";
			link.l1 = "Viszlát, Celine.";
			link.l1.go = "Selina_13";
		break;
		
		case "Selina_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload10_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			AddQuestRecord("SharlieF", "8");
			CloseQuestHeader("SharlieF");
			pchar.questTemp.ZsI_Cannibals = true;	//Sinistra Требуется для квеста "Знакомство с индейцами"
			
			sld = characterFromId("RD_Jilberte");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Jilberte":
			PlaySound("Voice\English\other\robinzons-08.wav");
			dialog.text = "Ó, Uram, tényleg minden mögöttünk van? Nem is tudom elhinni... Megmentettél engem és Celine-t is. Ha te nem lettél volna, ugyanaz a sors, ami a szerencsétlen Cesart érte, holnap ôt is elszólította volna, és ugyanez készülne rám is néhány nap múlva.";
			link.l1 = "Ezek az indiánok tényleg kannibálok?!";
			link.l1.go = "Jilberte_1";
		break;
		
		case "Jilberte_1":
			dialog.text = "Kételkedsz benne? Ha erôs a gyomrod, nézz bele a fôzôtüzük hamujába. Ott megtalálod szegény öreg Cesart. Most már csak néhány megrágott csont...";
			link.l1 = "Áldott szentség... Nem, kihagyom. Csak nemrég érkeztem ide Európából, és el sem tudom képzelni, hogy ilyen aljas, ördögi dolgok még mindig történnek a Földön.";
			link.l1.go = "Jilberte_2";
		break;
		
		case "Jilberte_2":
			dialog.text = "Sok furcsa dolog történik a Karib-tengeren, olyan dolgok, amelyekrôl az Óvilágban már hallottál suttogásokat... Indián orvosságosok, mágia, sámánok és titkos rituálék. Ha tovább maradsz itt, mindenféle ördögi dolognak szemtanúja leszel. De bocsáss meg, még nem köszöntem meg, hogy megmentettél - még mindig sokkos állapotban vagyok\nmegmentetted az életemet, és hálámat nemcsak szavakban, hanem aranyban is ki fogom fejezni. Kísérj el engem és Celine-t a városba. Ott majd megköszönhetem, ahogyan megérdemli, monsieur.";
			link.l1 = "Rendben, uram. Lépjen ki. Elôbb körülnézek itt.";
			link.l1.go = "Jilberte_3";
		break;
		
		case "Jilberte_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "Martinique_CaveEntrance", "officers", "reload1_3", "OpenTheDoors", 10.0);
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1 = "location";
			pchar.quest.Sharlie_RescueDaughter5.win_condition.l1.location = "Martinique_CaveEntrance";
			pchar.quest.Sharlie_RescueDaughter5.function = "RescueDaughter_GoHome";
		break;
		
		case "Jilberte_4":
			dialog.text = "Engedje meg, hogy még egyszer kifejezzem mélységes hálámat, amiért megmentett, monsieur! Ahogy ígértem, szóbeli hálámhoz anyagi hálámat is adom ezüst pezók és aranydublónok formájában.";
			link.l1 = "Örülök, hogy minden a legjobbra fordult, Gilbert.";
			link.l1.go = "Jilberte_5";
		break;
		
		case "Jilberte_5":
			AddMoneyToCharacter(pchar, 3000);
			TakeNItems(pchar, "gold_dublon", 20);
			Log_Info("Kaptál 20 dublont");
			PlaySound("interface\important_item.wav");
			dialog.text = "El sem tudja képzelni, mennyire örülök ennek! Még egyszer köszönöm, és engedje meg, hogy elbúcsúzzam, monsieur.";
			link.l1 = "Sok szerencsét, Gilbert! Egyébként, nem tudja véletlenül, hogy Saint-Pierre-ben van-e még valaki, akinek segítségre van szüksége?";
			link.l1.go = "Jilberte_6a";
		break;
		
		case "Jilberte_6a":
			dialog.text = "Nem tudom, de... Megkérdezheti a polgárokat az utcán, uram. Az egyszerû városlakók, sôt, még a jómódúak sem valószínû, hogy valami érdemlegeset tudnának ajánlani, de a gazdag nemesek... nekik talán van valami munkájuk az ön számára.";
			link.l1 = "Értettem, Gilbert, köszönöm. Viszlát!";
			link.l1.go = "Jilberte_6";
		break;
		
		case "Jilberte_6":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.Sharlie.RescueDaughter");
			
			//Подбегает дворянин с квестом "девочка по вызову"
			sld = GetCharacter(NPC_GenerateCharacter("GigoloMan", "Guide_2", "man", "man", 25, FRANCE, 5, true, "soldier"));
			SetFantomParamFromRank(sld, 25, true);
			sld.Dialog.Filename = "Quest\Sharlie\StartMiniQuests.c";
			sld.dialog.currentnode = "GigoloMan";
			sld.greeting = "noble_male";
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Fortfrance_town", "goto", "goto1");
			sld.talker = 9;
			LAi_SetCitizenType(sld);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Figyeljen ide, én törvénytisztelô polgára vagyok ennek a városnak. Meg kell kérnem, hogy ne járkáljon úgy, mint egy rabló, a pengéjével.", "Uram, kérem, a törvény világosan kimondja, hogy a város falain belül nem szabad kivont fegyverrel járkálni.");
			link.l1 = LinkRandPhrase("Jól van, rendben.", "Rendben.", "Ahogy kívánod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

void SelectPresentAmulet()
{
	switch (pchar.HeroParam.HeroType)
	{        
		case "HeroType_1":
			pchar.questTemp.SMQ.Amulet = "indian_7";
			pchar.questTemp.SMQ.Text = "növeli az állóképességet és ad egy második szelet.";
		break;
		
		case "HeroType_2":
			pchar.questTemp.SMQ.Amulet = "amulet_7";
			pchar.questTemp.SMQ.Text = "növeli az ellenálló képességet a harci sérülésekkel szemben.";
		break;
		
		case "HeroType_3":
			pchar.questTemp.SMQ.Amulet = "indian_4";
			pchar.questTemp.SMQ.Text = "növeli a fegyvereid támadóerejét.";
		break;
		
		case "HeroType_4":
			pchar.questTemp.SMQ.Amulet = "indian_1";
			pchar.questTemp.SMQ.Text = "sokkal halálosabbá teszi a tûzfegyvereket.";
		break;
	}
}
