// Эркюль Тонзаг, он же Плешивый Гастон
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
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
			{
				dialog.text = "Pekâlâ, merhaba, "+pchar.name+" . Seni sağ gördüğüme sevindim.";
				link.l1 = "Gaston! Sen misin?";
				link.l1.go = "SJ_talk";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
			{
				dialog.text = "Selamlar, "+pchar.name+" . Senin işlerini zaten biliyorum - John bana her şeyi anlattı. Ne diyeceğimi bile bilmiyorum. Sana hayran kaldım!";
				link.l1 = "Senden böyle övgüler duymak beni mutlu etti, Hercule!";
				link.l1.go = "SJ_talk_11";
				break;
			}
			dialog.text = "İyi günler. Benim için bir işiniz var mı?";
			link.l1 = "Hayır. Hata ettim. Özür dilerim. Hoşça kal. .";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "SJ_talk":
			dialog.text = "Beni o isimle tanıyordun. Ama gerçek adım Hercule. Hercule Tonzag.";
			link.l1 = "Kutsal Tanrım! Seni görmek de beni çok mutlu etti... Kavganın heyecanında seni tanıyamadım. Yardıma tam zamanında yetiştin.";
			link.l1.go = "SJ_talk_1";
		break;
		
		case "SJ_talk_1":
			dialog.text = "Siz ayrılır ayrılmaz, Fleetwood'un evini korumak için önlemlerini artırdığına dair haber aldım. Bunun arkasında bir tuzak olabileceğini düşündüm. Hemen 'Twilight' adlı gemimle Antigua'ya yelken açtım—ve şimdi gördüğün gibi, iyi ki de öyle yapmışım.";
			link.l1 = "Doğru. Evdeki muhafızlarla başa çıkmayı zar zor başardım, ama sokakta dövüşmeye devam edecek halim kalmamıştı...";
			link.l1.go = "SJ_talk_2";
		break;
		
		case "SJ_talk_2":
			dialog.text = "Bu kavgadan sonra, Fleetwood bir Hollandalı casusu arananlar listesine aldı. Seni Hollandalı casusu sandılar. Onlarla köklü bir husumeti var. En kötüsü, evdeki bir asker hayatta kaldı ve yüzünü hatırladı. Ama artık bu bir sorun değil. Senin başlattığını ben bitirdim. O asker artık kimseyi tanıyamayacak, kimse de onu tanıyamaz...";
			link.l1 = "Onu öldürdün mü? Anlıyorum...";
			link.l1.go = "SJ_talk_3";
		break;
		
		case "SJ_talk_3":
			dialog.text = "Evet. Sen John'un evinde baygın yatarken, Fleetwood'u yaraladım, ama o alçak hayatta kalmayı başardı. Onu kör ettim - gözlerine biber attım, sonra da kılıcını çekmeye fırsat bulamadan vurup yere serdim. Ama o pislik üniformasının altına zırh giymişti - hayatını kurtardı. Akıllıca. Şimdi evinde yatakta, güvenliği artırılmış halde kalıyor. Hayatta kalması gerçekten çok talihsiz oldu.";
			link.l1 = "Yani, Antigua’daki asıl görevin Fleetwood’u ortadan kaldırmak mıydı?";
			link.l1.go = "SJ_talk_4";
		break;
		
		case "SJ_talk_4":
			dialog.text = "Genellikle, evet. Ama şimdi imkansız gibi görünüyor – ev her zaman kilitli, gece gündüz nöbet tutan yarım düzine seçilmiş muhafız var ve yanına sadece güvendiği birini alıyorlar – eski bir topçu Charlie, namı diğer Knippel.";
			link.l1 = "Bu da bir şey...";
			link.l1.go = "SJ_talk_5";
		break;
		
		case "SJ_talk_5":
			dialog.text = "Biraz bekle... Bu işe karışacak mısın?";
			link.l1 = "Neden olmasın? Yardıma ihtiyacın yok mu? Beni kurtardın, ben de sana yardım etmek istiyorum. Ayrıca hâlâ paraya ihtiyacım var.";
			link.l1.go = "SJ_talk_6";
			// belamour legendary edition -->
			link.l2 = "Neden olmasın? Siz ciddi insanlarsınız. Ve ciddi insanlar cömertçe öder. Ben sadece bir iş arıyorum.";
			link.l2.go = "SJ_talk_6a";
		break;
		
		case "SJ_talk_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			dialog.text = "Bana inan dostum, bunu başaramazsın. Gerçekten iyi bir adamsın, yeteneklisin, ve getirdiğin seyir defteri Fleetwood'un hayatına kastetme planımı yapmamda çok işime yaradı. Muhafızlarla iyi başa çıktın – ama artık Fleetwood'a ulaşman imkânsız. Benim bile bunu nasıl yapacağım hakkında en ufak bir fikrim yok.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Düşüneceğim. Hâlâ zamanım var. Gemime el konulması ve mürettebatımın olmaması gerçekten yazık.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Bunu düşüneceğim. Zamanım ve bir gemim var.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_6":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Bana inan dostum, bunu başaramazsın. Sen iyi bir adamsın, gerçekten yeteneklisin, getirdiğin seyir defteri de bana Fleetwood'un hayatına kastetmek için bir plan yapmamda yardımcı oldu. Muhafızlarla iyi başa çıktın – ama artık Fleetwood'a ulaşman imkânsız. Benim bile nasıl yapılacağına dair en ufak bir fikrim yok.";
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				link.l1 = "Düşüneceğim.   Hâlâ vaktim var.   Ne yazık ki gemime el kondu ve bir mürettebatım yok.";
				link.l1.go = "SJ_talk_7";
			}
			else
			{
				link.l1 = "Bunu düşüneceğim. Zamanım ve bir gemim var.";
				link.l1.go = "SJ_talk_8";
			}
		break;
		
		case "SJ_talk_7":
			dialog.text = "Bunun için endişelenme. Eski teknen el konulduğunda, tüm subaylarını ve bazı tayfalarını kendi gemim 'Alacakaranlık'a aldım. Hayatta olduğunu biliyorlar ve hizmette kalmayı kabul ettiler. Ve günlüğün karşılığında, 'Alacakaranlık'ı sana bırakıyorum.";
			link.l1 = "Teşekkür ederim! Bunu unutmayacağım!";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_8":
			AddMoneyToCharacter(pchar, 15000);
			dialog.text = "Evet, günlüğü almak için sana ödeme yapmak istiyorum. 15.000 peso - şu anda daha fazlası yok, maalesef. Bir gün içinde hesabı kapatırız. ";
			link.l1 = "Gerek yok. Bu yeterli. Zamanında yetişmeseydin, zaten paraya ihtiyacım kalmazdı.";
			link.l1.go = "SJ_talk_9";
		break;
		
		case "SJ_talk_9":
			dialog.text = "Pekâlâ, "+pchar.name+", gitmem lazım. Henüz Bridgetown'a dönmüyorum. Bana ihtiyacın olursa John'a sor. Bol şans!";
			link.l1 = "İyi şanslar, Hercule!";
			link.l1.go = "SJ_talk_10";
		break;
		
		case "SJ_talk_10":
			DialogExit();
			AddDialogExitQuestFunction("HollandGambit_NewShipTwilight");
		break;
		
		case "SJ_talk_11":
			dialog.text = "Sana Fleetwood'u ortadan kaldırdığın için bu zırhı vermek istiyorum. Gelecekteki savaşlarda seni koruyacak. Şimdi John'un yanına gidelim. Seninle konuşmak ve sana... ilginç bir teklif sunmak istiyor.";
			link.l1 = "Hediye için teşekkürler. Pekâlâ, hadi gidelim...";
			link.l1.go = "SJ_talk_12";
		break;
		
		case "SJ_talk_12":
			DialogExit();
			GiveItem2Character(pchar, "cirass7");//дать вещь
			sld = characterFromId("Merdok");
			AddLandQuestMark(sld, "questmarkmain");
			LAi_SetOwnerType(sld);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			AddQuestRecord("Holl_Gambit", "3-35");
		break;
		
		case "Tonzag_hired":
			dialog.text = "Ben de sizinle konuşmak isterim, kaptan. Size kendi ustalığımı öğretmeyi düşünüyordum, ama şimdi görüyorum ki asıl ben sizden öğrenmeliyim. Beni geminize subay olarak alın – pişman olmazsınız.";
			link.l1 = "Memnuniyetle, Hercule! Mürettebata hoş geldin!";
			link.l1.go = "Tonzag_hired_1";
			link.l2 = "Hercule, kendimi senin üstün olarak hayal edemiyorum. Teklifin için teşekkür ederim, ama seni astım olarak görmek bana hiç uygun gelmiyor.";
			link.l2.go = "Tonzag_exit";
		break;
		
		case "Tonzag_hired_1":
			ForceHeroAutolevel(npchar);//Тонзага - в офицеры
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			npchar.greeting = "tonzag_hire";
			NextDiag.CurrentNode = "tonzag_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			LAi_SetImmortal(npchar, false);
		
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;
		
		case "Tonzag_exit":
			dialog.text = "Dediğiniz gibi, "+pchar.name+". Görüşmek üzere. Belki tekrar karşılaşırız. Seninle çalışmak bir zevkti.";
			link.l1 = "Bol şanslar, dostum!";
			link.l1.go = "Tonzag_exit_1";
		break;
		
		case "Tonzag_exit_1":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			DialogExit();
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "tonzag_officer":
			dialog.text = "Sizi dinliyorum, kaptan. Ne söylemek istiyorsunuz?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "Oldukça karanlık görünüyorsun, kaptan. Bir şey mi oldu?";
				Link.l1 = "Takımadaları terk etmem gerekiyor. İki hafta içinde. Başkasının gemisinde, bir yolcu olarak.";
				Link.l1.go = "SharlieEpilog_Tonzag_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Hercule, Tayasal adlı eski bir Hint şehrine gidiyorum ve dahası, yolum bir teleportasyon heykelinden geçiyor. Benimle gelir misin?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Hercule, bana gemiyle ilgili tam bir rapor ver.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Her limana yanaştığımızda belirli malları satın almanı istiyorum.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Emriniz üzerine geldim, Kaptan.";
				Link.l2 = "Sana birkaç emir vermem gerekiyor.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "tonzag_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Emirlerimi dinleyin!";
            Link.l1.go = "stay_follow";
			link.l2 = "Şu anda bir şey yok. Rahat ol!";
			link.l2.go = "exit";
			NextDiag.TempNode = "tonzag_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Kaptan, üzgünüm ama ben sayılarla ve hesaplarla uğraşmam. Van Merden'a sor – bu işlerde iyidir, gerçi yuvasını bırakmaya niyeti olur mu, pek sanmam.";
			Link.l1 = "Haklısın, Hercule. Eh, kendime bir veznedar bulmam lazım...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Kaptan, Barbados'ta meyhanecilik yaptığımda sadece rom ve erzak alırdım. Ve erzak derken, sadece bisküviyle tuzlu etten bahsetmiyorum, düzgün yiyecek kastediyorum. Kusura bakmayın, ama bu benim işim değil.";
			link.l1 = "Belki de gemimi bir meyhaneye çevirmeliyiz... Şaka yapıyorum, Hercule. Neyse, ben hallederim.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Seni dinliyorum.";
			Link.l1 = "Bu, gemiye çıkmakla ilgili.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Bu senin geminle ilgili.";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Şimdilik bir şey yok.";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "Peki, dileğin nedir?";
			Link.l1 = "Düşman gemilerine çıkma. Kendine ve mürettebata dikkat et.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Düşman gemilerine çıkmanı istiyorum.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "Peki, dileğin nedir?";
			Link.l1 = "Gemiyi ele geçirdikten sonra başka bir gemiyle değiştirmemeni tercih ederim. O çok değerli.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Düşman gemilerine bindiğinde, eğer düzgünlerse onları kendin için alabilirsin.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Yapılacak.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Aye-aye.";
			Link.l1 = "Yapılacak.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Yapılacak.";
			Link.l1 = "Rahat ol.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		
		case "stay_follow":
            dialog.Text = "Emirleriniz nedir?";
            Link.l1 = "Burada kal!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Beni takip et ve geride kalma!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Merminin türünü değiştir.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Kullanılacak mühimmat türü seçimi:";
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
            dialog.Text = "Aye!";
            Link.l1 = "Rahat ol.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Aye!";
            Link.l1 = "Rahat ol.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Şanslı bir herifsin, kaptan. Seninle, John'la birlikte çalışmaya başladığım o gün iyi ki yanında olmuşum. Bu işte sana destek olmazsam köpekbalığı beni yutsun!";
			link.l1 = "Teşekkür ederim, Hercule! Senin hakkında yanılmadığıma sevindim.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Peki, ne zaman yola çıkıyoruz?";
			link.l1 = "Birazdan. Şimdi yolculuk için hazırlanmalıyız.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "23");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Pek bir şey yok, Kaptan. Eğer bu bizim işimizle ilgili olsaydı, çoktan işkence masasına yatırılmış olurduk.\nBizi hemen sorguya götürmediklerine göre, mesele acil değil demek ki.\nYa bir tuzak ya da şantaj.\nBirkaç gün boyunca burada bizi oyalayacaklar, hiçbir şey açıklamadan. Sonra da gelip bir teklif sunacaklar, kabul etmek zorunda kalacağımız bir teklif.";
			link.l1 = "Kişisel deneyim?";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Peki, şu anda onları böyle bir teklifle gelmeye ikna etmenin bir yolu var mı?";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Elbette. Gruoh bir zamanlar ölü bir adamın akrabalarından, Trinidad celladının veda dokunuşlarından onu kurtarması için para aldı.\nKadın, nezarethane hücrelerinde dolaşma hakkı için komutana ödeme yaptı. Bu yaygın bir uygulama - çoğu insan, karşı koyamayacak olanları işkence etmek için askerlere para verir, hem de tanık olmadan.\nAdam sessizce ve acı çekmeden öldü. Temiz ve düzgün bir işti.";
			link.l1 = "Gruoh? Kim o?";
			link.l1.go = "tonzag_jailed_1_1";
		break;
		
		case "tonzag_jailed_1_1":
			dialog.text = "Üzgünüm, Kaptan. Yanlış yer, yanlış zaman.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Deneyebiliriz. Yemek saatini bekleyelim, ben de nöbetçiyle birkaç laf ederim. Görüyorsun ya, hâlâ doğru dürüst arama yapmayı öğrenemediler. Eh...";
			link.l1 = "Ne oldu?";
			link.l1.go = "tonzag_jailed_2_1";
		break;
		
		case "tonzag_jailed_2_1":
			dialog.text = "Garip bir his, Kaptan. Hatta buna bir önsezi diyebilirim. Affedersiniz, sonra konuşalım.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "tonzag_killed_hunters":
			dialog.text = "Bir şey mi kaçırdım, Kaptan?";
			link.l1 = "Ah, pek de özel bir şey yok, denizde sıradan bir gün işte. Şuna bak, seni eski şeytan! Burada bana epey bir iş çıkarmışsın.";
			link.l1.go = "tonzag_killed_hunters_1";
		break;
		
		case "tonzag_killed_hunters_1":
			dialog.text = "Kan soğuk suyla çıkar, Kaptan. Konuşmamız lazım.";
			link.l1 = "Öyle mi diyorsun? Şimdilik şu günü sağ atlatmak fena olmazdı.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_Victory");
		break;
		
		case "tonzag_after_victory_helena":
			dialog.text = "Ben de seni gördüğüme sevindim, Rumba. Kaptan, şimdi sizi rahatsız etmeyeyim, sonra konuşuruz.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;
		
		case "tonzag_after_victory_mary":
			dialog.text = "Selam, Ginger. Kaptan, sizi rahatsız etmeyeyim, sonra konuşuruz.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;
		
		case "tonzag_after_victory_alonso":
			dialog.text = "Kaptan, sizi rahatsız etmeyeyim, sonra konuşuruz.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_drink":
			dialog.text = "Beni dinlemeye hazır mısın, Kaptan?";
			link.l1 = "Artık konuşmamızın zamanı geldi, Hercule. Şimdi fark ettim ki senin hakkında neredeyse hiçbir şey bilmiyorum.";
			link.l1.go = "tonzag_drink_1";
		break;
		
		case "tonzag_drink_1":
			dialog.text = "Demek tanışma vakti geldi. Çocukluk yıllarını atlayalım, çünkü anlatacak pek bir şey yok – zafer kazanmış bir asker, yenilmiş bir asker, bir firari, bir çapulcu... nasıl olduğunu bilirsin.";
			link.l1 = "Aslında bilmiyorum, ama şu ana kadar kulağa oldukça sıradan geliyor.";
			link.l1.go = "tonzag_drink_2";
		break;
		
		case "tonzag_drink_2":
			dialog.text = "Böyle bir askeri yolun ardından önümde pek fazla kariyer seçeneği yoktu – ya haydut olacaktım, ya darağacına gidecektim, ya da Hollanda Batı Hindistan Şirketi’ne layık bir muhafız. Anlayacağın, ben sonuncusunu seçtim.";
			link.l1 = "Oradan da mı firar ettin?";
			link.l1.go = "tonzag_drink_3";
		break;
		
		case "tonzag_drink_3":
			dialog.text = "Aksine, orada kariyer yaptım. Şirketin istihbarat biriminin savaş kanadına katılmam için teklif aldım ve orada gelecekteki eşimle tanıştım.";
			link.l1 = "Pekâlâ, şu ana kadar hikaye oldukça sakin ilerliyor... tabii Hollandalıların yöntemleri üzerinde fazla düşünmezsen.";
			link.l1.go = "tonzag_drink_4";
		break;
		
		case "tonzag_drink_4":
			dialog.text = "Dürüst olarak pek para kazanamazsın, rekabetle başa çıkmanın ise türlü yolları var. Evet, biz de özel yöntemlerle çalıştık...";
			link.l1 = "Sanırım ne demek istediğini anlıyorum...";
			link.l1.go = "tonzag_drink_5";
		break;
		
		case "tonzag_drink_5":
			dialog.text = "Evet, her şey olabilirdi: korsanlıktan tutun da mallarla dolu depoları ateşe vermeye kadar. Sonunda, düzen ortaya çıktı ve biz dağıtıldık... tabii ki sadece kağıt üzerinde. İşte Lig böyle doğdu; sadece Şirketin üst kademelerinin seçilmiş liderleri tarafından bilinen ve kontrol edilen bir yapıydı. Karayipler'de kendine güvenen bir kanun kaçağı için iki seçenek vardı: korsanlık ya da Lig. Ve genellikle Lig daha iyi öderdi\nÇoğunlukla Lig hâlâ Hollandalılar için çalışıyordu, ama arada başka işler de alabilirdi...";
			link.l1 = "İşler yavaş yavaş netleşmeye başlıyor...";
			link.l1.go = "tonzag_drink_6";
		break;
		
		case "tonzag_drink_6":
			dialog.text = "O oyunun arkasında Lig vardı Tortuga'da. Sonra da o çıkarma ekibi...";
			link.l1 = "Öyle tahmin etmiştim. Ama neden?";
			link.l1.go = "tonzag_drink_7";
		break;
		
		case "tonzag_drink_7":
			dialog.text = "Çünkü Lig'den kimse sağ çıkamaz, orada yaptıklarımızın bedelini de ödemeden kurtulamazsın Kaptan. Emekli olmak istedim, yine de denedim. Gördüğün gibi, pek de başarılı olamadım.";
			link.l1 = "Eski meslektaşlarının büyük masraflara girip, neredeyse yüz kişiyi harcayıp, bir kundak gemisini yakıp, savaş gemilerini riske atmalarının tek sebebi... seni firardan dolayı öldürmek mi diyorsun?";
			link.l1.go = "tonzag_drink_8";
		break;
		
		case "tonzag_drink_8":
			dialog.text = "Lig'de sıradan bir çırak değildim, Kaptan. Hakkında fazlasıyla bilgi sahibiyim. Beni öylece bırakmalarına imkan yok, bunu da açıkça göstermeleri gerek, yoksa başkalarının da işi bırakma fikri aklına düşer... Daha önce de bana ulaşmaya çalıştılar... epey uzun zaman önce... Karımı öldürdüler ve beni sakat bıraktılar, hem de bunun bedelini ağır ödediler. Bu hikayenin mutlu sonu yok, Kaptan. Emri verin, gemiden inerim ve onlarla son kez yüzleşirim.";
			link.l1 = "Saçmalama, Hercule... Peki, tüm bu işlerde Lucas Rodenburg'un rolü neydi? O da bu işlerin içinde olmalı! Senin, ya da daha doğrusu onun, 'örgütü', Lig...";
			link.l1.go = "tonzag_drink_9";
		break;
		
		case "tonzag_drink_9":
			dialog.text = "Farklı teşkilatlar, Kaptan. Kabul etmek gerekir ki, çoğu zaman aynı kişiye bağlıydılar ve birlikte çalışırlardı. Ama Rodenburg'un özel ajanları nokta atışı, etkili darbeler indirirdi, Lig ise kitlesel operasyonlar yürütürdü. Peki şimdi, Lig'e ne oldu? Gördüğünüz gibi, artık böyle bir teşkilat yok: Ben buradayım, John Murdock ayrıldı, Longway kaçtı, Van Berg denizin dibinde, Rodenburg idam edildi... Yine de, o merhum düzenbaza borçluydum. Lig'deyken beni fark etti ve ayrılmaya çalıştığımda, başımı büyük bir beladan kurtarıp yardımcısı yaptı. Tabii, diğerleri bundan hoşlanmadı ama hiçbiri ona karşı gelmeye cesaret edemedi... Sonra, malum şartlar altında, Murdock ve benden kurtulmaya karar verdi ama siz araya girdiniz ve beni hizmetinize aldınız.\nBen de düşündüm ki, 'İşte geçmişle bağımı koparmak için ikinci bir şans...' Rodenburg'u alt ettiniz, Lig koruyucusunu kaybetti, artık bir tehlike kalmadı... Ama tabii ki yanılmışım... Yaşlı ahmak... Neyse, bu kadar yeter Kaptan. Şimdi ne yapacağımızı düşünelim, tabii ilk limanda beni bırakmayı gerçekten planlamıyorsanız.";
			link.l1 = "Hayır, bilmiyorum. Sanırım bir planın var?";
			link.l1.go = "tonzag_drink_10";
		break;
		
		case "tonzag_drink_10":
			dialog.text = "Aslında özel bir şey yok. Hepsini yok edemeyiz, ama onlara öyle ağır kayıplar verebiliriz ki, peşimden...bizim peşimizden gelmeye devam etmeleri onlara değmez.";
			link.l1 = "Peki bunu nasıl yapacağız? Bir kampları var mı?";
			link.l1.go = "tonzag_drink_11";
		break;
		
		case "tonzag_drink_11":
			dialog.text = "Büyük bir kale mi? Hiç sanmam. Bu, Lig için fazla göze batar ve tehlikeli olurdu. Ayrıca kayıplardan kastım insan kaybı değil - insanlara aldırdıkları yok, ama altın kaybetmekten hoşlanmazlar. Şirketten gelen para artık onlara gitmiyor, değil mi? Ligin yeni bir hamisi olduğunu sanmıyorum, o yüzden altını başka bir yerden sıkıyor olmalılar.";
			link.l1 = "Ve orası neresi olurdu?";
			link.l1.go = "tonzag_drink_12";
		break;
		
		case "tonzag_drink_12":
			dialog.text = "Bilmiyorum, Kaptan.";
			link.l1 = "Hercule, ama az önce seni tam da fazla şey bildiğin için takip ettiklerini söyledin!";
			link.l1.go = "tonzag_drink_13";
		break;
		
		case "tonzag_drink_13":
			dialog.text = "Bir düşüneyim... Belki de şu anda Birlik İspanyollara karşı harekete geçiyordur. Onlar iyi bir sarsıntı için en uygun adaylar. Bu arada, Rodenburg her zaman Kastilyalı kodamanlarla iyi geçinirdi. Bazen Birlikteki çocukları onlara çeşitli işler için yönlendirirdi ve onlara asla zarar verilmesini istemezdi, ki bu arada, çocukların pek hoşuna gitmezdi...";
			link.l1 = "İyi ilişkiler diyorsun ha? Peki ya şu hidalgo ve parmağı? Beni onu meyhanene sürüklemeye zorladığını unuttun mu?";
			link.l1.go = "tonzag_drink_14";
		break;
		
		case "tonzag_drink_14":
			dialog.text = "Bu özel bir durumdu, ek bir işti. Eğer kendini suçlu hissediyorsan, Kaptan, rahat olabilirsin – o Don hak ettiğini buldu... Ama ben başka bir şeyden bahsediyorum: Patronları ortadan kaybolduktan sonra, Lig ajanları sadece arzularına yenik düşüp İspanyol pastasından büyük bir pay kapmaya çalışabilirlerdi. Rodenburg yönetiminde İspanyollarla çalıştıkları için, nerede ne olduğunu gayet iyi biliyorlar.";
			link.l1 = "Hm... haklı olabilirsin. Ama bildiğim kadarıyla, kimse gerçekten İspanyol bankalarına dalmıyor, denizde İspanyollara karşı iş yapmak ise tamamen şansa kalmış... Belki de bir İspanyol işletmesi aramalıyız? Bir fabrika?";
			link.l1.go = "tonzag_drink_15";
		break;
		
		case "tonzag_drink_15":
			dialog.text = "Makul bir varsayım, Kaptan... Başka bir ipucumuz var mı?";
			link.l1 = "Hm... bugün bize saldıran gemi güneye gitti...";
			link.l1.go = "tonzag_drink_16";
		break;
		
		case "tonzag_drink_16":
			dialog.text = "Kaptanlarının bir daha bize bulaşması pek olası değil, ama diğerlerini uyarıp işlerin planlandığı gibi gitmediğini söylemeli ve belki de mürettebatı başka bir yere götürmeli. Başka bir şey var mı?";
			if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain")) {
				link.l1 = "Evet, Tortuga hapishanesinin komutanıyla dostça bir sohbet ettim... Anakaradan bahsetti biraz.";
				link.l1.go = "tonzag_drink_know";
			} else {
				link.l1 = "Hayır, başka bir şey yok.";
				link.l1.go = "tonzag_drink_notknow";
			}
		break;
		
		case "tonzag_drink_know":
			dialog.text = "Mükemmel, Kaptan! Güney, ana kara, İspanyollar - bu da demek oluyor ki onları çabucak bulacağız. Yelken açıyor muyuz? Ve hikayemi dinlediğiniz için teşekkür ederim.";
			link.l1 = "Evet, seninle gerçekten içten bir sohbet ettik... Hadi yelken açalım!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_drink_notknow":
			dialog.text = "Fazla bir ipucu yok. Ama bizim gibiler için bu yeterli. Güneye doğru gidelim mi? Bir İspanyol ticaret şirketi arayalım? Ve hikâyemi dinlediğin için teşekkür ederim.";
			link.l1 = "Evet, seninle bayağı içten bir sohbetimiz oldu... Hadi yelken açalım!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;
		
		case "tonzag_dead":
			dialog.text = "Bak, Kaptan. İşte böyle çalışıyorlar.";
			link.l1 = "Sen de böyle mi çalıştın?";
			link.l1.go = "tonzag_dead_1";
		break;
		
		case "tonzag_dead_1":
			dialog.text = "Hadi gidelim, içinde ne var bakalım.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;
		
		case "tonzag_afterminefight":
			dialog.text = "Pis bir işti, Kaptan. Bu inin kökünü kazıdık, ama bu kesinlikle sonuncusu değil...";
			link.l1 = "Ya maden ne olacak, Hercule?! Dışarıdaki onca insan ne olacak?! Onlar da mı 'temizlendi'?! Ve o alçak ne demek istedi?";
			link.l1.go = "tonzag_afterminefight_1";
		break;
		
		case "tonzag_afterminefight_1":
			dialog.text = "Let's discuss this later, Captain. Their commander survived; we need to interrogate him.";
			link.l1 = "Ya hiçbir şey bilmiyorsa?";
			link.l1.go = "tonzag_afterminefight_2";
		break;
		
		case "tonzag_afterminefight_2":
			dialog.text = "He knows something. Think about it - they were waiting for us, carried out all the gold, and eliminated witnesses. That means they had a plan. I want to take a look around here, and later I'll bring the scoundrel to the ship myself. You should also keep an eye out; perhaps they were too hasty and missed something.";
			link.l1 = "Pekâlâ, ama gemiye döndüğümüzde ciddi bir konuşma yapmamız gerekecek!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
			DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
			AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;
		
		case "tonzag_in_hold":
			dialog.text = "Güzel haberler, Kaptan.";
			link.l1 = "Durumumuzda iyiye dair hiçbir şey göremiyorum, Hercule. Hadi gidelim, özel konuşmamız lazım.";
			link.l1.go = "tonzag_in_hold_1";
		break;
		
		case "tonzag_in_hold_1":
			dialog.text = "Demek öyle, ha? Peki, Kaptan.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;
		
		case "tonzag_drink_again":
			dialog.text = "Ciddi bir konuşma yapacağımızı görüyorum, Kaptan.";
			link.l1 = "Evet, ve konuşacak olan da ben olacağım. Öncelikle, burada bir eğilim oluştuğunu düşünmüyor musun? Nereye gitsek arkamızda ceset yığınları bırakıyoruz! Önce sen bir avuç misketle karnından vuruldun, ertesi gün ise yüzü aşkın insan, iyisiyle kötüsüyle, öldü... Buna deniz savaşı bile diyemem! Birkaç gün önce bir yerleşim yeri yerle bir edildi, bugün de madenlerde bir sürü insanı öldürerek bu yığına katkıda bulunduk.";
			link.l1.go = "tonzag_drink_again_1_1";
		break;
		
		case "tonzag_drink_again_1_1":
			dialog.text = "";
			link.l1 = "Doğal olarak, yarın bu yığının bir dağa dönüşme ihtimali beni endişelendiriyor, ama beni asıl korkutan şey, bütün bu kanın tek bir kişi yüzünden dökülüyor olması. Üstelik o kişi, tayfamda önemli bir yere sahip!";
			link.l1.go = "tonzag_drink_again_1";
		break;
		
		case "tonzag_drink_again_1":
			dialog.text = "";
			link.l1 = "İkincisi, bana yalan söyledin, Hercule. Eski meslektaşlarının seni ortadan kaldırmak için gösterdiği çabaya değecek bir kaçak yok. Mahzende tutsak ne diye bağırıyordu? Hain mi? Porto Bello mu? Gruoch mu? Bir şey yaptın, Hercule, ve bu sefer gerçeği bilmek istiyorum.";
			link.l1.go = "tonzag_drink_again_2";
		break;
		
		case "tonzag_drink_again_2":
			dialog.text = "Truth? The truth is, Captain, that I did desert, along with my wife Gruoh. Madame Tonzag didn't want to leave the League; she loved that life, but she loved me even more. We were supposed to take care of a Spanish hidalgo, but he made a better offer. It was our chance, and we both agreed to go into his service. Of course, the League thought we perished on a mission and sent a second group to Porto Bello to finish the job and seek revenge.";
			link.l1 = "Hepsini sen mi öldürdün?";
			link.l1.go = "tonzag_drink_again_3";
		break;
		
		case "tonzag_drink_again_3":
			dialog.text = "Önce Gruoh'u öldürdüler ve beni sakat bıraktılar. Hidalgo artık benimle hiçbir şey yapmak istemedi ve beni kovdu. İşte o zaman Rodenburg beni buldu...";
			link.l1 = "Şimdi sana nasıl güvenmemi bekliyorsun? Orduyu terk ettin, Birliği terk ettin, kendi ortaklarını öldürdün! Doğru an geldiğinde beni de mi satacaksın?";
			link.l1.go = "tonzag_drink_again_4";
		break;
		
		case "tonzag_drink_again_4":
			dialog.text = "Evet, firar ettim, sözleşmeyi bozdum, bir düzine kadar Lig üyesini öldürdüm. Ama o dersi aldım, Kaptan. Hem, ölü bir adam kimseye ihanet edemez, ben de Porto Bello'dan beri ölü sayılırım. Belki de bu yüzden artık beni öldürmek bu kadar zor.";
			link.l1 = "Bugünlük bu kadar yeter. Hâlâ bana her şeyi anlatmadığını hissediyorum.";
			link.l1.go = "tonzag_drink_again_5";
		break;
		
		case "tonzag_drink_again_5":
			dialog.text = "Tutsağı kendim halledeceğim, yoksa sen de katılmak ister misin?";
			link.l1 = "Hadi gidelim. Onu bizzat ben sorgulayacağım.";
			link.l1.go = "tonzag_drink_again_hold";
			link.l2 = "Hayır, bu işler bana göre değil. Yarım saat sonra kamarama gel, görüşürüz!";
			link.l2.go = "tonzag_drink_again_cabin";
		break;
		
		case "tonzag_drink_again_hold":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;
		
		case "tonzag_drink_again_cabin":
			DialogExit();
			
			NextDiag.CurrentNode = "tonzag_officer";
			AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;
		
		case "tonzag_hold":
			dialog.text = "Şimdi kim yönetiyor? Arno mu?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;
		
		case "tonzag_hold_1":
			dialog.text = "O pislik mi başa geçti? Sıradan bir haydut çetesine dönüşmeniz uzun sürmemiş...";
			link.l1 = "Austin kim?";
			link.l1.go = "tonzag_hold_2";
		break;
		
		case "tonzag_hold_2":
			dialog.text = "Austin'ın çetesi, özgür kaptanları ıssız yerlere çekip öldürmekte ve cesetlerinden para ya da değerli ne varsa soymakta ünlüydü. İyi bir işti, macera arayan eksik olmazdı, kimse de pek aldırmazdı. Ama bir kaptanla başları derde girdi, bu yüzden adamını Şirket'in koruması altına almak zorunda kaldı. Biz de onu tasmalı tuttuk, sadece işler hızlı ve basit çözülmesi gerektiğinde salıverdik.";
			link.l1 = "Böyle biriyle bir anlaşma yapabileceğimden şüpheliyim.";
			link.l1.go = "tonzag_hold_3";
		break;
		
		case "tonzag_hold_3":
			dialog.text = "Orası kesin. Eğer şimdi işleri o ve adamları yönetiyorsa, Lig yakında sıradan bir çeteye dönüşecek.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;
		
		case "tonzag_after_hold":
			dialog.text = "İlginç bir sohbetti.";
			link.l1 = "Gerçekten ne kadarı doğru, bilmek isterim... Peki ya Porto Bello’daki katliam? Eğer yalan söylemiyorsa, demek ki seninle en son konuştuğumuzda, o meşhur hayat hikayenden yine birkaç önemli ayrıntıyı gizlemişsin.";
			link.l1.go = "tonzag_after_hold_1";
		break;
		
		case "tonzag_after_hold_1":
			dialog.text = "Porto Bello'da hava çok sıcaktı, Kaptan. Kendi hayatım, işverenimin hayatı, karımın hayatı için savaştım. Sokakta yanlış zamanda bulunan her köylüyü saymaya ya da yasını tutmaya vaktim yoktu.";
			link.l1 = "Bu öncelik sırasına göre mi?";
			link.l1.go = "tonzag_after_hold_2";
		break;
		
		case "tonzag_after_hold_2":
			dialog.text = "Hayır, tabii ki hayır. Önce onunki. Her zaman.";
			link.l1 = "Ne dersin? Caracas'a gidelim mi?";
			link.l1.go = "tonzag_after_hold_3";
		break;
		
		case "tonzag_after_hold_3":
			dialog.text = "Ben şahsen gitmezdim, Kaptan. Size de gitmemenizi tavsiye ederim. Lig için artık bir düşman değilsiniz, ben de onların ilgisini çekmiyorum, en azından şimdilik sizin hizmetinizdeyken. Ayrıca içimde kötü bir his var\nOraya gidersek kötü olacak. Hem de çok kötü. Bu hikâyenin mutlu bir sonu yok. Ama sonuna kadar yanınızda olacağım, Kaptan.";
			link.l1 = "Düşüneceğim.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_hold_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_hold_4":
			dialog.text = "";
			link.l1 = "Bu arada, haklıydın – madeni yeterince iyi temizleyememişler. Bak.";
			link.l1.go = "tonzag_after_hold_5";
		break;
		
		case "tonzag_after_hold_5":
			dialog.text = "Bir subayın günlüğü... şifreli, ama eski bir şifre bu, biliyorum\nGörünüşe göre ilginç bir şey yok. Bu, tutsağımızın günlüğüymüş. Artık neden bu kadar konuşkan olduğunu anlıyorum. Bak şuraya – gizli bir hazineye dair işaretler var! Alçak herif, açıkça emekli olmayı planlamış ve her an sıvışmaya hazırmış!";
			link.l1 = "Ve bu gizli yer nerede?";
			link.l1.go = "tonzag_after_hold_6";
		break;
		
		case "tonzag_after_hold_6":
			dialog.text = "O adayı biliyorsun, Kaptan. O sularda Van Berd'i bitirdin.";
			link.l1 = "Pekala, çok uzak değil, gidip bakalım. Caracas'a gelince, henüz karar vermedim ama sanırım bir ayımız var.";
			link.l1.go = "tonzag_after_hold_7";
		break;
		
		case "tonzag_after_hold_7":
			dialog.text = "Dediğiniz gibi, Kaptan. Sonuna kadar yanınızdayım.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_after_drink":
			dialog.text = "It's done, Captain. Austin is currently in Caracas; I think we have a month.";
			link.l1 = "Öncelikle en baştan başlayalım. Mahkum ne dedi? Bu Austin de kim? Ve neden Caracas'a gitmeliyiz?";
			link.l1.go = "tonzag_after_drink_1";
		break;
		
		case "tonzag_after_drink_1":
			dialog.text = "Austin'ın çetesi, özgür Kaptanları vahşi doğaya çekip parçalaması ve cesetlerinden para ya da değerli eşyaları tamamen soymasıyla ünlüydü. İyi bir işti, macera peşinde koşanlar hiç eksik olmazdı, bu yüzden kimse aldırmazdı. Ama bir Kaptan'la işler ters gitti, bu yüzden adamlarını Şirket'in koruması altına almak zorunda kaldı. Biz de onu kısa bir ipte tuttuk, sadece hızlı ve kolay bir çözüme ihtiyacımız olduğunda serbest bıraktık.";
			link.l1 = "Böyle biriyle bir anlaşma yapabileceğimden şüpheliyim.";
			link.l1.go = "tonzag_after_drink_2";
		break;
		
		case "tonzag_after_drink_2":
			dialog.text = "Orası kesin. Eğer şimdi o ve adamları yönetimdeyse, Lig yakında sıradan bir çeteye dönüşür. Ama ben olsam Karakas'a gitmezdim, Kaptan.";
			link.l1 = "Cidden mi? Korkuyor musun?";
			link.l1.go = "tonzag_after_drink_3";
		break;
		
		case "tonzag_after_drink_3":
			dialog.text = "Öyle değil, Kaptan. Yaralarından ölmeden önce, tutsak senin artık Lig'in düşmanı olmadığını söyledi ve ben de onlara ilgisizim, en azından şimdilik senin hizmetindeyken. Görünüşe göre Lig'in yeni, güçlü bir hamisi var ve o, bize dokunmamalarını emretmiş.\nVe Caracas... İçimde kötü bir his var... Oraya gidersek başımıza kötü şeyler gelecek. Hem de çok kötü. Bu hikâyenin mutlu sonu yok. Ama sonuna kadar yanında olacağım, Kaptan.";
			link.l1 = "Düşüneceğim. Elbette, bu meseleyi bir an önce kökünden çözmek isterim, ama belki de haklısın. Geçen haftaki olaylardan sonra, bir daha bize yaklaşmaya cesaret edeceklerini sanmıyorum.";
			link.l1.go = "exit";
			
			if (CheckCharacterItem(pchar, "MerdokArchive")) {
				link.l1.go = "tonzag_after_drink_4";
			}
			
			AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;
		
		case "tonzag_after_drink_4":
			dialog.text = "";
			link.l1 = "Bu arada, haklıydın – madeni yeterince temizleyememişler. Bak.";
			link.l1.go = "tonzag_after_drink_5";
		break;
		
		case "tonzag_after_drink_5":
			dialog.text = "Bir subayın günlüğü... şifreli, ama eski bir şifre, biliyorum bunu\nPek ilginç bir şey yok gibi. Bu, mahkumumuzun günlüğüymüş. Bak şuraya – gizli bir hazineye dair işaretler var! Alçak herif açıkça emekli olmayı planlamış ve her an tüymeye hazırmış!";
			link.l1 = "Ve bu gizli yer nerede?";
			link.l1.go = "tonzag_after_drink_6";
		break;
		
		case "tonzag_after_drink_6":
			dialog.text = "O adayı biliyorsun, Kaptan. O sularda Van Berd'i bitirdin.";
			link.l1 = "Pekala, çok uzak değil, gidip bakalım. Caracas'a gelince, henüz karar vermedim ama sanırım bir ayımız var.";
			link.l1.go = "tonzag_after_drink_7";
		break;
		
		case "tonzag_after_drink_7":
			dialog.text = "Dediğiniz gibi, Kaptan.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;
		
		case "tonzag_church":
			dialog.text = "Bekle, Kaptan. Oraya tek başıma gidiyorum.";
			link.l1 = "And why is that? Feeling heroic now? It's too late; you've made this mess, but we have to clean it together.";
			link.l1.go = "tonzag_church_1";
		break;
		
		case "tonzag_church_1":
			dialog.text = "Benim hatalarımın bedelini ödemenize gerek yok, Kaptan. Haklıydınız - nereye gitsem, insanlar ölüyor ve masum kanı dökülüyor. O kiliseye birlikte girersek, bir Porto Bello daha yaşanacak, bunu istemiyorum.";
			link.l1 = "Orada gerçekten ne oldu?";
			link.l1.go = "tonzag_church_2";
		break;
		
		case "tonzag_church_2":
			dialog.text = "Bir katliam. Emekli olmak istiyordum, Kaptan. Altını, karımı alıp Carcassonne'a dönmek istiyordum. Ligin işimi bitirmek için daha fazla adam göndereceğini biliyordum, bu yüzden yeni hamimden cömert bir avans aldım. Sonra geriye sadece şehir muhafızlarını eski ortaklarıma ve yeni işverene karşı kışkırtmak kaldı. Bütün o kargaşada, parayla birlikte ortadan kaybolacaktım, belki zaman kalırsa Porto Bello'nun birkaç zenginini de soymayı düşünüyordum.";
			link.l1 = "Güzel bir plan, ama ben olsam farklı yapardım. Çok fazla şey ters gidebilir.";
			link.l1.go = "tonzag_church_2a";
			link.l2 = "Ben de melek sayılmam, ama senin yöntemlerin beni bile ürkütüyor. Şimdiye kadar bana ihanet etmemiş olmana şaşıyorum, sonuçta Lige, Hidalgo'ya ve hatta kendi karına bile ihanet ettin.";
			link.l2.go = "tonzag_church_2a";
		break;
		
		case "tonzag_church_2a":
			dialog.text = "Everything that could go wrong, did go wrong. Shooting a three-pounder towards the governor's palace was a mistake. It barely scratched the governor himself, but his beautiful daughter, as I hear, had to have both her legs amputated below the knees to save her life. The response was horrific - a blood bath; great many people perished, Captain. Now you're looking at the last living witness to those events, and not long ago, you cut down another one yourself.";
			link.l1 = "Açıkla.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_2b":
			dialog.text = "Eğer Madame Tonzag hâlâ hayatta olsaydı, seni hiç tereddüt etmeden satardım, Kaptan. Ben ölü bir adamım, bu dünyada başka bir yerim olmadığı için peşinden geliyorum. Şimdi o olayların hayattaki son tanığına bakıyorsun ve kısa süre önce bir diğerini de bizzat sen ortadan kaldırdın.";
			link.l1 = "Açıkla.";
			link.l1.go = "tonzag_church_3";
		break;
		
		case "tonzag_church_3":
			dialog.text = "Beni affedin, Kaptan, yol boyunca size her şeyi anlatmadığım için. İlk tanıştığımızda, sizi de benim gibi sıradan bir serseri sandım. Ve biliyor musunuz, ilk yaptığım şey neydi? Sizi arkamı toplamanız için gönderdim – başta öldürmek istemediğim, sonra ise ihanete karar verdiğim o İspanyol Don'u öldürmeye. O hidalgo, Rodriguez...";
			link.l1 = "Ve onun parmağına neden ihtiyacın vardı?";
			link.l1.go = "tonzag_church_4";
		break;
		
		case "tonzag_church_4":
			dialog.text = "Burada numara yok. Sadece bir test, Kaptan. Her yıl senin gibi onlarca genç haydutu işe alıyoruz. Sadece birkaçı temel dürüstlük testinden geçiyor, onlar da ilk görevlerde ölüyor. Fleetwood'un seyir defteriyle yaptığın operasyondan sağ çıkman beklenmiyordu. Ben sadece eve girip, sağ kalanları temizleyip defteri almayı planlamıştım.";
			link.l1 = "Hafızam beni yanıltmıyorsa, hikaye biraz farklı bir yöne sapmıştı.";
			link.l1.go = "tonzag_church_5";
		break;
		
		case "tonzag_church_5":
			dialog.text = "Öyle oldu, Kaptan. Size yardım etmeye neyin ittiğini bilmiyorum, ama Tilkilere karşı öyle bir yaşama sevinciyle savaştınız ki, o coşkunuz bana bile bulaştı, en azından bir anlığına. Sonunda, farkında olmadan, beni kurtardınız. Bana hiçbir borcunuz yok, Kaptan. Ve sizi oraya bırakmam. Bu benim meselem, benim kefaretim.";
			link.l1 = "Dediğin gibi olsun, Hercule. Böyle bir savaşçıyı kaybetmek acı veriyor, ama sen kendini çoktan kaybettin ve artık dökülecek kana değmezsin. Bana da hiçbir borcun yok, umarım o küçük kilisede kendini affettirirsin.";
			link.l1.go = "tonzag_church_bad";
			link.l2 = "Güzel konuşma, Hercule. Cehenneme git! Fark etmediysen, son zamanlarda senin dertlerin benimkiler oldu. Artık benim subayımsın ve affı hak edip etmediğine sadece ben karar veririm. Bu yüzden bizimle biraz daha kalacaksın ve ekibimin bir parçası olarak cesaretinle kurtuluşunu kazanacaksın!";
			link.l2.go = "tonzag_church_good";
		break;
		
		case "tonzag_church_bad":
			dialog.text = "Her şey için teşekkür ederim, Kaptan. Elveda!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;
		
		case "tonzag_church_good":
			dialog.text = "Emredersiniz, Kaptan!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;
		
		case "tonzag_afterchurchfight":
			dialog.text = "Ben de hayatımda çok alçak gördüm, Kaptan, ama ilk kez içimde bir ürperti hissettim. Ne dersiniz: küçük bir canavar büyük bir canavarı öldürürse, bu bir tür kefaret sayılır mı?";
			link.l1 = "Romun içine su katıyorlar mı? Çözdüğünde bana da söyle. Hadi gidelim, burada işimiz bitti.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;
		
		// Эпилог
		case "SharlieEpilog_Tonzag_1":
			dialog.text = "Ha! Bunu senden duyacağımı düşünmemiştim. Sırada ne var — bir manastıra mı gitmek istiyorsun?";
			link.l1 = "Ciddiyim, "+npchar.name+". Babamın sağlığı her geçen gün kötüleşiyor. Çok geç olmadan onu görmek istiyorum.";
			link.l1.go = "SharlieEpilog_Tonzag_2";
		break;

		case "SharlieEpilog_Tonzag_2":
			dialog.text = "Gemimizde ne var yani? Yoksa gerçekten Atlantik artık bizim için fazla mı geliyor?";
			link.l1 = "Karaya çıkıp yerleşmeyi düşündüm. Henüz denizsiz bir yaşamı hayal edemiyorum. Ama böyle bir gün gerçekten gelirse, buna hazır olmak istiyorum. İçimde neyle mücadele etmem gerektiğini anlamak istiyorum.";
			link.l1.go = "SharlieEpilog_Tonzag_3";
		break;

		case "SharlieEpilog_Tonzag_3":
			dialog.text = "Bu konuşmada iki kere beni şaşırttın. Gerçekten yelkenlerdeki rüzgârı bir şömine ve sıcak bir kaşık tahıla mı değiştiriyorsun?";
			link.l1 = "Babamın hastalığının kötüleşmesi bana hiç kimsenin sonsuz olmadığını hatırlattı. Sonrasında ne olacağını henüz karar vermedim. Şimdilik — sadece eve dönüş yolu. Ve… seninle gelmeni istemiştim. Bir arkadaş olarak. Ama eğer hayır dersen — anlarım. Israr etmeyeceğim.";
			link.l1.go = "SharlieEpilog_Tonzag_4";
		break;

		case "SharlieEpilog_Tonzag_4":
			dialog.text = "Hayır mı? Seni yalnız bırakırsam ömrüm boyunca çapayı temizlemek zorunda kalırım! Beni pek tanımıyorsun, kaptan.";
			link.l1 = "Tam da beklediğim cevap bu. Eski Fransa artık eskisi gibi değil. Çok boş, sıkıcı, yabancı… Orada dost diye çağırabileceğim birinin kaldığını sanmıyorum. İki hafta içinde yelken açıyoruz ve zaman kaybetmek niyetinde değilim. Kalkışımızı kutlamak için tavernada bir şenlik düzenleyelim. Ne dersin?";
			link.l1.go = "SharlieEpilog_Tonzag_5";
		break;

		case "SharlieEpilog_Tonzag_5":
			dialog.text = "Ha! Eğer hayır diyeceğimi sanıyorsan — çok bekleyeceksin!";
			link.l1 = "O zaman karar verildi — işlerimi halletir halletmez tavernada görüşürüz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tonzag_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Tonzag = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;

	}
}