// Раймонд Бейкер - палач Сент-Джонса и возможный офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Chcesz czegoś?";
			link.l1 = "Nie, to nic.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Dziękuję, Kapitanie! Nie mogę sobie nawet wyobrazić, co bym zrobił bez ciebie...";
			link.l1 = "Potrafię sobie wyobrazić. Umrzesz z głodu albo skończysz w brzuchu dzikusa z Dominiki. Ale masz szansę mi się odpłacić.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Jak mogę ci pomóc, Kapitanie?";
			link.l1 = "Chcę wiedzieć więcej o pewnym człowieku. Jest naszym wspólnym przyjacielem, że tak powiem. Właściwie to bardzo bliskim przyjacielem twoim. Mam na myśli kapitana Rzeźnika. Tak, tego, którego powiesiłeś dwadzieścia lat temu. Panie, czemu jesteś taki blady? Chcesz łyk rumu?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Czy... czy on cię przysłał?";
			link.l1 = "Bzdura! Jak mogę być 'wysłany przez niego', skoro on nie żyje! Bardziej interesują mnie rzeczy, które po nim zostały, niż sam Rzeźnik. Listy, dokumenty, tego rodzaju rzeczy. Może znalazłeś coś w jego kieszeniach... Czekaj! Nie rozumiem. Naprawdę myślisz, że Rzeźnik żyje? Sam go straciłeś!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Cholera! Nie masz pojęcia. To znaczy, że nie zostałeś wysłany przez Rzeźnika tak, jak myślałem...";
			link.l1 = "Cóż, cóż. To staje się coraz bardziej interesujące. Wygląda na to, że Henry miał wszelkie powody, by bać się Rzeźnika i dlatego zmarł na atak serca... Czy Rzeźnik żyje?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "Jest, kapitanie... I szukają mnie.";
			link.l1 = "Raymondzie, mówiono mi, że nie jesteś głupcem. Nie próbuj ze mną gierek. Jesteś tu bezpieczny przed wszelkim zagrożeniem. Powiedz mi wszystko, co wiesz, a wymyślę coś, by ci pomóc. Może mamy wspólnych wrogów. Zacznijmy od Rzeźnika.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "On żyje, ale teraz ma inne nazwisko! Jego ludzie odwiedzili mnie w noc egzekucji. Jackman i inny człowiek z jakimś dziwnym przezwiskiem. O ile pamiętam, to był 'Utopiony'.";
			link.l1 = "Kat. Henry Kat.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Racja! Zaproponowali mi prosty układ - umrzeć w najbardziej bolesny sposób lub uratować ich kapitana. Więc musiałem upozorować egzekucję przy użyciu specjalnego sprzętu, który stworzyłem w wolnym czasie. Widzisz, taka konstrukcja pasów i zacisków może rozłożyć ciężar ciała. \nWszystko, co musiałem zrobić, to połączyć to z tajnym hakiem w pętli. 'Trup' musiał jednak dobrze odegrać swoją rolę. Muszę powiedzieć, że gra aktorska Lawrence'a była bardzo przekonująca, zrobił wszystko dobrze, z wyjątkiem tego, że odmówił posikania się, z powodu...";
			link.l1 = "Zwałeś Rzeźnika 'Lawrence'm'?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "To jest jego prawdziwe imię. Mówiłem ci, że nazywa się Lawrence Beltrope. Od roku, odkąd wrócił na Karaiby, nie mogłem zaznać spokoju. A kiedy dowiedziałem się, że szukają mnie jacyś źli ludzie...\nNawet napisałem wyznanie dla władz na wszelki wypadek. Trzymam je zawsze przy sobie, bo boję się je oddać. Mogą pomyśleć, że byłem chętnym pomocnikiem. Proszę, pozwól mi zostać z twoją załogą. Przysięgam, jestem doskonałym lekarzem i mogę ci bardzo pomóc.";
			link.l1 = "Dobrze. A co z osobistymi rzeczami Rzeźnika... eh, Beltrope'a? Czy ma on związek z Thomasem Beltrope'em?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "Nie mam pojęcia. Nie mam niczego szczególnego od samego Beltrope'a. Ale dam ci wszystko, co mam, możesz z tym zrobić, co tylko zechcesz. Wszystkie dokumenty związane z tematem są w mojej torbie. Zachowałem wszystko na wszelki wypadek i trzymam blisko przy sobie.\nTutaj, spójrz... to jest legenda kapitana Rzeźnika, to jest moje wyznanie... To są rzeczy, które należały do Joshua Leadbeatera...";
			link.l1 = "Stój! Leadbeater? Kto to jest?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Och! To był człowiek niezwykły. To on osobiście ścigał Rzeźnika. Ludzie pamiętali go jako 'zamaskowanego człowieka'. Został zamordowany wkrótce po egzekucji Rzeźnika. Ktoś podciął mu gardło zębem rekina! Jeden cięcie i po wszystkim. Kiedy jeszcze żył, musiał wiele cierpieć.\nJeśli widziałeś jego twarz pod maską, to było nic, tylko mięso! Miał tę stronę z dziennika w kieszeni, gdy zginął. Musiało to być z pism Jessiki Rose. Przerażająca historia! Przeczytaj ją, a wszystko stanie się bardziej zrozumiałe.\nA oto sam ząb. Widzisz litery? S.D.... Cokolwiek to znaczy. Są tam też ślady krwi.";
			link.l1 = "Dosyć! Muszę wszystko dokładnie przeczytać i to przemyśleć. A ty będziesz moim pasażerem albo lekarzem okrętowym, dopóki się z tym wszystkim nie uporam. Możesz swobodnie oddychać, Raymondzie, jesteś bezpieczny na moim statku.";
			link.l1.go = "baker_10";
		break;
		
		case "baker_10":
			DialogExit();
			sld = characterFromId("Baker_Cap");
			LAi_SetImmortal(sld, false);
			sld.lifeday = 0;
			//sld.ship.hp = 0;
			//sld.SinkTenPercent = true;
			bQuestDisableMapEnter = false;
			GiveItem2Character(pchar, "shark_teeth");
			GiveItem2Character(pchar, "letter_jess");
			GiveItem2Character(pchar, "letter_baker"); // показания бейкера
			ChangeItemDescribe("letter_baker", "itmdescr_letter_baker"); // Addon-2016 Jason
			AddQuestRecordInfo("Legend_CapBucher", "1");
			AddQuestRecordInfo("Letter_jess", "1");
			AddQuestRecord("Shadows", "5");
			pchar.questTemp.Saga.Shadows = "islatesoro";
			// в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Baker_officer";
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Tak, kapitanie?";
			Link.l1 = "Słuchaj mojego rozkazu!";
            Link.l1.go = "stay_follow";
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, daj mi pełen raport o statku.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "Chcę, abyś kupował pewne towary za każdym razem, gdy jesteśmy w porcie.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "To nic. Zwolniony!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Chodź, kapitanie, jestem lekarzem, a nie kwatermistrzem. Choć w przeszłości pracowałem w innym charakterze... nieważne. Naprawdę nie zajmuję się księgowością, przepraszam.";
			Link.l1 = "Dobrze, niech tak będzie. Jesteś moim medykiem - jak uzgodniliśmy, gdy dołączyłeś do mojej załogi.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Kapitanie, szczerze mówiąc, nigdy nie zdobyłem dużego doświadczenia w handlu. Nigdy się nie targowałem, nigdy nie śledziłem cen. Także... wolałbym zostać na statku, jeśli nie masz nic przeciwko. Niektórzy z tych kupców mogą mnie rozpoznać, a zanim się obejrzysz - pojawią się zamaskowani ludzie.";
			link.l1 = "Zatem będziesz żył w strachu przed swoją przeszłością... Dobrze, wypuść powietrze, zrobię to sam.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Rozkazy?";
            Link.l1 = "Stań tutaj!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Podążaj za mną i trzymaj tempo!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Zmień rodzaj amunicji do swojej broni palnej.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wybór rodzaju amunicji:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Zaszła zmiana w nastawieniu!";
            Link.l1 = "Zwolniony.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Zaszedł zmiana usposobienia!";
            Link.l1 = "Zwolniony.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
