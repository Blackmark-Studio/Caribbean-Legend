void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain got scared and bought off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed, he lost " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
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
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit " + GetFullName(npchar) + " has finally found justice. He and his boys tried to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our dear robber shited his pants, ha-ha! That will be a lesson for him! Robbing the local farmers is one thing, but a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's ass. We were scared to even send couriers to the farm for milk, they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" stopped that rascal " + GetFullName(npchar) + ", who was in 'charge' of the jungle, terrorizing all the local farmers. I do hope, it will stop them from their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he chased on these robbers over all the jungle like a shark chases flock of sardines. Thank God that there are still people who can stand up for us at time when the authorities do nothing, too busy with their dark deeds..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("Olduğun yerde kal ve silahını bırak! Paran mı, canın mı!","Olduğun yerde dur, "+GetSexPhrase("yolcu","kız")+"!) Silahına dokunma ve ani hareketler yapma!","Olduğun yerde dur, "+GetSexPhrase("yolcu","kız")+"! Burası bir geçiş yolu. Geçmek istiyorsan, geçiş ücretini öde."),LinkRandPhrase("Hey, "+GetSexPhrase("dostum","kız")+"! O kadar da hızlı değil! Cebinin ne kadar dolu olduğunu görmek istiyorum.","Biraz yaklaşır mısın, dostum? Kesendeki altınların şıngırtısını duymak istiyorum.","Bekle, "+GetSexPhrase("dostum","kız")+"Adamlar ve ben, kesene ne kadar altın sığar diye bahse girdik. Şimdi işler şiddete varmadan önce kontrol etmemiz gerek."),"Acele etme, "+GetSexPhrase("yolcu","sevgilim")+"! Hadi içten bir konuşma yapalım, ne dersin?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Neden böyle saçmalıklar söylüyorsun?","Ne haber?","Ne diyorsun?"),"Ne demek istiyorsun?","Ne demek istiyorsun?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Eşkıyalar mı?! Harika, bir dövüş için can atıyordum!","Ah, siz haydutlarsınız! Adaletten mi saklanıyorsunuz? Görünen o ki, adalet şimdi sizi buldu...","Sana yabancıları saçmalıklarınla rahatsız etmenin görgüsüzlük olduğunu öğretmediler mi? Görünen o ki, bu dersi sana ben vermek zorundayım..."),LinkRandPhrase("Ah, sen de bayağı küstahsın, değil mi?! Umarım kılıcın dilin kadar keskindir.","Dilinizde usta olduğunuzu görüyorum, umarım kılıcınızda da ustasınız.","Ah, haydutlar! Sizin gibilerden o kadar çok kişi asıldı ki, yine de darağacına yürümekten vazgeçemiyorsunuz."),LinkRandPhrase(RandPhraseSimple("Ah, haydutlar! Bilirsin, genelde senin gibilerle lafımı boşa harcamam!","Ne terbiyesiz adam! Buharlaşan bir bok yığını gibi kokuyor ama hâlâ düzgün birine laf etmeye cüret ediyor "+GetSexPhrase("adam","kız")+"."),"Seninle lafı uzatmayacağım, ama tabancamın ne kadar etkileyici konuştuğunu göreceksin!","Yine haydutlar! İdamı sana vaat edemem ama karnında birkaç delik açabilirim!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("Ve biliyor musun, bir devriye beni yakından takip ediyor? Onlara bir ıslık çalsam, işin biterdi.",RandPhraseSimple("Biliyor musun, devriyeyi çağırabilirim. Bundan korkmuyor musun? Yakındalar. Sanırım seni arıyorlar.","Sana ulaşmak için yakın zamanda bir devriye gönderildi, her an burada olabilirler. Büyük bir risk alıyorsun."),RandPhraseSimple("I'd advise you to run as fast as you can. A patrol is heading this way; I've just spoken with their officer.","I would gladly continue our conversation, but I'm afraid the patrol unit I just met won't let our acquaintance develop into a close friendship."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("Aptallık etme! Parayı peşin ver, belki o zaman seni bırakırım!","Seyahat ücreti diye bir şey duymadın mı? Altınını vermezsen, kafandan olursun!","Heh, bu küçük macera sana bir kese altına mal olacak... tabii eğer sinirlenmezsem."),RandPhraseSimple("Çok basit. Bize tüm altınını veriyorsun ve sonra gitmekte özgürsün, ya da burada kalırsın ve biz yine de tüm altınını alırız. Ama sanırım ikinci seçenek pek hoşuna gitmez, he-he.","Anlamazlıktan gelme! Eğer keseni ölü bedeninden almak istemiyorsam, hemen ver onu bana!"),"Sana açıklayayım, madem bu kadar yavaş anlıyorsun. Eğer hayatını önemsiyorsan, bütün paranı bana ver.");
			Link.l1 = "Lanet olsun, alçak! Sadece "+makeint(makeint(Pchar.money)/20)*10+" peso.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("Parama mı göz diktin? Gel ve al, bakalım gerçekten neye değersin!","Bunu nasıl cüret edersin, kaba herif! Sana iyi davranışın ne olduğunu göstereceğim!","Ne özgüven ama! Peki, gerçek birine karşı nasıl dayanacaksın bakalım "+GetSexPhrase("deniz kurdu","Louve des mers")+"!"),LinkRandPhrase("Böyle bir rezalet için kırbaçlanmalısın!","Soysuzlar! Cehennemde sıcak bir yer için şeytanlarınıza dua edin!","Siz çoktan asılmalıydınız, cellat kuşları! Demek ki kılıcımı sizin kanınızla lekelemem gerekecek!"),RandPhraseSimple("Ve sana paramı vereceğimi düşündüren şey ne?","Ve silahlı olduğumu ve buraya sadece gezintiye çıkmak için gelmediğimi fark etmedin mi?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("Lanet olsun! Tamam, gidebilirsin. Ama burada olduğun sürece sakın ses çıkarmayı aklından bile geçirme!","Bu sefer şanslıydın, ama bir dahaki sefere bize iki katını borçlanacaksın! Bize hatırlatmayı unutma, heh-heh.");
				Link.l1 = RandPhraseSimple("Elbette.","Kaç artık, hâlâ vaktin varken.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("Seni sessizce öldüreceğiz, çıtını bile çıkaramayacaksın.","Kahretsin! Alarmı vermeden önce seni çabucak öldürmemiz gerekecek.");
					Link.l1 = "Pekâlâ, bu senin sonun olacak. Seni uyarmıştım.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("Devriyenle neden ilgileneyim ki? Onlara ben para ödüyorum. Şimdi cüzdanını ver ve çeneni kapa.","Beni korkutabileceğini mi sanıyorsun? Bu ormanda senin gibiler için devriye bizzat benim. Buradan henüz kimse bir bedel ödemeden çıkamadı!");
					Link.l1 = "Lanet olsun, alçak! Sadece "+makeint(makeint(Pchar.money)/20)*10+" peso.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("Heh, senin gibi bir zavallıdan emir alacak değilim.","Böyle bir küstahlık için kafanda birkaç yeni delik açarım! Beynini biraz havalandırmak fena olmaz.","Böylesine küstahlık cezasız kalmaz!"),"Bunu yapmamalıydın...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Hey, bu kadar heyecanlanma, "+GetSexPhrase("dostum","kız")+"! Şaka yapıyordum sadece! Yoluna devam edebilirsin!","Pekala, fikrimi değiştirdim. Eğer bu kadar güçlüysen, gidebilirsin."),"Ne, bir "+GetSexPhrase("'cesur kaptan'","'kavgacı kız'")+" ? Yine mi? Peki, huzurla git...","Sakin ol, "+GetSexPhrase("dostum","kız")+". Bakın, yanılmışız, "+GetSexPhrase(" seni bir tüccar sandık "," seni bir tüccar sandık ")+". Gidebilirsin.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("Pekâlâ, tekrar görüşene dek!","İnsanları soymayı bırakmalısın, hâlâ vaktin varken.","Pekâlâ, ama seni bir daha görürsem..."),RandPhraseSimple("Bir dahaki sefere, kime tehdit savurduğuna dikkat et, köpek.","Bugün şükürler olsun ki keyfim yerinde."),RandPhraseSimple("Bu suç dolu ticaret sonunda seni kesinlikle öldürecek. Elveda.","Bu akıllıca bir karar. Neyse, bol şans!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("Hayır, dostum. Şimdi sana biraz görgü kuralları öğreteceğim!","Korktun mu? E, insan yaptıklarının hesabını vermeli, değil mi?","Hayır! Seni canlı canlı yüzene kadar sakinleşmeyeceğim!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("Ve huzur içinde gidebilirdin! Şimdi suçlayacak tek kişi kendinsin!","Bunu başlatmamalıydın, seni serseri! Şimdi bir köpek gibi öleceksin!","Ah, pekâlâ! Seni parça parça edeceğim! Ciğerini çıkarıp köpeklere yedireceğim!");
				Link.l1 = RandPhraseSimple("Sözlerini boğazına tıkacağım!","Kime tehdit savuruyorsun, pislik?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("Pekâlâ! Onu ver ve kaybol!","Çok değil, ama hiç yoktan iyidir. Akıllı biriyle iş yapmak güzel! Gidebilirsin."),"Bu bambaşka bir hikaye! Bir arkadaşım derdi ki, 'akıllı birini dinlemek iyidir ama bir aptalla konuşmak çok daha eğlencelidir'! He-he!","Altınların karşılığında sana bir tavsiye vereceğim: Eğer   ormanda yürüyorsan dikkatli olmalısın "+GetSexPhrase("Ne korkaksın. Git meyhanede romunu iç, hem sen hem de kesen güvende kalsın!","bir kızsın. Soyulmak başına gelebilecek en kötü şey değildi.")+".");
				Link.l1 = "Lanet olsun sana!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "Beni kandırmaya mı çalışıyorsun? Merak etme, bıçağımla seni biraz gıdıklarım, belki bir şeyler dökülür.";
				Link.l1 = "Lanet olsun!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("Yine sen mi? Sinirlenmeden önce annene koş, hadi!","Ne? Hâlâ bütün altınını bana vermedin mi? Ha-ha!","Bak, "+GetSexPhrase("dostum","kız")+", senden bıktım artık! Hâlâ hayattayken gözümün önünden kaybol!");
			Link.l1 = "Evet, zaten gidiyorum.";
			Link.l1.go = "Exit";
			Link.l2 = "Haksızlık olacağını düşündüm. Bu yüzden işleri yoluna koymaya karar verdim...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("Daha ne istiyorsun? Zaten gitmene karar verdik!","Beni rahat bırak, "+GetSexPhrase("dostum","kız")+". Ben kendi işime bakarım, sen de kendi işine bak, ve birbirimizle iyi geçinmeye çalışmamalıyız!","Şimdi git, "+GetSexPhrase("dostum","kız")+"! Kahretsin, gerçekten tüm paranı vermeye razı mısın?");
			Link.l1 = "Evet, zaten gidiyorum.";
			Link.l1.go = "Exit";
			Link.l2 = "Hatırladım ki veda etmemiştin! O halde şimdi düzgünce vedalaşalım...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("Beni rahat bırak! Yardım edin! Yaşamak istiyorum!","Bana yardım et! "+GetSexPhrase("O bir manyak","O tam bir deli")+"! Beni öldürme!","Beni bağışlayın! Ben sadece sıradan bir haydutum! Ölmek için çok gencim!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("Evinde kalsaydın, hâlâ yaşıyor olurdun!","Bunu daha önce düşünmeliydin!","Bunun her zaman bir bedeli olacağını bilmeliydin!"),"Er ya da geç, bunun olacağı belliydi.","Pişman olmak için çok geç, şimdi dövüş, pislik!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
