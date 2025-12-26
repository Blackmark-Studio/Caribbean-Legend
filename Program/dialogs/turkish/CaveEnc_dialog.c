// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bir şey ister misin?";
			link.l1 = "Hayır, hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Vay canına, kimleri görüyorum! Bugün senin şanslı günün, dostum. Biz iyi insanlarız, bak, sadece biraz yemek pişiriyoruz falan... Seni yemeğimize davet etmiyorum, ama hâlâ vaktin varken kaybolsan iyi edersin.","Şimdi defol ve bizi rahatsız etme. Yarın tekrar gel – ve cüzdanını yanında getirmeyi unutma, ha-ha-ha!","Beni kızdırma, denizci! Mağaranın girişinin nerede olduğunu hâlâ hatırlıyor musun? Oraya şimdi, hem de çok, çok hızlı gitmelisin...","Artık çizgiyi aştın, dostum! Demek işlerimi bir kenara bırakıp seninle ilgilenmem gerekecek, alçak herif!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Çok naziksin, dostum...","Şaka yapmayı seviyorsun anlaşılan...","Pekâlâ, sen de yassı keklerini kızartmaya devam et o zaman...","İşte şimdi konuşuyoruz, ha-ha!",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Vay canına! Av aramaya gerek yok, zaten ayağımıza geldi... Hey, çocuklar - şu süslüyü biraz soyalım, ne dersiniz?","Kimse seni buraya davet etmedi dostum... Ama yine de burada olman güzel. Şimdi bakalım, kesen ne kadar doluymuş!","Seni buraya kimse zorla getirmedi, heh-heh... Ama madem geldin, ceplerinden neler dökülecek bir bakalım, biraz gıdıklayacağız seni...");
				link.l1 = LinkRandPhrase("Şimdi dilini biraz kısaltacağım...","Umarım kılıç kullanmadaki yeteneğin, dilin kadar keskindir, geveze!","Pekala, galiba çürüyen bedeninde birkaç delik daha açmanın zamanı geldi...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Vay canına! Av aramaya gerek yok, zaten burada... Hey millet, şu süslüyü soyalım mı, ne dersiniz?","Kimse seni buraya davet etmedi, dostum... Ama yine de burada olman iyi oldu. Bakalım, kesen ne kadar doluymuş!","Kimse seni buraya zorla getirmedi, he-he... Ama madem buradasın, ceplerinden neler dökülecek diye seni biraz gıdıklayacağız sanırım...");
			link.l1 = LinkRandPhrase("Şimdi dilini biraz kısaltacağım...","Umarım kılıç kullanmadaki yeteneğin, dilin kadar keskindir, geveze!","Görünüşe bakılırsa, çürüyen bedenine birkaç delik daha açmanın vakti geldi...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Kaybol, dostum. Burada yapacak bir işin yok!","Bak, sana güzelce söylüyorum: kaybol. Ne olacağı hiç belli olmaz...","Son uyarı: Eğer hemen defolup gitmezsen, buraya geldiğine bin pişman olacaksın.","Hepsi bu kadar, bela aradın kendine.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Bana ne yapacağımı söyleme, tamam mı?","Orada ne varmış ki? Sadece bir mağara, başka bir şey değil...","Aman, hadi ama...","Ha! Bakalım kim daha iyiymiş, pislik!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Solgun surat, uzaklaş. O memnun olacak ki "+npchar.name+"  nazik. Tanrılar bugün sana acıyor.","Mağaramdan defol yoksa kardeşlerimle birlikte çok fena sinirleniriz!","Defol, solgun suratlı köpek!","Şansın da hayatın da bitti, beyaz köpek!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Çok teşekkür ederim dostum, bu gerçekten çok nazikçe...","Bu mağara sana ait değil, ben ise istediğim yere giderim.","Sakin ol biraz, bataklık çocuğu.","Şimdi o lafları sana geri tıkacağım, hayvan...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Lanetli soluk yüz kamp ateşimize geldi! Vay canına! İşin bitti!","Aptal beyaz surat, jaguarın inine geldin. Ciğerini kızartacağım!","Küstah beyaz surat benim mağarama gelmeye cüret ediyor? O zaman buradan asla canlı çıkamayacak!");
				link.l1 = LinkRandPhrase("Şimdi dilini koparacağım...","Artık dünyada birkaç yamyam daha az olacak...","Pekâlâ, galiba çürüyen bedeninde birkaç delik daha açmanın zamanı geldi, kızarmış suratlı maymun.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Pis beyaz surat mağaramıza geldi! He-hee! Dilini koparıp kızartacağım!","Aptal beyaz surat jaguarın inine gelmiş. Kardeşler, şu lanet beyaz iti gebertin!","Küstah beyaz surat benim mağarama gelmeye cüret ediyor ha? O zaman buradan asla sağ çıkamayacak!");
			link.l1 = LinkRandPhrase("Senin lanet olası kafanı keseceğim...","Artık dünyada birkaç yamyam daha az olacak...","Pekâlâ, atalarını görmeye hazırlan, Kızılderili. Cehenneme kadar yolun var!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
