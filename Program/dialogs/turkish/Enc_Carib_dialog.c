void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Tebrikler! Bu bir hata. Jason'la iletişime geçip bunu nasıl ve nerede bulduğunu anlat. Kolay gelsin!";
			link.l1 = "Hemen yapacağım!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Denizin oğlu, selam sana! Senin hakkında duyduklarım var. Topraklarımızda özgürce dolaşabilirsin.",""+npchar.name+" seni selamlıyor, solgun yüzlü kardeş. Seni misafirimiz olarak görmekten memnunuz.","Seni selamlıyorum, cesur beyaz yüzlü savaşçı! "+npchar.name+" Kızılderililerin bir dostuyla tanıştığına memnun oldu. Huzur içinde git!");
				link.l1 = RandPhraseSimple("Ve sana da selam, kızıl derili kardeşim! Sana iyi avlar dilerim!","Selam, cesur savaşçı! Tanrılar sana ve ailene bereket versin!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("Sana ilginç gelebilecek bir şeyim var, kızıl derili kardeşim. Takas yapmak ister misin?","Sana ilginç bir şey satabilirim, cesur savaşçı. Alışveriş yapmak ister misin?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Dur, soluk yüz! Hangi hakla topraklarımda yürüyorsun?","Dur, beyaz adam! Burası atalarımın ve benim toprağım!","Dur, soluk yüzlü! Bu topraklarda işin yok");
				link.l1 = RandPhraseSimple("Burası senin toprağın mı? Defol git, kızarmış suratlı pislik!","Şuna bak - konuşan bir maymun! Şimdi defol!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("Barış için geldim, kızıl derili savaşçı. Boş yere dövüşmemeliyiz.","Sana ya da toprağına düşman değilim, savaşçı. Barış için geldim.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("Seninle ticaret yapmak için geldim, kavga etmek için değil.","Ben Kızılderililerle savaşmam. Onlarla ticaret yaparım.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("Doğduğun güne lanet edeceksin, solgun suratlı köpek... Kalbini çıkarıp ateşte kızartacağım!","Sana taş yedireceğim, solgun suratlı köpek! Dizlerinin üstünde ölüm için yalvarırken sana güleceğiz, beyaz it!");
			link.l1 = RandPhraseSimple("Hâlâ o pis ağzını kapatamıyor musun, boyalı korkuluk? Sürükleyip geldiğin ormana geri yollayacağım seni!","Bana tehdit mi savuruyorsun, pislik?! Şimdi geldiğin ağaca geri tırman bakalım!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("Sesinin doğru söylediğini duyuyorum. Bugün baltalarımızı sana karşı kaldırmayacağız. Huzurla git, soluk yüzlü.","Beyaz yüz nadiren huzur getirir, ama gözlerinde doğruyu söylediğini görüyorum. Şimdi git.");
			link.l1 = RandPhraseSimple("Akıllıca bir karar, savaşçı. Sana bol şans.","Anlaştığımıza sevindim, savaşçı.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("Yalancısın, soluk yüzlü köpek! Buraya Kızılderilileri öldürmeye geldin! Savaşa hazır mısın, soluk yüzlü?!","Sen Kızılderilileri öldürüyorsun. Beyaz dil yalancı dildir. Onu keserim ve ateşte kızartırım!");
			link.l1 = RandPhraseSimple("Pekâlâ dostum, o zaman beni suçlama. Tanrı şahidimdir, bundan kaçınmaya çalıştım...","Pekala, sen istedin, savaşçı.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Ticaret mi? Beyaz adamın silahına ihtiyacımız var. O soluk yüzlünün tek elle kullanılan ateşli silahı! Bunun için mallarımızı takas ederiz! Takas edecek bir ateşli silahın var mı?";
				link.l1 = "Hmm. Evet, biliyorum. Peki bana karşılığında ne vereceksin?";
				link.l1.go = "war_indian_trade";
				link.l2 = "Sen alçak! Sonra da tabancalarımla kolonistleri mi vuracaksın? Hayır, buna izin vermem! Size gelince, çakallar, şimdi hepinizi doğrayacağım...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "Aradığımız şey sende yok, soluk yüz... Savaş ganimetimiz olacaksın!";
				link.l1 = "Denemeye cesaretin varsa, korkuluk...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("Beyaz suratlı köpeklerle ticaret yapmayız. Öldürür, alırız!","Biz kirli Miskito ya da Arawak değiliz, soluk yüzlülerle ticaret yapmayız! Onları öldürür, savaş ganimetlerini alırız!");
			link.l1 = RandPhraseSimple("Pekâlâ, o zaman soy beni, alçak!","Önce kılıcımı elimden alman gerekecek, pislik!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "Sen neyin varsa gösterirsin, biz de ona ne vereceğimizi söyleriz.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hey-ho! Bunun için sana vereceğiz "+sText+".";
			link.l1 = "Anlaştık!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Hayır. Asla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hey-ho! Kurnaz bir silah... Bunun için sana bir şeyler vereceğiz "+sText+".";
			link.l1 = "Anlaştık!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Hayır. Asla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "Hey-ho! Güçlü bir silah! Birçok, birçok düşmanı öldürür! Onun için sana veriyoruz "+sText+".";
			link.l1 = "Anlaştık!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Hayır. Asla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Korkunç bir silah... Bunu sana bunun karşılığında vereceğiz "+sText+".";
			link.l1 = "Anlaştık!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Hayır. Asla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Güzel ve kudretli bir silah! Birçok, birçok düşmanı öldürdü! Bunun karşılığında sana veriyoruz "+sText+".";
			link.l1 = "Anlaştık!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Hayır. Asla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Güzel bir silah... Karşılığında sana bir şeyler vereceğiz "+sText+".";
			link.l1 = "Anlaştık!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "Hayır. Asla.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "Güzel. İşte malların. Artık ticaret yapmayacağız. Sonra tekrar gel. Daha iyi ateşli silah getirene daha fazlasını veririz. Şimdi git!";
				link.l1 = "Elveda, kızıl derili savaşçı.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Pekâlâ. İşte malların. Takas edecek başka ateşli silahların var mı?";
				if (CheckCaribGuns())
				{
					link.l1 = "Var. Alacak mısın?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "Hayır. Bir dahaki sefere daha fazlasını getireceğim.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Getir. Daha iyi bir ateşli silah getir, sana daha fazlasını verelim. Şimdi git!";
			link.l1 = "Görüşürüz, savaşçı...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "O zaman her şeyi bedavaya alıyoruz, soluk yüzlü!";
				link.l1 = "Deneyebilirsin...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Selam, beyaz adam. Ormanımızda ne arıyorsun?","Ormanımız çok tehlikelidir. Burada ne yapıyorsun?","Buraya ne getirdi seni, cesur beyaz yüz?");
			link.l1 = RandPhraseSimple("Yoldan geçiyordum sadece, kırmızı tenli dostum. Sanırım bu yolda ikimiz için de yeterince yer var?","Selamlar, ormanın oğlu! Burada işim var ve Kızılderililerle savaşmam.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("Ve neden bilmek istiyorsun? Kendi yoluna git ve beladan uzak dur!","Kendi yoluna git, kızıl tenli. Seninle konuşacak vaktim yok.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("Biz barışçıl insanlarız. Beyaz adamlarla düşman değiliz. Git, ama topraklarımızda dikkatli ol!","Hintli dostlarının solgun yüzlü arkadaşıyla tanıştığıma memnun oldum. Huzurla git, denizin oğlu!");
			link.l1 = RandPhraseSimple("Sana da bol şans, selva'nın oğlu...","Elveda, kızıl derili dostum.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("Biz barışçıl avcılarız. Ama topraklarımızda soluk yüzlülerin böyle konuşmasına asla izin vermeyiz!","Beyaz adamlarla savaşmayız, ama eğer beyaz adamlar bize hakaret ederse, atalarımızın bize öğrettiği gibi karşılık veririz!");
			link.l1 = RandPhraseSimple("Hâlâ o pis ağzını kapatamıyor musun, boyalı korkuluk? Sürükleyip geldiğin ormana geri göndereceğim seni!","Bana tehdit mi savuruyorsun, pislik?! Şimdi geldiğin ağaca geri tırmanacaksın!");
			link.l1.go = "exit_fight";
		break;
	}
}
