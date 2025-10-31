// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek rád, mi a kérdés?"), "Már másodszor próbálod megkérdezni...", "Már harmadszorra próbálod újra megkérdezni...",
                          "Mikor lesz már vége?! Elfoglalt ember vagyok, a kolónia ügyein dolgozom, és te még mindig próbálsz kérdezni valamit!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem. Rossz helyen és rossz idôben."), "Igaz... De késôbb, nem most...",
                      "Megkérdezem... De egy kicsit késôbb...", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Van egy kényes ügyem a számodra. Nemrég egy magánember egy aranykeresztet adományozott egy lazurittal a Basse-Terre-i plébániának. A probléma az, hogy a keresztet ellopták a Santiago plébániáról, és a lopás során meggyilkoltak egy lelkészt...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Philippe de Poincy fôkormányzó parancsára érkeztem, hogy átvegyem az önök fegyveres fregattjának parancsnokságát.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "Készen állok arra, hogy a fregattot a hajórajhoz vezessem.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "Itt van egy találkozóm egy személlyel...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Monsieur, kereskedelmi tevékenységet kívánok folytatni a városban. Konkrétan a szeszes italok folyamatos, nagyüzemi kereskedelme érdekel.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Már mindent elvettél. Mit akarsz még?", "Maradt még valami, amit nem vittél el?");
            link.l1 = RandPhraseSimple("Csak körülnézek...", "Csak ellenôrzöm, hátha elfelejtettem valamit...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. Ez elég érdekes. De miért gondolja, hogy engem érdekelnek a spanyolok problémái?";
			link.l1 = "Nem a spanyolokról van szó, Monsieur. A vallás nem nemzetiség szerint osztja meg az embereket. Az ön plébániáján van egy tárgy, amit a szent szolga vére borít, és a Santiago plébánián is történt egy gyalázás...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "Kérem, hogy mutasson igazságot és rendelje el, hogy a szentatya adja vissza a keresztet a tulajdonosának.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "És mióta vagy te ilyen igaz és komolyan hívô, ha, "+pchar.name+"? A spanyolok nem a barátaink, és nem látok okot arra, hogy a szentatyát nyomuljunk ebben a kérdésben. A kereszt ajándék volt és ez így van rendjén. A mi papunknak semmi köze ahhoz a lopáshoz és gyilkossághoz, szóval...";
			link.l1 = "És te nem tudsz segíteni, igaz?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Hogy ôszinte legyek, "+pchar.name+", nem érzem, hogy muszáj lenne. Nem szeretem azokat a pápista fanatikusokat.";
			link.l1 = "Értem. Elnézést a zavarásért, Monsieur...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "A hajó készen áll, de nincs szabad hely a századában. Kapitány, csökkentse a századát és térjen vissza, akkor azonnal átadom a fregattot.";
				link.l1 = "Rendben.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Igen, természetesen, a hajó készen áll a kihajózásra. A kapitánya tisztában van vele, és minden parancsát teljesíteni fogja.";
				link.l1 = "Akkor elindulunk. Viszontlátásra, felség.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Kitûnô. Készüljön fel az új hajó üdvözlésére. A kapitánya tisztában van vele, és minden parancsát teljesíteni fogja.";
			link.l1 = "Akkor elindulunk. Viszontlátásra, felség.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Monsieur Charles de Maure, tökéletes idôzítés! Az öreg barátom nagyon szeretne találkozni önnel, és megkért, hogy értesítsem az érkezésérôl. Kérem, jöjjön a nappalimba, azonnal értesítem Angerrant. Egyébként hogyan ismerkedtek meg?";
			link.l1 = "Együtt játszottunk. Ô vesztett, volt egy kis veszekedésünk. Gondolom, Monsieur de Chievous szeretné rendbe hozni a dolgokat köztünk.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "Kétségtelenül! Remélem, hogy rendbe hozza a dolgokat kettôjük között. Angerran lehet, hogy nem a legkellemesebb ember, akivel üzletelni lehet, de okos és becsületes, akárcsak te. Ritka fajta.";
			link.l1 = "Hízeleg nekem, excellenciás uram. A nappaliban fogom várni, ha nem bánja.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "De persze, ahogy akarja, érezze magát otthon. Lehet, hogy várnia kell egy kicsit. Megrendelem, hogy hozzanak valami italt.";
			link.l1 = "Köszönöm, excellenciás uram, de most nem kérek. Csak leülök és várok a közös... barátunkra.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "Kapitány, bölcsen tette, hogy megkeresett. Mindent megteszünk a szigeten folyó illegális kereskedelem elleni küzdelem érdekében, és ôszintén üdvözlöm azokat az egyenes kapitányokat, akik legális csatornákon keresztül próbálnak üzletet kötni.";
			link.l1 = "Szóval, milyen feltételek és lépések szükségesek a kereskedelem megkezdéséhez?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "Ez elég egyszerû. A szeszesital-kereskedelemhez havonta száz dublont kell fizetni a kincstárnak, megfelelô nyilvántartást kell vezetni, és rendszeresen jelentést kell tenni a tevékenységrôl. Amint a pénzösszeg befizetésre került, megkezdheti a kereskedelmet.";
			link.l1 = "Kiváló. A feltételek teljesen ésszerûek. Egy Christian Deluce nevû helyi lakos fog eljárni a nevemben. Bízom benne, hogy ez nem okoz problémát.";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "Ahogy óhajtja, kapitány. De ne feledje - a védencéért a teljes felelôsség az ön vállán nyugszik. Ha megszegi a szabályokat, osztozni fog a következményekben.";
			link.l1 = "Természetesen. Köszönöm a felvilágosítást, kormányzó. Elintézzük a dolgokat, és Christian gondoskodik az adófizetésrôl.";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "Pompás. Örülök, hogy ilyen szorgalmasan közelít. Sok sikert kívánok a vállalkozásukhoz.";
			link.l1 = "Nagyon hálás vagyok. Bízom benne, hogy együttmûködésünk a város javát szolgálja. Viszontlátásra.";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
