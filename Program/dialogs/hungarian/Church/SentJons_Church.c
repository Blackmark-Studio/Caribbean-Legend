// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések, "+ GetSexPhrase("fiam","lányom") +"?", "Kérdezz csak, hallgatlak..."), "Figyelek, beszélj most, "+ GetSexPhrase("fiam","lányom") +"...", "Harmadszorra, "+ GetSexPhrase("fiam","lányom") +", kérd, amire szükséged van.",
                          "Egy lelkésznek rengeteg munkája van, és te eltereled a figyelmemet, "+ GetSexPhrase("fiam","lányom") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem, atyám..."), "Nincs mit mondanom, elnézést kérek.",
                      "Megkérdezem, de késôbb. Bocsásson meg, atyám.", "Bocsásson meg, szent atyám...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Szentatya, Thomas Morrison lányáról szeretnék beszélni.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Szentatya, Thomas megkért, hogy mondjam el, hogy elfogadja a bûnbánat útját, jótetteknek fogja szentelni magát, és új harangot fog adni a plébániának - bármi áron.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Beszélj, gyermekem, hallgatlak.";
			link.l1 = "Tudom, hogy ellenzed, hogy a cigány segítsen a lánynak. De hogyan kényszeríthetsz egy apát arra, hogy a legkisebb esélyt is elutasítsa, hogy megmentse a lányát? Lehet, hogy a módszerei megkérdôjelezhetôek, de olyan tudással rendelkezik, ami segíthet.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "Fiam, csak az Úr gyógyíthatja meg a lányt. Az Ô tervébe vetett hit az, ami átsegít minket a megpróbáltatásokon. Ha Tamás szorgalmasan imádkozik, követi Isten igéjét, és bôkezûen adakozik a gyülekezetnek, az Úr meghallgatja imáit és kegyelmet mutat.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Trustworthy) De még neked is el kell ismerned, hogy az Úr embereken keresztül cselekszik. Mi van, ha a cigány csupán eszköze az Ô akaratának? Mi van, ha az Ô terve olyan mélyreható, amit mi egyszerû halandók nem érthetünk meg? Az Úr titokzatos utakon jár, nem igaz?";
				link.l1.go = "dwh_pastor_VD_1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l1 = "Arra kényszerítesz egy apát, hogy végignézze a lánya pusztulását, ahelyett, hogy hagynád, hogy megpróbálja megmenteni. Ez irgalmas?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				Notification_Perk(false, "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "Bölcs szavai vannak, kapitány. De mégsem engedhetem, hogy az eretnekség beszivárogjon a nyájunk szívébe, és megrendítse az egyik legodaadóbb fiú hitét.";
			link.l1 = "Semmi sem ingatná meg jobban a hitét, mint a lánya elvesztése. De ha megengeded neki, hogy minden eszközt felhasználjon, még a bûnösnek tartottakat is, akkor a hite erôsödni fog, nem pedig gyengülni.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "De... milyen példát mutatna ez a gyülekezet többi tagjának?";
			link.l1 = "Példát arra, hogy az egyház nem vakon büntet, hanem az igazi bûnbánat felé vezet és vezet. A Szentírás nem arra tanít bennünket, hogy az ôszinte bûnbánat és a jó cselekedetek megválthatják a bûnt? Egy nagylelkû adomány a gyülekezetnek lehet az elsô lépés a megváltás felé.";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "Talán igaza van, kapitány úr. Hajlandó vagyok megadni Thomasnak ezt az esélyt. De tudd meg - ha letér az igaz útról, és elveszíti a hitét, akkor te is felelôsséget viselsz érte! Ami az adományokat illeti - az egyháznak nincs szüksége gazdagságra, nekünk megvan, amire szükségünk van. Kivéve... a harang megsérült a spanyol támadás során...";
			link.l1 = "Átadom a szavaidat Thomasnak. Köszönöm, hogy idôt szakított rám, Szentatya. Az Úr tartsa meg önt.";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "Ez nem szívtelenség, kapitány, ez hit. Nem hagyjuk magára a lány sorsát, hanem az Úr kezébe helyezzük. Ha Tamás imádkozik, hisz és alázatosan vár, biztos vagyok benne, hogy az Úr meghallgatja imáinkat és meggyógyítja a lányt.";
			link.l1 = "Tudod, hogy még a sziget nemesei, beleértve a kormányzót is, igénybe vették a cigány szolgálatát. És nincsenek kiátkozva. Akkor miért vagy olyan szigorú Thomasszal?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "Persze, hogy tudom, fiam. De ôk elveszett lelkek, akiket még nem érintett meg az Úr igazi fénye. Thomas a nyájunk oszlopos tagja, az egyik legjobb. Ha hagynánk, hogy a gonoszság megrongálja a hitét, az az egész egyházat veszélyeztetné, és én nem engedhetek meg ilyen súlyos bûnt.";
			link.l1 = "Tehát nem adsz neki még egy kis esélyt sem? Ez valóban igazságos?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "Amit önök megváltásnak neveznek, az könnyen romláshoz vezethet. Tapasztalatból beszélek. Egyszer, akaratom ellenére, egy hozzá hasonló gyógyító kezelte az unokahúgomat. Egy kislány, aki kínok között halt meg. És csak az Úr tudja, hogy a lelke kárhozatra ítéltetett-e a rituálék miatt. Ne próbáljon meggyôzni engem - hiábavaló.";
			link.l1 = "Rendben van. Ha ez a végsô válasza, nem fogok vitatkozni. Az Úr tartsa meg önt.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;

		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			LAi_CharacterEnableDialog(sld);
		break;

		case "dwh_pastor_VD_5":
			dialog.text = "Kitûnô, fiam. Az új harang az Úr és a templom iránti odaadásának jelképe lesz. Hadd tegye, amit kell, de emlékeztesd rá - a Mindenható szeme minden cselekedet felett ôrködik, és semmi sem kerüli el az Ô akaratát.";
			link.l1 = "Úgy legyen, Szentatya. Búcsúzom.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
			LAi_RemoveLoginTime(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
