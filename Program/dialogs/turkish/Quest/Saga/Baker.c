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
			dialog.text = "Bir şey mi istiyorsun?";
			link.l1 = "Hayır, bir şey değil.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "baker":
			dialog.text = "Teşekkür ederim, Kaptan! Sensiz ne yapardım, düşünemiyorum...";
			link.l1 = "Hayal edebiliyorum. Açlıktan ölebilir ya da Dominika'dan bir vahşinin midesine düşebilirdin. Ama şimdi bana borcunu ödeyebilirsin.";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Sana nasıl yardımcı olabilirim, Kaptan?";
			link.l1 = "Bir adam hakkında daha fazla şey bilmek istiyorum. O, tabiri caizse, bizim ortak tanıdığımız biri. Aslında, senin çok yakın bir arkadaşın. Kaptan Butcher'dan bahsediyorum. Evet, yirmi yıl önce astığın o adamdan. Aman Tanrım, neden bu kadar solgunlaştın? Bir yudum rom ister misin?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Seni... seni o mu gönderdi?";
			link.l1 = "Saçmalık! O öldüyse, onun tarafından 'gönderilmiş' olmam nasıl mümkün olabilir! Benim ilgimi çeken, Kasap'ın kendisinden çok geride bıraktığı şeyler. Mektuplar, belgeler, buna benzer şeyler. Belki de ceplerinde bir şeyler bulmuşsundur... Dur bir dakika! Anlamıyorum. Gerçekten Kasap'ın hayatta olduğunu mu düşünüyorsun? Onu bizzat sen idam ettin!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			dialog.text = "Lanet olsun! Hiçbir fikrin yok. Demek ki seni Kasap göndermemiş, düşündüğüm gibi...";
			link.l1 = "Vay canına. Bu iş giderek daha da ilginçleşiyor. Görünen o ki, Henry'nin Kasap'tan korkmak için her türlü sebebi varmış ve bu yüzden kalp krizinden ölmüş... Kasap hâlâ hayatta mı?";
			link.l1.go = "baker_4";
		break;
		
		case "baker_4":
			dialog.text = "O öyle, Kaptan... Ve beni arıyorlar.";
			link.l1 = "Raymond, aptal olmadığını söylediler bana. Benimle oyun oynama. Burada hiçbir tehditten korkmana gerek yok. Bildiğin her şeyi anlat, ben de sana yardım edecek bir yol bulurum. Belki de ortak düşmanlarımız vardır. Kasap'tan başlayalım.";
			link.l1.go = "baker_5";
		break;
		
		case "baker_5":
			dialog.text = "Hayatta, ama artık adı farklı! Adamları idam gecesi bana geldiler. Jackman ve bir de tuhaf lakaplı bir adam vardı. Yanılmıyorsam, ona 'Boğulmuş Adam' diyorlardı.";
			link.l1 = "Cellat. Cellat Henry.";
			link.l1.go = "baker_6";
		break;
		
		case "baker_6":
			dialog.text = "Right! They offered me a simple deal – die in the most painful way, or save their captain. So I had to fake the execution with some special equipment I had made in my spare time. You see, such an arrangement of belts and clamps can distribute the body's weight.\nAll I had to do was attach it to a secret hook in the noose. The 'corpse' had to play his part well, though. I must say, Lawrence's acting was most convincing; he did everything right, except he refused to piss himself, because of...";
			link.l1 = "Butcher'a az önce 'Lawrence' mi dedin?";
			link.l1.go = "baker_7";
		break;
		
		case "baker_7":
			dialog.text = "Bu onun gerçek adı. Sana Lawrence Beltrope olarak bilindiğini söylemiştim. Bir yıl önce Karayiplere döndüğünden beri içim hiç rahat değil. Ve bazı tehlikeli insanların beni aradığını öğrenince...\nHer ihtimale karşı yetkililer için bir itiraf bile yazdım. Onu her zaman yanımda tutuyorum, teslim etmeye korkuyorum. Yoksa olaylara isteyerek karıştığımı sanabilirler. Lütfen, mürettebatında kalmama izin ver. Yemin ederim, çok iyi bir hekimim ve sana gerçekten faydam dokunur.";
			link.l1 = "Pekâlâ. Peki ya Butcher'ın... şey, Beltrope'un kişisel eşyaları? Thomas Beltrope ile bir akrabalığı var mı?";
			link.l1.go = "baker_8";
		break;
		
		case "baker_8":
			dialog.text = "No clue. I don't have anything special left from Beltrope himself. But I will give you everything I have; you are free to do whatever you want with it. All papers related to the subject are in my bag. I saved everything just in case and keep it close to me.\nHere, take a look... this is the legend of Captain Butcher, this is my confession... These are things that belonged to Joshua Leadbeater...";
			link.l1 = "Dur! Leadbeater? Kim o?";
			link.l1.go = "baker_9";
		break;
		
		case "baker_9":
			dialog.text = "Ah! O çok özel bir adamdı. Kasabı bizzat avlayan oydu. İnsanlar ona 'maskeli adam' derdi. Kasabın idamından kısa süre sonra öldürüldü. Birisi boğazını köpekbalığı dişiyle kesti! Tek bir hamlede her şey bitti. Hâlâ hayattayken çok acı çekmiş olmalı.\nMaskenin altındaki yüzünü görseydiniz, etten başka bir şey yoktu! Ölürken cebinde bu günlük sayfası vardı. Muhtemelen Jessica Rose'un yazılarından biri. Tüyler ürpertici bir hikaye! Oku, her şey çok daha netleşecek.\nVe işte dişin kendisi. Harfleri görebiliyor musun? S.D.... Ne anlama geliyorsa artık. Biraz da kan lekesi kalmış.";
			link.l1 = "Yeter! Her şeyi dikkatlice okuyup iyice düşünmem lazım. Ve sen, tüm bunlarla işim bitene kadar ya yolcum ya da gemimin doktoru olacaksın. Rahat bir nefes alabilirsin Raymond, gemimde güvendesin.";
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
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddCharacterExpToSkill(pchar, "Sailing", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Baker_officer":
			dialog.text = "Evet, kaptan?";
			Link.l1 = "Emirlerimi dinleyin!";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Kaptan, biraz endişeli görünüyorsunuz. Yüzünüz de epey solgun... Farklı bir durumda size tonikleri̇mden birini önerirdim ama...";
				Link.l1 = "Tıptan biraz anlar olmuşsun, "+npchar.name+". Teşekkürler, iyiyim. Sadece, başka koşullarda asla cesaret edemeyeceğim bir adımı atmak üzereyim.";
				Link.l1.go = "SharlieEpilog_Baker_1";
				break;
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Raymond, bana gemiyle ilgili tam bir rapor ver.";
			    Link.l11.go = "QMASTER_1";

			    // Warship. Автозакупка товара
				Link.l12 = "Her limana yanaştığımızda belirli malları satın almanı istiyorum.";
				Link.l12.go = "QMASTER_2";
			}
			
			link.l2 = "Önemli bir şey değil. Dağılın!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Baker_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
        case "QMASTER_1":
			dialog.Text = "Hadi ama Kaptan, ben bir hekimim, muhasebeci değil. Gerçi eskiden başka bir işte çalışmıştım... neyse. Gerçekten muhasebe işlerinden anlamam, üzgünüm.";
			Link.l1 = "Pekâlâ, öyle olsun. Sen benim doktorumsun - ekibime katıldıktan sonra anlaştığımız gibi.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Kaptan, açık konuşmak gerekirse, ticaret konusunda pek tecrübem yok. Hiç pazarlık yapmadım, fiyatları takip etmedim. Ayrıca... izin verirseniz gemide kalmayı tercih ederim. Şu tüccarların bazıları beni tanıyabilir ve farkına bile varmadan, peşime maskeli adamlar düşer.";
			link.l1 = "Yani, geçmişinden korkarak yaşamaya devam edeceksin... Peki, derin bir nefes al, ben hallederim.";
			Link.l1.go = "exit";
        break;
		
		case "stay_follow":
            dialog.Text = "Emirleriniz?";
            Link.l1 = "Burada dur!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve yetişmeye çalış!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ateşli silahınız için mühimmat türünü değiştirin.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Mermi türünü seçmek:";
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
            dialog.Text = "Bir tutum değişikliği var!";
            Link.l1 = "Serbestsin.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Bir değişiklik oldu!";
            Link.l1 = "Serbestsin.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// Эпилог
		case "SharlieEpilog_Baker_1":
			dialog.text = "Hımm... Sanırım bir şeyi yanlış anladım. Yakında alacağınız haberin sizi sevindireceğini düşünmüştüm.";
			link.l1 = "Neden bahsediyorsun?";
			link.l1.go = "SharlieEpilog_Baker_2";
		break;

		case "SharlieEpilog_Baker_2":
			dialog.text = "Öhöm... Affedersiniz. Ne yaptığımı ben de bilmiyorum. Belki güneş çarptı. Aslında sizinle konuşmak istiyordum, kaptan.";
			link.l1 = "Gerçekten mi? Neyle ilgili?";
			link.l1.go = "SharlieEpilog_Baker_3";
		break;
		
		case "SharlieEpilog_Baker_3":
			dialog.text = "Bu bitmek bilmeyen deniz savaşları için artık fazla yaşlandım, hem de sadece dolaylı olarak katılıyor olsam bile. Biraz birikmiş param var ve karaya çıkmak istiyorum. Özel muayenehane açmak niyetindeyim. Umarım bir itirazınız yoktur?";
			link.l1 = "Elbette hayır, "+npchar.name+". Senin gibi yetenekli bir subayı özleyeceğim kesin. Ama kararını anlıyor ve saygı duyuyorum. Bol şans. Eminim kısa sürede tanınan ve saygı gören bir doktor olacaksın.";
			link.l1.go = "SharlieEpilog_Baker_nothing";
			link.l2 = "Akıllıca bir karar, ve elbette hiçbir itirazım yok. Sana fazladan bir aylık maaş verilmesini sağlayacağım — fazlası zarar etmez. Eh... yeni hayatında bol şans dilerim.";
			link.l2.go = "SharlieEpilog_Baker_salary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // только если есть жена
			{
				link.l3 = "Ha-ha, elbette karşı çıkmam, sevgili "+npchar.name+". Şu an seni her zamankinden daha iyi anlıyorum. Al bunu. Bu üç aylık maaş. Umarım her şey gönlünce olur.";
				link.l3.go = "SharlieEpilog_Baker_salary_X3";
			}
		break;
		
		case "SharlieEpilog_Baker_nothing":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
		
		case "SharlieEpilog_Baker_salary":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
			//
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Baker_salary_X3":
			dialog.text = "Teşekkür ederim, kaptan. Sizin de eşinizle birlikte yaşayabileceğiniz rahat bir ev aramaya başlamanız iyi olur. Sonuçta, denizin sallantısı karındaki bazı süreçlere pek iyi gelmez...";
			link.l1 = "Karın mı? Ne demek istiyorsun? Gemide kimsenin deniz tutması yok.";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_2";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Baker_salary_X3_2":
			dialog.text = "Sadece kendi kendime konuştum, kaptan. Takılmayın. Eşinize ve kendinize iyi bakın.";
			link.l1 = "Sen de kendine dikkat et, "+npchar.name+". Yerleştikten sonra bana Aziz Pierre Kilisesi’ndeki Peder Benoît aracılığıyla haber gönder.";
			link.l1.go = "SharlieEpilog_Baker_salary_X3_3";
		break;
		
		case "SharlieEpilog_Baker_salary_X3_3":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Baker_exit");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
