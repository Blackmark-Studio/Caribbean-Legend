int iLoxlyPseudoGlobal;

// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else Dialog.CurrentNode = "RelationAny_Done";
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "A nevem Albert Loxley és ügyvéd vagyok. Ügyfeleim érdekeit képviselem a tárgyalásokon. A szolgáltatásaim drágák, de megéri, errôl biztosíthatom.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "Bajban vagyok az angol hatóságokkal.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "Bajban vagyok a francia hatóságokkal.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "Bajban vagyok a spanyol hatóságokkal.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "Bajban vagyok a holland hatóságokkal.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "Összevesztem a csempészekkel.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Köszönöm, de szerencsére egyelôre nincs szükségem ügyvédi szolgáltatásokra.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
					break;
				}
				link.l1 = "Köszönöm, de szerencsére egyelôre nincs szükségem ügyvédi szolgáltatásokra.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "Szükségem van a szolgálataira. Egy Helen McArthur nevû fiatal hölgy megbízottja vagyok, ô a híres Nicolas Sharp unokája. Ô az egyetlen törvényes örökös, aki anyja és nagybátyja halála után megmaradt. A nagybátyja végrendelete szerint minden joga megvan Isla Tesoróra. Mennyit kérne azért, hogy segítsen Helennek a sziget jogos úrnôjévé válni?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "Szüksége van a szolgálataimra, uram? Biztosíthatom, hogy elégedett lesz.";
						link.l1 = "Igen, szükségem van rájuk. Egy Helen McArthur nevû fiatal hölgy meghatalmazottja vagyok, ô a híres Nicolas Sharp unokája. Ô az egyetlen törvényes örökös, aki anyja és nagybátyja halála után megmaradt. A nagybátyja végrendelete szerint minden joga megvan Isla Tesoróra. Mennyit kérne azért, hogy segítsen Helennek a sziget jogos úrnôjévé válni?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Uram, még nem ismerem az üzletének anyagát. Kérem, jöjjön el hozzám késôbb, ahogy már mondtam.";
						link.l1 = "Rendben.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Uram, sajnos több idôre van szükségem, hogy összegyûjtsem az összes szükséges iratot a levéltárban. Még nem állok készen. Kérem, találkozzunk késôbb.";
						link.l1 = "Rendben.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Uram, miért dolgozik ilyen lassan?! Az igazgatójának vége. A végrendelet érvényesítésének határideje lejárt, és az Isla Tesoro mostantól Angliához tartozik. Hamarosan katonai bázis lesz belôle."
							link.l1 = "Wow! Úgy tûnik, hogy minden erôfeszítésem hiábavaló volt...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Á, itt van, uram. Megismerkedtem az anyagokkal, így itt az ideje az elôlegnek. Elhoztad a dublónokat?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Igen, hoztam. Itt vannak a dubloonok.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Elnézést a rossz memóriámért, egy ládában hagytam ôket a hajón. Azonnal hozom ôket.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Uram, miért dolgozik ilyen lassan?! Az igazgatójának vége. A végrendelet érvényesítésének határideje lejárt, és az Isla Tesoro mostantól Angliához tartozik. Hamarosan katonai bázis lesz belôle."
							link.l1 = "Wow! Úgy tûnik, hogy minden erôfeszítésem hiábavaló volt...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Uram, talált valamit, ami bizonyítaná a megbízójuk származását?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Még nem. De dolgozom rajta.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Igen. Tényleg kimerítô bizonyítékom van.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "Itt van, uram. Örülök, hogy látom. Be kell vallanom, már régóta vártam önt. Ô az igazgatója?";
						link.l1 = "Igen. Hadd mutassam be Helen McArthurt.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Szüksége van a szolgálataimra, uram? Biztosíthatom, hogy elégedett lesz.";
					link.l1 = "Köszönöm, de egyelôre nincs szükségem rájuk.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "Jó napot, uram. Gondolom, elhozta a honoráriumomat.";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Igen, hoztam. Itt vannak a dubloonok.";
						link.l1.go = "saga_36";
					}
					link.l2 = "Tudja, Mr. Loxley, azt hittem... A lényeg az, hogy 900 dublon több mint elég a munkájához.";
					link.l2.go = "saga_38";
					link.l3 = "Emlékszem, Mr. Loxley. Majd késôbb elhozom...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Szüksége van a szolgálataimra, uram? Biztosíthatom, hogy elégedett lesz.";
				link.l1 = "Köszönöm, de egyelôre nincs szükségem rájuk.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Uram, bizonyára túl sokáig volt a tengeren. Isla Tesoro most az angol haditengerészet katonai bázisa! Igen, Sharp végrendelete létezik, de lejárt, és Isla Tesoro az angol korona tulajdonába került. Sajnos!"
				link.l1 = "Hûha! Úgy tûnik, hogy minden erôfeszítésem hiábavaló volt...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "A hölgy azt állítja, hogy az egész sziget az övé? Hm... Úgy tûnik, hogy ez nem lesz könnyû ügy. Isla Tesoro már majdnem egy angol gyarmat...";
				link.l1 = "Még nem. A végrendelet szerint az a férfi vagy nô lesz Isla Tesoro tulajdonosa, aki megmutatja a térkép mindkét részét. Nekünk megvan Sharp térképének mindkét része, ami az örökség legfôbb bizonyítéka.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicolas Sharp... Nocsak, nocsak. El kell látogatnom egy archívumba, és meg kell ismerkednem az Isla Tesoróra vonatkozó anyagokkal. Magánál van a térkép?";
			link.l1 = "Igen, de csak akkor adom oda, ha aláírtuk a szerzôdést. Szóval, mi a helyzet a szolgáltatásai árával?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Az ön nagyrabecsült részvétele sem marad észrevétlen. Cartagena... Lesznek kérdések.";
			dialog.text = "Ahogy mondtam - nem lesz könnyû. Egy egész sziget tulajdonjogát kell bizonyítania, nem pedig egy öreg kádat vagy egy kunyhót. Különben is, Nicolas Sharp kalóz volt, és a kalózok vagy rokonaik segítése drága mulatság."+sTemp;
			link.l1 = "Megmondja a tényleges összeget?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "Négyszázötven.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "Ezer...";
			dialog.text = "Uram, a végsô összeg a tárgyalás során fog kialakulni. Még mindig nem tudom, mennyire lesz problémás. De kész vagyok egy elôleget megbecsülni - "+sTemp+" dublonok. Ezt az aranyösszeget egyszer vagy kétszer kell majd újra kifizetni, attól függôen, hogy mennyire jól megy majd az üzletünk.\nEgy héten belül hozza el a pénzt, idôre van szükségem, hogy átnézzem az archívumokat és felkészüljek. Aztán majd megegyezünk. Megegyeztünk?";
			link.l1 = "A szigetvilág legjobb ügyvédjeként ajánlottak téged, szóval megegyeztünk. Egy hét múlva találkozunk!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Nagyon jó. Készen állok arra, hogy elvállaljam az ügyét, és képviseljem az érdekeit a bíróságon. Most pedig térjünk a lényegre. Jó munkát végeztem az archívumban, és fontos emberekkel beszéltem. Sharp örökségének ügye nem lesz könnyû. Jó, hogy megszerezte a térkép mindkét darabját. De lehet, hogy ez nem lesz elég.\nDoyle ezredesnek nagy tervei vannak Isla Tesoróval, mivel nem sikerült átvennie az irányítást Tortuga felett. Természetes védmûvekkel rendelkezik, és a jövôben katonai bázisként szolgálhatna ezen a területen.";
			link.l1 = "De Helennek az angol törvények szerint minden joga megvan a szigethez!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Nem tudja talán, hogy a néhai Sharp tett egy kiegészítést a végrendeletéhez. Az örökösnek vagy örökösöknek az ô vezetéknevét kell viselniük. És amennyire emlékszem, a lányodnak más vezetékneve van. Azt mondta, hogy McArthur, igaz?";
			link.l1 = "Ez a mostohaapja vezetékneve, de Helennek minden joga megvan ahhoz, hogy a Sharpot viselje vezetéknévként, mert ô a néhai Beatrice Sharp, Nicolas lányának a lánya.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Pompás! De ki tudja ezt eskü alatt megerôsíteni? Helen nevelôszülei ismerték Beatrice Sharpot?";
			link.l1 = "Amennyire én tudom, akkor nem voltak. Mister McArthur Gladys' lányának tekintette, és Gladys csak a lány apját ismerte.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Ez nagy kár. Nézze, én nem találtam az archívumokban semmilyen említést arról, hogy Beatrice Sharpnak valaha is voltak utódai. Lehetséges, hogy egyáltalán nincs hivatalos feljegyzés a gyermek születésérôl. Bárki nevezheti magát Sharp unokájának, és igényt tarthat arra, hogy viselje a vezetéknevét.";
			link.l1 = "De csak Helen rendelkezik a teljes térképpel!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Ez az ô aduja, és talán elég is lenne, ha a helyi hatóságoknak nem lennének saját terveik Isla Tesoróval. A levéltárban található egy dokumentum, amely Beatrice kézírásával és az ô aláírásával van ellátva. Meg kell találnunk valamilyen általa írt dokumentumot, amely bizonyítaná a lánya születésének tényét, a lányét, akit annak a Gladysnak adtak... eh, mi is volt a vezetékneve?";
			link.l1 = "Chandler. Gladys Chandler Belize-bôl.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Pontosan. Van lehetôségük ilyesmit találni?";
			link.l1 = "Ezt kétlem. Túl sok év telt el. A legenda szerint maga Butcher kapitány lehetett Helen apja. Talán a St. John's-i volt hóhér tud errôl valamit mondani. Ô volt az utolsó ember, aki élve látta a lány apját.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Hm. Tényleg szórakoztató ember volt. Ha jól emlékszem, Raymond Bakernek hívták. Egyszer volt szerencsém beszélgetni vele. Okos és mûvelt ember. Nos, próbálj meg találni valamit Antiguáról, és folytatom a keresgélést az archívumokban, talán találok valami hasznosat.";
			link.l1 = "Rendben. Nekem megfelel.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Add ide Sharp térképét, és siess, beszélj Bakerrel, talán az ô segítségével találsz néhány dokumentumot. Talán még bizonyítékot is találsz a születésérôl.";
			link.l1 = "Eh, bárcsak tudnék. Rendben, viszlát, Mr. Loxley.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "Tényleg? Nézzük meg ezt a bizonyítékot.";
			link.l1 = "Ez egy magánlevél, amit Beatrice Sharp írt a bátyjának. Azt írja, hogy lánya született, és hogy az apja valójában Lawrence Beltrope. A lányt egy Gladys Chandler nevû fiatal özvegyasszonyhoz küldték. Lawrence Beltrope-ot Mészáros kapitányként is ismerik. Tessék, itt van a levél...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "Gladys kész eskü alatt megerôsíteni. Azt is kész megerôsíteni, hogy az apa Butcher kapitányként mutatkozott be.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Várjon egy percet! Butcher kapitányt, a gonosz kalózt és az angol alattvalók gyilkosát húsz évvel ezelôtt felakasztották a Szent János erôdben. Lawrence Beltrope pedig, Richard Doyle közeli barátja, nemrég tragikusan elhunyt. És ami a legfontosabb, Doyle ôt akarta Sharptown új kormányzójává tenni!";
				link.l1 = "Ha! Persze, ezt senki sem tudja... Van egy írásos vallomásom Raymond Bakertôl, St. John's volt hóhérjától, hogy a biztos halál fenyegetése alatt arra kényszerítették, hogy megrendezze Butcher kivégzését! Tessék, nézze meg...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Várjon egy percet! Butcher kapitányt, a gonosz kalózt és az angol alattvalók gyilkosát húsz évvel ezelôtt akasztották fel St. John's erôdjében. Lawrence Beltrope pedig él, és Port Royal egyik legjobb kúriájában lakik. És ami a legfontosabb, Doyle ôt akarja Sharptown új kormányzójává tenni!";
				link.l1 = "Ha! Persze, ezt senki sem tudja... Van egy írásos vallomásom Raymond Bakertôl, St. John's volt hóhérjától, hogy a biztos halál fenyegetése alatt arra kényszerítették, hogy megrendezze Butcher kivégzését! Tessék, nézze meg...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Hm. Nocsak, nocsak...";
			link.l1 = "Hát nem nagyon ügyes? Mészáros kapitánynak sikerült életben maradnia, és visszament Angliába. Visszaváltoztatta a nevét Lawrence Beltrope-ra, és észrevétlenül visszatért ide.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "De ez... Ez mindent megváltoztat! Beatrice levelének közzététele bebizonyítja, hogy a katonai kormányzó mindvégig rejtegette a szökevény kalóz Mészárost, akit azonnal le kellett volna tartóztatni, és akinek bíróság elôtt kellett volna megjelennie a múltbéli bûnei miatt!\nÉs Baker vallomása teljesen megsemmisít minden ellene szóló érvet! Ez nagyszerû! Egy ilyen ásszal a kezünkben tisztességesen meg fogjuk verni Doyle-t!";
			link.l1 = "Örülök neki. Számítok rád ebben a perben. És mondja meg, hogyan halt meg Lawrence Beltrope?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "Ez egy hátborzongató történet, uram. A saját hálószobájában találtak rá, eltorzult arccal. Túl nehéz elképzelni, hogy mi ijeszthette meg ennyire ezt a rettenthetetlen embert. Azt mondják, hogy hófagy borította. A teste tele volt ijesztônek tûnô, tépett sebekkel, de egyetlen csepp vér sem volt a padlón! Képzeljék csak el! Egy csepp vér sem!";
			link.l1 = "Igen, ez egyenesen egy rémálomnak tûnik. Úgy tûnik, hogy meggyilkolták... De ki tehette ezt?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Ez ismeretlen. Túlságosan szövevényes... A helyôrség orvosa azt mondta, hogy a sebei nem voltak halálosak. Beltrope a félelembe, a fájdalomba vagy valami másba halt bele. Mindenesetre ez egy misztikus halál.";
			link.l1 = "Értem... És mikor kezdôdik a tárgyalás?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Minden Öntôl függ, uram. Minden dokumentumot benyújtok a bíróságra, amint kifizeti a honoráriumom második részét - 450 dublont. Helen egy héttel ezután kapja meg a jogait.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Rendben van. Itt vannak a dublonjai.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Igen, persze. Elhozom az összeget, amire szüksége van.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Uram, megdöbbentettél! Olyan sokat tettél, a sziget már majdnem a mi kezünkben volt, de most vége van, mert késlekedtél a honoráriummal! A végrendelet lejárt, és Isla Tesoro mostantól az angol koronához tartozik. Katonai támaszpont lesz."
				link.l1 = "Hûha! Úgy tûnik, hogy minden erôfeszítésem hiábavaló volt...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Elhozta a honoráriumom második részét, uram?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Igen, persze. Itt vannak a dubloonjaid.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Elnézést a rossz memóriámért, egy ládában hagytam ôket a hajón. Azonnal hozom ôket.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "De ez... ez mindent megváltoztat! Beatrice levelének közzététele azt jelenti, hogy Lawrence Beltrope-ot azonnal le kell tartóztatni, és bíróság elé kell állnia a múltbéli bûnei miatt!\nÉs Baker vallomása teljesen megsemmisít minden ellene szóló érvet! Ez nagyszerû! Egy ilyen ásszal a kezünkben tisztességesen megverjük Doyle-t!";
			link.l1 = "Nagyon örülök. Mikor kezdôdik a tárgyalás?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Kitûnô, uram. Öröm volt önnel üzletelni. Nos, itt az alku. Jöjjön vissza holnap. Igen-igen, jól hallotta - holnap! Elvégre én vagyok a szigetvilág legjobb ügyvédje, és vannak kapcsolataim.\nHozza magával az igazgatóját, nélküle nem lesz tárgyalás. Ne késsen, és ne hagyja el a várost. És ha tudod, vidd magaddal a fizetés utolsó részét is, teljesen biztos vagyok a gyôzelmünkben.";
			link.l1 = "Jól van. Holnap az irodájában leszünk, Mr. Loxley.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "MacArthur? Nem, Sharp vagyok! Nos, kövessenek!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Engedje meg, hogy gratuláljak önnek, uram, és az igazgatójának. Mostantól ô Ilsa Tesoro törvényes uralkodója. Érdemes egy kis pezsgôt inni emiatt!";
			link.l1 = "Természetesen, Mr. Loxley. A beszéde kiváló volt. Azt hittem, Doyle ezredes szívrohamot kap, amikor elmondta a bíróságon, hogy Lawrence Beltrop a Mészáros kapitány.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Igen, Mr. Doyle-nak el kell búcsúznia az álmától, hogy katonai bázist létesítsen Isla Tesoro-n. És mit tehetne? A törvény az törvény, és mindenkinek meg van írva, még a tisztelt ezredesnek is.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Minden papír rendben van, és megerôsítik Helen jogát a szigethez?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "Hallottam, hogy a bíró elrendelte Lawrence Beltrop letartóztatását. Feltételezem, hogy fel fogják akasztani?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Természetesen, uram. Minden egyes vesszôt ellenôriztem. Biztos lehet benne, hogy rendben vannak.";
			link.l1 = "Rendben...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Nos, a munkámnak vége. Az ügy bonyolult volt, de együtt nyertük meg. Most már csak a honoráriumom utolsó részét kell kifizetnie, uram. Nem akarom sürgetni, tudom, hogy biztos elfoglalt. De hiszem, hogy egy héten belül talál idôt arra, hogy elhozza nekem az utolsó 450 dublont.\nMellesleg, egy ilyen ügyfél, mint ön, mindig jelentôs árengedményekre számíthat. Sokat tudok segíteni önnek, a szigetvilág minden fôvárosába, még az ellenséges fôvárosokba is vannak kapcsolataim, így bármilyen jogi problémája megoldható.";
			link.l1 = "Kiváló. Most már tudom, kit kell megkérdeznem.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "Garantálom, hogy még a legnehezebb helyzetekben is pozitív eredményt ér el.";
			link.l1 = "Remek. Most mennem kell, nekem és Helennek sok dolgunk van.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Viszlát, uram.";
			link.l1 = "Viszontlátásra, Mr. Loxley.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "Gondolom, ô Mészáros kapitány, kalóz és bandita. Bár ô most nincs Port Royalban. Szerencsésen távozott, mélyen a szigetre költözött. De a vadászat megkezdôdött, és biztosan el fogják kapni.";
			link.l1 = "Értem... A papírok rendben vannak?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nagyszerû! Öröm volt önnel üzletelni, uram! Mostantól bármilyen ügyben kérheti a segítségemet, és kedvezményt kap. Gondok a törvénnyel, vérdíj a fejére... Szívesen látjuk. Mindig örülni fogok, ha találkozunk.";
			link.l1 = "Jobb lenne, ha egyáltalán nem kerülnék bajba, de... történnek dolgok. Köszönöm és viszlát, Mr. Loxley.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "Hogy érti ezt, uram? Megszegi a megállapodásunk feltételeit?";
			link.l1 = "Pontosan. A munka nagy részét én végeztem. El sem tudja képzelni, mit kellett tennem, hogy megszerezzem a bizonyítékot. És maga csak fogta azokat a papírokat, és elment a bíróságra. Kilencszáz dublon több mint elég, ebben biztos vagyok.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Úgy beszél, mint egy kalóz, uram! Nos, én nem leszek szegény, ha elveszítek négyszázötven dublont, de maga sem lesz gazdag. Sôt, sokkal többet vesztettél! És talán a jövôben is veszíteni fog valamit... Azonnal hagyja el a házamat, és soha többé ne mutatkozzon itt!";
			link.l1 = "És ezt meg is fogom tenni. Isten önnel, Loxley úr!";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "Nem akarok beszélni magával. Tûnjön el, vagy hívom az ôrséget!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Uram, megnyertük volna az ügyét, ha korábban eljött volna hozzám. A végrendelet lejárt. Sajnálom, uram.";
			link.l1 = "Eh, én még jobban sajnálom! Nos, viszlát, Mr. Loxley.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", Uram. Örülök, hogy látom. Szüksége van a szolgálataimra?";
			link.l1 = "Igen. Ezért vagyok itt.";
			link.l1.go = "loxly_1";
			link.l2 = "Nem, szerencsére jelenleg nincs rá szükségem. Csak üdvözölni akartam.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "Készen állok meghallgatni önt. Milyen segítségre van szüksége?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "Bajban vagyok az angol hatóságokkal.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "Bajban vagyok a francia hatóságokkal.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "Bajban vagyok a spanyol hatóságokkal.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Bajban vagyok a holland hatóságokkal.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Összevesztem a csempészekkel.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "Sajnálom, meggondoltam magam...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "Már dolgozom az ügyén. Minden rendben lesz, biztosíthatom.";
			Link.l1 = "Köszönöm. Köszönöm. Várni fogom.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			i = sti(npchar.quest.relation);
			iLoxlyPseudoGlobal = CalculateRelationSum(i, true);
			int iRate = abs(ChangeCharacterNationReputation(pchar, i, 0));
			if (iRate <= 10) sTemp = "Nos, ezt nem nevezném bajnak. Csak egy kis probléma. Azonnal elintézem az ügyet.";
			if (iRate > 10 && iRate <= 30) sTemp = "Igen, a hírneve kissé romlott, de nem látok semmi kritikusat. Azonnal elintézem az ügyet.";
			if (iRate > 30 && iRate <= 60) sTemp = "Igen, rossz útra tévedtél a hatóságokkal. Nem lesz könnyû, de biztos vagyok benne, hogy gond nélkül elintézem a nézeteltéréseiteket.";
			if (iRate > 60 && iRate <= 90) sTemp = "És hogyan csinálta ezt, uram? A gondjai nem egyszerûen komolyak, hanem tényleg komolyak. A hatóságok nagyon szeretnének elkapni téged. Nagy erôfeszítéseket kell tennem, hogy rendezzem a nézeteltéréseit.";
			if (iRate > 90) sTemp = "Hát... A helyzet katasztrofális - állítják önrôl, mint a legádázabb ellenségrôl. Nehéz lesz, de végül is én vagyok a legjobb ügyvéd a Karib-tengeren, úgyhogy elintézem a nézeteltéréseiteket.";
			dialog.text = ""+sTemp+" a "+XI_ConvertString(Nations[i].Name+"Abl")+". Ez a "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(pchar.money) >= iLoxlyPseudoGlobal)
			{
				link.l1 = "Rendben, Mr. Loxley, egyetértek. Itt a pénze, és próbálja meg minél hamarabb rendezni a dolgokat.";
				link.l1.go = "relation";
			}
			link.l2 = "Most nincs nálam annyi pénz, amennyit kér. Késôbb visszajövök!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			i = sti(npchar.quest.relation);
			dialog.text = "Öröm volt önnel üzletelni, uram. Újra szabadon lélegezhet, a problémája a következô két hétben megszûnik. Kérem, kerülje a konfrontációt " + XI_ConvertString(Nations[i].Name + "Abl") + ", amíg a tárgyalások közepén vagyok.";
			link.l1 = "Rendben, figyelembe veszem a figyelmeztetését. Köszönöm és viszlát!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
			ChangeNationRelationFromRelationAgent(i);
			attrLoc = "RelationAgent" + GetNationNameByType(i);
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			iLoxlyPseudoGlobal = CalculateRelationContraSum(true);
			dialog.Text = "És miért tetted ezt? A csempészek jó fiúk, a maguk módján becsületesek. Mindannyiunknak élni és enni kell... Rendben, nem nagy ügy, és csak "+FindRussianMoneyString(iLoxlyPseudoGlobal)+".";
			if(sti(Pchar.money) >= iLoxlyPseudoGlobal)
			{
				Link.l1 = "Rendben, Mr. Loxley, egyetértek. Itt a pénze, és próbálja meg minél hamarabb rendezni a dolgokat.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Most nincs nálam annyi pénz, amennyit kér. Késôbb visszajövök!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Kitûnô, megoldom a problémádat. Hamarosan újra üzletelni akarnak majd veled.";
			Link.l1 = "Köszönjük!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -iLoxlyPseudoGlobal);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
