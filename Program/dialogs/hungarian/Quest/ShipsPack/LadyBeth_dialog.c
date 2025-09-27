void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "A döntése, kapitány? Talán nem kellene?";
				link.l1 = "Sikerült több önkéntest összegyûjteni a feladatra?";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "Kapitány, egy szóra.";
				link.l1 = "Jelentést, Alonso.";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "A legénység kíváncsi, hogy mik a tervei a Kajmán-szigetekkel kapcsolatban. Az emberek aggódnak.";
			link.l1 = "Még nem döntöttem. És miért aggódnak az emberek, Alonso?";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "Ez a sziget Blackwood kapitány birtoka. A tengerészek szerint úgy ássa fel, mint egy megszállott, hosszában és szélességében. Hogy több tucat embert tett tönkre az ásatásai során... És azok, akik elhagyják ôt... furcsa történeteket mesélnek.";
			link.l1 = "Miféle meséket?";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "Hogy Blackwood már nem az az ember, aki volt. Hogy megszállottan keresi a hódítók kincseit. Hogy kész mindent és mindenkit feláldozni érte. Tudjuk, mennyire szeretsz szép történetekbe keveredni, egyedül landolni és csapdákba esni... Nos, ebbôl nem fogsz kijutni.";
			link.l1 = "Köszönöm a beszámolót és a figyelmeztetést. Ha úgy döntök, hogy leszállok, mindenképpen magammal viszem az elôôrsöt és a legjobb harcosaink egy részét.";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "Ez nehéz lehet, kapitány. A fedélzetre lépés egy dolog, de partra szállni tengerészgyalogosok golyói és a csôcselék szablyái alatt, akiket Blackwood állítólag a Kis-Antillák minden lyukából felbérelt, egészen más. És rossz pletykák keringenek a Kajmán-szigetekrôl... Nem, nem sok önkéntest fog találni ilyen munkára.";
			link.l1 = "Akkor azzal kell beérnünk, akivel csak tudunk. A részvétele kötelezô, Alonso.";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "Véleményem szerint már mindenkinek bebizonyítottam mindent, amit be lehetett bizonyítani. Minden jó harcos és lövész megy. Ez parancs.";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "Hmm... Nos, át kell gondolnom az egészet. Talán késôbb visszatérünk erre a kérdésre.";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "Mi a helyzet Blackwood hajójával? Nem okozhat gondot?";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50 || sti(pchar.rank) >= 17)
			{
				dialog.text = "Igenis, kapitány!";
				link.l1 = "Mi a helyzet Blackwood hajójával? Nem okozhat gondot?";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50) notification("Képességellenôrzés megfelelt", SKILL_Leadership);
				if (sti(pchar.rank) >= 17) notification("Szintellenôrzés megfelelt", "None");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "Attól tartok, még nem, kapitány.";
				}
				else
				{
					dialog.text = "Sem nekem, sem a tisztjeinek nem kell bizonyítania semmit, és a parancs szerint oda megyünk, ahová ön mondja, de az egyszerû tengerész másképp gondolkodik. Attól tartok, lesznek problémák, kapitány.";
				}
				link.l1 = "Akkor azzal kell beérnünk, akivel csak tudunk. A részvétele kötelezô, Alonso.";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "Hmm... Nos, át kell gondolnom az egészet. Talán késôbb visszatérünk erre a kérdésre.";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_Leadership) < 50) notification("Képességpróba Sikertelen (50)", SKILL_Leadership);
				if (sti(pchar.rank) < 17) notification("17. szint szükséges", "None");
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "Egy hó. Azt mondják, egy igazi szépség, heves temperamentummal. Én nem aggódnék miatta. Valószínûleg az egész legénység a szárazföldön szorgoskodik, míg a hajó biztonságban van a partvidék redôiben. Ha és amennyiben gyôzünk, akkor a partról elvihetjük zsákmányként.";
			link.l1 = "Gyûjtsd össze az embereket. Ma jó nap van - a szerencse a mi oldalunkon áll.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "Örülök, hogy látlak, kapitány. Azt hiszem, már mindent megbeszéltünk...";
				link.l1 = "Valóban. Viszontlátásra.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", "+npchar.name+"";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", Blackwood kapitány.";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "Üdvözlöm. Ön Blackwood kapitány?";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+". Ön Albert Blackwood kapitány, igaz?";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "Örülök, hogy látom, kapitány. Azt hiszem, már mindent megbeszéltünk.";
			link.l1 = "Valóban. Viszontlátásra.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "Igen, én vagyok. És ön?";
			link.l1 = "Kapitány "+GetFullName(pchar)+". Én vagyok a hajó parancsnoka '" + PChar.Ship.Name + "'.";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "Kapitány... Járt már a Kajmán-szigeteken?";
			link.l1 = "Csak arra jártam.";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "Hallottál valamit az ottani kincsekrôl?";
			link.l1 = "Nem, semmi különöset.";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "Spanyolok nyomai? Régi fegyverek? Érmék a konkvisztádorok idejébôl?";
			link.l1 = "Semmi ilyesmit nem találtam.";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "Helyi legendák? Történetek Cortezrôl? Valami temetkezésekrôl?";
			link.l1 = "Sajnálom, kapitány, de nincs ilyen információm. És ez már kezd olyan lenni, mint egy kihallgatás.";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "Elnézést kérek... Egy volt tiszt rossz szokása. Csak... ez rendkívül fontos számomra.";
			link.l1 = "Miért érdekli ennyire a Kajmán-szigetek?";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "Nem fontos. Még egyszer, elnézést kérek.";
			link.l1 = "Megértem. Sok szerencsét a kereséshez.";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Jó éjszakát!";
			else sStr = "Szép napot kívánok";
			dialog.text = "Gyere el hozzám, ha találsz valami érdemlegeset. Szívesen beszélgetnék egy másik kapitánnyal... olyannal, aki ért a tengerhez. " + sStr + ".";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "Személyesen. És ön... Helen MacArthur kapitány? Jan Svenson pártfogoltja, igaz? Hallottam magáról.";
			link.l1 = "Ön jól informált, Blackwood kapitány. De nem lep meg, hogy egy angol tiszt tud rólam.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "Volt tiszt. És az összes vörös kabátos tud magáról és az ön... egyedi preferenciáiról a koronától. A vasfa, ahogy mondják, nem büdös. És a történet, hogy az apja, Sean MacArthur gyerekkora óta a tengerre vitte, és kapitányt csinált magából, afféle legendává vált a flottában.";
			link.l1 = "És milyen érzés találkozni ezzel a legendával?";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "Engem személy szerint lenyûgözött. Bár sok volt kollégám, be kell vallanom, eléggé irritálónak találja. De ahhoz, hogy valaki kapitány legyen, több kell, mint nemesi születés vagy királyi szabadalom, nem igaz?";
			link.l1 = "Ez igaz. Tudás, tapasztalat és állandó készség kell hozzá, hogy bizonyítsd a rátermettségedet. Különösen az én esetemben.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "Pontosan! A tengeren, mint az életben, nem a címek számítanak, hanem az eredmények. Örülök, hogy megismerhetem, MacArthur kapitány. Remélem, még találkozunk. Talán beugrik egy pohár borra, amikor visszatérek az expedíciómról?";
			link.l1 = "Talán. Sok szerencsét a kereséshez, kapitány.";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "Nem érdekel. De sok szerencsét a kereséshez, kapitány.";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "Ah, Kapitány "+pchar.lastname+"! Örülök, hogy látlak. Szeretne leülni?";
			link.l1 = "Örömmel.";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "Kapitány... mondja, mit jelentenek önnek az igazi kincsek?";
			link.l1 = "Az igazi kincs a szerelem. A megfelelô ember az ember mellett. Nincs rosszabb, mint egyedül lenni.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "A pénz, természetesen. Mi más lehetne kincs?";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "Értékes és egyedi felszerelés. Egy jó kard vagy pisztoly többet ér, mint az arany.";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "A tudás. A legértékesebb kincs az, ami a fejedben van.";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "Szerelmem? Hmm... Nem számítottam ilyen válaszra egy kalóz lányától. I... El voltam jegyezve. Elizabeth-tel. Egy barbadosi ültetvényes lányával. De az apja... úgy döntött, hogy nincs elég pénzem. Mit tudnék felajánlani a lányának a szerelmemen kívül? Szerencséje volt, MacArthur kapitány. Az apja jobban értékelte a képességeit, mint a hozományát.";
				link.l1 = "Talán nem a szerencsérôl van szó, hanem arról, hogy az igaz szerelmet nem aranyban mérik. Az apám megértette ezt. És mi van a menyasszonyával? Ô is osztja az apja nézeteit?";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "A szerelmet? Igen... Talán igaza van. I... El voltam jegyezve. Barbadoson. Szerettük egymást, de... az apja nem tartott méltó párnak. Ha! Nem elég gazdag. Ezért vagyok itt - kincseket keresek, hogy bebizonyítsam, tévedtek. Talán hiába?";
				link.l1 = "Talán csak beszélned kellene vele? A pokolba azzal az ültetvénytulajdonossal.";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "Beszélj... Igen, talán. De mit mondanék? 'Szomorú, nem tudtam tisztességes életet biztosítani neked'? Nem. Vissza kell adnom egy gyôztest. Vagy egyáltalán nem kell visszatérned.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "Elizabeth? Nem... ô szeret engem. De én... Nem hagyhatom, hogy szegénységben éljen. Jobbat érdemel. És be kell bizonyítanom, hogy méltó vagyok rá.";
			link.l1 = "Néha a büszkeség jobban akadályozza a boldogságot, mint a szegénység, kapitány.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "Nem térhetek vissza üres kézzel. Egyszerûen nem tehetem. Elnézést kérek, rengeteg munkám van. Örülök, hogy elbeszélgettünk, MacArthur kapitány.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "Milyen banális válasz. De nehéz vitatkozni vele. Valóban, ha az ember Bristol nyomornegyedében nôtt fel, amikor a morzsákért kellett küzdenie... akkor kezdi megérteni a pénz valódi értékét. Ez nem luxus. Hanem szabadság. A képesség, hogy soha többé nem térhetsz vissza abba a mocsokba, ahonnan oly nehezen másztál ki.";
			link.l1 = "Egyetértek. A pénz megoldja a legtöbb problémát. És ha nem oldja meg ôket - az azt jelenti, hogy egyszerûen nincs belôle elég.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "Pontosan! Megérted. A pénz nem tesz boldoggá, de a hiánya biztosan boldogtalanná tesz. Én ezt túl jól tudom...";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "Érdekes. Praktikus. Van egy arquebusom... egy igazi, a hódítók idejébôl. Egy bizonyos pap ajándéka. Néha azt hiszem, többet ér, mint az összes arany, amit találtam. De... ez nem oldja meg a problémáimat.";
			link.l1 = "A jó fegyverek sok problémát megoldhatnak. És soha nem fognak elárulni.";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "Ebben van igazság. De néhány csatát nem lehet fegyverrel megnyerni.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "A tudás... Igen, értem. Mindent tanulmányoztam, amit csak tudtam a hódítókról, a kincsekrôl. Összeállítottam egy egész kézikönyvet a kincsvadászatról. Kialakítottam egy rendszeres gyakorlatok és anyagi ösztönzôk rendszerét a hajó lövész századának. Bármelyik kapitány szívesen megkapná a kézikönyvemet. De ez a sok tudás... Hiábavaló, ha nem vezet eredményre. Valódi eredményekhez.";
			link.l1 = "De a tudás az, ami segít az eredmények elérésében. Enélkül minden keresés csak bolyongás a sötétben.";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Nos, már késôre jár, és rengeteg munkám van.";
			else sStr = "Nos, sok dolgom van.";
			dialog.text = "" + sStr + ". Köszönöm a beszélgetést, kapitány. Igazán érdekes volt.";
			link.l1 = "Neked is köszönöm. "+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "Ah, "+pchar.name+"! Örülök, hogy látlak. Kiváló hírem van - végre találtam megoldást a problémáimra. Hamarosan expedícióra indulok, és ezúttal igazi kincsekkel térek vissza! Egyébként egy baráti tanács - maradj távol a Kajmántól. Az már az én területem.";
			link.l1 = "Kajmán-szigetek nem tartozik hozzád, Albert. Nincsenek koronajogaid hozzá. Ez kalózkodás.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "Fenyeget engem, Blackwood?";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "Koronás jogok? Bristol nyomornegyedében kellett volna élnie, "+pchar.name+", akkor megértené, mit érnek ezek a papírok. Ha éhes vagy, a törvények értelmetlenek. Azonban... igazad van. Hivatalosan nincs jogom a szigethez. De megtaláltam ott azt, amit évek óta keresek. És nem hagyom, hogy bárki elvegye tôlem.";
			link.l1 = "Remélem, megérti, hogy veszélyes úton jár.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "Mindig is tudtam, hogy az utam nem lesz könnyû. Isten veled, "+pchar.name+". Talán még találkozunk.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "Fenyegetô? Nem, egyáltalán nem. Csak egy baráti tanács egyik kapitánytól a másiknak. A Kajmán-szigetek veszélyes... különösen azok számára, akik beleavatkoznak az ügyeimbe.";
			link.l1 = "Emlékezni fogok a 'tanácsaidra'. Sok sikert a Kajmán-szigeteken.";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "És sok szerencsét magának, kapitány. Remélem, nem lesz rá szüksége. Viszontlátásra.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Maga?! Azt hiszed, megadom magam? Azt hiszed, hogy visszatérek a szegénységbe? Inkább meghalok, minthogy újra a nyomornegyedben éhezzek! Nincs kegyelem, nincs jutalom, nincs gyôzelem! Az ágy alatt egy puskaporos hordó van... Mindannyian az aljára kerülünk!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "Ki vagy te, hogy megtámadsz engem?! Azt hiszed, megadom magam? Nem! Inkább meghalok, minthogy újra éhen haljak a nyomornegyedben! Nincs kegyelem, nincs jutalom, nincs gyôzelem! Az ágy alatt egy puskaporos hordó van... Mindannyian az aljára kerülünk!";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "Kapitány! Figyelmeztettelek. Most megfizetsz a kíváncsiságodért.";
			}
			else
			{
				dialog.text = "Ki vagy te, és hogy merészelsz behatolni a területemre?! Ez a sziget az enyém!";
			}
			link.l1 = "Majd meglátjuk, Blackwood. Ma egy megszállottal kevesebb lesz a világon.";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "Oldjuk meg ezt békésen, Blackwood. Elmehetek.";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "Blackwood, maga egy értelmes ember! Maga egy tiszt! A királyi zászló lobog a táborod felett, az Isten szerelmére! Nem tudnánk megegyezni?";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "Megszállott? Megszállott? Én csak egy ember vagyok, aki tudja, mit akar!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "Elmegyünk? Azok után, amit láttál? Nem, nem, nem, nem! Senkinek sem szabad tudnia arról, amit itt találtam. Senkinek!";
			link.l1 = "A szavamat adom, hogy nem mondom el senkinek. A kapitány becsületére esküszöm.";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "Nincs becsület ebben a világban, kapitány. Csak mocsok, szegénység és megvetés van. Sajnálom, de itt kell meghalnod.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "Gondoltam. Sokat gondolkodtam. És rájöttem - ez az egyetlen esélyem. Vagy megtalálom Cortez aranyát, vagy... semmi. Megértetted? SEMMI! Nem fogok visszatérni a korábbi életemhez! Nem térek vissza a mocsokba és a szegénységbe! Jobb itt meghalni!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "A csatára! Bullock, Fraser - lôjetek, ha közelednek! Hopkins, támadás!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "Jól vagy?";
			link.l1 = "Igen, minden rendben. És te?";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "Élve. De ezek a szárazföldi csaták nem nekem valók. Adjatok egy fedélzetet a lábam alá, és szétszedem bármelyik hajót, de itt... furcsa hely. Száz tengeri farkast partra vinni, csákányokat lóbálni, erôdítményeket építeni... Ezt nem tudnám megtenni.";
			link.l1 = "Blackwood tudta, hogyan kell lelkesíteni a legénységét.";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "Hallottam róla Bluefieldben. Sok angol tengerész tisztelettel beszélt róla. A flotta legjobb tisztje, ragyogó karrier... és hirtelen mindent eldobott, hogy kincsekre vadásszon.";
			link.l1 = "Mit gondol róla?";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "Úgy gondolom, hogy Blackwood példája világosan mutatja a felelôsség terhét, amit mi... Úgy értem, önöknek, az embereik elôtt. Kérem, ne váljon olyan kapitánnyá, mint amilyen ô lett.";
			link.l1 = " Megpróbálom, Helen.";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "Köszönöm, kapitányom. Tudom, hogy sikerülni fog.";
			link.l1 = "Úgy lesz.";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "Úgy lesz.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			ReturnOfficer_Helena();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "Charles... milyen szörnyû itt.";
			link.l1 = "Jól vagy, Mary? Úgy tartottad magad, mint egy igazi katona.";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "Nem, nem vagyok jól, rendben. Nézd ezeket az embereket! A végkimerülésig dolgoznak, éheznek, betegségekben halnak meg... És miért? Aranyért, ami talán nem is létezik.";
			link.l1 = "Blackwood azt hitte, hogy itt van.";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "Ez a vörös kabát... pontosan olyan, mint az enyém. Egy angol tiszt... Tudja, hirtelen eszembe jutottak a szüleim. A gyökereimrôl... arról, amit sosem tudtam. Talán én is egy vagyok közülük?";
			link.l1 = "Közülük?";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "Azok, akik olyasmit keresnek, ami talán nem is létezik. És aztán elveszítik magukat a keresésben. I... Szeretnék errôl késôbb beszélni, rendben? Amikor elhagyjuk ezt a szörnyû helyet.";
			link.l1 = "Persze, Mary.";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "Elôbb temessük el ôt, kérlek? Még ha nem is érdemli meg. Annak az embernek a kedvéért, aki valaha volt.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			ReturnOfficer_Mary();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "Kapitány, Tichingitu látja a rossz helyet itt. Nagyon rossz hely.";
			link.l1 = "Hogy érti ezt?";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "Ez a sziget el van átkozva. A föld túl sok vért és könnyet szívott magába. Mindenki, aki itt ás, belélegzi ezt az átkot.";
			link.l1 = "Gondolod, hogy Blackwoodot megszállták?";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "Nem csak megszállták. Ô egy... hogy is mondjam... üres edény volt. Valami behatolt belé, és kiszorította a lelkét. Láttam már ilyet. Amikor a törzsem sámánja emberáldozatot hozott a szellemeknek. Az a sámán ugyanúgy nézett ki.";
			link.l1 = "De mi okozhat ilyen megszállottságot?";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "Az ürességgel teli embert könnyû kitölteni más gondolatokkal. Valaki megtalálja a gyenge pontját és kihasználja. Tichingitu szinte sajnálja ezt az embert.";
			link.l1 = "Majdnem?";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "Igen, majdnem. Minden harcos felelôs a saját döntéséért. Még akkor is, ha démonok suttognak a fülébe.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			ReturnOfficer_Tichingitu();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "A fenébe, kapitány! Ezt nézd meg! Mint a régi szép idôkben!";
			link.l1 = "Tudod jól, milyen a szárazföldi háború.";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "A nasebyi csatára emlékeztet. A mi lovassági szárnyunk összecsapott Rupert lovassági embereivel. Ugyanolyan vadsággal harcoltak a királyukért.";
			link.l1 = "Mit gondolsz Blackwoodról?";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "Ez a Blackwood vagy egy zseni volt, vagy egy komplett ôrült. Szerintem mindkettô. Tudod, mi lep meg? Az emberei. Sokuk volt katona. Nem valami utcai patkányok, hanem igaziak. És mindannyian követték ôt ebben az ôrületben. Még Fox tengerészgyalogosai is. Ha! Na, itt van valaki, aki örülni fog a mai vérengzésnek! Sosem bocsátotta meg nekik, hogy dezertáltak.";
			link.l1 = "Talán a pénz miatt?";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "Nem, valami másról van szó. Ennek a fickónak hatalma volt felettük. Igazi hatalma. És azt is hallottam, hogy eljegyzett egy gazdag barbadosi lányt. Furcsa, hogy nem vette feleségül, miután ennyi kincset szerzett. Tipikus katona - nem tudta, mikor kell befejezni a háborút.";
			link.l1 = "Köszönöm, Tommy. Igazi gondolkodó vagy.";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "Hm?";
			link.l1 = "Semmi.";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			ReturnOfficer_Irons();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "Milyen keserû ezt látni, kapitány. Hová süllyedtünk?";
			link.l1 = "Mi?";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "Az angol flotta! Nézd csak: apró vörös kabátos pöttyök hevernek egy halomban ezzel a halott söpredékkel!";
			link.l1 = "Ennek egy része 'scum' az embereink, Charlie. Megértem az érzéseidet, de...";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "Bassza meg, uram!";
			link.l1 = "Megértem az érzéseit, de a dühét és a csalódottságát inkább Blackwoodra irányítsa. Ô az, aki dezertált a szeretett angol flottájából, és ide vezette ôket.";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "Igen, így van. Menjünk, még nincs vége a napnak.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "Csak a parancsnokukat követték!";
			link.l1 = "Ahogy te is követted Fleetwoodot?";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "Igen, így van. Menjünk, még nincs vége a napnak.";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "Ahogy én követtelek téged!";
			link.l1 = "Remélem, jobb kapitánynak bizonyulok, mint Blackwood és Fleetwood. Gyerünk, még nincs vége a napnak.";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "Igenis, kapitány. És ha vége - addig iszom, amíg a következô véget nem ér.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			ReturnOfficer_Knippel();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "Madre de Dios, kapitány! Jól vagy?";
			link.l1 = "Azt még meglátjuk. Hány embert vesztettünk?";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			
			dialog.text = "Megölték? Ebben a vállalkozásban elvesztettük "+sti(pchar.SailorDiedInBattleInfo)+" embereinket. Nem akarok tolakodónak tûnni, kapitány, de... Figyelmeztettem!";
			link.l1 = "Nem veszem figyelembe ezt a megjegyzést, mert ma bizonyítottál, Alonso. Honnan van ennyi tehetséged?";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "Egy nap majd elmesélem magának ezt a történetet, kapitány - persze csak ha elég sokáig élünk.";
			link.l1 = "Van még valami értékes tanácsod?";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "Ha lennének itt kincsek - már rég megtalálták volna ôket. De attól még át kell kutatnunk a szigetet, és túlélôket találni, aztán eldönteni, hogy mit tegyünk velük. És nem szabad megfeledkeznünk Blackwood hajójáról sem: Csak jót hallottam arról a gyönyörû hóról. Kár lenne kihagyni egy ilyen zsákmányt, kapitány. Természetesen én csak a legénység álláspontját közvetítem ebben a kérdésben.";
			link.l1 = "Természetesen. Gyerünk, menjünk. A zsákmány vár!";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "Ne lôjenek! Megadjuk magunkat!";
			link.l1 = "Ki vagy te?";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "Mi... mi a 'Lady Beth'. Blackwood kapitány legénységéhez tartozunk. Ô... életben van?";
			link.l1 = "Nem. A kapitányuk halott.";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "Akkor mindennek vége... Hála Istennek.";
			link.l1 = "Úgy tûnik, nem gyászolja a kapitányát.";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "Nem érti. Blackwood nagyszerû ember volt. A legjobb kapitány, akit valaha ismertem. De az utóbbi hónapokban... megváltozott. Megszállottá, kegyetlenné vált. Éjjel-nappal dolgoztatott minket, hogy keressünk valamit, ami talán nem is létezik.";
			link.l1 = "Beveszlek a legénységembe. Tapasztalt tengerészekre van szükségünk.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "Jaj a legyôzötteknek, fiúk. Mostantól a helyetek az én raktáramban van. Ha szerencsétek van - megélhetitek a barbadosi ültetvényt.";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "Tényleg? Nem félsz, hogy... hogy valami baj van velünk ezek után?";
			link.l1 = "Mindenki megérdemel egy második esélyt.";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "Köszönöm, kapitány. Esküszöm, nem fogja megbánni. Jó tengerészek vagyunk. És... talán most már nem lesznek rémálmok.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "Köszönöm, köszönöm! Legalább életben maradunk. Vigyen ki minket innen, kérem. Ez a sziget... mintha el lenne átkozva.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "Mi a fene?! Hogy merészeled megtámadni a 'Lady' és megölni Jeremy-t? Nem jutnak ki innen élve, gazemberek, a kapitány vissza fog térni és...";
			link.l1 = "A kapitányod meghalt. Jeremy tüzelt elôször, és én elviszem a 'Lady' törvényes zsákmányként, amit vérrel fizetek.";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "A kapitány... halott? Hazudsz, kutya! Egy gombot sem érsz az egyenruháján!";
			link.l1 = "Ha az egyenruha jelentett valamit, akkor az a Blackwoodé volt, aki már régen elment. Választhattok - egy halott emberért harcoltok, vagy megmentitek az életeteket.";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "Nem adjuk át a hajót harc nélkül!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "Figyeljetek, srácok. Tudom, hogy hûségesek vagytok a kapitányotokhoz. Ez tiszteletre méltó. De ô halott, ti pedig életben vagytok. És el kell döntenetek, hogyan éljetek tovább. Felajánlunk nektek egy esélyt, hogy újrakezdjétek.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "Kapitány, ezek az emberek nem ellenségek. Csak parancsot teljesítettek. Sokan közülük egykori királyi tengerészek, jól képzettek és fegyelmezettek. Pazarlás lenne nem használni a képességeiket. Fiúk, hosszú flottaszolgálatom alatt nem egyszer voltam már a helyetekben. És jól döntöttem. Tegyétek meg ti is.";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "Nos, tengerész fiúk! A választás egyszerû - vagy életben maradtok, vagy fogolyként a raktérben, vagy csatlakoztok a legénységünkhöz, jó fejadaggal és rendszeres fizetéssel, vagy... (húzza az ujját a torkán) Én a helyetekben az elsôt választanám!";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "A legénységem tagjai lesztek.";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "Jaj a legyôzötteknek, fiúk. Mostantól a helyetek az én raktáramban van. Ha szerencsétek van - megélhetitek a barbadosi ültetvényt.";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "Bevesz minket a legénységébe? Mindezek után?";
			link.l1 = "A jó tengerészek mindig értékesek. És Blackwood kapitány tudta, hogyan válassza ki az embereit.";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "Köszönöm, kapitány. Nem hagyjuk cserben.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "Nos... legalábbis ez az egyetlen módja, ahogy ez a kaland végzôdhetett. Bocsásson meg nekünk, Blackwood kapitány. Nem védtük meg magát.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "Nem adjuk át a hajót harc nélkül!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "Bocsásson meg. Maga Elizabeth?";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "Igen, én vagyok. És maga kicsoda?";
			link.l1 = "Kapitány "+GetFullName(pchar)+". Én... ismertem Albert Blackwoodot.";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "Az én Albertemet? Ó, Istenem... Ô... jól van?";
			link.l1 = "Sajnos, nem. Meghalt a csatában. Az utolsó erejéig harcolt.";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "I... Gyanítottam. Annyi év egyetlen szó nélkül... Tudja, vártam rá. Sokáig vártam. Apa azt mondta, Albertnek csak az elôléptetésre kell várnia. A kormányzó már mindent eldöntött, néhány hónap kérdése volt. De Albert... ô egészen másképp fogta fel ezt a beszélgetést. Azt mondta, hogy gazdagként tér vissza, méltó a kezemhez. És elment. Csak... elment.";
			link.l1 = "Az utolsó napjáig gondolt rád.";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "Milyen ostoba. Nem volt szükségem a kincseire. Ôt szerettem, nem a pénzét. Kész voltam megszökni vele... de ô olyan büszke volt. Vártam egy levelet, egy szót... Aztán csak ez a furcsa kézikönyv érkezett. Olyan hideg, számító dokumentum... egyáltalán nem olyan, mint az az Albert, akit ismertem. Ekkor jöttem rá, hogy elvesztettem ôt.";
			link.l1 = "A dolgai között ezt találtam.";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "Egy térkép a házamhoz? Én voltam a legfôbb kincse? Micsoda irónia. Az egész Karib-térségben kereste a gazdagságot, és az egyetlen dolog, ami számított neki, mindig itt volt... Várj. Van valamim a számodra. Ez Albert kézikönyve. Egy évvel ezelôtt küldte el nekem. Azt mondta, segít neki megtalálni a kincseket és visszatérni hozzám. Most még hasznosabb lesz neked.";
			link.l1 = "Köszönöm, Elizabeth. Sajnálom, hogy így alakult.";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "És megnôsültem, kapitány. Mr. Bishophoz. Apám ragaszkodott hozzá. Maga nem ismeri ezt az embert... és nem is akarja ismerni. Minden nap arra gondolok, hogy milyen lett volna az életem, ha Albert... csak úgy... visszatér.";
			link.l1 = "Most már én is erre fogok gondolni.";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "Viszlát, kapitány. És... vigyázzon magára. Ne kergesse a szellemeket.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "Igen, ez én vagyok.";
			link.l1 = " Helen MacArthur kapitány. Én... ismertem Albert Blackwoodot.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "Az én Albertemet? Ó, Istenem... Ô... És maga kicsoda?";
			link.l1 = "Helen MacArthur kapitány, azt mondtam... A saját hajóm parancsnoka vagyok.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "Kapitány? Egy nôi kapitány? Maga... Alberttel voltál? Milyen értelemben... ismerte ôt?";
			link.l1 = "Csak mint kapitány. Sajnálom, de Albert meghalt. Tanúja voltam az utolsó csatájának.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "Megértem. Bocsássa meg a gyanúmat. Csak... Blackwood kapitány mindig is vonzotta a nôk figyelmét. Még itt, Barbadoson is. Különösen itt.";
			link.l1 = "Maga szerette ôt.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "Teljes szívembôl. Apám azt mondta, Albertnek csak az elôléptetésre kell várnia. Csak néhány hónapról volt szó. De ô úgy értelmezte apa szavait, mint a szegénység miatti elutasítást. Azt mondta, hogy kincsekkel fog visszatérni. És elment.";
			link.l1 = "A férfiak és a büszkeségük!";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "Maga szerencsés, MacArthur kapitány. Szabad vagy. Oda hajózik, ahová akar. Nincsenek ültetvényesek, nincsenek apák, akik döntenek a sorsodról. Nincs férj, aki a tulajdonának tekinti.";
			link.l1 = "A szabadságnak nagy ára van. És minden nap meg kell védened.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "Talán tudok valamit, ami segíthet ebben az ügyben. Tessék, vegye el. Ez a kincsvadász kézikönyve. Albert küldte nekem egy évvel ezelôtt. Azt mondta, ez a legjobb dolog, amit valaha készített. Hogy ez segíteni fog neki meggazdagodni és visszatérni hozzám. De minden egyes oldalon egyre kevésbé hasonlított arra az Albertre, akit ismertem.";
			link.l1 = "Köszönöm. Köszönöm. Megtartom.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "Kérem, kapitány... becsülje meg a szabadságát. Hozzámentem Bishop ezredeshez. Egy olyan emberhez, akitôl még az apám is fél. Ha én is szabad lennék, mint maga... Minden más lenne.";
			link.l1 = "Tudom.";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "Viszlát, kapitány. És szép szeleket neked is.";
			link.l1 = ""+Goodbye()+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
} 