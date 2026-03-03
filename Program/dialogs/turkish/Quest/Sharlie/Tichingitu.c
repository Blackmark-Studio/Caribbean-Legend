// Тичингиту - индеец-офицер
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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ne istiyorsun?";
			link.l1 = "Hiçbir şey.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Ne istiyorsun, solgun yüzlü? Tichingitu'nun sana söyleyecek hiçbir şeyi yok.";
			link.l1 = "Adın Tichingitu mu? Hm. Dinle, savaşçı, buraya sana bakmaya gelmedim. Sana bir soru sormaya geldim: O şişman adamın evine neden girdin?";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "";
			link.l1 = "Hiçbir şey söylemiyor musun? Akıllıca değil. Hırsızlık ve yaptığın diğer her şey için asılacaksın. Bana neden böyle bir şey yaptığını anlat, belki sana yardım edebilirim.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Tichingitu, solgun yüzlülerin kasabasına nice yollardan, engin denizlerden, uçsuz bucaksız ormanlardan ve bataklıklardan geldi. Tichingitu yorgundu ve yemek yemek istiyordu. Tichingitu açlıktan ölüyordu. Kimse Tichingitu'ya yardım etmek istemedi. Bağırdılar: 'Defol git, kızıl derili köpek.' Meyhane sahibi, Hintliyi serseri bir köpek gibi dışarı attı. Tichingitu yemek yemek istiyordu.";
			link.l1 = "Lanet olsun, ama neden... ormandan çıkıp bu yerleşkeye geldin?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Tichingitu, yerli kabileden kovuldu. Kabilenin şamanıyla kavga etti, şaman her şeyi reise anlattı, Tichingitu'ya lanet okudu. Tichingitu kabileyi terk etti, ana topraklardan çok, çok uzağa gitti. Tichingitu'nun ne evi var, ne silahı, hiçbir şeyi yok.";
			link.l1 = "Buna gerçekten talihsizlik denir. Kendi insanlarınla neden kavga ettin?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Kabilenin şamanı kötü bir adam. Karımın bedenine kötü bir ruh girdiğini söyledi. Karımın ölmesi gerektiğini söyledi. Ama karım sadece hastaydı, içine hiçbir ruh girmemişti. Tichingitu karımı iyileştirmeye çalıştı, ama şaman onu öldürdü. Tichingitu şamana karşı çıktı, sonra herkes Tichingitu'ya sırtını döndü, bu yüzden Tichingitu gitti.";
			link.l1 = "Karını kurtarmaya mı çalıştın? Bu yüzden mi köyden kovuldun?";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Evet, solgun yüz. Tichingitu'nun başka seçeneği yok. Ya çalacak ya da açlıktan ölecek...";
			link.l1 = "Yani, ne diyeyim... Açlıktan birkaç kuruş çalan bir adam için darağacı... Tichingitu, sana yardım etmeye çalışacağım. O iri yarı adam Fadey'i tanıyorum, hani gizlice evine girdiğin adamı. Belki bir şeyler yapabilirim... Gidip komutanla konuşacağım.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_1");
		break;
		
		case "Tichingitu_wait":
			dialog.text = "Tichingitu bekle. Kızılderili ölümden korkmaz. Şaman Tichingitu'yu lanetledi, Tichingitu ölmek zorunda.";
			link.l1 = "Her şey henüz kaybolmuş değil. Yardım etmeye çalışacağım...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_wait";
		break;
		
		case "Tichingitu_6":
			DelLandQuestMark(npchar);
			dialog.text = "Tichingitu bekliyor. Kızılderili ölümden korkmaz. Şaman Tichingitu'ya lanet etti, Tichingitu ölmek zorunda.";
			link.l1 = "Kötümser olmana gerek yok. Hapis hayatın sona erdi. Seni özgürlüğüne kavuşturmama yardım ettiler.";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			dialog.text = "Beyaz suratlı şaka mı? Tichingitu özgür mü?";
			link.l1 = "Hayır, şaka yapmıyorum. Hücreni açıp seni dışarı çıkaracaklar. Beni takip et, seni hapishaneden çıkaracağım.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tichingitu_DlgExit_2");
		break;
		
		case "Tichingitu_9":
			dialog.text = "";
			link.l1 = "İşte yine özgürsün. Hadi bakalım, Tichingitu, bir daha bir şey çalmamaya ve başını belaya sokmamaya dikkat et! En iyisi bir Kızılderili köyü bulup kendi halkınla yaşaman olur, sanmıyorum ki seni aralarına almaya karşı çıksınlar.";
			link.l1.go = "Tichingitu_10";
		break;
		
		case "Tichingitu_10":
			dialog.text = "Tichingitu gitmez. Efendi Tichingitu'nun hayatını kurtardı. Tichingitu kalır. Tichingitu'nun hayatı efendiye ait.";
			link.l1 = "Ha? Ne diyorsun sen? Hangi efendi, hangi hayat? Ne dediğimi anlamıyor musun? Özgürsün! Hadi git!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Hintli'nin borcu var, beyaz efendi. Tichingitu sana sadakat ve dürüstlükle hizmet eder. Tichingitu savaşmayı bilir. Tichingitu efendisi için savaşta ölecek. O burada kalır.";
			link.l1 = "Aman Tanrım! Kahretsin... Ben sana nasıl bir efendiyim, Tichingitu? Sana yardım ettim, seni köle yapmak için değil.";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu köle değil. Tichingitu özgür bir Kızılderili. Tichingitu sana hizmet etmek istiyor. Tichingitu dövüşmeyi bilir, hiçbir köpek efendisine yaklaşamadan ölür. Tichingitu tüfeği nasıl temizleyeceğini ve dolduracağını bilir. Tichingitu tüfekle ateş edebilir.";
			link.l1 = "Gerçi... Biliyor musun Tichingitu, bu o kadar da kötü bir fikir değil. Bana sadık insanlar lazım ve sen de kötü biri gibi görünmüyorsun. Üstelik tüfek kullanmayı da biliyorsun. Hem, tek başına ne yapacaksın ki? Sonunda yine bir şey çalarsın ve bir dahaki sefere kesin asılırsın... Peki, kalabilirsin. Ama unutma: benimle hayat sakin geçmeyecek.";
			link.l1.go = "Tichingitu_13";
			link.l2 = "Pekâlâ, yeter. Huzurla git, kızıl tenli kardeşim. Tanrıların seni korusun!";
			link.l2.go = "Tichingitu_exit";
		break;
		
		case "Tichingitu_exit":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_DlgExit_3");
		break;
		
		case "Tichingitu_13":
			dialog.text = "Tichingitu hiçbir şeyden korkmaz, beyaz efendi. Tichingitu sana hizmet etmekten memnun. Tichingitu son nefesine kadar sadıktır.";
			link.l1 = "Pekâlâ. Mürettebata hoş geldin, Tichingitu!";
			link.l1.go = "Tichingitu_hire";
		break;
		
		case "Tichingitu_hire":
			DialogExit();
			AddDialogExitQuestFunction("Tichingitu_Hire");
		break;
		
	//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Tichingitu_officer":
			dialog.text = "Tichingitu seni dinliyor, Kaptan "+pchar.name+"!";
			// Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = ""+npchar.name+", kaptan "+pchar.name+"’in gözlerinde bir kafa karışıklığı görüyor.";
				Link.l1 = "Sen her zaman içimi okursun dostum. Anla, eve dönmem gerekiyor — Avrupa’ya. Zor bir karar verdim: başkasının gemisiyle, bir yolcu olarak yelken açacağım.";
				Link.l1.go = "SharlieEpilog_Tichingitu_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Tichingitu, Tayasal adında eski bir Kızılderili köyüne gitmek üzereyim. Sana yalan söylemeyeceğim, bu yolculuk son derece tehlikeli ve alışılmadık: bir teleportasyon putu aracılığıyla. Sen... Benimle gelir misin?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Tichingitu, gemideki durumu bana ayrıntılı olarak anlat.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Her limana yanaştığımızda belirli malları satın almanı istiyorum.";
				Link.l12.go = "QMASTER_2";
			}

			Link.l1 = "Emirlerimi dinleyin!";
            Link.l1.go = "stay_follow";
			link.l2 = "Şu anda bir şey yok. Rahat ol!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Gemi raporu mu? Tichingitu'nun raporu yok, efendim. Sadece silahı ve kıyafetleri var. Tichingitu hiçbir yerden rapor almadı.";
			Link.l1 = "Pekâlâ, neyse.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Efendim, Tichingitu sensiz asla bir koloninin içine adım atmaz. Tichingitu bir dükkâna girince - herkes yine Tichingitu'yu hırsız sanıyor. Sonra da, hapishane.";
			link.l1 = "Evet, muhtemelen haklısın. Yine o hapishane meselesi mi? Hem, kimse senin bir muhasebeci olduğuna inanmaz zaten.";
			link.l1.go = "exit";
		break;
		
		case "stay_follow":
            dialog.Text = "Ne emretmek istersiniz?";
            Link.l1 = "Burada dur!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve geride kalma!";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ateşli silahınız için mühimmat türünü değiştirmeniz gerekiyor.";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "Tüfeğiniz için cephane türünü değiştirin.";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "Yakın dövüş için ana silahını değiştir.";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "Hedefe uzak durmanı istiyorum.";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Mühimmat türünü seç:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
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
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Kullanılacak mühimmat türünü seç:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "Savaşın başında şunları kullanacaksın:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Plan değişti!";
            Link.l1 = "Rahat ol.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Plan değişti!";
            Link.l1 = "Rahat ol.";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "Ne kadar kaldı, Kaptan? Tichingitu'ya kaç yarda olduğunu söyle, ama yirmiden fazla olmasın.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Kaptan, Tichingitu'yu bağışlayın, ama sizi anlamıyorum.";
				link.l1 = "Üzgünüm, benim hatam...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Tichingitu öylece duruyor, hiç hareket etmiyor. Bunu mu istiyorsunuz, Kaptan?";
				link.l1 = "Evet, tam olarak öyle.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Tichingitu hedefinden yirmi yarddan fazla uzaklaşamaz. Sonra da ıskalar.";
				link.l1 = "Pekâlâ, aramızda yirmi adım mesafe bırak.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Tichingitu her şeyi anladı. Tichingitu, söylediğiniz görevi üstlenecek.";
			link.l1 = "Güzel.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Tichingitu'nun hayatı, uzun zamandır, Kaptanımın hayatı oldu. Kızılderili, Kaptanın Tichingitu için yaptıklarını unutmaz. Tichingitu, Kaptan nereye derse oraya, sorgusuz sualsiz peşinden gider.";
			link.l1 = "Teşekkür ederim, dostum!";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ne zaman yola çıkıyoruz?";
			link.l1 = "Biraz sonra. Şimdilik yolculuğa hazırlanmamız gerekecek.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "21");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Beyaz adama yüz dublon öderiz, gideriz ve işimizi özgürce bitiririz.";
			link.l1 = "Ya tekrar yakalanırsak?";
			link.l1.go = "tonzag_jailed_1";
			locCameraFromToPos(-16.78, 1.88, -1.70, true, -5.00, -6.10, -20.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Bin doblon ödüyoruz.";
			link.l1 = "Alaycı, ama çok da sezgili.";
			link.l1.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Guadeloupe daha da kötü.";
			link.l1 = "Nasıl yani?";
			link.l1.go = "tonzag_jailed_3";
		break;
		
		case "tonzag_jailed_3":
			dialog.text = "Orada, sadece Tichingitu'yu asmak istiyorlar. Burada ise birden fazlasını. O kadar da kötü değil.";
			link.l1 = "Bu artık düpedüz alaycılık!";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Tam isabetli atış. Kaptan, yaşlı adam güçlü, hızlı davranırsak onu kurtarabiliriz.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
			AddDialogExitQuestFunction("Tonzag_JailFear");
		break;
		
		case "tonzag_dead":
			dialog.text = "Beyaz adam hiç merhamet göstermiyor. Benimkilerden pek çoğu, Kaptan. Çok fazla. Ama seninkiler, daha da fazla.";
			link.l1 = "Bunlar senin kabileden mi?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Bazıları... bazıları benim.";
			link.l1 = "Dayan dostum.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Tichingitu_officer";
		break;
		
	// Тичингиту говорит о том, что нужно спасти Делюка
		case "Del_Deluck":
			dialog.text = "Bir 40 doblon daha mı?";
			link.l1 = "Ha? Yine Deluc'un hapisten çıkması için para ödeyip ödemeyeceğimi mi soruyorsun?";
			link.l1.go = "Del_Deluck_1";
		break;
		
		case "Del_Deluck_1":
			dialog.text = "Evet.";
			link.l1 = "Ben de pek emin değilim... Sence nasıl?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Onu kurtarmalıyız.";
			link.l1 = "Bu onurlu bir davranış. Kendi insanını asla geride bırakmazsın, değil mi?";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "Ya da bırak onu. Ormanda zayıfı jaguara bırak.";
			link.l1 = "Kim?";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			dialog.text = "Büyük kedi.";
			link.l1 = "Tichingitu, seni anlamakta zorlanıyorum. Sadece bana söyle: Bu durumda ne yapmalıyım?";
			link.l1.go = "Del_Deluck_5";
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Kendi kafanı kullan.";
			link.l1 = "Çok yardımcı oldun!";
			link.l1.go = "Del_Deluck_6";
		break;
		
		case "Del_Deluck_6":
			DialogExit();
			AddQuestRecord("FolkeDeluc", "2");
			ReturnOfficer_Tichingitu();
		break;
		
		// Эпилог
		case "SharlieEpilog_Tichingitu_1":
			dialog.text = "Kaptan "+pchar.name+", "+npchar.name+"’i yanında götürmeyecek mi?";
			link.l1 = "Sen benim dostumsun, "+npchar.name+", ve tabii ki seni bu yolculuğa davet ediyorum. Ama anlamalısın ki Eski Dünya’daki insanlar yerlileri görmeye alışık değiller. Sana parmakla işaret edecekler ve seni kölem sanacaklar — ve ona göre davranacaklar.";
			link.l1.go = "SharlieEpilog_Tichingitu_2";
		break;

		case "SharlieEpilog_Tichingitu_2":
			dialog.text = ""+npchar.name+" bunu umursamaz. "+npchar.name+", soluk benizlilerin yerlilerden nefret ettiğini bilir ve kaptan "+pchar.name+"’i verdiği söz gibi — son nefesine kadar takip eder.";
			link.l1 = "Herkes yerlilerden nefret etmiyor. Ama çoğu kuşkuyla bakıyor — bu, inançlarını yabancı olana karşı koruma şekilleri. Her halükârda, kimsenin seni küçük düşürmesine ya da kölem sanmasına izin vermem. Eminim ki kabilelerinden kimse Avrupa’yı görmemiştir — o lanetli şaman bile en çılgın rüyalarında bunu hayal etmemiştir.";
			link.l1.go = "SharlieEpilog_Tichingitu_3";
		break;

		case "SharlieEpilog_Tichingitu_3":
			dialog.text = "Maskoke yerlisi denizci değildir. Avrupa’ya asla ulaşamaz. Duymuştum: büyük kano oraya gitmek için iki dolunay süresi alır.";
			link.l1 = "Evet, "+npchar.name+", ve bu rüzgar yanımızda olursa. Bu kolay bir yolculuk değil. İki hafta içinde yola çıkıyoruz... ve bizimle geliyor olmandan memnunum. Bu vesileyle meyhanede küçük bir kutlama yapmayı planlıyorum. Ateş suyunu sevmediğini biliyorum ama yine de bizimle olursan mutlu olurum.";
			link.l1.go = "SharlieEpilog_Tichingitu_4";
		break;
		
		case "SharlieEpilog_Tichingitu_4":
			dialog.text = ""+npchar.name+" gelecek. Ama belki daha iyisi — kutlamalı bir baskın mı?";
			link.l1 = "Ha-ha. Bu sefer olmaz, dostum — zamanı değil. Başladığımızda sana haber vereceğim. Şimdi gitmeliyim — işlerim var.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tichingitu_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tichingitu = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
