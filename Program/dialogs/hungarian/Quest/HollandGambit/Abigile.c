// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Jó napot, mynheer. Mi szél hozta az otthonunkba?";
					link.l1 = "Jó napot, Abigail. A nevem " + GetFullName(pchar) + ". Kapitány vagyok, aki a Köztársaság és a Holland Nyugat-indiai Társaság javára dolgozik.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Istenem, megtaláltad apám pénzét? Igaz ez? Ah, annyira örülök! Gyorsan menj apámhoz, beszélni akar veled. Menj és látogasd meg!";
					link.l1 = "Máris megyek, asszonyom.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "Megmentettél minket a teljes kétségbeeséstôl, kapitány! Annyira hálás vagyok önnek! Most már helyreállhat a Shneur család jó híre!";
					link.l1 = "Csak úriemberi kötelességemet teljesítem, asszonyom. Remélem, semmi sem tartja vissza attól, hogy feleségül menjen a pártfogómhoz.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Szüksége van valamire, kapitány?";
				link.l1 = "Most nem, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Üdvözlégy Szent Királynô, életünk, édességünk és reményünk. Hozzád kiáltunk, Éva szegény számûzött gyermekei. Hozzád küldjük fel sóhajainkat, gyászolva és sírva a könnyek völgyében... Ó, mynheer, megijesztettél! Mi szél hozott ide?";
					link.l1 = "Bocsáss meg, Abigail, ha jól sejtem? Richard Fleetwood küldött...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Akar valamit, kapitány?";
				link.l1 = "Most nem, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Mi folyik itt? Mi ez a zaj? Papa, ki ez az idegen férfi?";
					link.l1 = "Jó napot, asszonyom. Abigail Schneur, ugye? Örülök, hogy látom. Bocsássa meg a szemtelenségemet, de van itt egy sürgôs levél, amit önnek címeztek... nos, szívesen elmondanám, de a kedves apja még azt sem engedi, hogy a házában álljak, nemhogy átadjam önnek ezt az üzenetet.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Á, itt vagy, Charles. Kész vagyok követni téged bárhová!";
					link.l1 = "Akkor menjünk.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "Már a Szent Jánosnál vagyunk, Charles? Hamarosan találkozom Richarddal?";
					link.l1 = "Igen, madame, St. John's-ban vagyunk. Sajnos Richard jelenleg nincs a városban, két napja parancsot kapott, hogy Barbados közelében járôrözzön. Ne aggódjon, egy héten belül visszatér.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charles! Annyira örülök, hogy látlak! Van valami hír Richardról?";
					link.l1 = "Sajnos, drága madame. Richárdnak egy ideig Bridgetownban kellett maradnia egy titkos és fontos küldetés miatt, valami hollandokkal kapcsolatos dologról van szó. Gondolom, Richard elmondta, hogy mivel foglalkozik, ugye?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Charles! Te vagy az! Végre visszatértél!";
					link.l1 = "Üdvözlöm, madame. Örülök, hogy látom.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ah, végre itthon vagyok! Annyira örülök, hogy újra látom a papát! Charles, köszönök mindent, amit értem tettél!";
					link.l1 = "Kérem, nincs szükség ilyen beszédre, madame. Csak úriemberként teszem a kötelességem egy bajba jutott hölgyért.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Papa, ha eszedbe jut valami, kérlek, mondd el! Charles, ô... benne meg lehet bízni. Merem állítani, hogy ô az egyetlen, aki segíthet rajtunk!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "Imádkozni fogok érted éjjel és nappal! Mondd... mondd, hogy meg fogod tenni! Hogy megtalálod a szigetet!";
					link.l1 = "Megteszem, amit tudok, asszonyom.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Á, Charles! Visszajöttél! Mondd gyorsan, megtaláltad a szigetet? Nem tudok tovább várni!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Igen, Abi. Megtaláltam a szigetet és apád pénzét. Azért jöttem, hogy visszaadjam neked.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Sajnos, asszonyom. Nem találtam sem Keller kapitányt, sem a szigetet. Megtettem, amit tudtam, de...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "Á, te vagy az, Charles! Szüksége van valamire? Megkínálhatom egy kis kávéval?";
				link.l1 = "Nem, semmit. Kérem, ne fáradjon.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Jó napot, mynheer. Mi a baj?";
			link.l1 = "Semmi, asszonyom. Elnézését kérem. Viszontlátásra.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "Megtiszteltetés, hogy megismerhetem, kapitány " + GetFullName(pchar) + ". Sokféle történetet hallottam már önrôl a többi hölgytôl a városban. Ön az az ember, aki elfogta a kalózok szellemhajóját, és zsákmányként Willemstadba hozta. Mondja kapitány... igaz az, hogy a hajó parancsnoka volt... Richard Fleetwoodé volt?";
			link.l1 = "Minden, amit hallott, igaz, asszonyom. Ugyanúgy megdöbbentem, mint bárki más, amikor megtudtam az igazságot. Ez egy botrány! Az Angol Nemzetközösség tengerésztisztje saját nemzetének kereskedôit fosztogatja, mint egy közönséges kalóz! Ez a gazember úgy próbálta álcázni aljas tetteit, hogy úgy tett, mintha egy renegát 'szellemhajó' lenne a Holland Nyugat-indiai Társaság támogatásával. Ezt az álcát arra használta, hogy a Társaságot hibáztassa, és holland hajókat is megtámadjon.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "Kavarog a fejem... Nehéz ilyen szörnyû dolgokat hallani, kapitány. Személyesen ismertem Richard Fleetwoodot, de soha nem gondoltam volna, hogy...";
			link.l1 = "Asszonyom, Lucas Rodenburg, a pártfogóm tájékoztatott az Ön Curacaóba tartó útjáról Recifébôl. Most már világos. Fleetwood elsüllyesztette a hajóját, majd visszatért 'save' Önt és az apját attól, hogy azon az elveszett szigeten ragadjanak. Magam is olvastam a kalóz naplóját, minden részletet feljegyzett a naplójában.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Micsoda rémálom... Úgy tûnik, apámnak mégiscsak igaza volt. Azt mondta nekem, hogy Richard volt az a kalóz, aki minden szerencsétlenségünk forrása volt. Örülnöm kellene, hogy kiderült az igazság... áh, sajnálom, kapitány úr. Szegény fejemnek túl sok mindent kell befogadnia... mit akar egy ilyen fontos ember, mint ön, egy közönséges lánytól?";
			link.l1 = "Abigail, egy nagyon bonyolult és kényes ügy miatt vagyok itt. Meghallgatna engem?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Természetesen, mynheer. Csupa fül vagyok.";
			link.l1 = "Ahogy mondtam, a Társaságot szolgálom. Lucas Rodenburg nem csak a katonai parancsnokom, hanem jó barátom is. Ô küldött hozzád egy üzenettel. A legnagyobb boldogság lenne számodra, ha beleegyeznél a házassági ajánlatába. Azért vagyok itt, hogy megkérjem a pártfogóm kezét. Ô kész bármit megtenni a világon az ön boldogságáért.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "Ó, kapitány! Most már értem, hogy Mynheer Rodenburg miért nem volt hajlandó erre maga is... Szegény apám nagyon boldog lenne, de én...";
			link.l1 = "Asszonyom, látom, hogy valami bántja önt. Kételkedik Mynheer Rodenburg ôszinteségében? Talán segíthetnék megváltoztatni a véleményét?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "Ó, nem kapitány, nem kételkedem Mynheer Rodenburg ôszinteségében. Lucas olyan sokat tett értem és a papámért, nem tudom, mi történne velünk, ha nem vigyázna ránk. De kérem, értse meg a helyzetemet!\nA családom nem Rothchild, de sosem voltunk szegények. A Shneur család Európa bankházai között jól ismert a vagyonunkról... de most ez a szörnyû kalóz tönkretett minket! Nem tûrhetem tovább ezt a csúnya pletykát, amirôl tudom, hogy a hátunk mögött folyik. A város minden fecsegô háziasszonya és szolgálólánya azt hiszi, hogy én csak Mynheer Rodenburg pénzére hajtok. 'Mily nagyon hasonlítok egy zsidó nôre,' mondják. A kegyetlen nyomorultak! Bárcsak apám emlékezne a sziget helyére! Ott rejtette el a családi vagyonunk maradékát, hogy megmentse azoknak a gonosz kalózoknak a kezétôl, akik meggyilkolták a nôvéreimet és a bátyámat!\nDe szegény apám nem tengerész, egyszerûen nem emlékszik, hol van az a sziget és a családunk pénze! Kérem, beszéljen az apámmal, kapitány! Talán ô fel tud idézni valamit, ami hasznos lehet az önök tapasztalt érzékei számára. Kérem, találja meg azt a szigetet és a vagyonunkat! Megmentettél egy szegény lányt a szégyentôl és a szégyentelenségtôl!";
			link.l1 = "Rendben van, Abigail. Beszélek apáddal. Bízz bennem, kislány, megteszem, amit tudok.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Köszönöm, mynheer. Imádkozni fogok érted éjjel és nappal. Atyáink Istene legyen veled!";
			link.l1 = "Isten veled, Abigail. Jó hírekkel térek vissza, esküszöm.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "Ó, igen! Mynheer Rodenburg becsületes és kedves ember. Habozás nélkül beleegyezem, és boldog leszek, ha férjemnek nevezhetem.";
			link.l1 = "Akkor befejezettnek tekintem a küldetésemet. Most el kell mennem Mynheer Rodenburghoz, és elmondani neki a jó hírt. Ôszintén boldogságot kívánok önnek, asszonyom.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "Richard küldte?! Áldott Mária, köszönöm! Ah, mynheer! Hallottam, hogy szegény Richárd megsebesült és közel állt a halálhoz. Igaz ez? Mondd, életben van?! Egészséges?!";
			link.l1 = "Richard él és... többnyire egészséges. Elôször a rossz hírek: egy kicsit rosszabbul van, és ideiglenesen megvakult, de már javulóban van. Most a jó hír: Richard azt akarja, hogy elhajózzatok vele Angliába, ahol összeházasodtok. A Karib-tengeren töltött ideje lejárt, és várja a válaszodat.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ah, kedves hírnököm, mondd meg Richárdnak, hogy a boldogságunk érdekében kész vagyok vele menni, ahová csak akar. De félek, hogy a szökésünk megöli szegény apámat... Uram, kétségbe vagyok esve, és nem tudom, mit tegyek. Bárcsak Richard megtalálná azt az elátkozott szigetet és a ládát a családi aranyunkkal... Talán ez valahogy megvigasztalná apámat a távollétemben.";
			link.l1 = "Értem... Az volt a feladatom, hogy elhozzalak Antiguára, de ez kissé bonyolítja a dolgokat. Ha megtalálom a szigetet és a ládát, és elhozom neked, akkor velem jössz Szent Jánosba és Richardhoz?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "Ó, igen, uram, megemlékeznék önrôl a családi imáinkban! Az elsôszülött fiunkat rólad nevezném el! Köszönöm szépen, kapitány úr! Imádkozni fogok önért! Menjetek, és Krisztus és a Boldogságos Szûzanya legyen veletek!";
			link.l1 = "Nem akarom, hogy túl sokáig várjon rám, asszonyom. Hamarosan visszatérek.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Ó... Van egy leveled tôle? Ó, papa, ne légy ilyen szigorú a vendégeinkkel! Zavarba hozol a neurotikus fantáziáddal! Mynheer, kérlek, kövess, beszélni akarok veled.";
			link.l1 = "Köszönöm, kisasszony. Örülök, hogy látok valakit ebben a házban, aki értelmesen beszél.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Bocsáss meg apámnak, Mynheer. Igazán jó és kedves ember, de a mi... szerencsétlenségünk megtörte ôt.";
			link.l1 = "Semmi baj, úrnôm, megértem. Hadd mutatkozzam be, Charlie vagyok, a... Knippel. Richard Fleetwood parancsára vagyok itt, azt akarja, hogy vigyem el hozzá. Tessék, kérem, olvassa el a levelet.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Oh Richard...(olvasás). Oh, Istenem! Úgy döntött... hogy visszaadja apámnak az összes elveszett pénzét! Micsoda nagylelkûség! Drága, édes Richard! Mynheer, te úgy hozol jó híreket, mint maga Gábriel! Richard, hol van? Curacaón van?";
			link.l1 = "Nem, kisasszony. Megpróbálták megölni, és súlyosan megsebesült. Most Antiguán van... még nem fejezte be a levelet.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "Szûz Mária, aki bûn nélkül fogant, imádkozz értünk, akik hozzád folyamodunk! Mondd, biztonságban van? Súlyos a sebe?";
			link.l1 = "Ne aggódjon így, kisasszony! Richard nem az a fajta ember, aki hagyja, hogy néhány fattyú csak úgy megölje. Most pihen és gyógyul. Azt akarja, hogy elvigyem hozzá. Aztán maguk ketten elhajóznak Londonba... Kérem, fejezze be a levelet, kisasszony, elsiet.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ah, igen... elnézést(olvasás). Myheer Knippel, készen állok, hogy veled hajózzak. Egy napra van szükségem, hogy összepakoljam a holmimat és beszéljek a papámmal. Gyere vissza holnap, és veled megyek.";
			link.l1 = "Rendben, hölgyem. Holnap itt leszek. Ne aggódj, én és a legénységem megvédünk minden veszélytôl az utunk során.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, milyen kár. De azt hiszem, még egy hetet tudok várni, ahogy eddig is vártam...";
			link.l1 = "Jól mondta, kisasszony. És hogy megkönnyítsem a várakozását, azt javaslom, hogy cserélje el ezt a meglehetôsen szigorú kabinját a barátom házára. Ott puha ágy és finom ételek várják majd.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "Nagyon kedves vagy, Charlie. Köszönöm, Charlie. Jó lesz szárazföldet találni a lábam alatt... Eléggé émelygek a hullámokon való hánykolódás után.";
			link.l1 = "Kövessen, kérem, kisasszony.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "Örülök, hogy találkoztunk, John. Köszönöm a kedves vendéglátást, uraim!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "Ó, Charlie, Richarddal csak néhányszor találkoztam, és nem sokat mesélt arról, hogy mivel foglalkozik.";
			link.l1 = "Eléggé meglep, hogy ilyen nagy titkot rejteget a nô elôl, akit szeret... Kisasszony, Richard nem egy átlagos kapitány. Ô az angol titkos tanács különleges ügynöke is. Egy nagyon fontos ember, aki kényes megbízásokkal foglalkozik, amelyeket közvetlenül maga a Lord Protector rendel el. Jelenleg az ô feladata a holland Nyugat-indiai Társaság karibi kereskedelmi hatalmának megsemmisítése.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Uram, mirôl beszél?";
			link.l1 = "Igen, kisasszony. Az ön szeretett Richardja - a barátom - nagyon fontos ember. Mindig is büszke voltam rá, hogy a barátja lehetek, de mostanában még velem szemben is nagyon titkolózik. Nyilvánvaló, hogy valami titkos küldetésen van. Nagyon sajnálom, hogy ez a küldetés nem teszi lehetôvé, hogy találkozzon önnel.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, megijesztesz. Biztos vagy benne, hogy jól van?";
			link.l1 = "Biztos vagyok benne. Én csak... Nem helyeslem, ahogy most veled bánik. Megértem, hogy a megbízatása létfontosságú, és még érted sem árulhatja el a kötelességét.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Ó, kedves Charlie... Ha kell, a második eljövetelig várok Richardra. Talán a kocsma fölött maradhatnék... Nem használhatom ki John vendégszeretetét ilyen sokáig.";
			link.l1 = "Ne beszéljen ostobaságokat, hölgyem! Az ön jelenléte megtisztel bennünket, és nem Charlie a Knippel a nevem, ha kiutasítom a menyasszonyom menyasszonyát kedves barátom, Richard Fleetwood házából és otthonából!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... Nagyon meghatott a hozzám való hozzáállása. Én csak egy közönséges lány vagyok, ráadásul zsidó...";
			link.l1 = "Kisasszony! Tudom, hogy ez vakmerô beszéd, ön egy remek keresztény fiatalasszony! És ne is gondoljon a kocsmákra! Soha nem bocsátom meg magamnak, ha cserbenhagylak Richárd szolgálatában.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Köszönöm, Charlie. Örülök, hogy ilyen... jó ember vagy.";
			link.l1 = "Ez a kötelességem, kisasszony. Most sajnálom, de mennem kell. Most már szabadon sétálhat a városban, biztosan magányosnak érzi magát ebben a házban, igazam van?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Hát... John nagyon érdekes társaság. Órákig tud beszélni a porairól, keverékeirôl és különbözô... betegségekrôl. Udvarias és kedves ember is. Rendszeresen járok templomba is, a helyi pap nagyon kedves... de persze Richard nagyon hiányzik.";
			link.l1 = "Azt hiszem, hamarosan visszajön. Charlie a Knippel áll rendelkezésedre, ha bármire szükséged van.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "Hallottam pletykákat Richardról... hogy eltûnt. Tudsz róla valamit, Charlie?";
			link.l1 = "Tudok, Abigail. Sajnálom, hogy... Richard Fleetwood elment Angliába, és nem fog visszajönni. Elôléptették vagy áthelyezték, vagy valami ilyesmi... mindegy, azok után, amit veled tett, nem akarom megismerni.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ah, tudtam, hogy így fog végzôdni....(zokog) Miért nem hallgattam a papára! Ô legalább örült volna, ha hozzámegyek Lucas Rodenburghoz.";
			link.l1 = "Bocsásson meg még egyszer, kisasszony...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "Miért, Charlie? Egyáltalán nem vagy bûnös. Csak kedves voltál hozzám!";
			link.l1 = "Hogy még több rossz hírt mondtam neked. Most érkeztem vissza Curacaóból, Lucas Rodenburgot letartóztatták a Köztársaság elleni lázadásért és árulásért. Láncra verve visszaküldik Amszterdamba, hogy bíróság elé álljon. Megpróbálta meggyilkolni Peter Stuyvesantot, a Társaság igazgatóját. Ráadásul megkísérelte megdönteni Willemstad kormányzójának hatalmát, és legalább egy másik személy meggyilkolásával is gyanúsítják, így kétlem, hogy a Stadtholder megpofozná.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Ó, Istenem! Micsoda rémálom! Azt hiszem, mindjárt elájulok! Charles, igaz ez? Nem, kérlek, mondd, hogy nem!";
			link.l1 = "Sajnálom, kisasszony, ez egyre rosszabb lesz. Rodenburg tetteinek vizsgálata során kiderült, hogy a kalóz, aki elsüllyesztette a flottáját, Lucas Rodenburg parancsára cselekedett. A saját magánháborúját vívta az angol hajózás ellen. Nagyon sajnálom, Abigail. Mindazok, akikkel itt a Karib-tengeren találkoztál, hazugok, tolvajok és gyilkosok voltak.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Ó...tönkrementem. Charles... kérlek... vigyél haza Willemstadba. Szükségem van a papámra...";
			link.l1 = "Természetesen, kedves kisasszony. Sajnos, itt St. John's nincs semmi az ön számára. Menj, pakolj össze, búcsúzz el Johntól, és azonnal indulunk.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "Nem, Charlie, meg kell köszönnöm. Ha te és John nem lennétek, nem is tudom, mi történne velem. Ti vagytok az egyetlen becsületes emberek, akikkel a szigetvilágban találkoztam.";
			link.l1 = "Hm... elpirulok tôled, Abigail. Örülök, hogy segíthettem neked. És nagyon sajnálom ezt az egész zûrzavart.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "Tudod, Charlie, sokat gondolkodtam a curacaói utazásunk alatt. Most már minden világos - Richard Fleetwood, Mynheer Rodenburg - minden csak egy szörnyû rémálomnak tûnik, ami végre véget ért. Újra az apámmal vagyok, és visszatérhetünk a normális életünkhöz\nNem lesz azonban könnyû - nincs pénzünk. De átvészeljük, minden rendben lesz. A Szûzanya vigyázni fog ránk, ô soha nem felejti el a gyermekeit, még az én makacs öreg apámat sem, aki megtagadja a Fiát.";
			link.l1 = "Abigail kisasszony, segíteni fogok önnek.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "Segít nekünk? De hogyan, Charlie?";
			link.l1 = "Richard elmesélte nekem a hajótörésed és a megmentésed történetét. Azt is tudom, hogy apádnak sikerült elrejtenie a holmiját egy ismeretlen szigeten. Meg fogom találni, és visszahozom a pénzedet.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Ó, Charlie... Sem én, sem az apám nem tudjuk megmondani, hol van az a szerencsétlen sziget... Nem vagyunk tengerészek. Ráadásul az életemért rettegtem a támadás alatt, a véren és a halálszagon kívül semmire sem emlékszem.";
			link.l1 = "Abigail, próbálj meg emlékezni. Kérlek, minden részlet segíthet, még a legapróbb részletek is. Talán történt valami a támadás elôtt? Hogy néz ki ez a sziget?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "Sziget... Úgy néz ki, mint egy sziget? Egy öböl, dzsungel. Semmi sem tûnt fel nekem. Ó, emlékszem! Talán ez segíthet neked. Nem sokkal a kalóztámadás elôtt találkoztunk egy flottával, és üdvözöltük a kapitányát. Meghívták a hajónkra, és együtt vacsoráztak a kapitányunkkal. Mi is ott voltunk. Talán ô is tud errôl a szigetrôl.";
			link.l1 = "Ez már valami! Mi volt a neve a fluytnak és a kapitányának?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "Nem emlékszem, Charlie. Tényleg nem...";
			link.l1 = "Próbálj meg emlékezni, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "Várni fogunk rád. Segíts nekem, Charlie, a Knippel. Te vagy az egyetlen reményünk... Imádkozni fogok érted! Isten éltessen!";
			link.l1 = "Már úton vagyok. Viszlát, Abi. Isten veled, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Ó, kedvesem... milyen kár. Reméltük, de... köszönjük, Charlie, hogy megpróbáltál segíteni nekünk, amikor senki más nem akart. Úgy tûnik, Isten ezt a sorsot szánta nekem.";
			link.l1 = "Isten veled, Abigail. Remélem, hogy minden rendben lesz.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "Ez... ez igaz? Tényleg visszahoztad nekünk az elveszett pénzünket? Ó, Charlie!";
			link.l1 = "Igen, ez igaz. Megvan. Tessék, vedd el. Ez mind a tiéd.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "Hogy köszönhetném meg?! Hogyan?!";
			link.l1 = "Nincs szükségem köszönetre, Abi. Ez a legkevesebb, amit tehetek érted. Most új életet kezdhetsz anélkül, hogy Rodenburgok, Fleetwoodok vagy más idegen férfiak megpróbálnának kihasználni téged. Biztos vagyok benne, hogy apád megtalálja a módját, hogy ez a pénz még több pénzt termeljen... úgy tûnik, ez egy öröklött tulajdonság.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Charlie, ne légy ilyen szemtelen! Olyan sokat tettél értem, értem és szegény apámért. Megszoktam a jelenlétedet az életemben. Fáradhatatlanul imádkoztam érted minden nap, és ezután is minden nap imádkozni fogok érted és a legénységedért a Szûzanyához! Te vagy a mi ôrangyalunk. Maga az Úr küldött téged a családunkhoz, akár hiszed, akár nem\nMielôtt elmész, szeretném, ha tudnád, hogy házunk ajtaja mindig, bármikor nyitva áll elôtted. És... kérlek, hadd csókoljalak meg, drága Charlie...";
			link.l1 = "Nos... igen, persze Abi... ha ragaszkodsz hozzá.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "Isten áldjon, Charles. Semmi sem változott számunkra... a templom elôtt koldulok a maradékért.";
			link.l1 = "Maradjon erôs, kisasszony. Isten legyen önnel.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charles, te vagy az! Úgy örülök, hogy látlak! Kérlek, ülj le! Fôzök egy kávét!";
			link.l1 = "Én is örülök, hogy látlak, Abi. És örülök, hogy jól vagy.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Á, szóval ennyi?! Vendégül láttalak, és te úgy döntöttél, hogy kirabolsz?! Ôrség!";
			link.l1 = "Fogd be a szád, ostoba lány.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
