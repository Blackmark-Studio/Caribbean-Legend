// диалог индейцев в поселениях
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Nincs mirôl beszélnünk!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> индейцы в поселении
		case "IndianMan":
			NextDiag.TempNode = "IndianMan";
			dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Sápadtarcú","Fehér squaw") +" akar beszélgetni?", 
				"Már megint te, "+ GetSexPhrase("sápadtarcú","fehér squaw") +".", 
				""+ GetSexPhrase("Paleface szeret beszélgetni. Úgy néz ki, mint egy squaw.","Fehér squaw szeret beszélni.") +"",
                "szellemek hozták el hozzám a sápadtarcú "+ GetSexPhrase("bátyámat","húgomat") +" .", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Igen.", 
				"Igen, megint én.",
                "Nagyon költôi.", 
				"Én is örülök, hogy látlak.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		
		case "IndPearlMan_1":
			dialog.text = "Mondd, miért jöttél, sápadtarcú?";
			link.l1 = "Ó, semmi különös, csak meg akartam hallgatni, hogy mit akarsz mondani...";
			link.l1.go = "exit";
		break;
		
		case "IndianWoman":
			NextDiag.TempNode = "IndianWoman";
			dialog.text = NPCStringReactionRepeat("Fehér ember beszélgetni akar?", 
				"Már megint te, sápadtarcú?", 
				"A sápadtarcú szeret beszélgetni.",
                "Szellemek hozták el hozzám a sápadtarcú bátyámat.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Igen.", 
				"Igen, megint én.",
                "Nagyon költôi.", 
				"Én is örülök, hogy látlak.", npchar, Dialog.CurrentNode);
			link.l1.go = "IndianWoman_1";
		break;
		
		case "IndianWoman_1":
			dialog.text = LinkRandPhrase(""+npchar.name+" hallgass meg, tenger fia.","Mit akarsz "+npchar.name+", sápadtarcú?","A fülem nyitva áll a szavaidra, idegen.");
			if (CheckIndianGift() && !CheckAttribute(npchar, "quest.gift"))
			{
				link.l1 = LinkRandPhrase("Van valamim a számodra. Akarod megnézni?","Szeretnél megnézni valami igazán érdekeset? Biztosan tetszeni fog...","Van valamim, ami tetszeni fog neked, a dzsungel gyermeke. Akarod megnézni?");
				link.l1.go = "gift";
			}
			link.l9 = "Ó, semmi különös, csak meg akartam hallgatni, hogy mit akarsz mondani...";
			link.l9.go = "exit";
		break;
		
		case "gift":
			iTemp = 2;
			dialog.text = RandPhraseSimple(""+npchar.name+" meg akarja nézni. Mutasd meg.", ""+npchar.name+" érdekli. Mutasd meg!");
			if (CheckCharacterItem(pchar, "mineral6"))
			{
				link.l1 = "Adj egy tükröt.";
				link.l1.go = "gift_1";
			}
			for (i=50; i>=47; i--)
			{
				if (CheckCharacterItem(pchar, "jewelry"+i))
				{
					sTemp = "l"+iTemp;
					link.(sTemp) = "Adj"+XI_ConvertString("ékszert"+i)+".";
					link.(sTemp).go = "gift_"+i;
					iTemp++;				
				}
			}
		break;
		
		case "gift_1":
			RemoveItems(pchar, "mineral6", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ó! Most már "+npchar.name+" nem csak a folyóvízben nézheti magát! Köszönöm, kedves idegen!";
			link.l1 = "Persze, most már annyit csodálhatod az arcodat, amennyit csak akarod...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_47":
			RemoveItems(pchar, "jewelry47", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ó! Olyan gyönyörû! Ez a karkötô a "+npchar.name+"? Köszönöm, kedves idegen!";
			link.l1 = "Tedd fel a mogorva kezedre, szépségem, csodásan fogsz kinézni...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_48":
			RemoveItems(pchar, "jewelry48", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ó! Milyen gyönyörû gyûrû? Ez a "+npchar.name+", ugye? Köszönöm, kedves idegen!";
			link.l1 = "Húzd fel az ujjadra, és minden barátod irigykedni fog...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_49":
			RemoveItems(pchar, "jewelry49", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ó! Azok a csodálatos zöld gyöngyök a "+npchar.name+"? Annyira gyönyörû! Köszönöm, kedves idegen!";
			link.l1 = "Díszítsd velük a nyakadat, a szelva lánya. Mindenki csodálni fog téged...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_50":
			RemoveItems(pchar, "jewelry50", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Ó, milyen gyönyörû zöld gyûrû! Ez egy ajándék a "+npchar.name+"? Köszönöm, kedves idegen!";
			link.l1 = "Jól fog kinézni a kezeden, szépséges...";
			link.l1.go = "gift_exit";
		break;
		
		case "gift_exit":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) // Addon 2016-1 Jason Пиратская линейка
			{
				dialog.text = "Akartál kérdezni "+npchar.name+" valamit, a tenger fia?";
				link.l1 = "Igazad van, szépségem. Én és rettenthetetlen harcosaim Selvába megyünk, a spanyol településre a hegyek közé, és vezetôt keresünk. Nagylelkû leszek magához az emberhez és a feleségéhez is. Sok gazdagságom van: gyönyörû fegyverek, varázsszemüvegek, tükrök, nyakláncok, karkötôk és gyûrûk. Talán a férjed lehet az általunk keresett idegenvezetô?";
				link.l1.go = "hayamee";
			}
			else
			{
				DialogExit();
			}
			ChangeIndianRelation(1.00);
			npchar.quest.gift = true;
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		// Кумвана, вождь деревни араваков
		case "cumvana":
			dialog.text = "Üdvözletem, tenger fia. Én vagyok Kumwana, a Locono nép Teknôs klánjának fônöke. Milyen ügy hozott a falumba?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Ajándékot hoztam neked, fônök. Nézd meg, tetszeni fog neked.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "Fônök, azért jöttem, hogy a segítségedet kérjem. El akarok jutni egy Merida nevû spanyol településre, ami a hegyek között található a selvatoknál, a probléma az, hogy nem tudom, hogyan jutok oda.";
				link.l1.go = "cumvana_no";
			}
			DelLandQuestMark(npchar);
		break;
		
		case "cumvana_no":
			dialog.text = "Ez nagyon jó neked, tenger fia, hogy nem ismered az oda vezetô utat. Egy erdôn keresztül vezet, a Capong törzs rettenthetetlen földjén. Igazi jaguárok, ôk azok, oh-ey! Soha nem megyek arra a spanyol helyre. Az én népem - békés nép, nem megyünk Capong földjére. Kumwana nem tud neked tanácsot adni. Az út túl veszélyes.";
			link.l1 = "De a spanyolok találtak egy utat oda! És én nem félek azoktól a Capongoktól...";
			link.l1.go = "cumvana_no_1";
		break;
		
		case "cumvana_no_1":
			dialog.text = "De neked kellene. Kegyetlen emberek. Sok emberemet megölték az erdôben. Kumwana mindent elmondott.";
			link.l1 = "Hát, a francba...";
			link.l1.go = "cumvana_no_2";
		break;
		
		case "cumvana_no_2":
			DialogExit();
			AddQuestRecord("Roger_5", "5");
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_1":
			dialog.text = "Oh-ey! Már megint te, a tenger fia. Mit akarsz mondani Kumwanának?";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0 || CheckCharacterItem(pchar, "compass1") || GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l1 = "Ajándékot hoztam neked, fônök. Nézd meg, tetszeni fog neked.";
				link.l1.go = "cumvana_2";
			}
			else 
			{
				link.l1 = "A remény, hogy megtalálom Meridát, még mindig velem van...";
				link.l1.go = "cumvana_1_1";
			}
		break;
		
		case "cumvana_1_1":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_1";
		break;
		
		case "cumvana_2":
			dialog.text = "Locono mindig örül, ha jó barátokat lát.";
			if (GetCharacterFreeItem(pchar, "pistol5") > 0)
			{
				link.l1 = "Ajándékozz egy pisztolyt."; // 5
				link.l1.go = "cumvana_2_1";
			}
			if (CheckCharacterItem(pchar, "compass1")) // 3
			{
				link.l2 = "Ajándékozz egy iránytût.";
				link.l2.go = "cumvana_2_2";
			}
			if (GetCharacterFreeItem(pchar, "spyglass1") > 0)
			{
				link.l3 = "Ajándékozz egy olcsó kémszemüveget.";
				link.l3.go = "cumvana_2_3";
			}
			if (GetCharacterFreeItem(pchar, "spyglass2") > 0)
			{
				link.l4 = "Ajándékozz egy közönséges kémszemüveget."; // 2
				link.l4.go = "cumvana_2_4";
			}
			if (GetCharacterFreeItem(pchar, "spyglass3") > 0)
			{
				link.l5 = "Ajándékozz egy tisztességes kémszemüveget."; // 4
				link.l5.go = "cumvana_2_5";
			}
		break;
		
		case "cumvana_2_1":
			Log_Info("Kaptál egy pisztolyt");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "pistol5", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_3");
			dialog.text = "Oh-ey! Milyen szép sápadtarcú fegyver! Kumwana elfogadja az ajándékodat! Te is, tenger fia, fogadj el egy ajándékot Kumwanától és Locono népétôl.";
			link.l1 = "Köszönöm, fônök!";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_2":
			Log_Info("Kaptál egy iránytût.");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "compass1", 1);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Sápadtarcúak varázslatos amulettje! Kumwana elfogadja az ajándékodat! Te is, tenger fia, fogadd el Kumwana és Locono népének ajándékát.";
			link.l1 = "Köszönöm, fônök!";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_3":
			Log_Info("Adtál egy olcsó kémszemüveget.");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass1", 1);
			GiveItem2Character(pchar, "obereg_2");
			GiveItem2Character(pchar, "indian_5");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Sápadtarcúak varázscsöve! Kumwana elfogadja az ajándékodat! Te is, tenger fia, fogadd el Kumwana és Locono népének ajándékát.";
			link.l1 = "Köszönöm, fônök!";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_4":
			Log_Info("Adtál egy közönséges kémszemüveget.");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass2", 1);
			GiveItem2Character(pchar, "obereg_6");
			GiveItem2Character(pchar, "indian_6");
			GiveItem2Character(pchar, "obereg_1");
			dialog.text = "Oh-ey! Sápadtarcúak varázscsöve! Kumwana elfogadja az ajándékodat! Te is, tenger fia, fogadd el Kumwana és Locono népének ajándékát.";
			link.l1 = "Köszönöm, fônök!";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_2_5":
			Log_Info("Adtál egy tisztességes kémszemüveget.");
			//Log_Info("You have received amulets");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "spyglass3", 1);
			GiveItem2Character(pchar, "obereg_9");
			GiveItem2Character(pchar, "indian_7");
			GiveItem2Character(pchar, "obereg_5");
			dialog.text = "Oh-ey! Sápadtarcúak varázscsöve! Kumwana elfogadja az ajándékodat! Te is, tenger fia, fogadd el Kumwana és Locono népének ajándékát.";
			link.l1 = "Köszönöm, fônök!";
			link.l1.go = "cumvana_3";
		break;
		
		case "cumvana_3":
			dialog.text = "Mi szél hozott a falunkba, tenger fia?";
			link.l1 = "Fônök, azért jöttem, hogy a segítségedet kérjem. El akarok jutni egy Merida nevû spanyol településre, ami a hegyek között található a ti szelvátokban, a probléma az, hogy nem tudom, hogyan jutok oda. Talán tudnál adni nekem egy bátor harcost, aki megmutatná az utat oda?";
			link.l1.go = "cumvana_4";
		break;
		
		case "cumvana_4":
			dialog.text = "Oh-ey! Veszélyes út, veszélyes. Az odavezetô út egy erdôn keresztül vezet, a Capongok rettenthetetlen törzsének földjén. Igazi jaguárok, ôk azok, oh-ey! Soha nem megyek arra a spanyol helyre. Az én népem - békés nép, mi nem megyünk a Capong földjére.";
			link.l1 = "Nekem tényleg el kell jutnom Meridába. Kumwana, kérdezd meg az embereidet, talán valaki csatlakozik az egységemhez? A harcosaim tapasztaltak, jól felfegyverzettek és nem félnek semmitôl, még az ördögtôl sem. Megvédjük a vezetôt, és bôkezûen megjutalmazzuk, ha vége.";
			link.l1.go = "cumvana_5";
		break;
		
		case "cumvana_5":
			dialog.text = "Rendben van, tenger fia. Összeállítok egy harcosokból álló kört, és elmondom nekik a kívánságodat. Találkozzunk holnap hajnal után.";
			link.l1 = "Köszönöm, fônök!";
			link.l1.go = "cumvana_6";
		break;
		
		case "cumvana_6":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_SetStayType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			//AddQuestRecord("Roger_5", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			SetLaunchFrameFormParam("Másnap...", "Mtraxx_MeridaVozhdDialog", 0, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0);
			RecalculateJumpTable();
		break;
		
		case "cumvana_7":
			dialog.text = "Oh-ey! Már megint te, a tenger fia. Mit akarsz mondani Kumwanának?";
			link.l1 = "Még semmi, fônök.";
			link.l1.go = "cumvana_7x";
			if(CheckAttribute(pchar,"questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "merida_hayamee")
			{
				link.l2 = " Figyelj, Kumwana. Az embereimnek és nekem át kell kelnünk a folyón, hogy elérjük azt az átkozott kis várost. Hadd magyarázzam el, mennyire fontos ez nekünk.";
				link.l2.go = "cumvana_hard";
			}
		break;
		
		case "cumvana_hard":
			dialog.text = "A vadászaim már tájékoztattak téged, hogy...";
			link.l1 = "Nem kell kétszer elismételned magad, Kumwana. De nézz ki - és ne becsüld túl a képességeidet. A bátor fiaim, akik a spanyol kövekért jöttek ide, szétszóródtak a faludban. És a türelmük kezd elfogyni. És hogy mi fog történni, amikor végre elfogy, jobb, ha nem tudod - hidd el nekem.";
			link.l1.go = "cumvana_medium_1";
			link.l2 = "Fogd be a szád és figyelj, vörösbôrû majom. Az én népem sokkal szörnyûbb tud lenni, mint ezek az átkozott kapongok. Ne tévesszen meg az, hogy mi most olyan kedvesek vagyunk. Egyszerû választást adok nektek: vagy huszonnégy órán belül találsz egy vezetôt, vagy mindannyiótokat megkötözünk, és a csapatunk elôtt küldünk át a dzsungelen. Ha rossz irányba vezetsz minket, te magad is elpusztulsz a mocsárban, vagy megkötözve harcolsz a kapongokkal. Megértettétek?";
			link.l2.go = "cumvana_hard_1";
			link.l3 = "Kumwana, szükségem van erre a vezetôre. Hosszú utat tettünk meg, és igazán nem akarom azt mondani az embereimnek, hogy hiába.";
			link.l3.go = "cumvana_good_1";
			pchar.questTemp.Mtraxx_MeridaZapugivanieIndeets = true;
		break;
		
		case "cumvana_good_1":
			dialog.text = "Kumwana már mondja, egyik Lokono sem akar a sápadtarcúval menni.";
			link.l1 = "És te nem tudsz tenni ellene semmit? Kérdezz meg valakit személyesen. Elvégre rend van. Te vagy a fônök, vagy nem?";
			link.l1.go = "cumvana_good_2";
		break;
		
		case "cumvana_good_2":
			dialog.text = "A fônök nem kényszeríti az indiánt. A fônök uralkodik és békét akar a népének. Az indiánok tudják - a Kapong látni fogja, hogy a Lokono hozza a sápadtarcúakat. A fejüket a Kanaima foglyul ejti. Azért jönnek, hogy bosszút álljanak a Lokonon. Kapong - megölni. Elfogni a Lokono-kat, rabszolgákká tenni ôket.";
			link.l1 = "És ki fogta el a fejeteket? Milyen szellem vagy démon teszi az indiánokat ilyen gyáva férgeket? Nos, talán tényleg fel kell hagynom a Merida elleni hadjárattal. De valamit ne feledj, fônök. Amikor megkérdezik tôlem, mit tudok a lokonókról, mindig azt válaszolom, hogy értéktelen gyávák törzse. Egy olyan gyáva és rövidlátó uralkodó vezeti ôket, mint ôk maguk, akinek arcát a rémület grimasza torzítja el a Kapongok puszta emlékétôl. Nem fogsz dicsôséget szerezni az indiánok között, sem tiszteletet köztünk, sápadtarcúak között.";
			link.l1.go = "cumvana_good_3";
		break;
		
		case "cumvana_good_3":
			dialog.text = "A sápadtarcúak nem ismerik az indiánok szokásait...";
			link.l1 = "Eleget tudok ahhoz, hogy tudjam, kit neveznek az indiánok gyávának, és kit bátor harcosnak. Isten veled, Kumwana. És emlékezz a szavaimra. Gyáva és rövidlátó uralkodó vagy.";
			link.l1.go = "cumvana_good_4";
		break;
		
		case "cumvana_good_4":
			DialogExit();
			ChangeIndianRelation(5.00);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			pchar.questTemp.Mtraxx = "fail";
			
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeGoodDialog.function = "Mtraxx_MeridaHayameeGoodDialog";
		break;
		
		case "cumvana_medium_1":
			dialog.text = "Miért fenyegetsz így? Azt hisszük, hogy jó vagy...";
			link.l1 = "Jó vagyok, amíg együttmûködsz, érted? Egy napotok van. És bízz bennem, az embereim megtesznek mindent, amit parancsolok. Erôsebbek vagyunk. És ha kételkedsz benne... Láttam a feleséged. És a lányaidat. Azt hiszem, most már érti az üzenetet.";
			link.l1.go = "cumvana_hard_2";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "cumvana_hard_1":
			dialog.text = "Miért fenyegetsz így? Azt hisszük, hogy jó vagy...";
			link.l1 = "Jó vagyok, amíg együttmûködsz, érted? Egy napotok van. És bízz bennem, az embereim megtesznek mindent, amit parancsolok. Erôsebbek vagyunk. És ha kételkedsz benne... Láttam a feleséged. És a lányaidat. Azt hiszem, most már érti az üzenetet.";
			link.l1.go = "cumvana_hard_2";
		break;
		
		case "cumvana_hard_2":
			dialog.text = "Kumwana megérti, sápadt arccal. A faluban van egy Tagofa nevû vadász. Talán ô el tud téged vezetni a településre...";
			link.l1 = "Huszonnégy óra múlva visszatérek. Charlie hercegnek nincs több hozzáfûznivalója, vadember.";
			link.l1.go = "cumvana_hard_3";
		break;
		
		case "cumvana_hard_3":
			DialogExit();
			ref Hayam = characterFromId("Hayamee");
			ChangeCharacterAddressGroup(Hayam, "none", "", "");
			Hayam.lifeday = 0;
			pchar.questTemp.Mtraxx = "merida_hayamee_hard";
			npchar.dialog.currentnode = "cumvana_7";
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeHardTagofaWait", 0, 0, 1, false);
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Women")) DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			ChangeCharacterComplexReputation(pchar, "nobility", -80);
			ChangeOfficersLoyality("bad", 5);
			ChangeIndianRelation(-50.0);
			//log_Info("The attitude of the Indians has decreased");
			AddQuestRecord("Roger_5", "8a");
			pchar.GenQuest.CannotWait = true; //запретить отдыхать
			
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1 = "location";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.win_condition.l1.location = "Locono_village";
			pchar.quest.Mtraxx_MeridaHayameeHardLepriconDialog.function = "Mtraxx_MeridaHayameeHardLepriconDialog";
		break;
		
		case "cumvana_7x":
			DialogExit();
			npchar.dialog.currentnode = "cumvana_7";
		break;
		
		case "cumvana_8":
			dialog.text = "A tenger fia, te vagy az. Kumwana a Locono harcosaival beszélgetett.";
			link.l1 = "És? Van önkéntesed?";
			link.l1.go = "cumvana_9";
		break;
		
		case "cumvana_9":
			dialog.text = "Van itt néhány vadász, aki már járt ott. De félnek Capongéktól, a jaguárok hadiösvényen vannak. Nem mennek, mert azt mondják, hogy a Capongok megölik a csapatodat. Nem félnek a sápadtarcúaktól.";
			link.l1 = "Az én harcosaim sokkal jobbak, mint bármelyikük! Az egységem egy része egy életet töltött a dzsungelben! Nem vagyunk amatôrök!";
			link.l1.go = "cumvana_10";
		break;
		
		case "cumvana_10":
			dialog.text = "Sajnálom, tenger fia. A vadászom fél, a capongok veszélyesek, nagyon is veszélyesek.";
			link.l1 = "Rendben, akkor talán meg tudják magyarázni, hogyan jutunk oda? A részleteket.";
			link.l1.go = "cumvana_11";
		break;
		
		case "cumvana_11":
			dialog.text = "Ahhoz, hogy odaérjetek, a folyón kell hajózni, majd egy különleges helyen kiszállni. Ha rossz helyre mész, akkor a mocsárba kerülsz és meghalsz. A mi szelvánk tele van veszélyekkel. Egyedül nem fogod megtalálni a helyet, a tenger fia.";
			link.l1 = RandSwear()+"És akkor mit tegyek? Hogyan gyôzzem meg a vadászokat?";
			link.l1.go = "cumvana_12";
		break;
		
		case "cumvana_12":
			dialog.text = "Kumwana nem mond többet, tenger fia.";
			link.l1 = "Rendben...";
			link.l1.go = "cumvana_13";
		break;
		
		case "cumvana_13":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			npchar.dialog.currentnode = "cumvana_7";
			AddQuestRecord("Roger_5", "7");
			pchar.questTemp.Mtraxx = "merida_advice";
			LAi_SetHuberType(npchar);
			AddLandQuestMark(characterFromId("Lepricon"), "questmarkmain");
		break;
		
		// Хайами
		case "hayamee":
			if (npchar.id == "Hayamee")
			{
				dialog.text = "A férjem Tagofa a törzs legjobb vadásza. Oh-ey! "+npchar.name+" büszke a férjére. "+npchar.name+" gyakran jár Tagofával Szelvába. Messzire megy. Tagofa tudja, hol van a spanyol település.";
				if (IsCharacterPerkOn(pchar, "Trustworthy") && stf(pchar.questTemp.Indian.relation) >= 40.0)
				{
					link.l1 = "Tagofa tudja az utat a spanyol városba, amit a sápadtarcúak Meridának hívnak?";
					link.l1.go = "hayamee_1";
				}
				else
				{
					link.l1 = "Nocsak, nocsak... Tudja Tagofa, hogyan lehet eljutni a spanyol városba?";
					link.l1.go = "hayamee_bad_1";
				}
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("A férjem nem megy selva, fia a tenger. Ô halat fog. Jó halász, oh-ey! ","A férjem jó vadász, ó-ey, de nem megy mély dzsungelbe."), RandPhraseSimple("Jaguár megsebesítette a férjemet vadászaton. Most a faluban ül, nyilakat készít, oh-ey!","Hat holddal ezelôtt három Capong megtámadta a férjemet. Most nem megy vadászni messze a falutól. Soha!"));
				link.l1 = LinkRandPhrase("Kár...","Kár...","Milyen kár..."));
				link.l1.go = "exit";
			}
		break;
		
		case "hayamee_bad_1":
			dialog.text = "Tagofa ebben a dzsungelben nôtt fel. Ismer minden fát és követ a környéken!";
			link.l1 = "Sok ajándékot adok neked és Tagofának, ha elvisz minket oda. Ékszereket, fegyvereket, bármit. Bármit, amit csak akarsz. Természetesen ésszerûségen belül, he-he. Hogyan beszélhetnék a férjeddel?";
			link.l1.go = "hayamee_bad_2";
		break;
		
		case "hayamee_bad_2":
			dialog.text = "Tagofa nem megy a sápadtarcúval. Tagofa a faluban marad. Menjetek vadászni. Ne harcolj a Kaponggal.";
			link.l1 = "Nem kell harcolnia a Kaponggal. Amint meglátja ôket, el tud bújni. Csak az én népem fog harcolni.";
			link.l1.go = "hayamee_bad_3";
		break;
		
		case "hayamee_bad_3":
			dialog.text = "Nem, yalanaui. A sápadtarcú sosem tartja a szavát. A sápadtarcú beszél - és a szó azonnal elrepül a semmibe. A Kapong megöli Tagofát, aztán eljön a falunkba, és megöli a Lokonót.";
			link.l1 = "Azt hiszed, csak a Kapongok miatt kell aggódnod? Nagyon tévedsz...";
			link.l1.go = "hayamee_bad_4";
			if (stf(pchar.questTemp.Indian.relation) < 40.0) notification("Az indiánok nem tisztelnek téged. "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			if (!IsCharacterPerkOn(pchar, "Megbízható")) Notification_Perk(false, "Trustworthy");
		break;
		
		case "hayamee_bad_4":
			dialog.text = "Yahahu, hogy belépjen a sápadtarcú! Hayami nem beszél többé yalanaui.";
			link.l1 = "Nocsak, nocsak...";
			link.l1.go = "hayamee_bad_5";
		break;
		
		case "hayamee_bad_5":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
		break;
		case "hayamee_1":
			dialog.text = "Tagofa egy napja vadászni ment. Megígérte, hogy holnap visszajön, amikor a nap alszik. Gyere holnap a tenger fia, én Tagofával leszek abban a kunyhóban, ahogy a faluban jársz, menj jobbra. Megkérdezem tôle, hogy veled megy-e vagy sem.";
			link.l1 = "Mondd meg Tagofának, hogy megajándékozom a legszebb pisztollyal. És téged is megajándékozlak egy csomó ékszerrel.";
link.l1.go = "hayamee_1_1";
		break;
		
		case "hayamee_1_1":
			dialog.text = "Lokono nem bízik a Yalanauiban. A Yalanaui becsapja az indiánt, rabszolgává teszi az indiánt. De Lokono hallotta a neved, sápadtarcú. A bizalmam a tiéd. Gyere holnap napnyugta után, a tenger fia. Tagofával leszek abban a kunyhóban. Megkérdezem tôle, hogy veled megy-e vagy sem.";
			link.l1 = "Mondd meg Tagofának, hogy neki adom a legszebb pisztolyomat. Neked pedig sok ékszerem van.";
			link.l1.go = "hayamee_2";
			notification("Az indiánok tisztelnek téged "+stf(pchar.questTemp.Indian.relation)+"/40", "None");
			notification("Megbízható", "Trustworthy");
		break;
		
		case "hayamee_2":
			dialog.text = "Oh-ey!";
			link.l1 = "...";
			link.l1.go = "hayamee_3";
		break;
		
		case "hayamee_3":
			DialogExit();
			AddQuestRecord("Roger_5", "9");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Women");
			LAi_CharacterDisableDialog(npchar);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.hour  = 22.0;
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait1.function = "Mtraxx_MeridaHayameeTimer";
		break;
		
		case "hayamee_4":
			pchar.quest.Mtraxx_MeridaPotionLate.over = "yes";
			dialog.text = ""+npchar.name+" Örülök, hogy látom a tenger fiát. Tagofa visszajött. De túl sok kasheerit ivott és alszik. Ne ébresszétek fel, Tagofa pihen. Majd én beszélek.";
			link.l1 = "Nagyon jól, "+npchar.name+". A férje elkísér minket Meridába?";
			link.l1.go = "hayamee_5";
		break;
		
		case "hayamee_5":
			dialog.text = "Tagofa beleegyezett, hogy átvezeti a harcosaitokat a szelván keresztül a spanyol faluba. De vannak feltételek...";
			link.l1 = "Melyek?";
			link.l1.go = "hayamee_6";
		break;
		
		case "hayamee_6":
			dialog.text = "Megvéded Tagofát a Capong harcosoktól. Tagofa nem harcol spanyolok ellen, nem harcol Capong ellen. Ha veszélybe kerül, elmenekül, és senki sem találja meg, ô a legjobb Locono vadász.";
			link.l1 = "Értem, értem. Aggódsz az emberedért, ez érthetô. Ígérem, hogy mi magunk fogunk elbánni azokkal a Capongokkal.";
			link.l1.go = "hayamee_7";
		break;
		
		case "hayamee_7":
			dialog.text = "Oh-ey! Tagofa ajándékot kér a tenger fiától: egy kisebbet, hogy sok követ lôjön, és egy nagyobbat, hogy egy követ lôjön, a szépeket. Továbbá töltényeket akar minden puskához: annyit, amennyit mindkét keze háromszor ujjaz.";
			link.l1 = "Hûha! Az embere ért valamit a fegyverekhez, mi? Nagyon jól. Mi van még?";
			link.l1.go = "hayamee_8";
		break;
		
		case "hayamee_8":
			dialog.text = "És Tagofa akar egy szép varázsszemet a sápadtarcúaknak.";
			link.l1 = "Egy kémszemüveget? Az jó lesz. Még valamit?";
			link.l1.go = "hayamee_9";
		break;
		
		case "hayamee_9":
			dialog.text = "Tagofa számára nincs többé. "+npchar.name+" szép dolgokat akar. Aranygyûrû nagy piros kôvel, és gyöngyök sok sok zöld kôvel. "+npchar.name+" láttam Fehér Márián Maracaibóban.";
			link.l1 = "Egy aranygyûrû rubinnal és jáde gyöngyökkel?";
			link.l1.go = "hayamee_10";
		break;
		
		case "hayamee_10":
			dialog.text = "Nem jáde. Fényes, és a fehér emberek értékelik.";
			link.l1 = "Smaragd? Smaragdgyöngyök?";
			link.l1.go = "hayamee_11";
		break;
		
		case "hayamee_11":
			dialog.text = "Oh-ey!";
			link.l1 = "Heh, "+npchar.name+" tud valamit az ékszerekrôl! Nagyon jó, meg fogod kapni.";
			link.l1.go = "hayamee_12";
		break;
		
		case "hayamee_12":
			dialog.text = "Hozz össze mindent a "+npchar.name+" , a tenger fia. Akkor Tagofa vezetni fog téged és a harcosaidat. Ne vesztegesd az idôt, fél holdon belül Tagofa és én a szomszéd faluba megyünk. Egy nagy napra. Most menj, "+npchar.name+" aludni akar.";
			link.l1 = "Nem akarom, hogy túl sokáig várjatok. Viszlát.";
			link.l1.go = "hayamee_13";
		break;
		
		case "hayamee_13":
			DialogExit();
			AddQuestRecord("Roger_5", "10");
			LAi_CharacterDisableDialog(npchar);
			SetFunctionTimerCondition("Mtraxx_MeridaHayameeLate", 0, 0, 15, false); // таймер
			// Тагофу в сидячее положение
			pchar.quest.mtraxx_merida_wait2.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.hour  = 9.0;
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_merida_wait2.function = "Mtraxx_MeridaTagofaHide";
		break;
		
		case "hayamee_14":
			bOk = GetCharacterFreeItem(pchar, "spyglass1") > 0 || GetCharacterFreeItem(pchar, "spyglass2") > 0 || GetCharacterFreeItem(pchar, "spyglass3") > 0;
			dialog.text = "Elhoztad, amit "+npchar.name+" és Tagofa kért?";
			if (bOk && GetCharacterFreeItem(pchar, "pistol3") > 0 && GetCharacterFreeItem(pchar, "pistol5") > 0 && GetCharacterItem(pchar, "bullet") >= 30 && GetCharacterItem(pchar, "grapeshot") >= 30 && GetCharacterItem(pchar, "gunpowder") >= 60 && CheckCharacterItem(pchar, "jewelry41") && CheckCharacterItem(pchar, "jewelry42"))
			{
				link.l1 = "Igen. Minden a listád szerint van.";
				link.l1.go = "hayamee_15";
			}
			else
			{
				link.l1 = "Nem, még mindig rajta vagyok.";
				link.l1.go = "hayamee_14x";
			}
		break;
		
		case "hayamee_14x":
			DialogExit();
			npchar.dialog.currentnode = "hayamee_14";
		break;
		
		case "hayamee_15":
			pchar.quest.Mtraxx_MeridaHayameeLate.over = "yes";
			Mtraxx_MeridaRemoveGifts();
			dialog.text = ""+npchar.name+" boldog, a tenger fia. Mostantól férjnek hívlak. Veled megy. De ne feledd, mit ígértél a "+npchar.name+"!";
			link.l1 = "Igen, igen, emlékszem mindenre. Vigyázni fogok rá, ne aggódj.";
			link.l1.go = "hayamee_16";
		break;
		
		case "hayamee_16":
			DialogExit();
			pchar.questTemp.Mtraxx = "merida_hayamee_peace";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 7.0);
			DoQuestFunctionDelay("Mtraxx_MeridaTagofaEnter", 20.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
			
		case "CitizenNotBlade":
			dialog.text = "Tedd el a fegyvered, sápadtarcú, vagy kényszeríteni fogunk rá!";
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ne aggódj, elrakom...");
			link.l1.go = "exit";
		break;  

	}
}
