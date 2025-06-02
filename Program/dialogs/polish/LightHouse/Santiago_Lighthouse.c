// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Czego chcesz?","Czego chciałbyś się dowiedzieć?"),"Czego potrzebujesz, "+GetAddress_Form(NPChar)+"?","To już trzeci raz, gdy próbujesz mnie zapytać...","Mam cię dość, znikaj!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Przepraszam, zmieniłem zdanie.","Nic takiego, przepraszam."),"Zapomniałem, przepraszam...","Do trzech razy sztuka, co? Przepraszam...","Przepraszam, przepraszam! Już się wynosze...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "Witam. Inkwizytor z Santiago, Dadre Vincento, wspomniał o tobie w swoim liście. Powiedział, że możesz mi pomóc.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = "Jakieś wieści od Ojca Vincento, "+npchar.name+"?";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "Muszę zobaczyć się z Padre Vincento. Znalazłem przedmioty, które go interesują.";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = "Więc, "+npchar.name+", co ci powiedział Padre Vincento?";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Pewnie, senor. Musisz być człowiekiem dużego poważania, skoro sam Padre Vincento robi z tobą interesy.";
			link.l1 = "Znakomicie. Więc to ty jesteś naszym posłańcem. Teraz słuchaj, ten człowiek bardzo interesuje Padre Vincento. Teraz jest pod twoją opieką, musisz go przewieźć do Santiago lub znaleźć kogoś, kto to zrobi.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "...";
			link.l1 = "Jesteś odpowiedzialny za więźnia w imieniu Inkwizytora. Nie radziłbym ci zdejmować mu kajdan, Gaius Marchais to silny człowiek. Daj ten list padre Vincento i powiedz mu, że oczekuję odpowiedzi od niego za dwa dni. Mam nadzieję, że to wystarczy.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("Oddałeś list.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Zrozumiano, Senor. Zrobię, co w mojej mocy. To nie pierwszy raz, kiedy pomagam świętemu ojcu.";
			link.l1 = "To nie wszystko. Kapitan karaki, San Gregorio, Carlos Guevarra musiał tu być. Przywiózł mi wanilię. Czy przekazał ci mój list?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Tak, twój ładunek jest w porządku i czeka na ciebie, señor.";
			link.l1 = "Dobrze, to załaduję go na mój statek. Będę tu przez dwa dni, czekając na odpowiedź Padre Vincento. To na razie nie jest pożegnanie, "+npchar.name+"!";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "Tak, Señor. Oto list od Padre Vincenta. Jest z ciebie bardzo zadowolony, resztę dowiesz się z listu.";
			link.l1 = "Wybornie. Do tego czasu, "+npchar.name+" A teraz - żegnaj.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Bardzo dobrze. Daj mi je, a ja przekażę je świętemu ojcu.";
			link.l1 = "Nie ma mowy, chłopie! Nie było łatwo je zdobyć, i nie oddam ich tak po prostu. Oddam je tylko osobiście Padre Vincento.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Ale seniorze! Skąd mam wiedzieć, że mnie nie oszukujesz?";
			link.l1 = "Spójrz: kadzielnica, kielich i krzyż z lazurytem... "+npchar.name+", kim myślisz, że jestem? Naprawdę sądzisz, że jestem na tyle głupi, by iść do Inkwizycji bez nich?";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Przebacz mi, señor... Przyjdź jutro, a powiem Padre Vincento o twoim przybyciu.";
			link.l1 = "Dobrze. Do zobaczenia jutro.";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "Jego Wysokość cię przyjmie, Senor. Nie zwlekaj z wizytą. Oto dokument, pokaż go strażnikom, a oni cię wpuszczą. Ale najpierw podnieś hiszpańską flagę, bo inaczej żołnierze prawdopodobnie cię aresztują.";
			link.l1 = "Rozumiem. Zatem Hiszpanie. Dzięki, przyjacielu! Już w drogę!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 400);//скрытность
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
