void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Buraya gelmeye cüret ediyorsun ha?! Cesurca bir hareket...","Bu aptallar nasıl olur da düşmanın işgal etmesine izin verir?! Akıl alır gibi değil...","Eh, muhafızlarım neye yarar ki, eğer bir aptal konutumda başıboş dolaşıyorsa..."),LinkRandPhrase("Ne istiyorsun, alçak herif?! Askerlerim seni çoktan buldu ve kaçamayacaksın."+GetSexPhrase(", pis kirli korsan"," pislik korsan")+"!","Pis katil, konutumdan uzak dur! Muhafızlar!!!","Senden korkmuyorum, alçak! Asılacaksın, kaçamayacaksın..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Askerler hiçbir şeye mal olmaz...","Beni asla yakalayamayacaklar."),RandPhraseSimple("Kes sesini, "+GetWorkTypeOfMan(npchar,"")+", yoksa dilini kesip boğazına tıkarım...","Sana söyleyeyim dostum: Sessiz otur, belki bir gün daha görebilirsin..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Malikanemde düşman var! Alarm!!!";
				link.l1 = "Kahretsin!";
				link.l1.go = "fight"; 
				break;
			}			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+" Efendim. Ben "+GetFullName(npchar)+", Lost-Tekes madeninin komutanı, sahibi olan "+NationKingsName(npchar)+". Şimdi, ziyaretinizin amacını bana söyler misiniz, "+GetAddress_Form(NPChar)+".";
				link.l1 = "Burada ilk kez bulunuyorum ve bu yerleşim ile yasaları hakkında daha fazla bilgi almak istiyorum...";
				link.l1.go = "info";
				link.l2 = "Sadece sizi selamlamak istemiştim, zaten gidiyorum.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = "Yine siz misiniz, efendim? Başka ne istiyorsunuz?";
			link.l1 = "Önemli değil. Gidiyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "I respect such discipline. Well, I'll bring you up to speed in that case, since you are that interested.\nLos-Teques mine is the property of the Spanish Crown. We mine silver and gold ore here, as well as silver and gold nuggets. All gold and silver belong to Spain and are transported to the Old World.\nThe mine is well guarded; a unit of elite Spanish soldiers is always stationed here. Pirates have made several attempts to rob our mine, but the consequences were always bad... for them.\nAs you can see, it is a small town. We have a tavern and a store. You can buy gold and silver ingots for a good price there. Besides, our quartermaster, who is also the merchant in the store, can sell you other interesting metals and ores.\nMost of our workers are convicts, but we also have a small number of black slaves. As you can see, we are always in need of new manpower; every day at least one of these blasted convicts dies.\nSo, if you bring us slaves, we will exchange nuggets for them. Contact our lead engineer for such matters. You can find him in the shaft.\nBehave yourself here. Don't start duels or fights, don't try to steal anything, especially gold or silver. We don't have a prison here, but we do have a court martial.\nThat's pretty much it. Follow these simple rules and you will have no problems. You are allowed to move freely within the mine. Don't forget to visit the tavern; they perform certain... services with my permission. Welcome!";
			link.l1 = "Teşekkür ederim!";			
			link.l1.go = "exit";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = "Soygun!!! Bu kabul edilemez! Kendini hazırla, "+GetSexPhrase("pal","kız")+"...";
			link.l1 = LinkRandPhrase("Kahretsin!","Caramba!!","Kahretsin!");
			link.l1.go = "PL_Q3_fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
	}
}
