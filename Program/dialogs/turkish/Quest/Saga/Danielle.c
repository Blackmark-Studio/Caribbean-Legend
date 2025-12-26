// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

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
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "Dur biraz, yakışıklı! Sanırım konuşmamız gerek.";
			link.l1 = "Sizi tanıyor muyum? Neyse, bir hanımefendi için her zaman birkaç saatim vardır.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "Henüz plan yapma, Kaptan. Kendine birkaç saatliğine daha genç, saf görünümlü bir kız bul. Sana bir işim var. Aslında evliyim. Kocamın adı Nathaniel Hawk.";
			link.l1 = "Ne ilginç! Demek sen o... şey, Dannie Hawk'sın, Bay Svenson senden bahsetmişti.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Karşında duruyorum. Evet, Orman Şeytanı'nın benim hakkımda pek iyi düşünmediğini biliyorum—duygular karşılıklı—ama sana uyarı vermesi gerekiyordu: ben kılıcımı sadece süs olsun diye taşımıyorum. O yüzden lafı dolandırma, oğlum!\nBir süredir Svenson'u ve misafirlerini takip ediyorum, çünkü kocamı ormanda ölüme gönderen oydu. Önce Jackman'la işbirliği yaptığını sanmıştım, ama şimdi öyle olmadığını görüyorum. Konuşmanız sırasında pencerenin altında saklanıyordum. Her şeyi duyamadım ama birçok faydalı bilgi öğrendim.\nGerçekten kocamı bulmaya ve Jackman'a haddini bildirmeye kararlı mısın? Yoksa sadece büyük laflar mı ediyordun?";
			link.l1 = "Başkalarının konuşmalarını gizlice dinlemek doğru değil, Madame Hawk. Ama bana daha saygılı hitap ederseniz sizi affederim. Hawk'ı arayıp aramadığım yalnızca beni ilgilendirir. Söyleyecek faydalı bir şeyiniz varsa konuşun, yoksa beni rahat bırakın. İkinci kez sormam.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A-ha, ne kadar da ateşlisin! Hadi ama, Kaptan... Sinirim seni rahat ettirmiyor, orası kesin. Korkak olmadığını ve kendi değerini bildiğini görüyorum. O halde... tanışalım. Sana söz veriyorum, bundan sonra sana karşı daha dikkatli olacağım. Sana ihtiyacım var, senin de bana. Aynı amaçları paylaşıyoruz. Beni tayfana al, pişman olmazsın. Nathan'ı bulana kadar sana sadakatle ve dürüstlükle hizmet edeceğim, sana söz veriyorum.";
			link.l1 = "Kabul edildiğini bil... Dannie. Svenson bana kocanı zaten aramaya başladığını söyledi. Dikkatini çeken bir şey buldun mu?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Çok değil, ama Jackman'ı yalan söylemekle suçlamaya yeter. O alçak, Nathan’ımın karşılaştığı madenin muhafızlarının esir almadığını söylemişti. Gerçi kimse kocamın cesedini körfezde görmedi, ama nasıl görebilirdi, çünkü aslında onu esir olarak madene götürmüşler. Miskito halkından bir şaman olan Yılan Göz, onu orada bulmuş.\nKaçmasına da yardım etmiş. Ama kocamın şimdi nerede olduğu hâlâ bilinmiyor. Şaman, onu yiyen bir Kukulcan’dan falan bahsedip duruyordu, ama hiçbir şey anlamadım. Ayrıca, yerliler beyaz kadınları ciddiye almıyor, bunu da açıkça belli etti. Sen onunla konuşmalısın, belki sana daha açık olur.";
			link.l1 = "Hiç yoktan iyidir! Böyle bir haber beni mutlu ediyor. Bu Hintliyi nerede bulabilirim?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ormanın derinliklerinde bir köy var. Amatique Körfezi'ne çıkmamız ve ormandan batıya gitmemiz gerekiyor. Eğer yolu bulamazsan, sana gösteririm. Köyün çok uzağında olmayan bir yerde taş bir put var, yerliler onu tanrı olarak görüyor. Ben oraya birkaç kez gittim. Aslında pek bir özelliği yok. Sadece yosun kaplı basit bir taş.";
			link.l1 = "İlginç. Peki, gidelim. Şamanla konuşup ne yapacağımıza bakarız. Hazır mısın?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Elbette! Tabii ki hazırım. Maroon Town'dan ayrıldığımdan beri yollardayım zaten. Ayrıca, senin sıradan yolcularından biri olmak istemiyorum.";
			link.l1 = "Pekâlâ. Gemime gidelim.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+" ! Hadi! Sana Kızılderili şamanın bahsettiği taş putu göstereceğim. Sıradan bir taş sütun işte. Hadi gidelim!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "Hey! Şuna bak, bu sadece taş bir heykel. Hiçbir özelliği yok...";
			link.l1 = "Anlıyorum... Ama en üstteki figür biraz ürkütücü değil mi, sence de? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "Tüm Kızılderili heykelleri korkutucu ve uğursuz görünüyor. Daha önce de buna benzer bir şey görmüştüm. Hepsi birbirinin aynısı. Neyse, hadi gidelim, köy yakında!";
			link.l1 = "Hadi gidelim!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "Peki, ne diyorsun, "+pchar.name+"? O kızıl derili karagöz ustası sana ne söyledi? Onun felsefi laflarından bir şey alabildin mi?";
			link.l1 = "Yine gizlice mi dinliyordun, Dannie?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "Yani... biraz. Bilirsin, biz kadınlar böyleyiz işte. Ama anlamalısın – sadece kocam için endişeleniyorum. Onu gerçekten seviyorum. Yani ne olmuş yani, kulak misafiri oluyorsam? Neyse, işe yarar bir şey öğrendin mi?";
			link.l1 = "Düşünüyorum... Yılan Gözlü'yü anlamak kolay değildi. Yine de, köye girerken gördüğümüz o putun bir tür sihirli geçit olduğunu ve insanları bir yerden bir yere ışınlayabildiğini anladım.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "Bana öyle bakma. Bu benim fikrim değildi ve şimdiye kadar başımla ilgili bir sorun yaşamadım. Bana şamanın ne dediğini sordun, ben de anlatıyorum.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "Lütfen, beni affedin. Artık size öyle bakmayacağım. Devam edin.";
			link.l1 = "Nathan neredeyse peşindekilere yakalanacakken, Hintli ona kurtuluş yolu olarak heykeli göstermiş, ona Kukulcan demiş ve Nathan’ı tamamen yutup başka bir yerde geri çıkardığını söylemiş. Kısacası, Nathan heykel sayesinde bir yerden başka bir yere ışınlanmış gibi görünüyor.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "Tanrım, bu da ne... Nathan'la ben daha önce de benzer bir belaya bulaşmıştık, şimdi yine başımıza geliyor. O Maya büyüsüyle dolu Hint tapınağında yaşadıklarımız yetmemiş gibi...";
			link.l1 = "Az önce ne dedin?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "Ah, önemli bir şey değil, "+pchar.name+", önemli değil. Sadece çılgın gençliğimin anıları. Ama Nathan bunu nasıl başardı? Yani, nasıl ışınlandı? Biz o putun yanındaydık, ben etrafında dolaşıp ona dokunuyordum... sonuçta o sadece bir taş!";
			link.l1 = "Yılan Göz bana putun gece yarısı canlandığını söyledi. Ancak o zaman Kukulcan'ın ruhu içine girdiğinde altın bir ışıkla parlamaya başlıyormuş. İşte o an ona dokunmamak gerekirmiş. Ya da belki de dokunmalı...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "Uğursuz... Şimdi ne yapacağız? Gece yarısını bekleyip sonra ormana mı gireceğiz?";
			link.l1 = "Hayır. Şaman, bu idolün sadece insanları ışınlamakla kalmayıp, aynı zamanda onların yaşamlarını da tükettiğini söyledi. Onu anladığım kadarıyla, sağlığını emdiğini kastetti. Yılan Göz bu heykellerden üç kez geçti ve her ışınlanmadan sonra kendine özgü bir iksirle iyileşti.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "Bu iksiri ondan istedin mi?";
			link.l1 = "Tabii. Ama öncelikle, sadece üç şişe kaldı ve ayrıca, onları almak için üç muska istedi.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "Bunu iksir olmadan yapmaya ne dersin? Gece heykelin yanına gidip ona dokunalım...";
			link.l1 = "Çok riskli. Kızılderilinin biraz deli ve bizi kandırıyor olabileceğini kabul ediyorum, ama bir psikopat gibi görünmüyor, bu yüzden doğruyu söylediğine inanıyorum. Bana Kızılderili büyüsüyle ilgili bir şeyler anlatıyordun... Onun varlığından şüphe mi ediyorsun?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "Evet, öyleydim. Buna hiç şüphem yok, çünkü kendi gözlerimle gördüm. Yani, sanırım haklısın, riske atmanın bir anlamı yok.";
			link.l1 = "Aynen öyle. Bu yüzden önce tılsımları bulacağız, sonra o harika iksiri şamandan alıp heykele gideceğiz. Ben gideceğim. Yalnız.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "Neden böyle?   Peki ya ben?";
			link.l1 = "Ben yokken gemimde kalacaksın ve burada sen sorumlu olacaksın. Tartışmaya bile kalkışma, Dannie. İksirden sadece üç şişe var. Eğer şaman haklıysa ve bu şey gerçekten işe yarıyorsa, portalın nereye açıldığı bile belli değil. Belki de orada Nathan'ı bulamayacağım.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "Sen de Nathan gibisin. Bütün erkekler aynı... Peki, kabul ediyorum.";
			link.l1 = "Birbirimizi anladığımıza sevindim. Şimdi gidelim, muska­ları bulmamız gerekiyor.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "Peki ne olmuş? İksirleri aldın mı?";
			link.l1 = "Evet. İksirleri ve bazı talimatları aldım. Geriye sadece gece yarısı putun yanına gidip ona dokunmak kaldı.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "Korkuyor musun?";
			link.l1 = "Evet. Korkarım ki şaman sadece deli çıkabilir ve hiçbir şekilde ışınlanma gerçekleşmeyebilir.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "Pekâlâ, pekâlâ... Hiç mi korkmuyorsun? Azıcık bile mi?";
			link.l1 = "Dannie, üstüme fazla gelme... Gerçekten bilmek istiyorsan, evet, kendime pek güvenmiyorum, itiraf etmeliyim.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "Seninle geleceğim.";
			link.l1 = "Yine tartışmaya mı başlayacaksınız? Anlaştık sanmıştım...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "Beni yanlış anladın. Sadece yanında kalacağım. Heykelin işe yarayıp yaramadığından emin olmam gerek...";
			link.l1 = "Bir itirazım yok. Ama heykel beni 'yutarsa' peşimden gelmeyi aklından bile geçirme. Duydun mu?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "Evet. Söz veriyorum, peşinden gitmeyeceğim... Kaptan.";
			link.l1 = "Güzel. Ve Dannie, söylendiği kadar cadaloz olmadığın anlaşılıyor.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "Beni pek tanımıyorsun, "+pchar.name+". Ama şimdi bundan bahsetmeyelim.";
			link.l1 = "Hadi... Neyse, gece yolculuğumuz için hazırlanalım!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "Bak, "+pchar.name+"! Kutsal olan her şey adına yemin ederim, heykelin üzerinde garip bir ışık var!";
			link.l1 = "Şaman yalan söylememiş gibi görünüyor. Ve eğer karanlık beni yanıltmıyorsa, heykelin tepesi artık o kadar taş gibi görünmüyor.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "Kesinlikle... Saf altından yapılmış gibi görünüyor! İnanılmaz!";
			link.l1 = "Zamanı geldi, Dannie. Bana şans dile ve benim için parmaklarını çaprazla. İdole yaklaşma! Burada kal.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "İyi şanslar, "+pchar.name+". Umarım bu işe yarar... Şamanın iksirini hazırladın mı?";
			link.l1 = "Evet, burada. Her şey yoluna girecek, Dannie. Peki, gidiyorum! (Put T'ye basarak idolü etkinleştir)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "A-a-ah?! Lanet olsun! Sen ne biçim bir yaratıksın, Allah kahretsin?! Defol git! Hayatımda daha beter mahluklar gördüm, Van der Decken'ın kendisi dahil! Şimdi istediğini alacaksın!";
			link.l1 = "(kısık sesle) Dannie, dur! Yeter artık! Şimdi!";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(fısıltıyla) Van der Decken mi? Ha-ha-ha-ha! O zavallı solucan zaten bana hizmet ediyor! Şimdi sıra sende! Önümde eğil, sadık hizmetkâr! Ölüler orduma sen komuta edeceksin!";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "A-A-A-A-A-A-A-A-A-A-A-A-A! Git buradan! Şu an bu olamaz!";
			link.l1 = "(kısık sesle) Danny, dur! Yeter artık! Şimdi!";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "Ne?! Ne dedin?! Dannie?";
			link.l1 = "(kısık sesle) Hemen durun! Kılıcınızı indirin! Şunu çıkarmama izin verin!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "Lanet olsun, canavar, kulağa... "+pchar.name+"?!";
			link.l1 = "(hafifçe) Aa... Demek öyle!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "Az kalsın ödümü kopardın! Kılıcımla seni doğramama ramak kalmıştı!";
			link.l1 = "Bunu gördüm... ve neden bu kadar ateşlisin, ha?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "Ben buyum işte... Ah, kalbim hâlâ göğsümden fırlayacak gibi atıyor...";
			link.l1 = "Dannie, şimdi neredeyiz? Miskito köyüne çok uzak değiliz, değil mi?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "Başka nerede olabilirdik ki! Seni ortadan kaybeden heykel işte bu. Muhteşemdi! Bunu hayatım boyunca unutmayacağım.";
			link.l1 = "Anladım, bütün bu zaman boyunca beni burada mı bekledin?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "Bana söyle, başka ne yapabilirdim ki? Heykel seni yuttuktan sonra, tek umudum bir gün seni geri çıkaracağıydı. Hem, Yılan Göz bunun en olası sonuç olduğunu söyledi.\nMiskitolarla yaşadım ve her gün o putu izledim. Neden böyle saçmalıklardan bahsediyoruz ki? Söylesene! Orada ne oldu? Neredeydin?";
			link.l1 = "Dannie, bu hikaye çok uzun, o kadar çok şey gördüm ki... Ama içimi dökmek için söyleyeyim, Nathaniel'i buldum!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "Nathan'ı buldun mu? Nerede o? Peki, nasıl?!";
			link.l1 = "Yalan söylemeyeceğim - hayatta, ama durumu çok kötü. Comanche iksiri yoktu ve put bütün gücünü emmiş. Tuhaf Terkedilmiş Gemiler Adası'nda, eski, harap bir geminin kamarasında yatıyor. Ben de oraya ışınlandım, yani Yılan Göz haklıymış!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "Zavallı Nathan... O lanetli ada nerede? Oraya nasıl gideceğiz?! Sadece put aracılığıyla mı? Miskitoların elindeki bütün sağlık iksirlerini almaya çalışacağım ve bu gece oraya gideceğim! Bir şekilde başaracağım...";
			link.l1 = "Dur! Bekle! Nathan hasta, ama hayatı tehlikede değil. Bir çocuk ona bakıyor ve yemek veriyor. Eğer putun içinden geçersen sağlığını mahvedersin, ada gerçekten tehlikeli. Bu çok riskli!";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "Peki ne öneriyorsun? Nathan acı çekerken, hatta belki de ölürken hiçbir şey yapmayalım mı diyorsun?";
			link.l1 = "Panik yapmayı bırak. Birincisi, sana Nathan'ın hasta olduğunu söyledim, ama ölmek üzere değil. Onunla konuştum. İkincisi, adaya yelken açacağım ve sen de benimle geleceksin.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "O adanın nerede olduğunu biliyor musun?";
			link.l1 = "Elbette, biliyorum! Orada yalnızca Nathan'ı değil, Shark Dodson'ı da buldum. Adanın yaklaşık koordinatları ve çevresindeki resifleri aşmak için rotalar elimde. Şimdi gemime dönüp Blueweld'e doğru yelken açacağız...";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "Ne amaçla? Neden şimdi doğrudan adaya yelken açamıyoruz?";
			link.l1 = "Dannie, bir sefer düzenlemem gerekiyor. Adada ciddi bir erzak sıkıntısı var, bu yüzden bulabildiğim kadar yiyecek satın alacağım. Sonra oraya gitmek için bir gemi seçmem gerekecek, çünkü her gemi adanın resiflerinde yol alamaz. Ayrıca önce Svenson'la da konuşmak istiyorum...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "Hazırlanmak çok uzun sürmeyecek. Ada buradan uzak değil, Havana'nın kuzeybatısında, Meksika Körfezi'nin doğusunda.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "Pekâlâ... o zaman başlayalım. Nathan'ı bulmuşsun ve bu en önemli şey. Teşekkür ederim! Orada kendini iyi hissetmiyor mu?";
			link.l1 = "Şey... hasta. Üstelik, morali de bozuk ve umutsuz. Seni özlüyor. Ve evet, Nathan seni çok sevdiğini söylememi istedi.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(gözyaşını silerek) Ah, yaşlı budala! Hiçbir zaman beni dinlemedi... "+pchar.name+", hadi gemine gidelim! Bir an önce yelken açmak istiyorum!";
			link.l1 = "Tabii, Dannie. Ben de sana maceralarımı anlatırım. Hadi gidelim!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "Böyle bir yeri daha önce hiç görmemiştim. Bütün ada gemilerden oluşuyor!";
			link.l1 = "Sana bundan bahsetmiştim, Danny...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "Ama şimdi bunu kendi gözlerimle görebiliyorum. Neyse, bana Nathaniel'i nerede bulabileceğimi söyle?";
			link.l1 = "O gemilerden birinin içinde. Ama oraya yüzerek gitmelisin.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "Umurumda değil. Bu gemiye nasıl gideceğimi söyle.";
			link.l1 = "Dannie, calm down. You and Nathan have been waiting for a long time, so just have a bit more patience! I will lead you to him; you will never find him on your own. I don't want you to run into the Narwhals or Rivados; you'll start arguing with them and it won't end well.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "Pekala, o zaman gidelim. Seni takip edeceğim.";
			link.l1 = "Unutma, çok yüzmemiz gerekecek.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "Sorun yok, halledebilirim.";
			link.l1 = "Bunu duyduğuma sevindim... Kocanı yakında göreceksin!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "Nathaniel... Nathan! Kahretsin! Sevgilim...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "Tanrım, kendine bir bak... Neden bunu kendine yaptın?!..(ağlıyor) Beni asla dinlemiyorsun, asla! O ormana gitme dedim sana! Ama yine de gittin! Neden, Nathan?!";
			link.l1 = "Dannie... Üzgünüm. Başka seçeneğim yoktu, bunu biliyorsun...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "Bunu biliyorum! Tanrım, sevgilim... sana ne olmuş! (gözyaşları içinde) Tamam, canım, her şey yoluna girecek... Ben buradayım. Seni Miskito'ya, Yılan Gözü'ne götüreceğiz. "+sld.name+"  bana şamanın seni iyileştirebileceğini söyledi. Bir gemimiz var... Her şey yoluna girecek!";
			link.l1 = "Dannie, sevgilim... aşkım! Varlığın beni ancak yarı yarıya iyileştirdi. Nereye istersen oraya gideriz. Eğer Yılan Göz'e gitmemiz gerekiyorsa, oraya gidelim.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "Eşyalarını topla. Ah, ne aptalım... Toplanacak hiçbir şey yok, sadece boş şişeler. Nathan...";
			link.l1 = "Dannie...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ... Nathan ve bana o sahne için affet.";
			link.l1 = "Dannie! Seni affetmemi mi istiyorsun? Sorun yok. Duygularından utandın mı?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "Hayır, değilim... Sadece...";
			link.l1 = "Bu sahneden kimsenin asla haberi olmayacak. Söz veriyorum. Ve Nathan'a ne olduğunu da kimse bilmeyecek. Maroon Town'ın korsanları güçlü ve korkusuz bir Nathaniel Hawk görecek!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "Teşekkür ederim, "+pchar.name+"! Sana borçlandım... Kocamı gemiye götüreceğim. Merak etme, oraya götürmeyi başarırım, yolu hatırlıyorum. Onu bir yatağa yatırıp yanında kalacağım. Buradaki işlerini bitirdiğinde Yılan Gözü'ne yelken açarız. Nathan, iyileşeceğine inanıyorum.";
			link.l1 = "Pekala, Dannie. Zaten burada uzun kalmayacağız. Emin misin, yardıma ihtiyacın yok mu?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "Eminim. Gemiye ulaşacağız. Merak etme, kocamın ölmesine izin vermem!";
			link.l1 = "Dannie, sen... harikasın!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(gözyaşını silerek) Git... sadece git, "+pchar.name+"... ve lütfen burada hiç vakit kaybetme!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "Ee, ne olmuş yani? Kocamı iyileştirecek mi? Söylesene, onu iyileştirecek mi!";
			link.l1 = "Dannie, Nathan burada kalmak zorunda. Yalnız. Şaman ayinleri sırasında rahatsız edilmemesini istedi. Bu senin için de geçerli. Nathaniel’i bir ay içinde iyileştireceğine söz verdi.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "Biliyor musun, "+pchar.name+", şimdi nihayet tekrar özgürce nefes alabiliyorum. Şamanın kocamı eski haline döndüreceğine yürekten inanıyorum. Nathan'ı burada tereddüt etmeden bırakacağım, çünkü Yılan Göz onu iyileştiremiyorsa - kimse iyileştiremez.";
			link.l1 = "Her şey yoluna girecek, Dannie. Yılan Göz bana hiç yalan söylemedi. Ona güveniyorum.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "Ben de öyle. Bir süre seninle kalacağım, "+pchar.name+", buna razı mısın? Sonuçta hâlâ o alçak Jackman'ı bulmamız gerekiyor, tüm dertlerimizin sebebi o. Pusu kuran oydu! Maroon Town'da Nathan'ın yerine geçen de oydu! Fırkateynimiz 'Centurion'u çalan da oydu!";
			link.l1 = "Anlaştık. Jackman'la ilgilenmemiz gerek. Jackman ölmeden hiçbirimiz güvende değiliz. Onu öldürmek ise kolay olmayacak.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "Bir planın var mı, "+pchar.name+"?";
			link.l1 = "Henüz değil. Jan Svenson'a gidip ondan tavsiye almam lazım. Her şeyi sırayla yapalım, önce terfi etmeliyiz "+sTemp+" önce Kıyı Kardeşliği'nin başkanına. Yani, bunu yapmak için her korsan baronundan oy almamız gerekiyor.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "Pekala, hadi Svenson'a gidelim. Bakalım o yaşlı bunak ne diyecek...";
			link.l1 = "Biliyor musun, Jan'a bu kadar olumsuz yaklaşmamalısın. Aslında, onunla barışsan çok daha iyi olurdu... sonuçta, hepimizin amacı aynı!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "Ama sadece sana saygı duyduğum için... Peki, "+pchar.name+", üzgünüm. Svenson'a hakaret etmek istemedim, sadece gergindim. Bir daha olmayacak.";
			link.l1 = "İyi. Dannie, her şey yoluna girecek. Sana söz veriyorum!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "Sana tamamen güveniyorum, "+pchar.name+". Svenson'a gidelim mi?";
			link.l1 = "Hadi gidelim, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "Evet? Dinliyorum. Size nasıl yardımcı olabilirim?";
			link.l1 = "Jackman'ın nerede saklanıyor olabileceğine dair bir fikrin var mı? Bu herifi benden daha iyi tanıyorsun. Belki bir yeri, bir üssü vardır...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "Vallahi ben de bilmiyorum! Jacob her zaman çok gizemliydi. Onun bir sığınağı olduğunu hiç duymadım. Bence mantıklı düşünmeye çalışmak daha iyi olur... Knive'dan aldığın mektubu bir daha okuyalım. Belki orada bir ipucu buluruz.";
			link.l1 = "Deneyelim...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Şey... Isla Tesoro'dan ve bir vasiyetten bahsediyor... Sana tanıdık geliyor mu?";
			link.l1 = "Jan'la ben, Blaze Sharp'ın Isla Tesoro'da Jackman tarafından öldürüldüğünü ve suçun Shark'ın üstüne atıldığını düşünüyoruz. Ve bir vasiyet... bir kaltak... kesin Helen'le ilgili... Kahretsin, bunu daha önce nasıl göremedim! Bu herif kesin Isla Tesoro civarında dolaşıyor!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "O halde zamanımızı boşa harcamayalım, "+pchar.name+"?";
			link.l1 = "Evet. Isla Tesoro'ya gidelim. Yaşlı 'Marlin' bu baskında bize yardımcı olacak.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "O pislik sonunda öldü... İnanamıyorum - yine 'Centurion'un güvertesindeyim! Buradaki her çiviyi bilirim, sanki gemi de beni tanıdı.";
			link.l1 = "Artık tekrar senin, Dannie. Senin ve Nathaniel'ın.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "You can't even imagine how glad I am. Nathaniel used to talk about our ship often; he'll be glad to know that she is ours once again.";
			link.l1 = "Şimdi ne yapacaksın, Dannie?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "Ben mi? Gemiyi Sharp Town'a götüreceğim, en azından asgari bir mürettebat tutacağım ve Blueweld'e yelken açacağım. Jan Svenson'dan 'Centurion'a göz kulak olmasını isteyeceğim, ardından Miskito halkına gideceğim ve Snake Eye kocamı iyileştirene kadar orada bekleyeceğim.";
			link.l1 = "Gerçekten Jan Svenson'u ziyaret etmeye mi gidiyorsun? Şaşırdım...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+",   hepsi senin yüzünden oldu. Sözlerini düşündüm: 'hepimizin amacı aynı'. Hatırlıyor musun? Svenson'la barışmak istiyorum, sonuçta Nathan'ı bana geri getirmesine yardım etti. Artık tartışmayı bırakmanın zamanı geldi.";
			link.l1 = "Ağzına sağlık, Dannie! Nathaniel kendini daha iyi hissettiği anda Maroon Kasabası’ndaki yerini geri alabilecek.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "Belki... ama şöyle bir şey var, korsan baronu seçilerek belirleniyor. Ya diğerleri kabul etmezse?";
			link.l1 = "Bırak Svenson halletsin. O, herkesi ikna edebilir. Jackman'ın ortadan kaldırılması da işe yarayacak.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "Pekâlâ. Zaten Svenson'u kendime dost etmem gerekiyor... "+pchar.name+"!   Bize ve Nathan'a yaptıkların için sana teşekkür etmek istiyorum. Kocamı kurtardın ve kaybettiğimiz her şeyi bize geri verdin. Sana borçlandım.";
			link.l1 = "Hadi ama, Dannie. Biz arkadaşız.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "Maroon Town'da seni her zaman görmekten memnuniyet duyarız, bunu bilmeni isterim. Vaktin olunca orada bizi bul. Nathaniel ve ben, sana bir şekilde teşekkür etmeyi başaracağız.";
			link.l1 = "Aman Tanrım, Dannie! Davetini memnuniyetle kabul ediyorum. Oturup içeceğiz ve seninle Nathan'ın Van der Decken'i nasıl batırdığını konuşacağız...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "Söyledi mi? Ah, bana bunu hatırlatma...";
			link.l1 = "Fine, Dannie. You've got a lot of work ahead of you, and I have to visit our sworn friends - Marcus and Barbazon. I hope you'll let me turn this cabin upside down; I'm sure there are plenty of interesting things in Jackman's chests.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "Tabii, gerçekten karşı çıkacağımı mı sanıyorsun?";
			link.l1 = "Güzel. Aslında, senden ayrılmak üzücü, Dannie... Maroon Town'da görüşürüz!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+",   seni gördüğüme çok sevindim! Maroon Kasabası'na geri döndük ve Nathan yeniden hak ettiği yerde. Aslında köydeki herkes bundan memnun. Artık her şey eskisi gibi iyi gidecek! Özverili yardımın için gerçekten minnettarım!\nSana bir hediye vermek istiyorum. Al, bunu kabul et. Bu tılsım, dövüşleri senin için çok daha kolay hale getirebilir. Ve bu formülle, bunlardan kendin de yapabilirsin.";
			link.l1 = "Teşekkürler, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received the recipe of the talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "Hepsi bu değil. Burada iki sandık dolusu altın da buldum. Bunlar kesinlikle Jackman'ın malıydı. Onları minnettarlığımın bir göstergesi olarak al. Sakın reddetmeye kalkma! Bana ve Nathan'a yardım etmek için ne kadar para harcadığını biliyorum.";
			link.l1 = "Pekala, pekala, Dannie, kabul ediyorum!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received two chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Mükemmel! "+pchar.name+",   bilmeni isterim ki artık bizim en iyi dostumuz sensin. Nathan ve ben seni Maroon Town'da her zaman görmekten mutluluk duyarız! Daha sık uğra bize!";
			link.l1 = "Teşekkür ederim! Sizi tekrar görmekten memnuniyet duyarım, o yüzden beni bekleyin!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "Sana nasıl yardımcı olabiliriz, "+pchar.name+"?";
				link.l1 = "Ne yazık ki, tam çıkıyordum... Elveda, Danny.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "Ve işte burada "+GetFullName(pchar)+". Yüzünden belli, hiç vakit kaybetmemişsin!";
					link.l1 = "İtiraf etmeliyim, eğlenmeyi gerçekten biliyorsun! Teşekkür ederim, harika vakit geçirdim.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "Seni gördüğüme sevindim, "+pchar.name+"! Rom, şarap? Yoksa bir güzel mi?";
			link.l1 = "Teşekkürler, Dannie! Sadece seni görmek istemiştim...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "Kız mı? Sessiz ol, Danny! Kapının önünde parçalara ayrılmış ve güzelce katlanmış halde bulunmak istemezsin, değil mi? Ha-ha. Kapının hemen dışında bekleyen sadık hanımefendim böyle numaraları asla affetmez.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "Bir kız mı? Kulağa ilginç geliyor, Danny. Uzun zamandır... bir kadının kalp atışını... özledim. Bir göz atmalıyım sanırım – öyle herkesi önermezsin, değil mi?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "Gerçekten mi? Neden bu kadar solgunsun? Ha-ha, sadece şaka yapıyordum. Ona iyi bak, duyuyor musun?";
			link.l1 = "Elbette. O, buralardaki tüm hazinelerden daha kıymetli benim için!";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "Bu daha iyi, ha-ha. Devam et, sevgilin muhtemelen endişelenmeye başlamıştır.";
			link.l1 = "Hoşça kal, Danny. Ve endişen için teşekkür ederim, ha-ha.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "Sana temin ederim, bu genç güzellik sana unutulmaz bir zaman yaşatmayı iyi biliyor, "+pchar.name+". İyi eğlenceler! Seni meyhanedeki odada bekliyor olacak.";
			link.l1 = "Teşekkürler, Danny. Hemen geliyorum. Bir dakika bile kaybetmek istemiyorum!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", Maroon Town'da her zaman hoş geldin. En güzel kızlar senin!";
			link.l1 = "Oh, Danny. Yemin ederim, burası benim ikinci evim.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "Ve işte kaptanım geldi. Bugün sadece benimsin! Gel bana, seni ne zamandır bekliyorum...";
			link.l1 = "Öyle mi? Daha fazla bekleyemiyor musun? O halde, hiç vakit kaybetmeyelim!";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("Kaptanım... kadınları fethetmeyi gerçekten iyi biliyorsunuz! Daha önce böyle bir şey hiç yaşamamıştım! Belki birkaç saat daha kalırsınız?","Şimdiden gidiyor musun, sevgilim?");
			link.l1 = RandPhraseSimple("Beni bu kadar kolay bırakmak istemeyeceğini biliyordum. Hoşça kal, sevgilim. Beni büyük şeyler bekliyor...","Ne yazık ki, işler araya giriyor. Ama belki bir gün tekrar karşılaşırız...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "Nihayet Nathan ve ben tekrar rahat nefes alabiliyoruz! O lanet olası Jackman öldü! 'Centurion' için üzülüyorum ama o alçağın gemimi çaldığı anda kaybını zaten kabullenmiştim. O yüzden fazla kafama takmıyorum.";
			link.l1 = "Ama ben biliyorum. Aptalın tekiyim! Bütün kanıtlar gemiyle birlikte denizin dibine gömüldü. Oysa yeni Kıyı Kardeşliği başkanlığı oylamasında işimize yarayabilirdi. Şimdi... hepsi yok oldu.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "Çok üzülme! Böyle şeyler olur. Bir dahaki sefere daha şanslı olursun... Neyse. Bana ve Nathan'a yaptıkların için sana teşekkür etmek istiyorum. Kocamın hayatını kurtardın. Sana çok şey borçluyum.\nBilesin ki Maroon Town seni her zaman memnuniyetle karşılayacak. Zaman bulduğunda beni ve Nate'i orada ziyaret et. Sana borcumuzu ödeyecek bir yol mutlaka buluruz.";
			link.l1 = "Pekala, Dannie. Sana mutlaka uğrayacağım. Şimdiden mi gidiyorsun?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Evet, Miskito'ya gideceğim. Umarım Yılan Göz Nathan'ı çoktan iyileştirmiştir. Sonra Maroon Kasabası'na döneceğiz.";
			link.l1 = "Heh, sana öyle alıştım ki, senden ayrılmak gerçekten üzücü... İyi şanslar, Dannie!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "Ah, aptal numarası yapma, tatlım. Charles, bu aşık kuş o putun etrafında günlerce dolanıp durdu, zavallı Yılan Göz'ü de sorularıyla bıktırdı. Sonra da eve koşup ona bir şey getirdi, değil mi?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "Oh, teşekkürler Charles, güzel bir gösteriydi. Bütün Maroon Kasabası bunun dedikodusunu yapacak, ha-ha!";
			link.l1 = "Bunun senin yeni önceliğin olduğuna hiç şüphem yok – bunun gerçekleşmesini sağlamak.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "Aslında, benim listemin en alt sırasında. Kıza kızma – onun için ilk seferi. Nathan'la ben maceralarımıza atıldığımızda, tüm takımada da bizimle dalga geçiyordu.";
			link.l1 = "Konuya ve havaya değişiklik getirelim. Bu puttan bıktım, hadi gidelim.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "Anlaştık, hadi gidelim, kahraman.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "Ne istiyorsun, Kaptan?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "Dannie, sana bir şey danışmak istiyorum!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "Emirlerimi dinleyin!";
            Link.l1.go = "stay_follow";
			link.l2 = "Bir şey değil. Dağılabilirsiniz!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "Emirler?";
            Link.l1 = "Burada dur!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve yetiş!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ateşli silahlarınız için mühimmat türünü değiştirin.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Mühimmat türünü seçme:";
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
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Bir değişiklik var!";
            Link.l1 = "Serbestsin.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Bir tutum değişikliği var!";
            Link.l1 = "Serbestsin.";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
